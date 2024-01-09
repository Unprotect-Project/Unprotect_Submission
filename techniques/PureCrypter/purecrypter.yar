import "dotnet"

rule PureCrypter 
{
    meta:
        author = "RussianPanda"
        date = "2024-01-09"
        reference = "https://www.zscaler.com/blogs/security-research/technical-analysis-purecrypter"
        description = "Detects PureCrypter"
        hash = "566d8749e166436792dfcbb5e5514f18c9afc0e1314833ac2e3d86f37ff2030f"
    strings:
        $s1 = {28 ?? 00 00 ?? 28 02 00 00 2B 28 ?? 00 00 (0A|06)}
        $s2 = {73 ?? 00 00 0A}
        $s3 = {73 ?? 00 00 06 6F ?? 00 00 06}
        $s4 = {52 65 73 6F 75 72 63 65 4D 61 6E 61 67 65 72}
        $s5 = {28 ?? 00 00 ?? 6F ?? 00 00 0A 28 03 00 00 2B ?? 6F ?? 00 00 0A 28 ?? 00 00 2B} 
        
    condition:
        filesize < 6MB and
        4 of ($s*) and for any i in (0..dotnet.number_of_streams - 1):  (dotnet.streams[i].name == "#~") and dotnet.number_of_resources > 0 and dotnet.number_of_resources < 2 and dotnet.resources[0].length > 300KB 
    
}


import "dotnet"

rule PureCrypter_Core
{
    meta:
        author = "RussianPanda"
        date = "2024-01-09"
        reference = "https://www.zscaler.com/blogs/security-research/technical-analysis-purecrypter"
        description = "Detects PureCrypter Core payload"
        hash = "e4faa7d7a098414449abffb210fd874798207ee9d27643c8088676ff429b56b7"
    strings:
        $s1 = {47 5A 69 70 53 74 72 65 61 6D}
        $s2 = {41 73 73 65 6D 62 6C 79 4C 6F 61 64 65 72 00 43 6F 73 74 75 72 61}
        $s3 = {44 65 66 6C 61 74 65 53 74 72 65 61 6D}
        $cnct = {72 ?? ?? 00 70 28 FB 00 00 0A 72 ?? ?? 00 70 28 ?? 00 00 0A}
        $nr1 = {7B 00 31 00 31 00 31 00 31 00 31 00 2D 00 32 00 32 00 32 00 32 00 32 00 2D 00 34 00 30 00 30 00 30 00 31 00 2D 00 30 00 30 00 30 00 30 00 31 00 7D}
        $nr2 = {7B 00 31 00 31 00 31 00 31 00 31 00 2D 00 32 00 32 00 32 00 32 00 32 00 2D 00 34 00 30 00 30 00 30 00 31 00 2D 00 30 00 30 00 30 00 30 00 32 00 7D}
        $nr3 = {7B 00 31 00 31 00 31 00 31 00 31 00 2D 00 32 00 32 00 32 00 32 00 32 00 2D 00 32 00 30 00 30 00 30 00 31 00 2D 00 30 00 30 00 30 00 30 00 32 00 7D}
        $nr4 = {7B 00 31 00 31 00 31 00 31 00 31 00 2D 00 32 00 32 00 32 00 32 00 32 00 2D 00 32 00 30 00 30 00 30 00 31 00 2D 00 30 00 30 00 30 00 30 00 31 00 7D}
        
    condition: 
        filesize < 5MB and
        all of ($s*) and
        for any i in (0..dotnet.number_of_streams - 1): (dotnet.streams[i].name == "#~")
        and dotnet.number_of_resources > 4 and dotnet.number_of_resources < 6
        and 2 of ($nr*) and dotnet.assembly_refs[1].name contains "protobuf-net"
        and #cnct > 5 

}
