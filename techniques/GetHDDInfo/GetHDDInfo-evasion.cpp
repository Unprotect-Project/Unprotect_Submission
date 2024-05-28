#include "Header.h"


int main(int argc, char *argv[])
{
	char driveName[MAX_PATH];
	sprintf(driveName, "\\\\.\\PhysicalDrive%d", DRIVE);

	// Get handle of the physical drive
	HANDLE hDrive = CreateFileA(driveName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	// Check the validity of the file handle
	if (hDrive == INVALID_HANDLE_VALUE)
	{
		ErrorPrint(L"CreateFile");
		exit(1);
	}
	
	// Prepare the command buffer
	ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
	PSENDCMDINPARAMS Command = (PSENDCMDINPARAMS)malloc(CommandSize);
	// Prepare the command
	Command->irDriveRegs.bCommandReg = ID_CMD;

	DWORD bytesReturned = 0;
	// Retrieve IDENTIFY data
	if (DeviceIoControl(hDrive,
		SMART_RCV_DRIVE_DATA, // 0x7C088
		Command,
		sizeof(SENDCMDINPARAMS),
		Command,
		CommandSize,
		&bytesReturned,
		NULL))
	{
		// Print the IDENTIFY data
		DWORD diskData[256]; // 256 is the IDENTIFY_DATA structure's size
		USHORT *punIdSector = (USHORT *)(PIDENTIFY_DATA)((PSENDCMDOUTPARAMS)Command)->bBuffer;
		for (int i = 0; i < 256; i++)
			diskData[i] = punIdSector[i];

		PrintDriveInfo(0, diskData);
	}
	else ErrorPrint(L"DeviceIoControl (SMART_RCV_DRIVE_DATA)");

	CloseHandle(hDrive);
}

void PrintDriveInfo(int iDrive, DWORD diskData[256])
{
	char serialNumber[1024];
	char modelNumber[1024];
	char revisionNumber[1024];

	// Copy the hard drive serial, model, and revision number to respective buffer
	ConvertToString(diskData, 10, 19, serialNumber);
	ConvertToString(diskData, 27, 46, modelNumber);
	ConvertToString(diskData, 23, 26, revisionNumber);

	std::cout << "------------------------ [Drive " << DRIVE << "] ------------------------" << std::endl;
	std::cout << std::left << std::setw(35) << "Drive Serial Number________________ : [" << serialNumber << "]\n";
	std::cout << std::left << std::setw(35) << "Drive Model Number_________________ : [" << modelNumber << "]\n";
	std::cout << std::left << std::setw(35) << "Drive Controller Revision Number___ : [" << revisionNumber << "]\n";
	
	std::cout << "Drive Type_________________________ : [";
	if (diskData[0] & 0x0080)
		std::cout << "Removable]\n";
	else if (diskData[0] & 0x0040)
		std::cout << "Fixed]\n";
	else
		std::cout << "Unknown]\n";
}

char *ConvertToString(DWORD diskData[256], int iFirstIndex, int iLastIndex, char *pcszBuf)
{
	int index = 0;
	int position = 0;

	// NOTE: each integer has two characters stored in it backwards
	for (index = iFirstIndex; index <= iLastIndex; index++)
	{
		// Get high byte for 1st character
		pcszBuf[position++] = (char)(diskData[index] / 256); // / 256 = >> 8
		// Get low byte for 2nd character
		pcszBuf[position++] = (char)(diskData[index] % 256); // ^ 256 = & 0xFF
	}

	// End the string and cut off trailing blanks
	pcszBuf[position] = '\0';
	for (index = position - 1; index > 0 && isspace(pcszBuf[index]); index--)
		pcszBuf[index] = '\0';

	return pcszBuf;
}