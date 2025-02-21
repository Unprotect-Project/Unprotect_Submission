# *Halo's Gate for EDR Evasion*

## Authorship information
* Contribution Authorship : 0x0d4y
* Email    : 0x0d4y_researcher@0x0d4y.blog
* Blog     : https://0x0d4y.blog/
* LinkedIn : https://www.linkedin.com/in/icaro-cesar/

## New Technique Information

* Technique Title: *Halo's Gate for EDR Evasion*
* Technique Category : Antivirus/EDR Evasion
* Technique description: **Halo's Gate** is an evasion technique used by malware to bypass Endpoint Detection and Response (EDR) solutions by directly invoking system calls (syscalls) in Windows, avoiding monitored user-mode API hooks. It builds on concepts from techniques like *Hell's Gate* and *Syswhispers* but introduces refinements to further obfuscate malicious activity. This technique was recently identified being used by the new Loader called *`BabbleLoader`*. **Halo's Gate** is an evolution of the *Hell’s Gate* technique, both aimed at bypassing EDR hooks. They detect unhooked syscall stubs by checking for specific opcodes (e.g., `0x4c 0x8b 0xd`1 and `0xb8` followed by the *SSN*). If a `0xe9` (`jmp` to EDR hook) is found, the function is hooked. **Halo's Gate** improves by analyzing *SSNs* of unhooked neighboring APIs (since *SSNs* are sequential) to calculate the target API’s correct *SSN*, enabling execution without triggering EDR hooks.

## Additional Resources:

* [A Deep Dive into EDR and Machine Learning-Based Endpoint Protection Evasion](https://0x0d4y.blog/babbleloader-deep-dive-into-edr-and-machine-learning-based-endpoint-protection-evasion/)
* [EDR Bypass: Retrieving Syscall ID with Hell's Gate, Halo's Gate, FreshyCalls and Syswhispers2](https://alice.climent-pommeret.red/posts/direct-syscalls-hells-halos-syswhispers2/)
