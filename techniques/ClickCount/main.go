package main

import (
	"fmt"
	"syscall"
	"time"
)

var (
	user32           = syscall.NewLazyDLL("user32.dll")
	getAsyncKeyState = user32.NewProc("GetAsyncKeyState")
)

func evadeClicksCount() {
	// Increment variable when a click is detected
	var clickCount int
	// Set the minimal number of clicks to be detected
	var minimalClickCount = 10
	// Set the maximum idle time in seconds
	var maxIdleTime = 120
	var t time.Time = time.Now()

	for clickCount <= minimalClickCount {
		leftClick, _, _ := getAsyncKeyState.Call(uintptr(0x1))
		rightClick, _, _ := getAsyncKeyState.Call(uintptr(0x2))
		// Check if a click is detected
		if leftClick%2 == 1 || rightClick%2 == 1 {
			clickCount += 1
			t = time.Now()
		}

		if int(time.Since(t).Seconds()) > maxIdleTime {
			fmt.Println("Sandbox Detected !")
		}
	}
	fmt.Println("Legitimate user detected !")
}

func main() {
	evadeClicksCount()
}
