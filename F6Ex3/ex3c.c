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

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif 

	TCHAR message[MAX];
	DWORD num;

	_tprintf(TEXT("\nMensagem -> "));
	_fgetts(message, MAX, stdin);
	_tprintf(message);
	_tprintf(TEXT("\Numero -> "));
	wscanf_s(TEXT("%u"), &num);
	_tprintf(TEXT("%u\n"), num);

	return 0;

}