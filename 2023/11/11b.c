#include <inttypes.h>
#include <stdio.h>

#define N 1000

#define ABS(a) ((a)>0 ? (a) : -(a))

uint8_t dr[N], dc[N];
int64_t i, j, k, n, p, g[N*N][2];

int main() {
	char line[N];
	for (i = 0; fgets(line, N, stdin) != NULL; i++) {
		for (j = 0; line[j] != '\n'; j++) {
			if (line[j] == '#') {
				g[n][0] = i;
				g[n++][1] = j;
				dr[i] = dc[j] = 1;
			}
		}
	}

	for (k = 1; k < i; k++) dr[k] += dr[k-1];
	for (k = 1; k < j; k++) dc[k] += dc[k-1];

	for (i = 0; i < n; i++) {
		g[i][0] += 999999 * (g[i][0] - dr[g[i][0]]);
		g[i][1] += 999999 * (g[i][1] - dc[g[i][1]]);
	}

	for (i = 0; i < n; i++)
		for (j = i+1; j < n; j++)
			p += ABS(g[i][0] - g[j][0]) + ABS(g[i][1] - g[j][1]);

	printf("%" PRId64 "\n", p);
	return 0;
}
