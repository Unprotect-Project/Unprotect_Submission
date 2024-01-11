rule golang_base64_enc {
	meta:
		author = "RussianPanda"
		decription = "Detects Base64 Encoding and Decoding patterns in Golang binaries"
        	reference = "https://unprotect.it/technique/base64/"
		date = "1/10/2024"
		hash = "509a359b4d0cd993497671b91255c3775628b078cde31a32158c1bc3b2ce461c"
	strings:
	        $s1 = {62 61 73 65 36 34 2e 53 74 64 45 6e 63 6f 64 69 6e 67 2e 45 6e 63 6f 64 65 54 6f 53 74 72 69 6e 67 28 [0-15] 29}
	        $s2 = {62 61 73 65 36 34 2e 53 74 64 45 6e 63 6f 64 69 6e 67 2e 44 65 63 6f 64 65 53 74 72 69 6e 67 28 [0-15] 29}
	        $s3 = {69 66 20 65 72 72 20 21 3D 20 6E 69 6C 20 7B}
		$s4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
 	condition:
		all of ($s*) 
        	and uint16(0) == 0x5A4D
}


rule base64_enc {
	meta:
		author = "RussianPanda"
		decription = "Detects Base64 Encoding"
        	reference = "https://unprotect.it/technique/base64/"
		date = "1/10/2024"
		hash = "09506d1af5d8e6570b2b7d05143f444f5685d2a9f3304780ef376edf7b2d79e6"
	strings:
		$s2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
        	$s3 = {83 E? 3F}
 	condition:
		all of ($s*) 
        	and uint16(0) == 0x5A4D
		
}
