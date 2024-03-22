# *BlockInput*

## Authorship information
* Name or nickname (required): *Serhii*
* Twitter: https://twitter.com/semelnyk
* Linkedin: https://www.linkedin.com/in/serhii-melnyk
* Email: serhiimelnyk@outlook.com
  
## Technique Information
* Technique title (required): BlockInput
* Technique category (required): Anti-Debugging
* Technique description (required): As per Microsoft's documentation, BlockInput function "prevents keyboard and mouse input events from reaching applications," effectively restricting user interaction with the system. Malware occasionally employs this tactic to hinder analysis by debuggers or other analysis tools throughout the process' runtime. To deactivate the block, the program must make a live call to BlockInput with the parameter 0. Windows automatically lifts the block when the process ends or the user initiates Ctrl+Alt+Del.

## Additional resources
* https://learn.microsoft.com/en-gb/windows/win32/api/winuser/nf-winuser-blockinput

## Code snippets
* Please add your code in separate files.

## Detection rules
* Please add your rules in separate files.
