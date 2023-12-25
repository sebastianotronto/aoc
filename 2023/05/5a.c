#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define ISNUM(c) (c >= '0' && c <= '9')
#define MIN(x,y) ((x)<(y)?(x):(y))

int main() {
	char *buf, line[N];
	int64_t i, m, ns, seed[N], next[N], r[3];

	for (ns = 0, buf = fgets(line, N, stdin); *buf; buf++) {
		if (!ISNUM(*buf)) continue;
		next[ns++] = atoll(buf);
		while (ISNUM(*buf)) buf++;
	}


	while ((buf = fgets(line, N, stdin)) != NULL) {
		if (!ISNUM(*buf)) {
			memcpy(seed, next, ns * sizeof(int64_t));
			fgets(line, N, stdin); /* Discard description */
			continue;
		}

		for (i = 0; *buf; buf++) {
			r[i++] = atoll(buf);
			while (ISNUM(*buf)) buf++;
		}

		for (i = 0; i < ns; i++)
			if (seed[i] >= r[1] && seed[i] < r[1] + r[2])
				next[i] = seed[i] + (r[0] - r[1]);
	}

	for (i = 1, m = next[0]; i < ns; i++)
		m = MIN(m, next[i]);

	printf("%" PRId64 "\n", m);
	return 0;
}
