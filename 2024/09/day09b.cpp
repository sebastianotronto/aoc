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

int main() {
	vector<long long> a;
	vector<pair<int, int>> freesp, file;
	char c;
	for (int id = 0; cin >> c; id++) {
		if (id % 2 == 1)
			freesp.push_back(make_pair(a.size(), c-'0'));
		else
			file.push_back(make_pair(a.size(), c-'0'));
		for (int j = 0; j < c-'0'; j++)
			a.push_back(id % 2 == 0 ? id/2 : -1); // -1 = space
	}

	for (auto& p : file | views::reverse) {
		for (auto& f : freesp) {
			if (f.first >= p.first) break;
			if (f.second >= p.second) {
				for (int k = 0; k < p.second; k++) {
					a[f.first+k] = a[p.first+k];
					a[p.first+k] = -2;
				}
				f.first += p.second;
				f.second -= p.second;
				break;
			}
		}
	}

	long long checksum = 0;
	for (long long i = 0; i < (long long)a.size(); i++)
		if (a[i] >= 0)
			checksum += i*a[i];
	cout << checksum << endl;

	return 0;
}
