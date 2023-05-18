#include <Windows.h>
#include <iostream>
#include <intrin.h>

/// See: Feature Information Returned in the ECX Register
union CpuFeaturesEcx {
    ULONG32 all;
    struct {
        ULONG32 sse3 : 1;       //!< [0] Streaming SIMD Extensions 3 (SSE3)
        ULONG32 pclmulqdq : 1;  //!< [1] PCLMULQDQ
        ULONG32 dtes64 : 1;     //!< [2] 64-bit DS Area
        ULONG32 monitor : 1;    //!< [3] MONITOR/WAIT
        ULONG32 ds_cpl : 1;     //!< [4] CPL qualified Debug Store
        ULONG32 vmx : 1;        //!< [5] Virtual Machine Technology
        ULONG32 smx : 1;        //!< [6] Safer Mode Extensions
        ULONG32 est : 1;        //!< [7] Enhanced Intel Speedstep Technology
        ULONG32 tm2 : 1;        //!< [8] Thermal monitor 2
        ULONG32 ssse3 : 1;      //!< [9] Supplemental Streaming SIMD Extensions 3
        ULONG32 cid : 1;        //!< [10] L1 context ID
        ULONG32 sdbg : 1;       //!< [11] IA32_DEBUG_INTERFACE MSR
        ULONG32 fma : 1;        //!< [12] FMA extensions using YMM state
        ULONG32 cx16 : 1;       //!< [13] CMPXCHG16B
        ULONG32 xtpr : 1;       //!< [14] xTPR Update Control
        ULONG32 pdcm : 1;       //!< [15] Performance/Debug capability MSR
        ULONG32 reserved : 1;   //!< [16] Reserved
        ULONG32 pcid : 1;       //!< [17] Process-context identifiers
        ULONG32 dca : 1;        //!< [18] prefetch from a memory mapped device
        ULONG32 sse4_1 : 1;     //!< [19] SSE4.1
        ULONG32 sse4_2 : 1;     //!< [20] SSE4.2
        ULONG32 x2_apic : 1;    //!< [21] x2APIC feature
        ULONG32 movbe : 1;      //!< [22] MOVBE instruction
        ULONG32 popcnt : 1;     //!< [23] POPCNT instruction
        ULONG32 reserved3 : 1;  //!< [24] one-shot operation using a TSC deadline
        ULONG32 aes : 1;        //!< [25] AESNI instruction
        ULONG32 xsave : 1;      //!< [26] XSAVE/XRSTOR feature
        ULONG32 osxsave : 1;    //!< [27] enable XSETBV/XGETBV instructions
        ULONG32 avx : 1;        //!< [28] AVX instruction extensions
        ULONG32 f16c : 1;       //!< [29] 16-bit floating-point conversion
        ULONG32 rdrand : 1;     //!< [30] RDRAND instruction
        ULONG32 not_used : 1;   //!< [31] Always 0 (a.k.a. HypervisorPresent)
    } fields;
};
static_assert(sizeof(CpuFeaturesEcx) == 4, "Size check");

const bool IsHyperV()
{
	int cpu_info[4] = {};
	__cpuid(cpu_info, 1);
	const CpuFeaturesEcx cpu_features = { static_cast<ULONG_PTR>(cpu_info[2]) };
    __cpuid(cpu_info, 0x40000001);
    DWORD vid = 0;
    vid = (DWORD)cpu_info[0];
    return (vid >= 4000);
}

int main()
{
    if (IsHyperV()) {
        std::cout << "Hyper-v Ture" << std::endl;
    }
    else {
        std::cout << "Hyper-v Flase" << std::endl;
    }
    return 0;
}