/*
I have lost my code for part one. It reused some stuff from day 10.
This code can be adjusted to work for part one, just change the input reading.
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

typedef struct { int64_t i, j; } point_t;

char *buf, in[50];
int64_t k, l, oldl, n, r, t, nolda, nb, a[N], olda[N], b[N];
point_t p[N];
point_t go[] = {{.i=0, .j=1}, {.i=1, .j=0}, {.i=0, .j=-1}, {.i=-1, .j=0}};

int cmp_int64(const void *x, const void *y) {
	const int64_t *a = x, *b = y;
	return *a > *b ? 1 : (*a < *b) ? -1 : 0;
}

int cmp_point(const void *x, const void *y) {
	const point_t *p = x, *q = y;
	int a = cmp_int64(&p->i, &q->i);
	int b = cmp_int64(&p->j, &q->j);
	return a ? a : b;
}

int64_t val(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	return c - 'a' + 10;
}

int64_t removedoubles(int64_t a[], int64_t n) {
	int64_t i, j = 0;
	for (i = 0; i < n; i++) {
		a[j] = a[i];
		if (i+1 < n && a[j] == a[i+1])
			i++;
		else
			j++;
	}
	return j;
}

int64_t overlaplen(int64_t a[], int64_t na, int64_t b[], int64_t nb) {
	int64_t ret = 0;
	for (int64_t i = 0; 2*i+1 < na; i++)
		for (int64_t j = 0; 2*j+1 < nb; j++)
			ret += MAX(0,
			    MIN(a[2*i+1], b[2*j+1]) - MAX(a[2*i], b[2*j]) + 1);
	return ret;
}

int64_t linelen(int64_t a[], int64_t n) {
	return overlaplen(a, n, a, n);
}

int main() {
	p[n++] = (point_t) {0};
	while ((buf = fgets(in, 50, stdin)) != NULL) {
		while (*buf != '#') buf++;
		k = 0;
		for (int i = 1; i < 6; i++)
			k = 16*k + val(*(buf+i));
		point_t d = go[*(buf+6) - '0'];
		p[n] = (point_t){.i = p[n-1].i+d.i*k, .j = p[n-1].j+d.j*k};
		n++;
	}

	qsort(p, --n, sizeof(point_t), &cmp_point);

	for (int64_t i = 0, ia = 0; i < n-1; i++) {
		a[ia++] = p[i].j;
		if (p[i].i != p[i+1].i) {
			qsort(a, ia, sizeof(int64_t), &cmp_int64);
			ia = removedoubles(a, ia);
			t += linelen(a, ia) * (p[i+1].i - p[i].i + 1) -
			    overlaplen(a, ia, olda, nolda);
			nolda = ia;
			memcpy(olda, a, nolda * sizeof(int64_t));
		}
	}

	printf("%" PRId64 "\n", t);
	return 0;
}
