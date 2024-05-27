#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestUniqString(char **words, int numWords){
  int currLen;
  int smallestUniqueIndex = 1;
  int temp = 100000;
  int isUniq;

  for (int i = 1; i <= numWords; i++) { // each word
    int uniqChars = 1;

    currLen = strlen(words[i]);
    char *currWord = words[i];

    for (int j = 0; j < currLen - 1; j++) { // first char
      for (int k = j + 1; k < currLen; k++) { // rest of chars
        if (currWord[j] != currWord[k]) {
          isUniq = 1;
        } else if (currWord[j] == currWord[k]) {
          isUniq = 0;
          uniqChars--;
          break;
        }
      }

      if (isUniq == 1) {
        uniqChars++;
      }
    }

    if (uniqChars < temp) {
      temp = uniqChars;
      smallestUniqueIndex = i;
    }

    printf("%s %d %d\n", words[i], currLen, uniqChars);
  }

  return smallestUniqueIndex;
}

int main(int argc, char **argv) {
  printf("\nFinal: %s", argv[smallestUniqString(argv, argc - 1)]);
  return 0;
}