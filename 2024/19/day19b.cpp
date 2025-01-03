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

vector<string_view> gettowels(const string_view& line) {
	vector<string_view> ret;
	unsigned sz = line.size();
	for (int i = 0, j = 0; j != -1; i = j+2) {
		j = line.find(",", i);
		ret.push_back(line.substr(i, (j == -1 ? sz : j) - i));
	}
	return ret;
}

int64_t f(const string_view& p, const vector<string_view>& towels, vector<int64_t>& mem) {
	unsigned lp = p.size();
	if (lp == 0) return 1;
	if (mem[lp] != -1) return mem[lp];
	int64_t ret = 0;
	for (auto t : towels) {
		unsigned lt = t.size();
		if (t == p.substr(0, lt))
			ret += f(p.substr(lt, lp - lt), towels, mem);
	}
	return (mem[lp] = ret);
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
		count += f(p, towels, mem);
	}
	cout << count << endl;
	return 0;
}
