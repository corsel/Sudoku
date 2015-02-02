#include <stdio.h>
#include <stdlib.h>

//terminal text colors
#define RED_COLOR "\x1B[31m"
#define GREEN_COLOR "\x1B[32m"
#define BLUE_COLOR "\x1B[34m"
#define WHITE_COLOR "\x1B[37m"

//typedefs
typedef unsigned short int bool;
typedef unsigned short int ushort;

//function prototypes
void printState(void);
ushort consistencyCheck(void);

//global variables
ushort **table;

int main(int argc, char** argv)
{
	table = malloc(9 * sizeof(void*));
	int i;
	for (i = 0; i < 9; i++)
	{
		table[i] = calloc(9, sizeof(ushort));
	}
	while(1)
	{
		ushort row, column, value;
		scanf("%1hu %1hu %1hu", &row, &column, &value);
		if (value == 0)
			break;
		else if (row >= 9 || row <= -1 || column >= 9 || column <= -1 || value >= 10 || value <= 0)
			continue;
		table[row][column] = value;
	}
	printState();
	for (i = 0; i < 9; i++)
	{
		free(table[i]);
	}
	free(table);
	int a; scanf("%i", &a);
	return 0;
}

void printState()
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		if (i%3 == 0)
			printf("=========================================================================");
		else
			printf("------------------------------------------------------------------------");
		printf("\n||\t|\t|\t||\t|\t|\t||\t|\t|\t||\n|");
		for (j = 0; j < 9; j++)
		{
			if (j%3 == 0)
				printf("|");
			printf("   %hu\t|", table[i][j]);
		}
		printf("|\n||\t|\t|\t||\t|\t|\t||\t|\t|\t||\n");
	}
	printf("=========================================================================");
}

ushort consistencyCheck()
{
	ushort *rowArray = calloc(9, sizeof(ushort));
	ushort *columnArray = calloc(9, sizeof(ushort));
	ushort *boxArray = calloc(9, sizeof(ushort));
	
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			//row
		}
	}

	free(rowArray);
	free(columnArray);
	free(boxArray);
}
