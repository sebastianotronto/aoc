import fileinput
from functools import cache

a = {}
with fileinput.input() as lines:
	for line in lines:
		v, l2 = line[:-1].split(': ')
		a[v] = l2.split(' ')

@cache
def np(v, d, f):
	if v == 'out':
		return 1 if d and f else 0
	return sum(np(w, d or v == 'dac', f or v == 'fft') for w in a[v])

print(np('svr', False, False))
