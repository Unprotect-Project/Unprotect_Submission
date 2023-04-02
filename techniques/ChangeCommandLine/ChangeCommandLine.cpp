#include <windows.h>
#include <stdio.h>

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _PEB_LDR_DATA {
	BYTE Reserved1[8];
	PVOID Reserved2[3];
	LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY {
	PVOID Reserved1[2];
	LIST_ENTRY InMemoryOrderLinks;
	PVOID Reserved2[2];
	PVOID DllBase;
	PVOID Reserved3[2];
	UNICODE_STRING FullDllName;
	BYTE Reserved4[8];
	PVOID Reserved5[3];
	union {
		ULONG CheckSum;
		PVOID Reserved6;
	} DUMMYUNIONNAME;
	ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	BYTE Reserved1[16];
	PVOID Reserved2[10];
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef
VOID
(NTAPI *PPS_POST_PROCESS_INIT_ROUTINE) (
VOID
);

typedef struct _PEB {
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	PPEB_LDR_DATA Ldr;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID Reserved4[3];
	PVOID AtlThunkSListPtr;
	PVOID Reserved5;
	ULONG Reserved6;
	PVOID Reserved7;
	ULONG Reserved8;
	ULONG AtlThunkSListPtr32;
	PVOID Reserved9[45];
	BYTE Reserved10[96];
	PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
	BYTE Reserved11[128];
	PVOID Reserved12[1];
	ULONG SessionId;
} PEB, *PPEB;

void ChangeCommandLine(wchar_t* newCommandLine)
{
	PPEB PEB = (PPEB)__readgsqword(0x60); //make sure you're compiling in x64, if not you need to change this to fetch the PEB properly

	wprintf(L"Command line: %s (strlength %d)\n", PEB->ProcessParameters->CommandLine.Buffer, PEB->ProcessParameters->CommandLine.Length);

	wcscpy_s(PEB->ProcessParameters->CommandLine.Buffer, wcslen(newCommandLine) + 1, newCommandLine);
	PEB->ProcessParameters->CommandLine.Length = wcslen(newCommandLine) * 2;

	wprintf(L"New command line: %s (strlength %d)\n", PEB->ProcessParameters->CommandLine.Buffer, PEB->ProcessParameters->CommandLine.Length);
}

int main(int argc, char** argv)
{
	ChangeCommandLine(L"\"C:\\Our\\New\\Path\\NewProgramName.exe\" p1 p2 p3"); //we can change the command line however we'd like, including removing the application name from the path.
	return 0;
}
