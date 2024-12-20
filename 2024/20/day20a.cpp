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

class Map {
public:
	int N, M, L;
	int *cell;

	Map(const vector<string>& lines) 
	    : N{(int)lines.size()}, M{(int)lines[0].size()}, cell{new int[M*N]}
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cell[M*i+j] = lines[i][j] == '#' ? -1 : 0;
				if (lines[i][j] == 'S') {
					is = i;
					js = j;
				}
				if (lines[i][j] == 'E') {
					ie = i;
					je = j;
				}
			}
		}
		findpath();
	}

	~Map() {
		delete[] cell;
	}

	int& operator()(int i, int j) {
		if (i < 0 || i >= N || j < 0 || j >= M)
			return out_of_bound;
		return cell[M*i+j];
	}

	const int& operator()(int i, int j) const {
		if (i < 0 || i >= N || j < 0 || j >= M)
			return out_of_bound;
		return cell[M*i+j];
	}

	int cheat(int i, int j) {
		if ((*this)(i, j) != -1)
			return -1;
		if ((*this)(i+1, j) >= 0 && (*this)(i-1, j) >= 0)
			return abs((*this)(i+1, j) - (*this)(i-1, j)) - 2;
		if ((*this)(i, j+1) >= 0 && (*this)(i, j-1) >= 0)
			return abs((*this)(i, j+1) - (*this)(i, j-1)) - 2;
		return -1;
	}
private:
	int is, js, ie, je;
	int out_of_bound = -1;
	vector<pair<int, int>> directions {{0,1}, {0,-1}, {1,0}, {-1,0}};

	void findpath() {
		int i, j, k;
		for (i = is, j = js, k = 1; i != ie || j != je; step(i, j, k))
			(*this)(i, j) = k;
		(*this)(ie, je) = k;
		L = k-1;
	}

	void step(int& i, int& j, int& k) {
		k++;
		for (auto p : directions) {
			if ((*this)(i+p.first, j+p.second) == 0) {
				i = i+p.first;
				j = j+p.second;
				return;
			}
		}
		cout << "Error! at " << i << ", " << j << endl;
	}
};

int main() {
	string line;
	vector<string> lines;
	while (getline(cin, line))
		lines.push_back(line);
	Map m(lines);

	int count = 0;
	for (int i = 0; i < m.N; i++) {
		for (int j = 0; j < m.M; j++) {
			int c = m.cheat(i, j);
			if (c >= 100)
				count++;
		}
	}

	cout << count << endl;

	return 0;
}
