#include <stdio.h>
#include <string.h>

#define N 10000

char *nums[10] = { "zero (unused)", "one", "two", "three", "four", "five",
	"six", "seven", "eight", "nine" };

int main() {
	char *buf, line[N];
	int j, first, last, sum;

	sum = 0;
	while ((buf = fgets(line, N, stdin)) != NULL) {
		for (first = -1; *buf; buf++) {
			for (j = 1; j < 10; j++)
				if (!strncmp(buf, nums[j], strlen(nums[j])))
					*buf = j + '0';
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
