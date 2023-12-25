#include <stdio.h>
#include <string.h>

#define M 200
#define MAX(x,y) ((x)>(y)?(x):(y))

char map[M][M];
int s, t, n, nb, b[M][2], entered[M][M];

#define E 1
#define N 2
#define W 4
#define S 8
int turn[9][255] = {
	[E] = { ['.'] = E, ['-'] = E,   ['/'] = N, ['\\'] = S, ['|'] = N|S },
	[N] = { ['.'] = N, ['-'] = E|W, ['/'] = E, ['\\'] = W, ['|'] = N   },
	[W] = { ['.'] = W, ['-'] = W,   ['/'] = S, ['\\'] = N, ['|'] = N|S },
	[S] = { ['.'] = S, ['-'] = E|W, ['/'] = W, ['\\'] = E, ['|'] = S   },
};
int go[9][2] = { [E] = {0, 1}, [N] = {-1, 0}, [W] = {0, -1}, [S] = {1, 0} };

void walk(int i, int j, int d) {
	if (i < 0 || j < 0 || i >= n || j >= n || (entered[i][j] & d)) return;
	if (!entered[i][j]) s++;
	entered[i][j] |= d;
	for (int k = 1; k <= 8; k <<= 1)
		if (k & turn[d][(int)map[i][j]])
			walk(i+go[k][0], j+go[k][1], k);
}

void clear(void) {
	s = 0;
	for (int i = 0; i < n; i++)
		memset(entered[i], 0, n * sizeof(int));
}

int main() {
	for (n = 0; fgets(map[n], M, stdin) != NULL; n++) ;

	for (int i = 0; i < n; i++) {
		clear(); walk(i, 0,   E); t = MAX(s, t);
		clear(); walk(i, n-1, W); t = MAX(s, t);
		clear(); walk(0,   i, S); t = MAX(s, t);
		clear(); walk(n-1, i, N); t = MAX(s, t);
	}

	printf("%d\n", t);
	return 0;
}
