#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>

#include "Helper.h"


// function declaration
void printWinner(struct gamer* currentgamer);

void findPrimeNumbers()
{
	int biggestPrime;
	int* pbiggestPrime = &biggestPrime;
	char s[80];

	printf("###                Primzezahl                ###\n\n");
	printf("Weiter mit Enter...: ");

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
					printf("{%d} ist KEINE Primzahl, teilbar durch (%d)\n", i, k);
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

	printf("\a{%d} ist die gr\x94\xe1te gefundene Primzahl\n", biggestPrime);
	printf("\a{%d} ist die gr??te gefundene Primzahl\n", *pbiggestPrime);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Executiontime {%.2lf} secs\n", time_spent);
}


void searchForCharInString()
{
	char bu = 'n';
	char temp[255];
	strcpy_s(temp, sizeof(temp), "Hannes ist doof \n und dumm, lel\n");

	printf("Temp: %s\n\n", temp);

	char* res = strchr(temp, bu);
	char* res2 = strchr(temp, '\n');

	printf("res: %s", res);
	printf("res2: %s", res2);
}

void aufgabeTest()
{
	printf("Bitte geben Sie die Baureihe inklusive (-) ein. z.B: {xxx-xxx-x}");

	char gesamt[9 + 1];
	char br[3 + 1];
	char charge[3 + 1];
	char safetyValue[3 + 1];
	gets_s(gesamt, sizeof(gesamt));

	strncpy_s(br, sizeof(br), gesamt, 3);
	strncpy_s(charge, sizeof(charge), gesamt + 4, 3);
	strncpy_s(safetyValue, sizeof(safetyValue), gesamt + 8, 3);

	printf("Baureihe: %s\n", br);
	printf("Charge: %s\n", charge);
	printf("Pr?fsumme: %s\n", safetyValue);

	// calc pr?fsumme

	int pruefSumme = 0;
	int temp = 0;
	int* ptrTemp = temp;
	int* ptrpruefSumme = pruefSumme;

	// durchlaufe 1. BLock
	for (int i = 0; i < sizeof(br); i++)
	{
		int a;
		char value[3];
		char c[1];

		if (i % 2 == 0) // gerade zahl
		{
			c[0] = br[i];
			a = atoi(c);
		}
		else
		{
			c[0] = br[i];
			a = atoi(c) * 2;
		}

		if (a >= 10)
		{
#pragma warning(suppress : 4996)
			sprintf(value, "%d", a);
			//sprintf_s(value,sizeof(),)
			char val1[1];
			char val2[1];

			val1[0] = value[0];
			val2[0] = value[1];

			int numb1 = atoi(val1);
			int numb2 = atoi(val2);

			int b = numb1 + numb2;

			temp = b;
		}
		else
		{
			temp = a;
		}

		printf("Alte Pr?fsumme: %d + neuer Wert %d\n", pruefSumme, temp);
		pruefSumme += temp;
	}

	// durchlaufe 2. BLock
	for (int i = 0; i < sizeof(charge); i++)
	{
		int a;
		char value[3];
		char c[1];

		if (i % 2 != 0) // gerade zahl
		{
			c[0] = charge[i];
			a = atoi(c);
		}
		else
		{
			c[0] = charge[i];
			a = atoi(c) * 2;
		}

		if (a >= 10)
		{
#pragma warning(suppress : 4996)
			sprintf(value, "%d", a);
			//sprintf_s(value,sizeof(),)
			char val1[1];
			char val2[1];

			val1[0] = value[0];
			val2[0] = value[1];

			int numb1 = atoi(val1);
			int numb2 = atoi(val2);

			int b = numb1 + numb2;

			temp = b;
		}
		else
		{
			temp = a;
		}

		printf("Alte Pr?fsumme: %d + neuer Wert %d\n", pruefSumme, temp);
		pruefSumme += temp;
	}

	int result = 0;
	if (pruefSumme <= 10)
	{
		result = 10 - pruefSumme;
	}
	else if (pruefSumme <= 20)
	{
		result = 20 - pruefSumme;
	}
	else if (pruefSumme <= 30)
	{
		result = 30 - pruefSumme;
	}
	else if (pruefSumme <= 40)
	{
		result = 40 - pruefSumme;
	}
	else if (pruefSumme <= 50)
	{
		result = 50 - pruefSumme;
	}
	else if (pruefSumme <= 60)
	{
		result = 60 - pruefSumme;
	}

	printf("Berechnete Pr?fsumme: %d\n", result);

	char ht[10];
	//itoa(result, ht, 10);
	_itoa_s(result, ht, sizeof(ht), 10);

	printf("Berechnete Pr?fsumme als charArray: %s\n", ht);
}

void aufgabeTest2()
{
	printf("Bitte geben Sie Ihre Kontonummer an. z.B: {xxxxxxxxxxxxxx} maximal 20\n Kontonummer: ");

	char kn[20 + 1];

	gets_s(kn, sizeof(kn));
	int len = strlen(kn);


	int sum = 0;

	char multiplier[] = { 2,3,4,5,6,7 };
	int k = 0;

	for (int i = len - 1; i != -1; i--)
	{
		if (k >= sizeof(multiplier))
		{
			k = 0;
		}

		int currentMultiplier = (int)multiplier[k];
		k++;

		char a[1];
		a[0] = kn[i];

		if (a != 48)
		{
			int temp = atoi(a);
			temp = temp * currentMultiplier;
			sum += temp;
			printf("%d wird mit %d multipliziert: Neue Summe: %d\n", atoi(a), currentMultiplier, sum);
		}
	}

	printf("Summe: %d \n Modulo:11 \n", sum);

	int rest = sum % 11;

	printf("Rest: %d\n", rest);

	int res = 11 - rest;

	if (res == 10 || res == 11)
	{
		res = 0;
	}

	printf("Pruefsumme: %d\n", res);

	char temp2[2];
#pragma warning(suppress : 4996)
	sprintf(temp2, "%d", res);

	strncat_s(kn, sizeof(kn), temp2, len);

	printf("Neue Kontonummer mit Pruefsumme: %s\n", kn);

}

typedef struct gamer
{
	char name[20];
	int attempts;
};

void aufgabeTest3()
{
	// local variables
	int min = 0;
	int max = 1000;
	int zufzahl = getRandom(min, max);
	bool winnerDefined = false;
	bool userEingabeOkay = false;

	// Initialize gamer struct/object
	struct gamer player1 = { "", 0 };
	struct gamer player2 = { "", 0 };
	struct gamer* currentgamer;

	// Insert name for player 1
	printf("Bitte geben Sie einen Namen f?r Spieler 1 ein:");
	gets_s(player1.name, sizeof(player1.name));

	// Insert name for player 2
	printf("Bitte geben Sie einen Namen f?r Spieler 2 ein:");
	gets_s(player2.name, sizeof(player2.name));

	printf("Das Spiel zwischen %s und %s hat begonnen\n\n", player1.name, player2.name);

	for (int i = 0; !winnerDefined; i++)
	{
		char eingabe[20];

		if (i % 2 == 0) // gamer1
		{
			printf("\n%s ist am Zug.\n", player1.name);
			currentgamer = &player1; // Referenz wird ?bergeben
		}
		else //gamer 2
		{
			printf("%s ist am Zug.\n", player2.name);
			currentgamer = &player2;
		}

		do {
			printf("Bitte geben Sie eine Zahl zwischen %d und %d ein\n", min, max);
			gets_s(eingabe, sizeof(eingabe));
			int eingabeAsInt = atoi(eingabe);

			if (eingabeAsInt > max || eingabeAsInt < min || eingabeAsInt == 0)
			{
				if (eingabeAsInt == 0)
				{
					char temp[50];
					strcpy_s(temp, sizeof(temp), "Bitte eine Zahl gr\x94");
					strcat_s(temp, sizeof(temp), "\xe1");
					strcat_s(temp, sizeof(temp), "er 0 eingeben\n");
					printf("%s", temp);
				}
				else
				{
					printf("Bitte nochmal versuchen\n");
				}
			}
			else
			{
				userEingabeOkay = true;
				currentgamer->attempts++;
				if (eingabeAsInt == zufzahl)
				{
					//printf("%s hat gewonnen - %s hat die richtige Zahl geraten und hat %d versuche ben\x94tigt.", currentgamer->name, currentgamer->name, currentgamer->attempts);

					printWinner(currentgamer);
					winnerDefined = true;
				}
				if (eingabeAsInt > zufzahl)
				{
					max = eingabeAsInt;
				}
				if (eingabeAsInt < zufzahl)
				{
					min = eingabeAsInt;
				}
			}

		} while (!userEingabeOkay);
	}
}

void printWinner(struct gamer* currentgamer)
{
	printf("%s hat gewonnen - %s hat die richtige Zahl geraten und %d versuche dafuer ben\x94tigt.", currentgamer->name, currentgamer->name, currentgamer->attempts);
}

/// <summary>
/// Liefert eine Zufallszahl im Bereich
/// </summary>
/// <param name="min">Min Wert</param>
/// <param name="max">Max Wert</param>
/// <returns></returns>
int getRandom(int min, int max)
{
	int zufzahl = -1;
	bool randNumberFound = false;
	srand(time(NULL));

	while (!randNumberFound)
	{
		if (zufzahl < max && zufzahl > min)
		{
			randNumberFound = true;
		}
		else
		{
			zufzahl = rand(); // max 32767
		}
	}

	return zufzahl;
}

int addieren(int a, int b)
{
	return a + b;
}

void addierenPtr(int* a, int* b, int* res)
{
	*res = *a + *b;
}

double up_x(int a, double d, float* _f, char bu, char* _bu, char* text)
{
	double derg;

	derg = a + d + *_f + bu, * _bu + text[0];

	return derg;
}

/// <summary>
/// Gets the lenght of a string (char array)
/// </summary>
/// <param name="param">Text</param>
/// <returns></returns>
int schtringlaenge(char* param)
{
	int counter = 0;
	char* firstChar;
	firstChar = &param[0];

	//printf("\nPointer des ersten Zeichens: %p\n", firstChar);

	for (int i = 0; sizeof(param); i++)
	{
		// (index i-1)
		if (counter > 0)
		{
			if (&firstChar[0] == &param[i])
			{
				printf("\n# Vergleich #");
				printf("\n [%c]:%p", firstChar[0], firstChar);
				printf("\n [%c]:%p\n\n", param[i], &param[i]);
				break;
			}
		}

		if (param[i] != '\0')
		{
			printf("Aktueller char: %c - der Poitner dazu: %p\n", param[i], &param[i]);
			counter++;
		}
		else
		{
			i = -1;
			//break;
		}
	}

	return counter;
}

/// <summary>
/// Copy-Function
/// </summary>
/// <param name="t2">Destination</param>
/// <param name="t1">Source</param>
schtringkopie(char* t2, char* t1)
{
	// t2: Destination
	// t1: Source
	for (int i = 0; i <= strlen(t1); i++)
	{
		t2[i] = t1[i];
	}
}



long long _atoi(char* str)
{
	clock_t begin = clock();
	long long res = 0;
	int k = 0;
	int buffer[255];
	int negativ = str[0] == 45 ? 1 : 0;

	// get ascii code from char
	for (int i = 0; str[i] != '\0' || i < strlen(str); i++)
	{
		res = str[i] - '0';
		// filter numbers
		if (res <= 9 && (res > 0)) //(0-9)
		{
			buffer[k] = res;
			k++;
		}
	}

	printf("\nBuffer Length: %d\n", k);
	int base = k - 1; // z.B. 5 --> 10^5 = 100.000
	printf("Power: %d\n", base);

	res = 0;
	int i = 0;

	while (base >= 0)
	{
		long long val = 10;
		if (base == 0)
		{
			val = 1;
		}

		for (int i = 1; i < base; i++)
		{
			val *= 10;
		}

		res += val * buffer[i];
		printf("Current Number with power: %lld +: %10d \n", res, (val * buffer[i]));
		i++;
		base--;
	}

	if (negativ == 1)
	{
		res = res * (-1);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Executiontime {%.2lf} secs\n", time_spent);

	return res;
}

/// <summary>
/// Entry Point
/// </summary>
void mainOld()
{
	//findPrimeNumbers();
	// 
	//editStrings();
	//stringFunctions();
	//searchForCharInString();
	//aufgabeTest();
	//aufgabeTest2();
	// 
	//aufgabeTest3();

	printf("Bitte geben Sie eine Zahl ein\n\n");

	char text[255];

	gets_s(text, sizeof(text));

	long long myNewNumber = _atoi(text);
	printf("\n --> Eingegebene Zahl: %lld\n", myNewNumber);

	hold();
}
