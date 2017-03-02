#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 9

/* NOTE: You will have to code the 2 functions BELOW "checkDups" and "clearArray"
before running this program to see the generated output.
*/
int checkDups(int nums[], int num, int n);		/* given an array of 'n' elements, this function determines if the
														value 'num' is already present within the array 'nums'*/
void clearArray(int nums[], int n);			/* Sets all 'n' values in the 'nums' array to 0 */

int genSudokuNumbers(int grid[]);	/* already coded */

void genSudokuBoard(int grid[], int display[]);		/*Picks 4 random numbers from the grid and copies them into display*/
void displaySudokuBoard(int display[], int bigOh);	/*displays the valid numbers and the whole Sudoku board to the screen*/
void getRandNum(int low, int high, int *pn);		/*randomly picks a number from 1 to 9 and updates the pn variable*/
void printSudokuBoardToFile(int display[], const char *fileName);		/*Writes the Sudoku board and valid numbers 
																		to the filename*/
int main() 
{
	int grid[N*N], display[N*N] = { 0 };
	int loops, low = 1, high = 9, pn = 0;
	const char fileName[] = { "Assignment3_SebastianVieira.txt" };

	loops = genSudokuNumbers(grid); /* students must add code to return the correct
									value for all instructions executed in all loops */
	genSudokuBoard(grid, display);
	displaySudokuBoard(grid, loops);
	getRandNum(low, high, &pn);
	printSudokuBoardToFile(display, fileName);

	return 0;
}

int checkDups(int nums[], int num, int n) 
{
	int valid = 0;
	int i;

	for (i = 0; i < n; i++)
	{
		if (nums[i] != num)
		{
			valid = 0;
		}
		else
		{
			valid = 1;
			i = n;
		}
	}
	return valid;
}

void clearArray(int nums[], int n) 
{
	int i;
	for (i = 0; i < n; i++)
	{
		nums[i] = 0;
	}
}

int genSudokuNumbers(int grid[]) 
{
	int c, i, j, rowNum, colNum, blockNum;
	int test[N], dup, temp, valid, cnt, iterations = 0;

	srand((int)time(NULL));         /* seeding the random number generator */
	for (i = 0; i<N*N; i++) 
	{								 /* initializing the grid array to all 0's */
		grid[i] = 0;
		
	}
	iterations++;
	for (c = 0; c<N*N; c++) 
	{     /* main loop to generate N*N numbers for the grid */
		temp = rand() % N + 1; /* generate random # from 1 to N inclusive */
		valid = dup = cnt = 0;
		iterations++;
		while (!valid) 
		{         /* keep looping as long as the 'valid' flag is false */
			clearArray(test, N);
			/* the calculations below determine the row, col,
			and block numbers (index 0 to 8) based on the
			linear index variable 'c' */
			rowNum = c / N;
			colNum = c % N;
			blockNum = (rowNum / 3) * 3 + (colNum / 3);
			iterations++;
			/* now check to see if the number 'temp' is a
			duplicate in the row, column, and block to which
			'c' corresponds */

			for (j = 0; j<colNum; j++) 
			{										/* fill row (but only up to colNum) */
				test[j] = grid[rowNum*N + j];
				
			}
			dup += checkDups(test, temp, colNum);
			iterations++;
			if (!dup) 
			{                   /* row is valid, now check column */
				clearArray(test, N);
				for (j = 0; j<rowNum; j++) 
				{ /* fill column (but only up to rowNum) */
					test[j] = grid[j*N + colNum];
					
				}
				dup += checkDups(test, temp, rowNum);
				iterations++;
				if (!dup) 
				{                /* column is valid now check block */
					clearArray(test, N);

					for (j = 0; j<N; j++) 
					{
						test[j] = grid[((blockNum / 3)*N * 3) + (colNum / 3) * 3 + (j / 3)*N + j % 3];
						
					}
					/* equation used to generate array
					coordinates for all N blocks
					(i.e.)
					0, 1, 2,   9, 10, 11,  18, 19, 20  {blk 0}
					3, 4, 5,  12, 13, 14,  21, 22, 23  {blk 1}
					6, 7, 8,  15, 16, 17,  24, 25, 26  {blk 2}

					27, 28, 29, 36, 37, 38, 45, 46, 47 {blk 3}
					30, 31, 32, 39, 40, 41, 48, 49, 50
					33, 34, 35, 42, 43, 44, 51, 52, 53

					54, 55, 56, 63, 64, 65, 72, 73, 74
					57, 58, 59, 66, 67, 68, 75, 76, 77
					60, 61, 62, 69, 70, 71, 78, 79, 80 {blk 8}
					*/
					dup += checkDups(test, temp, N);
					
				}
				iterations++;
			}
			if (!dup) 
			{					/* no duplicates in row, column, or block, so number
											can be inserted into the grid */
				grid[c] = temp;
				valid = 1;
				cnt = 0;
				
				
			}
			else 
			{     /* duplicate number found, so reset flags and generate
					   new random number */
				temp = rand() % N + 1;
				dup = 0;
				cnt++;
				
			}
			iterations++;
			if (cnt > N*N) 
			{
								/* if after N*N attempts, no possible value is found
								then reset the entire array and start over
										(brute force algorithm)
										average runtime: 500000 iterations */
				dup = cnt = 0;
				valid = 1;
				clearArray(grid, N*N);
				temp = rand() % N + 1;
				c = -1; /* will be reset to 0 in for loop */
				
			
			}
		
		}
		
	} 
	
	return iterations; /* 'iterations' must be updated within this function BEFORE it is returned */
}

void displaySudokuBoard(int display[], int bigOh)
{
	int i;

	printf("PLAY IPC144 SUDOKU\n");
	printf("+------+------+------+\n");
	
	for (i = 0; i<N*N; i++)				/* displaying all N*N numbers in the 'grid' array */
	{								
		if (i%N == 0 && i != 0)
		{
			printf("|");				/* printing a newline for every multiple of N */
			printf("\n");
			
			if (i == 27 || i == 54)
			{
				printf("+------+------+------+\n");
			}
			
			printf("|");
		}
		else if (i % 3 == 0)
		{
			printf("|");
		}
		
		printf("%d ", display[i]);
		
	}
	if (i == 81)
	{
		printf("|\n");
		printf("+------+------+------+\n");
	}

	printf("Total Instructions:%d ", bigOh);		/*displays the number of instructions*/
}

void genSudokuBoard(int grid[], int display[])
{
	int index, r, filled, dup[4] = { 0 };
	int indexnumber[N][N] = { { 0, 1, 2, 9, 10, 11, 18, 19, 20 }, { 3, 4, 5, 12, 13, 14, 21, 22, 23 }, { 6, 7, 8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 }, { 30, 31, 32, 39, 40, 41, 48, 49, 50 }, { 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 }, { 57, 58, 59, 66, 67, 68, 75, 76, 77 }, { 60, 61, 62, 69, 70, 71, 78, 79, 80 } };
	
	for (index = 0; index < N; index++)
	{
		filled = 0;

		while (filled < 4)
		{
			
			r = indexnumber[index][rand() % N];
			dup[filled] = r;
			filled++;

			if (filled == 4)			/*checks to see if there are any duplicates*/
			{
				if (dup[0] == dup[1] || dup[0] == dup[2] || dup[0] == dup[3])
				{
					filled = 0;
				}
				else if (dup[1] == dup[0] || dup[1] == dup[2] || dup[1] == dup[3])
				{
					filled = 0;
				}
				else if (dup[2] == dup[0] || dup[2] == dup[1] || dup[2] == dup[3])
				{
					filled = 0;
				}
				else if (dup[3] == dup[0] || dup[3] == dup[1] || dup[3] == dup[2])
				{
					filled = 0;
				}
				else
				{
					display[dup[0]] = grid[dup[0]];
					display[dup[1]] = grid[dup[1]];
					display[dup[2]] = grid[dup[2]];
					display[dup[3]] = grid[dup[3]];
					
				}
			}
		
		}	

	}
	
}

void getRandNum(int low, int high, int *pn)			
{
	
	*pn = rand() % high + low;
}

void printSudokuBoardToFile(int display[], const char *filename)		
{
	FILE *fp = NULL;
	int i;

	fp = fopen(filename, "w");

	if (fp != NULL)
	{
		fprintf(fp, "PLAY IPC144 SUDOKU\n");
		fprintf(fp, "+------+------+------+\n");

		for (i = 0; i < N*N; i++)
		{								
			if (i%N == 0 && i != 0)
			{
				fprintf(fp, "|");				
				fprintf(fp,"\n");

				if (i == 27 || i == 54)
				{
					fprintf(fp, "+------+------+------+\n");
				}

				fprintf(fp, "|");
			}
			else if (i % 3 == 0)
			{
				fprintf(fp, "|");
			}

			if (display[i] != 0)
			{
				fprintf(fp, "%d ", display[i]);
			}
			else
			{
				fprintf(fp, "  ");
			}
		
		}
		if (i == 81)
		{
			fprintf(fp, "|\n");
			fprintf(fp, "+------+------+------+\n");
		}
	}
	else
	{
		printf("Failed to open File\n");
	}
	fclose(filename);
}