package main

import (
	"runtime"
	"fmt"
)

func getCPUCount() int {
	return runtime.NumCPU()
}

func main() () {
	var cpuCount int = getCPUCount()
	// Change the max CPU count to evade the sandbox !
	var maxCPU int = 1

	if cpuCount <= maxCPU {
		fmt.Println("Sandbox detected")
	} else {
		fmt.Println("Sandbox not detected")
	}
}
