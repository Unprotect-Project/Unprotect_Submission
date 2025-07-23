#include <stdio.h>
#include <Windows.h>
#include <intrin.h>

#define PF_FASTFAIL_AVAILABLE					0x17
#define FAST_FAIL_STACK_COOKIE_CHECK_FAILURE	0x2 // Any other error should be okay

int main() {
    if (IsProcessorFeaturePresent(PF_FASTFAIL_AVAILABLE)) {
		printf("Calling __fastfail(): Windows 8+ system detected.\n");
		__fastfail(FAST_FAIL_STACK_COOKIE_CHECK_FAILURE);
        // Stop with exception Fail Fast code C0000409
	}
	printf("__fastfail() not called: running in Windows 7 or previous.\n");
	
	return 0;
}