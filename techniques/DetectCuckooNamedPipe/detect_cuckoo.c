#include <stdio.h>
#include <Windows.h>

int main() {
    const char *pipeName = "\\\\.\\pipe\\cuckoo";

    BOOL pipeExists = WaitNamedPipeA(pipeName, 10000);

    if (pipeExists) {
        printf("Cuckoo Sandbox detected via named pipe.\n");
        return 1;
    } else {
        printf("No Cuckoo pipe found. Proceeding..\n");
    }

    return 0;
}