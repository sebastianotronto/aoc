#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

enum class Direction { U, D, R, L, UR, UL, DR, DL };
Direction all_directions[] = {
	Direction::U, Direction::D, Direction::R, Direction::L,
	Direction::UR, Direction::UL, Direction::DR, Direction::DL
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
	case Direction::UR:
		return make_pair(i-1, j+1);
	case Direction::UL:
		return make_pair(i-1, j-1);
	case Direction::DR:
		return make_pair(i+1, j+1);
	case Direction::DL:
		return make_pair(i+1, j-1);
	}

	return make_pair(-999,-999);
}

class Board {
public:
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

	string word_at(int i, int j, Direction d, int l) {
		string ret = "";
		auto p = make_pair(i, j);
		for (int k = 0; k < l; k++, p = step(p, d))
			ret += (*this)[p];
		return ret;
	}

	~Board() {
		delete []cells;
	}

private:
	const char out_of_bound = '.';
	char *cells;

	char operator[](pair<int, int> p) {
		auto [i, j] = p;
		if (i >= N || i < 0 || j >= M || j < 0)
			return out_of_bound;
		return cells[N*i + j];
	}
};

int main() {
	string line;
	vector<string> lines;
	while (getline(cin, line))
		lines.push_back(line);

	Board board(lines);
	int tot = 0;
	for (int i = 0; i < board.N; i++) {
		for (int j = 0; j < board.M; j++) {
			int tmp = 0;
			auto p = make_pair(i, j);
			auto [x, y] = step(p, Direction::UL);
			string wUL = board.word_at(x, y, Direction::DR, 3);
			tmp += wUL == "MAS";

			pair<int&, int&>(x, y) = step(p, Direction::UR);
			string wUR = board.word_at(x, y, Direction::DL, 3);
			tmp += wUR == "MAS";

			pair<int&, int&>(x, y) = step(p, Direction::DL);
			string wDL = board.word_at(x, y, Direction::UR, 3);
			tmp += wDL == "MAS";

			pair<int&, int&>(x, y) = step(p, Direction::DR);
			string wDR = board.word_at(x, y, Direction::UL, 3);
			tmp += wDR == "MAS";

			if (tmp == 2) tot++;
		}
	}
	cout << tot << endl;

	return 0;
}
