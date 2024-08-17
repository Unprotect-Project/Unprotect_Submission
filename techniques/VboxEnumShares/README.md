# *VboxEnumShares*

## Authorship information
* Nickname: *HoIIovv*
* Twitter: https://twitter.com/HoIIovv
* Website: https://nicolabottura.github.io/
* Linkedin: https://www.linkedin.com/in/nicola-bottura/
  
## Technique Information
* Technique title: VboxEnumShares
* Technique category: Anti-VM
* Technique Description: This method represents a variation of the `WNetGetProviderName(WNNC_NET_RDR2SAMPLE, ...)` approach, which is typically employed to determine if the network share's provider name is specific, such as VirtualBox. Instead of relying on this well-established technique, we utilize `WNetOpenEnum` and `WNetEnumResource` functions to iterate through each network resource. The primary objective is to identify VirtualBox shared folders, which typically feature "VirtualBox" or "VBoxSrv" substrings in their names. The latter, VBoxSrv, serves as a pseudo-network redirector provided by VirtualBox, enabling access to shared folders within the guest OS. These folders are sub-resources of the VirtualBox Shared Folder resource. By systematically enumerating these folders, a malware sample can ascertain the presence of the hypervisor in an alternative manner.

YARA rules are not provided due to the potential for false positives when searching for the two mentioned APIs. However, it's important to consider these APIs during the analysis of evasive samples.