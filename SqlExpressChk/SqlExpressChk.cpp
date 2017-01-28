// SqlExpressChk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Version.h"

wchar_t* SQL_ROOT = L"Software\\Microsoft\\Microsoft SQL Server";
wchar_t* INSTANCES = L"Instance Names\\SQL";
wchar_t* SQLEXPRESS = L"SQLEXPRESS";
wchar_t* PATH_TO_VERSION = L"MSSQLServer\\CurrentVersion";
wchar_t* PARAM_CurrentVersion = L"CurrentVersion";

bool ReadRegistryString(HKEY hkeyroot, wchar_t* location, wchar_t* keyname, wchar_t* keyvalue, int keyvalue_length);

int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t *value = (wchar_t*)malloc(256 * sizeof(wchar_t));
	wchar_t *buffer = (wchar_t*)malloc(256 * sizeof(wchar_t));

	wsprintf(buffer, L"%s\\%s\\%s", SQL_ROOT, SQLEXPRESS, PATH_TO_VERSION);
	if (!ReadRegistryString(HKEY_LOCAL_MACHINE, buffer, PARAM_CurrentVersion, value, 100))
		return 1;

	if (Version(argv[1]) > Version(value))
		return 2;

	return 0;
}

bool ReadRegistryString(HKEY hkeyroot, wchar_t* location, wchar_t* keyname, wchar_t* keyvalue, int keyvalue_length)
{
	int result;
	HKEY hkey;
	LONG regopen = RegOpenKeyEx(hkeyroot, location, 0, KEY_READ, &hkey);
	if (ERROR_SUCCESS != regopen) {
		swprintf_s(keyvalue, keyvalue_length, L"");
		return false;
	}
	wchar_t* buffer = new wchar_t[keyvalue_length];
	DWORD buffersize = keyvalue_length * sizeof(wchar_t);
	DWORD type;
	LONG regquery = RegQueryValueEx(hkey, keyname, 0, &type, (LPBYTE) buffer, &buffersize);
	if (ERROR_SUCCESS != regquery) {
		RegCloseKey(hkey);
		swprintf_s(keyvalue, keyvalue_length, L"");
		return false;
	}
	if (type != REG_SZ) {
		RegCloseKey(hkey);
		swprintf_s(keyvalue, keyvalue_length, L"");
		return false;
	}
	result = swprintf_s(keyvalue, keyvalue_length, L"%s", buffer);
	delete[] buffer;
	buffer = 0;
	RegCloseKey(hkey);
	return true;
}

