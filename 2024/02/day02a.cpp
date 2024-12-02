#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool isvalid(const string &line) {
	int x, y, b;
	istringstream s(line);

	s >> x >> y;
	b = x > y ? 1 : -1;
	do {
		int d = b * (x-y);
		if (d < 1 || d > 3)
			return false;
		x = y;
	} while (s >> y);

	return true;
}

int main() {
	int tot = 0;
	for (string line; getline(cin, line); )
		tot += isvalid(line);
	cout << tot << endl;
	return 0;
}
