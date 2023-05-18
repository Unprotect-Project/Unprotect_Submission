#include <Windows.h>
#include <iostream>
#include <io.h>

// win api
const bool IsDirectory2(std::string& strDirName) {
	const auto iCode = CreateDirectoryA(strDirName.c_str(), NULL);
	if (ERROR_ALREADY_EXISTS == GetLastError())
		return true;
	if (iCode)
		RemoveDirectoryA(strDirName.c_str());
	return false;
}

// win api
const bool IsDirectory1(std::string& strDirName) {
	const HANDLE hFile = CreateFileA(
		strDirName.c_str(),
		GENERIC_READ,                   
		0,                              
		NULL,
		OPEN_EXISTING,                  
		FILE_FLAG_BACKUP_SEMANTICS,     
		NULL);
	if (!hFile || (INVALID_HANDLE_VALUE == hFile))
		return false;
	if(hFile)
		CloseHandle(hFile);
	return true;
}

// crt
const bool IsDirectory(std::string& strDirName) {
	if (0 == _access(strDirName.c_str(), 0))
		return true;
	return false;
}

int main()
{
	std::string strDirName = "C:\\Cuckoo";
	if (IsDirectory(strDirName)) {
		std::cout << "Ture: " << strDirName.c_str() << std::endl;
	}
	else {
		std::cout << "Flase: " << strDirName.c_str() << std::endl;
	}

	if (IsDirectory1(strDirName)) {
		std::cout << "Ture: " << strDirName.c_str() << std::endl;
	}
	else {
		std::cout << "Flase: " << strDirName.c_str() << std::endl;
	}

	if (IsDirectory2(strDirName)) {
		std::cout << "Ture: " << strDirName.c_str() << std::endl;
	}
	else {
		std::cout << "Flase: " << strDirName.c_str() << std::endl;
	}


	return 0;
}