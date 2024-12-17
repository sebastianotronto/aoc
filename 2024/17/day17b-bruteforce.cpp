#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

class CPU {
public:
	CPU(uint64_t a, uint64_t b, uint64_t c) : A{a}, B{b}, C{c} {}

	bool process(const vector<uint64_t>& v) {
		unsigned j = 0;
		for (unsigned ip = 0; ip < v.size() && j <= v.size(); ) {
			switch (v[ip]) {
			case 0:
				A >>= combo(v[ip+1]);
				ip += 2;
				break;
			case 1:
				B ^= v[ip+1];
				ip += 2;
				break;
			case 2:
				B = combo(v[ip+1]) % 8;
				ip += 2;
				break;
			case 3:
				ip = A == 0 ? ip+2 : v[ip+1];
				break;
			case 4:
				B ^= C;
				ip += 2;
				break;
			case 5:
				if (j == v.size() || v[j] != combo(v[ip+1])%8)
					return false;
				j++;
				ip += 2;
				break;
			case 6:
				B = A >> combo(v[ip+1]);
				ip += 2;
				break;
			case 7:
				C = A >> combo(v[ip+1]);
				ip += 2;
				break;
			default:
				cout << "Error! Operator " << v[ip] << endl;
				exit(1);
			}
		}
		return j == v.size();
	}

	void setreg(uint64_t a, uint64_t b, uint64_t c) {
		A = a;
		B = b;
		C = c;
	}
private:
	uint64_t A, B, C;

	uint64_t& reg(uint64_t i) {
		return i == 0 ? A : (i == 1 ? B : C);
	}

	uint64_t combo(uint64_t i) {
		return i <= 3 ? i : reg(i-4);
	}
};

int main() {
	uint64_t a, b, c;
	cin >> a >> b >> c;
	CPU cpu(a, b, c);

	vector<uint64_t> instructions;
	while (cin >> a)
		instructions.push_back(a);

	const uint64_t M = 10000000000;
	const uint64_t N = 100000000000;
	for (a = M; a < N; a++) {
if (a % 1000000 == 0)
cout << "tring " << a << endl;
		cpu.setreg(a, 0, 0);
		if (cpu.process(instructions)) {
			cout << "Found it: " << a << endl;
			return 0;
		}
	}
	cout << "Not found for A < " << N << endl;
	return 0;
}
