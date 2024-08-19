rule YARA_Detect_AlKhaser_AntiDebug_WriteWatch
{
    meta:
        description = "Default invalid parameter values of Al-Khaser's Anti-Debug technique (VirtualAlloc/MEM_WRITE_WATCH). Used for checking API hooks in debuggers/sandboxes."
        author = "@albertzsigovits"
        date = "2024-07-10"
        reference = "https://github.com/LordNoteworthy/al-khaser/blob/967afa0d783ff9625caf1b069e3cd1246836b09f/al-khaser/AntiDebug/WriteWatch.cpp#L85"
        sha256 = "e07383f6a340d8422a69b1d40cf848652165517407f7d0dc7260eed4a76499b3"

    strings:
        $ = "%ThisIsAnInvalidEnvironmentVariableName?[]<>@\\;*!-{}#:/~%" ascii wide
        $ = "%ThisIsAnInvalidFileName?[]<>@\\;*!-{}#:/~%" ascii wide

    condition:
        uint16(0) == 0x5A4D
        and uint32(uint32(0x3C)) == 0x00004550
        and any of them
}
