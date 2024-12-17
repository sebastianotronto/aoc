/*
This solution is ad-hoc for my input.

Brute force was not working, so I inspected the input. I noticed that
the only jump instruction was at the end, jumping back to 0. So the
program is a 'while (A != 0)' loop.

Disassembling the program I got:

start:
2 4 // B = A % 8
1 5 // B = B ^ 5
7 5 // C = A >> B
1 6 // B = B ^ 6
4 1 // B = B ^ C
5 5 // print B % 8
0 3 // A = A >> 3
3 0 // If A != 0 goto start

Which can be rewritten as

for (A = a; A != 0; A >>= 3) {
	B1 = (A % 8) ^ 5;
	C = A >> B1;
	B2 = (B1 ^ 6) ^ C;
	print(B2 % 8);
}

Where a is the value initially in register A. Here I split B in B1 and
B2 for simplicity.

What we need to do now is work out a sequence of values a_1, a_2, a_3...
such that at step i the program prints p_i (the i-th instruction of
the program itself, i.e. the desired input) and leaves a_{i+1} in the
register. This is easier to do if we reason backwards: at the last step we
want the program to print 0 and leave 0 in register A. From the equations
above we can work out that this happens if at the second-to-last step
the value in the A register is 3.

Writing a_{i-1} = 8a_i + Y and x = B2 % 8 we have

x = (B1 ^ 6) ^ (a_{i-1} >> B1) % 8 =
  = (Y ^ 5 ^ 6) ^ (a_{i-1} >> (Y ^ 5)) % 8 =
  = (Y ^ 3) ^ ((8*a_i+Y) >> (Y ^ 5)) % 8

At each step there are multiple possible values for Y, we have to try
them all.
*/

#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

uint64_t f(uint64_t a, uint64_t Y) {
	// This is what my input program outputs at each iteration
	// if the value in register A is 8*a+Y
	return (Y ^ 3) ^ ((8*a + Y) >> (Y ^ 5));
}

bool tryi(const vector<uint64_t>& p, vector<uint64_t>& A, int i) {
	if (i < 0)
		return true;

	for (uint64_t Y = 0; Y < 8; Y++) {
		if (p[i] == f(A[i+1], Y) % 8) {
			A[i] = (A[i+1] << 3) + Y;
			if (tryi(p, A, i-1))
				return true;
		}
	}

	return false;
}

int main() {
	// Hard-coded input
	vector<uint64_t> p {2, 4, 1, 5, 7, 5, 1, 6, 4, 1, 5, 5, 0, 3, 3, 0};

	uint64_t N {p.size()};
	vector<uint64_t> A(N+1);
	A[N] = 0; // Last value in the register, so the program stops

	tryi(p, A, N-1);

	cout << A[0] << endl;
	return 0;
}
