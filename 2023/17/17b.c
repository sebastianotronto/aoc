#include <stdio.h>

#define M 150
#define MAXE 1000000
#define INF 999999999

#define E 0
#define N 1
#define W 2
#define S 3

int go[4][2] = { [E] = {0, 1}, [N] = {-1, 0}, [W] = {0, -1}, [S] = {1, 0} };

typedef struct { int i, j, k, s, d; } node_t;

char map[M][M];
int n, nq, d[M][M][4][11];
node_t heap[MAXE];

void swap(int i, int j) {
	node_t aux = heap[i];
	heap[i] = heap[j];
	heap[j] = aux;
}

void push(node_t node) {
	heap[nq] = node;
	for (int k = nq++; k > 0 && heap[k].d < heap[(k-1)/2].d; k = (k-1)/2)
		swap(k, (k-1)/2);
}

node_t pop(void) {
	node_t ret = heap[0];
	heap[0] = heap[--nq];
	for (int k = 0, j = 0; 2*k+1 < nq; k = j) {
		j = 2*k+1;
		if (j+1 < nq && heap[j].d > heap[j+1].d) j++;
		if (heap[k].d > heap[j].d) swap(k, j);
	}
	return ret;
}

int main() {
	for (n = 0; fgets(map[n], M, stdin) != NULL; n++) ;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < 4; k++)
				for (int s = 0; s < 11; s++)
					d[i][j][k][s] = INF;

	push((node_t){.i = 0, .j = 0, .k = -1, .s = 0});
	node_t v;
	for (v = pop(); v.i != n-1 || v.j != n-1; v = pop()) {
		for (int k = 0; k < 4; k++) {
			if (k == v.k + 2 || k == v.k - 2) continue;
			if (v.s < 4 && v.k != -1 && v.k != k) continue;
			int ii = v.i+go[k][0];
			int jj = v.j+go[k][1];
			if (ii < 0 || jj < 0 || ii >= n || jj >= n) continue;
			int ss = k == v.k ? v.s + 1 : 1;
			int dd = v.d + map[ii][jj] - '0';
			if (d[ii][jj][k][ss] <= dd || ss > 10) continue;
			d[ii][jj][k][ss] = dd;
			push((node_t){.i=ii, .j=jj, .k=k, .s=ss, .d=dd});
		}
	}

	printf("%d\n", v.d);
	return 0;
}
