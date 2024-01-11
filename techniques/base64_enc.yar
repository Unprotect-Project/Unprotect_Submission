rule susp_b64_enc {
	meta:
		author = "RussianPanda"
		decription = "Detects Base64 Encoding"
        reference = "https://unprotect.it/technique/base64/"
		date = "1/10/2024"

	strings:

		$s2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
        $s3 = {83 E? 3F}
     
 	condition:
		all of ($s*) 
        and uint16(0) == 0x5A4D
		
}