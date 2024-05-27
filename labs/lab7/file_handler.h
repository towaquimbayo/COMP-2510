#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students {
	char *firstName;
	char *lastName;
	float gpa;
	char status;
	int toefl;
	struct Students *next;
} Students;

int countLines(FILE *fptr);
void printStudents(struct Students *students, FILE *outputFile, int option);
int gpaValidation(float gpa);
int toeflValidation(char status, int toefl);
void fillStruct(FILE *fptr, FILE *outputFile, int option);
int file_handler(FILE *fptr, FILE *outputFile, int option);