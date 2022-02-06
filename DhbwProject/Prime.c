#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>
#include <windows.h>

//#define MAX_THREADS 4
#define MAX_THREADS 2
//#define MAX_NUMBER 100000000 // 100.000.000
//int MAX_NUMBER = 1.000; // 168
//int MAX_NUMBER = 10.000; // 1229
//int MAX_NUMBER = 100.000; // 9592
//int MAX_NUMBER = 1.000.000; // 78498
//int MAX_NUMBER = 10.000.000; // 664579
//int MAX_NUMBER = 100.000.000; // 5761455
int MAX_NUMBER = 100000000;

static int* __restrict _NUMBERS; //__restrict performance boost
double all_time_spent = 0.0;

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
	int* workerId;
	int* from;
	int* til;
}*PMYDATA;

void calcSubPrimes(int* _i)
{
	register int i = _i;
	register int k = i * i;
	for (; k <= MAX_NUMBER; k += i)
	{
		if (_NUMBERS[k] == 1) _NUMBERS[k] = 0;
	}

	//for (register int b = MAX_NUMBER; b >= i * i; b -= i)
	//{
	//	if (_NUMBERS[b] == 1) _NUMBERS[b] = 0;
	//}
	//printf("\n___ calcSubPrimes done with %d", i);
}

void InitializeNumbers()
{
	double time_spent = 0.0;
	clock_t begin = clock();

	//printf("Alle geraden Zahlen sind keine Primzahlen und werden somit ignoriert\n");
	for (register int i = 3; i <= MAX_NUMBER; i += 2) _NUMBERS[i] = 1;

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	all_time_spent += time_spent;
	printf("Initialisierung %f seconds (Clock)\n", time_spent);

	DWORD thread1;
	// Create SubThread
	CreateThread(NULL, 0, calcSubPrimes, 3, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 5, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 7, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 11, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 13, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 17, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 19, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 23, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 29, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 31, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 37, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 41, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 43, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 47, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 53, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 59, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 61, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 67, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 71, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 73, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 79, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 83, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 89, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 97, 0, &thread1);

	// 100 erreicht

	CreateThread(NULL, 0, calcSubPrimes, 101, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 103, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 107, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 109, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 113, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 127, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 131, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 137, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 139, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 149, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 151, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 157, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 163, 0, &thread1);
	// 
	// 
	CreateThread(NULL, 0, calcSubPrimes, 167, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 173, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 179, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 181, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 191, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 193, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 197, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 199, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 211, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 223, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 227, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 229, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 233, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 239, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 241, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 251, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 257, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 263, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 269, 0, &thread1);
	// 
	// 
	CreateThread(NULL, 0, calcSubPrimes, 271, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 277, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 281, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 283, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 293, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 307, 0, &thread1);
	// 
	// 
	CreateThread(NULL, 0, calcSubPrimes, 311, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 313, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 317, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 331, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 337, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 347, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 349, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 353, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 359, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 367, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 373, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 379, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 383, 0, &thread1);

	//
	CreateThread(NULL, 0, calcSubPrimes, 389, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 397, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 401, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 409, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 419, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 421, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 431, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 433, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 439, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 443, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 449, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 457, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 461, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 463, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 467, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 469, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 479, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 487, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 491, 0, &thread1);
	CreateThread(NULL, 0, calcSubPrimes, 499, 0, &thread1);
}

/// <param name="from"></param>
/// <param name="til"></param>
/// <param name="_numbers"></param>
/// <param name="noPrimes"></param>
//void calcPrimes(int* from, int* til, int* _numbers, int* noPrimes)
void calcPrimes(struct param* p)
{
	double time_spent = 0.0;
	clock_t begin = clock();

	register int from = (int)p->from;
	register int til = (int)p->til;

	// Sieve
	if (from == 0) from = 3;
	if (from % 2 == 0) from++;
	for (register unsigned int i = from; i <= til; i += 2)
	{
		if (i <= 10000 && _NUMBERS[i] == 1 && i > 499) // Root of max_number
		{
			for (register int p = (i * i); p <= MAX_NUMBER; p = p + i)
			{
				if (_NUMBERS[p] == 1) _NUMBERS[p] = 0;
			}
		}
	}

	//if (from == 0) from = 3;
	//if (from % 2 == 0) from++;
	//for (register unsigned int i = from; i <= til; i += 2)
	//{
	//	if (i <= 10000 && _NUMBERS[i] == 1 && i > 499) // Root of max_number
	//	{
	//		// umgedrehte Loop => schneller als normale
	//		for (register int b = MAX_NUMBER; b >= (i * i); b -= i)
	//		{
	//			if (_NUMBERS[b] == 1) _NUMBERS[b] = 0;
	//		}
	//	}
	//}

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
}

int CreateErathotenes()
{
	HANDLE tHandles[MAX_THREADS];
	DWORD threads[MAX_THREADS];
	PMYDATA pDataArray[MAX_THREADS];

	int from = 0;
	int til = MAX_NUMBER;

	// Special case
	_NUMBERS[0] = 0;
	_NUMBERS[1] = 0;
	_NUMBERS[2] = 1;
	_NUMBERS[3] = 1;

	// to store the execution time of code
	double time_spent = 0.0;
	clock_t begin = clock();

	for (int i = 0; i < MAX_THREADS; i++)
	{
		from = (MAX_NUMBER / MAX_THREADS) * (i);
		til = ((MAX_NUMBER / MAX_THREADS) * (i + 1)) - 1;

		pDataArray[i] = malloc(sizeof(PMYDATA));
		pDataArray[i]->from = from;
		pDataArray[i]->til = til;
		pDataArray[i]->workerId = i;
		threads[i] = i;

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

	clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	all_time_spent += time_spent;
	printf("Calculation %f seconds (Clock)\n", time_spent);

	for (size_t i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(tHandles[i]);
	}
}

void CountPrimes(int* counter)
{
	int c = *counter;
	double time_spent = 0.0;
	clock_t begin = clock();

	for (int i = 1; i <= MAX_NUMBER; i++)
		if (_NUMBERS[i] == 1) c++;

	*counter = c;

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	all_time_spent += time_spent;
	printf("Counting primes %f seconds (Clock) \n", time_spent);
}

void FindPrimes()
{
	// Globale Variable --> Speicher wird reserviert
	_NUMBERS = (int*)malloc(MAX_NUMBER * sizeof(int));

	int found = 0;
	struct Array _numbers;
	initArray(&_numbers, MAX_NUMBER);

	///////////////////////
	// START
	///////////////////////

	//InitializeNumbers(_numbers.array); // ALle Stellen wurden mit 1 überschrieben
	InitializeNumbers(); // ALle Stellen wurden mit 1 überschrieben

	//printf("CreateEra called with adress: %p and %d\n", _NUMBERS, &_NUMBERS);
	CreateErathotenes();

	CountPrimes(&found);

	printf(" Primes found: %d\n", found);

	if (found == 5761455 || found == 50847534) // 10^8 oder 10^9 
	{
		printf("\n #############################################################\n\n");
		printf(" Herzlichen Glueckwunsch - Es wurden alle Primzahlen gefunden!!\n\n");
		printf("             Overall Calculation %f seconds (Clock) \n", all_time_spent);
		printf(" #############################################################\n");
	}


	freeArray(&_numbers);
}

FindPrimes2()
{
	double time_spent = 0.0;
	clock_t begin = clock();

	_NUMBERS = (int*)calloc(MAX_NUMBER, sizeof(int));

	// Special case
	_NUMBERS[0] = 0;
	_NUMBERS[1] = 0;
	_NUMBERS[2] = 1;
	_NUMBERS[3] = 1;
	_NUMBERS[4] = 1;

	//InitializeNumbers(); // ALle Stellen wurden mit 1 überschrieben
	int limit = MAX_NUMBER;
	int found = 0;
	int wlimit;
	register int i, j, k, x, y, z;
	//unsigned char* sieb;
	//sieb = (unsigned char*)calloc(limit, sizeof(unsigned char));

	wlimit = sqrt(limit);

	for (x = 1; x <= wlimit; x++) {
		for (y = 1; y <= wlimit; y++) {
			z = 4 * x * x + y * y;
			if (z <= limit && (z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 || z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53)) {
				_NUMBERS[z] = !_NUMBERS[z];
			}
			z = 3 * x * x + y * y;
			if (z <= limit && (z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43)) {
				_NUMBERS[z] = !_NUMBERS[z];
			}
			z = 3 * x * x - y * y;
			if (x > y && z <= limit && (z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59)) {
				_NUMBERS[z] = !_NUMBERS[z];
			}
		}
	}

	for (i = 5; i <= wlimit; i++) {
		if (_NUMBERS[i] == 1) {
			for (j = 1; j * i * i < limit; j++) {
				_NUMBERS[j * i * i] = 0;
			}
		}
	}

	printf("The following primes have been calculated:\n");
	for (i = 0; i <= limit; i++) {
		if (_NUMBERS[i] == 1) {
			found++;
			//printf("\n%d (%d)", i, found);
		}
	}

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	all_time_spent += time_spent;
	printf("Init + Calc + Find %f seconds \n\n", time_spent);

	printf("\n Primes found: %d\n", found);

	if (found == 5761455 || found == 50847534) // 10^8 oder 10^9 
	{
		printf("\n #############################################################\n\n");
		printf(" Herzlichen Glueckwunsch - Es wurden alle Primzahlen gefunden!!\n\n");
		printf("             Overall Calculation %f seconds \n\n", all_time_spent);
		printf(" #############################################################\n");
	}
}

int main() {

	FindPrimes();
	//FindPrimes2();
	hold();
}