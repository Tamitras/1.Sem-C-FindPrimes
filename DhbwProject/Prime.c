#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>
#include "Helper.h"
#include <windows.h>

#define MAX_THREADS 2
//#define MAX_NUMBER 100000000 // 100.000.000
int MAX_NUMBER = 100000;

HANDLE hMutex;

typedef struct Array
{
	int* array;
	size_t used;
	size_t size;
}Array;

void initArray(Array* a, size_t initialSize) {
	a->array = (int*)malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(Array* a, int element) {
	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
	// Therefore a->used can go up to a->size 
	if (a->used == a->size) {
		a->size *= 2;
		//a->array = realloc(a->array, a->size * sizeof(int));
		int* temp = realloc(a->array, a->size * sizeof * temp);
		if (!temp) { exit(EXIT_FAILURE); } a->array = temp;
	}
	a->array[a->used++] = element;
}

size_t getLength(Array* a)
{
	return a->used;
}

void freeArray(Array* a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

int contains(Array* a, int key)
{
	for (size_t i = 0;
		i <= a->used
		&& key != 0
		&& (a->array[i] == key || key % a->array[i] == 0); i++)
	{
		//printf(" Zahl %d bereits in Blacklist\n", key);
		return 1;
	}

	return 0;
}

typedef struct param
{
	void* workerId;
	int* from;
	int* til;
	int* max;
	int* _numbers;
	int* noPrimes;
	int* counter;
}*PMYDATA;

void* WorkerFunction(struct param* param)
{
	long* myId = (long*)param->workerId;
	int counter = (int*)param->counter;

	for (int i = 1; i <= counter; i++)
	{
		printf("\n%2ld (%d run) wird ausgeführt. Sleeping\n", *myId, i);
		Sleep(2000);
		printf("%2ld (%d run) wurde   beendet.\n", *myId, i);
	}
}

void InitializeNumbers(int* _numbers)
{
	// Alle Stellen mit 1 vorbelegen
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		_numbers[i] = 1;
	}
}


/// <param name="from"></param>
/// <param name="til"></param>
/// <param name="_numbers"></param>
/// <param name="noPrimes"></param>
//void calcPrimes(int* from, int* til, int* _numbers, int* noPrimes)
DWORD WINAPI calcPrimes(struct param* param)
{
	int from = param->from;
	int til = param->til;
	int max = param->max;

	int* _numbers = (int*)param->_numbers;
	int* noPrimes = (int*)param->noPrimes;
	int zero = 0;

	printf("Thread gestartet. Von %d bis %d\n", from, til);

	double time_spent = 0.0;
	clock_t begin = clock();

	int teilerFound = 0;
	int highestTeiler = 2;

	for (int i = from; i >= from && i <= til; i++)
	{
		if (_numbers[i] == 1)
		{
			for (int k = highestTeiler; k < MAX_NUMBER && k < i; k++)
			{
				if (_numbers[k] == 1 && i % k == 0 && i > highestTeiler) // k teilt i z.B. 2 teilt 4
				{
					teilerFound = 1;
					highestTeiler = k;

					for (int f = i; f < MAX_NUMBER; f = f + k)
					{
						if (_numbers[f] == 1)
						{
							WaitForSingleObject(hMutex, INFINITE);
							_numbers[f] = zero;
							*noPrimes = *noPrimes + 1;
							ReleaseMutex(hMutex);
						}
					}
				}
			}
		}

		if (i == max / 10) // bis 10%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 10%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 2) // bis 20%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 20%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 3) // bis 30%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 30%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 4) // bis 40%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 40%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 5) // bis 50%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 50%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 6) // bis 60%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 60%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 7) // bis 70%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 70%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 8) // bis 80%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 80%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == (max / 10) * 9) // bis 90%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 90%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
		if (i == max - 1) // bis 100%
		{
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Benötigte Zeit bis 100%% %f seconds\n", time_spent);
			time_spent = 0.0;
			begin = clock();
		}
	}
	return 0;
}

int CreateErathotenes(int* _numbers, int* noPrimes)
{
	_numbers[0] = 0;
	_numbers[1] = 0;

	//calcPrimes(0, MAX_NUMBER/2, _numbers, noPrimes);	
	//calcPrimes(MAX_NUMBER/2, MAX_NUMBER, _numbers, noPrimes);

	HANDLE tHandles[MAX_THREADS];
	DWORD threads[MAX_THREADS];
	PMYDATA pDataArray[MAX_THREADS];

	//create mutext with this thread the owner of the mutex
	hMutex = CreateMutex(NULL, TRUE, NULL);

	for (int i = 0; i < MAX_THREADS; i++)
	{
		struct param myParam1;

		int from = 0;
		int til = MAX_NUMBER;
		int max = MAX_NUMBER;

		switch (i)
		{
		case 0:
			from = 0;
			til = MAX_NUMBER / 2;
			break;
		case 1:
			from = (MAX_NUMBER / 2) + 1;
			til = MAX_NUMBER;
			break;
		default:
			break;
		}

		//pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PMYDATA));
		pDataArray[i] = malloc(sizeof(PMYDATA));
		pDataArray[i]->from = from;
		pDataArray[i]->til = til;
		pDataArray[i]->max = max;
		pDataArray[i]->_numbers = _numbers;
		pDataArray[i]->noPrimes = noPrimes;

		threads[i] = i;

		printf("Thread %d gestartet. Von %d bis %d ThreadID (%u)\n", i, pDataArray[i]->from, pDataArray[i]->til, threads[i]);

		/* create the thread */
		tHandles[i] = CreateThread(
			NULL,					/* default security attributes */
			0,						/* default stack size */
			calcPrimes,				/* thread function */
			pDataArray[i],				/* parameter to thread function */
			0,						/* default creation    flags */
			&threads[i]);
	}

	ReleaseMutex(hMutex);

	WaitForMultipleObjects(MAX_THREADS, tHandles, TRUE, INFINITE);

	for (size_t i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(tHandles[i]);
	}
}

void FindPrimes()
{
	struct Array _numbers;
	initArray(&_numbers, MAX_NUMBER);

	// to store the execution time of code
	double time_spent = 0.0;
	clock_t begin = clock();

	InitializeNumbers(_numbers.array); // ALle Stellen wurden mit 1 überschrieben
	int noPrimes = 0;
	CreateErathotenes(_numbers.array, &noPrimes);
	int primesFound = MAX_NUMBER - noPrimes - 2;

	clock_t end = clock();
	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("The elapsed time is %f seconds\n", time_spent);
	printf(" Primes found: %lld\n", primesFound);
	freeArray(&_numbers);
}

void main() {

	FindPrimes();
	hold();
}