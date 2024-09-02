/**
 * bochs has multiple oversights in its CPU emulation, which allows us to detect if we're running in a bochs emulator:
 *  - 1. bochs may have invalid CPU brands that don't exist.
 *  - 2. For AMD CPUs, the "p" in "processor" should be in capital, which bochs doesn't implement.
 *  - 3. AMD CPUs have easter eggs for their K7 and K8 CPUs ("IT'S HAMMER TIME"), but bochs does not implement this.
 *
 * Discovered by Peter Ferrie, Senior Principal Researcher, Symantec Advanced Threat Research peter_ferrie@symantec.com
 * https://pferrie.tripod.com/papers/attacks2.pdf
 * 
 * This code snippet is from the VMAware project at https://github.com/kernelwernel/VMAware
 * 
 * detection written by kernelwernel, 2024
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
#include <array>
#include <iostream>
#include <regex>
#include <string>
#include <cstring>


// cross-platform wrapper function for linux and MSVC cpuid
void cpuid(
    std::uint32_t& a, 
    std::uint32_t& b, 
    std::uint32_t& c, 
    std::uint32_t& d,
    const std::uint32_t a_leaf
) {
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
}

// checks if the leaf is high enough for the CPU to support
bool is_leaf_supported(const std::uint32_t p_leaf) {
    std::uint32_t eax, unused = 0;
    cpuid(eax, unused, unused, unused, 0x80000000);
    return (p_leaf <= eax);
};

// get the CPU product
std::string get_brand() {
    if (!is_leaf_supported(0x80000004)) {
        return "";
    }

    std::array<std::uint32_t, 4> buffer{};
    constexpr std::size_t buffer_size = sizeof(int32_t) * buffer.size();
    std::array<char, 64> charbuffer{};

    constexpr std::array<std::uint32_t, 3> ids = {{
        0x80000002,
        0x80000003,
        0x80000004
    }};

    std::string brand = "";

    for (const std::uint32_t& id : ids) {
        cpuid(buffer.at(0), buffer.at(1), buffer.at(2), buffer.at(3), id);

        std::memcpy(charbuffer.data(), buffer.data(), buffer_size);

        const char* convert = charbuffer.data();
        brand += convert;
    }

    return brand;
}


// main bochs detection code
bool bochs_cpu() {
    std::uint32_t unused, ecx = 0;
    cpuid(unused, unused, ecx, unused, 0);

    constexpr std::uint32_t amd_ecx    = 0x444d4163; // "cAMD" (AMD)
    constexpr std::uint32_t intel_ecx1 = 0x6c65746e; // "ntel" (Intel)
    constexpr std::uint32_t intel_ecx2 = 0x6c65746f; // "otel" (Intel), this is because some Intel CPUs have a rare manufacturer string of "GenuineIotel"

    const bool intel = ((ecx == intel_ecx1) || (ecx == intel_ecx2));
    const bool amd = (ecx == amd_ecx);

    // if neither amd or intel, return false
    if (!(intel || amd)) {
        return false;
    }

    const std::string brand = get_brand();

    if (intel) {
        // technique 1: not a valid brand 
        if (brand == "              Intel(R) Pentium(R) 4 CPU        ") {
            return true;
        }
    } else if (amd) {
        // technique 2: "processor" should have a capital P
        if (brand == "AMD Athlon(tm) processor") {
            return true;
        }

        // technique 3: Check for absence of AMD easter egg for K7 and K8 CPUs
        constexpr std::uint32_t AMD_EASTER_EGG = 0x8fffffff; // this is the CPUID leaf of the AMD easter egg

        if (!is_leaf_supported(AMD_EASTER_EGG)) {
            return false;
        }

        std::uint32_t unused, eax = 0;
        cpuid(eax, unused, unused, unused, 1);

        constexpr std::uint8_t AMD_K7 = 6;
        constexpr std::uint8_t AMD_K8 = 15;

        auto is_k7 = [](const std::uint32_t eax) -> bool {
            const std::uint32_t family = (eax >> 8) & 0xF;
            const std::uint32_t model = (eax >> 4) & 0xF;
            const std::uint32_t extended_family = (eax >> 20) & 0xFF;

            if (family == 6 && extended_family == 0) {
                if (model == 1 || model == 2 || model == 3 || model == 4) {
                    return true;
                }
            }

            return false;
        };

        auto is_k8 = [](const std::uint32_t eax) -> bool {
            const std::uint32_t family = (eax >> 8) & 0xF;
            const std::uint32_t extended_family = (eax >> 20) & 0xFF;

            if (family == 0xF) {
                if (extended_family == 0x00 || extended_family == 0x01) {
                    return true;
                }
            }

            return false;
        };

        if (!(is_k7(eax) || is_k8(eax))) {
            return false;
        }

        std::uint32_t ecx_bochs = 0;
        cpuid(unused, unused, ecx_bochs, unused, AMD_EASTER_EGG);

        if (ecx_bochs == 0) {
            return true;
        }
    }

    return false;
}


int main() {
    std::cout << "is bochs present? = " << (bochs_cpu() ? "Yes, very likely a bochs emulated CPU\n" : "No, most likely baremetal\n");
    return 0;
} 