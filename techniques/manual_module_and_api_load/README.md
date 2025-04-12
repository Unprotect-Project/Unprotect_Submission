# *PE Parsing for manual Module Loading and API Call*

## Authorship information
* Contribution Authorship : 0x0d4y
* Email    : 0x0d4y_researcher@0x0d4y.blog
* Blog     : https://0x0d4y.blog/
* LinkedIn : https://www.linkedin.com/in/icaro-cesar/

## New Technique Information

* Technique Title: *PE Parsing for manual Module Loading and API Call*
* Technique Category : Antivirus/EDR Evasion
* Technique description: This technique is widely used by malware to load modules and APIs without having to use Windows APIs like LoadLibrary, GetModuleHandle, etc. Thus, the technique can also be called Walking to the PEB, as the malware accesses the PEB to access a specific DLL, parses it to access the Export Table, and finally collects the API address. For example, through the Walking to the PEB technique, malware can find modules like NtDLL and then parse the PE file to load it and find the required APIs. This way, the malware remains stealthy, without the need to call APIs that will be Hooked by the Endpoint Protection Software.

## Additional Resources:

* [A Deep Dive into EDR and Machine Learning-Based Endpoint Protection Evasion](https://0x0d4y.blog/babbleloader-deep-dive-into-edr-and-machine-learning-based-endpoint-protection-evasion/): *BabbleLoader* performs the NtDLL Parsing process, with the aim of loading certain APIs.
* [Dive into PEB Walk in Malware Analysis](https://fareedfauzi.github.io/2024/07/13/PEB-Walk.html): This article explains in detail the Walking to the PEB technique.
