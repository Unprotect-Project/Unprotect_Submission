# Shikata Ga Nai (SGN)

## Authorship information
* Name or nickname : Dreamkinn
* Twitter: https://twitter.com/dreamkinn
  
## Technique Information
* Technique title : Shikata Ga Nai (SGN)
* Technique category : Data obfuscation
* Technique description : Shikata Ga Nai (SGN) is a polymorphic binary encoding scheme developed by [Ege Balci](https://github.com/EgeBalci/sgn) and further popularized by its implementation in Metasploit Framework's infamous `msfvenom`. Provided a binary input, SGN will output a self-decoding obfuscated shellcode. The algorithm encodes the input using a XOR feedback loop and prepends a decoding routine to it. After adding some garbage instructions, the initial payload is fully obfuscated and remains very resistant to static heuristic analysis. The blob can be run from the first instruction and will decode&run the original binary payload. Note that in order for the decoding part to execute properly, the SGN-encoded shellcode should live in a RWX protected memory space.

## Additional resources
* https://github.com/EgeBalci/sgn
* https://github.com/rapid7/metasploit-framework/blob/master/modules/encoders/x86/shikata_ga_nai.rb
* https://www.mandiant.com/resources/blog/shikata-ga-nai-encoder-still-going-strong


## Code snippets
* sgn.sh

## Detection rules
* sgn.yar
