#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>

int main(int argc, char **argv) {
	printf("		2022 Day9 Part 2\n");
	if (argc < 2) {printf("ERROR args file\n"); exit(0);}
#ifdef _ACCOLADE_
	printf("ta to codeconvert.ai (zeo manipulation) & DaydreamingThinker for the python code\n");
#endif
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> inp;

	while (std::getline(f, line)) {
		inp.push_back(line);
	}

	std::set<std::tuple<int, int>> locs;
	std::vector<std::vector<int>> rope(10, std::vector<int>(2, 0));
	locs.insert(std::make_tuple(rope.back()[0], rope.back()[1]));

	for (const auto& row : inp) {
		std::istringstream iss(row);
		std::string d;
		int s;
		iss >> d >> s;

		for (int i = 0; i < s; ++i) {
			int dy = 0, dx = 0;
			if (d == "U") { dy = 1; }
			else if (d == "D") { dy = -1; }
			else if (d == "L") { dx = -1; }
			else if (d == "R") { dx = 1; }

			rope[0][0] += dy;
			rope[0][1] += dx;

			for (int tail = 1; tail < 10; ++tail) {
				dy = rope[tail - 1][0] - rope[tail][0];
				dx = rope[tail - 1][1] - rope[tail][1];
				if (std::max(std::abs(dy), std::abs(dx)) > 1) {
					rope[tail][0] += (dy != 0) ? dy / std::abs(dy) : 0;
					rope[tail][1] += (dx != 0) ? dx / std::abs(dx) : 0;
				}
				locs.insert(std::make_tuple(rope.back()[0], rope.back()[1]));
			}
		}
	}
	//std::cout << locs.size() << std::endl;
	printf("**ans: %d\n", (int)locs.size());
	return 0;
}
