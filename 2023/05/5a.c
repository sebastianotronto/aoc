#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

bool isnum(char c) { return c >= '0' && c <= '9'; }

int main() {
	char *buf, line[N];
	int64_t i, m, ns, seed[N], next[N], r[3];

	for (ns = 0, buf = fgets(line, N, stdin); *buf; buf++) {
		if (!isnum(*buf)) continue;
		next[ns++] = atoll(buf);
		while (isnum(*buf)) buf++;
	}


	while ((buf = fgets(line, N, stdin)) != NULL) {
		if (!isnum(*buf)) {
			memcpy(seed, next, ns * sizeof(int64_t));
			fgets(line, N, stdin); /* Discard description */
			continue;
		}

		for (i = 0; *buf; buf++) {
			r[i++] = atoll(buf);
			while (isnum(*buf)) buf++;
		}

		for (i = 0; i < ns; i++)
			if (seed[i] >= r[1] && seed[i] < r[1] + r[2])
				next[i] = seed[i] + (r[0] - r[1]);
	}

	m = next[0];
	for (i = 1; i < ns; i++)
		m = m > next[i] ? next[i] : m;

	printf("%" PRId64 "\n", m);
	return 0;
}
