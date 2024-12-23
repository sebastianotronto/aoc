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

int index(char a, char b) { return (int)(a-'a') + 26*(int)(b-'a'); }
bool t(int i) { return i % 26 == 't' - 'a'; }

int main() {
	string line;
	while (getline(cin, line)) {
		int i = index(line[0], line[1]);
		int j = index(line[3], line[4]);
		computers.insert(i);
		computers.insert(j);
		m[i][j] = m[j][i] = true;
	}

	vector cv(computers.begin(), computers.end());
	int tot = 0;
	for (unsigned i = 0; i < cv.size(); i++)
		for (unsigned j = i+1; j < cv.size(); j++)
			for (unsigned k = j+1; k < cv.size(); k++)
				tot += m[cv[i]][cv[j]] && m[cv[j]][cv[k]] && m[cv[k]][cv[i]] &&
				       (t(cv[i]) || t(cv[j]) || t(cv[k]));

	cout << tot << endl;
	return 0;
}
