/**
 * Hyper-V has a signature value of "Hv#1" in eax if leaf `0x40000001` is provided to CPUID.
 *
 * This code snippet is from the VMAware project at https://github.com/kernelwernel/VMAware
 * 
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


bool hyperv_sig() {
    auto cpuid_eax = [](
        std::uint32_t& eax, 
        const std::uint32_t leaf
    ) -> void {
#if (MSVC)
        std::int32_t x[4]{};
        __cpuid((std::int32_t*)x, static_cast<std::int32_t>(leaf));
        eax = static_cast<std::uint32_t>(x[0]);
#elif (LINUX)
        std::uint32_t unused = 0;
        __get_cpuid(leaf, &eax, &unused, &unused, &unused);
#else
        return;
#endif
    };

    std::uint32_t eax = 0;
    cpuid_eax(eax, 0x40000001);

    constexpr std::uint32_t signature = 0x31237648; // "Hv#1"

    return (eax == signature);
}

int main() {
    std::cout << "Hyper-V's signature found? = " << (hyperv_sig() ? "Yes, very likely a Hyper-V VM" : "No, could be baremetal") << "\n";
    return 0;
}