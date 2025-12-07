import fileinput

with fileinput.input() as lines:
	rows = [line[:-1] for line in lines]
	pos = {rows[0].find('S'): 1}

for row in rows[1:]:
	newpos = {}
	for p, w in pos.items():
		for pp in [p-1,p+1] if row[p] == '^' else [p]:
			t = newpos.get(pp, 0)
			newpos[pp] = t + w
	pos = dict(newpos)

print(sum(pos.values()))
