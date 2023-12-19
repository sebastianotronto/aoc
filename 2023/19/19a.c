#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

typedef struct { int64_t val[26]; } part_t;
typedef struct { char v, comp, wnext[10]; int64_t b; } rule_t;
typedef struct { char name[50]; int64_t n; rule_t r[100]; } workflow_t;

int64_t nw, np, A;
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

part_t readp(char *buf) {
	part_t p = {0};
	while (*buf != '}') {
		buf++;
		p.val[*buf-'a'] = atoll(buf+2);
		while(*buf != ',' && *buf != '}') buf++;
	}
	return p;
}

int64_t value(part_t p) {
	return p.val['x'-'a'] + p.val['m'-'a'] + p.val['a'-'a'] + p.val['s'-'a'];
}

bool satisfy(part_t p, rule_t r) {
	if (r.v == 0) return true;
	int64_t val = p.val[r.v-'a'];
	return r.comp == '<' ? (val < r.b) : (val > r.b);
}

workflow_t findw(char *name) {
	for (int i = 0; i < nw; i++)
		if (!strcmp(name, w[i].name))
			return w[i];
	printf("Error: workflow %s not found\n", name);
	exit(1);
}

int main() {
	char *buf, line[N];

	for (nw = 0; *(buf = fgets(line, N, stdin)) != '\n'; nw++)
		w[nw] = readw(buf);

	for (np = 0; (buf = fgets(line, N, stdin)) != NULL; np++)
		p[np] = readp(buf);

	for (int i = 0; i < np; i++) {
		workflow_t ww = findw("in");
		for (rule_t r; ; ww = findw(r.wnext)) {
			for (int64_t j = 0; !satisfy(p[i], r = ww.r[j]); j++) ;
			if (!strcmp("A", r.wnext) || !strcmp("R", r.wnext)) {
				A += value(p[i]) * (r.wnext[0] == 'A');
				break;
			}
		}
	}

	printf("%" PRId64 "\n", A);
	return 0;
}
