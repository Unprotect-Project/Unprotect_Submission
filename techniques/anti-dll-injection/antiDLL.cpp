/*
antiDLL.cpp
AlSch092 @ github
Example of disabling typical DLL injection via LoadLibrary using export name tampering
*/

#include <iostream>
#include <Windows.h>
#include <ImageHlp.h>
#include <string>
#pragma comment(lib, "ImageHlp")

using namespace std;

bool ModifyDLLExportName(string dllName, string functionName, string newName)
{
	DWORD* dNameRVAs(0); //array: addresses of export names
	_IMAGE_EXPORT_DIRECTORY* ImageExportDirectory;
	unsigned long cDirSize;
	_LOADED_IMAGE LoadedImage;
	string sName;

	if (MapAndLoad(dllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
	{
		ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)ImageDirectoryEntryToData(LoadedImage.MappedAddress, false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);

		if (ImageExportDirectory != NULL)
		{
			//load list of function names from DLL, the third parameter is an RVA to the data we want
			dNameRVAs = (DWORD*)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ImageExportDirectory->AddressOfNames, NULL);

			for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
			{
				sName = (char*)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, dNameRVAs[i], NULL);

				if (strcmp(functionName.c_str(), sName.c_str()) == 0)
				{
					UINT64 funcName_Address = (UINT64)GetModuleHandleA(dllName.c_str()) + dNameRVAs[i]; //get VA From RVA + imagebase

					DWORD oldProt = 0;

					if (!VirtualProtect((LPVOID)funcName_Address, 1024, PAGE_EXECUTE_READWRITE, &oldProt))
					{
						printf("VirtualProtect failed: %d\n", GetLastError());
						return false;
					}
					else
					{
						strcpy_s((char*)funcName_Address, 100, newName.c_str()); //if you write a string longer than the current name you need to shuffle the entire export name array to fit it.
						printf("Copied over export function name..\n");
					}
				}
			}
		}
		else
		{
			printf("[ERROR] ImageExportDirectory was NULL!\n");
			UnMapAndLoad(&LoadedImage);
			return false;
		}
	}
	else
	{
		printf("MapAndLoad failed: %d\n", GetLastError());
		return false;
	}

	UnMapAndLoad(&LoadedImage);

	return true;
}

int main(void)
{
	
	ModifyDLLExportName("KERNELBASE.DLL", "LoadLibraryA", ""); //stops any DLL injection which relies on calling LoadLibrary in a remote process
	ModifyDLLExportName("KERNELBASE.DLL", "LoadLibraryW", ""); //many injectors will write the DLL name into the target process then createRemoteThread which calls LoadLibrary
	ModifyDLLExportName("KERNELBASE.DLL", "LoadLibraryExA", "");
	ModifyDLLExportName("KERNELBASE.DLL", "LoadLibraryExW", "");

	//calling exported functions will implicitly load the .DLL required at runtime if not done already; any exported functions you call after modifying exports might throw an error box stating it can't find the address
	//this can be solved by loading the library/address before calling ModifyDLLExportName
	system("pause");  //for example, this will pop up an error box about missing LoadLibrary, but if you add this same call to the first line of main(), the error box won't happen!
  return 0;
}
