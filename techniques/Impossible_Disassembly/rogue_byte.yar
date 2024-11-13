rule RogueByte
{
    meta:
        description = "Detect disassembly obfuscation with a rogue byte"
        author = "Joakim (Gelven) Pettersen"
        date = "2024-11-08"

    /*
    Example:
    48 8d 05 00 00 00 00    lea    rax,[rip+0x0]
    48 83 c0 07             add    rax,0x7
    50                      push   rax
    c3                      ret
    */
    strings:
        /* rax..rdi */
        $s1 = { 48 8D ?? 00 00 00 00 [0-10] 48 83 ?? 07 [0-10] ( FF E? | 5? C3 ) }
        /* r8..r15 */
        $s2 = { 4C 8D ?? 00 00 00 00 [0-10] 49 83 ?? 08 [0-10] ( 41 FF E? | 41 5? C3 ) }

    condition:
        any of them
}
