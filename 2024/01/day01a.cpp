#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int x, y, tot;
	vector<int> v, w;

	while (cin >> x >> y) {
		v.push_back(x);
		w.push_back(y);
	}

	sort(v.begin(), v.end());
	sort(w.begin(), w.end());

	tot = 0;
	for (unsigned i = 0; i < v.size(); i++)
		tot += abs(v[i] - w[i]);

	cout << tot << endl;
	return 0;
}
