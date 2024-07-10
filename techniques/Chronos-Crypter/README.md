# *Cronos-Crypter*

## Authorship information
* Name or nickname (required): *ForensicITGuy*
* Twitter: https://twitter.com/ForensicITGuy
* Website: https://forensicitguy.github.io
* Linkedin: https://www.linkedin.com/in/tonymlambert/
  
## Technique Information
* Technique title (required): Cronos-Crypter
* Technique category (required): Packers
* Technique description (required): Cronos-Crypter is an open-source crypter publicly available on GitHub. The crypter applies AES encryption or XOR obfuscation to a selected payload before storing it as a .NET resource of a final generated .NET executable payload. Cronos-Crypter contains multiple capabilties for persistence and defense evasion. An operator may select persistence via a Windows Registry autorun key or a Scheduled Task. An operator may also select for decrypted payloads to be injected into a newly spawned copy of itself or `regasm.exe`. To further evade defenses, the operator may also specify to introduce a sleep delay, bypass AMSI controls, and avoid execution within virtual machine environments.

## Additional resources
* https://github.com/TalosSec/Cronos-Crypter
