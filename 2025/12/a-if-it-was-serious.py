import fileinput

class Present:
	def __init__(self, lines5):
		self.baseshape = [line[:-1] for line in lines5[1:4]]
		self.area = sum(l.count('#') for l in self.baseshape)

	@staticmethod
	def pretty(s):
		return '\n'.join(s)

	def __str__(self):
		return Present.pretty(self.baseshape)

	@staticmethod
	def singlerot(s):
		return [''.join(s[j][2-i] for j in range(3)) for i in range(3)]

	@staticmethod
	def singleflip(s):
		return [''.join(s[i][2-j] for j in range(3)) for i in range(3)]

	def shape(self, rot, flip):
		s = list(self.baseshape)
		for _ in range(rot):
			s = Present.singlerot(s)
		if flip:
			s = Present.singleflip(s)
		return s

class Region:
	def __init__(self, line):
		wh, n = line[:-1].split(': ')
		self.w, self.h = tuple(int(i) for i in wh.split('x'))
		self.p = [int(i) for i in n.split(' ')]

	def __str__(self):
		return f"({self.w}x{self.h}) {self.p}"

with fileinput.input() as lines:
	lines = list(lines)
	presents = [Present(lines[5*i:5*(i+1)]) for i in range(6)]
	regions = [Region(line) for line in lines[30:]]

# Then you'd have to find some algorithm to solve this, but it is crazy hard
