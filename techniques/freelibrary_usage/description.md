# *freelibrary_usage*

## Authorship information
* Name or nickname (required): *github.com/west-wind*
  
## Technique Information
* Technique title (required): Using FreeLibrary to remove AV/EDR hooks
* Technique category (required): Antivirus Evasion
* Technique description (required): Malware authors are known to check for AV/EDR dll's that are loaded in its address space and will try to unload the DLL by first using the GetModuleHandleA to get a handle (if its loaded), and then use FreeLibrary to free/unload the library before actually executing its malicious code. 

## Additional resources
* http://malwarejake.blogspot.com/2013/07/interesting-malware-defense.html 

## Code snippets
* Please add your code in separate files.

## Detection rules
* Please add your rules in separate files.
