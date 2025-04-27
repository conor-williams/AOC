//vss2sn
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue> 
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
#include <regex>
#include <cassert>
#include <unordered_map>
#include <array>

using namespace std;
struct Brick {
	array<int, 3> start {0,0,0};
	array<int, 3> end {0,0,0};
	int id = 0;
	bool operator == (const Brick& b) const {
		return b.start == start && b.end == end;
	}
};

bool check_if_overlap(const Brick& b1, const Brick& b2) {
	bool x_overlap = false;
	bool y_overlap = false;
	x_overlap = min(b2.start[0], b2.end[0]) <= b1.start[0] && b1.start[0] <= max(b2.start[0], b2.end[0]);
	y_overlap = min(b2.start[1], b2.end[1]) <= b1.start[1] && b1.start[1] <= max(b2.start[1], b2.end[1]);
	if (x_overlap && y_overlap) return true;
	x_overlap = x_overlap || (min(b2.start[0], b2.end[0]) <= b1.end[0] && b1.end[0] <= max(b2.start[0], b2.end[0]));
	y_overlap = y_overlap || (min(b2.start[1], b2.end[1]) <= b1.end[1] && b1.end[1] <= max(b2.start[1], b2.end[1]));
	if (x_overlap && y_overlap) return true;
	x_overlap = x_overlap || (min(b1.start[0], b1.end[0]) <= b2.start[0] && b2.start[0] <= max(b1.start[0], b1.end[0]));
	y_overlap = y_overlap || (min(b1.start[1], b1.end[1]) <= b2.start[1] && b2.start[1] <= max(b1.start[1], b1.end[1]));
	if (x_overlap && y_overlap) return true;
	x_overlap = x_overlap || (min(b1.start[0], b1.end[0]) <= b2.end[0] && b2.end[0] <= max(b1.start[0], b1.end[0]));
	y_overlap = y_overlap || (min(b1.start[1], b1.end[1]) <= b2.end[1] && b2.end[1] <= max(b1.start[1], b1.end[1]));
	if (x_overlap && y_overlap) return true;
	return false;
}

int main(int argc, char * argv[]) {
	printf("		2023 Day 22 Part 2\n");
	string input;
	if (argc > 1) {
		input = argv[1];
	}

	string line;
	fstream file(input);
	const regex mask_pattern(R"((-?[0-9]+),(-?[0-9]+),(-?[0-9]+)~(-?[0-9]+),(-?[0-9]+),(-?[0-9]+))");
	smatch mask_match;
	vector<Brick> bricks;
	while(getline(file, line)) {
		regex_search(line, mask_match, mask_pattern); 
		Brick b;
		b.id = bricks.size();
		b.start[0] = stoi(mask_match[1]);
		b.start[1] = stoi(mask_match[2]);
		b.start[2] = stoi(mask_match[3]);
		b.end[0] = stoi(mask_match[4]);
		b.end[1] = stoi(mask_match[5]);
		b.end[2] = stoi(mask_match[6]);
		bricks.push_back(b);
		// cout << b.start[0] << ' ' << b.start[1] << ' ' 
		//           << b.start[2] << ' ' << b.end[0] << ' ' 
		//           << b.end[1]<< ' ' << b.end[2] << '\n';
	}
	for (auto& b : bricks) {
		if (b.start[2] > b.end[2]) {
			swap(b.start, b.end);
		}
	}
	sort(
			begin(bricks), 
			end(bricks), 
			[](const auto& b1, const auto& b2) { 
			return b1.start[2] < b2.start[2];
			}
		 );
	{  
		const auto h = bricks[0].end[2] - bricks[0].start[2];
		bricks[0].start[2] = 1;
		bricks[0].end[2] = 1 + h;
	}
	for (int i = 1; i < (int)bricks.size(); i++) {
		// cout << "\nBrick moving down: " << char('A' + bricks[i].id) << '\n';
		const auto h = bricks[i].end[2] - bricks[i].start[2];
		for (int j = i - 1; j >= 0; j--) {
			// cout << "Comparing with: " << char('A' + bricks[j].id) << '\n';
			bricks[i].start[2] = bricks[j].start[2];
			bricks[i].end[2] = bricks[i].start[2] + h;
			if (check_if_overlap(bricks[i], bricks[j])) {
				// cout << "Overlap found between " << char('A' + bricks[i].id) << " and " << char('A' + bricks[j].id) << '\n';
				// cout << char('A' + bricks[j].id) << " occupies " << bricks[j].start[2] << "->" <<  bricks[j].end[2]  << " in Z" << '\n';
				bricks[i].start[2] = bricks[j].end[2] + 1;
				bricks[i].end[2] = bricks[i].start[2] + h;
				// cout << char('A' + bricks[i].id) << " now set to " << bricks[i].start[2] << "->" <<  bricks[i].end[2]  << '\n';
				break;
			}
		}
		// While the bricks are arranged in z bfore they start falling, 
		// they might have a differnt height order after they land
		partial_sort(
				begin(bricks), 
				next(begin(bricks), i), 
				end(bricks), 
				[](const auto& b1, const auto& b2) { 
				return b1.end[2] < b2.end[2];
				}
				);
	}
	array<int, 3> values {0,0,0};
	for (const auto& b : bricks) {
		values[0] = max(values[0], b.start[0]);
		values[0] = max(values[0], b.end[0]);
		values[1] = max(values[1], b.start[1]);
		values[1] = max(values[1], b.end[1]);
		values[2] = max(values[2], b.start[2]);
		values[2] = max(values[2], b.end[2]);
	}
	vector<vector<vector<int>>> map (
			values[0]+1, vector<vector<int>>(
				values[1]+1, vector<int>(
					values[2]+1, 0
					)
				)
			);
	// cout << values[0] << ' ' << values[1] << ' ' << values[2] << '\n';
	for (const auto& b : bricks) {
		for (int x = min(b.start[0],b.end[0]); x <= max(b.start[0],b.end[0]); x++) {
			for (int y = min(b.start[1], b.end[1]); y <= max(b.start[1],b.end[1]); y++) {
				for (int z = min(b.start[2], b.end[2]); z <= max(b.start[2],b.end[2]); z++) {
					// cout << x << ' ' << y << ' ' << z << '\n';
					map[x][y][z] = b.id;
				}
			}
		}
	}

	// for (int z = 0; z <= values[2]; z++) {
	//   for (int x = 0; x <= values[0]; x++) {
	//     cout << map[x][0][z];
	//   }
	//   cout << '\n';
	// }

	unordered_map<int, vector<int>> supports;
	unordered_map<int, vector<int>> supported_by;
	for(const auto& b : bricks) {
		supports[b.id] = {};
		supported_by[b.id] = {};
	}
	for (int i = 0; i < (int)bricks.size(); i++) {
		for (int j = 0; j < (int)bricks.size(); j++) {
			if (i == j) continue;
			if(bricks[i].end[2] + 1 == bricks[j].start[2] && check_if_overlap(bricks[i], bricks[j])) {
				supports[bricks[i].id].push_back(bricks[j].id);
				supported_by[bricks[j].id].push_back(bricks[i].id);
			}
		}
	}
	size_t count = 0;
	for (const auto& b : bricks) {
		queue<int> q;
		for (const auto& ele : supports[b.id]) {
			q.push(ele);
		}
		// Do not cache bricks that might have been seen as 
		// they are added each time one of the bricks that supports them is destroyed
		// Only the last time they are added, 
		// at which point all the bricks supporting them might have been destroyed
		// will they be free fall and hence be counted
		unordered_set<int> moved {b.id};
		while(!q.empty()) {
			const auto current = q.front();
			q.pop();
			bool will_move = true;
			for (const auto& ele : supported_by[current]) {
				if (moved.find(ele) == moved.end()) {
					will_move = false;
					break;
				}
			}
			if (!will_move) continue;
			moved.insert(current);
			for (const auto& supported_by_current : supports[current]) {
				q.push(supported_by_current);
			}
		}
		count += moved.size() - 1;
	}
	//cout << count << '\n';
	printf("**ans: %d\n", (int)count);
	return 0;
}
