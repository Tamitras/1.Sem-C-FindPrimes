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
int MAX_NUMBER = 10000;

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

struct param
{
	void* workerId;
	int* counter;
};

//void* WorkerFunction(struct param* param)
//{
//	long* myId = (long*)param->workerId;
//	int counter = (int*)param->counter;
//
//	for (int i = 1; i <= counter; i++)
//	{
//		printf("\n%2ld (%d run) wird ausgeführt. Sleeping\n", *myId, i);
//		Sleep(2000);
//		printf("%2ld (%d run) wurde   beendet.\n", *myId, i);
//	}
//}

void InitializeNumbers(int* _numbers)
{
	// Alle Stellen mit 1 vorbelegen
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		_numbers[i] = 1;
	}
}

int CreateErathotenes(int* _numbers)
{
	int noPrimeNumbers = 0;
	int primeNumbers = -2;
	int maxVielfaches = MAX_NUMBER;

	int flag = 1; // still looking for prime

	struct Array bl;
	initArray(&bl, MAX_NUMBER);

	bl.array[0] = 2;
	bl.used++;

	// Durchlaufe jede Zahl bis MAX
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		//printf("Prüfe Index %d --> ", i);
		flag = 1;

		if (contains(&bl, i) == 1) // Aktuelle Zahl ist in der Blacklist enthalten --> No Prime
		{
			//printf(" %d ist in Blacklist enthalten  --> no Prime \n", i);
			//_numbers[i] = 0;
			flag = 0;
		}

		int teiler = bl.used + 1;

		while (teiler < i && teiler > 0 && flag == 1)
		{
			if (i % teiler == 0)
			{
				bl.array[bl.used++] = i;
				flag = 0;
				//printf(" %d wird geteilt von teiler %d und somit ist %d keine Primzahl --> \n", i, teiler, i);
				// Füge Blacklist weitere Teiler hinzu 3->6->9->12 etc
			}
			teiler++;
		}

		//// Durchlaufe jedes Vielfaches
		//for (int vielFaches = bl.used +1;
		//	vielFaches < i 
		//	&& vielFaches > 0 
		//	&& flag == 1; vielFaches++) // Sieb für 2,3,4
		//{
		//	if (i % vielFaches == 0)
		//	{
		//		//Durch Vielfaches teilbar --> Vielfaches kommt auf die BlackList
		//		//printf(" %d ist ein vielfaches von %d und somit ist %d keine Primzahl --> ", i, vielFaches, i);
		//		bl.array[bl.used++] = i;

		//		//for (int k = vielFaches; k <= MAX_NUMBER; k = vielFaches + k)
		//		//{
		//		//	bl.array[bl.used++] = k;
		//		//}

		//		//bl.used++;
		//		//printf("Vielfaches:(%d) wird der Blacklist hinzugefügt\n", vielFaches);
		//		flag = 0;
		//		//_numbers[i] = 0;
		//	}
		//}

		//(flag == 1) ? primeNumbers++ : NULL;
	}

	//printf("Naechstes Vielfaches ist an der Reihe: %d\n\n", vielFaches);

	freeArray(&bl);
	return primeNumbers - 2;
}

void FindPrimes()
{
	struct Array _numbers;
	initArray(&_numbers, MAX_NUMBER);

	// to store the execution time of code
	double time_spent = 0.0;
	clock_t begin = clock();

	//InitializeNumbers(_numbers.array);
	int primesFound = CreateErathotenes(_numbers.array);

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

	//int primesFound = 0;
	//int* _primesFound = &primesFound;
	//CalcPrimeNumbers(_primesFound, 0);

	//HANDLE tHandles[5];
	//DWORD threads[MAX_THREADS];

	//for (int i = 0; i < MAX_THREADS; i++)
	//{
	//	HANDLE tHandle;
	//	DWORD threadId;

	//	// Parameterinitialisierung
	//	struct param myParam;
	//	myParam.counter = 5;
	//	myParam.workerId = &threadId;
	//	printf("<WorkerIdD: %ld>\n", &threadId);

	//	// Pointer wird erzeugt
	//	struct param* myParamPtr = &myParam;

	//	/* create the thread */
	//	tHandles[i] = CreateThread(
	//		NULL,					/* default security attributes */
	//		0,						/* default stack size */
	//		WorkerFunction,			/* thread function */
	//		myParamPtr,				/* parameter to thread function */
	//		0,						/* default creation    flags */
	//		&threads[i]);

	//}

	/////* returns the thread identifier */
	////if (ThreadHandle != NULL) {
	////	/* now wait for the thread to finish */ WaitForSingleObject(ThreadHandle, INFINITE);
	////	/* close the thread handle */
	////	CloseHandle(ThreadHandle);
	////}

	//WaitForMultipleObjects(MAX_THREADS, tHandles, TRUE, INFINITE);

	//for (size_t i = 0; i < MAX_THREADS; i++)
	//{
	//	CloseHandle(tHandles[i]);
	//	printf("%ld beendet.\n", tHandles[i]);
	//	printf("%d beendet.\n", &tHandles[i]);
	//}

	hold();
}