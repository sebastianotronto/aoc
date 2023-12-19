#include <stdio.h>

#define N 100000

char *b, line[N];
int c, s;

int main() {
	fgets(line, N, stdin);

	for (b = line, c = 0, s = 0; *b; b++) {
		if (*b == ',' || *b == '\n') {
			s += c;
			c = 0;
		} else
			c = (c + (int)*b) * 17 % 256;
	}

	printf("%d\n", s);
	return 0;
}
