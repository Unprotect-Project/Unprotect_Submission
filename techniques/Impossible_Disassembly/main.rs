#![no_main]

macro_rules! rogue_byte {
    ($byte:expr) => {
        unsafe {
            core::arch::asm!(
                "lea r8, [rip]",           // Get next position
                "add r8, 8",               // Offset after rogue
                "push r8",                 // Jump after rogue
                "ret",
                concat!(".byte ", $byte),  // inject rogue byte
                options(nostack, nomem)
            )
        }
    };
}

// $ pwn shellcraft amd64.linux.sh
#[no_mangle]
#[link_section=".text"]
static SHELLCODE: [u8; 48] = [
    0x6a,0x68,0x48,0xb8,0x2f,0x62,0x69,0x6e,0x2f,0x2f,0x2f,0x73,
    0x50,0x48,0x89,0xe7,0x68,0x72,0x69,0x01,0x01,0x81,0x34,0x24,
    0x01,0x01,0x01,0x01,0x31,0xf6,0x56,0x6a,0x08,0x5e,0x48,0x01,
    0xe6,0x56,0x48,0x89,0xe6,0x31,0xd2,0x6a,0x3b,0x58,0x0f,0x05
];

#[no_mangle]
fn main() -> usize {
    // Get shellcode function pointer
    let malicious: extern "C" fn() -> usize = unsafe { 
        std::mem::transmute(&SHELLCODE as *const _ as *const ())
    };

    rogue_byte!(0xe8);
    malicious();

    return 0;
}
