import fileinput
from functools import cache

neginf = -1e13

@cache
def joltage(line, n):
	if n == 0:
		return 0
	if n > len(line)-1:
		return neginf
	j = 0
	for i in range(len(line)-1):
		j = max(j, int(line[i])*10**(n-1)+joltage(line[i+1:],n-1))
	return j

with fileinput.input() as lines:
	print(sum(joltage(line, 12) for line in lines))
