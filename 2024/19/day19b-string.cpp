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

vector<string> gettowels(const string& line) {
	vector<string> ret;
	int j = 0;
	for (int i = 0; j != -1; i = j+2) {
		j = line.find(",", i);
		ret.push_back(line.substr(i, (j == -1 ? line.size() : j)-i));
	}
	return ret;
}

int64_t countpossible(const string& p, const vector<string>& towels, vector<int64_t>& mem) {
	if (p.size() == 0)
		return 1;
	if (mem[p.size()] != -1)
		return mem[p.size()];
	int64_t ret = 0;
	for (auto t : towels) {
		if (t == p.substr(0, t.size()))
			ret += countpossible(p.substr(
			    t.size(), p.size() - t.size()), towels, mem);
	}
	return (mem[p.size()] = ret);
}

int main() {
	string line;
	getline(cin, line);
	auto towels = gettowels(line);
	getline(cin, line);
	vector<string> patterns;
	while (getline(cin, line))
		patterns.push_back(line);
	vector<int64_t> mem(1000);
	int64_t count = 0;
	for (auto p : patterns) {
		for (auto& m : mem) m = -1;
		count += countpossible(p, towels, mem);
	}
	cout << count << endl;
	return 0;
}
