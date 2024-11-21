# Impossible Disassembly

## Authorship information
* Name or nickname (required): *Gelven*
* Website: https://gelven4sec.github.io
* Linkedin: *jpettersen*
* Email: *jo.pettersen@proton.me*

## Technique Information
* Technique title (required): Impossible Disassembly
* Technique category (required): Anti-Disassembly
* Technique description (required): Impossible disassembly is an anti-disassembling technique that involves inserting data bytes after a conditional jump instruction in order to prevent the real instruction that follows from being disassembled. This technique takes advantage of a basic assumption in disassembly, which states that one byte is only interpreted in the context of one instruction. By inserting a byte that is the opcode for a multibyte instruction, the disassembler will be unable to correctly interpret the next instruction, and will therefore generate incorrect disassembly output.

## Additional resources
* [Practical Malware Analysis: Ch 15: Anti-Disassembly](https://www.slideshare.net/SamBowne/practical-malware-analysis-ch-15-antidisassembly)
* [https://medium.com/swlh/assembly-wrapping-a-new-technique-for-anti-disassembly-c144eb90e036](https://medium.com/swlh/assembly-wrapping-a-new-technique-for-anti-disassembly-c144eb90e036)
* [Anti-disassembly with a rogue byte](https://gelven4sec.github.io/posts/rogue_byte/)

## Code snippets
* main.rs

## Detection rules
* rogue_byte.yar
