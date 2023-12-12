#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200
#define T 5
#define isnum(c) (c == '-' || (c >= '0' && c <= '9'))

char *buf, line[N];
int64_t s, m, n, p, a[N], mem[N][N][N];

int64_t readl(int64_t nums[], char *buf) {
	int64_t i;
	for (i = 0; *buf; buf++) {
		if (!isnum(*buf)) continue;
		nums[i++] = atoll(buf);
		while (isnum(*buf)) buf++;
	}
	return i;
}

int64_t f(int64_t j, int64_t i, int64_t k) {
	if (mem[j][i][k] != -1)
		return mem[j][i][k];
	if (i > n || k > a[i])
		return mem[j][i][k] = 0;

	int64_t ret = 0;
	if (j == m)
		ret = i == n && k == 0;
	if (line[j] == '#' || line[j] == '?')
		ret += f(j+1, i, k+1);
	if ((line[j] == '.' || line[j] == '?') && (k == 0 || k == a[i]))
		ret += f(j+1, i+(k>0), 0);
	return mem[j][i][k] = ret;
}

int main() {
	while ((buf = fgets(line, N, stdin)) != NULL) {
		n = readl(a, buf);

		/* Multiply strings by T (1 for part 1, 5 for part 2) */
		for (m = 0; line[m] != ' '; m++) ;
		for (int64_t t = 1; t < T; t++) {
			memcpy(a + t * n, a, n * sizeof(int64_t));
			line[t*(m+1)-1] = '?';
			memcpy(line + t * (m + 1), line, (m + 1));
		}
		m = T*(m+1);
		line[m-1] = '.';
		line[m] = 0;
		n *= T;
		a[n] = 0;

		/* Reset memoization table */
		for (int64_t j = 0; j <= m; j++)
			for (int64_t i = 0; i <= n; i++)
				for (int64_t k = 0; k <= m; k++)
					mem[j][i][k] = -1;

		/* Compute solution */
		s += f(0, 0, 0);
	}

	printf("%" PRId64 "\n", s);
	return 0;
}
