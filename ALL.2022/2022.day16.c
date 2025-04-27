#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>

//Gravitar64 + codeconvert.ai
using namespace std;

vector<vector<string>> read_puzzle(const string &file) {
	ifstream f(file);
	vector<vector<string>> puzzle;
	string line;
	regex token_regex("[A-Z]+|\\d+");
	while(getline(f, line)) {
		// Process each line starting from the second character and find tokens
		string subline = line.substr(1);
		sregex_iterator iter(subline.begin(), subline.end(), token_regex);
		sregex_iterator end;
		vector<string> tokens;
		for(; iter != end; ++iter) {
			tokens.push_back(iter->str());
		}
		puzzle.push_back(tokens);
	}
	return puzzle;
}

pair<int, int> solve(const vector<vector<string>> &puzzle) {
	// graph = {valve:leads for valve, _, *leads in puzzle}
	map<string, vector<string>> graph;
	for (const auto &tokens : puzzle) {
		if (tokens.size() >= 1) {
			string valve = tokens[0];
			vector<string> leads;
			for (size_t j = 2; j < tokens.size(); j++) {
				leads.push_back(tokens[j]);
			}
			graph[valve] = leads;
		}
	}

	// flows = {valve: int(flow) for valve, flow, *_ in puzzle if flow != '0'}
	map<string, int> flows;
	for (const auto &tokens : puzzle) {
		if (tokens.size() >= 2) {
			string valve = tokens[0];
			string flow_str = tokens[1];
			if (flow_str != "0") {
				flows[valve] = stoi(flow_str);
			}
		}
	}

	// indicies = {valve: 1 << i for i, valve in enumerate(flows)}
	map<string, int> indicies;
	int idx = 0;
	for (const auto &kv : flows) {
		indicies[kv.first] = 1 << idx;
		idx++;
	}

	// distances = {(v,l): 1 if l in graph[v] else 1000 for l in graph for v in graph}
	map<pair<string, string>, int> distances;
	for (const auto &v_pair : graph) {
		for (const auto &l_pair : graph) {
			string v = v_pair.first;
			string l = l_pair.first;
			if (find(graph[v].begin(), graph[v].end(), l) != graph[v].end())
				distances[{v, l}] = 1;
			else
				distances[{v, l}] = 1000;
		}
	}

	// floyd-warshall = Distance for any possible pair of valves
	vector<string> keys;
	for (const auto &kv : graph)
		keys.push_back(kv.first);
	for (const auto &k : keys) {
		for (const auto &i_val : keys) {
			if(i_val == k) continue;
			for (const auto &j : keys) {
				if(j == k || j == i_val) continue;
				distances[{i_val, j}] = min(distances[{i_val, j}], distances[{i_val, k}] + distances[{k, j}]);
			}
		}
	}

	// define visit as recursive lambda function:
	function<map<int,int>&(const string&, int, int, int, map<int,int>&)> visit = 
		[&](const string &valve, int minutes, int bitmask, int pressure, map<int,int> &answer) -> map<int,int>& {
			// answer[bitmask] = max(answer.get(bitmask, 0), pressure)
			if (answer.find(bitmask) == answer.end() || answer[bitmask] < pressure)
				answer[bitmask] = pressure;
			// for valve2, flow in flows.items():
			for (const auto &kv : flows) {
				string valve2 = kv.first;
				int flow = kv.second;
				int remaining_minutes = minutes - distances[{valve, valve2}] - 1;
				if ((indicies[valve2] & bitmask) || remaining_minutes <= 0)
					continue;
				visit(valve2, remaining_minutes, bitmask | indicies[valve2], pressure + flow * remaining_minutes, answer);
			}
			return answer;
		};

	// part1     = max(visit('AA', 30, 0, 0, {}).values())
	map<int,int> answer1;
	visit("AA", 30, 0, 0, answer1);
	int part1 = 0;
	for (const auto &kv : answer1) {
		part1 = max(part1, kv.second);
	}

	// visited2  = visit('AA', 26, 0, 0, {})
	map<int,int> visited2;
	visit("AA", 26, 0, 0, visited2);
	// part2     = max(v1+v2 for bitm1, v1 in visited2.items()
	//                 for bitm2, v2 in visited2.items() if not bitm1 & bitm2)
	int part2 = 0;
	for (const auto &kv1 : visited2) {
		for (const auto &kv2 : visited2) {
			if (!(kv1.first & kv2.first))
				part2 = max(part2, kv1.second + kv2.second);
		}
	}

	return {part1, part2};
}

int main(int argc, char **argv) {
	printf("		2022 Day16 Part 1\n"); fflush(stdout);
	pair<int, int> result = solve(read_puzzle(argv[1]));
	//cout << "(" << result.first << ", " << result.second << ")" << endl;
	printf("**ans: %d\n", result.first);

	return 0;
}

