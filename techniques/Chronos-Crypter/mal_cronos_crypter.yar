import "pe"
import "dotnet"

rule MAL_Cronos_Crypter_Strings {
    meta:
        description = "Detects Cronos Crypter based on strings found in file."
        author = "Tony Lambert"
        reference = "0eb4874937a6a37665e74fcd90413b0d4161659a0226b1ebf667b954b41b1012"
        date = "2024-03-17"
    strings:
        $s1 = "Cronos-Crypter" ascii wide
        $s2 = "Rfc2898DeriveBytes" ascii wide
        $s3 = "RijndaelManaged" ascii wide
    condition:
        pe.is_pe and all of them
}

rule MAL_Cronos_Crypter_Salt {
    meta:
        description = "Detects Cronos Crypter based encryption salt value and string that should be seen in memory."
        author = "Tony Lambert"
        reference = "0eb4874937a6a37665e74fcd90413b0d4161659a0226b1ebf667b954b41b1012"
        date = "2024-03-17"
    strings:
        $s1 = "Cronos-Crypter" ascii wide
        $salt = {1A 14 CA EA 88 7B 45 2F}
    condition:
        all of them
}

rule MAL_Cronos_Crypter_Assembly_Name {
    meta:
        description = "Detects Cronos Crypter based on .NET assembly name."
        author = "Tony Lambert"
        reference = "0eb4874937a6a37665e74fcd90413b0d4161659a0226b1ebf667b954b41b1012"
        date = "2024-03-17"
    condition:
        dotnet.assembly.name startswith "Cronos-Crypter"
}