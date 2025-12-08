import fileinput

class SetJoin:
	def __init__(self, n):
		self._parent = [i for i in range(n)]

	def rep(self, i):
		if self._parent[i] != i:
			self._parent[i] = self.rep(self._parent[i])
		return self._parent[i]

	def join(self, i, j):
		self._parent[self.rep(i)] = self.rep(j)

with fileinput.input() as lines:
	pts = [tuple(int(x) for x in line[:-1].split(',')) for line in lines]

def dist(p, q):
	return (p[0]-q[0])**2 + (p[1]-q[1])**2 + (p[2]-q[2])**2

r = range(len(pts))
d = sorted([(dist(pts[i], pts[j]), i, j) for i in r for j in r if j > i])

sj = SetJoin(len(pts))
for _, j, k in d:
	if sj.rep(j) != sj.rep(k):
		sj.join(j, k)
		sol = pts[j][0] * pts[k][0]

print(sol)
