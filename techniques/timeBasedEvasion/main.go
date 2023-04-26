package main

import (
	"time"
	"net"
	"encoding/binary"
	"net/http"
	"fmt"
	"math"
)

func isConnected() bool {
	_, err := http.Get("http://1.1.1.1")
	if err == nil {
		return true
	}
	return false
}

func getNtpTime() time.Time {
	type ntp struct {
		FirstByte, A, B, C uint8
		D, E, F            uint32
		G, H               uint64
		ReceiveTime        uint64
		J                  uint64
	}
	sock, _ := net.Dial("udp", "us.pool.ntp.org:123")
	sock.SetDeadline(time.Now().Add((2 * time.Second)))
	defer sock.Close()
	transmit := new(ntp)
	transmit.FirstByte = 0x1b
	binary.Write(sock, binary.BigEndian, transmit)
	binary.Read(sock, binary.BigEndian, transmit)
	return time.Date(1900, 1, 1, 0, 0, 0, 0, time.UTC).Add(time.Duration(((transmit.ReceiveTime >> 32) * 1000000000)))
}

func evadeTimeAcceleration() bool {
	var maxIdleTime int = 3

	if isConnected() {
		firstTime := getNtpTime()
		time.Sleep(time.Duration(maxIdleTime*1000) * time.Millisecond)
		secondTime := getNtpTime()

		if secondTime.Sub(firstTime).Seconds() > float64(maxIdleTime) {
			return true
		}
	} else {
		firstTime := time.Now()
		time.Sleep(time.Duration(maxIdleTime*1000) * time.Millisecond)

		// math.Floor is used to compensate for processor ticks that is a few micro-seconds
		if math.Floor(time.Since(firstTime).Seconds()) > float64(maxIdleTime) {
			return true
		}
	}
	return false
}

func main() () {
	if evadeTimeAcceleration() {
		fmt.Println("Sandbox detected")
	} else {
		fmt.Println("Sandbox not detected")
	}
}
