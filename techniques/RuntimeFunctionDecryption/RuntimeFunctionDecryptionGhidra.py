def decryptShellcode(size, xor_key, rva):
    va = rva + 0x400000
    va = hex(va)[2:]
    addr = toAddr(va)
    addr2 = addr
    enc = get_bytes(toAddr(va), size)
    for i in range(size):
            clearListing(addr2)
            addr2 = addr2.add(1)
    size2 = size
    for i in range(0,size):
        enc[i] = enc[i]^xor_key
        
            
    for i in enc:
       i = i & 0xFF
       setByte(addr, i)
       addr = addr.add(1)
