#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <assert.h>

#include <unistd.h>

#define getchar()
#include <unistd.h>

using namespace std;
#define _DEBUG_
vector <int> ve2[30];
vector <int> veOrig[30];
int isfreeatback(int pint);
int alreadyProcessed(int c);
void freeup(int pint);
int workers[6]; 
int NUMW = 5;
int time[6] = {0};
int TIME = 60;
int allqfree();
vector <int> already;
vector <int> pas;
int main(int argc, char **argv)
{
	if (argc >= 3) {NUMW = atoi(argv[2]);}
	if (argc >= 4) {TIME = atoi(argv[3]);}
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day7.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int SIZE = 1000; char line1[SIZE];

	//Step J must be finished before step H can begin.
	int leny = 0;

	while (1)
	{
		fgets(line1, SIZE, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		char F, T;
		sscanf(line1, "Step %c must be finished before step %c can begin.", &F, &T);
		ve2[T-65].push_back(F-65);
		leny++;
	}

	for (int i = 0; i < 26; i++) {
		veOrig[i] = ve2[i];
	}
	vector <int> ans;
ag: //one letter at a time - lowest letter first - a topological sort
	for (int i = 0; i < 26; i++) {
		if ((int)ve2[i].size() == 0 && find(pas.begin(), pas.end(), i) == pas.end()) {
			if (find(ans.begin(), ans.end(), i) == ans.end()) {ans.push_back(i);}
		}
	}

	sort(ans.begin(), ans.end());
	int found = 0;
	auto first = ans.begin();
	int onelet = *first;
	ans.erase(first);
	{
		printf("for removal: %c ", onelet+65);
		pas.push_back(onelet);
		for (int i = 0; i < 26; i++) {
			vector <int>::iterator it;
			if ((it = find(ve2[i].begin(), ve2[i].end(), onelet)) == ve2[i].end()) {
				//ok
			} else {
				if (found == 0) {found = 1;}
				printf("in %c -- was looking %c - removing %c\n", i+65, onelet+65, (*it)+65);
				ve2[i].erase(it);
			}
		}
	}
	printf("pas now: "); for (auto ii: pas) { printf("%c", ii+65);} printf("\n");
	if (found == 1) {
		goto ag;
	}
////////////////////////////P2...

	for (int i = 0; i < 26; i++) {
		ve2[i] = veOrig[i];
	}


	int ti = 0;
	for (int i = 0; i < NUMW; i++){workers[i] = 100;}
	do {
		for (int i = 0; i < NUMW; i++) {
			if (time[i] != 0) {
				time[i]--;
				if (time[i] == 0) {
					printf("freeup Q %d\n", i);
					if (workers[i] != 100) {
						freeup(workers[i]);
						workers[i] = 100;
					}
				}
			}
		}
		for (int bb = 0; bb < (int)pas.size(); bb++) {
			if (isfreeatback(pas[bb]) == 0 && alreadyProcessed (pas[bb]) == 0) {
				printf("%c now free\n", pas[bb]+65);
				for (int jj=0;jj<NUMW;jj++) {
					if (workers[jj] == 100) {
						 //put that onto free worker
						printf("put onto Q %d (pas[bb] %c)\n", jj, pas[bb]+65); getchar();
						if (find(already.begin(), already.end(), pas[bb]) == already.end()) {
							already.push_back(pas[bb]);
						} else {
							printf("ERR"); exit(0);
						}
						workers[jj] = pas[bb];

						time[jj] = TIME+1+pas[bb];
						printf("incr of ppos\n");
						goto ne;
					}
				}
			}
ne:			
			continue;
			//if (f1 == 0) {printf("no Q free for %c\n", pas[ppos]+65);}
		}
		if (allqfree()==1) { break; }

		printf("ti: %d\n", ti);
		ti++;
	} while (1);
	printf("ti is %d\n", ti);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", ti);
}
int alreadyProcessed(int c) {
	for (int i = 0; i < (int)already.size(); i++) {
		if (c == already[i]) {
			return 1;
		}
	}
	return 0;
}
int allqfree() {
	int f2 = 1;
	for (int i = 0; i < NUMW; i++) {
		if (workers[i] == 100 && time[i] == 0) {
		} else {
			f2 = 0; break;
		}
	}
	return f2;
}
void freeup(int pint) {
	for (int i = 0; i < 26; i++) {
		vector <int>::iterator it;
		if ((it = find(ve2[i].begin(), ve2[i].end(), pint)) == ve2[i].end()) {
			//ok
		} else {
			//if (found == 0) {found = 1;}
			ve2[i].erase(it);
		}
	}
}

int isfreeatback(int pint) {
	if (ve2[pint].size() == 0) {
		return 0;
	}
	return 1;
}
