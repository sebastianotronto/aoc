/*
I ran the simulation at 1FPS for a few minutes, staring at the screen and
hoping to see a Christmas tree, without luck. But I noticed that the robots
formed a strange "vertical" pattern every 103 timesteps, starting at t=30,
and a strange "horizontal" pattern every 101 timesteps, starting at t=81.
So I solved the diophantine equation 30+103y = 81+101x, and the smallest
solution (y=76, x=77) gave the correct answer t=30+103*76=7858
*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unistd.h>
#include <vector>
using namespace std;

#define N 101
#define M 103
#define T 100

char board[N][M];

struct Robot {
	pair<int64_t, int64_t> p, v;
	Robot(int64_t p1, int64_t p2, int64_t v1, int64_t v2) : p(p1, p2), v(v1, v2) {}
};

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

pair<int64_t, int64_t> pos(Robot r, int64_t t) {
	return make_pair((r.p.first + t*(r.v.first+N))%N,
	    (r.p.second + t*(r.v.second+M))%M);
}

void visualize(vector<Robot>& robots, int64_t t) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board[i][j] = ' ';
	for (const auto& r : robots) {
		auto [x,y] = pos(r, t);
		board[x][y] = '*';
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << board[i][j];
		cout << endl;
	}
	cout << endl;
}

int main() {
	string line;
	int64_t p1, p2, v1, v2, q[5] = {0};
	vector<Robot> r;
	while (cin >> p1 >> p2 >> v1 >> v2)
		r.push_back(Robot(p1, p2, v1, v2));


	/* Starts at the solution */
	for (int64_t t = 7858; ; t++) {
		cout << "visualization of time " << t << ": " << endl;
		sleep(1);
		visualize(r, t);
	}

	cout << q[1] * q[2] * q[3] * q[4] << endl;

	return 0;
}
