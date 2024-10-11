#include <stdio.h>
#include <stdlib.h>

int main() {
	
	//allocate space for an array of 4 int's
	int* dynamicArray = malloc(4*sizeof(int));
	printf("dynamicArray allocated at %p\n", dynamicArray);
	
	for (int i=0; i<4; i++) {
		dynamicArray[i] = i;
		printf("%d ", dynamicArray[i]);
	}
	printf("\n");
	
	//allocate twice the space, note the address being returned
	dynamicArray = realloc(dynamicArray, 8*sizeof(int));
	printf("dynamicArray reallocated at %p\n", dynamicArray);
	
	//printing 8 elements, try running this code a few times
	//note the values of the last 4 elements, their values are undefined
	for (int i=0; i<8; i++) {
		//dynamicArray[i] = i;
		printf("%d ", dynamicArray[i]);
	}
	printf("\n");
	
	return 0;
}