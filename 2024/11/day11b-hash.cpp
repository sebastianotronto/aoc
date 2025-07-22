#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const std::pair<T1, T2>& p) const {
		return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
	}
};

unordered_map<pair<uint64_t, uint64_t>, uint64_t, hash_pair> t;

pair<uint64_t, uint64_t> split(uint64_t a) {
	int digits = 0;
	for (uint64_t b = a; b != 0; b /= 10)
		digits++;

	if (digits % 2 == 1)
		return make_pair(0, 0);

	uint64_t j = 1;
	for (int k = 0; k < digits/2; k++)
		j *= 10;

	return make_pair(a/j, a%j);
}

uint64_t count(uint64_t a, int n) {
	if (n == 0)
		return 1;

	if (auto it = t.find(make_pair(a, n)); it != t.end())
		return it->second;

	if (a == 0)
		return t[make_pair(a, n)] = count(1, n-1);

	if (auto [x, y] = split(a); x != 0) {
		auto c1 = count(x, n-1);
		auto c2 = count(y, n-1);
		return t[make_pair(a, n)] = c1+c2;
	}

	return t[make_pair(a, n)] = count(a*2024, n-1);
}

int main() {
	uint64_t x;
	vector<uint64_t> old, v;
	while (cin >> x)
		v.push_back(x);

	uint64_t tot = 0;
	for (auto a : v)
		tot += count(a, 75);

	cout << tot << endl;

	return 0;
}
