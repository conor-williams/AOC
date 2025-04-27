#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

map <string, vector <string>> mp;
void traverse(string st, string en, map<string, int> countSmallLetters, vector <string>path, int anySmallTwo);
map <string, int> al;
int count = 0;
int first = 1;
map <string, int> call;
set <string> singleSmalls;

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day 12.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	char line1[LINE];
	// XW-ed
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		char one[20], two[20];
		sscanf(line1, "%[^-]-%[^\0]", one, two);
		string oneS = one; string twoS = two;
		cout << oneS << " " << twoS << endl;
		mp[oneS].push_back(twoS);
		mp[twoS].push_back(oneS);

		leny++;

	}
	fclose(a);

	/*
	for (auto itm = mp.begin(); itm != mp.end(); itm++) {
		cout << "mapFirst: " << itm->first << endl;
		for (auto itv = itm->second.begin(); itv != itm->second.end(); itv++) {
			cout << *itv << " " ;
		}
		cout << endl;
	}
	*/

	count = 0;
	map <string, int> countSmallLetters;
	vector <string> path;
	/*
	for (auto xx = mp.begin(); xx != mp.end(); xx++) {
		if ((int)mp[(*xx).first].size() == 1 && islower((int)(*xx).first[0])
				&& (*xx).first != "start" && (*xx).first != "end") {
			vector <string> veX = mp[(*xx).first];
			string wat = veX.back();
			if (islower(wat[0])) {
				singleSmalls.insert((*xx).first);
			}
		}

	}
	*/

	for (auto itm = mp.begin(); itm != mp.end(); itm++) {
		if ((*itm).first == "start") {
			for (auto itv = itm->second.begin(); itv != itm->second.end(); itv++) {
				traverse((*itv), "end", countSmallLetters, path, 0);
			}
		}
	}

	printf("FIN ** count %d\n", count);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}

int ind = 0;
void traverse(string cur, string en, map<string, int> countSmalls, vector <string> path, int anySmallTwo) {
	ind++;
	if (cur == "start") {
		return;
	}

	if (cur == en) {
		count++;
		for (auto path1: path) {
			cout << path1 << " ";
		}
		cout << endl;
		return;
	}

	if (islower((int)cur[0]) && cur != "start" && cur != en) {
		countSmalls[cur]++;
				
		if (countSmalls[cur] > 2) {return;}
		if (countSmalls[cur] == 2 && anySmallTwo == 1) {return;}
		if (countSmalls[cur] == 2 && anySmallTwo == 0) {anySmallTwo = 1;}

		
		/*
		if (singleSmalls.find(cur) == singleSmalls.end()) {
			if (countSmalls[cur] > 2) {
				return;
			}
		} else {
			if (countSmalls[cur] > 1) {
				return;
			}
		}
		*/
	}
	
	path.push_back(cur);
	vector <string> ve = mp[cur];
	for (auto itv = ve.begin(); itv != ve.end(); itv++) {
		traverse(*itv, en, countSmalls, path, anySmallTwo);
	}
	ind--;
}
