# *Sandbox Evasion: XBEL Recently Opened Files Check*

## Authorship information
* Issac Briones (@1d8)
* https://1d8.github.io
* https://linkedin.com/in/icyber
  
## Technique Information
* Technique Title: *XBEL Recently Opened Files Check*
* Technique category (required): *Sandbox Evasion*
* Technique description (required): Adversaries may employ various user activity checks to detect and avoid virtualization and analysis environments. This may include changing behaviors based on the results of checks for the presence of artifacts indicative of a virtual machine environment (VME) or sandbox. In this particular case, the malware checks to see if the wallpaper set on the machine is the default Windows wallpaper. 
* Technique description (required): The `recently-used.xbel` XML file documents recent files on a Linux system that were accessed by applications. By parsing the file & checking how many files were recently accessed, we can determine whether or not a system is likely a sandbox or virtual machine. If a system has a low amount of files being accessed, it's likely a sandbox/VM. 

## Additional resources
* https://attack.mitre.org/techniques/T1497/002/

