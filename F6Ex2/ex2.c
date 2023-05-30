#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <stdio.h>
#include <fcntl.h> 
#include <io.h>

#define NCHARS 100

int _tmain(int argc, TCHAR* argv[]) {

	TCHAR message[NCHARS];
	TCHAR name = TEXT("Message");
	HANDLE hFileMapping;
	TCHAR* pBuff;
	HANDLE hEvent;
	HANDLE hThread;

	hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, NCHARS * sizeof(TCHAR), name);
	if (hFileMapping == NULL)
	{
		_tprintf_s(TEXT("Error: CreateFileMapping (%d)"), GetLastError());
		CloseHandle(hFileMapping);
		return 1;
	}
	pBuff = (TCHAR*)MapViewOfFile(message, FILE_MAP_WRITE, 0, 0, 0);
	if (pBuff == NULL)
	{
		_tprintf_s(TEXT("Error: MapViewOfFile (%d)"), GetLastError());
		CloseHandle(hFileMapping);
		return 1;
	}

	hEvent = CreateEvent(NULL, TRUE, FALSE, name);

	hThread = CreateThread();

	do {

		_tprintf_s(TEXT("Message: "));
		_fgetts(message, NCHARS, stdin);
		message[NCHARS - 1] = '\0';
		if (_tcscmp(_tolower(message), TEXT("sair")))
			break;
		pBuff = message;
		SetEvent(hEvent);
		Sleep(500);
		SetEvent(hEvent);

	} while (_tcscmp(_tolower(message), TEXT("sair")));

	CloseHandle(hFileMapping);
	CloseHandle(hEvent);

	return 0;
}