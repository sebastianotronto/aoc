#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 102
#define C 10000

uint64_t h[C];
char p[C][N][N];
int e, c, n, t, s[N];

void copy_panel(int c1, int c2) {
	for (int i = 0; i < n; i++)
		memcpy(p[c2][i], p[c1][i], n+2);
}

void tilt_north(void) {
	for (int i = 0; i < n; i++) s[i] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (p[c][i][j] == '#')
				s[j] = i+1;
			if (p[c][i][j] == 'O') {
				if (s[j] != i) p[c][i][j] = '.';
				p[c][s[j]++][j] = 'O';
			}
		}
	}
}

void tilt_west(void) {
	for (int i = 0; i < n; i++) s[i] = 0;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			if (p[c][i][j] == '#')
				s[i] = j+1;
			if (p[c][i][j] == 'O') {
				if (s[i] != j) p[c][i][j] = '.';
				p[c][i][s[i]++] = 'O';
			}
		}
	}
}

void tilt_south(void) {
	for (int i = 0; i < n; i++) s[i] = n-1;
	for (int i = n-1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (p[c][i][j] == '#')
				s[j] = i-1;
			if (p[c][i][j] == 'O') {
				if (s[j] != i) p[c][i][j] = '.';
				p[c][s[j]--][j] = 'O';
			}
		}
	}
}

void tilt_east(void) {
	for (int i = 0; i < n; i++) s[i] = n-1;
	for (int j = n-1; j >= 0; j--) {
		for (int i = 0; i < n; i++) {
			if (p[c][i][j] == '#')
				s[i] = j-1;
			if (p[c][i][j] == 'O') {
				if (s[i] != j) p[c][i][j] = '.';
				p[c][i][s[i]--] = 'O';
			}
		}
	}
}

bool equal(int c1, int c2) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (p[c1][i][j] != p[c2][i][j])
				return false;
	return true;
}

int main() {
	for (n = 0; fgets(p[0][n], N, stdin) != NULL; n++) ;

	for (c = 1; c < C; c++) {
		copy_panel(c-1, c);
		tilt_north();
		tilt_west();
		tilt_south();
		tilt_east();
		for (e = 0; e < c; e++)
			if (equal(e, c))
				goto found;
	}

found:
	c = (1000000000-e) % (c-e) + e;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			t += (p[c][i][j] == 'O') * (n-i);

	printf("%d\n", t);
	return 0;
}
