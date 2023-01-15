

Detect hypertreading capacity through CPUID
   mov eax, 1 ; Set EAX to 1 in order to access to the leaf processor info and feature bits
   cpuid ; call cpuid
   shr edx,28 ; shift the bit 28 ( which is hypertread bit on intel )
   and edx,1 ; cleanup
   ; 0 in edx means no hyperthearding capacity.

Detect unique cpu through PEB
   mov   eax, [fs:0x30]    ; Get PEB
   mov   eax,[eax+0x64]    ; Get Cpu Count
   dec   eax
   jnz   _isnot_pebuniq    ; If eax = 0 , we have only one CPU
   ret


