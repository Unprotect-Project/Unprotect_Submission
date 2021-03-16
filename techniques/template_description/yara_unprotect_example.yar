rule UNPROTECT_disable_process
{
    meta:
	      author = "Thomas Roccia | @fr0gger_"
	      description = "Disable blacklisted processes"

    strings:
        $api1 = "CreateToolhelp32Snapshot" nocase
        $api2 = "Process32First" nocase
        $api3 = "Process32Next" nocase

        $p1 = "taskkill.exe" nocase
        $p2 = "tskill.exe" nocase

    condition:
        uint32(uint32(0x3C)) == 0x4550 and 3 of ($api*) or any of ($p*) 
}
