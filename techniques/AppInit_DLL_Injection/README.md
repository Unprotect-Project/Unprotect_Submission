# *AppInit DLL Injection*

## Authorship information
* Issac Briones (@1d8)
* https://1d8.github.io
* https://linkedin.com/in/icyber
  
## Technique Information
* Technique Title: *AppInit DLL Injection*
* Technique category (required): *Process Manipulating*
* Technique description (required): Any **Dynamic Link Libraries (DLL)** that are specified within the `AppInit_DLLs` registry key values are loaded by user32.dll into any process that utilizes user32.dll. So by modifying the `AppInit_DLLs` registry key value and pointing it to a malicious DLL, an attacker can force the system to load their DLL into every process that utilizes user32.dll and force it to execute their code.

## Additional resources
* https://attack.mitre.org/techniques/T1546/010/
