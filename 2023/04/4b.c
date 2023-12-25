#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define ISNUM(c) (c >= '0' && c <= '9')

int main() {
	char *buf, line[N];
	int c, i, j, x, sum, nw, nr, w[100], r[100], sc[N];

	sum = c = 0;
	memset(sc, 0, N * sizeof(int));
	while ((buf = fgets(line, N, stdin)) != NULL) {
		nr = nw = 0;
		sc[++c]++;
		while (*buf != ':') buf++;
		while (*buf != '|') {
			buf++;
			if (!ISNUM(*buf)) continue;
			w[nw++] = atoi(buf);
			while (ISNUM(*buf)) buf++;
		}
		while (*buf != '\n') {
			buf++;
			if (!ISNUM(*buf)) continue;
			r[nr++] = atoi(buf);
			while (ISNUM(*buf)) buf++;
		}
		for (x = 0, i = 0; i < nr; i++) {
			for (j = 0; j < nw; j++) {
				if (r[i] == w[j]) {
					sc[(++x) + c] += sc[c];
					break;
				}
			}
		}
		sum += sc[c];
	}

	printf("%d\n", sum);
	return 0;
}
