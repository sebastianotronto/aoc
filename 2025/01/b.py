import fileinput

p = 50
c = 0
with fileinput.input() as lines:
	for line in lines:
		oldp = p
		s = 1 if line[0] == "R" else -1
		p += s * int(line[1:])
		c += abs(p) // 100 + (1 if p <= 0 and oldp != 0 else 0)
		p %= 100

print(c)
