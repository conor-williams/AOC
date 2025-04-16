//thanks for the python code: danielgaylord aka cloud08540 + codeconvert.ai...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <deque>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;
struct State {
	int p1_score;
	int p2_score;
	int p1_place;
	int p2_place;
	bool p1_turn;

	bool operator==(const State &other) const {
		return tie(p1_score, p2_score, p1_place, p2_place, p1_turn) ==
			tie(other.p1_score, other.p2_score, other.p1_place, other.p2_place, other.p1_turn);
	}
};

struct StateHash {
	size_t operator()(const State &s) const {
		size_t h1 = hash<int>()(s.p1_score);
		size_t h2 = hash<int>()(s.p2_score);
		size_t h3 = hash<int>()(s.p1_place);
		size_t h4 = hash<int>()(s.p2_place);
		size_t h5 = hash<bool>()(s.p1_turn);
		// Combine the hash values
		size_t  hash = h1; hash *= 37; hash += h2; hash *= 37; hash += h3; hash *= 37; hash += h4; hash *= 37; hash += h5; return hash;
		//return (((h1 ^ (h2 << 1)) >> 1) ^ (h3 << 1)) ^ (h4 << 1) ^ h5;
	}
};


FILE *a;
#define LINE 1000
unordered_map<State, pair<long long, long long>, StateHash> cache;

int startP1; int startP2;
pair <long long, long long> take_turn(
		int scoreP1, int scoreP2, int posP1, int posP2, bool turnP1);

int ar[10] = {0};
int main(int argc, char **argv)
{
	a = fopen(argv[1], "r"); printf("		2021 Day 21 Part2\n"); fflush(stdout);
	char line1[LINE];

	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		sscanf(line1, "Player 1 starting position: %d", &startP1);
		sscanf(line1, "Player 2 starting position: %d", &startP2);
		leny++;
	}
	fclose(a);

	/*
	for (int ii = 1; ii <= 3; ii++) { //dice1
		for (int ji = 1; ji <= 3; ji++) { //dice2
			for (int ki = 1; ki <= 3; ki++) { //dice3
				int totPoss = (ii+ji+ki);
				ar[totPoss-3]++;
			}
		}
	}
	*/

	//printf("winsP1 is %llu\n", winsP1);
	//printf("winsP2 is %llu\n", winsP2);
	auto pa = take_turn(0, 0, startP1, startP2, true);
	auto result = pa.first > pa.second? pa.first: pa.second;
	printf("**ans: %llu\n", result);

}

pair <long long, long long> take_turn(
		int scoreP1, int scoreP2, int posP1, int posP2, bool turnP1) {
	if (scoreP1 >= 21) {
		return {1, 0};
	} else if (scoreP2 >= 21) {
		return {0, 1};
	}
	State current {scoreP1, scoreP2, posP1, posP2, turnP1};
	if (cache.find(current) != cache.end()) {
		return cache[current];
	}

	long long totP1 = 0;
	long long totP2 = 0;

	//for (int ii = 0; ii < 7; ii++) 
	for (int roll1 = 1; roll1 <= 3; ++roll1) {
		for (int roll2 = 1; roll2 <= 3; ++roll2) {
			for (int roll3 = 1; roll3 <= 3; ++roll3) {
				int ii = roll1 + roll2 + roll3;
				if (turnP1) {
					int amt = ii;
					int newposP1 = ((posP1 - 1 + amt) % 10) + 1;
					int newScoreP1 = scoreP1 + newposP1;
					auto res = take_turn(newScoreP1, scoreP2, newposP1, posP2, !turnP1);
					totP1 += res.first;
					totP2 += res.second;
				} else {
					int amt = ii;
					int newposP2 = ((posP2 - 1 + amt) % 10) + 1;
					int newScoreP2 = scoreP2 + newposP2;
					auto res = take_turn(scoreP1, newScoreP2, posP1, newposP2, !turnP1);
					totP1 += res.first;
					totP2 += res.second;
				}
			}
		}
	}
		
	cache[current] = make_pair(totP1, totP2);
	return cache[current];
}
