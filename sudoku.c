#include <stdio.h>
#include <stdlib.h>

//terminal text colors
#define RED_COLOR "\x1B[31m"
#define GREEN_COLOR "\x1B[32m"
#define BLUE_COLOR "\x1B[34m"
#define WHITE_COLOR "\x1B[37m"

//function prototypes
void printState(void);
int consistencyCheck(void);

//global variables
unsigned short int **table;

int main(int argc, char** argv)
{
	table = malloc(9 * sizeof(void*));
	int i;
	for (i = 0; i < 9; i++)
	{
		table[i] = malloc(9 * sizeof(unsigned short int));
		int j;
		for (j = 0; j < 9; j++)
		{
			table[i][j] = 0;
		}
	}
	printf("%s%lu%s\n", RED_COLOR, sizeof(unsigned char), WHITE_COLOR);
	while(1)
	{
		unsigned short int row, column, value;
		scanf("%1hu %1hu %1hu", &row, &column, &value);
		if (value == 0)
			break;
		else if (row >= 9 || row <= -1 || column >= 9 || column <= -1 || value >= 10 || value <= 0)
			continue;
		table[row][column] = value;
	}
	printState();
	int a; scanf("%i", &a);
	return 0;
}

void printState()
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		if (i%3 == 0)
			printf("\n\n ========================================================================\n\n|");
		else
			printf("\n\n ------------------------------------------------------------------------\n\n|");

		for (j = 0; j < 9; j++)
		{
			if (j%3 == 0)
				printf("|");
			printf("   %hu\t|", table[i][j]);
		}
	}
	printf("\n\n ========================================================================\n\n");
}
