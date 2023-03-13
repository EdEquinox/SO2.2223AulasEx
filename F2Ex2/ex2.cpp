#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define SIZE 256

int _tmain(int argc, TCHAR* argv[]) {

	HKEY key;
	TCHAR path[SIZE], keyName[SIZE], namedValue_name[SIZE], namedValue_value[SIZE];
	DWORD result, option = 0;
	DWORD namedValue_name_size = (DWORD)SIZE, namedValue_value_size = (DWORD)SIZE;
	LSTATUS status;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	_tprintf(TEXT("Enter the name of the key: "));
	_tscanf_s(TEXT("%3s"), keyName, SIZE);
	fflush(stdin);

	_tcscpy_s(path, SIZE, TEXT("SOFTWARE\\SO2\\"));
	_tcscat_s(path, SIZE, keyName);
	_tprintf(TEXT("Key [ %s ]\n\n"), path);

	status = RegCreateKeyEx(
		HKEY_CURRENT_USER,
		path,
		0,
		NULL,
		REG_OPTION_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&key,
		&result);

	if (status != ERROR_SUCCESS) {
		_tprintf_s(TEXT("Error creating/opening the key. (%d)"), GetLastError());
		exit(-1);
	}

	else {
		if (result == REG_CREATED_NEW_KEY)
			_tprintf_s(TEXT("The key didn't exist. A new key was created successfully.\nPath: %s\n"), path);
		else if (result == REG_OPENED_EXISTING_KEY)
			_tprintf_s(TEXT("The key already existed. The key was opened successfully.\nPath: %s\n"), path);
	}

	do {
		_tprintf_s(TEXT("\n\n Menu:\n[1]: Create Named-Value.\n[2]: See Named-Value.\n[3]: Delete Named-Value.\n[4]: See all Named-Values.\n[5]: Exit.\n"));
		_tprintf_s(TEXT("Option: "));
		_tscanf_s(TEXT("%d"), &option);
		fflush(stdin);

		switch (option) {
		case 1: {
			_tprintf_s(TEXT("\nEnter the name of the Named-Value: "));
			_tscanf_s(TEXT("%s"), namedValue_name, SIZE);
			fflush(stdin);

			_tprintf_s(TEXT("\nEnter the value of the Named-Value: "));
			_tscanf_s(TEXT("%s"), namedValue_value, SIZE);
			fflush(stdin);

			status = RegSetValueEx(
				key,
				namedValue_name,
				0,
				REG_SZ,
				(LPBYTE)namedValue_value,
				(DWORD)(_tcslen(namedValue_value) + 1) * sizeof(TCHAR));

			if (status != ERROR_SUCCESS)
				_tprintf_s(TEXT("Error creating the Named-Value. (%d)"), GetLastError());
			break;
		}
		case 2: {
			_tprintf_s(TEXT("\nEnter the name of the Named-Value to search: "));
			_tscanf_s(TEXT("%s"), namedValue_name, SIZE);
			fflush(stdin);

			status = RegQueryValueEx(
				key,
				namedValue_name,
				NULL,
				NULL,
				(LPBYTE)namedValue_value,
				&namedValue_value_size);

			if (status != ERROR_SUCCESS)
				_tprintf_s(TEXT("Error reading the Named-Value. (%d)"), GetLastError());
			else {
				_tprintf_s(TEXT("\nNamed-Value:\nName: [%s]   Value: [%s]\n"), namedValue_name, namedValue_value);
			}

			break;
		}
		case 3: {
			_tprintf_s(TEXT("\nEnter the name of the Named-Value to delete: "));
			_tscanf_s(TEXT("%s"), namedValue_name, SIZE);
			fflush(stdin);
			status = RegDeleteValue(key, namedValue_name);
			if (status != ERROR_SUCCESS)
				_tprintf_s(TEXT("Error deleting the Named-Value. (%d)"), GetLastError());
			break;
		}
		case 4: {
			_tprintf_s(TEXT("\nAll Named-Values of the current key:\n\n"));
			DWORD i = 0;
			while ((status = RegEnumValue(
				key,
				i++,
				namedValue_name,
				&namedValue_name_size,
				NULL,
				NULL,
				(LPBYTE)namedValue_value,
				&namedValue_value_size)) != ERROR_NO_MORE_ITEMS) {
				if (status != ERROR_SUCCESS)
					_tprintf_s(TEXT("Error deleting the Named-Value. (%d)"), GetLastError());
				_tprintf_s(TEXT("Named-Value:\nName: [%s]   Value: [%s]\n\n"), namedValue_name, namedValue_value);
				namedValue_name_size = (DWORD)SIZE;
				namedValue_value_size = (DWORD)SIZE;
			}
			break;
		}
		case 5: break;

		default: {
			_tprintf(TEXT("\nInvalid option.\n"));
			break;
		}
		}
	} while (option != 5);

	RegCloseKey(key);

	return 0;
}
