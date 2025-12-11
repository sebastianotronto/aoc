import fileinput

a = {}
with fileinput.input() as lines:
	for line in lines:
		v, l2 = line[:-1].split(': ')
		a[v] = l2.split(' ')

def np(v):
	return 1 if v == 'out' else sum(np(w) for w in a[v])

print(np('you'))
