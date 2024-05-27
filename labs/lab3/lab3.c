#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printReversedTokens(char *inputString, int strLen){
    // Delimeter for spaces
    char delimeter[] = " ";

    // pointer for each word in the inputString
    char *token;

    token = strtok(inputString, delimeter);

    // Scan each word in the string until it reaches the end
    while (token != NULL) {
        // Length of each word
        int tokLength = strlen(token);
        char temp;

        // Reverse each word in the string
        for (int i = 0; i < tokLength / 2; i++) {
            temp = token[i];
            token[i] = token[tokLength - i - 1];
            token[tokLength - i - 1] = temp;
        }

        // Prints the word in reverse and returns to the next word
        printf("%s\n", token);
        token = strtok(NULL, delimeter);
    }

}

int main(int argc, char **argv){
    if (strlen(argv[1]) > 50 && atoi(argv[2]) > 50) {
        printf("%s", "Your input string length is too long to be executed! Please keep it maximum 20 characters");
    } else if (strlen(argv[1]) != atoi(argv[2])) {
        printf("%s", "Your input string length does not match the inputted integer length value.");
    } else {
        printReversedTokens(argv[1], atoi(argv[2]));
    }
    exit(0);
}
