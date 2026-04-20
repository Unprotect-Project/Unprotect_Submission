rule smart_assembly
{
  meta:
    author = "Euler Neto"
    description = "Rule to detect the utilization of the .NET packer SmartAssembly"
    target_entity = "file"
  strings:
    $sig1 = "SmartAssembly.Attributes"
    $sig2 = "Powered by SmartAssembly"
    $s1 = "#Strings"
  condition:
    uint16(0) == 0x5a4d
    and any of ($sig*)
    and $s1
}