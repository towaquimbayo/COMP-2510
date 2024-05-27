/**
 * File: file_handler.c
 *
 * Author: Towa Quimbayo
 * Date: November 04, 2022
 * Course: COMP 2510 - Procedural Programming
 *
 * Summary of File:
 *
 * This file converts each line of your input file into International and
 * Domestic student structs. It will then filter out the students and print
 * to the output file to the filename that was inserted in command line args
 * depending on the option number you chose.
 */
#include "file_handler.h"

/**
 * Count the number of students by counting new line chars. Doesn't count for 1 character
 * even if its not a new line.
 *
 * @param fptr for input file
 * @return number of students
 */
int countLines(FILE *fptr) {
	char c;
	int count = 0;
	int charactersPerLine = 0;
	while ((c = (char) fgetc(fptr)) != EOF) {
		if (c != ' ') {
			charactersPerLine++;
		}
		if (c == '\n' && charactersPerLine > 1) {
			++count;
			charactersPerLine = 0;
		}
	}
	if (count == 0) {
		printf("%s", "Error: No students in the file.");
		exit(1);
	}
	rewind(fptr);
	return count;
}

/**
 * Prints and writes all valid domestic students that meet the requirements on
 * to the output file.
 *
 * @param domesticStudent for list of domestic students
 * @param outputFile for the filename of the output file
 * @param num for the number of domestic students
 */
void printDomesticStudentList(DomesticStudent *domesticStudent, FILE *outputFile, int num) {
	for (int i = 0; i < num; ++i) {
		if (gpaValidation(domesticStudent[i].gpa)) {
			fprintf(outputFile, "%s %s %1.3f %c\n",
			        domesticStudent[i].firstName,
			        domesticStudent[i].lastName,
			        domesticStudent[i].gpa,
			        domesticStudent[i].status);
			printf("%s %s %1.3f %c\n",
			       domesticStudent[i].firstName,
			       domesticStudent[i].lastName,
			       domesticStudent[i].gpa,
			       domesticStudent[i].status);
		}
	}
}

/**
 * Prints and writes all valid international students that meet the requirements on
 * to the output file.
 *
 * @param internationalStudent for list of international students
 * @param outputFile for the filename of the output file
 * @param num for the number of domestic students
 */
void printInternationalStudentList(InternationalStudent *internationalStudent, FILE *outputFile, int num) {
	for (int i = 0; i < num; ++i) {
		if (gpaValidation(internationalStudent[i].gpa) && toeflValidation(internationalStudent[i].status, internationalStudent[i].toefl)) {
			fprintf(outputFile, "%s %s %1.3f %c %d\n",
			        internationalStudent[i].firstName,
			        internationalStudent[i].lastName,
			        internationalStudent[i].gpa,
			        internationalStudent[i].status,
			        internationalStudent[i].toefl);
			printf("%s %s %1.3f %c %d\n",
			       internationalStudent[i].firstName,
			       internationalStudent[i].lastName,
			       internationalStudent[i].gpa,
			       internationalStudent[i].status,
			       internationalStudent[i].toefl);
		}
	}
}

/**
 * Prints and writes all valid students that meet the requirements on
 * to the output file.
 *
 * @param students for list of all students including international and domestic
 * @param outputFile for the filename of the output file
 * @param num for the number of domestic students
 */
void printAllStudentList(Students *students, FILE *outputFile, int num) {
	for (int i = 0; i < num; ++i) {
		if (gpaValidation(students[i].gpa) && toeflValidation(students[i].status, students[i].toefl)) {
			if (students[i].status == 'D') {
				fprintf(outputFile, "%s %s %1.3f %c\n",
				        students[i].firstName,
				        students[i].lastName,
				        students[i].gpa,
				        students[i].status);
				printf("%s %s %1.3f %c\n",
				       students[i].firstName,
				       students[i].lastName,
				       students[i].gpa,
				       students[i].status);
			} else {
				fprintf(outputFile, "%s %s %1.3f %c %d\n",
				        students[i].firstName,
				        students[i].lastName,
				        students[i].gpa,
				        students[i].status,
				        students[i].toefl);
				printf("%s %s %1.3f %c %d\n",
				       students[i].firstName,
				       students[i].lastName,
				       students[i].gpa,
				       students[i].status,
				       students[i].toefl);
			}
		}
	}
}

/**
 * Validation check for students who have gpa higher than 3.9
 *
 * @param gpa for given gpa value from a student
 * @return 1 if the student gpa is valid, 0 if not
 */
int gpaValidation(float gpa) {
	return (gpa >= 3.9f) ? 1 : 0;
}

/**
 * Validation check for students who have a toefl grade
 * that is higher than 70. Domestic students don't matter so
 * returns 1 as default.
 *
 * @param status for given status value from a student
 * @param toefl for given toefl value from a student
 * @return 1 if the student toefl is valid, 0 if not
 */
int toeflValidation(char status, int toefl) {
	if (status == 'D') {
		return 1;
	} else {
		return (toefl >= 70) ? 1 : 0;
	}
}

/**
 * Creates the student structs by mapping each attributes using fscanf.
 * Checks if each attribute is valid and then maps to the valid student type struct.
 * We do a switch case in the end to print and write the valid filtered students on
 * to the output file depending on the option number.
 *
 * @param fptr for input file
 * @param outputFile for output file
 * @param option for the option number
 */
void fillStruct(FILE *fptr, FILE *outputFile, int option) {
	int numOfStudents = countLines(fptr);
	InternationalStudent *internationalStudent = malloc(sizeof(InternationalStudent) * (numOfStudents));
	DomesticStudent *domesticStudent = malloc(sizeof(InternationalStudent) * (numOfStudents));
	Students *students = malloc(sizeof(InternationalStudent) * (numOfStudents));

	// Store Structs
	int domStuCount = 0; // Number of domestic students
	int intStuCount = 0; // Number of international students
	for (int i = 0; i < numOfStudents; ++i) {
		char firstName[15];
		char lastName[25];
		float gpa;
		char status;
		int toefl;
		int isDomestic = 0;

		int scannedItems = fscanf(fptr,"%s %s %f %c %d", firstName, lastName, &gpa, &status, &toefl);

		if (scannedItems < 4 || scannedItems > 5) {
			printf("%s %s!", "Error: Missing fields or extra fields for the Student:", firstName);
			exit(1);
		} else if (status == 'I' && scannedItems != 5) {
			printf("%s %s!", "Error: Missing fields for the International Student:", firstName);
			exit(1);
		} else if (status == 'D' && scannedItems != 4) {
			printf("%s %s!", "Error: Missing fields for the Domestic Student:", firstName);
			exit(1);
		} else if (strlen(firstName) > 15) {
			printf("%s", "Error: The first name must be 15 or less characters");
			exit(1);
		} else if (strlen(lastName) > 25) {
			printf("%s", "Error: The last name must be 25 or less characters");
			exit(1);
		} else if (gpa < 0 || gpa > 4) {
			printf("%s", "Error: GPA must be within the range of 0 to 4!");
			exit(1);
		} if (status != 'I' && status != 'D') {
			printf("%s", "Error: Student's status must be represented by 'I' or 'D'.");
			exit(1);
		} else if (status == 'I' && !(toefl >= 0 && toefl <= 120)) {
			printf("%s", "Error: Invalid TOEFL score for one of the students. Must be within range of 0 to 120!");
			exit(1);
		}

		if (status == 'D') {
			strcpy(domesticStudent[domStuCount].firstName, firstName);
			strcpy(domesticStudent[domStuCount].lastName, lastName);
			domesticStudent[domStuCount].gpa = gpa;
			domesticStudent[domStuCount].status = status;
			isDomestic = 1;
			++domStuCount;
		} else {
			strcpy(internationalStudent[intStuCount].firstName, firstName);
			strcpy(internationalStudent[intStuCount].lastName, lastName);
			internationalStudent[intStuCount].gpa = gpa;
			internationalStudent[intStuCount].status = status;
			internationalStudent[intStuCount].toefl = toefl;
			++intStuCount;
		}

		// Store all students
		if (isDomestic) {
			strcpy(students[i].firstName, domesticStudent[domStuCount - 1].firstName);
			strcpy(students[i].lastName, domesticStudent[domStuCount - 1].lastName);
			students[i].gpa = domesticStudent[domStuCount - 1].gpa;
			students[i].status = domesticStudent[domStuCount - 1].status;
		} else {
			strcpy(students[i].firstName, internationalStudent[intStuCount - 1].firstName);
			strcpy(students[i].lastName, internationalStudent[intStuCount - 1].lastName);
			students[i].gpa = internationalStudent[intStuCount - 1].gpa;
			students[i].status = internationalStudent[intStuCount - 1].status;
			students[i].toefl = internationalStudent[intStuCount - 1].toefl;
		}
	}

	// Filter students by minimum requirements and option
	switch (option) {
		case 1:
			// only saves the filtered output of domestic students
			printf("%s %d%s", "Your option was", option, ", so we filter for all Domestic Students.\n\n");
			printDomesticStudentList(domesticStudent, outputFile, domStuCount);
			break;
		case 2:
			// only saves the filtered output of international students
			printf("%s %d%s", "Your option was", option, ", so we filter for International Students.\n\n");
			printInternationalStudentList(internationalStudent, outputFile, intStuCount);
			break;
		case 3:
			// only saves the output of all students
			printf("%s %d%s", "Your option was", option, ", so we filter for All Students.\n\n");
			printAllStudentList(students, outputFile, numOfStudents);
			break;
	}

	free(internationalStudent);
	free(domesticStudent);
	free(students);
}

/**
 * Checks if option is a valid number and calls the fill struct to
 * map and create the student structs.
 *
 * @param fptr for input file
 * @param outputFile for output file
 * @param option for the option number
 */
int file_handler(FILE *fptr, FILE *outputFile, int option) {
	if (option < 1 || option > 3) {
		printf("%s", "Error: Invalid option value. Please choose an integer between 1, 2 or 3.");
		exit(1);
	}
	fillStruct(fptr, outputFile, option);
	return 0;
}