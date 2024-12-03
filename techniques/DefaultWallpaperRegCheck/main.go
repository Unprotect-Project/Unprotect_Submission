package main
import (
	"golang.org/x/sys/windows/registry"
	"fmt"
)

func main() {
	k, err := registry.OpenKey(registry.CURRENT_USER, `CONTROL Panel\\Desktop`, registry.QUERY_VALUE)
	if err != nil {
		fmt.Println(err)
	}
	defer k.Close()

	s, _, err := k.GetStringValue("Wallpaper")
	if err != nil {
		fmt.Println(err)
	}

	if (s == "C:\\Windows\\web\\wallpaper\\Windows\\img0.jpg") {
		fmt.Println("[+] Default wallpaper detected! Possible sandbox/VM...")
	} else {
		fmt.Println("[+] Wallpaper isn't set to default. Continuing checks...")
	}
}
