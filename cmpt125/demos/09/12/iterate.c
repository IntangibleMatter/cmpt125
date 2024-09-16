#include <stdio.h>

// will also work as `int* array`
void addOneToAll(int array[], unsigned int size) {
	for (int i = 0; i < size; i++) {
		// printf("%d ", array[i]);
		array[i]++;
	}
}

int main() {
	// create a 1D int array
	int myIntArray[5] = {97, 98, 99, 100, 101};

	printf("Printing the array with a for loop: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", myIntArray[i]);
	}
	printf("\n");

	int index = 0;
	printf("Printing the array with a while loop: ");
	while (index < 5) {
		printf("%c ", myIntArray[index]);
		index++;
	}
	printf("\n");

	addOneToAll(myIntArray, 5);

	printf("Printing the array with a for loop: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", myIntArray[i]);
	}
	printf("\n");

	int userNum = 0;

	do {
		printf("Give a number (0 to end): ");
		int successes = scanf("%d", &userNum);
		if (successes <= 0) {
			printf("That's not a valid number\n");
			break;
		}
		printf("Recieved %d\n", userNum);
	} while (userNum != 0);

	return 0;
}
