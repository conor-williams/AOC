#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <functional>
#include <numeric>
#include <utility>

//imgtezak

// Structure for Part 1 condition rules and final rule in workflow
struct Condition1 {
	bool isFinal; // false for condition rule, true for final rule
	std::string cat; // category for condition (empty for final rule)
	std::string op;  // operator for condition (empty for final rule)
	std::string amt; // amount for condition (empty for final rule)
	std::string res; // result state or final rule string
};

long long part1(const std::string &puzzle_input) {
	// Split the puzzle_input into workflows and parts (split by "\n\n")
	size_t pos = puzzle_input.find("\n\n");
	std::string workflows = puzzle_input.substr(0, pos);
	std::string parts = puzzle_input.substr(pos + 2);

	std::string work_regex_str = R"((\w+)\{([^}]+)\})";
	std::string cond_regex_str = R"((\w+)(<|>)(\d+):(\w+))";
	std::regex work_regex(work_regex_str);
	std::regex cond_regex(cond_regex_str);

	std::map<std::string, std::vector<Condition1>> flow;

	// For each workflow rule found by regex in "workflows"
	auto work_begin = std::sregex_iterator(workflows.begin(), workflows.end(), work_regex);
	auto work_end = std::sregex_iterator();
	for (std::sregex_iterator i = work_begin; i != work_end; ++i) {
		std::smatch match = *i;
		std::string name = match[1].str();
		std::string rules = match[2].str();
		// Find all condition rules within rules using cond_regex
		std::vector<Condition1> conditionList;
		auto cond_begin = std::sregex_iterator(rules.begin(), rules.end(), cond_regex);
		auto cond_end = std::sregex_iterator();
		for (std::sregex_iterator j = cond_begin; j != cond_end; ++j) {
			std::smatch c_match = *j;
			Condition1 cond;
			cond.isFinal = false;
			cond.cat = c_match[1].str();
			cond.op  = c_match[2].str();
			cond.amt = c_match[3].str();
			cond.res = c_match[4].str();
			conditionList.push_back(cond);
		}
		// Get final rule: it's the last element after splitting rules by comma
		std::istringstream iss(rules);
		std::string token;
		std::string finalRule;
		while (std::getline(iss, token, ',')) {
			finalRule = token;
		}
		// Append final rule as a Condition1 with isFinal true
		Condition1 finalCond;
		finalCond.isFinal = true;
		finalCond.cat = "";
		finalCond.op = "";
		finalCond.amt = "";
		finalCond.res = finalRule;
		// Combine the conditionals with the final rule
		conditionList.push_back(finalCond);
		flow[name] = conditionList;
	}

	std::string part_regex_str = R"(x=(\d+),m=(\d+),a=(\d+),s=(\d+))";
	std::regex part_regex(part_regex_str);
	long long total_accepted = 0;

	// For each part found in parts using part_regex
	auto part_begin = std::sregex_iterator(parts.begin(), parts.end(), part_regex);
	auto part_end = std::sregex_iterator();
	for (std::sregex_iterator i = part_begin; i != part_end; ++i) {
		std::smatch match = *i;
		// Create part as a map with keys corresponding to 'x', 'm', 'a', 's'
		std::map<char, int> part;
		part['x'] = std::stoi(match[1].str());
		part['m'] = std::stoi(match[2].str());
		part['a'] = std::stoi(match[3].str());
		part['s'] = std::stoi(match[4].str());

		std::string curr = "in";
		while (curr != "A" && curr != "R") {
			bool conditionTriggered = false;
			// Loop through the condition rules except the final rule
			const std::vector<Condition1> &rules = flow[curr];
			for (size_t i = 0; i < rules.size() - 1; i++) {
				const Condition1 &cond = rules[i];
				// Use operator mapping: '>' uses greater than, '<' uses less than
				int partValue = part[cond.cat[0]]; // cat is one character from "xmas"
				int amt = std::stoi(cond.amt);
				if ((cond.op == ">" && partValue > amt) || (cond.op == "<" && partValue < amt)) {
					curr = cond.res;
					conditionTriggered = true;
					break;
				}
			}
			if (!conditionTriggered) {
				// Set curr to final rule
				curr = rules.back().res;
			}
		}

		if (curr == "A") {
			int sum = part['x'] + part['m'] + part['a'] + part['s'];
			total_accepted += sum;
		}
	}

	return total_accepted;
}

//
// Part 2 translation
//
struct Condition2 {
	bool isFinal; // false for condition rule, true for final rule
	int catIdx;   // index corresponding to character in "xmas" (unused for final rule)
	std::string op;  // operator for condition (unused for final rule)
	int amt;         // amount for condition (unused for final rule)
	std::string res; // result state or final rule string
};

long long part2(const std::string &puzzle_input) {
	// Split the puzzle_input into workflows and parts (split by "\n\n")
	size_t pos = puzzle_input.find("\n\n");
	std::string workflows = puzzle_input.substr(0, pos);
	std::string parts = puzzle_input.substr(pos + 2);

	std::string work_regex_str = R"((\w+)\{([^}]+)\})";
	std::string cond_regex_str = R"((\w+)(<|>)(\d+):(\w+))";
	std::regex work_regex(work_regex_str);
	std::regex cond_regex(cond_regex_str);

	std::map<std::string, std::vector<Condition2>> flow;

	// For each workflow rule found by regex in "workflows"
	auto work_begin = std::sregex_iterator(workflows.begin(), workflows.end(), work_regex);
	auto work_end = std::sregex_iterator();
	for (std::sregex_iterator i = work_begin; i != work_end; ++i) {
		std::smatch match = *i;
		std::string name = match[1].str();
		std::string rules = match[2].str();
		std::vector<Condition2> conditional;
		// For each condition rule in rules using cond_regex
		auto cond_begin = std::sregex_iterator(rules.begin(), rules.end(), cond_regex);
		auto cond_end = std::sregex_iterator();
		for (std::sregex_iterator j = cond_begin; j != cond_end; ++j) {
			std::smatch c_match = *j;
			Condition2 cond;
			cond.isFinal = false;
			// Find index of category in string "xmas"
			std::string cat = c_match[1].str();
			size_t idx = std::string("xmas").find(cat);
			cond.catIdx = static_cast<int>(idx);
			cond.op = c_match[2].str();
			cond.amt = std::stoi(c_match[3].str());
			cond.res = c_match[4].str();
			conditional.push_back(cond);
		}
		// Get final rule: it's the last element after splitting rules by comma
		std::istringstream iss(rules);
		std::string token;
		std::string finalRule;
		while (std::getline(iss, token, ',')) {
			finalRule = token;
		}
		Condition2 finalCond;
		finalCond.isFinal = true;
		finalCond.catIdx = -1;
		finalCond.op = "";
		finalCond.amt = 0;
		finalCond.res = finalRule;
		conditional.push_back(finalCond);
		flow[name] = conditional;
	}

	// Define the state structure for Part 2 simulation
	struct State {
		std::string curr;
		std::vector<std::pair<int,int>> intervals;
	};

	// Start state: ('in', (1, 4000), (1, 4000), (1, 4000), (1, 4000))
	State start;
	start.curr = "in";
	start.intervals = { {1, 4000}, {1, 4000}, {1, 4000}, {1, 4000} };

	std::vector<State> queue;
	queue.push_back(start);
	long long total_accepted = 0;

	while (!queue.empty()) {
		State state = queue.back();
		queue.pop_back();
		std::string curr = state.curr;
		std::vector<std::pair<int,int>> intervals = state.intervals;
		if (curr == "A" || curr == "R") {
			if (curr == "A") {
				// Compute product of (hi - lo + 1) for each interval
				long long prod = 1;
				for (const auto &pr : intervals) {
					prod *= (pr.second - pr.first + 1);
				}
				total_accepted += prod;
			}
			continue;
		}
		bool broke = false;
		const std::vector<Condition2> &rules = flow[curr];
		// Process each condition rule except the final rule
		for (size_t i = 0; i < rules.size() - 1; i++) {
			const Condition2 &cond = rules[i];
			int cat_idx = cond.catIdx;
			int lo = intervals[cat_idx].first;
			int hi = intervals[cat_idx].second;
			// All passthrough, no transfer
			if ((cond.op == ">" && cond.amt >= hi) || (cond.op == "<" && cond.amt <= lo)) {
				continue;
			}
			// All transfer no passthrough
			if ((cond.op == ">" && cond.amt < lo) || (cond.op == "<" && cond.amt > hi)) {
				State newState;
				newState.curr = cond.res;
				newState.intervals = intervals;
				queue.push_back(newState);
				broke = true;
				break;
			}
			// Some of both
			std::pair<int,int> transfer, passthrough;
			if (cond.op == ">") {
				transfer = std::make_pair(cond.amt + 1, hi);
				passthrough = std::make_pair(lo, cond.amt);
			} else {
				transfer = std::make_pair(lo, cond.amt - 1);
				passthrough = std::make_pair(cond.amt, hi);
			}
			intervals[cat_idx] = passthrough;
			std::vector<std::pair<int,int>> intervals2 = intervals;
			intervals2[cat_idx] = transfer;
			State newState;
			newState.curr = cond.res;
			newState.intervals = intervals2;
			queue.push_back(newState);
		}
		// Else clause: if loop not broken then remaining is transferred
		if (!broke) {
			State newState;
			newState.curr = rules.back().res;
			newState.intervals = intervals;
			queue.push_back(newState);
		}
	}

	return total_accepted;
}

int main(int argc, char **argv){

	printf("2023 Day 19 Part2\n");
#ifdef _ACCOLADE_
	printf("mgtezak on reddit - + codeconvert.ai, t.y.\n");
#endif
	std::ifstream f(argv[1]);
	std::stringstream buffer;
	buffer << f.rdbuf();
	std::string puzzle_input = buffer.str();

	//std::cout << "Part 1: " << part1(puzzle_input) << std::endl;
	//std::cout << "Part 2: " << part2(puzzle_input) << std::endl;
	long long ans2 = part2(puzzle_input);
	printf("**ans: %lld\n", ans2);

	return 0;
}

