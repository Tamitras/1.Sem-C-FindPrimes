#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>
#include "Helper.h"

void printDatum()
{
	time_t rawtime;
	struct tm* info;
	time(&rawtime);
#pragma warning(suppress : 4996)
	info = localtime(&rawtime);

#pragma warning(suppress : 4996)
	printf("\n\nCurrent local time and date: %s", asctime(info));

	//printf("Aktuelles Datum: %s",currentTime);
}

void hold()
{
	char s[80];
	char temp[255];
	char exit[255];

	strcpy_s(temp, sizeof(temp), "en");
	strcpy_s(exit, sizeof(exit), "Schlie\xe1");

	strcat_s(exit, sizeof(exit), temp);

	//printDatum();
	printf("\n%s mit Enter...", exit);
	fgets(s, sizeof s, stdin);
}



