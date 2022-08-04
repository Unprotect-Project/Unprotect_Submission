# Hijack Dynamic Address Resolution

## Authorship Information
* Name: Alex Schwarz
* Website: 
* Twitter:
* Linkedin: https://www.linkedin.com/in/alex-schwarz-94248269/
  
## Technique Information
* Technique Title: Hijack Dynamic Address Resolution
* Technique Category: Process Manipulation
* Technique Description: For a running process we can change the results of calls to GetProcAddress for the exported functions of a module along with modifying the export's offsets and name at runtime. For example, we can change the offset of kernel32.dll's function "VirtualAlloc" to the offset of some other function such that when VirtualAlloc is called (after getting its address from GetProcAddress), our second routine will be called instead. To achieve this we use the WINAPI 'MapAndLoad' from ImageHlp.h, then use ImageDirectoryEntryToData to get our list of exports. Then we use ImageRvaToVa WINAPI to retrieve each export's function name offset; if desired the export name can be written over, resulting in calls to GetProcAddress with that export name to fail or be directed to some other routine. 
* 
## Code Snippets
* modifyExports.cpp
