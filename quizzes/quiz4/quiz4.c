#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestUniqString(char **words, int numWords){
	int smallestIndex = 1;
	int highest = 1000;
	int len;
	int isUnique;

	for (int i = 1; i <= numWords; i++) {
		int uniqueCount = 1;
		len = strlen(words[i]);
		char *currWord = words[i];

		for (int j = 0; j < len - 1; j++) {
			for (int k = j + 1; k < len; k++) {
				if (currWord[j] != currWord[k]) {
					isUnique = 1;
				} else if (currWord[j] == currWord[k]) {
					isUnique = 0;
					break;
				}
			}

			if (isUnique == 1) {
				uniqueCount++;
			}
		}

		if (uniqueCount < highest) {
			highest = uniqueCount;
			smallestIndex = i;
		}
	}
	return smallestIndex;
}

int main(int argc, char **argv) {

    printf("%s", argv[smallestUniqString(argv, argc - 1)]);

    return 0;
}
