import fileinput
from math import gcd

inf = 999999999

def readline(l):
	b = [int(x) for x in l[l.index('{')+1:l.index('}')].split(',')]

	A = [[] for j in b]
	c = []

	end = l.index(']')
	while '(' in l[end:]:
		begin = l[end:].index('(') + end + 1
		end = l[begin:].index(')') + begin
		bu = [int(x) for x in l[begin:end].split(',')]
		c.append(min(b[j] for j in bu))
		for i in range(len(b)):
			A[i].append(1 if i in bu else 0)

	return A, b, c

def printabc(A, b, c):
	print("--")
	for i in range(len(b)):
		print(A[i], [b[i]])
	print(f"Parameter bounds: {c}")
	print("--")

def swaprow(A, b, i, j):
	if i != j:
		A[i], A[j] = A[j], A[i]
		b[i], b[j] = b[j], b[i]

def swapcol(A, c, i, j):
	if i != j:
		for k in range(len(A)):
			A[k][i], A[k][j] = A[k][j], A[k][i]
		c[i], c[j] = c[j], c[i]

def reducerow(A, b, i, j):
	if A[i][i] != 0:
		x = A[i][i]
		y = -A[j][i]
		d = gcd(x, y)
		A[j] = [(y*A[i][k]+x*A[j][k])//d for k in range(len(A[i]))]
		b[j] = (y*b[i]+x*b[j])//d

def reduce(A, b, c):
	for i in range(len(A[0])):
		# Swap columns until there is one in position i with at least
		# one non-zero element.
		I = []
		k = i
		while len(I) == 0 and k < len(A[0]):
			swapcol(A, c, i, k)
			I = [j for j in range(i, len(A)) if A[j][i] != 0]
			k += 1

		# If no such column is found, we are done
		if len(I) == 0:
			break

		# Swap rows so that A[i][i] is non-zero
		swaprow(A, b, i, I[0])

		# Reduce all other rows
		for j in range(i+1, len(A)):
			reducerow(A, b, i, j)

	# Remove all rows of zero and check if the system is solvable
	I = [i for i in range(len(A)) if any(a != 0 for a in A[i])]
	if any(b[i] != 0 for i in range(len(A)) if i not in I):
		printabc(A, b, c)
		print("Unsolvable!")
		exit(1)
	A = [A[i] for i in I]
	b = [b[i] for i in I]

	# TODO continue with back substitution?
	for i in range(len(A)-1, -1, -1):
		for j in range(i):
			reducerow(A, b, i, j)

	# Clean all rows to minimize coefficients (unnecessary, but makes
	# numbers smaller).
	for i in range(len(A)):
		d = gcd(*A[i]) * (-1 if A[i][i] < 0 else 1)
		A[i] = [A[i][k]//d for k in range(len(A[i]))]
		b[i] = b[i]//d

	return A, b, c

def paramcomb(nparam, c):
	if nparam == 0:
		return [[]]

	ret = []
	for i in range(c[-nparam]+1):
		ret += [[i, *l] for l in paramcomb(nparam-1, c)]
	return ret

def solve_system_min_sum(A, b, c):
	#nparam = len(A[0])-len(A)
	#print(f"{nparam}: {paramcomb(nparam, c)}")

	k = len(A[0]) - len(A)
	mins = inf
	for c in paramcomb(k, c):
		sol = sum(c)
		for i in range(len(A)):
			p = sum(c[j]*A[i][len(A[0])-k+j] for j in range(len(c)))
			a = (b[i] - p)//A[i][i]
			if a < 0 or a*A[i][i] != b[i] - p:
				sol = inf
				break
			sol += a
		mins = min(mins, sol)
	return mins

with fileinput.input() as lines:
	sols = []
	k = 1
	for line in lines:
		print(f"doing line {k}: {line[:-1]}")
		A, b, c = readline(line)
		#printabc(A, b, c)
		A, b, c = reduce(A, b, c)
		#printabc(A, b, c)
		sols.append(solve_system_min_sum(A, b, c))
		k += 1
	print(sols)
	print(sum(sols))
