#include <stdio.h>

#define N 102

char line[N];
int i, j, t, s[N], r[N];

int main() {
	for (i = 0; fgets(line, N, stdin) != NULL; i++) {
		for (j = 0; line[j] != '\n'; j++) {
			if (line[j] == '#') s[j] = i+1;
			if (line[j] == 'O') r[s[j]++]++;
		}
	}
	for (j = 0; j < i; j++)
		t += r[j] * (i-j);

	printf("%d\n", t);
	return 0;
}
