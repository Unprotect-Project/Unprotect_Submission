#include <iostream>
#include <Windows.h>
#include <winnetwk.h>
#include <algorithm>
#include <string>

#pragma comment(lib, "Mpr.lib")

void EnumerateResources(LPNETRESOURCEW pRsrc, DWORD scope, DWORD type, DWORD usage) {
	HANDLE hEnum = NULL;
	DWORD result = WNetOpenEnumW(scope, type, usage, pRsrc, &hEnum);

	if (result != NO_ERROR) {
		std::cerr << "WNetOpenEnumW failed with error: " << result << std::endl;
		return;
	}

	BYTE buffer[65536];
	DWORD count;
	DWORD bufSize;

	do {
		count = (DWORD)-1;
		bufSize = sizeof(buffer);
		result = WNetEnumResourceW(hEnum, &count, buffer, &bufSize);

		if (result == NO_ERROR || result == ERROR_MORE_DATA) {
			// Results from WNetEnumResource are returned as an array of NETRESOURCE structures
			LPNETRESOURCEW pNR = (LPNETRESOURCEW)buffer;
			for (DWORD i = 0; i < count; i++) {
				std::wstring remoteName_upper;
				if (pNR[i].lpRemoteName) { // Convert RemoteName to uppercase
					remoteName_upper = pNR[i].lpRemoteName;
					std::transform(remoteName_upper.begin(), remoteName_upper.end(), remoteName_upper.begin(), ::towupper);
				}
				if (!remoteName_upper.empty() && (remoteName_upper.find(L"VIRTUALBOX") != std::wstring::npos || remoteName_upper.find(L"VBOXSVR") != std::wstring::npos)) {
					wprintf(L"Found VirtualBox environment! RemoteName: %ls, Provider: %ls\n", pNR[i].lpRemoteName, pNR[i].lpProvider);
				}
				else if (pNR[i].lpRemoteName) {
					wprintf(L"Net resource: %ls , %ls\n",
						pNR[i].lpRemoteName ? pNR[i].lpRemoteName : L"(null)",
						pNR[i].lpProvider ? pNR[i].lpProvider : L"(null)");
				}
				// If the resource has more children, enumerate them recursively
				if (pNR[i].dwUsage & RESOURCEUSAGE_CONTAINER) {
					EnumerateResources(&pNR[i], scope, type, usage);
				}
			}
		}
		else if (result != ERROR_NO_MORE_ITEMS) {
			std::cerr << "WNetEnumResourceW failed with error: " << result << std::endl;
			break;
		}
	} while (result == ERROR_MORE_DATA);

	WNetCloseEnum(hEnum);
}

int main() {
	EnumerateResources(nullptr, RESOURCE_GLOBALNET, RESOURCETYPE_DISK, 0);
	return 0;
}
