import fileinput

rang = True
ranges = []
s = 0
with fileinput.input() as lines:
	for line in lines:
		if line == '\n':
			rang = False
		elif rang:
			i = line.find('-')
			ranges.append((int(line[:i]), int(line[i+1:-1])))
		else:
			x = int(line[:-1])
			if any(x >= r[0] and x <= r[1] for r in ranges):
				s += 1
print(s)
