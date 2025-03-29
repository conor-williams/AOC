#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// Function: run_activation_system
// Parameters:
//   magic_number: an integer read from the file (acting as a constant for each run)
//   is_part_1: a boolean flag indicating which part of the computation to execute
// Returns an integer result based on the internal logic
int run_activation_system(int magic_number, bool is_part_1) {
	// Initialize a set to store seen values, variable c, and last_unique_c as in the original Python code
	set<int> seen;
	int c = 0;
	int last_unique_c = -1;

	while (true) {
		int a = c | 65536;  // Bitwise OR operation between c and 65536
		c = magic_number;   // Reset c to the magic_number

		while (true) {
			// Update c with a series of bitwise and arithmetic operations to mirror the Python behavior
			c = (((c + (a & 255)) & 16777215) * 65899) & 16777215;

			// Check if a is less than 256
			if (256 > a) {
				if (is_part_1) {
					return c;  // For part 1, immediately return c
				} else {
					if (seen.find(c) == seen.end()) {
						seen.insert(c);  // Add c to the set if it has not been seen before
						last_unique_c = c;
						break;  // Break from the inner loop and continue the outer loop
					} else {
						return last_unique_c;  // If c is seen again, return the last unique value of c
					}
				}
			} else {
				a = a / 256;  // Integer division to reduce a
			}
		}
	}
}

int main(int argc, char **argv) {
	printf("2018 day21 Part2\n");
	// Open the file "i1.txt" for reading

	ifstream infile(argv[1]);

#ifdef _ACCOLADE_
	printf("deleted on reddit, codeconvert.ai no modification\n");
#endif
	//
	// Read all lines from the file into a vector of strings
	vector<string> lines;
	string line;
	while (getline(infile, line)) {
		lines.push_back(line);
	}
	infile.close();

	// Ensure the file has at least 9 lines, as we need index 8
	//if (lines.size() < 9) {
	//   cerr << "Error: not enough lines in file" << endl;
	//  return 1;
	//}

	// Tokenize the 9th line (index 8) to extract the magic_number (the second token)
	istringstream iss(lines[8]);
	vector<string> tokens;
	string token;
	while (iss >> token) {
		tokens.push_back(token);
	}
	/*
	if (tokens.size() < 2) {
		cerr << "Error: not enough tokens in line" << endl;
		return 1;
	}
	*/
	int magic_number = stoi(tokens[1]);  // Convert the second token to an integer

	// Print the output for part 1 and part 2 respectively by calling run_activation_system
	///cout << run_activation_system(magic_number, true) << endl;
	//cout << run_activation_system(magic_number, false) << endl;
	int ans2 =  run_activation_system(magic_number, false);

	printf("**ans: %d\n", ans2);
	return 0;
}

