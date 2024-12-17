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

	void process(const vector<uint64_t>& v) {
		for (unsigned ip = 0; ip < v.size(); ) {
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
				cout << combo(v[ip+1])%8 << ",";
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
		cout << endl;
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

	cpu.process(instructions);
	return 0;
}
