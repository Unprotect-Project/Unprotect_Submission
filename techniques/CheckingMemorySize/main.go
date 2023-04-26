package main

import (
	"unsafe"
	"syscall"
	"fmt"
)

var (
	kernel_32               = syscall.MustLoadDLL("kernel32.dll")
	globalMemoryStatusEx, _ = kernel_32.FindProc("GlobalMemoryStatusEx")
)

type memStatusEx struct {
	dwLength     uint32
	dwMemoryLoad uint32
	ullTotalPhys uint64
	unused       [6]uint64
}

func evadeSystemMemory() () {
	msx := &memStatusEx{dwLength: 64}
	r, _, _ := globalMemoryStatusEx.Call(uintptr(unsafe.Pointer(msx)))
	if r == 0 {
		fmt.Println("Error getting memory status")
	}

	var maxMemory float64 = 2.0
	var system_memory = float64(msx.ullTotalPhys/1024/1024) / 1024

	if system_memory <= maxMemory {
		fmt.Println("Sandbox detected")
	} else {
		fmt.Println("Sandbox not detected")
	}
}

func main() {
	evadeSystemMemory()
}
