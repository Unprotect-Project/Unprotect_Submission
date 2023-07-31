# Anti-DLL injection through export name tampering

## Authorship Information
* Name: Alex Schwarz
* Website: https://github.com/AlSch092/
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Anti-DLL injection through export name tampering
* Technique Category: Process Manipulation
* Technique Description: We can stop certain methods of DLL injection by modifying the exported function names for the "LoadLibrary" set of routines. We can enumerate the entires in the image's export directory to find the addresses of the LoadLibrary routines name, and then write an empty string over it. This makes calls to GetProcAddress return NULL when a process attempts to query the address of any LoadLibrary routine. Many DLL injectors will write the DLL name into the target process and then create a remote thread calling LoadLibraryA/W/Ex, and because the address of LoadLibrary is required for this type of DLL injection, this step in the process will fail and DLL injection will be unsuccessful.

## Code Snippets
* antiDLL.cpp
