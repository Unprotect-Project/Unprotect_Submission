# EDR/AV evasion using direct syscalls and assembly

### Features:
 - No encryption
 - No VirtualAlloc
 - No CreateThread
 - Direct execution of payload on heap using assembly and returning back

NOTE: This is a PoC. There are hard-coded values like syscall number. This can be extended futher by using hellsgate or other similar variations like Syswhispers.

### Credits
 - Steve - For his quality research posted on https://steve-s.gitbook.io/0xtriboulet/
 - chatGPT, Google and other innumerable resources
 - https://defuse.ca/online-x86-assembler.htm
