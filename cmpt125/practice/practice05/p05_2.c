#include <stdio.h>

void foo(int n) {
	if (n > 0) {
		foo(n - 1);
		printf("%d ", n);
	}
}

void foo_norecurse(int n) {
	int i = 1;
	while (i <= n) {
		printf("%d ", i);
		i++;
	}
}

int main() {
	foo_norecurse(10);
	return 0;
}
