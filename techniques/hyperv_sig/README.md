# Hyper-V signature evasion

## Authorship information
* Name: kernelwernel
* Website: https://github.com/kernelwernel

## Technique Information
* Technique title: Hyper-V signature
* Technique category: Sandbox evasion
* Technique description: Hyper-V has a signature value of "Hv#1" in eax if leaf `0x40000001` is provided to CPUID.

## Additional resources
* https://github.com/kernelwernel/VMAware
* https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/feature-discovery

## Code snippets
* hyperv_sig.cpp