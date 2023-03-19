#Originally from: https://github.com/wand3rlust/Niernen

import random

#Encode shellcode using XOR, ADD, SUB, ROL, and ROR
def encode_shellcode(shellcode, key):
    encoded_shellcode = bytearray()
    for i, byte in enumerate(shellcode):
        #XOR
        xored_byte = byte ^ key[i % len(key)]
        #ADD
        added_byte = (xored_byte + key[(i + 1) % len(key)]) % 256
        #SUB
        subbed_byte = (added_byte - key[(i + 2) % len(key)]) % 256
        #ROL
        rolled_byte = ((subbed_byte << 1) | (subbed_byte >> 7)) % 256
        #ROR
        ror_byte = ((rolled_byte >> 1) | (rolled_byte << 7)) % 256
        encoded_shellcode.append(ror_byte)
    return bytes(encoded_shellcode)


#Generate a random key of given length and convert it into bytes
def generate_key(length):
    return bytes([random.randint(0, 255) for i in range(length)])


plaintext_shellcode = input("\nEnter plaintext shellcode: ")
#Encode the user unput into UTF-8 and change from string to byte
shellcode = plaintext_shellcode.encode()
#Generate same length key as shellcode hex
key = generate_key(len(shellcode))
#Call encode_shellcode function with 2 arguments i.e, UTF-8 shellcode and key
encoded_shellcode = encode_shellcode(shellcode, key)
print("\nOriginal shellcode (in hex): ", shellcode.hex())
print("\nKey (in hex): ", key.hex())
print("\nEncoded shellcode (in hex): ", encoded_shellcode.hex())
#Convert byte format to string
encoded_shellcode = encoded_shellcode.hex()
#Append \x after every 2nd character
encoded_shellcode = "\\x" + "\\x".join(encoded_shellcode[i:i + 2] for i in range(0, len(encoded_shellcode), 2))
print("\nEncoded shellcode (with \\x): ", encoded_shellcode)
print("\n")
