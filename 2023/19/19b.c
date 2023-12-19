#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define MAX(x,y) ((x)>(y)?(x):(y))

typedef struct { int64_t val[26]; } part_t;
typedef struct { char v, comp, wnext[10]; int64_t b; } rule_t;
typedef struct { char name[50]; int64_t n; rule_t r[100]; } workflow_t;

int64_t nw, A;
workflow_t w[N];
part_t p[N];

workflow_t readw(char *buf) {
	workflow_t ret = {0};
	for (int i = 0; *buf != '{'; buf++, i++)
		ret.name[i] = *buf;
	for (rule_t r; *buf != '}'; ret.r[ret.n++] = r) {
		buf++;
		memset(&r, 0, sizeof(r));
		if (*(buf+1) == '<' || *(buf+1) == '>') {
			r.v = *buf;
			r.comp = *(buf+1);
			r.b = atoll(buf+2);
			while (*buf != ':') buf++;
			buf++;
		}
		for (int i = 0; *buf != ',' && *buf != '}'; buf++, i++)
			r.wnext[i] = *buf;
	}
	return ret;
}

workflow_t findw(char *name) {
	for (int i = 0; i < nw; i++)
		if (!strcmp(name, w[i].name))
			return w[i];
	printf("Error: workflow %s not found\n", name);
	exit(1);
}

int64_t work(workflow_t ww, int64_t lox, int64_t hix, int64_t lom, int64_t him,
    int64_t loa, int64_t hia, int64_t los, int64_t his) {
	if (lox > hix || lom > him || loa > hia || los > his)
		return 0;

	int64_t ret = 0;
	for (int j = 0; j < ww.n; j++) {
		int64_t lox1 = lox, hix1 = hix, lom1 = lom, him1 = him,
			loa1 = loa, hia1 = hia, los1 = los, his1 = his;
		rule_t r = ww.r[j];
		switch (r.v) {
		case 'x':
			if (r.comp == '<') { hix1 = r.b-1; lox = r.b; }
			else { lox1 = r.b+1, hix = r.b; }
			break;
		case 'm':
			if (r.comp == '<') { him1 = r.b-1; lom = r.b; }
			else { lom1 = r.b+1, him = r.b; }
			break;
		case 'a':
			if (r.comp == '<') { hia1 = r.b-1; loa = r.b; }
			else { loa1 = r.b+1, hia = r.b; }
			break;
		case 's':
			if (r.comp == '<') { his1 = r.b-1; los = r.b; }
			else { los1 = r.b+1, his = r.b; }
			break;
		default:
			break;
		}
		ret += (r.wnext[0] == 'A' || r.wnext[0] == 'R') ?
			MAX(0, hix1-lox1+1) * MAX(0, him1-lom1+1) *
			    MAX(0, hia1-loa1+1) * MAX(0, his1-los1+1) *
			    (r.wnext[0] == 'A')
			:
			work(findw(r.wnext), lox1, hix1,
			    lom1, him1, loa1, hia1, los1, his1);
	}

	return ret;
}

int main() {
	char *buf, line[N];

	for (nw = 0; *(buf = fgets(line, N, stdin)) != '\n'; nw++)
		w[nw] = readw(buf);

	int64_t s = work(findw("in"), 1, 4000, 1, 4000, 1, 4000, 1, 4000);

	printf("%" PRId64 "\n", s);
	return 0;
}
