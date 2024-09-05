# Impair Defenses: Impair Command History Logging

## Authorship Information

* Name: Issac Briones (@1d8)
* Website: https://1d8.github.io
* Linkedin: https://linkedin.com/in/icyber

## Technique Information

* Technique Title: Impair Defenses: Impair Command History Logging
* Technique Category: Defense Evasion (MITRE)
* Technique description: An adversary can impair command history logging in Bash on a Linux system by taking advantage of the `HISTCONTROL` environment variable which controls how commands are saved in the command history file.  An adversary may set this environment variable so that commands starting with a space aren't saved in the command history file. 
* *NOTE: This is a code addition snippet and additional information added to the existing technique here: https://www.unprotect.it/technique/impair-defenses-impair-command-history-logging/*

## Additional Resources

* https://www.unprotect.it/technique/impair-defenses-impair-command-history-logging/

## Code Snippets

`export HISTCONTROL=ignorespace`
Then prepend all of their commands with a space character to avoid the executed commands being saved to the history file:
` whoami`
` id`
` cat /etc/passwd`


