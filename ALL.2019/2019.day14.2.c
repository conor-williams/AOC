#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <unistd.h>

using namespace std;
vector<string> data1;
long long calculate_ore(long long amount_fuel);

//ta:Diderikdm
int fd;
int main(int argc, char **argv) {
	printf("2019 Day14 part2\n");
	//part 1: 1046184
#ifdef _ACCOLADE_
	printf("ta Diderikdm on reddit + codeconvert.ai - 1 hour manipulation (float)\n");
#endif
	if (argc < 2) {printf("ERR args file\n"); exit(0);}
	fflush(stdout); fd = dup(1); close(1);
	ifstream infile(argv[1]);
	string line;
	while(getline(infile, line)) {
		data1.push_back(line);
	}

	long long one_fuel = calculate_ore(1);
	cout << one_fuel << endl;

	//part 2: 1639374
	unsigned long long x = 1000000000000ULL / one_fuel;
	printf("x is %llu\n", x);
	unsigned long long y = calculate_ore(x);
	printf("y is %llu\n", y);
	double part = (double)(1000000000000ULL / (double)y);
	printf("part is %f\n", part);
	unsigned long long final_result = x * part;
	printf("final_result %llu\n", final_result);
	cout << final_result << endl;
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", final_result);
	/////////////////////// (pyt...)
	///	print(int(int(1000000000000 / one_fuel)*(1000000000000 / calculate_ore(int(1000000000000 / one_fuel)))))
	///	print(int(1000000000000 / one_fuel))
	///	print(calculate_ore(int(1000000000000 / one_fuel)))
	///////////////////////


	return 0;
}

long long calculate_ore(long long amount_fuel) {

	vector<vector<string>> needed;
	vector<string> result;
	map<string, long long> ing;
	map<string, long long> ing_plus;
	ing["ORE"] = 1;
	ing_plus["ORE"] = 0;

	for (auto &e : data1) {
		// Split line "e" into "need" and "res"
		size_t pos = e.find(" => ");
		string need = e.substr(0, pos);
		string res = e.substr(pos + 4);
		// Split "need" by ", "
		vector<string> parts;
		size_t start = 0;
		size_t pos_comma = need.find(", ");
		while (pos_comma != string::npos) {
			parts.push_back(need.substr(start, pos_comma - start));
			start = pos_comma + 2;
			pos_comma = need.find(", ", start);
		}
		parts.push_back(need.substr(start));
		needed.push_back(parts);

		// Split "res" by " " into amount and ingr
		size_t pos_space = res.find(" ");
		string amount_str = res.substr(0, pos_space);
		string ingr_name = res.substr(pos_space + 1);
		result.push_back(ingr_name);
		ing[ingr_name] = stoll(amount_str);
		ing_plus[ingr_name] = 0;
	}

	vector<string> chain;
	vector<long long> chain_needed;
	vector<int> chain_levelsdeep;
	chain.push_back("FUEL");
	chain_needed.push_back(amount_fuel);
	chain_levelsdeep.push_back(1);

	int e_index = 0;
	while (e_index < chain.size()) {
		int levelsdeep = chain_levelsdeep[e_index] + 1;
		for (size_t i = 0; i < result.size(); i++) {
			if (result[i] == chain[e_index]) {
				for (int j = needed[i].size() - 1; j >= 0; j--) {
					// Split needed[i][j] by " " to get need_amount and need_what
					string g = needed[i][j];
					size_t pos_space = g.find(" ");
					string need_amount_str = g.substr(0, pos_space);
					string need_what = g.substr(pos_space + 1);
					chain.insert(chain.begin() + e_index + 1, need_what);
					chain_needed.insert(chain_needed.begin() + e_index + 1, stoll(need_amount_str));
					chain_levelsdeep.insert(chain_levelsdeep.begin() + e_index + 1, levelsdeep);
				}
			}
		}
		e_index++;
	}

	long long ore_total = 0;
	int p = 1;
	while (p < chain.size()) {
		int key = 0;
		int q = 0;
		while (q < p) {
			if (chain_levelsdeep[q] < chain_levelsdeep[p]) {
				key = q;
			}
			q++;
		}
		if (chain[p] != "ORE") {
			long long factor = chain_needed[key] / ing[chain[key]];
			long long amountneeded_raw = (chain_needed[p] * factor) - ing_plus[chain[p]];
			long long amountneeded = ((long long)ceil((double)amountneeded_raw / ing[chain[p]])) * ing[chain[p]];
			chain_needed[p] = amountneeded;
			ing_plus[chain[p]] = amountneeded - amountneeded_raw;
		} else {
			long long factor = chain_needed[key] / ing[chain[key]];
			ore_total += chain_needed[p] * factor;
		}
		p++;
	}
	return ore_total;
}

