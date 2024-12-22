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

class Seq {
public:
	int64_t k;

	Seq() : k{0} {}

	Seq(int kk) : k{kk} {}
	
	Seq(int64_t a, int64_t b, int64_t c, int64_t d)
	    : k{(a+9)+19*((b+9)+19*((c+9)+19*(d+9)))} {}

	Seq(const vector<pair<int, int>>& v, int i)
	    : Seq(v[i-3].second, v[i-2].second, v[i-1].second, v[i].second) {}

	int64_t operator[](int64_t i) const {
		int64_t d;
		for (d = k; i > 0; i--)
			d /= 19;
		return (d % 19) - 9;
	}

	bool step() {
		return (++k) < 19*19*19*19;
	}
};

int64_t next(int64_t n) {
	constexpr int64_t M = 16777216;
	n = ((n*64) ^ n) % M;
	n = ((n/32) ^ n) % M;
	n = ((n*2048) ^ n) % M;
	return n;
}

int main() {
	int64_t s;
	vector<vector<pair<int, int>>> spc;
	vector<map<int64_t, int64_t>> tt;
	set<int64_t> seqs;

	for (int i = 0; cin >> s; i++) {
		spc.push_back(vector<pair<int, int>>());
		tt.push_back(map<int64_t, int64_t>());

		for (int j = 0; j < 2000; j++) {
			int64_t t = next(s);
			spc[i].push_back({t%10, t%10 - s%10});
			s = t;
			if (j >= 3) {
				auto k = Seq(spc[i], j).k;
				seqs.insert(k);
				if (tt[i].count(k) == 0)
					tt[i][k] = spc[i][j].first;
			}
		}
	}

	Seq seq;
	int64_t best = 0;
	for (auto k : seqs) {
		Seq seq(k);
		int64_t tot = 0;
		for (unsigned i = 0; i < spc.size(); i++)
			tot += tt[i][seq.k];
		best = max(best, tot);
	};

	cout << best << endl;

	return 0;
}
