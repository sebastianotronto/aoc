# Just estimate if the shape fit basd on the area. I feel like I am
# being pranked, this problem sucks.

import fileinput

def present_area(lines5):
	return sum(l.count('#') for l in lines5)

def region(line):
	wh, n = line[:-1].split(': ')
	wh = tuple(int(i) for i in wh.split('x'))
	c = [int(i) for i in n.split(' ')]
	return wh, c

def fits(wh, c, areas):
	return wh[0]*wh[1] >= sum(c[i] * areas[i] for i in range(6))

with fileinput.input() as lines:
	lines = list(lines)
	areas = [present_area(lines[5*i:5*(i+1)]) for i in range(6)]
	regions = [region(line) for line in lines[30:]]

print(sum(1 if fits(*region, areas) else 0 for region in regions))
