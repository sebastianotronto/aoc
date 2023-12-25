#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

#define ABS(a) ((a)>0?(a):-(a))

#define isnum(c) (c == '-' || (c >= '0' && c <= '9'))

char *buf, line[N];
int s, n, a[N];

int readl(int nums[], char *buf) {
	int i;
	for (i = 0; *buf; buf++) {
		if (!isnum(*buf)) continue;
		nums[i++] = atoll(buf);
		while (isnum(*buf)) buf++;
	}
	return i;
}

int isgood(char *line, int a[], int n) {
	int b[N];
	memset(b, 0, N * sizeof(int));
	memcpy(b, a, n * sizeof(int));
	for (int j = 0, c = 0; *line != ' '; line++) {
		if (*line == '?') printf("Error!\n");
		if (*line == '.') { j += c; c = 0; }
		if (*line == '#') { c = 1; b[j]--; }
	}
	for (int j = 0; j < N; j++)
		if (b[j])
			return 0;
	return 1;
}

int arrange(char *line, char *buf, int a[], int n) {
	while (*buf != '?' && *buf != ' ') buf++;
	if (*buf == ' ')
		return isgood(line, a, n);
	*buf = '.';
	int x = arrange(line, buf, a, n);
	*buf = '#';
	int y = arrange(line, buf, a, n);
	*buf = '?';
	return x + y;
}

int main() {
	while ((buf = fgets(line, N, stdin)) != NULL) {
		n = readl(a, buf);
		s += arrange(line, buf, a, n);
	}

	printf("%d\n", s);
	return 0;
}
