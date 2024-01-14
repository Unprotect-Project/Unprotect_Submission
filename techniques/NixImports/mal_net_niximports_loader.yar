rule MAL_NET_NixImports_Loader_Jan24 {
	meta:
		description = "Detects open-source NixImports .NET malware loader. A stealthy loader using dynamic import resolving to evade static detection"
		author = "Jonathan Peters"
		date = "2024-01-12"
		reference = "https://github.com/dr4k0nia/NixImports/tree/master"
		hash = "dd3f22871879b0bc4990c96d1de957848c7ed0714635bb036c73d8a989fb0b39"
		score = 80
	strings:
		$op1 = { 1F 0A 64 06 1F 11 62 60 } // Hash algorithm
		$op2 = { 03 20 4D 5A 90 00 94 4B 2A } // Magic
		$op3 = { 20 DE 7A 1F F3 20 F7 1B 18 BC } // Hardcoded function hashes
		$op4 = { 20 CE 1F BE 70 20 DF 1F 3E F8 14 } // Hardcoded function hashes

		$sa1 = "OffsetToStringData" ascii
		$sa2 = "GetRuntimeMethods" ascii
		$sa3 = "netstandard" ascii
	condition:
		uint16(0) == 0x5a4d and
		all of ($sa*) and
		2 of ($op*)
}
