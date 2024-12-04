#include <stdio.h>

long foo(int n) {
	if (n == 0) {
		printf("1 ");
		return 1;
	} else {
		long f = foo(n - 1) + foo(n - 1);
		printf("%d ", (int)f);
		return f;
	}
}

long foo_norecurse(int n) { return 0; }

int main() {
	printf("foo:\n");
	foo(2);
	printf("\nfoo without recursion:\n");
	foo_norecurse(10);
	return 0;
}
