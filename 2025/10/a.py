import fileinput

def readline(line):
	m = 0
	for i in range(1, line.index(']')):
		if line[i] == '#':
			m |= 1 << (i-1)

	b = []
	j = line.index(']')
	while '(' in line[j:]:
		i = line[j:].index('(') + j + 1
		j = line[i:].index(')') + i
		x = 0
		for y in line[i:j].split(','):
			x |= 1 << int(y)
		b.append(x)

	return m, b

def works(m, b, s):
	x = 0
	for j in range(len(s)):
		if s[j] == '1':
			x ^= b[j]
	return x == m

def sol(m, b):
	s = 99999999
	for i in range(2**len(b)):
		if works(m, b, bin(i)[2:].rjust(len(b), '0')):
			s = min(s, i.bit_count())
	return s

with fileinput.input() as lines:
	print(sum(sol(*readline(line)) for line in lines))

