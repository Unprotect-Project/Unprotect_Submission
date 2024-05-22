# *Hide Artifacts: Hidden Window*

## Authorship information
* Name: Issac Briones (@1d8)
* Website: https://1d8.github.io
* Linkedin: https://linkedin.com/in/icyber
  
## Technique Information
* Technique Title - Hide Artifacts: Hidden Window
* Technique Category - Defense Evasion (MITRE)
* Technique Description - Adversaries may use hidden windows to conceal malicious activity from the plain sight of users. In some cases, windows that would typically be displayed when an application carries out an operation can be hidden. This may be utilized by system administrators to avoid disrupting user work environments when carrying out administrative tasks. On Windows, there are a variety of features in scripting languages in Windows, such as PowerShell, Jscript, and Visual Basic to make windows hidden. One example of this is powershell.exe -WindowStyle Hidden. Adversaries may abuse these functionalities to hide otherwise visible windows from users so as not to alert the user to adversary activity on the system.
* *NOTE: This is a code addition snippet to the existing technique here: https://www.unprotect.it/technique/hide-artifacts-hidden-window/*

## Additional resources
* https://www.unprotect.it/technique/hide-artifacts-hidden-window/

## Code snippets
```c
#include <windows.h>
#include <stdio.h>
void main() {
    HWND winHandle = GetConsoleWindow();
    ShowWindow(winHandle, SW_HIDE);
}
```

