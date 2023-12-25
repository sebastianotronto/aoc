#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

#define isnum(c) (c == '-' || (c >= '0' && c <= '9'))

int64_t readl(int64_t nums[], char *buf) {
	int64_t i;
	for (i = 0; *buf; buf++) {
		if (!isnum(*buf)) continue;
		nums[i++] = atoll(buf);
		while (isnum(*buf)) buf++;
	}
	return i;
}

bool isconstant(int64_t a[], int n) {
	for (int i = 0; i < n-1; i++)
		if (a[i] != a[i+1])
			return false;
	return true;
}

int64_t next(int64_t a[], int64_t n) {
	int64_t x = a[n-1];
	if (isconstant(a, n))
		return x;
	for (int i = 0; i < n-1; i++)
		a[i] = a[i+1] - a[i];
	return x + next(a, n-1);
}

int main() {
	char line[N];
	int64_t s, a[N];

	for (s = 0; fgets(line, N, stdin) != NULL; )
		s += next(a, readl(a, line));

	printf("%" PRId64 "\n", s);
	return 0;
}
