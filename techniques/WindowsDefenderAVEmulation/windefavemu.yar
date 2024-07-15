rule YARA_Detect_WindowsDefender_AVEmulator
{
    meta:
        description = "Goat files inside Defender AV Emulator's file system. Often used in PE malware as an evasion technique to evade executing in Windows Defender's AV Emulator."
        author = "@albertzsigovits"
        date = "2024-07-10"
        reference = "https://media.defcon.org/DEF%20CON%2026/DEF%20CON%2026%20presentations/Alexei-Bulazel-Reverse-Engineering-Windows-Defender-Updated.pdf"
        sha256 = "eb80da614515ff14b3fc312bef38b0d765ce3f4356db5b7b301a3b7c47f7c311"

    strings:
        $ = "\\INTERNAL\\__empty" ascii wide
        $ = "myapp.exe" ascii wide
        $ = "aaa_TouchMeNot_.txt" ascii wide

    condition:
        uint16(0) == 0x5A4D
        and uint32(uint32(0x3C)) == 0x00004550
        and 2 of them
}
