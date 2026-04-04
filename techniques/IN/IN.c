#include <stdio.h>
#include <stdint.h>
#include <excpt.h>  

int isRunningInVMware(void)
{
    uint32_t ebx_magic = 0;

    __try {
        __asm {
            pushad                       

            mov eax, 564D5868h          
            mov ecx, 0Ah                
            mov dx,  5658h              
            in  eax, dx                 

            mov ebx_magic, ebx          

            popad                        
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return 0;                        
    }

    return (ebx_magic == 0x564D5868);    
}

int main(void)
{
    if (isRunningInVMware()) {
        printf("Running in VMware!\n");
    } else {
        printf("Not running in VMware.\n");
    }

    return 0;
}
