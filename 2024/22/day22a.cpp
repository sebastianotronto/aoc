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

int64_t next(int64_t n) {
	constexpr int64_t M = 16777216;
	n = ((n*64) ^ n) % M;
	n = ((n/32) ^ n) % M;
	n = ((n*2048) ^ n) % M;
	return n;
}

int main() {
	int64_t s;
	int64_t tot = 0;
	while (cin >> s) {
		for (int i = 0; i < 2000; i++)
			s = next(s);
		tot += s;
	}
	cout << tot << endl;
	return 0;
}
