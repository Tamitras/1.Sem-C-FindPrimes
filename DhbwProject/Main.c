#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>

void findPrimeNumbers()
{
	//printf("The number of bits in a byte %d\n", CHAR_BIT);

	//printf("The minimum value of CHAR = %d\n", CHAR_MIN);				/*		-128			*/
	//printf("The maximum value of CHAR = %d\n", CHAR_MAX);				/*		 127			*/

	//printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);		/*		-128			*/
	//printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);		/*		 127			*/

	//printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);		/*		 255			*/

	//printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);			/*		-32768			*/
	//printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);			/*		 32767			*/

	//printf("The minimum value of INT = %d\n", INT_MIN);					/*		-2147483648		*/
	//printf("The maximum value of INT = %d\n", INT_MAX);					/*		2147483647		*/

	//printf("The minimum value of LONG = %ld\n", LONG_MIN); 				/*		-2147483648		*/
	//printf("The maximum value of LONG = %ld\n", LONG_MAX); 				/*		2147483647		*/

	int biggestPrime;
	int* pbiggestPrime = &biggestPrime;

	printf("Weiter mit Enter...: ");
	char s[80];
	fgets(s, sizeof s, stdin);
	clock_t begin = clock();

	int intMax = SHRT_MAX;

	//for (short i = 1; i <= SHRT_MAX; i++) // Compiler says: inifite loop, 32767 --> 1
	for (int i = 1; i < intMax; i++)
	{
		int k = 2;
		// Divideable by 1 and itself
		bool tryFindPrimeNumber = true;
		bool isPrimeNumber = false;

		if (i < intMax * 0.1)
		{
			printf("In progress\r %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.1 && i < intMax * 0.2)
		{
			printf("In progress\r # %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.2 && i < intMax * 0.3)
		{
			printf("In progress\r ## %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.3 && i < intMax * 0.4)
		{
			printf("In progress\r ### %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.4 && i < intMax * 0.5)
		{
			printf("In progress\r #### %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.5 && i < intMax * 0.6)
		{
			printf("In progress\r ##### %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.6 && i < intMax * 0.7)
		{
			printf("In progress\r ###### %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.7 && i < intMax * 0.8)
		{
			printf("In progress\r ####### %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.8 && i < intMax * 0.9)
		{
			printf("In progress\r ######## %d%% ", (i * 100) / (intMax));
		}
		else if (i > intMax * 0.9 && i < intMax)
		{
			printf("In progress\r ######### %d%% ", (i * 100) / (intMax));
		}

		//printf("\rIn progress %d%%", (i * 100)/ (SHRT_MAX*10));
		fflush(stdout);

		while (tryFindPrimeNumber && k < i)
		{

			if (i % k == 0) {

				if (k == 1 || k == 2)
				{
					isPrimeNumber = true;
				}
				else
				{
					//printf("{%d} ist KEINE Primzahl, teilbar durch (%d)\n", i, k);
					tryFindPrimeNumber = false;
					isPrimeNumber = true;
					break;
				}
			}
			k++;
		}

		if (!isPrimeNumber && k != 2)
		{
			biggestPrime = i;
			//printf("{%d} ist _EINE Primzahl\n", i);
		}
	}

	printf("\r                                   ");
	fflush(stdout);

	printf("\n##### 100%% ##### abgeschlossen\n\n");
	fflush(stdout);

	printf("\a{%d} ist die größte gefundene Primzahl\n", biggestPrime);
	printf("\a{%d} ist die größte gefundene Primzahl\n", *pbiggestPrime);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Executiontime {%.2lf} secs\n", time_spent);
}

void main()
{
	printf("###                Primzezahl                ###\n\n");

	findPrimeNumbers();
}