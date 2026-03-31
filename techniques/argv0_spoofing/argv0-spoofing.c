#include <unistd.h>

int main(void){
    return execl("/usr/bin/echo", "ARGV0", "Hello, world!", NULL);
}
