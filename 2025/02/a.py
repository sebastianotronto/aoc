import fileinput

def invalid(n):
	return n[:len(n)//2] == n[len(n)//2:]

s = 0
with fileinput.input() as lines:
	for line in lines:
		for r in line.split(","):
			l = r.split("-");
			for n in range(int(l[0]), int(l[1])+1):
				if invalid(str(n)):
					print(n)
					s += n
print(s)
