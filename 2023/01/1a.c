#include <stdio.h>

#define N 10000

int main() {
	char *buf, line[N];
	int first, last, sum;

	sum = 0;
	while ((buf = fgets(line, N, stdin)) != NULL) {
		for (first = -1; *buf; buf++) {
			if (*buf < '0' || *buf > '9')
				continue;
			first = first == -1 ? *buf - '0' : first;
			last = *buf - '0';
		}
		sum += 10 * first + last;
	}
	printf("%d\n", sum);
	return 0;
}
