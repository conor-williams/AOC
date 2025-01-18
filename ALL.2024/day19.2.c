#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <regex>
#include <map>


#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;
FILE *a;
#define LINE 3500
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
deque <string> from;
deque <string> fromf;
deque <string> to;
deque <string> tof;
map <pair<string, int>, unsigned long long> mp;

unsigned long long gCount = 0;
int loop(string sto1, int pos, int *countLocal);
unsigned long long loop2(string sto1, int pos);
set <char> se;
int main(int argc, char **argv)
{
	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 19 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);

		if (line1[0] == '\0') {goto next;}
		if (line1[0] == 'Q') {/*debug*/break;}
		if (leny == 0) {
			char *fir = strtok(line1, " ,\0");
			do {
				string f1 = fir;
				reverse(f1.begin(), f1.end());
				from.push_back(f1);
				fromf.push_back(fir);
			} while ((fir = strtok(NULL, " ,\0")) != NULL);
		} else {
			string f2 = line1;
			reverse(f2.begin(), f2.end());
			to.push_back(f2);
			tof.push_back(line1);
			for (int i = 0; i < (int)strlen(line1); i++)  {
				se.insert(line1[i]);
			}
		}
next:
		leny++;
	}
	fclose(a);

	sort(from.begin(), from.end());

	int zzz = 0;
	unsigned long long count = 0;
	for (auto sto1: to) {
		//cout << zzz << ": " << sto1 << endl;
		int countLocal = 0;
		loop(sto1, 0, &countLocal);
		if (countLocal != 0) {
			gCount = 0;
			mp.clear();
			loop2(sto1, 0);
			count+= gCount;
		}
		zzz++;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", count);

}

int level = 0;
unsigned long long loop2(string sto1, int pos)
{
	level++;
	if (pos >= (int)sto1.length()) {
		level--; 
		//for (int zz = 0; zz < level; zz++) {printf("	");} cout << "returning 22" << endl;
		gCount++;
		return 0;
	}
	for (auto sfrm1: from) {
		//for (int zz = 0; zz < level; zz++) {printf("	");} cout << sfrm1 << endl;
		int len = sfrm1.length();
		int retVal = sto1.compare(pos, len, sfrm1);
		if (retVal == 0) {
			if (mp.find({sfrm1, pos}) == mp.end()) {
				unsigned long long atmp = gCount;
				loop2(sto1, pos+len);
				mp[{sfrm1, pos}] = gCount - atmp;
			} else {
				//printf("using map plus %llu\n", mp[{sfrm1, pos}]);
				gCount += mp[{sfrm1, pos}];
			}
			continue;
		} else if (retVal < 0) {
			level--;
			return 0;
		} else { //greater
			continue;
		}
	}
	level--;
	return 0;
}
int level1 = 0;
int loop(string sto1, int pos, int *countLocal) {
	level1++;
	if (pos >= (int)sto1.length()) {
		level1--; 
		//for (int zz = 0; zz < level1; zz++) {printf("	");} cout << "returning 22" << endl;
		 (*countLocal)++;return 22;
	}
	for (auto sfrm1: from) {
		//for (int zz = 0; zz < level1; zz++) {printf("	");} cout << sfrm1 << endl;
		int len = sfrm1.length();
		int retVal = sto1.compare(pos, len, sfrm1);
		//string subto1 = sto1.substr(pos, len); int retVal = strcmp(subto1.c_str(), sfrm1.c_str());	
		if (retVal == 0) {
			//for (int zz = 0; zz < level1; zz++) {printf("	");}
			//printf("equal %s V %s\n", subto1.c_str(), sfrm1.c_str());
			int loopRet = 0;
			loopRet = loop(sto1, pos+len, countLocal);
			if (loopRet == 22) {level1--; return 22;}
		} else if (retVal < 0) {
			//for (int zz = 0; zz < level1; zz++) {printf("	");}
			//printf("less %s V %s\n", subto1.c_str(), sfrm1.c_str());
			level1--;
			return 99;
		} else { //greater
			//for (int zz = 0; zz < level1; zz++) {printf("	");}
			//printf("greater %s V %s\n", subto1.c_str(), sfrm1.c_str());
			continue;
		}
	}
	level1--;
	return 100;
}
//if (mp.find({sto1, p1}) == mp.end()) { mp[{sto1, p1}]++;}
//string subto1 = sto1.substr(pos, len); int retVal = strcmp(subto1.c_str(), sfrm1.c_str());	
//for (int zz = 0; zz < level; zz++) {printf("	");} //printf("less %s V %s\n", subto1.c_str(), sfrm1.c_str());
//for (int zz = 0; zz < level; zz++) {printf("	");} //printf("greater %s V %s\n", subto1.c_str(), sfrm1.c_str());
//if (loopRet == 22) {level--; return 22;}
//for (int zz = 0; zz < level; zz++) {printf("	");} //printf("equal %s V %s\n", subto1.c_str(), sfrm1.c_str());
