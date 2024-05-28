# *Stack Strings*

## Authorship information
* Name or nickname (required): *Serhii*
* Twitter: https://twitter.com/semelnyk
* Linkedin: https://www.linkedin.com/in/serhii-melnyk
* Email: serhiimelnyk@outlook.com
  
## Technique Information
* Technique title (required): Stack Strings
* Technique category (required): Anti-Disassembly
* Technique description (required): This approach involves breaking a string into individual characters and dynamically rebuilding it when the program runs. Known as "stack strings," each character of the string is stored in an array, making it difficult for analysts to extract the string's contents using standard tools. This method involves placing each character of the string into consecutive memory locations during runtime using MOV instructions.

## Additional resources
* https://www.tripwire.com/state-of-security/ghidra-101-decoding-stack-strings
* https://medium.com/@DCSO_CyTec/hostile-code-dealing-with-stack-strings-in-idapython-7a487b822518
* https://maxkersten.nl/binary-analysis-course/analysis-scripts/ghidra-script-to-handle-stack-strings/

## Code snippets
* Please add your code in separate files.

## Detection rules
* Please add your rules in separate files.
