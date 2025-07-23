rule detect_fastfail_processor_feature_check
{
    meta:
        description = "Detects Windows 8+ fast-fail feature check and __fastfail stub (int 29h)"
        author      = "Nicola Bottura"
        date        = "2025-07-23"
        reference   = "User‐provided C code snippet (techniques/DetectWin8/detect_win8+.c)"

    strings:
        // API import
        $api        = "IsProcessorFeaturePresent"
        // Immediate PF_FASTFAIL_AVAILABLE value (0x17) as little-endian dword
        $const      = { 17 00 00 00 }
        // The __fastfail stub: push 2; pop ecx; int 29h
        $stub1      = { 6A 02 59 CD 29 }
        // The __fastfail stub: mov ecx, 2; int 29h
        $stub2      = { B9 02 00 00 00 CD 29 }

    condition:
        $api and $const and ($stub1 or $stub2)
}
