# Anti-Debugging: INT n, ret

## Authorship Information
* Name: Alex Schwarz
* Website: 
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Call to Interrupt Procedure
* Technique Category: Anti-Debugging
* Technique Description:  The INT n instruction generates a call to the interrupt or exception handler specified with the destination operand. We execute the `int 0x03` instruction and then `ret` (0xCD03, 0xC3) nested in a __try, __except block, and in the case of a debugger being present our except block will not be executed and our function returns TRUE.  

## Code Snippets
* int-n.cpp
