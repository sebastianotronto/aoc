#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define ISNUM(c) (c >= '0' && c <= '9')
#define ISSYM(c) (c != '.' && c != 0 && c != '\n' && !ISNUM(c))

int grab(char *buf) {
	if (!ISNUM(*buf)) return 0;
	while (ISNUM(*buf)) buf--;
	buf++;
	int x = atoi(buf);
	while (ISNUM(*buf)) *buf++ = '.';

	return x;
}

int main() {
	char line[N], prev[N];
	int i, sum;

	sum = 0;
	memset(line, '.', N);
	memset(prev, '.', N);
	while (fgets(&line[1], N-1, stdin) != NULL) {
		for (i = 1; line[i]; i++) {
			if (ISSYM(line[i-1]) || ISSYM(line[i+1]) ||
			    ISSYM(prev[i-1]) || ISSYM(prev[i]) || ISSYM(prev[i+1]))
				sum += grab(&line[i]);
			if (ISSYM(line[i-1]) || ISSYM(line[i]) || ISSYM(line[i+1]))
				sum += grab(&prev[i]);
		}
		memcpy(prev, line, N);
	}

	printf("%d\n", sum);
	return 0;
}
