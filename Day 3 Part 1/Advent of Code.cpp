#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// takes a valid expression in the form of 'x,y'
// separates the string at the comma, parses integers on either side, then returns the multiple of x and y
int multiply(string s) {
	int comma = s.find(',');
	string s1 = s.substr(0, comma);
	string s2 = s.substr(comma + 1, s.length() - comma);

	int n1 = stoi(s1);
	int n2 = stoi(s2);

	return n1 * n2;

}

// checks expression to ensure only numbers and commas are present, any other character disqualifies the expression
// not proud of this, but it works :)
bool isValid(string s) {
	bool ret = true;

	for (char c : s) {
		bool valid = false;

		if (c == '0') valid = true;
		if (c == '1') valid = true;
		if (c == '2') valid = true;
		if (c == '3') valid = true;
		if (c == '4') valid = true;
		if (c == '5') valid = true;
		if (c == '6') valid = true;
		if (c == '7') valid = true;
		if (c == '8') valid = true;
		if (c == '9') valid = true;
		if (c == ',') valid = true;

		if (!valid) ret = false;

	}

	return ret;

}

// returns the substring between the next instance of 'mul(' and ')'
string nextMultiple(string s, int indexMul) {

	string sub = s.substr(indexMul, s.length() - indexMul);

	int indexParenthesis = sub.find(')');

	string mul = sub.substr(4, indexParenthesis - 4);

	return mul;

}

int main()
{
	ifstream file("input.txt");

	int sum = 0;

	if (file.is_open()) {
	
		string line;

		// reads file line-by-line
		while (getline(file, line)) {
			// create vector to store all expressions
			vector<string> muls;

			// find index of the next instance of 'mul('
			int indexMul = line.find("mul(");

			while (indexMul != string::npos) {
				// add expression to muls
				muls.push_back(nextMultiple(line, indexMul));

				// remove everything from current line up to the 'm' in 'mul(' such that it won't be recognized again
				line = line.substr(indexMul + 1, line.size() - (indexMul + 1));

				// find next instance of 'mul(', continue until there are no more in this line
				indexMul = line.find("mul(");
			}

			// loop through list of expressions and remove any that are not 'valid'
			for (int i = 0; i < muls.size(); i++) {
				if (!isValid(muls.at(i))) {
					muls.erase(muls.begin() + i);
					i--;
				}
			}

			// sum the result of multiplying each expression
			for (string s : muls) {
				sum += multiply(s);
			}

		}

		file.close();

		// output sum of all lines
		cout << "Sum: " << sum << endl;

	}


	return 0;

}