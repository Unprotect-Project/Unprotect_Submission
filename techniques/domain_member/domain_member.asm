; #########################################
; Compare the variable Computername & Logonserver
; if they are the same ( except the // ) you are 
; not logged to a domain controller

_isdomain:
   push ebp
   mov  ebp,esp
   push ebx

   jmp     runit

   len_computername dd 13
   ;str_computername db "COMPUTERNAME="
   ;str_computername db 78,66,64,93,88,89,72,95,67,76,64,72,48

   len_logonserver dd 14
   ;str_logonserver db "LOGONSERVER=\\"
   ;str_logonserver db 66,65,73,65,64,93,75,92,88,75,92,51,82,82

runit:
   call _getenvnoapi      ; Retrieve location of env and size
   push eax
   push  ecx

   ; Get computername
   invokel  _findstr, eax, ecx, str_computername + 1, dword [len_computername]
   mov   esi,eax
   pop   ecx
   pop   eax

   push  esi

   ; Get LogonSvr
   invokel  _findstr, eax, ecx, str_logonserver + 1, dword [len_logonserver]

   ; validate the loggon server..
   pop   esi
   mov   edi, eax
   mov   eax,0
   test  edi,edi        ; On linux (vine) .. no computername, avoid crash
   jz    _nodomain

   mov    eax,edi
   call  _strlenw
   mov   ecx,eax
   rep   cmpsb
   mov   eax,0
   CMP   ecx,0
   jz   _nodomain  ; if the computer is equal to the domain then .. no domain

   inc   eax  ; Eax = 1 ... domain logged
_nodomain:

      pop   ebx
      mov   esp,ebp
      pop   ebp
      ret


; #########################################
_getenvnoapi:
   ; Retrieve the memory offset of the environnement variables apiless.
   ; Out: Eax offset buffer
   ; Out: Ecx len buffer
   mov   eax, [fs:0x30]    ; Get PEB
   mov   eax, [eax + 0x10] ; Get ProcessParameters
   mov   esi, [eax + 0x48] ; Get Environment
   mov   edx,esi
.scan_end:
   lodsd          ; Scan for next 0x0 X 4
   cmp   eax,0
   jne   .scan_end
   sub   esi, edx
   mov   ecx,esi
   mov   eax,edx
   ret



; #########################################
_findstr:
; Find a string
;  Return 0 in eax if not found
;  In stack [ebp+0x08] : Offset Buffer
;  In stack [ebp+0x0c] : Size Buffer
;  In stack [ebp+0x10] : Offset Pattern
;  In stack [ebp+0x14] : Size Pattern
;  Out eax   : Offset of string END
;  Warning max 256 bytes... NO CHECK !

   push ebp
   mov  ebp,esp
   sub  esp, 512
   mov     esi, dword [ebp + 0x10]   ; Convert Ascii to Unicode
   lea     edi, [ebp- 512]           ; Env is in unicode in memory
   mov     dword [ebp + 0x10], edi
   mov     ecx, [ebp+0x14]
   mov   edx,ecx

strtouni:
    lodsb
    xor al, [xor_key]
    stosb
    xor eax,eax
    stosb
    loop    strtouni
    shl     dword [ebp+0x14], 1     ; Update size * 2

    mov     edx,dword [ebp+0x0c]    ; Len of Buffer to Seek
    sub     edx,dword [ebp+0x14]    ; Len of string to Seek
    std
iter:
    mov     esi, [ebp+0x08]             ; Buffer to Seek
    add     esi, edx                    ; Got to end - N
    mov     edi, [ebp+0x10]             ; Buffer to pattern
    mov     ecx, dword [ebp+0x14]       ; Size to compare

    dec ecx
    add     esi, ecx                    ; Got to buffer + Size
    add     edi, ecx                    ; Got to pattern + Size
    inc ecx

    repe    cmpsb                      ; compare string...
    jcxz    found                      ; If compare the same number we wins

    sub     edx,2
                                        ; N = N - 1 ( x2 Since unicode )
                                        ; could be optimised for unicode... but....
    jnz     iter                        ; Until N = 0

    mov     eax,0
    jmp     findstr_end


found:
   add esi,1                           ; Pad x2 unicode...
   add esi, dword [ebp+0x14]           ; Go to "after" the found string
   mov eax,esi

findstr_end:
   cld
   mov esp,ebp
   pop ebp
   retn 16 


; #########################################
; Get string len wide
; eax, string, return eax, len

_strlenw:        ; eax: a string ending in 0
   push ebx
   push eax      ; cache eax

  .strloopw:
    mov bx, word [eax]
    cmp bx, 0
    je .strretw      ; return len if bl == 0
    inc eax ; inc eax        ; else eax++

    jmp .strloopw

.strretw:
    pop ebx        ; ebx = cached eax
    sub eax, ebx    ; eax -= ebx
    pop ebx
    inc eax
    ret          ; eax = len


_getenvnoapi:
   ; Out: Eax offset buffer
   ; Out: Ecx len buffer
   mov   eax, [fs:0x30]    ; Get PEB
   mov   eax, [eax + 0x10] ; Get ProcessParameters
   mov   esi, [eax + 0x48] ; Get Environment
   mov   edx,esi
.scan_end:
   lodsd          ; Scan for next 0x0 X 4
   cmp   eax,0
   jne   .scan_end
   sub   esi, edx
   mov   ecx,esi
   mov   eax,edx
   ret
