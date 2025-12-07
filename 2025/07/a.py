import fileinput

with fileinput.input() as lines:
	rows = [line[:-1] for line in lines]
	pos = [rows[0].find('S')]

s = 0
for row in rows[1:]:
	newpos = set()
	for p in pos:
		if row[p] == '^':
			s += 1
			newpos.add(p-1)
			newpos.add(p+1)
		else:
			newpos.add(p)
	pos = list(newpos)

print(s)
