#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define ISNUM(c) (c >= '0' && c <= '9')

int grab(char *buf) {
	if (!ISNUM(*buf)) return 0;
	while (ISNUM(*buf)) buf--;
	buf++;
	int x = atoi(buf);
	while (ISNUM(*buf)) *buf++ = '.';

	return x;
}

void push(int *j, int *g, char *buf) {
	g[*j] = grab(buf);
	if (g[*j] > 0) (*j)++;
}

int main() {
	char *cont, line[N], prev[N], next[N], backup[3][N];
	int i, sum, j, g[9];

	sum = 0;
	memset(line, '.', N);
	memset(prev, '.', N);
	memset(next, '.', N);
	cont = fgets(&next[1], N-1, stdin);
	while (cont != NULL) {
		memcpy(line, next, N);
		cont = fgets(&next[1], N-1, stdin);
		for (i = 1; line[i]; i++) {
			if (line[i] == '*') {
				memcpy(backup[0], prev, N);
				memcpy(backup[1], line, N);
				memcpy(backup[2], next, N);
				j = 0;
				push(&j, g, &prev[i-1]);
				push(&j, g, &prev[i]);
				push(&j, g, &prev[i+1]);
				push(&j, g, &line[i-1]);
				push(&j, g, &line[i+1]);
				push(&j, g, &next[i-1]);
				push(&j, g, &next[i]);
				push(&j, g, &next[i+1]);
				if (j == 2) sum += g[0] * g[1];
				memcpy(prev, backup[0], N);
				memcpy(line, backup[1], N);
				memcpy(next, backup[2], N);
			}
		}
		memcpy(prev, line, N);
	}

	printf("%d\n", sum);
	return 0;
}
