#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define ischar(c) (c >= 'a' && c <= 'z')

typedef struct {
	int nin, nout, in[N], out[N];
	char name[20], outc[N][20];
	bool isff, ison, reg[N];
} node_t;

typedef struct {
	int i, n, node[1000];
	bool hi[1000];
} queue_t;

char *buf, line[N][N];
int b, n;
int64_t hitot, lowtot;
node_t m[N];

void add(queue_t *q, int v, bool hi) {
	q->node[q->n] = v;
	q->hi[q->n] = hi;
	q->n++;
}

void send(queue_t *q, int v, bool hi) {
	for (int j = 0; j < m[v].nout; j++) {
		add(q, m[v].out[j], hi);
		m[m[v].out[j]].reg[v] = hi;
		if (hi) hitot++; else lowtot++;
	}
}

void pushbutton(void) {
	queue_t q = {0};

	add(&q, b, false);
	lowtot++;
	while (q.i < q.n) {
		int v = q.node[q.i];
		bool hi = q.hi[q.i];
		q.i++;

		if (v == b) {
			send(&q, v, hi);
		} else if (m[v].isff) {
			if (!hi)
				send(&q, v, m[v].ison = !m[v].ison);
		} else {
			bool allhi = true;
			for (int j = 0; j < m[v].nin; j++)
				allhi = allhi && m[v].reg[m[v].in[j]];
			send(&q, v, !allhi);
		}
	}
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
			bool found = false;
			for (int k = 0; k < n; k++) {
				if (!strcmp(m[k].name, m[i].outc[j])) {
					m[i].out[m[i].nout++] = k;
					m[k].in[m[k].nin++] = i;
					found = true;
				}
			}
			if (!found) {
				m[i].out[m[i].nout++] = n;
				m[n].in[m[n].nin++] = i;
				n++;
			}
		}
	}

	for (int i = 0; i < 1000; i++)
		pushbutton();

	printf("%" PRId64 " (%" PRId64 " low, %" PRId64 " hi)\n",
	    hitot * lowtot, lowtot, hitot);
	return 0;
}
