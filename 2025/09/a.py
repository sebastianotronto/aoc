import fileinput

with fileinput.input() as lines:
	a = [tuple(int(x) for x in l[:-1].split(',')) for l in lines]

s = 0
for i in range(len(a)):
	for j in range(i+1, len(a)):
		s = max(s, (abs(a[i][0]-a[j][0])+1) * (abs(a[i][1]-a[j][1])+1))

print(s)
