#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 200

char map[M][M];
int s, n, nb, b[M][2], entered[M][M];

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
		if (k & turn[d][map[i][j]])
			walk(i+go[k][0], j+go[k][1], k);
}

int main() {
	for (n = 0; fgets(map[n], M, stdin) != NULL; n++) ;
	walk(0, 0, E);
	printf("%d\n", s);
	return 0;
}
