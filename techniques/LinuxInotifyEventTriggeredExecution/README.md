# Event Triggered Execution: Linux Inotify

## Authorship Information

* Name: Issac Briones (@1d8)
* Website: https://1d8.github.io
* Linkedin: https://www.linkedin.com/in/icyber

## Technique Information

* Technique Title: Event Triggered Execution: Linux Inotify
* Technique Category: Process Manipulating
* Technique description: Adversaries may establish persistence and/or elevate privileges using system mechanisms that trigger execution based on specific events. Various operating systems have means to monitor and subscribe to events such as logons or other user activity such as running specific applications/binaries.

## Additional Resources

* https://attack.mitre.org/techniques/T1546/

## Code Snippets

The attached code snippet will trigger after a file creation event occurs within the `/tmp` directory. It will read the contents of the newly created file. 

