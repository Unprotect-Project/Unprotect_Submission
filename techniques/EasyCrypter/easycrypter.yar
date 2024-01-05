rule EasyCrypter {
    meta:
        author = "RussianPanda"
        description = "Detects EasyCrypter"
        date = "01/05/2024"
        hash = "60063c99fda3b6c5c839ec1c310b03e8f9c7c8823f2eb7bf75e22c6d738ffa8f"

    strings:
        $s1 = {F6 17 [16-20] 80 2F 36 [16-20] 80 07 87}
        $s2 = {81 38 50 45 00 00 [20-22] 8B 88 A0 00 00 00 [2-4] 8B 80 A4 00 00 00 [5-7] 8B 40 50 [50-56] 89 0C 24 89 44 24 04 C7 44 24 08 00 30 00 00 C7 44 24 0C 04 00 00 00 FF 15 ?? ?? ?? 00}

    condition: 
        uint16(0) == 0x5A4D
        and $s1 and $s2 
}
