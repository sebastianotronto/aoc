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

bool ispossible(const string& p, const vector<string>& towels, vector<int>& mem) {
	if (p.size() == 0)
		return true;
	if (mem[p.size()] != -1)
		return mem[p.size()];
	for (auto t : towels) {
		if (t == p.substr(0, t.size()))
			if((mem[p.size()] = ispossible(p.substr(
			    t.size(), p.size() - t.size()), towels, mem)))
				return true;
	}
	return (mem[p.size()] = false);
}

int main() {
	string line;
	getline(cin, line);
	auto towels = gettowels(line);
	getline(cin, line);
	vector<string> patterns;
	while (getline(cin, line))
		patterns.push_back(line);
	vector<int> mem(1000);
	int count = 0;
	for (auto p : patterns) {
		for (auto& m : mem) m = -1;
		count += ispossible(p, towels, mem);
	}
	cout << count << endl;
	return 0;
}
