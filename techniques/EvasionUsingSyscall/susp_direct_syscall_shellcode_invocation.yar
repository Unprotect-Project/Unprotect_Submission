rule SUSP_Direct_Syscall_Shellcode_Invocation_Jan24 {
	meta:
		description = "Detects direct syscall evasion technqiue using NtProtectVirtualMemory to invoke shellcode"
		author = "Jonathan Peters"
		date = "2024-01-14"
		reference = "https://unprotect.it/technique/evasion-using-direct-syscalls/"
		hash = "f7cd214e7460c539d6f8d02b6650098e3983862ff658b76ea02c33f5a45fc836"
		score = 65
	strings:
		$ = { B8 40 00 00 00 67 4C 8D 08 49 89 CA 48 C7 C0 50 00 00 00 0F 05 [4-8] 4C 8D 3D 02 00 00 00 FF E0 }
	condition:
		all of them and
		filesize < 2MB
}
