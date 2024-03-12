// $ x86_64-w64-mingw32-gcc -o main.exe main.c

#include <windows.h>
#include <stdio.h>

int main()
{
    printf("[*] Running...\n");
    HANDLE currentProcess;

    // If we pass a bogus device string into this API call, the return value should always be zero to indicate failure.
    // The hypothesis here is that if this API call ever succeeds, it is in some kind of emulation environment that will allow a bogus device string.
    // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-buildcommdcbandtimeoutsa

    // device string from the POC: "jhl46745fghb"
    // properly formatted device string: "COM1:9600,n,8,1"
    if (BuildCommDCBAndTimeouts("jhl46745fghb", NULL, NULL))
    {
        printf("[*] Nope.\n");
        currentProcess = GetCurrentProcess();
        TerminateProcess(currentProcess, 0);
    }

    printf("[+] Boom!\n");

    return 0;
}
