#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <stdio.h>
#include <fcntl.h> 
#include <io.h>

#define MAX 50

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