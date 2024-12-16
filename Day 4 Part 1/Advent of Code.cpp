#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// all of these functions manually check for horizontal, vertical, and diagonal instances of 'XMAS'
// they first make sure the area to check does not exceed the bounds of either the vector nor the string

bool checkVerticalDown(int line, int col, vector<string> input) {
	if ((line + 3) < input.size()) {
		char m = input.at(line + 1).at(col);
		char a = input.at(line + 2).at(col);
		char s = input.at(line + 3).at(col);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

bool checkVerticalUp(int line, int col, vector<string> input) {
	if ((line - 3) >= 0) {
		char m = input.at(line - 1).at(col);
		char a = input.at(line - 2).at(col);
		char s = input.at(line - 3).at(col);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

bool checkHorizontalLeft(int line, int col, vector<string> input) {
	string lineStr = input.at(line);
	if ((col - 3) >= 0) {
		char m = lineStr.at(col - 1);
		char a = lineStr.at(col - 2);
		char s = lineStr.at(col - 3);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

bool checkHorizontalRight(int line, int col, vector<string> input) {
	string lineStr = input.at(line);
	if ((col + 3) < lineStr.length()) {
		if (lineStr.at(col + 1) == 'M' && lineStr.at(col + 2) == 'A' && lineStr.at(col + 3) == 'S') {
			return true;
		}
	}
	return false;
}

bool checkDiagonalNorthEast(int line, int col, vector<string> input) {
	if ((line - 3) >= 0 && (col + 3) < input.at(0).length()) {
		char m = input.at(line - 1).at(col + 1);
		char a = input.at(line - 2).at(col + 2);
		char s = input.at(line - 3).at(col + 3);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

bool checkDiagonalSouthEast(int line, int col, vector<string> input) {
	if ((line + 3) < input.size() && (col + 3) < input.at(0).length()) {
		char m = input.at(line + 1).at(col + 1);
		char a = input.at(line + 2).at(col + 2);
		char s = input.at(line + 3).at(col + 3);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

bool checkDiagonalNorthWest(int line, int col, vector<string> input) {
	if ((line - 3) >= 0 && (col - 3) >= 0) {
		char m = input.at(line - 1).at(col - 1);
		char a = input.at(line - 2).at(col - 2);
		char s = input.at(line - 3).at(col - 3);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

bool checkDiagonalSouthWest(int line, int col, vector<string> input) {
	if ((line + 3) < input.size() && (col - 3) >= 0) {
		char m = input.at(line + 1).at(col - 1);
		char a = input.at(line + 2).at(col - 2);
		char s = input.at(line + 3).at(col - 3);
		if (m == 'M' && a == 'A' && s == 'S') {
			return true;
		}
	}
	return false;
}

int main()
{
	ifstream file("input.txt");

	vector<string> input;

	if (file.is_open()) {

		string line;

		// reads file line-by-line, saves each line to 'input'
		while (getline(file, line)) {
			input.push_back(line);
		}
	}

	int sum = 0;

	// loops through each character in the input. if the char is equal to 'X', it checks whether that 'X' completes an 'XMAS'
	// if 'XMAS' is recognized, the sum is increased by one
	for (int line = 0; line < input.size(); line++) {
		string lineStr = input.at(line);
		for (int col = 0; col < lineStr.length(); col++) {
			if (lineStr.at(col) == 'X') {
				if (checkHorizontalRight(line, col, input)) {
					sum++;
				}
				if (checkHorizontalLeft(line, col, input)) {
					sum++;
				}
				if (checkVerticalUp(line, col, input)) {
					sum++;
				}
				if (checkVerticalDown(line, col, input)) {
					sum++;
				}
				if (checkDiagonalNorthEast(line, col, input)) {
					sum++;
				}
				if (checkDiagonalNorthWest(line, col, input)) {
					sum++;
				}
				if (checkDiagonalSouthEast(line, col, input)) {
					sum++;
				}
				if (checkDiagonalSouthWest(line, col, input)) {
					sum++;
				}
			}
		}
	}

	// prints sum to console
	cout << sum;

	return 0;

}