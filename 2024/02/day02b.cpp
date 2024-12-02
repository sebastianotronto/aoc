#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool isvalid_v(const vector<int> &v) {
	int b = v[0] > v[1] ? 1 : -1;
	for (unsigned i = 0; i < v.size()-1; i++) {
		int d = b * (v[i] - v[i+1]);
		if (d < 1 || d > 3)
			return false;
	}
	return true;
}

vector<int> getv(const string &line) {
	int x;
	vector<int> ret;
	istringstream s(line);

	while(s >> x)
		ret.push_back(x);

	return ret;
}

bool isvalid(const string &line) {
	vector v0 = getv(line);
	if (isvalid_v(v0))
		return true;
	for (unsigned i = 0; i < v0.size(); i++) {
		vector v = v0;
		v.erase(v.begin() + i);
		if (isvalid_v(v))
			return true;
	}
	return false;
}

int main() {
	int tot = 0;
	for (string line; getline(cin, line); )
		tot += isvalid(line);
	cout << tot << endl;
	return 0;
}
