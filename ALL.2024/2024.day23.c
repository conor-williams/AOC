#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <time.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
map <pair<string, string>, int> mp;
map <string, int> mpOne;
int main(int argc, char **argv)
{
        clock_t start, end; double cpu_time_used;
        start = clock();
        //DO
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        ///printf("        time: %f seconds\n", cpu_time_used);

        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 23 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	char fir[10], sec[10];
	sscanf(line1, "%[^-]-%s", fir, sec);
	printf(" %s --- %s\n", fir, sec);
	mp[{fir, sec}] = 1;
	mp[{sec, fir}] = 1;
	mpOne[{fir}]++;
	mpOne[{sec}]++;
	leny++;
}
fclose(a);

	int count = 0;
        start = clock();
        //DO
	printf("Main Loop:\n");
	for (auto it1 = mpOne.begin(); it1 != mpOne.end(); it1++) {
		string st1 = (*it1).first;
		for (auto it2 = it1/*mpOne.begin()*/; it2 != mpOne.end(); it2++) {
			if (it1 == it2) {continue;}
			string st2 = (*it2).first;
			if (mp.find({st1, st2}) != mp.end()) {
				for (auto it3 = it2/*mpOne.begin()*/; it3 != mpOne.end(); it3++) {
					if (it1 == it3) {continue;} if (it2 == it3) {continue;}
					string st3 = (*it3).first;
					if (mp.find({st1, st3}) != mp.end() && mp.find({st2, st3}) != mp.end()) {
						if (st1[0] == 't' || st2[0] == 't' || st3[0] == 't') {
							count++;
#ifdef _DEBUG_
							printf("%s %s %s\n", st1.c_str(), st2.c_str(), st3.c_str()); 
#endif
						}
					}
				}
			}
		}
	}
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);


	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", count);
}
