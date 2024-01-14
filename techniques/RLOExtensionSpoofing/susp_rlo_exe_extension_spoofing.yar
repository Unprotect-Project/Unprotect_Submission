rule SUSP_RLO_Exe_Extension_Spoofing_Jan24 {
	meta:
		description = "Detects Right-To-Left (RLO) Unicode (U+202E) extension spoofing for .exe files"
		author = "Jonathan Peters"
		date = "2024-01-14"
		reference = "https://unprotect.it/technique/right-to-left-override-rlo-extension-spoofing/"
		hash = "cae0ab10f7c1afd7941aff767a9b59901270e3de4d44167e932dae0991515487"
		score = 70
	strings:
		$ = { E2 80 AE 76 63 73 2E 65 78 65 } // csv
		$ = { E2 80 AE 66 64 70 2E 65 78 65 } // pdf
		$ = { E2 80 AE 78 73 6C 78 2E 65 78 65 } // xlsx
		$ = { E2 80 AE 78 63 6F 64 2E 65 78 65 } // docx
		$ = { E2 80 AE 70 69 7A 2E 65 78 65 } // zip
		$ = { E2 80 AE 67 6E 70 2E 65 78 65 } // png
		$ = { E2 80 AE 67 65 70 6A 2E 65 78 65 } // jpeg
		$ = { E2 80 AE 67 70 6A 2E 65 78 65 } // jpg
	condition:
		1 of them
}
