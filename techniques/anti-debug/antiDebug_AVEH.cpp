#include <windows.h>
#include <exception>
#include <stdio.h>

bool CaughtVEHDebugger = false;

LONG CALLBACK TopLevelHandler(EXCEPTION_POINTERS* info)
{
    if (info->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) //Detects when a VEH debugger single-steps through code
        CaughtVEHDebugger = true;
   
    printf("Executed toplevelhandler, Exception: %X\n", info->ExceptionRecord->ExceptionCode);
    return EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
    AddVectoredExceptionHandler(1, TopLevelHandler);
  
    if(CaughtVEHDebugger) 
        printf("Caught VEH debugger: %s\n", ((CaughtVEHDebugger > 0) ? "true" : "false"));
    
    return 0; 
}
