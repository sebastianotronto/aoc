/*
This one is a bit weird. This program works only for my specific input.
Similarly to day 8, this program outputs 4 numbers and you have to
take the lcm of them.

I solved it this way:
1. First, using a modified version of the code for part one (graph.c),
   I printed the graph as a list of adjacency lists.
2. I then went to https://csacademy.com/app/graph_editor and observed
   the graph. I noticed that after the button is pressed, the signal
   is sent to 4 independent parts of the graph. Each of these parts has
   only one entry point and one exit point. The entry points were not
   flip-flop nodes.
3. Finally, I implemented the code to check how long it takes for the
   graph to go back to the initial state, and I simulated sending a
   signal to each of the 4 parts independently.
*/

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 100
#define ischar(c) (c >= 'a' && c <= 'z')

typedef struct {
	int nin, nout, in[N], out[N];
	char name[20], outc[N][20];
	bool isff, ison, reg[N];
} node_t;

typedef struct {
	int i, n;
	struct {int node; bool hi;} elem[500];
} queue_t;

char *buf, line[N][N];
bool rx;
int b, r, n;
node_t m[N];
queue_t q;

void add(int v, bool hi) {
	q.elem[q.n].node = v;
	q.elem[q.n].hi = hi;
	q.n++;
}

void send(int v, bool hi) {
	for (int j = 0; j < m[v].nout; j++) {
		add(m[v].out[j], hi);
		m[m[v].out[j]].reg[v] = hi;
	}
}

int findm(char *name) {
	for (int k = 0; k < n; k++)
		if (!strcmp(m[k].name, name))
			return k;
	return n;
}

void sig(int node, bool high) {
	q.n = q.i = 0;
	add(node, high);
	while (q.i < q.n) {
		int v = q.elem[q.i].node;
		bool hi = q.elem[q.i].hi;
		q.i++;

		if (v == b) {
			send(v, hi);
		} else if (m[v].isff) {
			if (!hi)
				send(v, m[v].ison = !m[v].ison);
		} else {
			bool allhi = true;
			for (int j = 0; j < m[v].nin; j++)
				allhi = allhi && m[v].reg[m[v].in[j]];
			send(v, !allhi);
		}
	}
}

bool isclean(void) {
	for (int i = 0; i < n; i++) {
		if (m[i].isff && m[i].ison)
			return false;
		else
			for (int j = 0; j < m[i].nin; j++)
				if (m[i].reg[j])
					return false;
	}
	return true;
}

int64_t period(int node) {
	int64_t npush;
	for (npush = 0; npush == 0 || !isclean(); npush++)
		sig(node, false);
	return npush;
}

int main() {
	for (n = 0; (buf = fgets(line[n], N, stdin)) != NULL; n++) {
		if (ischar(*buf)) b = n;
		m[n].isff = *buf == '%';
		if (!ischar(*buf)) buf++;
		for (int i = 0; ischar(*buf); m[n].name[i++] = *(buf++)) ;
		buf += 4;
		for (int i = 0; *buf != '\n'; i++) {
			while (!ischar(*buf)) buf++;
			for (int j = 0; ischar(*buf); m[n].outc[i][j++] = *(buf++)) ;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; m[i].outc[j][0]; j++) {
			int k = findm(m[i].outc[j]);
			m[i].out[m[i].nout++] = k;
			m[k].in[m[k].nin++] = i;
			if (k == n) {
				for (int k = 0; m[i].outc[j][k]; k++)
					m[n].name[k] = m[i].outc[j][k];
				n++;
			}
		}
	}

	for (int i = 0; i < n; i++)
		if (!strcmp(m[i].name, "rx"))
			r = i;

	printf("%" PRId64 "\n", period(19));
	printf("%" PRId64 "\n", period(33));
	printf("%" PRId64 "\n", period(39));
	printf("%" PRId64 "\n", period(57));
	return 0;
}
