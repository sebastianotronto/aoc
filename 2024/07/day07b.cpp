#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

long long uncat(long long x, long long y) {
	if (y == 0)
		return x % 10 == 0 ? x / 10 : -1;
	while (y > 0) {
		if (x % 10 != y % 10)
			return -1;
		x /= 10;
		y /= 10;
	}
	return x;
}

bool possible(long long x, vector<long long>& a, int i) {
	if (i == 0)
		return a[0] == x;

	bool p = possible(x-a[i], a, i-1);
	if (a[i] != 0 && x % a[i] == 0)
		p = p || possible(x/a[i], a, i-1);
	auto u = uncat(x, a[i]);
	if (u != -1)
		p = p || possible(u, a, i-1);
	return p;
}

int main() {
	string line;
	long long tot = 0;
	while (getline(cin, line)) {
		long long x, i;
		vector<long long> a;
		stringstream s(line);
		s >> x;
		char colon;
		s >> colon;
		while (s >> i)
			a.push_back(i);
		if (possible(x, a, a.size()-1))
			tot += x;
	}
	cout << tot << endl;
	return 0;
}
