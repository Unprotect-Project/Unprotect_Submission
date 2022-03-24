Sha256 : **a41ba65405a032f4450ba80882cdd01d715d9d1684f4204050566be29a6dedb0**

VT : **https://www.virustotal.com/gui/file/a41ba65405a032f4450ba80882cdd01d715d9d1684f4204050566be29a6dedb0**

The malicious sample listed above abused variant bytes of **__IsNonwritableInCurrentImage** signature to add two instructions consisting of an anti-debugging technique referenced as **U0114** on **unprotect.it**

Malicious code :

```
.text:00A4264A                 push    0DEADBEEFh
.text:00A4264F                 call    kernel32_CloseHandle
```

Full abused function tagged as __IsNonwritableInCurrentImage.

```
text:00A42610 __IsNonwritableInCurrentImage proc near ; CODE XREF: sub_A428D0:loc_A429E2↓p
.text:00A42610
.text:00A42610 ms_exc          = CPPEH_RECORD ptr -18h
.text:00A42610
.text:00A42610 ; __unwind { // __except_handler4
.text:00A42610                 push    ebp
.text:00A42611                 mov     ebp, esp
.text:00A42613                 push    0FFFFFFFEh
.text:00A42615                 push    offset stru_A5AE98
.text:00A4261A                 push    offset __except_handler4
.text:00A4261F                 mov     eax, large fs:0
.text:00A42625                 push    eax
.text:00A42626                 sub     esp, 8
.text:00A42629                 push    ebx
.text:00A4262A                 push    esi
.text:00A4262B                 push    edi
.text:00A4262C                 mov     eax, ___security_cookie
.text:00A42631                 xor     [ebp+ms_exc.registration.ScopeTable], eax
.text:00A42634                 xor     eax, ebp
.text:00A42636                 push    eax
.text:00A42637                 lea     eax, [ebp+ms_exc.registration]
.text:00A4263A                 mov     large fs:0, eax
.text:00A42640                 mov     [ebp+ms_exc.old_esp], esp
.text:00A42643 ;   __try { // __except at loc_A42676
.text:00A42643                 mov     [ebp+ms_exc.registration.TryLevel], 0
.text:00A4264A                 push    0DEADBEEFh
.text:00A4264F                 call    kernel32_CloseHandle
.text:00A4264F ;   } // starts at A42643
.text:00A42655                 mov     [ebp+ms_exc.registration.TryLevel], 0FFFFFFFEh
.text:00A4265C                 xor     eax, eax
.text:00A4265E                 mov     ecx, [ebp+ms_exc.registration.Next]
.text:00A42661                 mov     large fs:0, ecx
.text:00A42668                 pop     ecx
.text:00A42669                 pop     edi
.text:00A4266A                 pop     esi
.text:00A4266B                 pop     ebx
.text:00A4266C                 mov     esp, ebp
.text:00A4266E                 pop     ebp
.text:00A4266F                 retn
.text:00A42670 ; ---------------------------------------------------------------------------
.text:00A42670
.text:00A42670 loc_A42670:                             ; DATA XREF: .rdata:stru_A5AE98↓o
.text:00A42670 ;   __except filter // owned by A42643
.text:00A42670                 mov     eax, 1
.text:00A42675                 retn
.text:00A42676 ; ---------------------------------------------------------------------------
.text:00A42676
.text:00A42676 loc_A42676:                             ; DATA XREF: .rdata:stru_A5AE98↓o
.text:00A42676 ;   __except(loc_A42670) // owned by A42643
.text:00A42676                 mov     esp, [ebp+ms_exc.old_esp]
.text:00A42679                 mov     [ebp+ms_exc.registration.TryLevel], 0FFFFFFFEh
.text:00A42680                 mov     eax, 2000h
.text:00A42685                 mov     ecx, [ebp+ms_exc.registration.Next]
.text:00A42688                 mov     large fs:0, ecx
.text:00A4268F                 pop     ecx
.text:00A42690                 pop     edi
.text:00A42691                 pop     esi
.text:00A42692                 pop     ebx
.text:00A42693                 mov     esp, ebp
.text:00A42695                 pop     ebp
.text:00A42696                 retn
.text:00A42696 ; } // starts at A42610
.text:00A42696 __IsNonwritableInCurrentImage endp
.text:00A42696
```