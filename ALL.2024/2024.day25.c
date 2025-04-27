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

char grid[20][20];
vector <vector <int>> veKey;
vector <vector <int>> veLock;
void getVecFromGrid(char grid[20][20], int pos);
int checkWillFit(vector <int> lo, vector <int> ke);
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
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2024 Day 25 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	int pos = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			getVecFromGrid(grid, pos);
			pos = 0;
			continue;

		} else {
			strcpy(grid[pos], line1);
			printf("grid[pos] is %s\n", grid[pos]);
			pos++;
		}
		leny++;
	}
	fclose(a);
	getVecFromGrid(grid, pos);
	printf("Locks:\n");
	for (auto it = veLock.begin(); it != veLock.end(); it++) {
		vector <int> veTmp = (*it);

		for (auto it2 = veTmp.begin(); it2 != veTmp.end(); it2++) {
			cout << (*it2) << " ";
		}
		cout << endl;
	}

	printf("Keys:\n");
	for (auto it = veKey.begin(); it != veKey.end(); it++) {
		vector <int> veTmp = (*it);

		for (auto it2 = veTmp.begin(); it2 != veTmp.end(); it2++) {
			cout << (*it2) << " ";
		}
		cout << endl;
	}


	int count = 0;
	for (auto itL = veLock.begin(); itL != veLock.end(); itL++) {
		for (auto itK = veKey.begin(); itK != veKey.end(); itK++) {
			if (checkWillFit((*itL), (*itK)) == 1) {
				count++;
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", count);
}
int checkWillFit(vector <int> lo, vector <int> ke) {
	int found = 0;
	for (int i = 0; i < (int)lo.size(); i++) {
		if (lo[i] + ke[i] <= 5) {
			//ok
		} else {
			found = 1;
			break;
		}
	}
	if (found == 0) {return 1;}
	return 0;
}

void getVecFromGrid(char grid[20][20], int pos) {
			int xend = (int)strlen(grid[0]);
			assert(xend == 5);
			printf("xend is %d\n", xend); fflush(stdout);
			int res[6];
			if (strcmp(grid[0], "#####") == 0) {//lock
				vector <int> veTmp;
				printf("found lock"); fflush(stdout);
				for (int x = 0; x < xend; x++) {
					for (int y = 1; y < pos; y++) {
						if (grid[y][x] == '.') {
							printf("found .\n"); fflush(stdout);
							res[x] = y-1;
							//veLock[lockNum].push_back(res[x]);
							veTmp.push_back(res[x]);
							printf("breaking\n"); fflush(stdout);
							break;
						}
					}
				}
				veLock.push_back(veTmp);
			} else if (strcmp(grid[0], ".....") == 0) {//key
				vector <int> veTmp;
				printf("found key"); fflush(stdout);
				for (int x = 0; x < xend; x++) {
					for (int y = 1; y < pos; y++) {
						if (grid[y][x] == '#') {
							res[x] = y-1;
							//veKey[keyNum].push_back(res[x]);
							veTmp.push_back(5-res[x]);
							break;
						}
					}
				}
				veKey.push_back(veTmp);
			}
}
