#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

bool isnum(char c) { return c >= '0' && c <= '9'; }

int main() {
	char *buf, line[N];
	int i, j, x, sum, nw, nr, w[100], r[100];

	sum = 0;
	while ((buf = fgets(line, N, stdin)) != NULL) {
		nr = nw = 0;
		while (*buf != ':') buf++;
		while (*buf != '|') {
			buf++;
			if (!isnum(*buf)) continue;
			w[nw++] = atoi(buf);
			while (isnum(*buf)) buf++;
		}
		while (*buf != '\n') {
			buf++;
			if (!isnum(*buf)) continue;
			r[nr++] = atoi(buf);
			while (isnum(*buf)) buf++;
		}
		for (x = 0, i = 0; i < nr; i++) {
			for (j = 0; j < nw; j++) {
				if (r[i] == w[j]) {
					x++;
					break;
				}
			}
		}
		sum += 1 << (x-1);
	}

	printf("%d\n", sum);
	return 0;
}
