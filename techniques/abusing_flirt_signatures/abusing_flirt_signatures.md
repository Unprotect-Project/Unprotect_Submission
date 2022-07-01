# Code injection to abuse FLIRT signatures

## Authorship information
* Nickname: Lexsek
* Twitter: https://twitter.com/Lexsek_

## Technique Information
* Technique title: Code injection to abuse FLIRT signatures
* Technique category: Anti-Disassembly
* Technique description: FLIRT signatures are based on pattern of bytes and variant bytes to identify known library functions.
The refore, malwares can abuse known FLIRT signatures by replacing those variant bytes to hide malicious code inside functions that would be tagged as a legitimate library in order to trick the analysts.

## Additional resources
* https://hex-rays.com/products/ida/tech/flirt/in_depth/
* https://github.com/Maktm/FLIRTDB
* https://www.virustotal.com/gui/file/a41ba65405a032f4450ba80882cdd01d715d9d1684f4204050566be29a6dedb0

## Code snippets
* snipped.md