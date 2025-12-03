import fileinput

def joltage(line, n):
	if n == 0:
		return 0

	x = max(line[:len(line) - (n-1)])
	return x*10**(n-1) + joltage(line[line.index(x)+1:], n-1)

with fileinput.input() as lines:
	print(sum(joltage([int(x) for x in line[:-1]], 12) for line in lines))
