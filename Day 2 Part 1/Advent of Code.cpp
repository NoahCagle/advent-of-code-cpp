#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool safe(string s) {
	int space = s.find(' ');
	int last = -1;
	bool increasing = false;
	bool decreasing = false;
	bool ret = true;

	while (space != string::npos) {
		string sub = s.substr(0, space);
		int n = stoi(sub);
		if (last == -1) {
			last = n;
		} else {
			int diff = last - n;
			if (diff > 0) {
				decreasing = true;
			}
			else if (diff < 0) {
				increasing = true;
			}

			int av = abs(diff);

			if (av > 3 || av < 1) {
				ret = false;
			}

		}

		last = n;
		s = s.substr(space + 1, s.length() - space);
		space = s.find(' ');

	}

	int n = stoi(s);
	int diff = last - n;
	if (diff > 0) {
		decreasing = true;
	}
	else if (diff < 0) {
		increasing = true;
	}

	int av = abs(diff);

	if (av > 3 || av < 1) {
		ret = false;
	}

	if (increasing && decreasing) {
		ret = false;
	}

	return ret;

}

int main()
{
	ifstream file("input.txt");

	string line;

	int sumSafe = 0;

	if (file.is_open()) {

		while (getline(file, line)) {
			if (safe(line)) sumSafe++;
		}

		file.close();

	}

	cout << sumSafe;

	return 0;

}