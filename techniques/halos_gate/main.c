// The structure below was collected from the paper about Hell's Gate, 
// created by am0nsec and RtlMateusz
BOOL GetVxTableEntry(
	_In_ PVOID pModuleBase,
	_In_ PIMAGE_EXPORT_DIRECTORY pImageExportDirectory,
	_In_ PVX_TABLE_ENTRY pVxTableEntry
);


// Code collected from Alice Climent-Pommeret's post
// Below we can see the loop, checking non-non-Hooked APIs (500 previous
// APIs and 500 subsequent APIs) in the neighborhood of the target API.
int UP -32;
int DOWN 32;

if (*((PBYTE)ptr_API_Addr) == 0xe9) {
	for (WORD idx = 1; idx <= 500; idx++) {
		if (*((PBYTE)ptr_API_Addr + idx * DOWN) == 0x4c
			&& *((PBYTE)ptr_API_Addr + 1 + idx * DOWN) == 0x8b
			&& *((PBYTE)ptr_API_Addr + 2 + idx * DOWN) == 0xd1
			&& *((PBYTE)ptr_API_Addr + 3 + idx * DOWN) == 0xb8
			&& *((PBYTE)ptr_API_Addr + 6 + idx * DOWN) == 0x00
			&& *((PBYTE)ptr_API_Addr + 7 + idx * DOWN) == 0x00) {
			BYTE high = *((PBYTE)ptr_API_Addr + 5 + idx * DOWN);
			BYTE low = *((PBYTE)ptr_API_Addr + 4 + idx * DOWN);
			pVxTableEntry->wSystemCall = (high << 8) | low - idx;
			return TRUE;
		}
		if (*((PBYTE)ptr_API_Addr + idx * UP) == 0x4c
			&& *((PBYTE)ptr_API_Addr + 1 + idx * UP) == 0x8b
			&& *((PBYTE)ptr_API_Addr + 2 + idx * UP) == 0xd1
			&& *((PBYTE)ptr_API_Addr + 3 + idx * UP) == 0xb8
			&& *((PBYTE)ptr_API_Addr + 6 + idx * UP) == 0x00
			&& *((PBYTE)ptr_API_Addr + 7 + idx * UP) == 0x00) {
			BYTE high = *((PBYTE)ptr_API_Addr + 5 + idx * UP);
			BYTE low = *((PBYTE)ptr_API_Addr + 4 + idx * UP);
			pVxTableEntry->wSystemCall = (high << 8) | low + idx;
			return TRUE;
		}
}