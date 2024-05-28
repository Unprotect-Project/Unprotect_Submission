# Process Reimaging

## Authorship Information
* Name: 一半人生
* Website: https://github.com/TimelifeCzy
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Process Reimaging
* Technique Category: Process Manipulating
* Technique Description: Process Reimaging is a technique used to evade detection by endpoint security solutions. It is a variation of the Process Hollowing or Process Doppelganging techniques, which are used to execute arbitrary code in the context of another process.

The Windows operating system has inconsistencies in how it determines the locations of process image FILE_OBJECTs, which can impact the ability of endpoint security solutions, such as Microsoft Defender Realtime Protection, to accurately detect the correct binaries loaded in malicious processes. This inconsistency can be exploited using the Process Reimaging technique, which does not require code injection.

## Code Snippets
* process_reimaging.cpp
