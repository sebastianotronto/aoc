#include <stdio.h>

#define N 1000

typedef enum { EAST, SOUTH, WEST, NORTH } direction_t;

int main() {
	char map[N][N];
	int i, j, k, n, s;
	direction_t dir;

	for (n = 0; fgets(map[n], N, stdin) != NULL; n++) ;

	for (i = 0; i < n; i++)
		for (j = 0; map[i][j]; j++)
			if (map[i][j] == 'S')
				goto found_s;

found_s:
	if (map[i][j+1] ==  '7' || map[i][j+1] == '-' || map[i][j+1] == 'J') {
		j++;
		dir = EAST;
		goto found_direction;
	}
	if (map[i+1][j] ==  'L' || map[i+1][j] == '|' || map[i+1][j] == 'J') {
		i++;
		dir = SOUTH;
		goto found_direction;
	}
	if (j > 0 && (map[i][j-1] ==  'L' || map[i][j-1] == '-' || map[i][j-1] == 'F')) {
		j--;
		dir = WEST;
		goto found_direction;
	}

found_direction:
	for (k = 1; map[i][j] != 'S'; k++) {
		switch (map[i][j]) {
		case '|':
			if (dir == SOUTH) i++;
			if (dir == NORTH) i--;
			break;
		case '-':
			if (dir == EAST) j++;
			if (dir == WEST) j--;
			break;
		case '7':
			if (dir == EAST) { i++; dir = SOUTH; }
			if (dir == NORTH) { j--; dir = WEST; }
			break;
		case 'F':
			if (dir == WEST) { i++; dir = SOUTH; }
			if (dir == NORTH) { j++; dir = EAST; }
			break;
		case 'J':
			if (dir == EAST) { i--; dir = NORTH; }
			if (dir == SOUTH) { j--; dir = WEST; }
			break;
		case 'L':
			if (dir == WEST) { i--; dir = NORTH; }
			if (dir == SOUTH) { j++; dir = EAST; }
			break;
		default:
			printf("Error: dead path\n");
			return 1;
		}
	}

	s = (k+1)/2;

	printf("%d\n", s);
	return 0;
}
