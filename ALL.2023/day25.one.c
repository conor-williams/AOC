#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <unistd.h>
//#define assert(asf)
#define getchar()
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;


struct hash_function
{
size_t operator()(const tuple<int , int , int, int>&x) const
{
unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
}
};

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); if (a == NULL) {printf("BAD file %s\n", argv[1]); exit(0);}
	//printf("2024 Day 1 Part 1\n"); fflush(stdout);

	//fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	map <string, vector<string>> mp;
	char fir1[20];
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		char * fir = strtok(line1, ":");
		strcpy(fir1, fir);
		fir = strtok(NULL, ":");
		char *sec = strtok(fir, " \0");
		vector <string> ve;
		do {
			ve.push_back(sec);	
		} while ((sec = strtok(NULL, " \0")) != NULL);
		mp[fir1] = ve;
		leny++;
	}
	fclose(a);
	/*
	for (auto it = mp.begin(); it!= mp.end(); it++) {
		vector <string> ve2 = (*it).second;	
		for (auto it2 = ve2.begin(); it2!= ve2.end(); it2++) {
			auto ve3 = mp[*it2];
			if (find(ve3.begin(), ve3.end()) != ve3.end()) {
				ve3.push_back((*it).first);
			}
			mp[*it2] = ve3;
		}

	}
	*/
	for (auto it = mp.begin(); it!= mp.end(); it++) {
		vector <string> ve2 = (*it).second;	
		for (auto it2 = ve2.begin(); it2!= ve2.end(); it2++) {
			printf("%s %s\n", (*it).first.c_str(), (*it2).c_str());
		}
	}	
		
	//fflush(stdout); dup2(fd, 1);
}
