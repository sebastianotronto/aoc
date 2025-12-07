import fileinput

with fileinput.input() as lines:
	rows = [line[:-1] for line in lines]

t = [1 if x == 'S' else 0 for x in rows[0]]
for row in rows[1:]:
	next = [0] * len(row)
	for i in range(len(row)):
		if row[i] == '^':
			next[i-1] += t[i]
			next[i+1] += t[i]
		else:
			next[i] += t[i]
	t = next

print(sum(t))
