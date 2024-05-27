/**
 * File: lab4.c
 *
 * Author: Towa Quimbayo
 * Date: October 6, 2022
 * Course: COMP 2510 - Procedural Programming
 *
 * Summary of File:
 *
 * This file converts converts 'n' rows and 'm' columns of binary digits into
 * decimal values. The file scans the first line whereas the first integer would
 * indicate 'n' rows and second integer would indicate 'm' columns. Starting from
 * second line, each line will contain binary digits separated by one space and
 * each line will be converted to a decimal value and get printed.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * void printBinaryToDecimal(FILE *fptr)
 *
 * Summary of printBinaryToDecimal function:
 *
 * Scans first line for 2 integers for rows and columns
 * then scans the rest of the lines and converts the binary
 * digit to decimal line by line and gets printed.
 *
 * Preconditions: FILE *fptr must be a valid file that contains
 * 2 integers greater than 0 on the first line and rest of the lines
 * will be only binary digits separated by spaces. The first integer
 * on the first line must match the number of rows that the file has
 * after the first line, and second integer on the first line must
 * match the number of columns per line of binary digits.
 *
 * Return Value: Nothing (void)
 *
 * Postconditions: converts and prints the binary digits to decimal value.
 * @param fptr for file pointer from main method
 *
 */
void printBinaryToDecimal(FILE *fptr) {
	if (fptr == NULL) {
		printf("%s", "The file doesn't exist.");
		exit(1);
	} else if (fgetc(fptr) == EOF) {
		printf("%s", "You have a file with no characters!");
		exit(1);
	}

	rewind(fptr);

	char firstLineNums[100];

	// Get first line of all characters, reach end of first new line char
	fscanf(fptr, "%[^\n]", firstLineNums);

	// Check if the scanned first line is more than 100 characters
	if (strlen(firstLineNums) >= 100) {
		printf ("%s", "Your first line in the file contains more than 100 characters!");
		exit(1);
	}

	char delimeter[] = " ";
	char* token = strtok(firstLineNums, delimeter);
	int numRows = -1;
	int numCols = -1;

	// Loop through the first line delimiting the space characters and assign numRows and numCols
	while (token != NULL) {
		if (atoi(token) > 0) {
			if (numRows == -1) {
				numRows = atoi(token);
			} else if (numCols == -1) {
				numCols = atoi(token);
			} else {
				printf("%s", "You have entered more than 2 integers on the first line!");
				exit(1);
			}
		}
		token = strtok(NULL, delimeter);
	}

	/**
	 * Check if numsRows and numCols have been assigned.
	 * If not, then we can conclude the user has entered invalid integers
	 * on the first line of the file.
	 */
	if (numRows == -1 || numCols == -1) {
		printf("%s", "The 2 integers you have entered on the first line must be a positive integer greater than 0!");
		exit(1);
	}

	//printf("Num Rows: %d \n", numRows);
	//printf("Num Cols: %d \n", numCols);

	char eachBinaryDigit = 0;
	char lineArr[numCols];
	int count = 0;
	int checkEmptyRows = 0;
	while ((eachBinaryDigit = fgetc(fptr)) != EOF) {
		// Check if its binary digit
		if (eachBinaryDigit == '0' || eachBinaryDigit == '1') {
			lineArr[count] = eachBinaryDigit;
			count++;
			if (count == numCols) {
				char binaryNum[numCols];
				// Remove any garbage characters
				for (int i = 0; i < count; i++) {
					binaryNum[i] = lineArr[i];
				}

				// Convert the array from binary to decimal and print
				int decimalValue = 0;
				int base = 1;
				int temp = atoi(binaryNum);
				while (temp > 0) {
					int lastDigit = temp % 10;
					temp = temp / 10;
					decimalValue += lastDigit * base;
					base *= 2;
				}
				printf("%d\n", decimalValue);
				checkEmptyRows++;
			}
		} else if ((eachBinaryDigit == '\n' || eachBinaryDigit == EOF) && count % numCols != 0) {
			// Check if any missing columns
			printf("%s", "Your column integer value does not match the number of binary digits per line!");
			exit(1);
		} else if (count % numCols == 0) {
			// Reset the array
			count = 0;
			//printf("\n");
		}
	}

	if (numRows > checkEmptyRows) {
		printf("You are missing %d row(s)!", (numRows - checkEmptyRows));
		exit(1);
	} else if (numRows < checkEmptyRows) {
		printf("You have %d extra row(s)!", (checkEmptyRows - numRows));
		exit(1);
	}
}

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");

	printBinaryToDecimal(fp);

	fclose(fp);
	return 0;
}
