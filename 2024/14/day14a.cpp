#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

#define N 101
#define M 103
#define T 100

int quadrant(pair<int64_t, int64_t> p) {
	if (p.first < N/2 && p.second < M/2)
		return 1;
	if (p.first < N/2 && p.second > M/2)
		return 2;
	if (p.first > N/2 && p.second < M/2)
		return 3;
	if (p.first > N/2 && p.second > M/2)
		return 4;
	return 0;
}

int main() {
	string line;
	int64_t p1, p2, v1, v2, q[5] = {0};
	while (cin >> p1 >> p2 >> v1 >> v2) {
		pair<int64_t, int64_t> final((p1 + T*(v1+N)) % N, (p2 + T*(v2+M)) % M);
		q[quadrant(final)]++;
	}

	cout << q[1] * q[2] * q[3] * q[4] << endl;

	return 0;
}
