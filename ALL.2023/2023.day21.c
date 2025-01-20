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
#define assert(asf)
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

map <pair <int, int>, int> mp;	
map <pair <int, int>, int> mpTmp;	
void move(int x, int y);

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

char grid[140][140];
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

	a = fopen(argv[1], "r"); if (a == NULL) {printf("BAD file %s\n", argv[1]); exit(0);}
	printf("2023 Day 21 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);
	int sx, sy;
	for (int yy = 0; yy < leny; yy++) {
		for (int xx = 0; xx < lenx; xx++) {
			if (grid[yy][xx] == 'S') {
				sx = xx; sy=yy; grid[yy][xx] = '.'; break;
			}
		}
	}

	int ENDSTEPS = 64;
	if (argc == 3) {ENDSTEPS = atoi(argv[2]);}
	mp[{sx, sy}] = 1;
	for (int ste = 0; ste < ENDSTEPS; ste++) {
		mpTmp.clear();
		for (auto it = mp.begin(); it != mp.end(); it++) {
			int x1 = (*it).first.first;
			int y1 = (*it).first.second;
			move(x1, y1);
		}
		mp = mpTmp;
		printf("steps: %d -- plots: %d\n", ste, (int)mp.size());
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", (int)mp.size());
}
void move(int x, int y) 
{
	if (y-1>= 0 && grid[y-1][x] != '#') {
		if (mpTmp.find({x, y-1}) == mpTmp.end()) {
			mpTmp[{x, y-1}] = 1;
		}
	}
	if (x+1 < lenx && grid[y][x+1] != '#') {
		if (mpTmp.find({x+1, y}) == mpTmp.end()) {
			mpTmp[{x+1, y}] = 1;
		}
	}
	if (y+1 < leny && grid[y+1][x] != '#') {
		if (mpTmp.find({x, y+1}) == mpTmp.end()) {
			mpTmp[{x, y+1}] = 1;
		}
	}
	if (x-1 >= 0 && grid[y][x-1] != '#') {
		if (mpTmp.find({x-1, y}) == mpTmp.end()) {
			mpTmp[{x-1, y}] = 1;
		}
	}
}
