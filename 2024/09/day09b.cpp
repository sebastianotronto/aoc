#include <algorithm>
#include <iostream>
#include <map>
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

	for (int i = file.size()-1; i >= 0; i--) {
		for (auto& f : freesp) {
			if (f.first >= file[i].first) break;
			if (f.second >= file[i].second) {
				for (int k = 0; k < file[i].second; k++) {
					a[f.first+k] = a[file[i].first+k];
					a[file[i].first+k] = -2;
				}
				f.first += file[i].second;
				f.second -= file[i].second;
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
