import fileinput

with fileinput.input() as lines:
	a = [tuple(int(x) for x in l[:-1].split(',')) for l in lines]

# Check if the border is turning clockwise or counter-clockwise
def dir(p, q):
	return p[0]*q[1]-p[1]*q[0]
t = 0
for i in range(len(a)):
	p, q, r = a[i%len(a)], a[(i+1)%len(a)], a[(i+2)%len(a)]
	t += 1 if dir((q[0]-p[0],q[1]-p[1]), (r[0]-q[0],r[1]-q[1])) > 0 else -1

def lbreaks(p, q, tl, br):
	# Adjust for horizontal or vertical
	(tt, z) = (t, 0) if p[0] == q[0] else (-t, 1)

	if min(p[1-z], q[1-z]) >= br[1-z] or max(p[1-z], q[1-z]) <= tl[1-z]:
		return False
	if p[z] == tl[z]:
		return tt * (q[1-z]-p[1-z]) > 0
	if p[z] == br[z]:
		return tt * (q[1-z]-p[1-z]) < 0

	return p[z] > tl[z] and p[z] < br[z]

def admissible(a, i, j):
	tl = (min(a[i][0], a[j][0]), min(a[i][1], a[j][1]))
	br = (max(a[i][0], a[j][0]), max(a[i][1], a[j][1]))
	return not any(lbreaks(a[k], a[(k+1)%len(a)], tl, br) for k in range(len(a)))

s = 0
for i in range(len(a)):
	for j in range(i+1, len(a)):
		if admissible(a, i, j):
			s = max(s, (abs(a[i][0]-a[j][0])+1)*(abs(a[i][1]-a[j][1])+1))
print(s)
