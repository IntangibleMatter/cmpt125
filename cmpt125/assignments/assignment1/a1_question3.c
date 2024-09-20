// Lyric Moysey-Rubin
// 301614885
// lwm2
#include "a1_question3.h"

// reverses polarity of all elements in a 2d array using pointer arithmetic.
// Uses *() to dereference, and adds ints to get to the index.
void reversePolarity(unsigned int row, unsigned int col, int **array) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			*(*(array + i) + j) *= -1;
		}
	}
}
