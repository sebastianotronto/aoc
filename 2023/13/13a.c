#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 64

#define MAX(a,b) ((a)>(b)?(a):(b))

char *buf, line[N];
int64_t i, s, nc, nr, r[N], c[N];

int64_t ismirror(int64_t i, int64_t a[], int64_t n) {
	for (int64_t j = MAX(0, 2*i-n+2); j <= i && 2*i-j+1 < n; j++)
		if (a[j] != a[2*i-j+1])
			return 0;
	return 1;
}

int main() {
	do {
		buf = fgets(line, N, stdin);
		if (buf == NULL || line[0] == '\n') {
			for (i = 0; i < nc-1; i++)
				s += (i + 1) * ismirror(i, c, nc);
			for (i = 0; i < nr-1; i++)
				s += 100 * (i + 1) * ismirror(i, r, nr);
			nr = nc = 0;
			memset(r, 0, N * sizeof(int64_t));
			memset(c, 0, N * sizeof(int64_t));
		} else {
			for (nc = 0; line[nc] != '\n'; nc++) {
				r[nr] = (r[nr] << 1) + (line[nc] == '#');
				c[nc] = (c[nc] << 1) + (line[nc] == '#');
			}
			nr++;
		}
	} while (buf != NULL);

	printf("%" PRId64 "\n", s);
	return 0;
}
