#include <windows.h>
#include <tchar.h>
#include <math.h>

#include <stdio.h>
#include <fcntl.h> 
#include <io.h>


// funcionalidade relacionada com temporização

static double PerfCounterFreq; // n ticks por seg.

void initClock() {
	LARGE_INTEGER aux;
	if (!QueryPerformanceFrequency(&aux))
		_tprintf(TEXT("\nSorry - No can do em QueryPerfFreq\n"));
	PerfCounterFreq = (double)(aux.QuadPart); // / 1000.0;
	_tprintf(TEXT("\nTicks por sec.%f\n"), PerfCounterFreq);
}

__int64 startClock() {
	LARGE_INTEGER aux;
	QueryPerformanceCounter(&aux);
	return aux.QuadPart;
}

double stopClock(__int64 from) {
	LARGE_INTEGER aux;
	QueryPerformanceCounter(&aux);
	return (double)(aux.QuadPart - from) / PerfCounterFreq;
}



// estrutura de dados para controlar as threads

typedef struct {
	unsigned int lowlim;
	unsigned int lim;
	unsigned int * count;
	CRITICAL_SECTION mutex;
} TDados;

// número * máximo * de threads
// podem (e devem) ser menos
#define MAX_THREADS 20

DWORD WINAPI mult(LPVOID param) {
	TDados* dados = (TDados*)param;
	unsigned int i;
	for (i = dados->lowlim; i <= dados->lim; i++)
	{
		if (i % 3 == 0)
		{
			EnterCriticalSection(&dados->mutex);
			(*(dados->count))++;
			LeaveCriticalSection(&dados->mutex);

		}
	}
	return 0;
}



int _tmain(int argc, TCHAR * argv[]) {
	
	// matriz de handles das threads
	HANDLE hThreads[MAX_THREADS];

	CRITICAL_SECTION mutex;
	
	// Matriz de dados para as threads;
	TDados tdados[MAX_THREADS];
	
	// número efectivo de threads
	int numthreads;
	
	// limite superior
	unsigned int limsup;

	// variáveis para cronómetro
	__int64 clockticks;
	double duracao;
	unsigned int count = 0;
	unsigned int range;
	unsigned int inter;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif 

	CreateEvent(NULL, TRUE, FALSE, NULL);
	initClock();
	_tprintf(TEXT("\nLimite sup. -> "));
	wscanf_s(TEXT("%u"), &limsup);
	_tprintf(TEXT("\nNum threads -> "));
	wscanf_s(TEXT("%u"), &numthreads);
	if (numthreads > MAX_THREADS)
		numthreads = MAX_THREADS;
	InitializeCriticalSection(&mutex, 400);
	for (size_t i = 0; i < numthreads; i++)
	{
		tdados[i].lowlim = 1 + (limsup / numthreads) * i;
		tdados[i].lim = (limsup / numthreads) * (i + 1);
		tdados[i].count = &count;
		tdados[i].mutex = mutex;

		_tprintf(TEXT("\nThread %u: %u to %u"), i, tdados[i].lowlim, tdados[i].lim);

		hThreads[i] = CreateThread(NULL, 0, mult, &tdados[i], 0, NULL);
	}

	clockticks = startClock();

	for (size_t i = 0; i < numthreads; i++)
	{
		ResumeThread(hThreads[i]);
	}

	WaitForMultipleObjects(numthreads, hThreads, TRUE, INFINITE);

	duracao = stopClock(clockticks);
	_tprintf(TEXT("\nSegundos=%f\n"), duracao);

	_tprintf(TEXT("\contador=%f\n"), count);

	 for (size_t i = 0; i < numthreads; i++)
	 {
		 CloseHandle(hThreads[i]);
	 }
	 DeleteCriticalSection(&mutex);
	return 0;
}
