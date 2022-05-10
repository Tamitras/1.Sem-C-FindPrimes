#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>														// required for ThreadHandling

int num_threads = 4;														// threads
long long max_number = 100000000;											// maxNumber

typedef char sieve_t;														// change to int decrease performance 
static sieve_t* __restrict sieve;											// keyword to let the compiler do some optimizations for speed
HANDLE* tHandles;
DWORD* threads;
int* oddNumbers;

void initialize_sieve(void)
{
	sieve[2] = 1;															// special case
	for (register unsigned long long i = 3; i <= max_number; i += 2)
		sieve[i] = 1;														// pre set all not even numbers to 1
}

void run_sieve_func(void* data)												// Null Pointer as parameter
{
	long long max_i = sqrt(max_number);										// Get the root of MaxNumber
	int _data = *(int*)data;												// cast void pointer to int pointer an get value of this pointer
	
	for (register long long i = _data; i <= max_i; i += 2 * num_threads)	// Keyword register means that the variable is stored in cpu register instead of RAM --> faster location/access
		if (sieve[i])
			for (register long long k = i * i; k <= max_number; k += i)
				if (sieve[k]) sieve[k] = 0;
}

void run_sieve(void)
{
	for (register long long i = 0; i < num_threads; i++) {					// Run with Threads
		oddNumbers[i] = 3 + 2 * i;											// Database of odd numbers
		threads[i] = i;

		tHandles[i] = CreateThread(
			NULL,
			0,
			run_sieve_func,
			&oddNumbers[i],
			0,
			&threads[i]
		);
	}

	WaitForMultipleObjects(num_threads, tHandles, TRUE, INFINITE);			// Wait for Threads to be finished
	for (int i = 0; i < num_threads; i++) {
		CloseHandle(tHandles[i]);											// Close all open ThreadHandles
	}
	
	free(threads);															// deallocation memory of threads and tHandles
	free(tHandles);
}

long count_primes(void)
{
	long count = 0;
	for (register long long i = 1; i <= max_number; i++)
		count += sieve[i];

	return count;
}

int main(int argc, char* argv[])
{
	if (argc > 1) 
		num_threads = atoi(argv[0]);										// char to integer (ato[I]nt)

	if (argc > 2) 
		max_number = atoll(argv[1]);										// char to long long (ato[L]ong[L]ong)

	printf("%-56s %d\n", "\nThreads:", num_threads);						// Print arguments
	printf("%-55s %lld\n", "Max Number:", max_number);

	double time_spent, total_time;											// Declare local variables
	clock_t begin, end;
	total_time = 0.0;

	/*Microsoft C Compiler definitions --> not working with GNU/Unix Compiler
	typedef uint8_t BYTE;
	typedef uint16_t WORD;
	typedef uint32_t DWORD;
	typedef uint64_t QWORD;
	*/
	sieve = (sieve_t*)calloc(max_number + 1, sizeof(sieve_t));				// 0 initialized
	tHandles = (HANDLE*)malloc(num_threads * sizeof(HANDLE));
	threads = (DWORD*)malloc(num_threads * sizeof(DWORD));
	oddNumbers = (int*)malloc(num_threads * sizeof(int));

	printf("----------------------------------------------------------------------\n");

	// Initialize sieve of Erathostenes
	begin = clock();
	initialize_sieve();
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	total_time += time_spent;
	printf("%-55s %.4f seconds\n", "Initialization time:", time_spent);		// Print init time with 4 digits floating point and after 55 digits in console.

	// Run sieve
	begin = clock();
	run_sieve();
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	total_time += time_spent;
	printf("%-55s %.4f seconds\n", "Calculation time:", time_spent);

	// Count primes
	begin = clock();
	long count = count_primes();
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	total_time += time_spent;
	printf("%-55s %.4f seconds\n", "Counting primes time:", time_spent);

	printf("----------------------------------------------------------------------\n");

	printf("%-55s %.4f seconds\n", "Total time:", total_time);
	printf("\n");

	if (count == 5761455 || count == 50847534) // 10^8 or 10^9 
		printf("Primes found = %ld\n", count);
	else
		printf("!!! Something went wrong !!!\n");

	//		10^8 (100.000.000)
	//								Init:	 0.01sec
	//								Calc:	 0.42sec
	//								Sum:	 0.01sec
	// 
	//								Gesamt: 0.44sec
	
	//		10^9 (1.000.000.000)
	//								Init:	 0.17sec
	//								Calc:	 5.35sec
	//								Sum:	 0.10sec
	// 
	//								Gesamt:  5.50sec
	
	//		10^10	(10.000.000.000)		
	//								Init:	 2.50sec
	//								Calc:	80.57sec
	//								Sum:	 1.30sec
	// 
	//								Gesamt: 85.00sec

	free(sieve); // deallocation memory of sieve
	scanf("%d", &count);

	return 0;
}