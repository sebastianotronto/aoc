import fileinput
from functools import reduce
from operator import mul

with fileinput.input() as lines:
	all = list(lines)
	a = [line[:-1] for line in all[:-1]]
	op = all[-1][:-1]

def sol(a, j, k):
	nums = []
	i = k-2
	while i >= j:
		n = 0
		for r in a:
			if r[i] != ' ':
				n = 10*n + int(r[i])
		nums.append(n)
		i -= 1
	return sum(nums) if op[j] == '+' else reduce(mul, nums, 1)

j = 0
s = 0
while j < len(op):
	k = j+1
	while k < len(op) and op[k] == ' ':
		k += 1
	if k >= len(op):
		k = max(len(r) for r in a)+1
	s += sol(a, j, k)
	j = k
print(s)
