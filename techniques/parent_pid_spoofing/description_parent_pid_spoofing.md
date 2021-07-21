# Parent PID Spoofing

## Authorship Information
* Name: Halil Dalabasmaz
* Website: artofpwn.com
* Twitter: https://twitter.com/hlldz
* Linkedin: https://www.linkedin.com/in/hlldz
  
## Technique Information
* Technique Title: Parent PID Spoofing
* Technique Category: Defense Evasion [Mitre]
* Technique Description: You can spoof the parent process identifier (PPID) of a new process to evade process-monitoring defenses. New processes are typically spawned directly from their parent, or calling, process unless explicitly specified. One way of explicitly assigning the PPID of a new process is via the CreateProcess API call, which supports a parameter that defines the PPID to use.

## Additional resources
* https://github.com/hlldz/APC-PPID
