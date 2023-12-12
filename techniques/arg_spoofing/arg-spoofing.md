# Process Argument Spoofing

## Authorship information
* Name or nickname : nuts7
* Twitter: https://twitter.com/__nuts7

## Technique Information
* Technique title : Process Argument Spoofing
* Technique category : Process Manipulating
* Technique description : Process Argument Spoofing is a technique that allows attackers to stomping the command line argument of a newly spawned process by updating Process Environment Block (PEB) structure, more specifically by patching the buffer of CommandLine attribute (UNICODE_STRING name structure data type) in RTL_USER_PROCESS_PARAMETERS structure placed named ProcessParameters in PEB.

## Additional resources
* https://blog.xpnsec.com/how-to-argue-like-cobalt-strike/
* https://www.bordergate.co.uk/argument-spoofing/

## Code snippets
* arg-spoofing.c
