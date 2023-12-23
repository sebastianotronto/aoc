#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 150
#define V 1000

typedef struct { int i, j; } node_t;
typedef struct { int u, w; } edge_t;
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool v[N][N];
char map[N][N];
int n, s, t, nv, ne[V];
node_t node[V];
edge_t g[V][4];

int max(int x, int y) { return x > y ? x : y; }

bool isjunc(int i, int j) {
	int nn = 0;
	for (int k = 0; k < 4; k++)
		nn += map[i+d[k][0]][j+d[k][1]] == '#';
	return nn != 2;
}

void advance(int io, int jo, int *i, int *j) {
	for (int k = 0; k < 4; k++) {
		int ni = *i + d[k][0], nj = *j + d[k][1];
		if (!v[ni][nj] && (ni != io || nj != jo) &&
		    map[ni][nj] != '#') {
			*i = ni;
			*j = nj;
			if (!isjunc(*i, *j)) v[*i][*j] = true;
			return;
		}
	}
}

int findorcreate(int i, int j) {
	for (int u = 0; u < nv; u++)
		if (node[u].i == i && node[u].j == j)
			return u;
	node[nv] = (node_t) {.i = i, .j = j};
	return nv++;
}

edge_t findedge(int io, int jo, int i, int j) {
	int w;
	v[i][j] = true;
	for (w = 1; !isjunc(i, j); w++) advance(io, jo, &i, &j);
	return (edge_t) {.u = findorcreate(i, j), .w = w};
}

void makegraph(int u) {
	int i = node[u].i, j = node[u].j;
	for (int k = 0; k < 4; k++) {
		int ni = i + d[k][0], nj = j + d[k][1];
		if (!v[ni][nj] && map[ni][nj] != '#') {
			edge_t e = findedge(i, j, ni, nj);
			g[u][ne[u]++] = (edge_t) {.u = e.u, .w = e.w};
			g[e.u][ne[e.u]++] = (edge_t) {.u = u, .w = e.w};
		}
	}
}

int longpath(int u) {
	int i = node[u].i, j = node[u].j, k, ret, p;

	if (i == n-1 && j == t) return 0;
	if (v[i][j]) return -1;

	v[i][j] = true;
	for (ret = -1, k = 0; k < ne[u]; k++)
		if ((p = longpath(g[u][k].u)) != -1)
			ret = max(ret, g[u][k].w + p);
	v[i][j] = false;

	return ret;
}

int main() {
	for (n = 1; fgets(map[n], N, stdin) != NULL; n++) ;
	memset(map[0], '#', n);
	memset(map[n], '#', n);
	for (int i = 0; i < n; i++) if (map[1][i] == '.') s = i;
	for (int i = 0; i < n; i++) if (map[n-1][i] == '.') t = i;

	findorcreate(1, s);
	for (int u = 0; u < nv; u++)
		makegraph(u);

	printf("%d\n", longpath(0));

	return 0;
}
