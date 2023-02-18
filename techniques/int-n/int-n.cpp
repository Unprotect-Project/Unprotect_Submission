#include <stdio.h>
#include <windows.h>

bool TestDebugger() 
{
    __try
    {
        __asm  //x86 implementation
        {
            _emit 0xCD 
            _emit 0x03 //INT 03
            _emit 0xC3 //RET
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }

    return true;
}

int main()
{
    if(TestDebugger())
    {
        printf("Found debugger!\n");
    }
}