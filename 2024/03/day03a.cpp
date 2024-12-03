#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

int trymult(const string_view &s) {
	if (s.substr(0, 4) != "mul(")
		return 0;

	auto t = s.substr(4, s.length()-4);

	int x = 0, y = 0;
	int i = 0;
	for (; i < 3; i++)
		if (t[i] >= '0' && t[i] <= '9')
			x = (x*10) + t[i]-'0';
		else break;
	if (i == 0 || t[i] != ',')
		return 0;
	i++;
	int j = 0;
	for (; j < 3; j++)
		if (t[i+j] >= '0' && t[i+j] <= '9')
			y = (y*10) + t[i+j]-'0';
		else break;
	if (j == 0 || t[j+i] != ')')
		return 0;
	return x*y;
}

int mults(const string &line) {
	int result = 0;
	for (auto i = line.begin(); i != line.end(); i++)
		result += trymult(string_view(i, line.end()));
	return result;
}

int main() {
	string line;
	int result = 0;
	while (cin >> line)
		result += mults(line);
	cout << result << endl;
	return 0;
}
