#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

pair<int, int> antinode(pair<int, int> p, pair<int, int> q) {
	auto [xp, yp] = p;
	auto [xq, yq] = q;
	return make_pair(2*xp-xq, 2*yp-yq);
}

void add_antinodes(set<pair<int, int>>& points,
    pair<int, int> p, set<pair<int, int>>& antinodes) {
	for (auto q : points) {
		antinodes.insert(antinode(p, q));
		antinodes.insert(antinode(q, p));
	}
}

int main() {
	string line;
	map<char, set<pair<int, int>>> d;
	set<pair<int, int>> antinodes;
	int i, j;
	for (i = 0; getline(cin, line); i++) {
		stringstream s(line);
		char c;
		for (j = 0; s >> c; j++) {
			if (c != '.') {
				pair<int, int> p(i, j);
				add_antinodes(d[c], p, antinodes);
				d[c].insert(p);
			}
		}
	}
	
	int tot = 0;
	for (auto [x, y] : antinodes)
		if (x >= 0 && x < i && y >= 0 && y < j)
			tot++;

	cout << tot << endl;
	return 0;
}
