#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 1500
#define ischar(c) (c >= 'a' && c <= 'z')

typedef struct { int nout, out[N]; char s[4], outc[N][4]; } node_t;

bool visited[N];
char *buf, line[N][N];
int n, nother, c[N][N], f[N][N];
node_t m[N];

int findm(char *s) {
	for (int k = 0; k < n; k++)
		if (m[k].s[0] == s[0] && m[k].s[1] == s[1] && m[k].s[2] == s[2])
			return k;
	return n;
}

void resetfc(void) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m[i].nout; j++)
			c[i][m[i].out[j]] = 1;
	for (int i = 0; i < n; i++)
		memset(f[i], 0, N * sizeof(int));
}

bool dfs(int v, int t) {
	if (v == t) return true;
	if (visited[v]) return false;
	visited[v] = true;
	for (int i = 0; i < m[v].nout; i++) {
		int u = m[v].out[i];
		if (c[v][u] == 0) continue;
		c[v][u]--;
		c[u][v]++;
		f[v][u]++;
		if (dfs(u, t)) return true;
		c[v][u]++;
		c[u][v]--;
		f[v][u]--;
	}
	return false;
}

bool residualpath(int s, int t) {
	memset(visited, 0, N * sizeof(bool));
	return dfs(s, t);
}

/* Ford-Fulkerson */
bool flowatmost(int s, int t, int k) {
	int flow;
	resetfc();
	for (flow = 0; flow <= k && residualpath(s, t); flow++) ;
	return flow <= k;
}

int main() {
	for (n = 0; (buf = fgets(line[n], N, stdin)) != NULL; n++) {
		for (int i = 0; ischar(*buf); m[n].s[i++] = *(buf++)) ;
		for (int i = 0; *buf != '\n'; i++) {
			while (!ischar(*buf)) buf++;
			for (int j = 0; ischar(*buf); m[n].outc[i][j++] = *(buf++)) ;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; m[i].outc[j][0]; j++) {
			int k = findm(m[i].outc[j]);
			m[i].out[m[i].nout++] = k;
			m[k].out[m[k].nout++] = i;
			if (k == n) {
				for (int k = 0; m[i].outc[j][k]; k++)
					m[n].s[k] = m[i].outc[j][k];
				n++;
			}
		}
	}

	for (int t = 1; t < n; t++)
		if (flowatmost(0, t, 3)) nother++;

	printf("%d\n", nother * (n-nother));
	return 0;
}
