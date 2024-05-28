# BuildCommDCBAndTimeoutA

## Authorship information
* Nickname: Huntress Research Team (Alden Schmidt, Adam Rice, Matt Kiely)
* Twitter: https://twitter.com/HuntressLabs
* Linkedin:
* Mastodon:

## Technique Information
* Technique Title: **UXXX | T1497.002 - System Checks - BuildCommDCBAndTimeoutsA
* Technique category: **Sandbox Evasion**
* Technique description: This technique uses a `BuildCommDCBAndTimeoutsA` API call to determine if the malware is detonating in a sandbox. Normally, a bogus device string would cause this API call to fail. However, some malware sandbox environments may emulate in a way that allows the API call to succeed even when given a bogus device string. See the proof of concept code for more details.

## Code Snippets
* BuildCommDCBAndTimeoutA_sandbox_evasion.c
