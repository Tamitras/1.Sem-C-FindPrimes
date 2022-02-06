#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

int num_threads = 4;
long long max_number = 100000000;

typedef char sieve_t;
static sieve_t* __restrict sieve;

void initialize_sieve(void)
{
    sieve = (sieve_t*)calloc(max_number + 1, sizeof(sieve_t)); // 0 initialized
    sieve[2] = 1;
    register long long i = 3;
    for (; i <= max_number; i += 2)
        sieve[i] = 1;
}


DWORD WINAPI run_sieve_func(void* data)
{
    long long max_i = sqrt(max_number);
    register long long i = *(int*)data;
    for (; i <= max_i; i += 2 * num_threads)
        if (sieve[i])
        {
            register long long k = i * i;
            for (; k <= max_number; k += i)
                if (sieve[k])
                    sieve[k] = 0;
        }
    return 0;
}


void run_sieve(void)
{
    HANDLE* tHandles = (HANDLE*)malloc(num_threads * sizeof(HANDLE));
    DWORD* threads = (DWORD*)malloc(num_threads * sizeof(DWORD));
    int* data = (int*)malloc(num_threads * sizeof(int));
    register int i = 0;

    for (; i < num_threads; i++) {
        data[i] = 3 + 2 * i;
        threads[i] = i;

        tHandles[i] = CreateThread(
            NULL,
            0,
            run_sieve_func,
            &data[i],
            0,
            &threads[i]
        );
    }

    WaitForMultipleObjects(num_threads, tHandles, TRUE, INFINITE);

    i = 0;
    for (; i < num_threads; i++) {
        CloseHandle(tHandles[i]);
    }

    free(threads);
    free(tHandles);
}

long count_primes(void)
{
    long count = 0;
    register long long i = 1;
    for (; i <= max_number; i++)
        count += sieve[i];

    return count;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }

    if (argc > 2) {
        max_number = atoll(argv[2]);
    }

    printf("num_threads: %d\n", num_threads);
    printf("max_number: %lld\n", max_number);

    double time_spent, total_time;
    clock_t begin, end;
    total_time = 0.0;

    printf("---------------------------------------------------------------------\n");

    // Initialize sieve
    begin = clock();
    initialize_sieve();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    total_time += time_spent;
    printf("%-55s %.3f seconds\n", "Initialization time:", time_spent);

    // Run sieve
    begin = clock();
    run_sieve();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    total_time += time_spent;
    printf("%-55s %.3f seconds\n", "Calculation time:", time_spent);

    // Count primes
    begin = clock();
    long count = count_primes();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    total_time += time_spent;
    printf("%-55s %.3f seconds\n", "Counting primes time:", time_spent);

    printf("---------------------------------------------------------------------\n");

    printf("%-55s %.3f seconds\n", "Total time:", total_time);
    printf("\n");
    printf("Primes found = %ld\n", count);

    free(sieve);

    return 0;
}