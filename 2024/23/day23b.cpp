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

set<int> computers;
bool m[26*26][26*26];

int index(char a, char b) { return (int)(b-'a') + 26*(int)(a-'a'); }
void printnode(int i) { cout << (char)('a'+i/26) << (char)('a'+i%26); }
bool t(int i) { return i % 26 == 't' - 'a'; }

bool all(int i, const set<int>& v) {
	for (auto j : v)
		if (!m[i][j])
			return false;
	return true;
}

int main() {
	string line;
	while (getline(cin, line)) {
		int i = index(line[0], line[1]);
		int j = index(line[3], line[4]);
		computers.insert(i);
		computers.insert(j);
		m[i][j] = m[j][i] = true;
	}

	vector<set<int>> cliques[15];
	cliques[0].push_back(set<int>());
	for (int i = 1; ; i++) {
		for (auto& c : cliques[i-1]) {
			int mm = *max_element(c.begin(), c.end());
			for (auto j : computers) {
				if (j <= mm) continue;
				if (all(j, c)) {
					set nw = c;
					nw.insert(j);
					cliques[i].push_back(nw);
				}
			}
		}
		auto n = cliques[i].size();
		cout << "Found " << n << " cliques of size " << i << endl;
		if (n == 0) break;
		auto cc = *cliques[i].begin();
		vector<int> cv(cc.begin(), cc.end());
		sort(cv.begin(), cv.end());
		for (auto j : cv) {
			printnode(j);
			cout << ",";
		}
		cout << endl;
	}

	return 0;
}
