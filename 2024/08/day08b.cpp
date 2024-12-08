#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

#define N 50
#define M 50

bool in_range(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M;
}

vector<pair<int, int>> antinode_all(pair<int, int> p, pair<int, int> q) {
	auto [xp, yp] = p;
	auto [xq, yq] = q;
	/* In theory these two coefficients must be divided by the gcd of
	 * of the coordinates, which leads to possibly more points,
	 * as far as I understood the problem statement. Apparently, this
	 * is not the case. */
	int gx = (xp - xq);
	int gy = (yp - yq);
	vector<pair<int, int>> v;
	for (int i = 0; in_range(xp+i*gx, yp+i*gy); i++)
		v.push_back(make_pair(xp+i*gx, yp+i*gy));
	for (int i = 0; in_range(xq-i*gx, yq-i*gy); i++)
		v.push_back(make_pair(xq-i*gx, yq-i*gy));
	return v;
}

void add_antinodes(set<pair<int, int>>& points,
    pair<int, int> p, set<pair<int, int>>& antinodes) {
	for (auto q : points) {
		auto a = antinode_all(p, q);
		for (auto r : a)
			antinodes.insert(r);
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
		if (in_range(x, y))
			tot++;

	cout << tot << endl;
	return 0;
}
