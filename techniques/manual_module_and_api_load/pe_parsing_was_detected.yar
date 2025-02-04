rule pe_parsing_was_detected {

    meta:
        author = "0x0d4y"
        description = "This rule detects intrinsic patterns of PE Parsing."
        date = "2025-02-03"
        score = 70
        reference = "https://0x0d4y.blog/babbleloader-technical-malware-analysis/"
        yarahub_reference_md5 = "fa3d03c319a7597712eeff1338dabf92"

    strings:
    $peb_walking_ldr_x64 = { 65 48 8b 04 25 60 ?? }
    $peb_walking_ldr_x32 = { 64 a1 30 ?? }
    $mz_header_parsing = { ?? 4d 5a }
    $pe_header_parsing = { ?? 50 45 }

    condition:
        uint16(0) == 0x5a4d and
        3 of ($peb_walking_ldr_x64, $peb_walking_ldr_x32, $mz_header_parsing, $pe_header_parsing)

}