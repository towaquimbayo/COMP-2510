#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char firstName[15];
	char lastName[25];
	float gpa;
	char status;
} DomesticStudent;

typedef struct {
	char firstName[15];
	char lastName[25];
	float gpa;
	char status;
	int toefl;
} InternationalStudent;

typedef struct {
	char firstName[15];
	char lastName[25];
	float gpa;
	char status;
	int toefl;
} Students;

int countLines(FILE *fptr);
void printDomesticStudentList(DomesticStudent *domesticStudent, FILE *outputFile, int num);
void printInternationalStudentList(InternationalStudent *internationalStudent, FILE *outputFile, int num);
void printAllStudentList(Students *students, FILE *outputFile, int num);
int gpaValidation(float gpa);
int toeflValidation(char status, int toefl);
void fillStruct(FILE *fptr, FILE *outputFile, int option);
int file_handler(FILE *fptr, FILE *outputFile, int option);