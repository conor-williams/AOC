#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;


FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
struct sums_s {
	string r1;
	string r2;
	string r3;
	char type;
	int complete;
};
struct sums_s sums[400];
map<string, int> mp;
int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 24 Part 1\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	int go = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			go = 1;
			leny=0;
			continue;
		} else if (go == 1) {
			char r1[10], r2[10], r3[10];
			char type[10];
			sscanf(line1, "%s %s %s -> %s", r1, type, r2, r3);
			sums[leny].r1 = r1;
			sums[leny].r2 = r2;
			sums[leny].r3 = r3;
			if (strcmp(type, "XOR") == 0) {sums[leny].type = '^';}
			else if (strcmp(type, "OR") == 0) {sums[leny].type = '|';}
			else if (strcmp(type, "AND") == 0) {sums[leny].type = '&';}
			sums[leny].complete = 0;
		} else if (go == 0) {
			char regname[10]; int regval;
			sscanf(line1, "%[^:]: %d\n", regname, &regval);
			mp[regname] = regval;
		}
		leny++;
	}
	fclose(a);

restart:
	for (int i = 0; i < leny; i++) {
		printf("here1 i is %d\n", i);
		if (sums[i].complete != 1) { 
			if (mp.find(sums[i].r1) == mp.end() || mp.find(sums[i].r2) == mp.end()) {	
				printf("not ready...\n");
				//not ready
			} else {
				switch (sums[i].type) {
					case '^':
						mp[sums[i].r3] = mp[sums[i].r1] ^ mp[sums[i].r2]; 
						printf("bitwise xor %s -> %d", sums[i].r3.c_str(), mp[sums[i].r3]);
						break;
					case '|':
						mp[sums[i].r3] = mp[sums[i].r1] | mp[sums[i].r2]; 
						printf("bitwise | %s -> %d", sums[i].r3.c_str(), mp[sums[i].r3]);
						break;
					case '&':
						mp[sums[i].r3] = mp[sums[i].r1] & mp[sums[i].r2]; 
						printf("bitwise & %s -> %d", sums[i].r3.c_str(), mp[sums[i].r3]);
						break;
				}
				sums[i].complete = 1;
				goto restart;
			}
		} else {
			continue;
		}
	}
	for (int i = 0; i < leny; i++) {
		if (sums[i].complete != 1) {
			goto restart;
		}
	}

	vector <int> ve;
	for (auto it = mp.begin(); it!=mp.end();it++) {
		string regg = (*it).first;
		if (regg[0] == 'z') {
			printf("%s: %d\n", regg.c_str(), (*it).second);
			ve.push_back((*it).second);
		} else {
			printf("%s\n", regg.c_str());
		}
	}
	cout << endl;
	string deci;
	for (auto it2 = ve.rbegin(); it2 != ve.rend(); it2++) {
		deci += to_string(*it2);
		cout << *it2;
	}
	
	char *bla;
	unsigned long long conved = strtoull(deci.c_str(), &bla, 2);

	cout << deci << endl;
	cout << "Ans: [ ";
	cout << conved;
	cout << " ] " << endl;
}
