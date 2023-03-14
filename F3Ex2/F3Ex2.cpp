// F3Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
typedef double (*applyFactorFunc)(double);
int _tmain(int argc, TCHAR* argv[])
{
	HMODULE hLib;
	double* varAdd;
	applyFactorFunc procAdd;
	double val;
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	hLib = LoadLibrary(TEXT("C:\\Users\\ZeMar\\Downloads\\SO2 - 2023 - Ficha 3 - DLL\\SO2 - 2023 - Ficha 3 - DLL\\x64\\SO2_F3_DLL.dll"));

	if (hLib!=NULL)
	{
		varAdd = (double*)GetProcAddress(hLib, "factor");
		procAdd = (applyFactorFunc)GetProcAddress(hLib, "applyFactor");

		if (varAdd!=NULL && procAdd!=NULL)
		{
			do
			{
				tcout << "\nEnter the factor: " << endl;
				tcin >> *varAdd;

				tcout << "\nEnter the value: " << endl;
				tcin >> val;

				tcout << *varAdd << " x " << val << " = " << procAdd(val);

			} while (*varAdd!=-1);
		}

		FreeLibrary(hLib);

	}

	return 0;
}
