/* For part 2 we save ranges as (first, last) instead of (first, length) */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000
#define ISNUM(c) (c >= '0' && c <= '9')
#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))


void append(int64_t dst[][2], int64_t src[][2], int64_t *nr, int64_t *nnr) {
	for (int i = 0; i < *nnr; i++) {
		dst[i+*nr][0] = src[i][0];
		dst[i+*nr][1] = src[i][1];
	}
	*nr += *nnr;
	*nnr = 0;
}

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
	char *buf, line[N];
	int64_t i, li, ri, m, nr, nnr, r[3], range[N][2], next[N][2], aux[N];

	nnr = readl(aux, fgets(line, N, stdin)) / 2;
	for (i = 0; i < nnr; i++) {
		next[i][0] = aux[2*i];
		next[i][1] = aux[2*i+1] + next[i][0] - 1;
	}

	for (nr = 0; (buf = fgets(line, N, stdin)) != NULL; ) {
		if (!ISNUM(*buf)) {
			append(range, next, &nr, &nnr);
			continue;
		}

		readl(r, buf);
		for (i = 0; i < nr; i++) {
			li = range[i][0];
			ri = range[i][1];
			if (li > ri || r[1] > ri || r[1]+r[2]-1 < li) continue;
			range[i][1] = MIN(ri, r[1]-1);
			next[nnr][0] = MAX(li, r[1]) + r[0]-r[1];
			next[nnr++][1] = MIN(ri, r[1]+r[2]-1) + r[0]-r[1];
			range[nr][0] = MAX(li, r[1]+r[2]);
			range[nr++][1] = ri;
		}
	}

	append(range, next, &nr, &nnr);
	for (i = 0, m = -1; i < nr; i++)
		if (range[i][0] <= range[i][1])
			m = m == -1 || m > range[i][0] ? range[i][0] : m;

	printf("%" PRId64 "\n", m);
	return 0;
}
