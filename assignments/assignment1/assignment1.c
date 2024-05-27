#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Do NOT change this function's signature including spaces
void formatAndPrintParagraph(FILE *fptr, int lineLength) {
	if (fptr == NULL) {
		printf("%s", "The file doesn't exist.");
		exit(1);
	} else if (fgetc(fptr) == EOF) {
		printf("%s", "You have a file with no characters!");
		exit(1);
	} else if (lineLength < 1) {
		printf("%s", "The line length must be integer value greater than 0!");
		exit(1);
	}

	// Count how many words in the file
	char eachChar;
	int totalChars = 0;
	int totalWordCount = 0;
	while ((eachChar = fgetc(fptr)) != EOF) {
		//printf("%c\n", eachChar);
		totalChars++;
		// Check these conditions to count words
		if (eachChar == ' ' || eachChar == '\t' || eachChar == '\n' || eachChar == '\0') {
			totalWordCount++;
		}
	}

	// Increment totalWordCount for last word if the file is not empty
	if (totalChars > 0) {
		totalWordCount++;
	} else if (totalWordCount == 0) {
		totalWordCount = 1;
	}

	// Reset the file
	rewind(fptr);

	const int MAX_WORD_LENGTH = lineLength;
	int currWordCount = 0, currCharCount = 0;
	char wordArray[totalWordCount][MAX_WORD_LENGTH];

	// If there is only one word
	if (totalWordCount == 1) {
		while ((eachChar = fgetc(fptr)) != EOF) {
			printf("%c", eachChar);
		}
		return;
	}

	// Store each word as a row in the char array
	while ((eachChar = fgetc(fptr)) != EOF) {
		if (eachChar == ' ' || eachChar == '\t' || eachChar == '\n' || eachChar == '\0' || eachChar == EOF) {
			// Terminate the string and start a new line
			wordArray[currWordCount][currCharCount] = '\0';

			// Reset the currCharCount
			currCharCount = 0;
			currWordCount++;
		}
		else {
			wordArray[currWordCount][currCharCount] = eachChar;
			//printf("%c ", wordArray[currWordCount][currCharCount]);

			if (currCharCount < lineLength) {
				currCharCount++;
			} else {
				printf("\n%s%d", "One of the words is longer than the line length of ", lineLength);
				exit(1);
			}
		}
	}

	// Justify the paragraph
	for (int i = 0; i < totalWordCount; i++) {
		int totalCharsPerLine = 0, numOfWordsThatFit = 0;
		// Check if it doesn't overflow
		while (((totalCharsPerLine + strlen(wordArray[i + numOfWordsThatFit])) <= lineLength)
				&& (numOfWordsThatFit + i < totalWordCount)) {
			// Add number of characters per word and 1 for space until it hits the line length
			totalCharsPerLine += strlen(wordArray[i + numOfWordsThatFit]) + 1;
			numOfWordsThatFit++;
		}

		// Remove the extra space character that was counted above
		totalCharsPerLine--;

		int numSpacesNeeded = lineLength - totalCharsPerLine;

		//printf("\nNumber of Spaces: %d, Number of Words: %d, Total Chars: %d\n", numSpacesNeeded, numOfWordsThatFit, totalCharsPerLine);

		if (numSpacesNeeded < numOfWordsThatFit) {
			for (int j = i; j < (i + numOfWordsThatFit); j++) {
				printf("%s", wordArray[j]);
				if (i + numOfWordsThatFit - j != 1) {
					printf("%s", " ");
					if (numSpacesNeeded > 0) {
						printf("%s", " ");
						numSpacesNeeded--;
					}
				}
			}
		} else {
			int spaceAvg = 0;

			if (numOfWordsThatFit == 1) {
				spaceAvg = 0;
				numSpacesNeeded = lineLength - totalCharsPerLine;
			} else {
				spaceAvg = (lineLength - totalCharsPerLine) / (numOfWordsThatFit - 1);
				numSpacesNeeded = (lineLength - totalCharsPerLine) % (numOfWordsThatFit - 1);
			}

			for (int j = i; j < (i + numOfWordsThatFit); j++) {
				printf("%s", wordArray[j]);
				if (i + numOfWordsThatFit - j != 1) {
					printf("%s", " ");
					for (int k = 0; k < spaceAvg; k++) {
						printf("%s", " ");
						if (numSpacesNeeded > 0) {
							printf("%s", " ");
							numSpacesNeeded--;
						}
					}
				}
			}
		}
		//perror("Error: ");

		i += numOfWordsThatFit - 1;
		printf("\n");
	}
}

// Do NOT touch main function no matter what
int main(int argc, char **argv){
	FILE *fp = fopen(argv[1], "r");

	formatAndPrintParagraph(fp, atoi(argv[2]));

	fclose(fp);
	exit(0);
}
