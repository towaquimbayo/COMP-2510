#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count = 0;

int checkSubstring(char c, char *sWord, int sLen) {
	printf("%c %c\n", c, *sWord);
	if (*sWord == c) {
		count++;
		return 1;
	}
	if (*sWord == '\0') {
		return 0;
	}
	return checkSubstring(c, sWord + 1, --sLen);
}

void reverseString(char *fWord, char *sWord, int fLen, int sLen) {
	if (fLen == 0) {
		return;
	} else {
		reverseString(fWord + 1, sWord, --fLen, sLen);
		checkSubstring(*fWord, sWord, sLen);
	}
}

int main(int argc, char **argv) {
	char *str1 = (char *)malloc(sizeof(char*) * strlen(argv[1]));
	char *str2 = (char *)malloc(sizeof(char*) * strlen(argv[2]));
	int str1_len = atoi(argv[3]);
	int str2_len = atoi(argv[4]);

	for(int i = 0; i < strlen(argv[1]); i++){
	str1[i] = argv[1][i];
	}
	for(int j = 0; j < strlen(argv[2]); j++){
	str2[j] = argv[2][j];
	}

	reverseString(str1, str2, str1_len, str2_len);
	printf("%d", count);
	if (count == str2_len) {
		printf("1");
	} else {
		printf("0");
	}

	//printf("%s ", str1);
	//printf("%s", str2);

	free(str1);
	free(str2);
  
	return 0;
}
