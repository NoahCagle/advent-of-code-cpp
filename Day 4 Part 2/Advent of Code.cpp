#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool completesXMAS(int line, int col, vector<string> input) {
	int lineLength = input.at(0).length();

	if ((line + 1) < input.size() && (line - 1) >= 0 && (col + 1) < lineLength && (col - 1) >= 0) {
		// imagining the possible X as a 3x3 grid, with the A being in the center, we store the values at each corner
		char topLeft = input.at(line - 1).at(col - 1);
		char bottomLeft = input.at(line + 1).at(col - 1);
		char topRight = input.at(line - 1).at(col + 1);
		char bottomRight = input.at(line + 1).at(col + 1);

		// create a string with each diagonal concatenated into one
		// im concatenating separately because whenever i tried to write 'topLeft + 'A' + bottomRight' Visual Studio starting whining
		string decreasingDiagonal;
		decreasingDiagonal += topLeft;
		decreasingDiagonal += 'A';
		decreasingDiagonal += bottomRight;

		string increasingDiagonal;
		increasingDiagonal += bottomLeft;
		increasingDiagonal += 'A';
		increasingDiagonal += topRight;

		// checks whether both diagonals spell 'MAS', forward or backwards
		if (decreasingDiagonal == "MAS" || decreasingDiagonal == "SAM") {
			if (increasingDiagonal == "MAS" || increasingDiagonal == "SAM") {
				return true;
			}
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

	for (int line = 0; line < input.size(); line++) {
		string lineStr = input.at(line);
		for (int col = 0; col < lineStr.length(); col++) {
			// if a char is 'A', then send it to the completesXMAS function to check its diagonals
			// if it completes an X-MAS, increasing the sum by 1
			if (lineStr.at(col) == 'A') {
				if (completesXMAS(line, col, input)) sum++;
			}
		}
	}

	// prints sum to console
	cout << sum;

	return 0;

}