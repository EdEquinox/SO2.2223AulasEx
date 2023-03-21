#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>

using namespace std;
#ifdef UNICODE
#define tcout wcout
#define tcin wcin
#define tstring wstring
#else
#define tcout cout
#define tcin cin
#define tstring string
#endif

bool isPrime(int n)
{
	int i;

	for (i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}

	return true;
}

DWORD WINAPI sumPri(LPVOID param) {
	int* sum = (int*) param;
	int count = 0;
	for (int i = 0; i <= 1000; i++) {
		if (isPrime(i)) {
			*sum = *sum + i;
			count++;
			if (count % 200 == 0)
			{
				Sleep(1000);
			}
		}
	}
	return 0;
}

DWORD WINAPI sumPar(LPVOID param) {
	int* sum = (int*) param;
	int count = 0;
	for (int i = 0; i <= 1000; i++) {
		if (i%2 == 0) {
			*sum = *sum + i;
			count++;
			if (count % 15 == 0)
			{
				Sleep(1000);
			}
		}
	}
	return 0;
}


int _tmain(int argc, TCHAR* argv[]){

	HANDLE hThreadArray[2];
	int sumPares = 0;
	int sumPrimos = 0;
	DWORD ret = 0;

	#ifdef UNICODE
		_setmode(_fileno(stdin), _O_WTEXT);
		_setmode(_fileno(stdout), _O_WTEXT);
		_setmode(_fileno(stderr), _O_WTEXT);
	#endif

	hThreadArray[0] = CreateThread(NULL, 0, sumPri, &sumPrimos, 0, NULL);
	hThreadArray[1] = CreateThread(NULL, 0, sumPar, &sumPares, 0, NULL);

	HANDLE handle = hThreadArray[0];
	int count = 0;
	while (count < 2)
	{
		ret = WaitForMultipleObjects(2 - count, hThreadArray, FALSE, 2000);
		if (ret == WAIT_TIMEOUT)
		{
			_tprintf(TEXT("Still waiting..."));
		}
		else
		{
			int index = ret - WAIT_OBJECT_0;
			CloseHandle(hThreadArray[index]);
			if (hThreadArray[index] == handle)
			{
				_tprintf(TEXT("O resultado dos primos é: %d\n"), sumPrimos);
				hThreadArray[0] = hThreadArray[1];

			}
			else
			{
				_tprintf(TEXT("O resultado dos pares é: %d\n"), sumPares);

			}
			count++;

		}
	}

	//WaitForSingleObject(hThreadArray[0], INFINITE);
	//WaitForSingleObject(hThreadArray[1], INFINITE);

}