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
	char c;
	for (int id = 0; cin >> c; id++)
		for (int j = 0; j < c-'0'; j++)
			a.push_back(id % 2 == 0 ? id/2 : -1); // -1 = space

	int j = 0;
	for (auto& x : a | views::reverse) {
		while (a[j] >= 0) j++;
		if (a[j] == -2) break;
		a[j] = x;
		x = -2; // -2 = freed up
	}

	long long checksum = 0;
	for (long long i = 0; i < (long long)a.size() && a[i] != -2; i++)
		checksum += i*a[i];
	cout << checksum << endl;

	return 0;
}
