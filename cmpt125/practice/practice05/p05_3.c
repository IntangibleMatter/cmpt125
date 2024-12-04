#include <stdio.h>

void foo(int n) {
	if (n == 0) {
		printf("0 ");
	} else {
		printf("%d ", n);
		foo(n - 1);
		printf("%d ", n);
	}
}

void foo_norecurse(int n) {
	int i = n;
	while (i > 0) {
		printf("%d ", i);
		i--;
	}
	printf("0 ");
	while (i < n) {
		i++;
		printf("%d ", i);
	}
}

int main() {
	printf("foo:\n");
	foo(10);
	printf("\nfoo without recursion:\n");
	foo_norecurse(10);
	return 0;
}
