/*
This code is a bit ugly, day12b.cpp contains a nicer implementation
(the perimeter part is of course different).
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

enum class Direction { U, D, R, L };
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
	const char out_of_bound = '$';
	int M, N;

	Board(vector<string> &lines) {
		N = lines.size();
		M = 0;
		for (string l : lines)
			M = max(M, (int)l.size());
		region = new int[M * N];
		cells = new char[M * N];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				region[M*i + j] = -1;
				cells[M*i + j] = j < (int)lines[i].size() ?
				    lines[i][j] : out_of_bound;
			}
		}
				
	}

	~Board() {
		delete []region;
		delete []cells;
	}

	char operator[](pair<int, int> p) {
		int c = coord(p);
		return c == -1 ? out_of_bound : cells[c];
	}

	int& reg(pair<int, int> p) {
		return region[coord(p)];
	}

private:
	char *cells;
	int *region;

	int coord(pair<int, int> p) {
		auto [i, j] = p;
		return i >= N || i < 0 || j >= M || j < 0 ? -1 : M*i + j;
	}
};

void fill(pair<int, int> p, char a, int r, Board &board) {
	if (board[p] != a || board.reg(p) == r)
		return;
	board.reg(p) = r;

	fill(step(p, Direction::U), a, r, board);
	fill(step(p, Direction::D), a, r, board);
	fill(step(p, Direction::R), a, r, board);
	fill(step(p, Direction::L), a, r, board);
}

int cell_perim(Board &board, pair<int, int> p) {
	int perim = 0;
	if (board[step(p, Direction::U)] != board[p]) perim++;
	if (board[step(p, Direction::D)] != board[p]) perim++;
	if (board[step(p, Direction::R)] != board[p]) perim++;
	if (board[step(p, Direction::L)] != board[p]) perim++;
	return perim;
}

int measure_region(Board &board, int r) {
	int area = 0;
	int perim = 0;
	pair<int, int> p;
	for (p.first = 0; p.first < board.N; p.first++) {
		for (p.second = 0; p.second < board.M; p.second++) {
			if (board.reg(p) == r) {
				area++;
				perim += cell_perim(board, p);
			}
		}
	}

	return area * perim;
}

int scan(Board &board, int maxr) {
	int tot = 0;
	for (int r = 0; r < maxr; r++)
		tot += measure_region(board, r);

	return tot;
}

int main() {
	string line;
	vector<string> lines;
	while (getline(cin, line))
		lines.push_back(line);

	Board board(lines);

	pair<int, int> p;
	int r = 0;
	for (p.first = 0; p.first < board.N; p.first++) {
		for (p.second = 0; p.second < board.M; p.second++) {
			if (board.reg(p) == -1) {
				fill(p, board[p], r, board);
				r++;
			}
		}
	}

	auto tot = scan(board, r);

	cout << tot << endl;

	return 0;
}
