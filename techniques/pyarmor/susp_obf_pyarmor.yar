rule SUSP_OBF_PyArmor_Jan24
{
	meta:
		description = "Detects PyArmor python code obfuscation. PyArmor is used by various threat actors like BatLoader"
		author = "Jonathan Peters"
		date = "2024-01-16"
		reference = "https://www.trendmicro.com/en_us/research/23/h/batloader-campaigns-use-pyarmor-pro-for-evasion.html"
		hash = "2727a418f31e8c0841f8c3e79455067798a1c11c2b83b5c74d2de4fb3476b654"
		score = 65
	strings:
		$ = "__pyarmor__" ascii
		$ = "pyarmor_runtime" ascii
    $ = "pyarmor(__" ascii
		$ = { 50 79 61 72 6D 6F 72 20 [5] 20 28 70 72 6F 29 }
		$ = { 5F 5F 61 72 6D 6F 72 5F ( 65 78 69 74 | 77 72 61 70 | 65 6E 74 65 72 ) 5F 5F }
	condition:
		2 of them
}
