# Change Command Line at Runtime

## Authorship Information
* Name: Alex Schwarz
* Website: https://github.com/AlSch092
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Change Process Command Line at Runtime
* Technique Category: Process Manipulation
* Technique Description: We can change the command line of any running process by modifying the 'ProcessParameters' parameter in a program's PEB. The 'ProcessParameters' member is a PRTL_USER_PROCESS_PARAMETERS structure containing the 'Buffer' and 'Length' members which we can write over with our own values. Remember to make sure you're writing the correct Length value with your new command line string. This technique can help hide your process from other processes, assuming the other processes read your file path and process name from the command line. We can also change our command line to the same value as other running processes. On some occasions, modifying the command line at runtime might even allow you to change the behaviour of trusted applications. 

## Code Snippets
* ChangeCommandLine.cpp
