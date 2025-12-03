import fileinput

s = 0
with fileinput.input() as lines:
	for line in lines:
		m1 = 0
		m2 = 0
		mi = -1
		for i in range(len(line)-2):
			if int(line[i]) > m1:
				m1 = int(line[i])
				mi = i
		for i in range(mi+1, len(line)-1):
			if int(line[i]) > m2:
				m2 = int(line[i])
		print(10*m1+m2)
		s += 10*m1+m2
print(s)
