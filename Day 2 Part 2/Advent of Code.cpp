#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// method to generate vector of integers based on a string of numbers separated by spaces
vector<int> stringToVector(string s) {
	vector<int> ret;

	// Find index of the next space
	int space = s.find(' ');

	while (space != string::npos) {
		// substring from start of string to next space
		string sub = s.substr(0, space);

		// parse substring and push it to the vector
		int n = stoi(sub);
		ret.push_back(n);

		// cut the first value from the string, find the new index of the next space
		s = s.substr(space + 1, s.length() - space);
		space = s.find(' ');
	}

	// because there are no more spaces after the last value, it gets left out unless I parse and push the remaining string
	int n = stoi(s);
	ret.push_back(n);

	return ret;

}

// determines whether or not a sequence is 'safe'
// loops through 'values' and compares current index to the previous index
bool safe(vector<int> values, int exclude) {
	// variable to memoize previous index, defaults to -1
	int last = -1;
	// boolean values to check for an increase or decrease between two values
	bool increasing = false;
	bool decreasing = false;

	// return value, remains true if not problems are found
	// is set to false if an issue is found
	bool ret = true;

	for (int i = 0; i < values.size(); i++) {
		
		// part 2 requires the ability to exclude values from the list. if the current index is not excluded, it is safe to proceed
		if (i != exclude) {
			// fetch value at current index
			int n = values.at(i);
			// last == -1, this is the first iteration. since the method compares the current index to the previous, we should not proceed
			if (last != -1) {
				int diff = n - last;
				// if the current value is higher than the previous value, the difference will be positive, therefore there is an increase. otherwise, it will be negative
				if (diff > 0) {
					increasing = true;
				}
				else if (diff < 0) {
					decreasing = true;
				}

				// find the absolute value of the difference between the current index and previous index
				int av = abs(diff);

				// if the difference is greater than 3 or less than 1, the sequence is not safe
				if (av > 3 || av < 1) {
					ret = false;
				}

			}

			// memoize current value to be used in the next iteration
			last = n;

		}
	}

	// once the loop exits, determine if there was both and increase and decrease observed
	if (increasing && decreasing) {
		ret = false;
	}

	// if a problem was found, begin excluding values until either a safe solution is found, or it is determined the sequence is unsafe regardless of exclusion
	if (!ret) {
		// for some reason, -1 is not recognized as less than (values.size() - 1), so it must be checked manually
		if (exclude < (values.size() - 1) || exclude == -1) {
			// recurse until either there are no more values to exclude, or a safe sequence is found
			ret = safe(values, exclude + 1);
		}
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
			if (safe(stringToVector(line), -1)) sumSafe++;
		}

		file.close();

	}

	cout << "Safe sequences: " << sumSafe << endl;

	return 0;

}