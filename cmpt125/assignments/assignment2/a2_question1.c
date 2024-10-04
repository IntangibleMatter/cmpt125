#include "a2_question1.h"

int replaceDigitsRecursive(int number, char target, char replacement) {
	int is_neg = number < 0 ? -1 : 1;
	int lastdig = number % 10;
	int i_target = target - '0';
	int i_replacement = replacement - '0';
	if (i_target < 0 || i_target > 9 || i_replacement < 0 ||
		i_replacement > 9) {
		return number;
	}

	if (is_neg == -1) {
		lastdig *= -1;
		number *= -1;
	}

	if (lastdig == i_target) {
		lastdig = i_replacement;
	}

	if (number % 10 == number) {
		return lastdig;
	} else {
		return is_neg *
			   (lastdig + (10 * replaceDigitsRecursive(number / 10, target,
													   replacement)));
	}
}
