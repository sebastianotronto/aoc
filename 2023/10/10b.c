#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define set(i, j, c) if (newmap[i][j] == '.') newmap[i][j] = c;

typedef enum { EAST, SOUTH, WEST, NORTH } direction_t;

char map[N+2][N+2], newmap[N+2][N+2];
int n, si, sj, count[26] = {0};
direction_t sdir;

void printmap(char m[][N+2]) {
	for (int i = 1; i < n; i++) {
		for (int j = 1; m[i][j] != 'B'; j++)
			printf("%c", m[i][j]);
		printf("\n");
	}
}

void color_rl(direction_t dir, int i, int j) {
	switch (dir) {
	case EAST:
		set(i-1, j, 'L');
		set(i+1, j, 'R');
		break;
	case SOUTH:
		set(i, j+1, 'L');
		set(i, j-1, 'R');
		break;
	case WEST:
		set(i-1, j, 'R');
		set(i+1, j, 'L');
		break;
	case NORTH:
		set(i, j+1, 'R');
		set(i, j-1, 'L');
		break;
	default:
		break;
	}
}

direction_t firstdir(int i, int j) {
	if (map[i][j+1] ==  '7' || map[i][j+1] == '-' || map[i][j+1] == 'J')
		return EAST;
	if (map[i+1][j] ==  'L' || map[i+1][j] == '|' || map[i+1][j] == 'J')
		return SOUTH;
	return WEST;
}

void advance(int *i, int *j, direction_t dir) {
	if (dir == EAST) { (*j)++; }
	else if (dir == SOUTH) { (*i)++; }
	else if (dir == WEST) { (*j)--; }
	else (*i)--;
}

direction_t newdir(int i, int j, direction_t dir) {
	switch (map[i][j]) {
	case '|':
	case '-':
		return dir;
	case '7':
		if (dir == EAST) return SOUTH;
		if (dir == NORTH) return WEST;
	case 'F':
		if (dir == WEST) return SOUTH;
		if (dir == NORTH) return EAST;
	case 'J':
		if (dir == EAST) return NORTH;
		if (dir == SOUTH) return WEST;
	case 'L':
		if (dir == WEST) return NORTH;
		if (dir == SOUTH) return EAST;
	default:
		printf("Error: dead path at (%d, %d)\n", i, j);
		exit(1);
	}
	return EAST;
}

void walk_and_color_rl(char c) {
	int i = si, j = sj;
	direction_t dir = sdir;

	newmap[i][j] = c;
	color_rl(dir, i, j);
	advance(&i, &j, dir);
	for (; map[i][j] != 'S'; advance(&i, &j, dir)) {
		newmap[i][j] = c;
		color_rl(dir, i, j);
		dir = newdir(i, j, dir);
		color_rl(dir, i, j);
	}
	color_rl(dir, i, j);
}

void fill(int i, int j, char c) {
	if (newmap[i][j] != '.' && newmap[i][j] != 'R' && newmap[i][j] != 'L')
		return;

	newmap[i][j] = c;
	count[c-'a']++;
	fill(i, j+1, c);
	fill(i, j-1, c);
	fill(i+1, j, c);
	fill(i-1, j, c);
}

int main() {
	/* Get input */
	for (n = 1; fgets(&map[n][1], N, stdin) != NULL; n++) ;

	/* Add borders, copy to newmap */
	for (int i = 0; i < N+2; i++) {
		for (int j = 0; j < N+2; j++) {
			newmap[i][j] = map[i][j];
			if (map[i][j] == 0 || map[i][j] == '\n')
				newmap[i][j] = map[i][j] = 'B';
		}
	}

	/* Find S and set the initial direction */
	for (si = 1; si < n; si++)
		for (sj = 1; map[si][sj] != 'B'; sj++)
			if (map[si][sj] == 'S')
				goto found_s;

found_s:
	/* Set the initial direction and walk the path mark it with X */
	sdir = firstdir(si, sj);
	walk_and_color_rl('X');

	/* Replace the unnecessary pipe symbols with dots */
	for (int i = 1; i < N; i++)
		for (int j = 1; map[i][j] != 'B'; j++)
			if (newmap[i][j] != 'X')
				newmap[i][j] = '.';

	/* Walk again the path and mark adjacent dots left and right */
	walk_and_color_rl('Y');

	/* Mark the remaining dots left and right */
	for (int i = 1; i < n; i++)
		for (int j = 1; newmap[i][j] != 'B'; j++)
			if (newmap[i][j] == 'R' || newmap[i][j] == 'L')
				fill(i, j, newmap[i][j] + 'a' - 'A');

	printmap(newmap);
	printf("r: %d\nl: %d\n", count['r'-'a'], count['l'-'a']);
	printf("Check with the map printed above which one is 'inside'\n");
	return 0;
}
