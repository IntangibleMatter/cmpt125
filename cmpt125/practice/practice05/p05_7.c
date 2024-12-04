#include <stdio.h>

void foo(int n) {
	if (n > 0) {
		printf("%d ", n);
		foo(n - 1);
	}
}

void foo_norecurse(int n) {
	while (n > 0) {
		printf("%d ", n);
		n--;
	}
}

int main() {
	foo(10);
	return 0;
}
