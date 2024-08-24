/**
 * QEMU has the CPU brand value of "QEMU Virtual CPU" if KVM is not based on the VM.
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
}


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


// main code, checks if the CPU brand matches with QEMU's
bool cpu_brand_qemu() {
    std::string brand = get_brand();

    std::regex qemu_pattern("QEMU Virtual CPU", std::regex_constants::icase);

    if (std::regex_match(brand, qemu_pattern)) {
        return true;
    }

    return false;
}


int main() {
    std::cout << "is the CPU brand \"QEMU Virtual CPU\"? = " << (cpu_brand_qemu() ? "Yes, very likely a QEMU CPU\n" : "No, most likely baremetal\n");
}