#include "a1_question1.h"
#include <stdio.h>

#define true 1
#define false 0
#define bool int

const int DIGIT_ARR_SIZE = 11;

int abs(int num) {
	if (num < 0) {
		return -num;
	}
	return num;
}

int digitCount(int num) {

	if (num == 0) {
		return 1;
	}
	int count = 0;
	while (num != 0) {
		num /= 10;
		count++;
	}
	return count;
}

int charToInt(char digit) { return (int)digit - '0'; }

bool checkIfValid(char chr) {
	int cid = charToInt(chr);
	if (cid > 0 && cid < 9) {
		return true;
	}
	return false;
}

void intToDigitArray(int number) {
	printf("%d: ", number);
	int max_base10 = 1;
	int absnum = abs(number);

	do {
		max_base10 *= 10;
	} while (absnum < max_base10);

	int digits[DIGIT_ARR_SIZE];
	for (int i = 0; i < DIGIT_ARR_SIZE; i++) {
		digits[i] = 0xFFFF;
	}

	int length = digitCount(absnum);
	int modby = 10;

	for (int i = 0; i < length; i++) {
		digits[i] = ((number % modby) - (number % (modby / 10)));
		modby *= 10;
		printf("%d ", digits[i]);
	}
	printf("\n");

	// return digits;
}

// char[] intArrayToString(int arr[], unsigned int size) {}

int replaceDigits(int number, char target, char replacement) {
	if (!checkIfValid(target) && !checkIfValid(replacement)) {
		return number;
	}
	return 0;
}

int main() {
	printf("test\n");
	printf("%d \n", 942);
	for (int i = 1; i < 4096; i *= 7) {
		intToDigitArray(i);
	}

	return 0;
}
