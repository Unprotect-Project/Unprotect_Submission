#include <windows.h>

/*  Function that repeatedly calls many Windows API functions in a loop
    Designed to stress the Windows API by making a large number 
    of system calls in rapid succession.
    
    Code authorship information :
        Name or nickname (required): 0xRo
        Twitter: https://x.com/0x_ror
        Website: https://blog.rodolpheg.xyz/
        Linkedin: https://www.linkedin.com/in/ghiorodolphe/
*/

void APIHammering() {
    for(int i = 0; i < 10000; i++) {
        GetSystemTime(NULL);
        GetTickCount();
        GetCurrentProcessId(); 
        GetCurrentThreadId();
        GetLastError();
        GetCurrentDirectory(MAX_PATH, NULL);
        GetSystemDirectory(NULL, MAX_PATH);
        GetWindowsDirectory(NULL, MAX_PATH);
        GetComputerName(NULL, NULL);
        GetUserName(NULL, NULL);
        GetEnvironmentVariable("PATH", NULL, 0);
        GetSystemMetrics(SM_CXSCREEN);
        GetSystemMetrics(SM_CYSCREEN);
        GetDiskFreeSpace(NULL, NULL, NULL, NULL, NULL);
        GetVersionEx(NULL);
        GetSystemInfo(NULL);
        GetLocalTime(NULL);
        GetTimeZoneInformation(NULL);
        GetCommandLine();
        GetCurrentProcess();
        GetModuleHandle(NULL);
        GetModuleFileName(NULL, NULL, MAX_PATH);
        GetLogicalDrives();
        GetDriveType(NULL);
        GetVolumeInformation(NULL, NULL, 0, NULL, NULL, NULL, NULL, 0);
        GetSystemPowerStatus(NULL);
        GetSystemTimeAdjustment(NULL, NULL, NULL);
        GetSystemWindowsDirectory(NULL, 0);
        GetSystemWow64Directory(NULL, 0);
        GetTempPath(MAX_PATH, NULL);
        GetThreadPriority(GetCurrentThread());
        GetThreadTimes(GetCurrentThread(), NULL, NULL, NULL, NULL);
        GetUserDefaultLCID();
        GetUserDefaultLangID();
        GetVersion();
        GetSystemDefaultLCID();
        GetStartupInfo(NULL);
        GetProcessTimes(GetCurrentProcess(), NULL, NULL, NULL, NULL);
        GetProcessVersion(0);
        GetProcessWorkingSetSize(GetCurrentProcess(), NULL, NULL);
        GetPriorityClass(GetCurrentProcess());
        GetProcessHandleCount(GetCurrentProcess(), NULL);
        GetProcessId(GetCurrentProcess());
        GetProcessIdOfThread(GetCurrentThread());
        GetProcessIoCounters(GetCurrentProcess(), NULL);
        GetLogicalProcessorInformation(NULL, NULL);
    }
}

int main() {
    printf("Starting Windows API hammering...\n");
    APIHammering();
    printf("Hammering completed.\n");
    return 0;
}
