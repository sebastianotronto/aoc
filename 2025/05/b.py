import fileinput

def overlap(r1, r2):
	return min(r1[1], r2[1]) >= max(r1[0], r2[0])

def fuse(r1, r2):
	return (min(r1[0], r2[0]), max(r1[1], r2[1]))

ranges = []
with fileinput.input() as lines:
	for line in lines:
		if line == '\n':
			break
		i = line.find('-')
		ranges.append((int(line[:i]), int(line[i+1:-1])))

s = set()
for r in ranges:
	c = r
	for rr in list(s):
		if overlap(c, rr):
			c = fuse(c, rr)
			s.remove(rr)
	s.add(c)

print(sum(r[1] - r[0] + 1 for r in s))
