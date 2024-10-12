// Lyric Moysey-Rubin
// lwm2
// 301614885

#include "a2_question1.h"

int replaceDigitsRecursive(int number, char target, char replacement) {
	// check and store if the numver is negative for later
	int is_neg = number < 0 ? -1 : 1;
	// get the last digit
	int lastdig = number % 10;
	// use char math to move the target and replacement from character
	// to decimal representation
	int i_target = target - '0';
	int i_replacement = replacement - '0';
	// return early if either character is invalid
	if (i_target < 0 || i_target > 9 || i_replacement < 0 ||
		i_replacement > 9) {
		return number;
	}

	// if negative, invert the numbers to avoid funky math later
	if (is_neg == -1) {
		lastdig *= -1;
		number *= -1;
	}

	// replacement
	if (lastdig == i_target) {
		lastdig = i_replacement;
	}

	// return when there's only one digit left
	if (number % 10 == number) {
		return lastdig;
	} else {
		// multiply by the negative factor to restore sign,
		// then do the recursive call.
		return is_neg *
			   (lastdig + (10 * replaceDigitsRecursive(number / 10, target,
													   replacement)));
	}
}
