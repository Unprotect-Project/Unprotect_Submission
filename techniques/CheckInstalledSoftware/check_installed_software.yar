rule check_installed_software {

  meta:
    author = "RussianPanda"
    date = "1/14/2024"
    reference = "https://unprotect.it/technique/checking-installed-software/"
    hash = "db44d4cd1ea8142790a6b26880b41ee23de5db5c2a63afb9ee54585882f1aa07"

  strings:
    $d1 = "DisplayVersion"
    $u1 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
    $reg = "RegOpenKeyExA"
    $h = {68 (01|02) 00 00 80}
  condition:
    uint16(0) == 0x5A4D
    and for any i in (1..#u1) : ($d1 in (@u1[i] - 200..@u1[i] + 200))
    and $reg and $h

}
