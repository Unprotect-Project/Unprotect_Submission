rule halos_gate_detected {
  meta:
      author = "0x0d4y"
      description = "This rule detects intrinsic patterns of Halo's Gate."
      date = "2025-02-01"
      score = 80
      reference = "https://0x0d4y.blog/babbleloader-technical-malware-analysis/"
      yarahub_reference_md5 = "fa3d03c319a7597712eeff1338dabf92"
    strings:
    $halos_gate = { 48 8b 44 24 ?? 0f b6 ?? 83 f8 4c 0f ?? ?? ?? ?? ?? 48 8b 44 ?? ?? 0f b6 ?? ?? 3d 8b ?? ?? ?? 75 ?? 48 8b 44 ?? ?? 0f b6 40 ?? 3d d1 ?? ?? ?? 75 ?? 48 8b 44 ?? ?? 0f b6 40 ?? 3d b8 ?? ?? ?? 75 ?? 48 8b 44 ?? ?? 0f b6 40 ?? 85 c0 75 ?? 48 8b 44 ?? ?? 0f b6 40 ?? 85c0 75 ?? 48 8b 44 ?? ?? 0f b6 40 ?? 88 44 ?? ?? 48 8b 44 24 ?? 0f b6 40 ?? 88 44 ?? ?? 0f b6 44 ?? ?? c1 e0 08 0f b6 4c ?? ?? 0b c1 48 8b 8c ?? ?? ?? ?? ?? 89 01 ?? ?? ?? ?? ?? 48 8b 44 ?? ?? 0f b6 00 3d e9 ?? ?? ?? }
    condition:
        uint16(0) == 0x5a4d and
        $halos_gate
}