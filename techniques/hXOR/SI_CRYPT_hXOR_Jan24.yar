rule SI_CRYPT_hXOR_Jan24 : Crypter {

    meta:
        version = "1.0"
        date = "2024-01-04"
        modified = "2024-01-04"
        status = "RELEASED"
        sharing = "TLP:CLEAR"
        source = "SECUINFRA Falcon Team"
        author = "Marius Genheimer @ Falcon Team"
        description = "Detects executables packed/encrypted with the hXOR-Packer open-source crypter."
        category = "TOOL"
        mitre_att = "T1027.002"
        actor_type = "CRIMEWARE"
        reference = "https://github.com/akuafif/hXOR-Packer"
        hash = "7712186f3e91573ea1bb0cc9f85d35915742b165f9e8ed3d3e795aa5e699230f"
        minimum_yara = "4.2.0"
        best_before = "2025-01-04"

    strings:

        //This rule has been validated for the compression, encryption and compression+encryption modes of hXOR

        //Signature to locate the payload
        $binSignature = {46 49 46 41} 

        //Strings likely to be removed in attempts to conceal crypter
        $s_1 = "hXOR Un-Packer by Afif, 2012"
        $s_2 = "C:\\Users\\sony\\Desktop\\Packer\\"
        $s_3 = "H:\\Libraries\\My Documents\\Dropbox\\Ngee Ann Poly\\Semester 5\\Packer"
        $s_4 = "Scanning for Sandboxie..."
        $s_5 = "Scanning for VMware..."
        $s_6 = "Executing from Memory >>>>"
        $s_7 = "Extracting >>>>"
        $s_8 = "Decompressing >>>>"
        $s_9 = "Decrypting >>>>"

        //Anti-Analysis
        $aa_1 = "SbieDll.dll"
        $aa_2 = "VMwareUser.exe"
        $aa_3 = "GetTickCount"
        $aa_4 = "CreateToolhelp32Snapshot"

    condition:
        uint16(0) == 0x5A4D
        and uint16(0x28) != 0x0000 //IMAGE_DOS_HEADER.e_res2[0] contains offset for payload
        and $binSignature in (200000..filesize)
        and ((any of ($s_*)) or (none of ($s_*)))
        and 3 of ($aa_*)
}