// F3Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
#include "SO2_F3_DLL.h"

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

int _tmain(int argc, TCHAR* argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	double val;

	do
	{
		tcout << "\nEnter the factor: " << endl;
		tcin >> factor;

		tcout << "\nEnter the value: " << endl;
		tcin >> val;

		tcout << factor << " x " << val << " = " << applyFactor(val);

	} while (factor != -1);
}
