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

class KeyLock {
public:
	KeyLock() { fill(a, a+5, 0); }

	void addrow(const string& s) {
		for (int i = 0; i < 5; i++)
			a[i] += s[i] == '#';
	}

	bool operator&(const KeyLock& other) const {
		for (int i = 0; i < 5; i++)
			if (a[i] + other.a[i] > 5)
				return false;
		return true;
	}
private:
	int a[5];
};

int main() {
	vector<KeyLock> keys, locks;
	string line;
	while (getline(cin, line)) {
		KeyLock k;
		bool key = line[0] == '.';
		for (int i = 0; i < 5; i++) {
			getline(cin, line);
			k.addrow(line);
		}
		if (key) keys.push_back(k);
		else locks.push_back(k);
		getline(cin, line);
		getline(cin, line);
	}

	int tot = 0;
	for (auto k : keys)
		for (auto l : locks)
			tot += (k & l) ? 1 : 0;
	cout << tot << endl;
	return 0;
}
