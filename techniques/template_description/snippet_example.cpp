#include <iostream>
#include <string>
#include <tchar.h>
#include <process.h>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

BOOL GetProcessList();
BOOL TerminateMyProcess(DWORD dwProcessId, UINT uExitCode);

int main( void )
{
  GetProcessList( );
  return 0;
}

BOOL GetProcessList( )
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

  //Blacklisted processes
  LPSTR ProcessName[] = { "ida.Exe",
                          "ProcMon.exe",
                          "Olldbg.exe",
                          "Wireshark.exe",
                          "iexplore.exe"
                            };

  // Take a snapshot of processes
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE )
  {
    return( FALSE );
  }

  pe32.dwSize = sizeof( PROCESSENTRY32 );

  if( !Process32First( hProcessSnap, &pe32 ) )
  {
    CloseHandle( hProcessSnap );
    return( FALSE );
  }

  do
  {
    string str(pe32.szExeFile);

    for (int i = 0; i < (sizeof(ProcessName) / sizeof(LPSTR)); i++)
    {
         if(str == ProcessName[i])
         {
             cout << "[*] processus exists: " << (ProcessName[i]) << endl;
             TerminateBlacklistedProcess(pe32.th32ProcessID, 1);
         }
    }
  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return( TRUE );
}

// Terminate the blacklisted processes
BOOL TerminateBlacklistedProcess(DWORD dwProcessId, UINT uExitCode)
{
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL  bInheritHandle  = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
    if (hProcess == NULL)
        return FALSE;

    BOOL result = TerminateProcess(hProcess, uExitCode);

    CloseHandle(hProcess);

    return result;
}
