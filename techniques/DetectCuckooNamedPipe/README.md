# *Detect Cuckoo by named pipe*

## Authorship information
* Nickname: *HoIIovv*
* Twitter: https://twitter.com/HoIIovv
* Website: https://nicolabottura.github.io/
* Linkedin: https://www.linkedin.com/in/nicola-bottura/
  
## Technique Information
* Technique title: DetectCuckooNamedPipe
* Technique category: Sandbox Evasion
* Technique description: Cuckoo is an open-source automated malware analysis system that facilitates dynamic analysis by running suspicious files within isolated virtual environments. Communication between the analysis host and the virtualized guest is established through a specific named pipe: `\\.\pipe\cuckoo`. Malware executed inside the guest system may exploit this implementation detail to detect the analysis environment—by attempting to connect to or wait for the pipe, the malware can infer that it is being monitored.

This detection method bears resemblance to the [https://unprotect.it/technique/checking-pipe/](Checking Pipe) technique, although it relies on a different API or implementation nuance to identify the sandbox. This particular evasion tactic was observed in a real-world malware sample (SHA-256: c4692372e62ead639ec700883b4da4805809612a4d0c40dfca59c4854447ced0), highlighting its practical use in the wild.
