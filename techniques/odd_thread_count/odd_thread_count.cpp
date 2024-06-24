/**
 * The thread count of the CPU must be an even number, which allows 
 * us to detect whether the thread count has been modified through 
 * the VM creation stage. If the thread count is not an even number, 
 * this is a sign of thread tampering (with a few exceptions which 
 * are already covered).
 *
 * This code snippet is from the VMAware project at https://github.com/kernelwernel/VMAware
 * detection made by kernelwernel, 2024
 */

#if (defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__))
#define MSVC 1
#define LINUX 0
#elif (defined(__linux__))
#define MSVC 0
#define LINUX 1
#else
#define MSVC 0
#define LINUX 0
#endif

#if (LINUX)
#include <cpuid.h>
#elif (MSVC)
#include <intrin.h>
#endif

#include <cstdint>
#include <thread>
#include <array>
#include <iostream>

/*
 * @brief Check for odd CPU threads, usually a sign of modification through VM setting because 99% of CPUs have even numbers of threads
 */ 
bool odd_cpu_threads() {
    struct stepping_struct {
        std::uint8_t model;
        std::uint8_t family;
        std::uint8_t extmodel;
    };

    struct stepping_struct steps {};

    // cross-platform wrapper function for linux and MSVC cpuid
    auto cpuid = [](
        std::uint32_t& a, 
        std::uint32_t& b, 
        std::uint32_t& c, 
        std::uint32_t& d,
        const std::uint32_t a_leaf
    ) -> void {
#if (MSVC)
        std::int32_t x[4]{};
        __cpuid((std::int32_t*)x, static_cast<std::int32_t>(a_leaf));
        a = static_cast<std::uint32_t>(x[0]);
        b = static_cast<std::uint32_t>(x[1]);
        c = static_cast<std::uint32_t>(x[2]);
        d = static_cast<std::uint32_t>(x[3]);
#elif (LINUX)
        __get_cpuid(a_leaf, &a, &b, &c, &d);
#else
        return;
#endif
    };

    auto is_intel = [&]() -> bool {
        constexpr std::uint32_t intel_ecx = 0x6c65746e;

        std::uint32_t unused, ecx = 0;
        cpuid(unused, unused, ecx, unused, 0);

        return (ecx == intel_ecx);
    };

    auto is_amd = [&]() -> bool {
        constexpr std::uint32_t amd_ecx = 0x69746e65;

        std::uint32_t unused, ecx = 0;
        cpuid(unused, unused, ecx, unused, 0);

        return (ecx == amd_ecx);
    };

    std::uint32_t unused, eax = 0;
    cpuid(eax, unused, unused, unused, 1);

    steps.model    = ((eax >> 4)  & 0b1111);
    steps.family   = ((eax >> 8)  & 0b1111);
    steps.extmodel = ((eax >> 16) & 0b1111);
    
    // check if the CPU is an intel celeron
    auto is_celeron = [&]() -> bool {
        if (!is_intel()) {
            return false;
        }

        constexpr std::uint8_t celeron_family   = 0x6;
        constexpr std::uint8_t celeron_extmodel = 0x2;
        constexpr std::uint8_t celeron_model    = 0xA;

        return (
            steps.family   == celeron_family   &&
            steps.extmodel == celeron_extmodel && 
            steps.model    == celeron_model
        );
    };

    // check if the microarchitecture was made before 2006, which was around the time multi-core processors were implemented
    auto old_microarchitecture = [&]() -> bool {
        constexpr std::array<std::array<std::uint8_t, 3>, 32> old_archs = {{
            // 80486
            {{ 0x4, 0x0, 0x1 }},
            {{ 0x4, 0x0, 0x2 }},
            {{ 0x4, 0x0, 0x3 }},
            {{ 0x4, 0x0, 0x4 }},
            {{ 0x4, 0x0, 0x5 }},
            {{ 0x4, 0x0, 0x7 }},
            {{ 0x4, 0x0, 0x8 }},
            {{ 0x4, 0x0, 0x9 }},

            // P5
            {{ 0x5, 0x0, 0x1 }},
            {{ 0x5, 0x0, 0x2 }},
            {{ 0x5, 0x0, 0x4 }},
            {{ 0x5, 0x0, 0x7 }},
            {{ 0x5, 0x0, 0x8 }},

            // P6
            {{ 0x6, 0x0, 0x1 }},
            {{ 0x6, 0x0, 0x3 }},
            {{ 0x6, 0x0, 0x5 }},
            {{ 0x6, 0x0, 0x6 }},
            {{ 0x6, 0x0, 0x7 }},
            {{ 0x6, 0x0, 0x8 }},
            {{ 0x6, 0x0, 0xA }},
            {{ 0x6, 0x0, 0xB }},

            // Netburst
            {{ 0xF, 0x0, 0x6 }},
            {{ 0xF, 0x0, 0x4 }},
            {{ 0xF, 0x0, 0x3 }},
            {{ 0xF, 0x0, 0x2 }},
            {{ 0xF, 0x0, 0x10 }},

            {{ 0x6, 0x1, 0x5 }}, // Pentium M (Talopai)
            {{ 0x6, 0x1, 0x6 }}, // Core (Client)
            {{ 0x6, 0x0, 0x9 }}, // Pentium M
            {{ 0x6, 0x0, 0xD }}, // Pentium M
            {{ 0x6, 0x0, 0xE }}, // Modified Pentium M
            {{ 0x6, 0x0, 0xF }}  // Core (Client)
        }};

        constexpr std::uint8_t FAMILY   = 0;
        constexpr std::uint8_t EXTMODEL = 1;
        constexpr std::uint8_t MODEL    = 2;

        for (const auto& arch : old_archs) {
            if (
                steps.family   == arch.at(FAMILY)   &&
                steps.extmodel == arch.at(EXTMODEL) &&
                steps.model    == arch.at(MODEL)
            ) {
                return true;
            }
        }

        return false;
    };

    // if neither AMD or Intel, return false
    if (!(is_intel() || is_amd())) {
        return false;
    }

    // Intel Celeron CPUs are relatively modern, but they can contain a single or odd thread count
    if (is_celeron()) {
        return false;
    }

    // CPUs before 2006 had no official multi-core processors (for both AMD and Intel)
    if (old_microarchitecture()) {
        return false;
    }

    // Is the thread count odd?
    return (std::thread::hardware_concurrency() & 1);
}

int main() {
    std::cout << "\nIs the thread count odd? = " << (odd_cpu_threads() ? "Yes, very likely a VM" : "No, could be baremetal") << "\n";
    return 0;
}