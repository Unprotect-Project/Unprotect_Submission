//Unprotect.it submission: Evasion Technique
//By AlSch092 @Github 
//April 1 2023

#include <windows.h>
#include <winnt.h>
#include <winternl.h>

#include <stdio.h>

void BreakSectionIteration()
{
	HINSTANCE hInst = GetModuleHandleW(NULL); //Get address of image base 

	PIMAGE_DOS_HEADER pDoH = (PIMAGE_DOS_HEADER)(hInst);
	PIMAGE_NT_HEADERS64 pNtH = (PIMAGE_NT_HEADERS64)((PIMAGE_NT_HEADERS64)((PBYTE)hInst + (DWORD)pDoH->e_lfanew));
	PIMAGE_FILE_HEADER pFh = &pNtH->FileHeader; //Get address to image file header

	DWORD dwOldProt = 0;
	VirtualProtect((LPVOID)pDoH, sizeof(PEB), PAGE_EXECUTE_READWRITE, &dwOldProt); //make sure we can write over some file header variables

	pFh->NumberOfSections = 0;      //setting the NumberOfSections to 0 can stop iteration when someone uses the IMAGE_FIRST_SECTION macro, and...

	//pFh->NumberOfSections = 65535;	   //we can also set it to some large number to try and get programs to read 'too many sections' from memory
	//...programs which query the section's name have a high chance of throwing exceptions or crashing because we are querying memory which is not actually section information, but other parts of our program at further offsets. 

	((pNtH))->FileHeader.SizeOfOptionalHeader = -1; //Changing the SizeOfOptionalHeader variable breaks the IMAGE_FIRST_SECTION macro, and when querying sections this macro will no longer provide us with the correct results.

	PIMAGE_SECTION_HEADER sectionHeader = IMAGE_FIRST_SECTION(pNtH); //we now iterate over our sections as normal to show the effect:

	int nSections = pNtH->FileHeader.NumberOfSections;

	for (int i = 0; i < nSections; i++) //changing the SizeOfOptionalHeader and NumberOfSections variables above will change the results of the following loop
	{
		__try
		{
			printf("Section Name: %s\n", sectionHeader[i].Name);
			printf("VA: %x\n", sectionHeader[i].VirtualAddress);
			printf("Misc: %x\n", sectionHeader[i].Misc);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			printf("FAILED TO PARSE SECTION NAME!\n");
			continue;
		}
	}
}

int main()
{
	BreakSectionIteration();
	return 0;
}