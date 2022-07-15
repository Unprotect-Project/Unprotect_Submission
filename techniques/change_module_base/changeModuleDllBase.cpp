#include <Windows.h>
#include <Winternl.h>
#include <stdint.h>

bool ChangeModuleDllBase(const wchar_t* szModule, uint64_t newAddress)
{
	PPEB PEB = (PPEB)__readgsqword(0x60);
	_LIST_ENTRY* f = PEB->Ldr->InMemoryOrderModuleList.Flink;
	bool Found = FALSE;
	int count = 0;

	while (!Found && count < 256)
	{
		PLDR_DATA_TABLE_ENTRY dataEntry = CONTAINING_RECORD(f, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (wcsstr(dataEntry->FullDllName.Buffer, szModule))
		{
			dataEntry->DllBase = (PVOID)newAddress;
			Found = TRUE;
			return true;
		}

		f = dataEntry->InMemoryOrderLinks.Flink;
		count++;
	}

	return false;
}

int main()
{
    ChangeModuleDllBase(L"YourProgram.exe", 0x123456789);
    return 0;
}
