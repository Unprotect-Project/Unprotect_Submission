# This requires file auditing from GPO to be applied to work
$query = "SELECT * FROM __InstanceCreationEvent WITHIN 5 WHERE TargetInstance ISA 'Win32_NTLogEvent' AND (TargetInstance.EventCode = '4663')"
Register-WmiEvent -Query $query -Action {
	Write-Host '[+] File deletion or network share access detected. Likely not a sandbox...'
	New-Item -Path "C:\Users\Administrator\Desktop\SandboxStop.txt" -ItemType File
}
