#include <stdio.h>
#include <stdlib.h>

#define N 10000
#define MAX(x,y) ((x)>(y)?(x):(y))

int color[26] = { ['r'-'a'] = 0, ['g'-'a'] = 1, ['b'-'a'] = 2 };

int main() {
	char *buf, line[N];
	int sum, x, maxc[3];

	sum = 0;
	while ((buf = fgets(line, N, stdin)) != NULL) {
		maxc[0] = maxc[1] = maxc[2] = 0;
		while (*buf++ != ':');
		while (*buf++) {
			if (*buf < '0' || *buf > '9') continue;
			x = atoi(buf);
			while (*buf < 'a' || *buf > 'z') buf++;
			maxc[color[*buf-'a']] = MAX(maxc[color[*buf-'a']], x);
		}
		sum += maxc[0] * maxc[1] * maxc[2];
	}

	printf("%d\n", sum);
	return 0;
}
