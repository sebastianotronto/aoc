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

	Direction(const int i, const int j) : U{ i }, R{ j } {}

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
	vector<int64_t> region_area;

	Board(const vector<string>& lines) :
	N{static_cast<int64_t>(lines.size())},
	M{static_cast<int64_t>(lines[0].size())},
	region_area(M*N), cells(M*N), region(M*N), visited(M*N)
	{
		for (int64_t i = 0; i < N; i++) {
			for (int64_t j = 0; j < M; j++) {
				region[M*i+j] = -1;
				cells[M*i+j] = lines[i][j];
			}
		}
	}

	char& operator[](const Position p) {
		if (const auto c = coord(p); c == -1)
			return out_of_bound;
		else
			return cells[c];
	}

	int64_t& reg(const Position p) {
		if (const auto c = coord(p); c == -1)
			return out_of_region;
		else
			return region[c];
	}

	void fill(const Position p, const int64_t r) {
		reg(p) = r;
		region_area[r]++;
		for (const auto d : all_directions)
			if (auto q = p.step(d);
			    (*this)[q] == (*this)[p] && reg(q) != r)
				fill(q, r);
	}

	int64_t compute_perim(int64_t r) {
		int count = 0;
		for (Position p(0, 0); p.i < N; p.i++)
			for (p.j = 0; p.j < M; p.j++)
				for (Direction d : all_directions)
					if (reg(p) == r && reg(p.step(d)) != r)
						  count += walk(p, d);

		return count;
	}

private:
	char out_of_bound = '$';
	int64_t out_of_region = -1;

	vector<char> cells;
	vector<int64_t> region;
	vector<set<Direction>> visited;

	int64_t coord(const Position p) const {
		auto [i, j] = p;
		return i >= N || i < 0 || j >= M || j < 0 ? -1 : M * i + j;
	}

	bool is_visited(const Position p, const Direction d) const {
		if (auto c = coord(p); c == -1)
			return false;
		else
			return visited[c].count(d) > 0;
	}

	void set_visited(const Position p, const Direction d) {
		if (auto c = coord(p); c != -1)
			visited[c].insert(d);
	}

	int64_t walk(const Position p, const Direction d) {
		const auto r = reg(p);
		for (auto q = p; reg(q) == r && reg(q.step(d)) != r;
		    q = q.step(d.turnleft())) {
			if (is_visited(q, d))
				return 0;
			set_visited(q, d);
		}

		return 1;
	}
};

int main() {
	string line;
	vector<string> lines;
	while (getline(cin, line))
		lines.push_back(line);

	Board board(lines);

	int64_t r = 0;
	for (Position p(0, 0); p.i < board.N; p.i++)
		for (p.j = 0; p.j < board.M; p.j++)
			if (board.reg(p) == -1)
				board.fill(p, r++);

	int64_t tot = 0;
	for (int64_t i = 0; i < r; i++)
		tot += board.region_area[i] * board.compute_perim(i);

	cout << tot << endl;

	return 0;
}
