#include "Windows.h"
#include <iostream>
#include "intrin.h"
using namespace std;



bool IsOnlyInstance(LPCTSTR gameTitle) {
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS) {
		return false;
	}
	return true;
}


void CheckMemory() {
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);

	cout << "you have " << status.ullTotalPhys << " RAM." << endl;

	cout << "You Have " << status.ullAvailVirtual << " virtual memory." << endl;

}

DWORD ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)
			&dwMHz, &BufSize);
	}


	return dwMHz;
}

void GetProcessorName()
{
	int CPUInfo[4] = { -1 };
	char CPUBrandString[0x40];
	__cpuid(CPUInfo, 0x80000000);
	unsigned int nExIds = CPUInfo[0];

	memset(CPUBrandString, 0, sizeof(CPUBrandString));

	// Get the information associated with each extended ID.
	for (int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string.
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	cout << CPUBrandString << endl;
}

int main() {
	__int64 lpFreeBytesAvailable = 0;
	__int64 lpTotalNumberOfBytes = 0;
	__int64 lpTotalNumberOfFreeBytes = 0;

	bool Onlyone = IsOnlyInstance("OperationMintyHippo");

	if (!Onlyone)
	{
		cout << "Your Program is already running." << endl;
	}

	int space = GetDiskFreeSpaceEx(NULL, (PULARGE_INTEGER)&lpFreeBytesAvailable, (PULARGE_INTEGER)&lpTotalNumberOfBytes, (PULARGE_INTEGER)&lpTotalNumberOfBytes);
	cout << "You have " << (lpFreeBytesAvailable / 1024) << " space." << endl;

	if ((lpFreeBytesAvailable / 1024) < 300)
	{
		cout << "You do not have the space for this program." << endl;
	}

	CheckMemory();
    ReadCPUSpeed();
	GetProcessorName();
	system("pause");
}