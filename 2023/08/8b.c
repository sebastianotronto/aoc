/*
I hate this stupid problem. If you read the description carefully (which is
what I did), you would think that the problem is much, much harder than it
actually is. In reality, the author made many assumptions about the possible
paths that made is super easy. Let's see a few:

- Different ghost's path do not end up in the same Z-node (this is not super
  important for the solution).
- Each ghost has exactly one Z-node in its path (one could think about this
  when reading the strange remark that "there are as many A-nodes as Z-nodes",
  which does not look important at first).
- Each ghosts meets a Z-node exactly once before entering a loop (this is
  a fundamental and incredibly strong assupmtion).
- If a ghost encounters a Z-node after X steps, it will encounter it exactly
  every X steps (like WTF I don't even have to solve a system of congruences?
  what is this, a problem for babies?)

Fuck.

This code does not even solve the problem by the way, it computes some data
about the path that each ghost takes. Then you can figure out the solution
with a pocket calculator, or by hand.
*/
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

typedef struct { char last; int next[2]; } node_t;
typedef struct { int preplen, plen, nz, z[N], zid[N]; } source_t;

int ind(char s[3], char m[][3], int n) {
	for (int j = 0; j < n; j++)
		if (s[0] == m[j][0] && s[1] == m[j][1] && s[2] == m[j][2])
			return j;

	return -1;
}

int v[N*N];
source_t worksource(int i, node_t *nodes, char *dir, int n, int k) {
	source_t s;
	int state;

printf("Working source %d\n", i);

	memset(v, 0, sizeof(int) * N*N);
	for (int j = i, d = 0, l = 1; true; d = (d+1)%k) {
		j = nodes[j].next[dir[d] == 'R'];
		state = j*k+d;
if (nodes[j].last == 'Z') printf("Found Z %d at %d\n", j, l);
		if (v[state]) {
			s.preplen = v[state]-1;
			s.plen = l - v[state];
printf("Stopping at %d. Preperiod: %d, period: %d\n", l, s.preplen, s.plen);
			return s;
		} else v[state] = l++;
	}

	return s;
}

int main() {
	node_t nodes[N];
	source_t src[N];
	char *buf, dir[N], line[N], name[N][3], lstr[N][3], rstr[N][3];
	int k, i, n, m, s;

	k = strlen(fgets(dir, N, stdin)) - 1;
	fgets(line, N, stdin);
	for (n = 0; (buf = fgets(line, N, stdin)) != NULL; n++) {
		memcpy(name[n], buf, 3);
		nodes[n].last = name[n][2];
		while (*buf != '(') buf++;
		memcpy(lstr[n], buf+1, 3);
		while (*buf != ' ') buf++;
		memcpy(rstr[n], buf+1, 3);
	}

	for (i = 0; i < n; i++) {
		nodes[i].next[0] = ind(lstr[i], name, n);
		nodes[i].next[1] = ind(rstr[i], name, n);
	}

printf("%d %d\n", n, k);

	for (i = 0, m = 0; i < n; i++)
		if (nodes[i].last == 'A')
			src[m++] = worksource(i, nodes, dir, n, k);

	return 0;
}
