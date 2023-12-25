#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 200

typedef struct { int i, j; } point_t;

char map[N][N];
int n, nq, nnext;
point_t s, q[N*N], nextq[N*N];

bool bad(point_t p) {
	int i = p.i, j = p.j;
	return i < 0 || j < 0 || i >= n || j >= n || map[i][j] == '#';
}

void add(point_t p) {
	if (bad(p)) return;
	for (int i = 0; i < nnext; i++)
		if (nextq[i].i == p.i && nextq[i].j == p.j)
			return;
	nextq[nnext++] = p;
}

point_t up(point_t p) { return (point_t) {.i = p.i-1, .j = p.j}; }
point_t down(point_t p) { return (point_t) {.i = p.i+1, .j = p.j}; }
point_t right(point_t p) { return (point_t) {.i = p.i, .j = p.j+1}; }
point_t left(point_t p) { return (point_t) {.i = p.i, .j = p.j-1}; }

int main() {
	for (n = 0; fgets(map[n], N, stdin) != NULL; n++)
		for (int i = 0; map[n][i] != '\n'; i++)
			if (map[n][i] == 'S')
				s = (point_t) {.i = n, .j = i};

	int d = 64;
	add(s);
	for (int i = 0; i < d; i++) {
		memcpy(q, nextq, nnext * sizeof(point_t));
		nq = nnext;
		nnext = 0;
		for (int j = 0; j < nq; j++) {
			add(up(q[j]));
			add(down(q[j]));
			add(right(q[j]));
			add(left(q[j]));
		}
	}

	printf("%d\n", nnext);
	return 0;
}
