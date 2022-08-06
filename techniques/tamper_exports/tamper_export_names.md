# Tamper Dll Export Names & GetProcAddress Spoofing

## Authorship Information
* Name: Alex Schwarz
* Website: 
* Twitter:
* Linkedin: https://www.linkedin.com/in/alex-schwarz-94248269/
  
## Technique Information
* Technique Title: Tamper Dll Export Names & GetProcAddress Spoofing
* Technique Category: Process Manipulation
* Technique Description: For a running process we can change the results of calls to GetProcAddress for exported functions of a module along with modifying the export's name at runtime. For example, we can change the name of kernel32.dll's function "VirtualAlloc" to the name of some other function such that when VirtualAlloc is called (after getting its address from GetProcAddress), our second routine will be called instead. To achieve this we use the WINAPI 'MapAndLoad' from ImageHlp.h, then use the ImageDirectoryEntryToData WINAPI to get our list of exports. Then we use ImageRvaToVa WINAPI to retrieve each export's function name offset and the export name can be written over, resulting in calls to GetProcAddress with that name to fail (if no longer found) or be directed to some other routine. 

## Code Snippets
* modifyExports.cpp
