import fileinput

def neigh(a, i, j):
	return [
		a[i-1][j-1], a[i-1][j], a[i-1][j+1],
		a[i][j-1],              a[i][j+1],
		a[i+1][j-1], a[i+1][j], a[i+1][j+1],
	].count('@')

with fileinput.input() as lines:
	a = [
		['.'] * 200,
		*[['.'] + list(line.replace('\n', '.')) for line in lines],
		['.'] * 200,
	]

s = 0
rem = True
while rem:
	rem = False
	for i in range(1,len(a)-1):
		for j in range(1,len(a[1])-1):
			if a[i][j] == '@' and neigh(a, i, j) < 4:
				s += 1
				rem = True
				a[i][j] = '.'
print(s)
