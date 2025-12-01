import fileinput

p = 50
c = 0
with fileinput.input() as lines:
	for line in lines:
		s = 1 if line[0] == "R" else -1
		p = (p + s * int(line[1:])) % 100
		if p == 0:
			c += 1

print(c)
