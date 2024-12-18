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

#define N 71
#define S 1024

bool b[N][N];

class Qelem {
public:
	int d, x, y;
	Qelem(int dis, int xx, int yy) : d{dis}, x{xx}, y{yy} {}
	bool operator<(const Qelem& other) const { return d > other.d; }
};


int coord(int x, int y) {
	return N*x+y;
}

bool inrange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}

int shortest_path(bool b[N][N]) {
	vector<bool> vis(N*N);

	priority_queue<Qelem> q;
	q.push(Qelem(0, 0, 0));

	while (!q.empty()) {
		auto v = q.top();
		q.pop();
		if (!inrange(v.x, v.y) || b[v.x][v.y] || vis[coord(v.x, v.y)])
			continue;
		if (v.x == N-1 && v.y == N-1) return v.d;
		vis[coord(v.x, v.y)] = true;
		q.push(Qelem(v.d+1, v.x+1, v.y));
		q.push(Qelem(v.d+1, v.x-1, v.y));
		q.push(Qelem(v.d+1, v.x, v.y+1));
		q.push(Qelem(v.d+1, v.x, v.y-1));
	}
	return -1;
}

int main() {
	int x, y;
	for (int i = 0; i < S && (cin >> x >> y); i++)
		b[x][y] = true;

	cout << shortest_path(b) << endl;
	return 0;
}
