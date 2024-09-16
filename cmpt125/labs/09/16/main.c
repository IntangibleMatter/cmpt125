#include "minmax.h"
#include <stdio.h>

int main() {
	int a = 10;
	int b = 20;
	int min_number, max_number;
	min_number = min(a, b);
	max_number = max(a, b);

	printf("Min number is %d and Max number is %d\n", min_number, max_number);
}
