//thanks to maikka39 @ reddit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

map <string, char> mp;
deque <char> polymerOrig;
deque <char> polymerTo;

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);

	a = fopen(argv[1], "r"); printf("		2021 Day 14 Part 2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			continue;
		} else if (leny == 0) {
			//polymer = line1;
			for (int i = 0; i < (int)strlen(line1); i++) {
				polymerOrig.push_back(line1[i]);
			}
		} else {
			char from[10]; char to;
			sscanf(line1, "%s -> %c", from, &to);
			string Sfrom = from;
			mp[from] = to;
		}
		leny++;
	}
	fclose(a);

	map<string, long long> pairs;
	map<char, long long> singles;
	for (int i = 0; i < (int)polymerOrig.size()-1; i++) {
		string pair_key;
		pair_key.push_back(polymerOrig[i]);
		pair_key.push_back(polymerOrig[i+1]);
		pairs[pair_key]++;
		singles[polymerOrig[i]]++;
	}
	singles[polymerOrig.back()]++;
	for (int iter = 0; iter < 40; iter++) {
		vector <pair<string, long long>> currentPairs;
		for (auto onePair: pairs) {
			currentPairs.push_back(onePair);
		}
		for (auto onePair: currentPairs) {
			string comb = onePair.first;
			long long count = onePair.second;
			char new_elem;
			new_elem = mp[comb];
			singles[new_elem] += count;
			pairs[comb] -= count;
			string newPair1;
			newPair1.push_back(comb[0]);
			newPair1.push_back(new_elem);
			pairs[newPair1] += count;
			string newPair2;
			newPair2.push_back(new_elem);
			newPair2.push_back(comb[1]);
			pairs[newPair2] += count;
		}
	}

	long long minCount = numeric_limits<long long>::max();
	long long maxCount = 0;

	for (auto onePair: singles) {
		if (onePair.second > maxCount) {
			maxCount = onePair.second;
		} 
		if (onePair.second < minCount) {
			minCount = onePair.second;
		}
	}
	long long ans1 = maxCount - minCount;
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", ans1);
}
