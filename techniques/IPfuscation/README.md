# *IPFuscation*

## Authorship information
* Name or nickname (required): *4rkt0uR0s*
* Email: *4rkt0uR0s@proton.me*
  
## Technique Information
* Technique title (required): IPV4/IPV6 Obfuscation
* Technique category (required): Data Obfuscation
* Technique description (required):  The obfuscated payload masquerades itself as an array of ASCII IPv4 addresses. Each one of these IPs is passed to the `RtlIpv4StringToAddressA` function, which will translate the ASCII IP string to binary. The binary representation of all of these IPs is combined to form a blob of shellcode. Additionally, IPfuscation variants were spotted using IPv6 instead of IPv4 addresses, UUIDs, and MAC addresses, all operating in almost the same way.

## Additional resources
* https://www.sentinelone.com/blog/hive-ransomware-deploys-novel-ipfuscation-technique/
* https://www.bleepingcomputer.com/news/security/hive-ransomware-uses-new-ipfuscation-trick-to-hide-payload/
* https://cyware.com/news/ipfuscation-is-hives-new-technique-to-evade-detection-96c3c748

## Code snippets
To generate an obfuscated payload from a shellcode, you must first run the python script which will return the obfuscated payload as a list of IPs
```bash
$ python3 ipv4fuscation.py
char * payload[13] = { 
	"72.101.108.108","111.32.85.110","112.114.111.116","101.99.116.80","114.111.106.101","99.116.44.32","116.104.105.115",
	"32.105.115.32","73.80.118.52","32.111.98.102","117.115.99.97","116.105.111.110","32.58.41.0"
};
```

Then, you can deobfuscate it at runtime in the heap, as in `ipv4defuscation.c`

```c
void Ipv4Deobfuscate(CHAR* Ipv4Array[], int Ipv4ArrayLength) {
	PCSTR Terminator = NULL;
	PBYTE pointer = NULL, tmp = NULL;
	pointer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, Ipv4ArrayLength*4);
	addressToWrite = pointer;
	printf("Allocated on heap at : 0x%p", pointer);
	for (int i = 0; i < Ipv4ArrayLength; i++){
		RtlIpv4StringToAddressA(Ipv4Array[i], FALSE, &Terminator, addressToWrite);
		addressToWrite = (PBYTE)(addressToWrite + 4);
	}
	getchar(); // Pause so you can inspect the heap
}
```