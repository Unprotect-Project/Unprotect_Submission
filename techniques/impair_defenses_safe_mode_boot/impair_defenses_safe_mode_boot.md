# Modification Authorship : 0x0d4y

# Technique - Impair Defenses: Safe Mode Boot

# Code snippet

## Through CMD

Below are code snippets for executing this technique.

```cmd
C:> bootcfg /raw /a /safeboot:network /id 1
C:> bcdedit /set {current} safeboot network
```

# Detection rules

Below is a Sigma detection rule to detect the execution of this technique

## SIGMA Detection Rule

```yaml
title: Impair Defenses Through Safe Mode Boot was Detected
description: Detects the Impair Defenses tatic, through safe mode boot technique
date : 04/12/2024
author: 0x0d4y
references:
- https://www.trendmicro.com/en_us/research/22/e/examining-the-black-basta-ransomwares-infection-routine.html
- https://blog.qualys.com/vulnerabilities-threat-research/2021/07/07/analyzing-the-revil-ransomware-attack
tags:
- attack.defense.evasion
- attack.T1562.009
- malware.ransomware
logsource:
      category: process_creation
      product: windows
detection:
    selection1:
        EventID:
            - '4688'
            - '1'
        NewProcessName:
            - 'bcdedit.exe'    
        CommandLine:
            - '*/set {current} safeboot*'
    selection2:
        EventID:
            - '4688'
            - '1'
        NewProcessName:
            - 'bootcfg.exe'
        CommandLine:
            - '*/safeboot:network /id 1*'
      condition: selection1 or selection2
level: critical
```