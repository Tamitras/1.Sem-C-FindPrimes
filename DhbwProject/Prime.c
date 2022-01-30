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

#define MAX_THREADS 1
//#define MAX_NUMBER 100000000 // 100.000.000
//int MAX_NUMBER = 1.000; // 168
//int MAX_NUMBER = 10.000; // 1229
//int MAX_NUMBER = 100.000; // 9592
//int MAX_NUMBER = 1.000.000; // 78498
//int MAX_NUMBER = 10.000.000; // 664579
//int MAX_NUMBER = 100.000.000; // 5761455
int MAX_NUMBER = 10000;
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
	//a->array = NULL;
	//a->used = 0;
	//a->size = 0;
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
	double time_spent = 0.0;
	clock_t begin = clock();

	for (int i = 3; i <= MAX_NUMBER; i += 2)
	{
		_numbers[i] = 1;
	}

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Initialisierung %f seconds with (%d) and %d \n\n", time_spent, _numbers, &_numbers);
	time_spent = 0.0;
	begin = clock();
}


/// <param name="from"></param>
/// <param name="til"></param>
/// <param name="_numbers"></param>
/// <param name="noPrimes"></param>
//void calcPrimes(int* from, int* til, int* _numbers, int* noPrimes)
DWORD WINAPI calcPrimes(struct param* param)
{
	DWORD  dwWaitResult;
	int from = param->from;
	int til = param->til;
	int max = param->max;

	//int* _numbers = (int*)param->_numbers;

	printf("Inside new Thread - Calculation von %d bis %d. Adresse von NumberPointer: %d (%d)\n\n", from, til, param->_numbers, &(*param)._numbers);

	double time_spent = 0.0;
	clock_t begin = clock();

	// Sieve
	for (long long i = from; i <= til; i += 2)
	{
		if (param->_numbers[i] == 1)
		{
			for (long long p = (i * i); p < til; p = p + i)
			{
				param->_numbers[p] = 0;
			}
		}
	}
	
	return 0;
}

int CreateErathotenes(Array * a)
{
	HANDLE tHandles[MAX_THREADS];
	DWORD threads[MAX_THREADS];
	PMYDATA pDataArray[MAX_THREADS];

	for (int i = 0; i < MAX_THREADS; i++)
	{
		int from = 0;
		int til = MAX_NUMBER;
		int max = MAX_NUMBER;

		from = (MAX_NUMBER / MAX_THREADS) * (i)+1;
		til = (MAX_NUMBER / MAX_THREADS) * (i + 1);

		pDataArray[i] = malloc(sizeof(PMYDATA));
		pDataArray[i]->from = from;
		pDataArray[i]->til = til;
		pDataArray[i]->max = max;
		pDataArray[i]->_numbers = a->array;

		threads[i] = i;

		printf("Thread %d gestartet. Von %d bis %d ThreadID (%u) Adresse von NumberPointer: %d (%d)\n", i, pDataArray[i]->from, pDataArray[i]->til, threads[i], pDataArray[i]->_numbers, a->array);

		/* create the thread */
		tHandles[i] = CreateThread(
			NULL,					/* default security attributes */
			0,						/* default stack size */
			calcPrimes,				/* thread function */
			pDataArray[i],			/* parameter to thread function */
			0,						/* default creation    flags */
			&threads[i]);
	}


	WaitForMultipleObjects(MAX_THREADS, tHandles, TRUE, INFINITE);

	//for (size_t i = 0; i < MAX_THREADS; i++)
	//{
	//	CloseHandle(tHandles[i]);
	//}
	//WaitForSingleObject(hMutex, INFINITE);
}

void countPrimes(int* _numbers, int* counter)
{
	for (size_t i = 0; i < MAX_NUMBER; i++)
	{
		if (_numbers[i] == 1)
		{
			*counter = *counter + 1;
			//printf("Prime found:%d \n", i);
		}

		//if (_numbers[i] != 0)
		//{

		//	printf("Prime found:%d \n", i);
		//}
	}
}

void FindPrimes()
{
	struct Array _numbers;
	initArray(&_numbers, MAX_NUMBER);
	int noPrimes = 0;

	// to store the execution time of code
	double time_spent = 0.0;
	clock_t begin = clock();

	InitializeNumbers(_numbers.array); // ALle Stellen wurden mit 1 überschrieben

	//DWORD threadid;
	//HANDLE tempHandle = CreateThread(
	//	NULL,					/* default security attributes */
	//	0,						/* default stack size */
	//	InitializeNumbers,		/* thread function */
	//	_numbers.array,			/* parameter to thread function */
	//	0,						/* default creation    flags */
	//	&threadid);


	printf("CreateEra called with adress: %d and %d\n", _numbers.array, &_numbers.array);
	CreateErathotenes(&_numbers);
	_numbers.array[0] = 0;
	_numbers.array[1] = 0;
	_numbers.array[2] = 1;
	_numbers.array[3] = 1;

	int found = 0;
	countPrimes(_numbers.array, &found);

	clock_t end = clock();
	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Calculation ends after %f seconds\n", time_spent);
	printf(" Primes found: %lld\n", found);
	printf(" No Primes found: %lld\n", MAX_NUMBER - 1 - found);
	freeArray(&_numbers);
}



void main() {

	FindPrimes();
	hold();
}