#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N    300
#define XMIN 2e14
#define XMAX 4e14
#define eps  1e-6

#define ABS(x) ((x)>0?(x):-(x))

typedef struct { double x, y, z; } point_t;
typedef struct { point_t p, v; } line_t;

char *buf, line[N];
int n, s;
line_t l[N];

bool isnum(char c) { return (c >= '0' && c <= '9') || c == '-'; }

line_t readl(char *buf) {
	double a[6];
	for (int i = 0; i < 6; i++) {
		a[i] = (double)atoll(buf);
		while (isnum(*buf)) buf++;
		while (*buf != '\n' && !isnum(*buf)) buf++;
	}
	return (line_t) {
	    .p = (point_t){.x = a[0], .y = a[1], .z = a[2]},
	    .v = (point_t){.x = a[3], .y = a[4], .z = a[5]}
	};
}

double det(double a, double b, double c, double d) { return a*d-b*c; }

bool parallel2d(line_t l1, line_t l2) {
	double d = det(l1.v.x, l2.v.x, l1.v.y, l2.v.y);
	return ABS(d) < eps;
}

point_t collide2d(line_t l1, line_t l2, double *t1, double *t2) {
	double a1 = l1.v.x;
	double b1 = -l2.v.x;
	double c1 = l2.p.x - l1.p.x;
	double a2 = l1.v.y;
	double b2 = -l2.v.y;
	double c2 = l2.p.y - l1.p.y;
	
	double d = det(a1, b1, a2, b2);
	*t1 = det(c1, b1, c2, b2) / d;
	*t2 = det(a1, c1, a2, c2) / d;

	double x = l1.p.x + l1.v.x * (*t1);
	double y = l1.p.y + l1.v.y * (*t1);

	return (point_t) {.x = x, .y = y};
}

int main() {
	for (n = 0; (buf = fgets(line, N, stdin)) != NULL; n++)
		l[n] = readl(buf);

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (parallel2d(l[i], l[j])) continue;
			double t1, t2;
			point_t p = collide2d(l[i], l[j], &t1, &t2);
			if (t1 < -eps || t2 < -eps) continue;
			s += p.x > XMIN-eps && p.x < XMAX+eps &&
			     p.y > XMIN-eps && p.y < XMAX+eps;
		}
	}

	printf("%d\n", s);
	return 0;
}
