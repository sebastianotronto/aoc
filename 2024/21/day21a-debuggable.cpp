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

string pushes_human(char c, char d) {
	auto p = paths(c, d, m_dir, rev_dir);
	auto shortest = numeric_limits<size_t>::max();
	string ret;
	for (auto path : p) {
		if (path.size() + 1 < shortest) {
			ret = path + 'A';
			shortest = path.size() + 1;
		}
	}
	return ret;
}

string pushes_dir1(char c, char d) {
	auto p = paths(c, d, m_dir, rev_dir);
	auto shortest = numeric_limits<size_t>::max();
	string ret;
	for (auto path : p) {
		path = 'A' + path + 'A';
		string pushes = "";
		for (unsigned i = 0; i < path.size()-1; i++)
			pushes += pushes_human(path[i], path[i+1]);
		if (pushes.size() < shortest) {
			ret = pushes;
			shortest = pushes.size();
		}
	}
	return ret;
}

string pushes_numpad(char c, char d) {
	auto p = paths(c, d, m_num, rev_num);
	auto shortest = numeric_limits<size_t>::max();
	string ret;
	for (auto path : p) {
		path = 'A' + path + 'A';
		string pushes = "";
		for (unsigned i = 0; i < path.size()-1; i++)
			pushes += pushes_dir1(path[i], path[i+1]);
		if (pushes.size() < shortest) {
			ret = pushes;
			shortest = pushes.size();
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
		string ppp;
		int64_t num = numeric(line);
		line = 'A' + line;
		for (unsigned i = 0; i < line.size()-1; i++)
			ppp += pushes_numpad(line[i], line[i+1]);
		cout << ppp << endl;
		tot += ppp.size() * num;
	}
	cout << tot << endl;
	return 0;
}
