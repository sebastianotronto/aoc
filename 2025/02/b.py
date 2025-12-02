import fileinput

def invk(n, k):
	for i in range(0, len(n)-k, k):
		if n[i:i+k] != n[i+k:i+2*k]:
			return False
	return True

def invalid(n):
	for k in range(1, len(n)//2 + 1):
		if invk(n, k):
			return True
	return False

s = 0
with fileinput.input() as lines:
	for line in lines:
		for r in line.split(","):
			l = r.split("-");
			for n in range(int(l[0]), int(l[1])+1):
				if invalid(str(n)):
					s += n
print(s)
				

