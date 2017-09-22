#include "Windows.h"
#include <iostream>
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
	system("pause");
}