package main

import (
	"fmt"
	"golang.org/x/sys/windows"
	"syscall"
	"unsafe"
)

var (
	user32 = windows.NewLazySystemDLL("user32.dll")
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtextw
	procGetWindowText = user32.NewProc("GetWindowTextW")
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtextlengthw
	procGetWindowTextL = user32.NewProc("GetWindowTextLengthW")
)

func getWindowTextLength(windowHandle windows.HWND) int {
	ret, _, _ := procGetWindowTextL.Call(uintptr(windowHandle))

	return int(ret)
}

func getWindowName(fg windows.HWND) string {
	// +1 to get the last character of the string
	var titleBarFullLen = int(getWindowTextLength(fg)) + 1

	buf := make([]uint16, titleBarFullLen)
	procGetWindowText.Call(
		uintptr(fg),
		uintptr(unsafe.Pointer(&buf[0])),
		uintptr(titleBarFullLen))

	return syscall.UTF16ToString(buf)
}

func main() {
	var foregroundWindowHandle windows.HWND = windows.GetForegroundWindow()
	var windowName string = getWindowName(foregroundWindowHandle)

	fmt.Println("Foreground window handle: ", foregroundWindowHandle)
	fmt.Println("Window name: ", windowName)
}
