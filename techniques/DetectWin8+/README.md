# *Detect Windows 8 or higher system*

## Authorship information
* Nickname: *HoIIovv*
* Twitter: https://twitter.com/HoIIovv
* Website: https://nicolabottura.github.io/
* Linkedin: https://www.linkedin.com/in/nicola-bottura/
  
## Technique Information
* Technique title: DetectWin8+
* Technique category: Anti-Monitoring
* Technique description: Beginning in Windows 8, Microsoft introduced the "fast-fail" mechanism to terminate the calling process with minimal overhead. Critical failures that have potentially corrupted the program’s state or stack beyond recovery cannot be handled by the regular exception‐handling facility. To address these, the compiler‐intrinsic __fastfail was added: it immediately aborts the process using low‐cost, bounded‐time code paths.

A program can detect whether it’s running on Windows 8 or later by querying the IsProcessorFeaturePresent API for PF_FASTFAIL_AVAILABLE. If this feature is present, the fast-fail mechanism is supported; if not, the program is on an older Windows version. An attacker could exploit this check to stealthily determine the Windows version by invoking what appears to be harmless fault‑handling operations.

Yara rules are provided but they may find various false positives as the patterns related to the technique are quite common.
