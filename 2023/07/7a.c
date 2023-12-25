#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100000

int value[255] = {
	['2'] = 2, ['3'] = 3, ['4'] = 4, ['5'] = 5,
	['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9,
	['T'] = 10, ['J'] = 11, ['Q'] = 12, ['K'] = 13, ['A'] = 14
};

typedef struct { char c[5]; int64_t b; } hand_t;

int strength(hand_t h) {
	int i, c2, c1, s, x[15];

	memset(x, 0, 15 * sizeof(int));
	for (i = 0, s = 0; i < 5; i++) {
		s = s * 15 + value[(int)h.c[i]];
		x[value[(int)h.c[i]]]++;
	}
	for (i = 2, c1 = 0, c2 = 0; i < 15; i++) {
		if (c1 < x[i]) {
			c2 = c1;
			c1 = x[i];
		} else if (c2 < x[i]) c2 = x[i];
	}

	return (c1*5 + c2) * 759375 + s;
}

int compare(const void *h1, const void *h2) {
	return strength(*(hand_t *)h1) - strength(*(hand_t *)h2);
}

int main() {
	char line[N];
	hand_t hand[N];
	int64_t i, n, p;

	for (n = 0; fgets(line, N, stdin) != NULL; n++) {
		memcpy(hand[n].c, line, 5);
		hand[n].b = atoll(line+6);
	}

	qsort(hand, n, sizeof(hand_t), &compare);

	for (i = 0, p = 0; i < n; i++)
		p += hand[i].b * (i+1);

	printf("%" PRId64 "\n", p);
	return 0;
}
