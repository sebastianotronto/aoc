#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1500
#define M 340
#define MAX(x,y) ((x)>(y)?(x):(y))

#define isnum(c) (c == '-' || (c >= '0' && c <= '9'))

char line[N];
int n, x, b[N][6], cube[M][M][M];

void readl(int nums[], char *buf) {
	for (int i = 0; i < 6; i++) {
		nums[i] = atoi(buf);
		while (isnum(*buf)) buf++;
		buf++;
	}
}

bool droppable(int i) {
	int z = b[i][2];
	if (z == 1) return false;
	for (int x = b[i][0]; x <= b[i][3]; x++)
		for (int y = b[i][1]; y <= b[i][4]; y++)
			if (cube[x][y][z-1])
				return false;
	return true;
}

void set(int n, int c) {
	for (int i = b[n][0]; i <= b[n][3]; i++)
		for (int j = b[n][1]; j <= b[n][4]; j++)
			for (int k = b[n][2]; k <= b[n][5]; k++)
				cube[i][j][k] = c;
}

void dobreak(int n) { set(n, 0); }
void unbreak(int n) { set(n, n+1); }

void drop(int i) {
	dobreak(i);
	b[i][2]--;
	b[i][5]--;
	unbreak(i);
}

int disintegratable(int i) {
	int ret = 1;
	dobreak(i);
	for (int j = 0; j < n; j++)
		if (j != i && droppable(j))
			ret = 0;
	unbreak(i);
	return ret;
}

int main() {
	for (n = 0; fgets(line, N, stdin) != NULL; n++) {
		readl(b[n], line);
		unbreak(n);
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < n; j++)
			while (droppable(j))
				drop(j);

	for (int i = 0; i < n; i++)
		x += disintegratable(i);

	printf("%d\n", x);
	return 0;
}
