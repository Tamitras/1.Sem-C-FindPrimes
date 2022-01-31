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

//#define MAX_THREADS 4
#define MAX_THREADS 10
//#define MAX_NUMBER 100000000 // 100.000.000
//int MAX_NUMBER = 1.000; // 168
//int MAX_NUMBER = 10.000; // 1229
//int MAX_NUMBER = 100.000; // 9592
//int MAX_NUMBER = 1.000.000; // 78498
//int MAX_NUMBER = 10.000.000; // 664579
//int MAX_NUMBER = 100.000.000; // 5761455
int MAX_NUMBER = 100000000;
int MAX_THREADS_COUNT = 2;

static int* __restrict _NUMBERS; //__restrict performance boost

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

void printPtr(void* ptr)
{
	printf(" Pointer: %p  --> zeigt Adress(&): %d\n\n", ptr, &ptr);
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


void InitializeNumbers()
{
	double time_spent = 0.0;
	clock_t begin = clock();

	//printf("Alle geraden Zahlen sind keine Primzahlen und werden somit ignoriert\n");
	for (int i = 3; i <= MAX_NUMBER; i += 2)
	{
		_NUMBERS[i] = 1;
		//printf("Am Index: %d ist nun %d\n", i, _NUMBERS[i]);
	}

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Initialisierung %f seconds with (%d) and %d \n\n", time_spent, _NUMBERS, &_NUMBERS);
	time_spent = 0.0;
	begin = clock();
}

/// <param name="from"></param>
/// <param name="til"></param>
/// <param name="_numbers"></param>
/// <param name="noPrimes"></param>
//void calcPrimes(int* from, int* til, int* _numbers, int* noPrimes)
DWORD WINAPI calcPrimes(struct param* p)
{
	// Sieve
	if ((int)p->from == 0) (int)p->from = 3;
	if ((int)p->from % 2 == 0) (int)p->from++;
	for (long long i = (int)p->from; i <= (int)p->til; i += 2)
		if (_NUMBERS[i] == 1)
			for (long long p = (i * i); p <= MAX_NUMBER; p = p + i)
				if (_NUMBERS[p] == 1) _NUMBERS[p] = 0;

	return 0;
}

int CreateErathotenes()
{
	HANDLE tHandles[MAX_THREADS];
	DWORD threads[MAX_THREADS];
	PMYDATA pDataArray[MAX_THREADS];

	//printPtr(_NUMBERS);

	for (int i = 0; i < MAX_THREADS; i++)
	{
		int from = 0;
		int til = MAX_NUMBER;

		from = (MAX_NUMBER / MAX_THREADS) * (i);
		til = (MAX_NUMBER / MAX_THREADS) * (i + 1) - 1;

		pDataArray[i] = malloc(sizeof(PMYDATA));
		pDataArray[i]->from = from;
		pDataArray[i]->til = til;
		threads[i] = i;

		//WaitForSingleObject(threads[0], INFINITE);

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

void countPrimes(int* counter)
{
	printPtr(_NUMBERS);

	for (int i = 1; i <= MAX_NUMBER; i++)
	{
		if (_NUMBERS[i] == 1)
		{
			*counter = *counter + 1;
			//printf("Prime found on Index:%d \n", i);
		}

		//if (_numbers[i] != 0)
		//{

		//	printf("Prime found:%d \n", i);
		//}
	}
}

void FindPrimes()
{
	// Globale Variable --> Speicher wird reserviert
	_NUMBERS = (int*)malloc(MAX_NUMBER * sizeof(int));
	printf("Initialisierung(malloc)\n");

	int found = 0;
	struct Array _numbers;
	initArray(&_numbers, MAX_NUMBER);

	// to store the execution time of code
	double time_spent = 0.0;
	clock_t begin = clock();

	//InitializeNumbers(_numbers.array); // ALle Stellen wurden mit 1 überschrieben
	InitializeNumbers(); // ALle Stellen wurden mit 1 überschrieben

	//printf("CreateEra called with adress: %p and %d\n", _NUMBERS, &_NUMBERS);
	CreateErathotenes();
	clock_t end = clock();

	// Special case
	_NUMBERS[0] = 0;
	_NUMBERS[1] = 0;
	_NUMBERS[2] = 1;
	_NUMBERS[3] = 1;

	countPrimes(&found);

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Calculation ends after %f seconds\n", time_spent);
	printf(" Primes found: %lld\n", found);
	printf(" No Primes found: %lld\n", MAX_NUMBER - 1 - found);
	freeArray(&_numbers);
}

int main() {

	FindPrimes();
	hold();
}