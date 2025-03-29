#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <tuple>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

vector<string> grid;
set<char> allkeys;
#define IN 200

tuple<int, int> find_start_position() {
	for (int y = 0; y < (int)grid.size(); ++y) {
		for (int x = 0; x < (int)grid[y].size(); ++x) {
			if (grid[y][x] == '@') {
				//printf("%d %d\n", x , y);
				return make_tuple(x, y);
			}
		}
	}
	return make_tuple(-1, -1); // Not found
}

vector<tuple<int, int, int, char>> reachable_keys(int sx, int sy, const set<char>& keys) {
	deque<tuple<int, int, int>> q;
	q.emplace_back(sx, sy, 0);
	set<pair<int, int>> seen;
	vector<tuple<int, int, int, char>> result;
	vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	while (!q.empty()) {
		auto [cx, cy, l] = q.front();
		q.pop_front();
		if (islower(grid[cy][cx]) && keys.find(grid[cy][cx]) == keys.end()) {
			result.emplace_back(l, cx, cy, grid[cy][cx]);
			continue;
		}
		for (const auto& [dx, dy] : directions) {
			int nx = cx + dx, ny = cy + dy;
			if (seen.count({nx, ny})) continue;
			seen.insert({nx, ny});

			char c = grid[ny][nx];
			if (c != '#' && (isupper(c) == 0 || keys.count(tolower(c)))) {
				q.emplace_back(nx, ny, l + 1);
			}
		}
	}
	return result;
}

int main(int argc, char **argv) {
	FILE * a = fopen(argv[1], "r");
	printf("2019 Day18 Part2\n");
	printf("SLOW 2minutes 15seconds\n");
#ifdef _ACCOLADE_
	printf("thanks reddit:bla2 -> convert with codeconvert.ai (part1 then modify...)\n");
#endif

	char line1[IN];

	int leny;
	while(1) {
		fgets(line1, IN-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		printf("LINE: %s getchar\n", line1); getchar();
#endif
		//strcpy(grid[leny], line1);
		grid.push_back(line1);
		leny++;
	}

	/*
	   string line;
	   while (getline(cin, line)) {
	   grid.push_back(line);
	   }
	   */
	//printf("%s\n", grid[0].c_str());


	auto [x, y] = find_start_position();
	for (auto it2 = grid.begin(); it2 != grid.end(); it2++) {
		for (const auto& c : string(*it2)) {
			if (islower(c)) {
				allkeys.insert(c);
			}
		}
	}

	///NOT IN PART 1
	grid[y - 1][x] = '#';
	grid[y][x - 1] = '#';
	grid[y][x] = '#';
	grid[y][x + 1] = '#';
	grid[y + 1][x] = '#';

	/*
	   for (auto it = allkeys.begin(); it != allkeys.end(); it++) {
	   cout << *it << endl;
	   }
	   */
	///NOT IN PART1
	vector<tuple<int, int>> pos = {
		{x - 1, y - 1},
		{x + 1, y - 1},
		{x - 1, y + 1},
		{x + 1, y + 1},
	};


	using State = tuple<int, vector<tuple<int, int>>, set<char>>;
	priority_queue<State, vector<State>, greater<State>> q;
	//q.emplace(0, vector<tuple<int, int>>{ {x, y} }, set<char>{});
	q.emplace(0, pos, set<char>{});
	set<pair<vector<tuple<int, int>>, set<char>>> seen;

	while (!q.empty()) {
		auto [d, cpos, keys] = q.top();
		q.pop();

		if (keys == allkeys) {
			printf("**ans: %d\n", d);
			break;
		}

		if (seen.count({cpos, keys})) continue;
		seen.insert({cpos, keys});

		for (size_t i = 0; i < cpos.size(); ++i) {
			auto [cx, cy] = cpos[i];
			for (const auto& [l, nx, ny, key] : reachable_keys(cx, cy, keys)) {
				vector<tuple<int, int>> npos = cpos;
				npos[i] = {nx, ny};
				set<char> new_keys = keys;
				new_keys.insert(key);
				//cout << d+l << endl;
				q.emplace(d + l, npos, new_keys);
			}
		}
	}

	return 0;
}
