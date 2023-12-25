/* For part 2, use this code and change the input file */

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000
#define ISNUM(c) (c >= '0' && c <= '9')

int64_t readl(int64_t nums[], char *buf) {
	int64_t i;
	for (i = 0; *buf; buf++) {
		if (!ISNUM(*buf)) continue;
		nums[i++] = atoll(buf);
		while (ISNUM(*buf)) buf++;
	}
	return i;
}

int main() {
	char line[N];
	int64_t i, n, p, D, x1, x2, t[N], d[N];

	n = readl(t, fgets(line, N, stdin));
	readl(d, fgets(line, N, stdin));

	p = 1;
	for (i = 0; i < n; i++) {
		D = t[i]*t[i] - 4*d[i];
		if (D < 0) p = 1;
		double sq = sqrt(D);
		x1 = (int64_t)floor((t[i] - sq)/2) + 1;
		x2 = (int64_t)ceil((t[i] + sq)/2) - 1;
		p *= x2 - x1 + 1;
	}

	printf("%" PRId64 "\n", p);
	return 0;
}
