#include <inttypes.h>
#include <stdio.h>

#define N 100000

char *b, line[N];
int64_t c, l, s, n[256], box[256][N];

int main() {
	fgets(line, N, stdin);

	for (b = line, c = 0; *b != '\n'; b++) {
		switch (*b) {
		case ',':
			c = l = 0;
			break;
		case '=':
			int64_t i;
			for (i = 0; i < n[c]; i++)
				if (box[c][i] / 10 == l)
					break;
			if (i == n[c]) n[c]++;
			box[c][i] = l * 10 + (int)(*(++b)-'0');
			break;
		case '-':
			for (int64_t i = 0; i < n[c]; i++) {
				if (box[c][i] / 10 == l) {
					for (int j = i+1; j < n[c]; j++)
						box[c][j-1] = box[c][j];
					n[c]--;
				}
			}
			break;
		default:
			c = (c + (int)*b) * 17 % 256;
			l = l*256 + (int)*b;
			break;
		}
	}

	for (int64_t i = 0; i < 256; i++)
		for (int64_t j = 0; j < n[i]; j++)
			s += (i+1) * (j+1) * (box[i][j]%10);

	printf("%" PRId64 "\n", s);
	return 0;
}
