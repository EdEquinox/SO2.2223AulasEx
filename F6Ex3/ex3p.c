#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <stdio.h>
#include <fcntl.h> 
#include <io.h>

#define SHM_NAME TEXT("SHM_PC")
#define MUTEX_WRITE_NAME TEXT("MUTEX_WRITE")
#define MUTEX_READ_NAME TEXT("MUTEX_READ")
#define SEM_WRITE_NAME TEXT("SEM_WRITE")
#define SEM_READ_NAME TEXT("SEM_READ")
#define SIZE_BUFF 10

typedef struct _BufferCell {
	unsigned int id;
	unsigned int val;
} BufferCell;

typedef struct _SharedMem {
	unsigned int idProd;
	unsigned int idCons;
	unsigned int writePos;
	unsigned int readPos;
	BufferCell buffer[SIZE_BUFF];
} SharedMem;

int _tmain(int argc, TCHAR* argv[]) {

	TCHAR message[50];
	HANDLE hFileMapping;
	SharedMem* pBuff;
	HANDLE sMem;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif 

	hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,  sizeof(SharedMem), SHM_NAME);
	if (hFileMapping == NULL)
	{
		_tprintf_s(TEXT("Error: CreateFileMapping (%d)"), GetLastError());
		CloseHandle(hFileMapping);
		return 1;
	}
	pBuff = (SharedMem*)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, sizeof(SharedMem));
	if (pBuff == NULL)
	{
		_tprintf_s(TEXT("Error: MapViewOfFile (%d)"), GetLastError());
		CloseHandle(hFileMapping);
		return 1;
	}

	pBuff->idProd = pBuff->idProd+1;
	while (_fgetts(message, 50, stdin)!="fim")
	{
		pBuff->buffer->val = 20;

	}





	TCHAR message[2];
	DWORD num;

	_tprintf(TEXT("\nMensagem -> "));
	_fgetts(message, 2, stdin);
	_tprintf(message);
	_tprintf(TEXT("\Numero -> "));
	wscanf_s(TEXT("%u"), &num);
	_tprintf(TEXT("%u\n"), num);

	return 0;
}