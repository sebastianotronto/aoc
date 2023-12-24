/*
Due to numerical errors, the result of this program was not correct on my
machine (ahah - doesn't work on my machine (: )
However, with slightly different values for eps I got two answers whose
difference was 4 and one was too high, the other too low. A quick binary
search gave the correct result.
I'll make a more stable version if I feel like it. EDIT: made slighly more
numerically stable, now the result is actually correct (if rounded to the
nearest integer).
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define D 10
#define N 300

#define ABS(x) ((x)>0?(x):-(x))
#define eps 1e-10
#define EQ(x,y) (ABS((x)-(y))<eps*(ABS(x)+ABS(y)))

typedef struct { double x, y, z; } point_t;
typedef struct { point_t p, v; } line_t;

char *buf, line[N];
int nlines, s;
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

void swap(double *x, double *y) { double aux = *x; *x = *y; *y = aux; }

void printa(double A[D][D], double C[D], int d) {
	for (int i = 0; i < d; i++) {
		printf("[ ");
		for (int j = 0; j < d; j++)
			printf("%.2lf ", A[i][j]);
		printf("]\t[%.2lf]\n", C[i]);
	}
}

/* Solve the linear system AX = C with row reduction */
/* Return true if it has a unique solution, false in any other case */
bool solvesystem(double A[D][D], double C[D], int d, double *X) {
	/* Row reduction */
	for (int i = 0; i < d; i++) {
		/* Make first nonzero */
		int imax;
		double maxi = 0.0;
		for (int j = i; j < d; j++) {
			if (A[j][i] > maxi) {
				maxi = A[j][i];
				imax = j;
			}
		}
		if (EQ(maxi, 0.0)) return false;
		swap(&C[i], &C[imax]);
		for (int j = 0; j < d; j++)
			swap(&A[i][j], &A[imax][j]);

		/* Reduce rows */
		for (int ii = i+1; ii < d; ii++) {
			double r = A[ii][i] / A[i][i];
			for (int k = i; k < d; k++)
				A[ii][k] -= r*A[i][k];
			C[ii] -= r*C[i];
		}
	}

	/* Back substitution */
	for (int i = d-1; i >= 0; i--) {
		X[i] = C[i];
		for (int j = i+1; j < d; j++)
			X[i] -= A[i][j]*X[j];
		X[i] /= A[i][i];
	}
	
	return true;
}

bool equal(point_t p, point_t q) {
	return EQ(p.x, q.x) && EQ(p.y, q.y) && EQ(p.z, q.z);
}

point_t pos(line_t l, double t) {
	return (point_t) {
	    .x = l.p.x + t*l.v.x,
	    .y = l.p.y + t*l.v.y,
	    .z = l.p.z + t*l.v.z
	};
}

void testsolution(line_t sol) {
	for (int i = 0; i < nlines; i++) {
		double t = -1.0;
		if (!EQ(sol.v.x, l[i].v.x))
			t = (sol.p.x-l[i].p.x)/(l[i].v.x-sol.v.x);
		if (!EQ(sol.v.y, l[i].v.y))
			t = (sol.p.y-l[i].p.y)/(l[i].v.y-sol.v.y);
		if (!EQ(sol.v.z, l[i].v.z))
			t = (sol.p.z-l[i].p.z)/(l[i].v.z-sol.v.z);
		point_t p1 = pos(sol, t), p2 = pos(l[i], t);
		/*
		printf("Line %d intersected at t = %.2lf "
		       "in (%.2lf, %.2lf, %.2lf) and (%.2lf, %.2lf, %.2lf)\n",
		       i, t, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
		*/
		if (t < eps ||
		    !EQ(p1.x, p2.x) || !EQ(p1.y, p2.y) || !EQ(p1.z, p2.z)) {
			printf("Error!\n");
			return;
		}
	}
	printf("All lines intersected correctly, solution is valid\n");
}

int main() {
	for (nlines = 0; (buf = fgets(line, N, stdin)) != NULL; nlines++)
		l[nlines] = readl(buf);

	/* To figure the correct starting point + velocity, we solve some
	 * systems of linear equations. Write your starting point and velocity
	 * as unknowns x, y, z, Vx, Vy, Vz. Equating the position of the
	 * rock at time t1 (another unknown parameter) with the position
	 * of one of the hailstones at the same time t1, we get a system
	 * of 3 equations and 7 unknowns. Unfortunately, these equations
	 * have degree 2 - this is not a linear system!
	 * However, manipulating these equations a bit we can get a linear
	 * equation of the type:
	 *     (Vy1-Vy2)x - (Vx1-Vx2)y + - (y1-y2)Vx + (x1-x2)Vy =
	 *         y2Vx2 + x2Vy2 - y1Vx1 - x1Vy1
	 * Where x1, y1, z2, Vx1, Vy1, Vz1 and x2, y2, z2, Vx2, Vy2, Vz2
	 * are the starting points and velocities of two of the hailstones.
	 * So with 2 lines we can get a linear equation. Similarly, we can
	 * get equations involving the unknowns z and Vz.
	 * We can use the myriad of hailstones we have to generate as many
	 * equations as we like. The system is going to be overdetermined,
	 * but the problem statement seems to ensure that there is going to
	 * be a solution. On the other hand it can happen that we make a
	 * bad choice of lines and the equation we use are underdetermined.
	 * This last problem is not accounted for in the code - if it happens,
	 * one can shuffle the input file until it works.
	 */
	int d = 6;
	double A[D][D] = {
		/* First equation: lines 0 and 1, x and y only */
		{l[0].v.y-l[1].v.y, l[1].v.x-l[0].v.x, 0.0,
		    l[1].p.y-l[0].p.y, l[0].p.x-l[1].p.x, 0.0},
		/* Second equation: lines 0 and 2, x and y only */
		{l[0].v.y-l[2].v.y, l[2].v.x-l[0].v.x, 0.0,
		    l[2].p.y-l[0].p.y, l[0].p.x-l[2].p.x, 0.0},
		/* Third equation: lines 0 and 1, x and z only */
		{l[0].v.z-l[1].v.z, 0.0, l[1].v.x-l[0].v.x,
		    l[1].p.z-l[0].p.z, 0.0, l[0].p.x-l[1].p.x},
		/* Fourth equation: lines 0 and 2, x and z only */
		{l[0].v.z-l[2].v.z, 0.0, l[2].v.x-l[0].v.x,
		    l[2].p.z-l[0].p.z, 0.0, l[0].p.x-l[2].p.x},
		/* Fifth equation: lines 0 and 1, y and z only */
		{0.0, l[0].v.z-l[1].v.z, l[1].v.y-l[0].v.y,
		    0.0, l[1].p.z-l[0].p.z, l[0].p.y-l[1].p.y},
		/* Sixth equation: lines 0 and 2, y and z only */
		{0.0, l[0].v.z-l[2].v.z, l[2].v.y-l[0].v.y,
		    0.0, l[2].p.z-l[0].p.z, l[0].p.y-l[2].p.y},
	};
	double C[D] = {
		/* First equation: lines 0 and 1, x and y only */
		l[1].p.y*l[1].v.x - l[1].p.x*l[1].v.y 
		    - l[0].p.y*l[0].v.x + l[0].p.x*l[0].v.y,
		/* Second equation: lines 0 and 2, x and y only */
		l[2].p.y*l[2].v.x - l[2].p.x*l[2].v.y 
		    - l[0].p.y*l[0].v.x + l[0].p.x*l[0].v.y,
		/* Third equation: lines 0 and 1, x and z only */
		l[1].p.z*l[1].v.x - l[1].p.x*l[1].v.z 
		    - l[0].p.z*l[0].v.x + l[0].p.x*l[0].v.z,
		/* Fourth equation: lines 0 and 2, x and z only */
		l[2].p.z*l[2].v.x - l[2].p.x*l[2].v.z 
		    - l[0].p.z*l[0].v.x + l[0].p.x*l[0].v.z,
		/* Fifth equation: lines 0 and 1, y and z only */
		l[1].p.z*l[1].v.y - l[1].p.y*l[1].v.z 
		    - l[0].p.z*l[0].v.y + l[0].p.y*l[0].v.z,
		/* Sixth equation: lines 0 and 2, y and z only */
		l[2].p.z*l[2].v.y - l[2].p.y*l[2].v.z 
		    - l[0].p.z*l[0].v.y + l[0].p.y*l[0].v.z,
	};
	double X[d];
	if (!solvesystem(A, C, d, X)) {
		printf("No unique solution, shuffle input and try again.\n");
		exit(1);
	}

	line_t sol = {
		.p = {.x = X[0], .y = X[1], .z = X[2]},
		.v = {.x = X[3], .y = X[4], .z = X[5]}
	};
	testsolution(sol);

	printf("p = (%.2lf, %.2lf, %.2lf), v = (%.2lf, %.2lf, %.2lf)\n",
	    sol.p.x, sol.p.y, sol.p.z, sol.v.x, sol.v.y, sol.v.z);
	printf("%lf\n", sol.p.x + sol.p.y + sol.p.z);
	return 0;
}
