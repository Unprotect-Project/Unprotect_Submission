# *Anti-UPX Unpacking*

## Authorship information
* Nickname: *hackeT*
* Twitter: *https://twitter.com/T_8ase*
* Linkedin: *https://www.linkedin.com/in/tatsuya-hasegawa-aa3279142/*
  
## Technique Information
* Technique Title: **Anti-UPX Unpacking**
* Technique category: **packers**
* MITRE ATT&CK category: **Defense Evasion::Obfuscated Files or Information::Software Packing [T1027.002]**
* MBC category: **Anti-Static Analysis::Software Packing::UPX [F0001.008]**
* Technique description: 

Anti-UPX Unpacking is the technique to prevent malware from being unpacked by tools like "upx" easily.
ELF format's IoT malware like Mirai generally uses this technique.
The normal UPX packing uses “UPX!” as a magic number, while Mirai assigns a different value to each sample. 
UPX-packed binary contains the following information in the header and magic number is in "l_magic".
In addition, “p_filesize” and “p_blocksize” are also zero-padded in some samples.
These falsification patterns are mentioned by CUJO's blog in order to bypass unpacking by "upx -d".
- Rewriting the UPX! magic headers
- ELF magic bytes are modified
- Copyright string is modified
- Section header names are modified
- Extra junk bytes added throughout the binary
- Custom UPX: since UPX is open source, anyone can go and look at its source code on Github and modify certain methods or re-write complete functions.
Regardless these header modifications, the samples can be unpacked and run correctly when it is executed.


This is the ELF upx header structures which the original source is from https://github.com/upx/upx/blob/master/src/stub/src/include/linux.h

struct b_info // 12-byte header before each compressed block
{ 

uint32_t sz_unc; // uncompressed_size
uint32_t sz_cpr; // compressed_size
unsigned char b_method; // compression algorithm
unsigned char b_ftid; // filter id
unsigned char b_cto8; // filter parameter
unsigned char b_unused; // unused

}; 

struct l_info // 12-byte trailer in header for loader (offset 116)
{ 

uint32_t l_checksum; // checksum
uint32_t l_magic; // UPX! magic [55 50 58 21]
uint16_t l_lsize; // loader size
uint8_t l_version; // version info
uint8_t l_format; // UPX format 

}; 

struct p_info // 12-byte packed program header follows stub loader
{ 

uint32_t p_progid; // program header id [00 00 00 00]
uint32_t p_filesize; // filesize [same as blocksize]
uint32_t p_blocksize; // blocksize [same as filesize] 

}; 



## References
https://blogs.jpcert.or.jp/en/2022/03/anti_upx_unpack.html

https://cujo.com/upx-anti-unpacking-techniques-in-iot-malware/

https://bsodtutorials.wordpress.com/2014/11/14/upx-packing-and-anti-packing-techniques/

https://www.akamai.com/blog/security/upx-packed-headaches


## Detection rules

**yara**
./anti_upx_unpacking_elf.yar



