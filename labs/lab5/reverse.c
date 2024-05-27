/**
 * File: lab5.c
 *
 * Author: Towa Quimbayo
 * Date: October 30, 2022
 * Course: COMP 2510 - Procedural Programming
 *
 * Summary of File:
 *
 * This file reverses the order of words in the file recursively, although its incomplete
 * and currently only reverses the characters in the file.
 */
#include "reverse.h"

/**
 * int recursive(FILE *fptr)
 *
 * Summary of recursive function:
 *
 * Read the file from the end to beginning and get each character
 * and print recursively. The idea is to detect the word when the
 * character is a space or new line, and print recursively so that
 * it would print the reverse order of words.
 *
 * Preconditions: FILE *fptr must be a valid file that contains
 * a string of anything. The file must end with a new line character.
 *
 * Return Value: 0 if it works
 *
 * Postconditions: Prints the reverse order of words in the file.
 * @param fptr for file pointer from main method
 *
 */
int recursive(FILE *fptr) {
	fseek(fptr, pos, SEEK_END);
	char c = (char) fgetc(fptr);

	if (c != EOF) {
		fseek(fptr, --pos, SEEK_CUR); // seek from end to beginning
		if (c != '\n') {
			if (c != ' ') {
				printf("%c", c);
				recursive(fptr); // prints reverse characters for the word at the moment
			} else {
				printf("%c", ' '); // if it's a space, print space
			}
			recursive(fptr); // repeat all of this until eof
		} else {
			printf("\n");
		}
	}
	return 0;
}