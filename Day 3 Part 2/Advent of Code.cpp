#include <fstream>
#include <iostream>
#include <string>
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

		// tracks whether instructions have been enabled or disabled
		bool instructionsEnabled = true;

		// reads file line-by-line
		while (getline(file, line)) {
			// create vector to store all 'commands', including expressions
			vector<string> commands;

			// find index of the next instance of 'mul(', 'do()' and 'don't()'
			int indexMul = line.find("mul(");
			int indexDo = line.find("do()");
			int indexDont = line.find("don't()");

			while (indexMul != string::npos) {

				// if there is an instance of 'do()' or 'don't()' present, check if it occurs before the next instance of 'mul('
				// if it does, add it to the list of commands before processing the next 'mul()' expression
				if (indexDo != string::npos) {
					if (indexDo < indexMul) {
						commands.push_back("do()");
					}
				}

				if (indexDont != string::npos) {
					if (indexDont < indexMul) {
						commands.push_back("don't()");
					}
				}

				// add expression to muls
				commands.push_back(nextMultiple(line, indexMul));

				// remove everything from current line up to the 'm' in 'mul(' such that it won't be recognized again
				line = line.substr(indexMul + 1, line.size() - (indexMul + 1));

				// find next instance of keywords, continue until there is no more 'mul(' in this line
				indexMul = line.find("mul(");
				indexDo = line.find("do()");
				indexDont = line.find("don't()");
			}

			// loop through list of expressions and remove any 'mul()' commands that are not 'valid'
			for (int i = 0; i < commands.size(); i++) {
				string current = commands.at(i);
				// if the current command is a 'do()' or 'don't()' command, skip it, as there is no need to check its validity
				if (current != "do()" && current != "don't()") {
					if (!isValid(current)) {
						commands.erase(commands.begin() + i);
						i--;
					}
				}
			}

			// loop through all commands. if the command is a 'do()' command, enable instructions. if it's a 'don't()' command, disable instructions
			// if the command is a 'mul()' command, add the result of the command ONLY if instructions are enabled
			for (string s : commands) {
				if (s == "do()")
					instructionsEnabled = true;
				else if (s == "don't()")
					instructionsEnabled = false;
				else if (instructionsEnabled)
					sum += multiply(s);
			}

		}

		file.close();

		// output sum of all lines
		cout << "Sum: " << sum << endl;

	}


	return 0;

}