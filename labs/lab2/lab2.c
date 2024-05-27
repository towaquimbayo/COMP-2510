#include <stdio.h>

void printMultiplicationTable() { // Do NOT touch this line at all
    /**
     * Decalre the array with 16 indexes for both rows and columns.
     *
     * First for loop to input the values into each each of the array,
     * and multiple (i + 1) and (j + 1). We add 1 because the index starts from 0.
     *
     * Last loop is for print each index.
     */
    int maxNum = 16;
    int table[maxNum][maxNum];
    for (int i = 0; i < maxNum; i++) {
        for (int j = 0; j < maxNum; j++) {
            table[i][j] = (i + 1) * (j + 1);
        }
    }

    for (int i = 0; i < maxNum; i++) {
        for (int j = 0; j < maxNum; j++) {
            printf("%5d", table[i][j]);
        }
        printf("\n");
    }
}

int isPalindrome(int elements[], int size) { // Do NOT touch this line at all
    /**
     * Loop through each index and check the first and last index one at a time to see if its palindrome.
     * Make it return -1 right away if the two indices are not equal, otherwise continue and return 1.
     */
    for (int i = 0; i < size; i++) {
        if (elements[i] != elements[size - 1 - i]) {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv){ // Do NOT touch this line at all
    int nums[] = {1, 5, 10, 5, 1};
    printMultiplicationTable();

    // If the palindrome method returns a 0 then it's a palindrome, if its -1 then it's not
    if (isPalindrome(&nums, sizeof(nums) / sizeof(nums[0])) == 0) {
        printf("This array of integers is a Palindrome!");
    } else {
        printf("This array of integers is NOT a Palindrome!");
    }
}
