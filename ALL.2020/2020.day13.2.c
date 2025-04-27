#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv) {
	printf("		2020 Day 13 Part 2\n");
	// #rune_kg on reddit
	// Include i/o and file handling libraries

	// Open file "i1.txt" and read its contents line by line
	ifstream file(argv[1]);
	if (!file) {
		cerr << "Error opening file." << endl;
		return 1;
	}
	string line;
	vector<string> lines;
	while(getline(file, line)) {
		lines.push_back(line);
	}
	file.close();

	// Ensure that there are at least two lines in the file.
	if (lines.size() < 2) {
		cerr << "File does not contain enough lines." << endl;
		return 1;
	}

	// Read the first and second lines
	string a = lines[0];
	string b = lines[1];

	// Convert the first line to an integer timestamp.
	//long long timestamp = stoll(a);

	// Parse the second line to create a vector of bus pairs (offset, bus id)
	vector<pair<int, long long>> busses;
	stringstream ss(b);
	string token;
	int index = 0;
	while(getline(ss, token, ',')) {
		if (token != "x") {
			busses.push_back(make_pair(index, stoll(token)));
		}
		index++;
	}

	// Part 1.
	// Initialize min_wait to 999999 (similar to Python's sys.maxint alternative)
	//long long min_wait = 999999;
	//long long part1 = 0;  // Will store the part1 result.

	// Part 2.
	long long d = 1;
	long long i = 0;  // Using 'i' to replicate the Python variable

	// Process each bus in the list.
	for (auto &bus_pair : busses) {
		int offset = bus_pair.first;
		long long bus = bus_pair.second;

		// Part 1.
		// Calculate loops equivalent to Python's: loops = -(timestamp // -bus)
		// This is equivalent to performing a ceiling division: (timestamp + bus - 1) / bus
		/*
		   long long loops = (timestamp + bus - 1) / bus;
		   long long wait = loops * bus - timestamp;
		   if (wait < min_wait) {
		   part1 = wait * bus;
		   min_wait = wait;
		   }
		   */

		// Part 2.
		while (true) {
			i += d;
			if ((i + offset) % bus == 0) {
				d *= bus;
				break;
			}
		}
	}

	// Uncomment the following line to print part1 result if needed.
	// cout << part1 << endl;

	// Print the final result (i)
	//cout << i << endl;
	printf("**ans: %lld\n", i);
	return 0;
}

