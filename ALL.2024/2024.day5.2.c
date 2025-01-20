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

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

struct pairs_s {
	int fir;
	int sec;
};
struct pairs_s pairs[1200];

char groups[1000][1000];

vector <int> vec[1000];
vector <int> badVec;
map <pair<int, int>, int> mp;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 5 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

int leny = 0;
int gr = 0;
int grPos = 0;
int pairsNum = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	if (line1[0] == '\0') {
		gr = 1;
		continue;
	}
	if (gr == 0) {
		int fir, sec;
		int ret = sscanf(line1, "%d|%d", &fir, &sec);
		if (ret == 2) {mp[{fir, sec}] = 1;} else {printf("ERR"); exit(0);}
		pairsNum++;
	} else {
		if (gr == 1) {
			char *fir = strtok(line1, ",\0");
			do {
				vec[grPos].push_back(atoi(fir));
			} while ((fir = strtok(NULL, ",\0")) != NULL);
			grPos++;
		}
	}
	leny++;
}
fclose(a);
	
	unsigned long long tot = 0;
	for (int i = 0; i < grPos; i++) {
		int sz  = vec[i].size();
		int bad = 0;
		for (int f1 = 0; f1 < sz-1; f1++) {
			for (int s1 = f1+1; s1 < sz; s1++) {
				if (mp[{vec[i].at(f1), vec[i].at(s1)}] == 1) {
					//ok
				} else {
					bad = 1;
					goto nextGroup;
				}
			}
		}
		if (bad == 0) {
			tot += vec[i].at(sz/2);
		}
nextGroup:
		if (bad == 1) {
			badVec.push_back(i);
		}
		continue;
	}
	
	int szBad = badVec.size();
	printf("num bad: %d\n", szBad);
	tot = 0;
	for (int i = 0; i < szBad; i++) {
		int pp = badVec.at(i);
		int sz = vec[pp].size();
again:
		int bad = 0;

		for (int f1 = 0; f1 < sz-1; f1++) {
			for (int s1 = f1+1; s1 < sz; s1++) {
				if (mp[{vec[pp].at(f1), vec[pp].at(s1)}] == 1) {
					//ok
				} else {
					bad = 1;
					int tmp = vec[pp][f1];
					vec[pp][f1] = vec[pp][s1];
					vec[pp][s1] = tmp;
					printf("goto again... swap pos %d (%d)with pos %d (%d)\n", f1, vec[pp][f1], s1, vec[pp][s1]);
					goto again;
				}
			}
		}
		if (bad == 0) {tot += vec[pp].at(sz/2);}
		
	}

	fflush(stdout); dup2(fd, 1);
			
	printf("**ans %llu\n", tot);
		
}
