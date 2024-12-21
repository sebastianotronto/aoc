#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

map<char, pair<int, int>> m_num = {
	{'7', {0,0}}, {'8', {0,1}}, {'9', {0,2}},
	{'4', {1,0}}, {'5', {1,1}}, {'6', {1,2}},
	{'1', {2,0}}, {'2', {2,1}}, {'3', {2,2}},
	{'x', {3,0}}, {'0', {3,1}}, {'A', {3,2}},
};

map<char, pair<int, int>> m_dir = {
	{'x', {0,0}}, {'^', {0,1}}, {'A', {0,2}},
	{'<', {1,0}}, {'v', {1,1}}, {'>', {1,2}},
};

map<pair<int, int>, char> rev_num;
map<pair<int, int>, char> rev_dir;

map<pair<char, char>, vector<string>> p;

vector<pair<pair<int, int>, char>> directions = {
	{{1,0}, 'v'}, {{-1,0}, '^'}, {{0,1}, '>'}, {{0,-1}, '<'}
};

int distance(int cx, int cy, int dx, int dy) {
	return abs(cx-dx) + abs(cy-dy);
}

vector<string> paths(char c, char d,
    map<char, pair<int, int>>& m, map<pair<int, int>, char>& rev) {
	if (p[make_pair(c, d)].size() != 0) return p[make_pair(c, d)];
	if (c == d) return {""};
	if (c == 'x') return {};

	vector<string> v;
	auto [cx, cy] = m[c];
	auto [dx, dy] = m[d];
	for (auto [dir, dirc] : directions) {
		pair i = make_pair(cx+dir.first, cy+dir.second);
		if (distance(cx, cy, dx, dy) < distance(i.first, i.second, dx, dy))
			continue;
		auto next = paths(rev[i], d, m, rev);
		for (auto n : next)
			v.push_back(dirc+n);
	}

	return p[make_pair(c, d)] = v;
}

int64_t pushes(char c, char d, map<char,
    pair<int, int>>& m, map<pair<int, int>, char>& r, int n) {
	auto p = paths(c, d, m, r);
	auto ret = numeric_limits<int64_t>::max();
	for (auto path : p) {
		if (n == 0) {
			ret = min(ret, (int64_t)path.size()+1);
		} else {
			path = 'A' + path + 'A';
			int64_t u = 0;
			for (unsigned i = 0; i < path.size()-1; i++)
				u += pushes(path[i], path[i+1], m_dir, rev_dir, n-1);
			ret = min(ret, u);
		}
	}
	return ret;
}

int64_t numeric(const string& code) {
	return (code[0]-'0')*100 + (code[1]-'0')*10 + (code[2]-'0');
}

int main() {
	for (auto [k, v] : m_num) rev_num[v] = k;
	for (auto [k, v] : m_dir) rev_dir[v] = k;

	string line;
	int64_t tot = 0;
	while (getline(cin, line)) {
		int64_t comp = 0;
		int64_t num = numeric(line);
		line = 'A' + line;
		for (unsigned i = 0; i < line.size()-1; i++)
			comp += pushes(line[i], line[i+1], m_num, rev_num, 2);
		tot += comp * num;
	}
	cout << tot << endl;
	return 0;
}
