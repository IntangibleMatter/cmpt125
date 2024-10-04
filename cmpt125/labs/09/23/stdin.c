#include <stdio.h>

#define MAX_DATA_SIZE 1024

int main() {
	char data[1024];

	while (fgets(data, MAX_DATA_SIZE, stdin) != NULL) {
		printf("%s", data);
	}
}
