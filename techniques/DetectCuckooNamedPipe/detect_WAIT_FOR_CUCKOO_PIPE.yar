rule detect_cuckoo_named_pipe
{
    meta:
        description = "Detect executables that check for Cuckoo Sandbox via \\\\.\\pipe\\cuckoo using WaitNamedPipeA/W"
        author      = "Nicola Bottura"
        date        = "2025-07-23"
        reference   = "User‐provided C code snippet (techniques/DetectCuckooNamedPipe/detect_cuckoo.c)"

    strings:
        // ASCII and WIDE versions of the pipe name
        $pipe_ascii = "\\\\.\\pipe\\cuckoo"
        $pipe_wide = { 5C 00 5C 00 2E 00 5C 00 70 00 69 00 70 00 65 00 5C 00 63 00 75 00 63 00 6B 00 6F 00 6F 00 }

        // API names
        $api_A      = "WaitNamedPipeA"
        $api_W      = "WaitNamedPipeW"

    condition:
        $pipe_ascii and $api_A or $pipe_wide and $api_W
}
