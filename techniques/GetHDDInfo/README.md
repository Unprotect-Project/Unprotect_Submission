# *Get HDD Info*

## Authorship information
* Nickname: *HoIIovv*
* Twitter: https://twitter.com/HoIIovv
* Website: https://nicolabottura.github.io/
* Linkedin: https://www.linkedin.com/in/nicola-bottura/
  
## Technique Information
* Technique title: GetHDDInfo
* Technique category: Anti-VM
* Technique description: the provided PoC shows how to retrieve the serial and model number for a physical disk. On VirtualBox, the returned values contain clear references to the hypervisor, which can be exploited to unveil the presence of the virtualized environment. The technique leverages DeviceIoControl Win32 API with IOCTL SMART_RCV_DRIVE_DATA. Requires root privileges to execute this IOCTL.

## Additional resources
* More details: https://nicolabottura.github.io/HDDInfo-Evasion-PoC.html