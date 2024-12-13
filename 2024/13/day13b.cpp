#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

#define N 10000000000000
#define INF 999999

class Machine {
public:
	pair<int64_t, int64_t> a, b, p;

	Machine(int64_t a1, int64_t a2,
	    int64_t b1, int64_t b2, int64_t p1, int64_t p2) :
	a(a1, a2), b(b1, b2), p(p1, p2) {}
};

int64_t det(int64_t a, int64_t b, int64_t c, int64_t d) {
	return a*d - b*c;
}

pair<int64_t, int64_t> solve_system(const Machine m) {
	auto d = det(m.a.first, m.b.first, m.a.second, m.b.second);
	auto dx = det(m.p.first, m.b.first, m.p.second, m.b.second);
	auto dy = det(m.a.first, m.p.first, m.a.second, m.p.second);
	return make_pair(dx/d, dy/d);
}

int main() {
	string line;
	int64_t a1, a2, b1, b2, p1, p2;
	vector <Machine> machines;
	while (cin >> a1 >> a2) {
		cin >> b1 >> b2;
		cin >> p1 >> p2;
		getline(cin, line);
		machines.push_back(Machine(a1, a2, b1, b2, p1+N, p2+N));
	}

	int64_t tot = 0;
	for (auto m : machines) {
		auto [x, y] = solve_system(m);
		if (m.a.first * x + m.b.first * y == m.p.first &&
		    m.a.second * x + m.b.second * y == m.p.second)
			tot += 3*x + y;
	}

	cout << tot << endl;

	return 0;
}
