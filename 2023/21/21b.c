/*
This is another problem I did not enjoy. Once again, it was only solvable
because of the carefully crafted input case. This makes the problem
solvable, but at the same time it leaves you wondering - which unsaid
assumptions are true and which are not?

For example, in my first 14 attempts or so I assumed that every non-# cell
was reached at the same time as if there were no #-cells. A reasonable
assumption, and almost true. Unfortunately there were some cells that
were completely enclosed by #-cells, and thus unreachable. See fuckyou.png
and fuckyou2.png.
*/

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200
#define S 202300L /* My input was 202300*131+65 */

char map[N][N];
int64_t n;

int go(char m[][N], int i, int j) {
	if (i >= 0 && j >= 0 && i < n && j < n && m[i][j] == '.') {
		m[i][j] = 'S';
		return 1;
	}
	return 0;
}

int64_t flood(int64_t x, int64_t y, int64_t steps) {
	int64_t c, i, j;
	char tmp[N][N];
	for (int i = 0; i < n; i++) memcpy(tmp[i], map[i], n*sizeof(char));
	tmp[x][y] = 'S';
	for (int s = 0; s < steps; s++) {
		for (i = 0, c = 0; i < n; i++) {
			for (j = (s+x+y+i)%2; j < n; j += 2) {
				if (tmp[i][j] == 'S') {
					tmp[i][j] = '.';
					c += go(tmp, i-1, j) +
					     go(tmp, i+1, j) +
					     go(tmp, i, j-1) +
					     go(tmp, i, j+1);
				}
			}
		}
	}
	return c;
}

int main() {
	for (n = 0; fgets(map[n], N, stdin) != NULL; n++) ;
	map[n/2][n/2] = '.';

	int64_t fulleven = flood(n/2, n/2, n-1);
	int64_t fullodd = flood(n/2, n/2, n);
	int64_t arrowr = flood(n/2, 0, n-1);
	int64_t arrowl = flood(n/2, n-1, n-1);
	int64_t arrowd = flood(0, n/2, n-1);
	int64_t arrowu = flood(n-1, n/2, n-1);
	int64_t topl = flood(0, 0, n/2-1);
	int64_t topr = flood(0, n-1, n/2-1);
	int64_t botl = flood(n-1, 0, n/2-1);
	int64_t botr = flood(n-1, n-1, n/2-1);
	int64_t cutbr = flood(0, 0, n/2+n-1);
	int64_t cutbl = flood(0, n-1, n/2+n-1);
	int64_t cuttr = flood(n-1, 0, n/2+n-1);
	int64_t cuttl = flood(n-1, n-1, n/2+n-1);

	int64_t fulls = S*S*fulleven + (S-1)*(S-1)*fullodd;
	int64_t smallborder = S*(topl + topr + botl + botr);
	int64_t bigborder = (S-1)*(cutbr + cutbl + cuttr + cuttl);
	int64_t arrows = arrowr + arrowl + arrowu + arrowd;
	int64_t final = fulls + smallborder + bigborder + arrows;

	printf("%" PRId64 "\n", final);

	return 0;
}
