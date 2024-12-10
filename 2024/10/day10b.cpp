#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

enum Direction { U = 0, D, R, L };
Direction all_directions[] = {
	Direction::U, Direction::D, Direction::R, Direction::L,
};

pair<int, int> step(pair<int, int> p, Direction d) {
	auto [i, j] = p;

	switch (d) {
	case Direction::U:
		return make_pair(i-1, j);
	case Direction::D:
		return make_pair(i+1, j);
	case Direction::R:
		return make_pair(i, j+1);
	case Direction::L:
		return make_pair(i, j-1);
	}

	return make_pair(-999,-999);
}

class Board {
public:
	const int out_of_bound = -1;
	int M, N;

	Board(vector<string> &lines) {
		N = lines.size();
		M = 0;
		for (string l : lines)
			M = max(M, (int)l.size());

		cells = new int[M * N];
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cells[N*i + j] = lines[i][j] - '0';
	}

	~Board() {
		delete []cells;
	}

	int operator[](pair<int, int> p) {
		int c = coord(p);
		return c == -1 ? out_of_bound : cells[c];
	}

private:
	int *cells;

	int coord(pair<int, int> p) {
		auto [i, j] = p;
		return i >= N || i < 0 || j >= M || j < 0 ? -1 : N*i + j;
	}
};

int reachable9(pair<int, int> p, Board& board) {
	if (board[p] == 9)
		return 1;

	int ret = 0;
	auto q = step(p, Direction::U);
	if (board[q] == board[p]+1)
		ret += reachable9(q, board);

	q = step(p, Direction::D);
	if (board[q] == board[p]+1)
		ret += reachable9(q, board);

	q = step(p, Direction::R);
	if (board[q] == board[p]+1)
		ret += reachable9(q, board);

	q = step(p, Direction::L);
	if (board[q] == board[p]+1)
		ret += reachable9(q, board);

	return ret;
}

int main() {
	string line;
	vector<string> lines;
	while (getline(cin, line))
		lines.push_back(line);

	Board board(lines);

	int tot = 0;

	pair i(0, 0);
	for (i.first = 0; i.first < board.N; i.first++) {
		for (i.second = 0; i.second < board.M; i.second++) {
			if (board[i] == 0) {
				tot += reachable9(i, board);
			}
		}
	}

	cout << tot << endl;

	return 0;
}
