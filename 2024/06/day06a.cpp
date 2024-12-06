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

Direction turn(Direction d) {
	switch (d) {
	case Direction::U:
		return Direction::R;
	case Direction::D:
		return Direction::L;
	case Direction::R:
		return Direction::D;
	case Direction::L:
		return Direction::U;
	}

	return Direction::U;
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
		cells = new char[M * N];
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cells[N*i + j] = j < (int)lines[i].size() ?
				    lines[i][j] : out_of_bound;
	}

	~Board() {
		delete []cells;
	}

	char operator[](pair<int, int> p) {
		int c = coord(p);
		return c == -1 ? out_of_bound : cells[c];
	}

	bool is_obstruction(pair<int, int> p) {
		return (*this)[p] == '#';
	}

	bool is_visited(pair<int, int> p) {
		return (*this)[p] == 'x';
	}

	void set_visited(pair<int, int> p) {
		int c = coord(p);
		cells[c] = 'x';
	}

private:
	char *cells;

	int coord(pair<int, int> p) {
		auto [i, j] = p;
		return i >= N || i < 0 || j >= M || j < 0 ? -1 : N*i + j;
	}
};

Direction guard_direction(char c) {
	switch (c) {
	case '^':
		return Direction::U;
	case 'v':
		return Direction::D;
	case '>':
		return Direction::R;
	case '<':
		return Direction::L;
	}

	return Direction::U;
}

pair<pair<int, int>, Direction> find_guard(Board &board) {
	pair<int, int> p(0, 0);
	for (p.first = 0; p.first < board.N; p.first++) {
		for (p.second = 0; p.second < board.M; p.second++) {
			if (board[p] != '.' && board[p] != '#') {
				Direction d = guard_direction(board[p]);
				return make_pair(p, d);
			}
		}
	}

	return make_pair(make_pair(-999, -999), Direction::U);
}

int main() {
	string line;
	vector<string> lines;
	while (getline(cin, line))
		lines.push_back(line);

	Board board(lines);

	int tot = 1;
	auto [p, d] = find_guard(board);
	board.set_visited(p);

	while (true) {
		auto q = step(p, d);
		if (board[q] == board.out_of_bound)
			break;
		if (board.is_obstruction(q)) {
			d = turn(d);
		} else {
			p = q;
			if (!board.is_visited(p)) {
				board.set_visited(p);
				tot++;
			}
		}
	}

	cout << tot << endl;

	return 0;
}
