#pragma comment(linker,"/export:FuncA=DLLExport.FunctionA,@1") 

#include <iostream>
#include <Windows.h>
#include <ImageHlp.h>
#pragma comment(lib, "ImageHlp")

using namespace std;

bool ModifyDLLExportName(string dllName, string functionName, string newName)
{
	DWORD* dNameRVAs(0);
	_IMAGE_EXPORT_DIRECTORY* ImageExportDirectory;
	unsigned long cDirSize;
	_LOADED_IMAGE LoadedImage;
	string sName;

	if (MapAndLoad(dllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
	{
		ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)ImageDirectoryEntryToData(LoadedImage.MappedAddress, false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);

		if (ImageExportDirectory != NULL)
		{

			dNameRVAs = (DWORD*)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ImageExportDirectory->AddressOfNames, NULL);

			for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
			{
				sName = (char*)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, dNameRVAs[i], NULL);

				if (strcmp(functionName.c_str(), sName.c_str()) == 0)
				{
					UINT64 funcName_Address = (UINT64)GetModuleHandleA(dllName.c_str()) + dNameRVAs[i];

					DWORD oldProt = 0;

					if (!VirtualProtect((LPVOID)funcName_Address, 1024, PAGE_EXECUTE_READWRITE, &oldProt))
					{
						printf("VirtualProtect failed: %d\n", GetLastError());
						return false;
					}
					else
					{
						strcpy_s((char*)funcName_Address, 100, newName.c_str());
						printf("Copied over export function name..\n");
					}
				}
			}
		}
		UnMapAndLoad(&LoadedImage);
	}

	return true;
}


int main(void)
{
	//user-provided DLL Tests
	LoadLibraryA("DllExport.dll");

	DWORD addr_exe = (DWORD)GetProcAddress(GetModuleHandleA("ModifyExports.exe"), "FuncA"); //using linker statement at top
	printf("Addr: %x\n", addr_exe);

	DWORD addr_dll = (DWORD)GetProcAddress(GetModuleHandleA("DllExport.dll"), "FunctionA"); //returns same value as above line (address of DllExport.FunctionA)
	printf("Addr: %x\n", addr_dll);

	ModifyDLLExportName("DllExport.dll", "FunctionA", "FunctionB");
	DWORD addr_dll_B = (DWORD)GetProcAddress(GetModuleHandleA("DllExport.dll"), "FunctionB"); //returns same value as above, thus looking up FunctionB gives us FunctionA.
	printf("Addr: %x\n", addr_dll_B);

	//WINAPI Tests

	DWORD addr = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "VirtualAlloc"); //this will return 0, as the above line changed the export's name.
	printf("Addr: %x\n", addr);
	ModifyDLLExportName("kernel32.dll", "VirtualAlloc", "VirtualQuery");
	addr = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "VirtualAlloc"); //returns 0
	printf("Addr: %x\n", addr);
	addr = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "VirtualQuery"); //now returns the address of VirtualAlloc, not VirtualQuery!
	printf("Addr: %x\n", addr);
	system("pause");
	return 0;
}
