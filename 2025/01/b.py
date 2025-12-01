import fileinput

p = 50
c = 0
with fileinput.input() as lines:
	for line in lines:
		oldp = p
		s = 1 if line[0] == "R" else -1
		p += s * int(line[1:])
		if p >= 100:
			d = p // 100
			c += d
			p -= d * 100
		elif p <= 0:
			d = -p // 100 + 1
			c += d if oldp != 0 else d-1
			p = (p + d * 100) % 100

print(c)
