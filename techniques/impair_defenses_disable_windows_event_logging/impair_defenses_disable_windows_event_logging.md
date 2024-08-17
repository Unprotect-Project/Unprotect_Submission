# Modification Authorship : 0x0d4y
### Email    : 0x0d4y_researcher@0x0d4y.blog
### Blog     : https://0x0d4y.blog/
### LinkedIn : https://www.linkedin.com/in/icaro-cesar/

# Technique - Impair Defenses: Disable Windows Event Logging

# Code snippet

## Through CMD

Below are code snippets for executing this technique.

```powershell
# Disable Windows Event Log through service
C:> sc config eventlog start=disabled

# Disable each Windows Event Log Category through auditpool
C:> auditpol /set /category:"Account Logon" /success:disable /failure:disable
C:> auditpol /set /category:"Detailed Tracking" /success:disable /failure:disable

# Clear and Disable all Categories
C:> auditpol /clear /y
C:> auditpol /remove /allusers

# Disable Windows Event Log Category through wevtutil
C:> wevtutil sl Security /e:false

# Disable Windows Event Log thourgh Regitry Log Channels
C:> reg add "HKEY_LOCAL_MACHINE\Microsoft\Windows\CurrentVersion\WINEVT\Channels\<anychannel>" /v Enabled /t REG_DWORD /d 0 /f
```

## Through PowerShell

```powershell
C:> Set-Service -Name EventLog -Status Stopped
```

# Detection rules

Below is a Sigma detection rule to detect the execution of this technique

## SIGMA Detection Rule

```yaml
title: Impair Defenses Through Disable Windows Event Logging was Detected
description: Detects the Impair Defenses tatic, through disable windows event logging technique
date : 04/12/2024
author: 0x0d4y
references:
- https://thedfirreport.com/2021/11/15/exchange-exploit-leads-to-domain-wide-ransomware/
- https://www.microsoft.com/en-us/security/blog/2021/01/20/deep-dive-into-the-solorigate-second-stage-activation-from-sunburst-to-teardrop-and-raindrop/
- https://attack.mitre.org/techniques/T1562/002/
tags:
- attack.defense.evasion
- attack.T1562.002
- malware.generic
logsource:
      category: process_creation, powershell_cmdlet, regitry_modification
      product: windows
detection:
    selection1:
        EventID:
            - '4688'
            - '1'
        NewProcessName:
            - 'sc.exe'    
        CommandLine|contains:
            - '*eventlog start=disabled*'
    selection2:
        EventID:
            - '4688'
            - '1'
        NewProcessName:
            - 'auditpol.exe'
        CommandLine|contains:
            - '*/success:disable*'
            - '*/clear*'
            - '*/remove*'
    selection3:
        EventID:
            - '4688'
            - '1'
        NewProcessName:
            - 'wevtutil.exe'
        CommandLine|contains:
            - '*sl*'
    selection4:
        EventID:
            - '4688'
            - '1'
        NewProcessName:
            - 'reg.exe'
        CommandLine|contains:
            - '*add*SOFTWARE\\Windows\\CurrentVersion\\WINEVT\\Channels\\*REG_DWORD /d 0*'
    selection5:
        EventID:
            - '13'
            - '4657'
        TargetRegistry|contains:
            - '*SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WINEVT\\*'
        Details:
            - 0
            - 0x00000000
    selection6:
        EventID:
            - '4104'
        Message|contains:
            - '*Set-Service -Name EventLog -Status Stopped*'
      condition: selection1 or selection2 or selection3 or selection4 or selection5 or selection6
level: critical
```