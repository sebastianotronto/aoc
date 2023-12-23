#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200

bool v[N][N];
char map[N][N];
int n, s, t, sol;

int max(int x, int y) { return x > y ? x : y; }

int longpath(int i, int j) {
	if (i == n-1 && j == t) return 0;
	if (v[i][j]) return -1;

	char c = map[i][j];
	int ret = -1;
	v[i][j] = true;
	if (c == '.' || c == '>') ret = max(ret, longpath(i, j+1));
	if (c == '.' || c == 'v') ret = max(ret, longpath(i+1, j));
	if (c == '.' || c == '<') ret = max(ret, longpath(i, j-1));
	if (c == '.' || c == '^') ret = max(ret, longpath(i-1, j));
	v[i][j] = false;

	return ret == -1 ? ret : ret + 1;
}

int main() {
	for (n = 1; fgets(map[n], N, stdin) != NULL; n++) ;
	memset(map[0], '#', n);
	for (int i = 0; i < n; i++) if (map[1][i] == '.') s = i;
	for (int i = 0; i < n; i++) if (map[n-1][i] == '.') t = i;

	printf("%d\n", longpath(1, s));
	return 0;
}
