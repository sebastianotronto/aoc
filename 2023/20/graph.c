/* Picture generated with https://csacademy.com/app/graph_editor/ */

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

char *buf, line[N][N];
bool rx;
int b, r, n;
int64_t npush;
node_t m[N];

int findm(char *name) {
	for (int k = 0; k < n; k++)
		if (!strcmp(m[k].name, name))
			return k;
	return n;
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

/* Print adjacency list
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d", m[i].nout);
		for (int j = 0; j < m[i].nout; j++)
			printf(" %d", m[i].out[j]);
		printf("\n");
	}
	printf("broadcaster = %d, r = %d\n", b, r);
*/

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m[i].nout; j++)
			printf("%d %d\n", i, m[i].out[j]);

	return 0;
}
