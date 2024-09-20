// Lyric Moysey-Rubin
// 301614885
// lwm2
#include "a1_question1.h"

// who needs stdbool.h?
#define true 1
#define false 0
#define bool int

// maximum length of a 32-bit integer
const int DIGIT_ARR_SIZE = 11;

// simple absolute value function because we can't use math.h.
int abs(int num) {
	if (num < 0) {
		return -num;
	}
	return num;
}

// counts the digits in a number by dividing the number by 10, then increasing
// the digit count until the number is 0.
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

// converts a character to an integer by subtracting '0' (0x31) from it,
// moving it from the ascii value of a number to its numerical value.
// I think credit goes to StackOverFlow for introducting me to the concept,
// but I can't find the post again.
int charToInt(char digit) { return (int)digit - '0'; }

// Ensure that a given character has a numerical value between 0 and 9.
bool checkIfValid(char chr) {
	int cid = charToInt(chr);
	if (cid >= 0 && cid <= 9) {
		return true;
	}
	return false;
}

// Converts an integer to an array of digits. It does so by taking the integer,
// and iterating through it as many times as there are digits in it (done by
// checking with another function). For each digit in the number, it modulos the
// number by (10*place value), then subtracts all lower digits in the number to
// make sure the number is aligned to a multiple of its place value. It's then
// divided by place value to move the number between 0 and 10.
void intToDigitArray(int number, int *digits, unsigned int size) {
	int max_base10 = 1;
	int absnum = abs(number);

	do {
		max_base10 *= 10;
	} while (absnum < max_base10);

	// use 0xFFFF as a number to indicate "this isn't what you should care
	// about"
	for (int i = 0; i < size; i++) {
		digits[i] = 0xFFFF;
	}

	int length = digitCount(absnum);

	for (int i = 0; i < length; i++) {
		digits[i] = absnum % 10;
		// using multiplication instead of division because division is slower
		absnum *= 0.1;
	}
}

// simple iterative loop. Looks through the array of digits. if a digit matches
// from, replace it with to.
void replaceDigitsInArray(int *digits, unsigned int size, int from, int to) {
	for (int i = 0; i < size; i++) {
		if (digits[i] == from) {
			digits[i] = to;
		}
	}
}

// Take all the digits in the resultant array of digits, and reconstruct it as
// an int by inverting the process used earlier to convert it to an array.
int digitArrayToInt(int *digits, unsigned int size) {
	int out_int = 0;
	int mult = 1;

	for (int i = 0; i < size; i++) {
		if (digits[i] == 0xFFFF) {
			break;
		}
		out_int += digits[i] * mult;
		mult *= 10;
	}

	return out_int;
}

int replaceDigits(int number, char target, char replacement) {
	int iTarget = charToInt(target);
	int iReplacement = charToInt(replacement);
	if (!checkIfValid(target) && !checkIfValid(replacement)) {
		return number;
	}

	int digits[DIGIT_ARR_SIZE];

	intToDigitArray(number, digits, DIGIT_ARR_SIZE);
	replaceDigitsInArray(digits, DIGIT_ARR_SIZE, iTarget, iReplacement);
	int out = digitArrayToInt(digits, DIGIT_ARR_SIZE);

	// ensure negative numbers stay negative
	if (number < 0) {
		out *= -1;
	}

	return out;
}
