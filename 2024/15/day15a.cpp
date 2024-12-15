#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include <set>
using namespace std;

class Direction {
public:
	const int U, R;

	Direction(char c) :
	    U{c == 'v' ? 1 : (c == '^' ? -1 : 0)},
	    R{c == '>' ? 1 : (c == '<' ? -1 : 0)} {}

	Direction(const int i, const int j) : U{i}, R{j} {}

	Direction turnright() const {
		return turn(-1, 0);
	}

	Direction turnleft() const {
		return turn(1, 0);
	}

	bool operator<(const Direction& d) const { // For set<Direction>
		return this->U < d.U || (this->U == d.U && this->R < d.R);
	}
private:
	Direction turn(int64_t sin, int64_t cos) const {
		return Direction(cos * U - sin * R, sin * U + cos * R);
	}
};

class Position {
public:
	int64_t i, j;

	Position() : Position(0, 0) {}

	Position(int64_t a, int64_t b) : i{a}, j{b} {}

	Position step(const Direction d) const {
		return Position(i+d.U, j+d.R);
	}
};

const Direction all_directions[] = {
	Direction(1, 0), Direction(-1, 0), Direction(0, 1), Direction(0, -1)
};

class Board {
public:
	int64_t N, M;
	Position robot;

	Board(const vector<string>& lines) :
	    N{static_cast<int64_t>(lines.size())},
	    M{static_cast<int64_t>(lines[0].size())},
	    cells(M*N)
	{
		for (int64_t i = 0; i < N; i++) {
			for (int64_t j = 0; j < M; j++) {
				cells[N*i+j] = lines[i][j];
				if (lines[i][j] == '@')
					robot = Position(i, j);
			}
		}
	}

	char& operator[](const Position p) {
		if (const auto c = coord(p); c == -1)
			return out_of_bound;
		else
			return cells[c];
	}

	void move_robot(const Direction d) {
		if (move(robot, d))
			robot = robot.step(d);
	}

	int64_t gps() {
		int64_t tot = 0;
		for (Position p(0, 0); p.i < N; p.i++)
			for (p.j = 0; p.j < M; p.j++)
				if ((*this)[p] == 'O')
					tot += 100*p.i + p.j;
		return tot;
	}

	void print() {
		for (Position p(0, 0); p.i < N; p.i++) {
			for (p.j = 0; p.j < M; p.j++)
				cout << (*this)[p];
			cout << endl;
		}
	}
private:
	char out_of_bound = '$';

	vector<char> cells;

	int64_t coord(const Position p) const {
		auto [i, j] = p;
		return i >= N || i < 0 || j >= M || j < 0 ? -1 : N * i + j;
	}

	bool move(Position p, Direction d) {
		auto q = p.step(d);
		switch ((*this)[q]) {
		case '.':
			(*this)[q] = (*this)[p];
			(*this)[p] = '.';
			return true;
		case 'O':
			return move(q, d) ? move(p, d) : false;
		default:
			return false;
		}
	}
};

int main() {
	string line;
	vector<string> lines;

	for (getline(cin, line); line.size() > 0; getline(cin, line))
		lines.push_back(line);
	Board board(lines);

	while (getline(cin, line))
		for (const auto& c : line)
			board.move_robot(Direction(c));

	cout << board.gps() << endl;

	return 0;
}
