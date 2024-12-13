/*
This is the dumb solution I wrote before actually thinking how to solve
the problem. Check out day13b.cpp for a better solution (just remove the
+N in the input-reading part).

Also, both this file and day13b.cpp take a different input format than
what was given. I used clean.sh to convert from 'input-original' to 'input'.
*/

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

#define INF 999999

class Machine {
public:
	pair<int, int> a, b, prize;

	Machine(int a1, int a2, int b1, int b2, int p1, int p2) :
	a(a1, a2), b(b1, b2), prize(p1, p2) {}
};

int main() {
	string line;
	int a1, a2, b1, b2, p1, p2;
	vector <Machine> machines;
	while (cin >> a1 >> a2) {
		cin >> b1 >> b2;
		cin >> p1 >> p2;
		getline(cin, line);
		machines.push_back(Machine(a1, a2, b1, b2, p1, p2));
	}

	int tot = 0;
	for (auto m : machines) {
		int minp = INF;
		for (int i = 0; i <= 100; i++) {
			int x = m.prize.first-m.a.first*i;
			int y = m.prize.second-m.a.second*i;
			if (x % m.b.first != 0 || y % m.b.second != 0)
				continue;
			int a = x / m.b.first;
			int b = y / m.b.second;
			if (a != b)
				continue;
			minp = min(minp, 3*i+a);
		}
		tot += minp == INF ? 0 : minp;
	}

	cout << tot << endl;

	return 0;
}
