/**
 * File: assignment2.c
 *
 * Author: Towa Quimbayo, Alex Gibbison
 * Date: November 06, 2022
 * Course: COMP 2510 - Procedural Programming
 *
 * Summary of File:
 *
 * This file does 2 things. If there is only 1 input of an integer value, it prints the min and max values for that bit width.
 * If its 3 inputs, the program will calculate the sum of the two integers and determine the value. It will also check for
 * overflow cases where if the sum is greater than max or less than min then it'll print the min / max value instead.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * signed_max(int bitWidth)
 *
 * Summary of signed_max function:
 *
 * Calculates and returns the maximum value from the given
 * bit width value recursively.
 *
 * Preconditions: bitWidth must be an integer from 4 to 64.
 *
 * Return Value: maximum value from given bits
 *
 * Postconditions: Prints the maximum value from given bits.
 * @param bitWidth for number of bits
 */
long long signed_max(int bitWidth) {
	long long max;

	if (bitWidth == 1) {
		max = 0LL;
		return max;
	} else {
		max = signed_max(--bitWidth);
		max = max << 1;
		max = max | 1LL;
		return max;
	}
}

/**
 * signed_min(int bitWidth)
 *
 * Summary of signed_min function:
 *
 * Calculates and returns the minimum value from the given
 * bit width value recursively.
 *
 * Preconditions: bitWidth must be an integer from 4 to 64.
 *
 * Return Value: minimum value from given bits
 *
 * Postconditions: Prints the minimum value from given bits.
 * @param bitWidth for number of bits
 */
long long signed_min(int bitWidth) {
	long long min = signed_max(bitWidth);
	return ~min;
}

/**
 * sat_add(long long operand1, long long operand2, int bitWidth)
 *
 * Summary of sat_add function:
 *
 * Calculates and returns the sum of the 2 operands recursively.
 *
 * Preconditions: bitWidth must be an integer from 4 to 64.
 * Operand1 and Operand2 must be a valid integer within range.
 *
 * Return Value: Sum of operand1 and operand2
 *
 * Postconditions: Returns the sum of operand1 and operand2.
 * @param operand1 for first operand
 * @param operand2 for second operand
 * @param bitWidth for number of bits
 */
long long sat_add(long long operand1, long long operand2, int bitWidth) {
	long long carryBit = (operand1 & operand2) << 1; // carry bit, shift left once that will be added to next iteration
	long long sum = operand1 ^ operand2; // XOR for simple addition, no carry's
	return carryBit == 0 ? sum : sat_add(carryBit, sum, --bitWidth);
}

/**
 * printMinMax(int bitWidth)
 *
 * Summary of printMinMax function:
 *
 * Prints the minimum and maximum value from given bit width.
 *
 * Preconditions: bitWidth must be an integer from 4 to 64.
 *
 * Return Value: No return
 *
 * Postconditions: Prints the min max of given bit width.
 * @param bitWidth for number of bits
 */
void printMinMax(int bitWidth) {
	printf("%d%s", bitWidth, "-bit signed integer range");
	printf("\n%s %lld 0x%016llx", "min:", signed_min(bitWidth), signed_min(bitWidth));
	printf("\n%s %lld 0x%016llx", "max:", signed_max(bitWidth), signed_max(bitWidth));
}

/**
 * printSum(long long operand1, long long operand2, int bitWidth)
 *
 * Summary of printSum function:
 *
 * Prints the sum value from the 2 operands.
 *
 * Preconditions: bitWidth must be an integer from 4 to 64.
 * Operand1 and Operand2 must be a valid integer within range.
 *
 * Return Value: No return
 *
 * Postconditions: Prints the sum of operand1 and operand2.
 * @param operand1 for first operand
 * @param operand2 for second operand
 * @param bitWidth for number of bits
 */
void printSum(long long operand1, long long operand2, int bitWidth) {
	// OP Positive (SB: 0) then if (OP - MAX > 0)
	// OP Negative (SB: 1) then if (OP - MIN < 0)
	if (((operand1 >> 63) == 0 && (((~(operand1 - signed_max(bitWidth)) + 1) >> 63) & 1))
		|| ((operand1 >> 63) == -1 && ((((operand1 - signed_min(bitWidth)) + (~0 + 1)) >> 63) & 1))
		|| ((operand2 >> 63) == 0 && (((~(operand2 - signed_max(bitWidth)) + 1) >> 63) & 1))
        || ((operand2 >> 63) == -1 && ((((operand2 - signed_min(bitWidth)) + (~0 + 1)) >> 63) & 1))
		|| (strcmp(strerror(errno), "Result too large") == 0)) {
		printf("%s", "One of the operands is invalid or out of range");
	} else {
		long long sum = sat_add(operand1, operand2, bitWidth);
		long long signBitSum = sum >> (bitWidth - 1);
		long long signBitOperand1 = operand1 >> (bitWidth - 1);
		long long signBitOperand2 = operand2 >> (bitWidth - 1);

		if (signBitOperand1 == 0 && signBitOperand2 == 0 && signBitSum != 0) {
			// positive overflow
			printf("%s\n", "There was a positive overflow.");
			printf("%lld %s %lld %s %lld", operand1, "+", operand2, "=", signed_max(bitWidth));
		} else if (signBitOperand1 == -1 && signBitOperand2 == -1 && signBitSum != -1) {
			// negative overflow
			printf("%s\n", "There was a negative overflow.");
			printf("%lld %s %lld %s %lld", operand1, "+", operand2, "=", signed_min(bitWidth));
		} else {
			printf("%lld %s %lld %s %lld", operand1, "+", operand2, "=", sum);
		}
	}
}

/**
 * main(int argc, char **argv)
 *
 * Summary of main function:
 *
 * Calls the minMax functions and sum calculation functions depending on argc.
 *
 * Preconditions: argc can be 2 or 4. If one input, must be a bit width value between 4 and 64.
 * If 3 inputs, then also check for the 2 operands if its within the range of the bit width.
 *
 * Return Value: 0 if success, 1 if fail
 *
 * Postconditions: Returns 0 if program runs successful
 * @param argc for command argument count
 * @param argv for command arguments
 */
int main(int argc, char **argv) {
	 if ((((atoll(argv[1]) + (~4 + 1)) >> 63) & 1) || (((64 + (~atoll(argv[1]) + 1)) >> 63) & 1)) {
		printf("%s", "Bit width must be a number between 4 and 64.");
		exit(1);
	}

	if (argc == 2) {
		printMinMax(atoi(argv[1]));
	} else if (argc == 4) {
		printSum(atoll(argv[2]), atoll(argv[3]), atoi(argv[1]));
	} else {
		printf("%s", "Must provide a bit width or bit width and the 2 operands.");
		exit(1);
	}

	return 0;
}