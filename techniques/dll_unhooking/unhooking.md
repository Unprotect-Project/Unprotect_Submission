# DLL Unhooking

## Authorship information
* Name or nickname : Dreamkinn
* Twitter: https://twitter.com/dreamkinn
  
## Technique Information
* Technique title : DLL Unhooking
* Technique category : Antivirus/EDR evasion
* Technique description : EDRs modify sensitive system functions within processes loaded DLLs in order to be able to inspect their usage. They do so by patching the first instructions of the functions within the DLLs so that when they are called, the execution flow of the program is hijacked and is sent to the EDR's code (inside a DLL loaded by the EDR in the program). There,  the EDR has time to inspect the arguments of the function and decide whether or not the usage is legitmate or malicious. If the usage is judged legitimate, the execution flow of the program is restored and the function is called normally. This type of "live patching" of the system DLLs is called **hooking**. In order to bypass the EDR's inspection, malware can "unhook" the functions that it needs to use. It could do so by restoring the original state of the whole DLL code section (.text). In order to perform this action, the malware needs access to a "clean" (unhooked) DLL, it can find it 1) on the system (can be detected with the open handle), 2) opening a remote file (the malware author needs to remotely host a DLL matching the OS version of the target system), or even 3) start a suspended process and retrieve the content of its DLL before it gets hooked. The DLL that is usually hooked/unhooked is the NTDLL.dll (at it is the closest to the kernel), however some EDRs can also hook higher-level APIs contained in e.g. kernel32.dll or user32.dll.

## Additional resources
* https://github.com/optiv/Freeze
* https://www.ired.team/offensive-security/defense-evasion/how-to-unhook-a-dll-using-c++

## Code snippets
* unhook.cpp
