import fileinput
from functools import reduce
from operator import mul

a = []
op = []
with fileinput.input() as lines:
	for line in lines:
		t = line[:-1].split(' ')
		if t[0] == '+' or t[0] == '*':
			op = [x for x in t if x != '']
		else:
			a.append([int(x) for x in t if x != ''])

def sol(a, op, i):
	return (sum(a[j][i] for j in range(len(a))) if op[i] == '+'
	        else reduce(mul, (a[j][i] for j in range(len(a))), 1))
	

print(sum(sol(a, op, i) for i in range(len(a[0]))))
