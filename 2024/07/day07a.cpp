#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

bool possible(long long x, vector<long long>& a, int i) {
	if (i == 0)
		return a[0] == x;
	if (a[i] != 0 && x % a[i] == 0)
		return possible(x/a[i], a, i-1) || possible(x-a[i], a, i-1);
	return possible(x-a[i], a, i-1);
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
