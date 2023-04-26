package main

import (
	"fmt"
	"golang.org/x/sys/windows/registry"
)

var (
	registryKey = `SYSTEM\CurrentControlSet\Control\Print\Printers`
)

func getPrintersName() {
	newKey, err := registry.OpenKey(registry.LOCAL_MACHINE, registryKey, registry.ENUMERATE_SUB_KEYS)
	if err != nil {
		fmt.Println("Error: ", err)
		panic(err)
	}

	subKeyNames, err := newKey.ReadSubKeyNames(-1)
	if err != nil {
		fmt.Println("Error: ", err)
		panic(err)
	}

	for i, subKeyName := range subKeyNames {
		fmt.Printf("[%d] %s \n", i, subKeyName)
	}
}

func getPrinterCount() {
	key, err := registry.OpenKey(registry.LOCAL_MACHINE, registryKey, registry.QUERY_VALUE)
	if err != nil {
		fmt.Println("Error = ", err)
		key.Close()
		panic(err)
	}
	defer key.Close()

	keyStat, err := key.Stat()
	if err != nil {
		fmt.Println("Error = ", err)
		panic(err)
	}
	fmt.Println("Subkey count = ", keyStat.SubKeyCount)
}

func main() {
	getPrinterCount()
	getPrintersName()
}
