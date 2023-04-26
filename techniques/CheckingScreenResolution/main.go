package main

import (
	"fmt"
	"syscall"
	"time"
)

var (
	user32               = syscall.NewLazyDLL("user32.dll")
	procGetSystemMetrics = user32.NewProc("GetSystemMetrics")
)

func getScreenResolution() {
	indexX := uintptr(0)
	indexY := uintptr(1)
	x, _, _ := procGetSystemMetrics.Call(indexX)
	y, _, _ := procGetSystemMetrics.Call(indexY)
	fmt.Println("X = ", x, " Y = ", y)
	// Modify the screen size as you want !
	if x < 1024 || y < 768 {
		fmt.Println("Sandbox Detected !")
	}
}

func main() {
	getScreenResolution()
	time.Sleep(time.Second * 10)
}
