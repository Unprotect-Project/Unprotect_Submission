# *Deleting Windows Volume Shadow Copy Service*

## Authorship information
* Nickname: *hackeT*
* Twitter: *https://twitter.com/T_8ase*
* Linkedin: *https://www.linkedin.com/in/tatsuya-hasegawa-aa3279142/*
  
## Technique Information
* Technique Title: **Volume Shadow Copy Service (VSC,VSS) Deletion**
* Technique category: **anti-forensic**
* MITRE ATT&CK category: **Impact::Inhibit System Recovery [T1490],  Defense Evasion::Indicator Removal on Host::File Deletion [T1070.004]**
* MBC category: **Impact::Data Destruction::Delete Shadow Copies [E1485.m04]**
* Technique description: Deleting Volume Shadow Copy makes the forensic investigation to be more difficult in terms of the recovery of previous artifact evidence. In addition, attackers using ransomware often delete VSCs not to be able to recover the original files of the encrypted files from VSCs. On the other hand, deleting by using vssadmin and wmic is on a file system level, the actual data remains in clusters. Thus it may be able to be recovered from VSC until other files overwrite the clusters.

### Well-Known techniques to delete VSC

**CMD**
- vssadmin.exe delete shadows /all /quiet
- wmic shadowcopy delete /nointeractive
- vssadmin resize shadowstorage /for=<backed volume> /on=<backup location volume> /maxsize=<new size>

**Powershell**
- Get-WmiObject Win32_ShadowCopy | % { $_.Delete() }
- Get-WmiObject Win32_Shadowcopy | ForEach-Object { $_Delete(); }
- Get-WmiObject Win32_ShadowCopy | Remove-WmiObject

**DLL**
- vssapi.dll (library of VSS api, used by Zepto ransomware)
 

## Additional resources
https://docs.microsoft.com/ja-jp/windows-server/administration/windows-commands/vssadmin-delete-shadows

https://www.fortinet.com/blog/threat-research/stomping-shadow-copies-a-second-look-into-deletion-methods

https://blogs.blackberry.com/en/2018/11/threat-spotlight-inside-vssdestroy-ransomware

https://blog.avast.com/zepto-ransomware-now-introduces-new-features-to-better-encrypt-your-files

http://www.kazamiya.net/DeletedSC

https://github.com/mnrkbys/vss_carver

https://www.shadowexplorer.com/


## Detection rules
**capa**

https://github.com/mandiant/capa-rules/blob/master/impact/inhibit-system-recovery/delete-volume-shadow-copies.yml

https://github.com/mandiant/capa-rules/blob/master/nursery/resize-volume-shadow-copy-storage.yml


**sigma**

https://github.com/SigmaHQ/sigma/blob/master/rules/windows/process_creation/proc_creation_win_shadow_copies_deletion.yml

https://github.com/SigmaHQ/sigma/blob/master/rules/windows/powershell/powershell_classic/posh_pc_delete_volume_shadow_copies.yml
