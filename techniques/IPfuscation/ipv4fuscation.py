def generate_ipv4_string(shellcode):
    shellcode_size = len(shellcode)
    
    # Ensure shellcode size is a multiple of 4
    if shellcode_size % 4 != 0:
        raise ValueError("Shellcode size must be a multiple of 4.")
    
    ipv4_array = []
    number_of_ip = 0

    # Generate shellcode every 4 bytes
    for i in range(0, shellcode_size, 4):
        ip = f"{int(shellcode[i], 16)}.{int(shellcode[i+1], 16)}.{int(shellcode[i+2], 16)}.{int(shellcode[i+3], 16)}"
        number_of_ip += 1

        if number_of_ip % (shellcode_size // 4) == 0:
            ipv4_array.append(f'"{ip}"')
        elif number_of_ip % 8 == 0:
            ipv4_array.append(f'\n\t"{ip}",')
        else:
            ipv4_array.append(f'"{ip}",')

    # Print the result in the same format
    print(f"char * payload[{len(ipv4_array)}] = {{ \n\t{''.join(ipv4_array)}\n}};\n")

shellcode = ["0x48","0x65","0x6c","0x6c","0x6f","0x20","0x55","0x6e","0x70","0x72","0x6f","0x74","0x65","0x63","0x74","0x50","0x72","0x6f","0x6a","0x65","0x63","0x74","0x2c","0x20","0x74","0x68","0x69","0x73","0x20","0x69","0x73","0x20","0x49","0x50","0x76","0x34","0x20","0x6f","0x62","0x66","0x75","0x73","0x63","0x61","0x74","0x69","0x6f","0x6e","0x20","0x3a","0x29","0x00"]
generate_ipv4_string(shellcode)