#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>

using namespace std;

//Gravitar64

// Read the puzzle file and return a string with only allowed characters ('A', 'B', 'C', 'D', '.')
string read_puzzle(const string &filename) {
	ifstream f(filename);
	ostringstream oss;
	oss << f.rdbuf();
	string content = oss.str();
	string result;
	for (char c : content) {
		if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '.')
			result.push_back(c);
	}
	return result;
}

// Wenn alle besetzten room_pos mit den ziel-amphis besetzt sind, dann sollte kein amphi
// den Raum verlassen. Allein diese Änderung beschleunigt von 6.3 Sek. auf 4.7 Sek.!!!!
int can_leave_room(const string &puzzle, const vector<int> &room_pos, char room) {
	bool allCorrect = true;
	for (int pos : room_pos) {
		if (puzzle[pos] != '.' && puzzle[pos] != room) {
			allCorrect = false;
			break;
		}
	}
	if (allCorrect) return -1;
	for (int a : room_pos) {
		if (puzzle[a] == '.')
			continue;
		return a;
	}
	return -1;
}

// Check if the path between position a and b is blocked in the hall (not including a and b)
bool blocked(int a, int b, const string &puzzle) {
	int step = (a < b) ? 1 : -1;
	for (int pos = a + step; pos != b + step; pos += step) {
		if (puzzle[pos] != '.')
			return true;
	}
	return false;
}

// Get possible positions in the parking (parc) where the amphipod can move
vector<int> get_possible_parc_pos(int a, const vector<int> &parc, const string &puzzle) {
	vector<int> positions;
	for (int b : parc) {
		if (puzzle[b] == '.') {
			if (blocked(a, b, puzzle))
				continue;
			positions.push_back(b);
		}
	}
	return positions;
}

// Move function: swaps positions a and b in the puzzle state and returns the new state
string move_pos(int a, int b, const string &puzzle) {
	string p = puzzle;
	swap(p[a], p[b]);
	return p;
}

// Check if an amphipod can enter its target room from position a to b
int can_enter_room(int a, int b, char amphi, const string &puzzle, const vector<int> &room_pos) {
	int best_pos = -1;
	for (int pos : room_pos) {
		if (puzzle[pos] == '.')
			best_pos = pos;
		else if (puzzle[pos] != amphi)
			return -1;
	}
	if (best_pos != -1 && !blocked(a, b, puzzle))
		return best_pos;
	return -1;
}

// Compute all possible moves from the current puzzle state.
vector<pair<int, int>> possible_moves(const string &puzzle, const vector<int> &parc,
		const unordered_map<char, int> &stepout,
		const unordered_map<char, vector<int>> &target) {
	vector<pair<int, int>> moves;
	// For parking positions having an amphipod
	for (int a : parc) {
		if (puzzle[a] != '.') {
			char amphi = puzzle[a];
			int b = can_enter_room(a, stepout.at(amphi), amphi, puzzle, target.at(amphi));
			if (b != -1)
				moves.push_back({a, b});
		}
	}
	// For rooms 'A', 'B', 'C', 'D'
	for (char room : string("ABCD")) {
		int a = can_leave_room(puzzle, target.at(room), room);
		if (a == -1)
			continue;
		vector<int> poss = get_possible_parc_pos(stepout.at(room), parc, puzzle);
		for (int b : poss)
			moves.push_back({a, b});
	}
	return moves;
}

// Solve function implementing the search for the solution
int solve(const string &puzzle_input) {
	unordered_map<char, int> energy = { {'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000} };
	vector<int> parc = {0, 1, 3, 5, 7, 9, 10};
	unordered_map<char, int> stepout = { {'A', 2}, {'B', 4}, {'C', 6}, {'D', 8} };
	unordered_map<char, vector<int>> target;
	for (char r : string("ABCD")) {
		int start = int(r) - 54; // ord(r)-54 in Python
		vector<int> positions;
		for (int i = start; i < puzzle_input.size(); i += 4) {
			positions.push_back(i);
		}
		target[r] = positions;
	}
	unordered_map<int, char> targetI;
	for (auto &p : target) {
		char key = p.first;
		for (int v : p.second) {
			targetI[v] = key;
		}
	}
	int repeats = (puzzle_input.size() - 11) / 4;
	string solution(11, '.');
	for (int i = 0; i < repeats; i++) {
		solution.append("ABCD");
	}

	// Min-heap using a priority queue with a custom comparator
	typedef pair<int, string> State;
	auto cmp = [](const State &a, const State &b) {
		return a.first > b.first;
	};
	priority_queue<State, vector<State>, decltype(cmp)> heap(cmp);
	unordered_map<string, int> seen;
	heap.push({0, puzzle_input});
	seen[puzzle_input] = 0;

	while (!heap.empty()) {
		auto [cost, state] = heap.top();
		heap.pop();
		if (state == solution)
			return cost;
		vector<pair<int, int>> moves = possible_moves(state, parc, stepout, target);
		for (auto &mv : moves) {
			int a = mv.first;
			int b = mv.second;
			// Determine the parking and room positions depending on order
			int parking = (a < b) ? a : b;
			int room_pos = (a < b) ? b : a;
			// Calculate the distance of the move: vertical plus horizontal
			int dist_horizontal = abs(stepout.at(targetI.at(room_pos)) - parking);
			int dist_vertical = (room_pos - 7) / 4;
			int distance = dist_horizontal + dist_vertical;
			int new_cost = cost + distance * energy[state[a]];
			string new_state = move_pos(a, b, state);
			if (seen.find(new_state) != seen.end() && new_cost >= seen[new_state])
				continue;
			seen[new_state] = new_cost;
			heap.push({new_cost, new_state});
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	printf("		2021 day23 Part1\n");
#ifdef _ACCOLADE_
	printf("Gravitar64 on reddit + codeconvert.ai\n");
#endif
	int ans1 = solve(read_puzzle(argv[1]));
	printf("**ans: %d\n", ans1);
	return 0;
}

