#include <stdio.h>
#include <string.h>

#define N 30000
#define ISNUM(c) (c >= '0' && c <= '9')

int map[N][2];

int index(char *c) { return c[0]-'A' + (c[1]-'A' + (c[2]-'A')*26)*26; }

int main() {
	char *buf, dir[N], line[N];
	int n, i, s;

	n = strlen(fgets(dir, N, stdin)) - 1;

	fgets(line, N, stdin);
	while ((buf = fgets(line, N, stdin)) != NULL) {
		i = index(buf);
		while (*buf != '(') buf++;
		map[i][0] = index(buf+1);
		while (*buf != ' ') buf++;
		map[i][1] = index(buf+1);
	}

	for (i = index("AAA"), s = 0; i != index("ZZZ"); s++)
		i = map[i][dir[s % n] == 'R'];

	printf("%d\n", s);
	return 0;
}
