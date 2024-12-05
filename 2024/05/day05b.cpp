#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <set>
#include <vector>
using namespace std;

vector<int> readints(string &s) {
	vector<int> v;
	stringstream sin(s);
	int x;

	while (sin >> x)
		v.push_back(x);

	return v;
}

bool valid(vector<int> &v, vector<pair<int, int>> &rules) {
	for (unsigned i = 0; i < v.size(); i++)
		for (unsigned j = i+1; j < v.size(); j++)
			for (auto r : rules)
				if (v[i] == r.second && v[j] == r.first)
					return false;
	return true;
}

bool canbenext(int x, vector<int> &v, bool picked[], vector<pair<int, int>> &rules) {
	for (unsigned i = 0; i < v.size(); i++) {
		if (picked[i])
			continue;
		for (auto r : rules)
			if (r.first == v[i] && r.second == x)
				return false;
	}

	return true;
}

vector<int> sort(vector<int> &v, vector<pair<int, int>> &rules) {
	vector<int> w;
	bool picked[v.size()] = { 0 };

	while (w.size() < v.size()) {
		for (unsigned i = 0; i < v.size(); i++) {
			if (!picked[i] && canbenext(v[i], v, picked, rules)) {
				picked[i] = true;
				w.push_back(v[i]);
			}
		}
	}

	return w;
}

int main() {
	string line;
	vector<pair<int, int>> rules;
	while (getline(cin, line)) {
		if (line == "")
			break;

		replace(line.begin(), line.end(), '|', ' ');
		auto v = readints(line);
		int x = v[0];
		int y = v[1];
		rules.push_back(make_pair(x, y));
	}

	int tot = 0;
	while (getline(cin, line)) {
		replace(line.begin(), line.end(), ',', ' ');
		auto v = readints(line);
		if (!valid(v, rules)) {
			auto w = sort(v, rules);
			tot += w[w.size()/2];
		}
	}
	cout << tot << endl;
	return 0;
}
