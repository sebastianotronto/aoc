import fileinput
from math import gcd

inf = 999999999

# Read an input line and return a triple A, b, c where:
#   A is the matrix of coefficient (A[i][j] is 1 if pressing the j-th button
#     increases the i-th counter, 0 otherwise).
#   b is the list of required final values of each counter.
#   c is a list of bounds for the number of times each button can be pressed:
#     c[i] is the minimum required value of a counter increased by button i.
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

# swaprow, swapcol and reducerow are utility functions for the matrix
# row reduction procedure.
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

# Reduce the matrix A by row, including back subsitution. Returns a triple
# A, b, c where:
#   A is the reduced matrix in the form [D|p] with D diagonal and p a matrix
#     whose number of columns is the number of free parameters for Ax = b.
#   b and c are the adjusted versions of the input paramters with the same
#     names. In particular, b is adjusted every time a row is reduced and
#     when rows are swapped, while c (the list of bounds) is adjusted when
#     two columns are swapped (which is equivalent to changing the order of
#     two buttons).
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
	A = [A[i] for i in I]
	b = [b[i] for i in I]

	# Back substitution
	for i in range(len(A)-1, -1, -1):
		for j in range(i):
			reducerow(A, b, i, j)

	return A, b, c

# Find all combinations of parameters respecting the bounds in c. The
# free parameters are always the last n-rank(A) columns of the matrix A
# (where n is the total number of columns).
def paramcomb(nparam, c):
	if nparam == 0:
		return [[]]

	ret = []
	for i in range(c[-nparam]+1):
		ret += [[i, *l] for l in paramcomb(nparam-1, c)]
	return ret

# Solve the integer linear system Ax = b, minimizing the sum of the
# coordinates of x.
def solve_system_min_sum(A, b, c):
	k = len(A[0]) - len(A)
	mins = inf
	for c in paramcomb(k, c):
		sol = sum(c)
		for i in range(len(A)):
			cc = (c[j]*A[i][len(A[0])-k+j] for j in range(len(c)))
			s = b[i]-sum(cc)
			a = s // A[i][i]
			# If a is negative or not integer, we skip this solution
			if a < 0 or s % A[i][i] != 0:
				sol = inf
				break
			sol += a
		mins = min(mins, sol)
	return mins

with fileinput.input() as lines:
	print(sum(solve_system_min_sum(*reduce(*readline(l))) for l in lines))
