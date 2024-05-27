/**
 * File: lab6.c
 *
 * Author: Towa Quimbayo
 * Date: November 04, 2022
 * Course: COMP 2510 - Procedural Programming
 *
 * Summary of File:
 *
 * This creates 2 file pointers, 1 for reading the input and 1 for creating a new output file.
 * The main method calls the file_handler method that will print the students according
 * to the option on to the output file.
 */
#include "file_handler.h"

/**
 * int main(int argc, char **argv)
 *
 * Summary of main function:
 *
 * Get the input and output file name from command line args and the option that they choose to print.
 *
 * Preconditions: FILE *inputFp must be a valid file where each line consists of valid attributes for
 * the students. FILE *outFp doesn't need to exist but if it does, the file will be overwritten by the output.
 * The file must end with a new line character.
 *
 * Return Value: 0 no errors
 *
 * Postconditions: Calls the file_handler method and prints the students.
 * @param argc argument count
 * @param **argv for input and output file, and option number between 1 and 3
 *
 */
int main(int argc, char **argv) {
	if (argc != 4) {
		printf("%s", "Error: Please write both the input and output filename, along with your option. (1, 2 or 3)");
		exit(1);
	}

	FILE *inputFp, *outFp;
	inputFp = fopen(argv[1], "r");
	if (inputFp == NULL) {
		printf("%s", "Error: No file found.");
		exit(1);
	} else if (fgetc(inputFp) == EOF) {
		printf("%s", "Error: Nothing in file.");
		exit(1);
	}
	rewind(inputFp);

	outFp = fopen(argv[2], "w");

	file_handler(inputFp, outFp, atoi(argv[3]));

	fclose(inputFp);
	fclose(outFp);
	return 0;
}