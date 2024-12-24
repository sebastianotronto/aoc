/*

I don't know what addition circuits look like, but they should have some
kind of regular structure. I manually inspected how the first few digits
behave to get an idea.

With some more manual inspection I noticed that the "temporary result"
gates that are results of a XOR operation always appear as terms in
exactly one XOR and one AND operation; the same thing happens for
OR-results, while AND-results appear as terms only in one OR operation.

This excludes z-gates, which are the result of a XOR operation (except
for z45, which is the result of an OR operation) and do not appear as
terms in any other operation. And of course "errors" do not follow this
pattern either.

So what I do is going through all gates and see if their result
satisfies the conditions above. This gives 8 candidates for the error,
but unfortunately they were not the correct answer (I tried submitting
this list 3 times).

I thought about it a bit longer and I realized that one of the entries
in my list is rfg, which appears as the result of x00 & y00. I thought
that since this was the first digit, it could be an edge case and thus
correctly behaving differently from the others. This leaves me with
7 candidates only, so I have to find another one.

One of the gates I had to swap (z23) was the result of an OR operation,
but should have been the result o a XOR. But any XOR-result could be
swapped with an OR-result without breaking the conditions I guessed at the
beginning. So I tried them all: for every XOR-gate I swapped the results
with my other 7 candidates in every way possible according to my rules,
and checked which of these re-arrangements gave the correct answer for
the example input.

I found two candidates (kdf and nsr). I could have checked more inputs
to see which of the two worked, or I could just try both of them. Of
course, I choose the second option, and kdf worked.

Did I get the gold star? Yes. Do I know how I was supposed to solve this
problem? Not a clue. But hey, I solved it without hints, a win is a win.

*/

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

enum class Op { AND, OR, XOR };

class Gate {
public:
	int x, y, z;
	Op op;

	bool ready(const int8_t *state) const {
		return state[x] != -1 && state[y] != -1;
	}

	bool operate(int8_t *state) const { /* Returns true if the operation flips a bit */
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

int8_t state[36*36*36];
vector<Gate> gates;

int d(char x) { return x >= 'a' && x <= 'z' ? x-'a' : 26+x-'0'; }
char h(int i) { return i >= 26 ? i-26+'0' : i+'a'; }
int index(char a, char b, char c) { return d(c) + 36 * (d(b) + 36 * d(a)); }
string name(int i) {
	string r = "   ";
	r[0] = h(i / (36*36));
	r[1] = h((i/ 36) % 36);
	r[2] = h(i % 36);
	return r;
}

int64_t digit(int i, char c) {
	return index(c, (i/10)+'0', (i%10)+'0');
}

int64_t getnum(char c, int m) {
	int64_t result = 0;
	for (int64_t i = 0, j = 1; i < m; i++, j *= 2)
		result += (int64_t)state[digit(i, c)] * j;
	return result;
}

Op make_op(char c) {
	switch (c) {
	case '&': return Op::AND;
	case '|': return Op::OR;
	default: return Op::XOR;
	}
}

char opname(Op op) {
	switch (op) {
	case Op::AND: return '&';
	case Op::OR: return '|';
	default: return '^';
	}
}

void printop(Gate g, const vector<Op>& a) {
	cout << name(g.z) << " is " << name(g.x) << " " << opname(g.op)
	     << " " << name(g.y) << " but appears in ";
	for (auto op : a)
		cout << opname(op) << " ";
	cout << endl;
}

int gg(const string& rr) {
	for (unsigned i = 0; i < gates.size(); i++)
		if (name(gates[i].z) == rr)
			return i;
	return -1;
}

void swapgates(vector<Gate>& local_gates, vector<int> ixsa,
    vector<int> iasx, int iosx, int gswap) {
}

void run(int8_t *state, const vector<Gate>& gates) {
	for (bool flag = true; flag; ) { 
		flag = false;
		for (auto g : gates)
			if (g.ready(state))
				flag = flag || g.operate(state);
	}
	int64_t x = getnum('x', 45);
	int64_t y = getnum('y', 45);
	int64_t z = getnum('z', 46);
	if (x+y == z) cout << "Correct result! " << z << endl;
}

int main() {
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

#if 0
	/* Print error candidates */
	vector<string> bad;
	for (auto g : gates) {
		if (name(g.z)[0] == 'z') {
			if ((name(g.z) == "z45" && g.op != Op::OR) ||
			    (name(g.z) != "z45" && g.op != Op::XOR)) {
				printop(g, vector<Op>());
				bad.push_back(name(g.z));
			}
			continue;
		}
		vector<Op> appears_in;
		for (auto f : gates)
			if (g.z == f.x || g.z == f.y)
				appears_in.push_back(f.op);
		if (g.op == Op::AND) {
			if (appears_in.size() != 1 || appears_in[0] != Op::OR) {
				printop(g, appears_in);
				bad.push_back(name(g.z));
			}
		} else {
			if (appears_in.size() != 2 ||
			    find(appears_in.begin(), appears_in.end(), Op::AND) == appears_in.end() ||
			    find(appears_in.begin(), appears_in.end(), Op::XOR) == appears_in.end()) {
				printop(g, appears_in);
				bad.push_back(name(g.z));
			}
		}
	}

	sort(bad.begin(), bad.end());

	for (auto b : bad)
		cout << b << ",";
	cout << endl;
#endif

	vector<string> is_xor_shouldbe_and = { "ckj", "rpp", "dbp" };
	vector<string> is_and_shouldbe_xor = { "fdv", "z15", "z39" };
	string is_or_shouldbe_xor = "z23";

	vector<int> ixsa = { gg("ckj"), gg("rpp"), gg("dbp") };
	vector<int> iasx = { gg("fdv"), gg("z15"), gg("z39") };
	int iosx = gg("z23");

	vector<vector<pair<int, int>>> swaps = {
		{{ixsa[0],iasx[0]}, {ixsa[1],iasx[1]}, {ixsa[2],iasx[2]}},
		{{ixsa[0],iasx[0]}, {ixsa[1],iasx[2]}, {ixsa[2],iasx[1]}},
		{{ixsa[0],iasx[1]}, {ixsa[1],iasx[0]}, {ixsa[2],iasx[2]}},
		{{ixsa[0],iasx[1]}, {ixsa[1],iasx[2]}, {ixsa[2],iasx[0]}},
		{{ixsa[0],iasx[2]}, {ixsa[1],iasx[1]}, {ixsa[2],iasx[0]}},
		{{ixsa[0],iasx[2]}, {ixsa[1],iasx[0]}, {ixsa[2],iasx[1]}}
	};

	for (unsigned gswap = 0; gswap < gates.size(); gswap++) {
		if (find(ixsa.begin(), ixsa.end(), gswap) != ixsa.end() ||
		    find(iasx.begin(), iasx.end(), gswap) != iasx.end() ||
		    (int)gswap == iosx || gates[gswap].op != Op::XOR)
			continue;
		cout << "Trying gswap " << name(gates[gswap].z) << endl;
		for (auto ss : swaps) {
			auto local_state = state;
			auto local_gates = gates;
			swap(local_gates[ss[0].first].z, local_gates[ss[0].second].z);
			swap(local_gates[ss[1].first].z, local_gates[ss[1].second].z);
			swap(local_gates[ss[2].first].z, local_gates[ss[2].second].z);
			swap(local_gates[iosx].z, local_gates[gswap].z);
			run(local_state, local_gates);
		}
	}

	return 0;
}
