
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <sstream>
#include <cassert>
#include <iterator>

using namespace std;

vector<pair<int, int>> dirs = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};

// Node type for graph
using Node = tuple<int, int, int>;

struct ParseResult {
	vector<string> grid;
	pair<int, int> start;
	pair<int, int> end;
};

ParseResult parse_input(const string& input_text) {
	vector<string> grid;
	stringstream ss(input_text);
	string line;

	while (getline(ss, line)) {
		grid.push_back(line);
	}

	int R = grid.size();
	int C = grid[0].size();

	pair<int, int> start = {R - 2, 1};
	pair<int, int> end = {1, C - 2};

	assert(grid[start.first][start.second] == 'S');
	assert(grid[end.first][end.second] == 'E');

	return {grid, start, end};
}

pair<map<Node, map<Node, int>>, map<Node, map<Node, int>>> make_graph(
		const vector<string>& grid, 
		const pair<int, int>& start, 
		const pair<int, int>& end) {

	map<Node, map<Node, int>> graph;
	map<Node, map<Node, int>> rgraph; // Reverse graph

	Node start_node = make_tuple(start.first, start.second, 1);
	vector<Node> nodes_stack = {start_node};

	int count = 0;
	while (!nodes_stack.empty()) {
		Node node = nodes_stack.back();
		nodes_stack.pop_back();

		if (graph.find(node) != graph.end()) {
			continue;
		}

		int r = get<0>(node);
		int c = get<1>(node);
		int d = get<2>(node);

		// Try rotating right and left
		for (int cd : {1, -1}) {
			int dd = (d + cd + 4) % 4;
			int dr = dirs[dd].first;
			int dc = dirs[dd].second;

			if (grid[r + dr][c + dc] != '#') {
				Node new_node = make_tuple(r, c, dd);
				graph[node][new_node] = 1000;
				rgraph[new_node][node] = 1000;

				if (graph.find(new_node) == graph.end()) {
					nodes_stack.push_back(new_node);
				}
			}
		}

		// Check if we can move forwards
		int dr = dirs[d].first;
		int dc = dirs[d].second;

		if (grid[r + dr][c + dc] == '#') {
			continue;
		}

		int rr = r + dr;
		int cc = c + dc;
		int last_d = d;
		int dist = 1;

		while (true) {
			count = count + 1;
			vector<tuple<int, int, int>> valid_moves;
			int backwards_dir = (last_d + 2) % 4;

			for (int di = 0; di < 4; di++) {
				if (backwards_dir == di) {
					continue;
				}
				int dr = dirs[di].first;
				int dc = dirs[di].second;

				if (grid[rr + dr][cc + dc] != '#') {
					valid_moves.push_back(make_tuple(di, dr, dc));
				}
			}

			if (valid_moves.size() == 0) {
				break;
			} else if (valid_moves.size() == 1) {
				int di = get<0>(valid_moves[0]);
				int dr = get<1>(valid_moves[0]);
				int dc = get<2>(valid_moves[0]);

				rr += dr;
				cc += dc;
				dist += 1;

				if (make_pair(rr, cc) == end) {
					Node new_node = make_tuple(rr, cc, last_d);
					graph[node][new_node] = dist;
					rgraph[new_node][node] = dist;

					if (graph.find(new_node) == graph.end()) {
						nodes_stack.push_back(new_node);
					}
				} else {
					dist += (di == last_d) ? 0 : 1000;
					last_d = di;
				}
			} else if (valid_moves.size() > 1) {
				Node new_node = make_tuple(rr, cc, last_d);
				graph[node][new_node] = dist;
				rgraph[new_node][node] = dist;

				if (graph.find(new_node) == graph.end()) {
					nodes_stack.push_back(new_node);
				}
				break;
			}
		}
	}
 	//for (const auto& [adjacent, weight] : graph[node]) { }
	//map<Node, map<Node, int>> graph;
	/*
	for (auto it = graph.begin(); it != graph.end(); it++) {
		//Node = tuple<int, int, int>;
		printf("Key: %d %d %d\n", get<0>(it->first), get<1>(it->first), get<2>(it->first));
		for (auto valit = it->second.begin(); valit != it->second.end(); valit++) {
			printf("	Val: %d %d %d - %d\n", get<0>(valit->first), get<1>(valit->first), get<2>(valit->first), valit->second);
		}
	}
	*/


	return {graph, rgraph};
}

pair<int, int> solve(const string& input_text) {

	ParseResult parsed = parse_input(input_text);
	vector<string> grid = parsed.grid;
	pair<int, int> start = parsed.start;
	pair<int, int> end = parsed.end;

	auto [graph, rgraph] = make_graph(grid, start, end);

	priority_queue<pair<int, Node>, vector<pair<int, Node>>, greater<pair<int, Node>>> heap;
	map<Node, int> dists;

	heap.push({0, make_tuple(start.first, start.second, 1)});

	int p1;
	Node end_node;

	while (!heap.empty()) {
		auto [dist, node] = heap.top();
		heap.pop();

		if (dists.find(node) != dists.end()) {
			continue;
		}

		dists[node] = dist;
		int r = get<0>(node);
		int c = get<1>(node);
		int d = get<2>(node);

		if (make_pair(r, c) == end) {
			p1 = dist;
			end_node = node;
			break;
		}

		for (const auto& [adjacent, weight] : graph[node]) {
			int new_dist = dist + weight;
			heap.push({new_dist, adjacent});
		}
	}

	int p2 = 0;
	vector<Node> nodes = {end_node};
	set<Node> seen;
	int count = 0;

	while (!nodes.empty()) {
		count = count + 1;
		Node node = nodes.back();
		nodes.pop_back();

		if (seen.find(node) != seen.end()) {
			continue;
		}

		seen.insert(node);
		p2 += 1;

		for (const auto& [adjacent, weight] : rgraph[node]) {
			if (dists.find(adjacent) != dists.end() && 
					dists[adjacent] + graph[adjacent][node] == dists[node]) {
				nodes.push_back(adjacent);
				p2 += graph[adjacent][node] % 1000 - 1;
			}
		}
	}

	return {p1, p2};
}

int main(int argc, char **argv) {
	printf("               2024 Day 16 Part 2\n"); fflush(stdout);

	ifstream file(argv[1]);
	string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	auto result = solve(content);


        printf("**ans: ");
        printf("%d", result.second);
	printf("\n");

	return 0;
}


