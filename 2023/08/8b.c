/*
I hate this stupid problem. There are a bunch of unwritten properties
of the paths that make the problem very simple:

- Different ghosts' paths do not end up in the same Z-node.
- Each ghost has exactly one Z-node in its path.
- Each ghost meets a Z-node exactly once before entering a loop.
- If a ghost encounters a Z-node after X steps, it will encounter it exactly
  every X steps; preperiods just end up aligning nicely.

In practice, everything just works out so that the lcm of the periods
is the solution, which is very much not the case for a general input.
This code computes the periods of the paths of the different ghosts. Then
you can figure out the solution with a pocket calculator, or by hand.
*/

#include <stdio.h>
#include <string.h>

#define N 1000

typedef struct { char last; int next[2]; } node_t;

int v[N*N];

int ind(char s[3], char m[][3], int n) {
	for (int j = 0; j < n; j++)
		if (s[0] == m[j][0] && s[1] == m[j][1] && s[2] == m[j][2])
			return j;
	return -1;
}

int findperiod(int i, node_t *nodes, char *dir, int n, int k) {
	memset(v, 0, sizeof(int) * N*N);
	for (int j = i, d = 0, l = 1, state = -1; ; d = (d+1)%k) {
		j = nodes[j].next[dir[d] == 'R'];
		state = j*k+d;
		if (v[state]) return l - v[state];
		else v[state] = l++;
	}
	return -1;
}

int main() {
	node_t nodes[N];
	char *buf, dir[N], line[N], name[N][3], lstr[N][3], rstr[N][3];
	int k, n;

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

	for (int i = 0; i < n; i++) {
		nodes[i].next[0] = ind(lstr[i], name, n);
		nodes[i].next[1] = ind(rstr[i], name, n);
	}

	for (int i = 0; i < n; i++)
		if (nodes[i].last == 'A')
			printf("%d\n", findperiod(i, nodes, dir, n, k));

	return 0;
}
