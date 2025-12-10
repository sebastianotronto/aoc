import fileinput
from functools import cache

def readline(line):
	b = []
	j = line.index(']')
	while '(' in line[j:]:
		i = line[j:].index('(') + j + 1
		j = line[i:].index(')') + i
		x = 0
		for y in line[i:j].split(','):
			x |= 1 << int(y)
		b.append(x)

	begin = line.index('{')+1
	end = line.index('}')
	j = tuple(int(x) for x in line[begin:end].split(','))

	return tuple(b), j

def newj(j, b, n):
	return tuple(j[i]-n if b & (1<<i) else j[i] for i in range(len(j)))

def can(b, i):
	return b & (1 << i) != 0

inf = 99999999999
@cache
def sol(b, j, best):
	print(f"{b} {j} {best}")
	if all(x == 0 for x in j):
		return 0
	if any(x < 0 for x in j):
		return inf
	if len(b) == 0:
		return inf
	for i in range(len(j)):
		if j[i] > 0 and not any(can(bb, i) for bb in b):
			return inf

	# Optimization: if any of the buttons is the last one available that
	# toggles a certain jolt, we press it as much as needed.
	for i in range(len(j)):
		for k in range(len(b)):
			bb = b[:k] + b[k+1:]
			if can(b[k], i) and not any(can(x, i) for x in bb):
				return j[i] + sol(bb, newj(j, b[k], j[i]), best)

	c = 0
	while all(x >= 0 for x in j) and c <= best:
		best = min(best, c + sol(b[1:], j, best))
		j = newj(j, b[0], 1)
		c += 1

	return best

with fileinput.input() as lines:
	sols = []
	c = 1
	for line in lines:
		print(f"doing line {c}: {line}")
		c += 1
		sols.append(sol(*readline(line), inf))
	print(sols)
	print(sum(sols))

