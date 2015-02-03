#include <stdio.h>
#include <stdlib.h>

//terminal text colors
#define RED_COLOR "\x1B[31m"
#define GREEN_COLOR "\x1B[32m"
#define BLUE_COLOR "\x1B[34m"
#define WHITE_COLOR "\x1B[37m"
#define debugMessage printf

//typedefs
typedef unsigned short int bool;
typedef unsigned short int ushort;
typedef unsigned short int bitwise;
typedef struct {ushort row; ushort column;} Coordinate;

//function prototypes
void printState(void);
bool simpleFill(void);
Coordinate consistencyCheck(void);
Coordinate convertCartToBox(Coordinate);
Coordinate convertBoxToCart(Coordinate);

//Debug
void testFillBox(void);
void testFillRow(void);

//global variables
ushort **table;

int main(int argc, char** argv)
{
	table = malloc(9 * sizeof(void*));
	ushort i;
	for (i = 0; i < 9; i++)
	{
		table[i] = calloc(9, sizeof(ushort));
	}	
	testFillRow();
	while(1)
	{
		ushort row, column, value;
		scanf("%1hu %1hu %1hu", &row, &column, &value);
		if (value == 0)
			break;
		else if (row >= 9 || row <= -1 || column >= 9 || column <= -1 || value >= 10 || value <= 0)
			continue;
		table[row][column] = value;
		Coordinate dummy = consistencyCheck();
		printf("\nconsistency vector:<%hu,%hu>\n", dummy.row, dummy.column);
	}
	printState();
	simpleFill();
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
	printf("\n");
	for (i = 0; i < 9; i++)
	{
		if (i%3 == 0)
			printf("==========================================================================");
		else
			printf("||------+-------+-------||------+-------+-------||------+-------+-------||");
		printf("\n||\t|\t|\t||\t|\t|\t||\t|\t|\t||\n|");
		for (j = 0; j < 9; j++)
		{
			if (j%3 == 0)
				printf("|");
			printf("   %hu\t|", table[i][j]);
		}
		printf("|\n||\t|\t|\t||\t|\t|\t||\t|\t|\t||\n");
	}
	printf("==========================================================================");
}

bool simpleFill()
{
	int i, j, k;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (table[i][j] != 0) continue;
			bitwise taken = 0xfe00;
			for (k = 0; k < 9; k++)
			{
				ushort temp;

				//row fill	
				temp = table[i][k];
				if (temp != 0)
					taken |= (0x0001<<(temp-1));

				//column fill
				temp = table[k][j];
				if (temp != 0)
					taken |= (0x0001<<(temp-1));

				//box fill
				Coordinate cartCoord = {i, j};
				Coordinate boxCoord = convertCartToBox(cartCoord);
				boxCoord.column = k;
				Coordinate tempCartCoord = convertBoxToCart(boxCoord);
				temp = table[tempCartCoord.row][tempCartCoord.column];
				if (temp != 0)
					taken |= (0x0001<<(temp-1));
			}
			taken = ~taken;
			if (i == 1 && j == 1)
			{
				debugMessage("\ntaken bit for <%hu,%hu> is %x\n", i, j, taken);
			}
			if ((taken & (taken - 1)) == 0)
			{	
				debugMessage("\nSingle set bit.");
				ushort setBitPosition = 0;
				for (k = 0; k < 9; k++)	
				{
					if ((taken >> setBitPosition) & 0x0001)
					{
						table[i][j] = setBitPosition + 1;					
						break;
					}
					setBitPosition++;
				}
			}
		}
	}
}

Coordinate consistencyCheck()
{
	int i, j;
	Coordinate returnCoordinate = {10, 10};
	for (i = 0; i < 9; i++)
	{
		ushort *rowArray = calloc(9, sizeof(ushort));
		ushort *columnArray = calloc(9, sizeof(ushort));
		ushort *boxArray = calloc(9, sizeof(ushort));

		for (j = i; j < 9; j++)
		{
			ushort temp;
			
			//row check
			temp = table[i][j];
			if (temp <= 9 && temp >= 1)
			{
				if (rowArray[temp] >= 1)
				{
					returnCoordinate.row = i;
					returnCoordinate.column = j;
					return returnCoordinate;
				}
				else
					rowArray[temp]++;
			}

			//column check
			temp = table[j][i];
			if (temp <= 9 && temp >= 1)
			{
				if (columnArray[temp] >= 1)
				{
					returnCoordinate.row = j;
					returnCoordinate.column = i;
					return returnCoordinate;
				}
				else
					columnArray[temp]++;
			}

			//box check
			Coordinate boxCoord = {i, j};
			Coordinate cartCoord = convertBoxToCart(boxCoord);
			temp = table[cartCoord.row][cartCoord.column];
			if (temp <= 9 && temp >= 1)	
			{
				if (boxArray[temp] >= 1)
				{
					returnCoordinate = cartCoord;
					return returnCoordinate;
				}
				else
					boxArray[temp]++;				
			}
		}
		free(rowArray);
		free(columnArray);
		free(boxArray);
	}
	return returnCoordinate;
}

Coordinate convertCartToBox(Coordinate argCoordinate)
{
	ushort x = argCoordinate.row;
	ushort y = argCoordinate.column;
	Coordinate returnCoord = {y / 3 + 3 * (x / 3), (y%3 + 3 * x)%9};
	return returnCoord;
}

Coordinate convertBoxToCart(Coordinate argCoordinate)
{
	ushort u = argCoordinate.row;
	ushort v = argCoordinate.column;
	Coordinate returnCoord = {(u/3) * 3 + v/3, (u%3) * 3 + v%3};
	return returnCoord;
}

void testFillBox()
{
	table[0][0] = 1;
	table[0][1] = 2;
	table[0][2] = 3;
	table[1][0] = 4;
	table[1][2] = 6;
	table[2][0] = 7;
	table[2][1] = 8;
	table[2][2] = 9;
}

void testFillRow()
{
	table[0][0] = 1;
	table[0][1] = 2;
	table[0][2] = 3;
	table[0][3] = 4;
	table[0][5] = 6;
	table[0][6] = 7;
	table[0][7] = 8;
	table[0][8] = 9;
}
