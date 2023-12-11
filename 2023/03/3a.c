#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

bool isnum(char c) { return c >= '0' && c <= '9'; }
bool issymbol(char c) { return c != '.' && c != 0 && c != '\n' && !isnum(c); }

int grab(char *buf) {
	int x;

	if (!isnum(*buf))
		return 0;

	while (isnum(*buf)) buf--;
	buf++;
	x = atoi(buf);
	while (isnum(*buf)) *buf++ = '.';

	return x;
}

int main() {
	char line[N], prev[N];
	bool l, c, r, ul, uc, ur;
	int i, sum;

	sum = 0;
	memset(line, '.', N);
	memset(prev, '.', N);
	while (fgets(&line[1], N-1, stdin) != NULL) {
		for (i = 1; line[i]; i++) {
			l = issymbol(line[i-1]);
			c = issymbol(line[i]);
			r = issymbol(line[i+1]);
			ul = issymbol(prev[i-1]);
			uc = issymbol(prev[i]);
			ur = issymbol(prev[i+1]);
			if (l || r || ul || uc || ur)
				sum += grab(&line[i]);
			if (l || c || r)
				sum += grab(&prev[i]);
		}
		memcpy(prev, line, N);
	}

	printf("%d\n", sum);
	return 0;
}
