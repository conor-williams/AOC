#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <deque>
#include <map>
#include <set>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
int var_len = 0;
void sigfunc(int a) { printf("[[ %d ]]\n", var_len); }
int lenx;
int leny;
deque <string> de;
//set <string> se;
int TIMES = 75;
int INCR = 75;

struct ans_s {
	//unsigned long long length;
	map <string, unsigned long long> mpi;
};
void doit(string inp, int ti, int LEVEL, unsigned long long mul);

map <pair<string, int>, struct ans_s> mp; 
map <string, pair<string, string>> done1;
unsigned long long ANS = 0;
int main(int argc, char **argv)
{

	signal(SIGQUIT, &sigfunc);
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	if (argc >= 3) {TIMES = atoi(argv[2]);} 
	if (argc == 4) {INCR = atoi(argv[3]);} 

	a = fopen(argv[1], "r"); printf("		2024 Day 11 Part 2\n"); fflush(stdout);
	
	fflush(stdout); int fd = dup(1); close(1);
	//int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1); fflush(stdout);

		char *fir = strtok(line1, " \0");
		do {
			de.push_back(fir);
			printf("pushing %s\n", fir);
		} while ((fir = strtok(NULL, " \0")) != NULL);
		leny++;
	}
	fclose(a);

	ANS = 0;
	for (auto it = de.begin(); it != de.end(); it++) {
		printf("doing %s\n", (*it).c_str());
		doit(*it, INCR, INCR, 1);
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", ANS);

}

void doit(string inp, int TI, int level, unsigned long long mul) {
	set <string> se;
	set <string> de2;
	map <string, unsigned long long> prevMap;
	map <string, unsigned long long> mainMap;
	mainMap[inp] = 1;
	if (mp.find({inp, TI}) == mp.end()) {
		de2.insert(inp);
		set <string> deAns;
		for (int times = 0; times < TI; times++) {
			prevMap = mainMap;
			mainMap.clear();
			for (auto it = de2.begin(); it != de2.end(); it++) {
				string bla = *it;
				if (done1.find(bla) == done1.end()) {
					if (bla == "0") {
						deAns.insert("1");
						done1[bla] = make_pair("1", "");
						mainMap["1"]+=prevMap[bla];
						continue;
					}
					int len = bla.length();
					if (len % 2 == 0) {
						char *rem1;
						string split1 = to_string(strtoull((bla).substr(0, len/2).c_str(), &rem1, 10));
						char *rem2;
						string split2 = to_string(strtoull((bla).substr(len/2, len/2).c_str(), &rem2, 10));
						deAns.insert(split1);
						deAns.insert(split2);
						mainMap[split1]+=prevMap[bla];
						mainMap[split2]+=prevMap[bla];

						done1[bla] = make_pair(split1, split2);
					} else {
						char *rem;
						string b1 = to_string(strtoull((bla).c_str(), &rem, 10) * 2024);
						deAns.insert(b1);
						done1[bla] = make_pair(b1, "");
						mainMap[b1]+=prevMap[bla];
					}
				}  else {
					pair p1 = done1[bla];
					deAns.insert(p1.first);
					mainMap[p1.first] += prevMap[bla];
					if (p1.second != "") {
						deAns.insert(p1.second);
						mainMap[p1.second] += prevMap[bla];
					}
				}
			}

			de2 = deAns;
			deAns.clear();
		}
		for (auto it = de2.begin(); it != de2.end(); it++) {
			mp[{inp, TI}].mpi[(*it)] = mainMap[*it];
			if (se.find(*it) == se.end()) {se.insert(*it);}
		}
	} else {
		de2.clear();
		for (auto it2 = mp[{inp, TI}].mpi.begin(); it2 != mp[{inp, TI}].mpi.end(); it2++) {
			if (se.find((*it2).first) == se.end()) {se.insert((*it2).first);}
			//se.insert((*it2).first);
		}
	}
	if (level == TIMES) {
		for (auto it = se.begin(); it != se.end(); it++) {
			ANS += mul*mp[{inp, TI}].mpi[*it];
		}
		return;
	}
	for (auto it = se.begin(); it != se.end(); it++) {
		doit(*it, INCR, level+INCR, mul*mp[{inp, TI}].mpi[*it]);
	}

}


//printf("times: %d:\n", times); for (auto elem: de) { printf(" %s ", elem.c_str()); } printf("\n");
//mp[{inp, TI}].length = (int)de2.size();
/*if ((*it2).second == 1) {
  de2.push_back((*it2).first);
  } else {
  for (unsigned long long i = 0; i < (*it2).second; i++ ) {
  de2.push_back((*it2).first);
  }
  }
 */
//var_len = de2.size();
