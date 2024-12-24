/* Use clean.sh on the input first */

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

int8_t state[36*36*36];

int d(char x) { return x >= 'a' && x <= 'z' ? x-'a' : 26+x-'0'; }
int index(char a, char b, char c) { return d(c) + 36 * (d(b) + 36 * d(a)); }
int z(int i) { return index('z', (i/10)+'0', (i%10)+'0'); }

enum class Op { AND, OR, XOR };

class Gate {
public:
	int x, y, z;
	Op op;

	bool ready() const {
		return state[x] != -1 && state[y] != -1;
	}

	bool operate() const { /* Returns true if the operation flips a bit */
		auto oldstate = state[z];
		switch (op) {
		case Op::AND:
			state[z] = state[x] & state[y];
			break;
		case Op::OR:
			state[z] = state[x] | state[y];
			break;
		case Op::XOR:
			state[z] = state[x] ^ state[y];
			break;
		}
		return oldstate != state[z];
	}
};

Op make_op(char c) {
	switch (c) {
	case '&': return Op::AND;
	case '|': return Op::OR;
	default: return Op::XOR;
	}
}

int main() {
	vector<Gate> gates;
	fill(state, state + 36*36*36, -1);
	string line;

	while (getline(cin, line) && line != "")
		state[index(line[0], line[1], line[2])] = line[5]-'0';

	while (getline(cin, line))
		gates.push_back(Gate {
			.x = index(line[0], line[1], line[2]),
			.y = index(line[6], line[7], line[8]),
			.z = index(line[13], line[14], line[15]),
			.op = make_op(line[4])
		});

	for (bool flag = true; flag; ) {
		flag = false;
		for (auto g : gates)
			if (g.ready())
				flag = flag || g.operate();
	}

	int64_t result = 0;
	for (int64_t i = 0, j = 1; state[z(i)] != -1; i++, j *= 2)
		result += (int64_t)state[z(i)] * j;

	cout << result << endl;

	return 0;
}
