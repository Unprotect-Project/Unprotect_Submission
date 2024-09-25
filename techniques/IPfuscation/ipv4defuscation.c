#include <Windows.h>
#include <stdio.h>
#include <ip2string.h>

#pragma comment(lib, "ntdll.lib")

void Ipv4Deobfuscate(CHAR* Ipv4Array[], int Ipv4ArrayLength) {
	PCSTR Terminator = NULL;
	PBYTE pointer = NULL, addressToWrite = NULL;
	pointer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, Ipv4ArrayLength*4);
	addressToWrite = pointer;
	printf("Allocated on heap at : 0x%p", pointer);
	for (int i = 0; i < Ipv4ArrayLength; i++){
		RtlIpv4StringToAddressA(Ipv4Array[i], FALSE, &Terminator, addressToWrite);
		addressToWrite = (PBYTE)(addressToWrite + 4);
	}
	getchar(); // Pause so you can inspect the heap
}


int main() {
	char * payload[13] = {
		"72.101.108.108","111.32.85.110","112.114.111.116","101.99.116.80","114.111.106.101","99.116.44.32","116.104.105.115",
		"32.105.115.32","73.80.118.52","32.111.98.102","117.115.99.97","116.105.111.110","32.58.41.0"
	};

	Ipv4Deobfuscate(payload, 13);

	return 0;
}