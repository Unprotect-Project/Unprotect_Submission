#include <stdio.h>
#include <windows.h>

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;


typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    LIST_ENTRY HashLinks;
    ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN SpareBool;
    HANDLE Mutant;
    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
} PEB, * PPEB;


struct NtDLL_Parse {
    DWORD* NtDLL_AddressOfFunctions;
    DWORD* NtDLL_AddressOfNames;
    WORD* NtDLL_AddressOfNamesOrdinals;
    DWORD NtDLL_NumberOfNames;
    HMODULE NtDLL_Handler;
};

void ParsePE(struct NtDLL_Parse* ntdll_parse, HMODULE hModule) {
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((BYTE*)hModule + dosHeader->e_lfanew);
    PIMAGE_EXPORT_DIRECTORY exportDirectory = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)hModule + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    ntdll_parse->NtDLL_Handler = hModule;
    ntdll_parse->NtDLL_AddressOfFunctions = (DWORD*)((BYTE*)hModule + exportDirectory->AddressOfFunctions);
    ntdll_parse->NtDLL_AddressOfNames = (DWORD*)((BYTE*)hModule + exportDirectory->AddressOfNames);
    ntdll_parse->NtDLL_AddressOfNamesOrdinals = (WORD*)((BYTE*)hModule + exportDirectory->AddressOfNameOrdinals);
    ntdll_parse->NtDLL_NumberOfNames = exportDirectory->NumberOfNames;
}

void FindNtCreateSection(struct NtDLL_Parse* ntdll_parse) {
    printf("[*] Searching for NtCreateSection...\n");

    for (DWORD i = 0; i < ntdll_parse->NtDLL_NumberOfNames; i++) {
        char* functionName = (char*)((BYTE*)ntdll_parse->NtDLL_Handler + ntdll_parse->NtDLL_AddressOfNames[i]);

        if (strcmp(functionName, "NtCreateSection") == 0) {
            DWORD rva = ntdll_parse->NtDLL_AddressOfFunctions[ntdll_parse->NtDLL_AddressOfNamesOrdinals[i]];
            DWORD offset = (DWORD)((BYTE*)ntdll_parse->NtDLL_Handler + rva);
            printf("[+] NtCreateSection Offset: 0x%X\n", offset);
            return;
        }
    }

    printf("[-] NtCreateSection not found!\n");
}

int main() {
    PPEB peb = (PPEB)__readgsqword(0x60); // or 0x30 for x86
    PLIST_ENTRY moduleList = &peb->Ldr->InMemoryOrderModuleList;
    PLDR_DATA_TABLE_ENTRY ntdllEntry = CONTAINING_RECORD(moduleList->Flink->Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
    HMODULE hNtdll = (HMODULE)ntdllEntry->DllBase;

    if (!hNtdll) {
        printf("[-] Failed to get ntdll.dll handle!\n");
        return -1;
    }

    struct NtDLL_Parse ntdll_parse;
    ParsePE(&ntdll_parse, hNtdll);

    printf("[+] Loaded Module: ntdll.dll\n");
    printf("[*] NtDLL_AddressOfFunctions: %p\n", ntdll_parse.NtDLL_AddressOfFunctions);
    printf("[*] NtDLL_AddressOfNames: %p\n", ntdll_parse.NtDLL_AddressOfNames);
    printf("[*] NtDLL_AddressOfNamesOrdinals: %p\n", ntdll_parse.NtDLL_AddressOfNamesOrdinals);
    printf("[*] NtDLL_NumberOfNames: %d\n", ntdll_parse.NtDLL_NumberOfNames);
    printf("[*] NtDLL_Handler: %p\n", ntdll_parse.NtDLL_Handler);

    FindNtCreateSection(&ntdll_parse);
    return 0;
}