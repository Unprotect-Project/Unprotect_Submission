# Change Number of Sections at Runtime, Pointer-To Sections

## Authorship Information
* Name: Alex Schwarz
* Website: https://github.com/AlSch092
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Change Pointer-To Sections and Number of Sections at Runtime
* Technique Category: Process Manipulation
* Technique Description: During runtime we can edit a processes PEB to change the number of code sections, making it more difficult to iterate over the sections for other processes. Typically the macro IMAGE_FIRST_SECTION() is used to fetch a pointer to the program's section information which can then be iterated over to get all the sections, and by changing the _IMAGE_FILE_HEADER structure's NumberOfSections variable to 0, we can trick unsuspecting programs to not query any section information from ours. We can also set the NumberOfSections variable to something much higher such as 65535, which might cause memory corruptions/buffer overruns in other programs when they try to query too many sections. Additionally, we can change the SizeOfOptionalHeader variable of the IMAGE_FILE_HEADER structure in the PEB to break the functionality of the IMAGE_FIRST_SECTION macro, such that results from the macro no longer point to correct section info. Please note that this technique may not stop disassembly tools from showing the proper code sections in their GUIs.

## Code Snippets
* IterateSectionsEvasion.cpp
