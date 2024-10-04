// Lyric Moysey-Rubin
// 301614885
// lwm2
#include "a1_question2.h"

// checks a range in an array to assert that it's sorted. does so by first
// ensuring that the indexes to search through are valid, correcting them if
// not, then iterates from (leftIndex + 1) to rightIndex, returning false
// if the value at the previous index is ever greater than the one at the
// current index.
bool rangedCheckforSorted(int array[], unsigned int size, int leftIndex,
						  int rightIndex) {
	if (rightIndex < leftIndex) {
		int temp = rightIndex;
		rightIndex = leftIndex;
		leftIndex = temp;
	}
	if (leftIndex < 0) {
		leftIndex = 0;
	}
	if (rightIndex > size) {
		rightIndex = size;
	}

	// start at leftIndex + 1 to ensure we always have an element to the left to
	// check against.
	for (int i = leftIndex + 1; i < rightIndex; i++) {
		if (array[i - 1] > array[i]) {
			return false;
		}
	}

	return true;
}
