;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Anti-Disassembly Technique: Abusing the Return Pointer
;
; This code demonstrates a technique to confuse disassemblers by manipulating
; the return pointer and using RET instructions in unexpected ways.
;
; How it works:
; 1. The code starts with a normal function call to establish legitimacy
; 2. Then it abuses the return pointer by:
;    - Pushing a calculated address into the middle of function2
;    - Using RET to jump there instead of actually returning
; 3. This tricks disassemblers because:
;    - They expect RET to mark the end of a function
;    - They can't easily track the dynamic control flow
;    - They may miss the code after the jump target
;
; Analysis Impact:
; - Static analysis tools will likely show incorrect control flow
; - Disassemblers may miss chunks of code entirely
; - Function boundaries become unclear
; - Makes it harder to understand the actual execution path
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.386
.model flat, stdcall
.code

start:
    ; Legitimate looking function call to establish normal pattern
    call normal_function    
    
    ; Here's where we start the anti-disassembly technique
    push offset hidden_function + 5  ; Push address into middle of function
    ret                             ; Jump to that address instead of returning
                                   ; Most disassemblers will think code ends here
    
    ; Decoy instructions that may confuse analysis
    mov eax, 0
    jmp $
    
normal_function:
    push ebp
    mov ebp, esp
    
    ; Normal looking code to appear legitimate
    xor eax, eax
    inc eax
    
    pop ebp
    ret
    
hidden_function:
    ; First few bytes might never be executed
    push ebp
    mov ebp, esp
    
    ; This is where execution actually continues
    ; Disassemblers may miss this entirely
    mov ebx, 0DEADBEEFh    ; Hidden payload
    xor ecx, ecx
    add edx, ebx
    
    ; More anti-analysis tricks
    call $+5               ; Push next instruction address
    pop eax               ; Get that address in eax
    add eax, 10          ; Calculate next real instruction
    push eax
    ret                  ; Another obfuscated jump
    
    ; Hidden code continues...
    mov eax, 1
    pop ebp
    ret

end start

