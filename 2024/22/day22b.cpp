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

int64_t Seq(int64_t a, int64_t b, int64_t c, int64_t d) {
    return (a+9) + 19*((b+9) + 19*((c+9) + 19*(d+9)));
}

int64_t next(int64_t n) {
	constexpr int64_t M = 16777216;
	n = ((n*64) ^ n) % M;
	n = ((n/32) ^ n) % M;
	n = ((n*2048) ^ n) % M;
	return n;
}

int main() {
	int64_t s;
	map<int64_t, int64_t> sums;

	for (int i = 0; cin >> s; i++) {
		int64_t a, b, c, d;
		set<int64_t> tt;

		for (int j = 0; j < 2000; j++) {
			a = b;
			b = c;
			c = d;
			d = -(s%10);
			s = next(s);
			d += s%10;
			if (j >= 3) {
				auto k = Seq(a, b, c, d);
				if (!tt.contains(k)) {
					tt.insert(k);
					sums[k] += s%10;
				}
			}
		}
	}

	auto values = views::values(sums);
	auto best = *max_element(values.begin(), values.end());
	cout << best << endl;

	return 0;
}
