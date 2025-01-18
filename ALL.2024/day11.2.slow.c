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

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
int var_len = 0;
void sigfunc(int a) { printf("[[ %d ]]\n", var_len); }
int lenx;
int leny;
deque <string> de;
int TIMES = 25;

struct ans_s {
	unsigned long long length;
	map <string, unsigned long long> mpi;
};
void doit(string inp, int ti);

map <pair<string, int>, struct ans_s> mp; 
int main(int argc, char **argv)
{

	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	if (argc == 3) {TIMES = atoi(argv[2]);} 

	a = fopen(argv[1], "r"); printf("2024 Day 11 Part 2\n"); fflush(stdout);
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

	for (auto it = de.begin(); it != de.end(); it++) {
		cout << "looking at: " << *it << endl;
		if (mp.find({(*it), 25}) == mp.end()) {
			doit(*it, 25);
		}
		for (auto it2 = mp[{*it, 25}].mpi.begin(); it2 != mp[{*it, 25}].mpi.end(); it2++) {
			if (mp.find({(*it2).first, 25}) == mp.end()) {
				doit((*it2).first, 25);
			}
			for (auto it3 = mp[{(*it2).first, 25}].mpi.begin(); it3 != mp[{(*it2).first, 25}].mpi.end(); it3++) {
				if (mp.find({(*it3).first, 25}) == mp.end()) {
					doit((*it3).first, 25);
				}
			}
		}
	}
	printf("after calc...\n"); fflush(stdout);
	unsigned long long ans = 0;

	for (auto it = de.begin(); it != de.end(); it++) {
		for (auto it2 = mp[{*it, 25}].mpi.begin(); it2 != mp[{*it, 25}].mpi.end(); it2++) {
			unsigned long long mul2 = (*it2).second;
			for (auto it3 = mp[{(*it2).first, 25}].mpi.begin(); it3 != mp[{(*it2).first, 25}].mpi.end(); it3++) {
				unsigned long long mul3 = (*it3).second;
				for (auto it4 = mp[{(*it3).first, 25}].mpi.begin(); it4 != mp[{(*it3).first, 25}].mpi.end(); it4++) {
					ans += mul2 * mul3 * (*it4).second; 
				}
			
/*
				unsigned long long mul3 = (*it3).second;
				for (auto it4 = mp[{(*it3).first, 7}].mpi.begin(); it4 != mp[{(*it3).first, 7}].mpi.end(); it4++) {
					ans += mul2 * mul3 * (*it4).second;
				}
*/
			}
		}
	}
/*
	for (auto it = de.begin(); it != de.end(); it++) {
		for (auto it2 = mp[{*it, 11}].mpi.begin(); it2 != mp[{*it, 11}].mpi.end(); it2++) {
			unsigned long long mul2 = (*it2).second;
			for (auto it3 = mp[{(*it2).first, 7}].mpi.begin(); it3 != mp[{(*it2).first, 7}].mpi.end(); it3++) {
				unsigned long long mul3 = (*it3).second;
				for (auto it4 = mp[{(*it3).first, 7}].mpi.begin(); it4 != mp[{(*it3).first, 7}].mpi.end(); it4++) {
					ans += mul2 * mul3 * (*it4).second;
				}
			}
		}
	}
*/
/*
	for (auto it = de.begin(); it != de.end(); it++) {
		printf("do25 %s\n", (*it).c_str()); fflush(stdout);
		do25(*it);
		for (auto it2 = mp[{*it, 25}].mpi.begin(); it2 != mp[{*it, 25}].mpi.end(); it2++) {
			if (mp.find({(*it2).first, 25}) == mp.end()) {
				do25((*it2).first); 
			}
			for (auto it3 = mp[{(*it2).first, 25}].mpi.begin(); it3 != mp[{(*it2).first, 25}].mpi.end(); it3++) {
				if (mp.find({(*it3).first, 25}) == mp.end()) {
					do25((*it3).first);
				}
			}
		}

		
	}
	unsigned long long ans = 0;
	for (auto it = de.begin(); it != de.end(); it++) {
		ans += mp[{*it, 25}].length;
		//for (auto it2 = mp[{*it, 25].mpi.begin(); it2 != mp[{*it, 25}].mpi.end; it2++) 
	}
	printf("calc ans %llu (JUST 25 ignore..)\n", ans); getchar();

	//unsigned long long ans = 0;
	ans = 0;
	for (auto it = de.begin(); it != de.end(); it++) {
		printf("calc %s\n", (*it).c_str()); fflush(stdout);
		//unsigned long long mul1 = mp[{*it, 25}].length;
		//printf("mul1 %llu\n", mul1); getchar();
		unsigned long long alllens2 = 0;
		for (auto it2 = mp[{*it, 25}].mpi.begin(); it2 != mp[{*it, 25}].mpi.end(); it2++) {
			unsigned long long mul2 = (*it2).second;                    //mp[{(*it2).first, 25}].length;
			//printf("mul2 %llu\n", mul2);
			unsigned long long alllens3 = 0;
			for (auto it3 = mp[{(*it2).first, 25}].mpi.begin(); it3 != mp[{(*it2).first, 25}].mpi.end(); it3++) {
				//printf("len it3: %llu\n", mp[{(*it3).first, 25}].length);
				//unsigned long long mul3 = (*it3).second;
				alllens3 += mp[{(*it3).first, 25}].length  * mul2;
			}
			alllens2 += alllens3;
		}
		ans += alllens2;// * mul1;
	}
*/

	//fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", ans);
}

void doit(string inp, int TI) {
	deque <string> de2;
	de2.push_back(inp);
	deque <string> deAns;
	for (int times = 0; times < TI; times++) {
		for (auto it = de2.begin(); it != de2.end(); it++) {
			string bla = *it;
			int len = (*it).length();
			if (bla == "0") {
				deAns.push_back("1");
			} else if (len % 2 == 0) {
				char *rem1;
				string split1 = to_string(strtoull((*it).substr(0, len/2).c_str(), &rem1, 10));
				char *rem2;
				string split2 = to_string(strtoull((*it).substr(len/2, len/2).c_str(), &rem2, 10));
				deAns.push_back(split1);
				deAns.push_back(split2);
			} else {
				char *rem;
				string b1 = to_string(strtoull((*it).c_str(), &rem, 10) * 2024);
				deAns.push_back(b1);
			}
		}

		de2 = deAns;
		var_len = de2.size();
		deAns.clear();
		//printf("times: %d:\n", times); for (auto elem: de) { printf(" %s ", elem.c_str()); } printf("\n");
	}
	mp[{inp, TI}].length = (int)de2.size();

	for (auto it = de2.begin(); it != de2.end(); it++) {
		if (mp.find({inp, TI}) == mp.end()) {
			mp[{inp, TI}].mpi[(*it)] = 1;
		} else {
			mp[{inp, TI}].mpi[(*it)]++;
		}
	}
}

//char *bl1; mp[{inp, TI}].mpi[strtoull((*it).c_str(), &bl1, 10)]++;

