# Domain Fronting

## Authorship Information
Myself :) probably other pentest guys

## Technique Information
* Technique Title: Cpu Count
* Technique Category: Sandbox Evasion

* Technique Description: In many Sandbox due to virtualisation constraint, The cpu count could be set to 1. In real live on workstations or servers, since more than a decade now, every x86 CPU are sell with multiple core or at least hyperthreading capacity simulating multiples cpu. Therefore it is possible under certain circonstances to detect virtualisation or sandbox by looking at the cpu count on the system. Even if it is possible to get this information by using windows API, WMI or looking into the registry, This is particulary interesting since this information is available without performing any api call. The number of CPU on the system may be collected by looking into the PEB which maintain this information. And for hyperthreading capacity it may be detected by asking it directly to the CPU using the CPUID instruction.
