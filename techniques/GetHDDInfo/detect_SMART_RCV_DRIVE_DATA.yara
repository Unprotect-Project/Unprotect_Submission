rule HDDInfo_rule
{
	meta:
		description = "Detect DeviceIoControl call with Io Control Code  SMART_RCV_DRIVE_DATA (0x7C088)"
		author = "Nicola Bottura"
		date = "2024-02-17"
		reference = "https://nicolabottura.github.io/HDDInfo-Evasion-PoC.html"
		hash = "aa202ae4d12e03887bb81c3a9129f44c464f54c790990494885d29bcde0ef4c1"
	strings:
		$api = "DeviceIoControl" nocase wide ascii
		$ioctl = { 88 C0 07 }

	condition:
		all of ($*)
}