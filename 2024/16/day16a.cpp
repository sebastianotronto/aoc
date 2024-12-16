#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>
#include <set>
using namespace std;

class Direction {
public:
	int U, R;

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

	int index() const {
		if (U == 1 && R == 0) return 0;
		if (U == -1 && R == 0) return 1;
		if (U == 0 && R == 1) return 2;
		if (U == 0 && R == -1) return 3;
		return -1;
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

class Qelem {
public:
	int64_t distance;
	Position p;
	Direction d;

	Qelem(int dis, Position pp, Direction dd) :
	    distance{dis}, p{pp}, d{dd} {}

	bool operator<(const Qelem& other) const {
		return distance > other.distance;
	}
};

class Board {
public:
	int64_t N, M;

	Board(const vector<string>& lines) :
	    N{static_cast<int64_t>(lines.size())},
	    M{static_cast<int64_t>(lines[0].size())},
	    cells(M*N), visited(4*M*N)
	{
		for (int64_t i = 0; i < N; i++)
			for (int64_t j = 0; j < M; j++)
				cells[M*i+j] = lines[i][j];
	}

	char& operator[](const Position p) {
		if (const auto c = coord(p); c == -1)
			return out_of_bound;
		else
			return cells[c];
	}

	Position find_S() {
		for (Position p(0, 0); p.i < N; p.i++)
			for (p.j = 0; p.j < M; p.j++)
				if ((*this)[p] == 'S')
					return p;
		return Position(-1, -1);
	}

	int shortest_path(Position p, Direction d) {
		clear_visited();
		priority_queue<Qelem> q;

		q.push(Qelem(0, p, d));

		while (!q.empty()) {
			auto e = q.top();
			q.pop();

			if ((*this)[e.p] == 'E')
				return e.distance;

			if (is_visited(e.p, e.d) || (*this)[e.p] == '#')
				continue;
			set_visited(e.p, e.d);

			q.push(Qelem(e.distance+1000, e.p, e.d.turnright()));
			q.push(Qelem(e.distance+1000, e.p, e.d.turnleft()));
			q.push(Qelem(e.distance+1, e.p.step(e.d), e.d));
		}
		return 999999999;
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
	vector<bool> visited;

	int64_t coord(const Position p) const {
		auto [i, j] = p;
		return i >= N || i < 0 || j >= M || j < 0 ? -1 : M * i + j;
	}

	void clear_visited() {
		for (int64_t i = 0; i < 4*M*N; i++)
			visited[i] = false;
	}

	bool is_visited(const Position p, const Direction d) {
		if (const auto c = coord(p); c == -1)
			return false;
		else
			return visited[4*c + d.index()];
	}

	void set_visited(const Position p, const Direction d) {
		if (const auto c = coord(p); c != -1)
			visited[4*c + d.index()] = true;
	}
};

int main() {
	string line;
	vector<string> lines;

	while (getline(cin, line))
		lines.push_back(line);

	Board board(lines);
	Direction d('>');
	Position p = board.find_S();

	cout << board.shortest_path(p, d) << endl;

	return 0;
}
