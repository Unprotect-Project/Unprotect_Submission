#include <windows.h>
#include <stdio.h>

void main() {
    HWND winHandle = GetConsoleWindow();
    ShowWindow(winHandle, SW_HIDE);
}
