import fileinput

with fileinput.input() as lines:
	pts = [tuple(int(x) for x in line[:-1].split(',')) for line in lines]

r = range(len(pts))

def dist(p, q):
	return (p[0]-q[0])**2 + (p[1]-q[1])**2 + (p[2]-q[2])**2

d = sorted([(dist(pts[i], pts[j]), i, j) for i in r for j in r if j > i])

rep = [i for i in r]

def findrep(i):
	return i if rep[i] == i else findrep(rep[i])

def joinrep(i, j):
	rep[findrep(i)] = findrep(j)

for _, j, k in d:
	if findrep(j) != findrep(k):
		joinrep(j, k)
		sol = pts[j][0] * pts[k][0]

print(sol)
