#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <set>
#include <map>


#include <unistd.h>

#define getchar()
#define assert(asdf)
/* compile with -Wl,--stack,999777666 */
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
char grid[142][142];
char gridTmp[142][142];
int already[142][142];
long long minPath;
long long minPathOrig = 999999999;
int next(int x, int y, int ex, int ey, int path, vector <pair<int, int>>ve);
void nextNoVec(int x, int y, int ex, int ey, int path, int noCheatPath);
void printit();
set <pair<int, int>> se;
void resetGrid();
void copyGrid();
map <long long, long long> mp;
int main(int argc, char **argv)
{
        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 20 Part 1\n"); fflush(stdout);
	printf("	SLOW ~20seconds\n");

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

	lenx = strlen(grid[0]);
	int sx, sy, ex, ey;
	int foundS = 0, foundE = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (foundS == 1 && foundE == 1) {
				goto after;
			} else if (grid[y][x] == 'S') {
				foundS = 1;
				sx = x; sy = y;
				grid[sy][sx] = '.';
			} else if (grid[y][x] == 'E') {
				foundE = 1;
				ex = x; ey = y;
				grid[ey][ex] = '.';
			}
		}
	}
	assert(foundS == 1 && foundE == 1);
	
after:
	memset(already, 0, sizeof(already));
	minPath = minPathOrig;
	vector <pair<int, int>> ve;
	ve.clear();
	printf("afgter ve.clear\n"); fflush(stdout);
	next(sx, sy, ex, ey, 0, ve);
	printf("se.size() %d\n", (int) se.size()); fflush(stdout);
	printf("minPath %lld\n", minPath); fflush(stdout); getchar();
	set <pair<int, int>> se2;
	long long noCheatMinPath = minPath;	
	for (auto se1: se) {
		int x1 = se1.first; int y1 = se1.second;
		
		if (y1-1 > 0) {if (grid[y1-1][x1] == '#') { se2.insert(make_pair(x1, y1-1));}}
		if (x1+1 < lenx-1) {if (grid[y1][x1+1] == '#') { se2.insert(make_pair(x1+1, y1));}}
		if (y1+1 < leny-1) {if (grid[y1+1][x1] == '#') { se2.insert(make_pair(x1, y1+1));}}
		if (x1-1 > 0) {if (grid[y1][x1-1] == '#') { se2.insert(make_pair(x1-1, y1));}}
	}
	long long count = 0;
	copyGrid();
	for (auto se3: se2) {
		int x1 = se3.first; int y1 = se3.second;

		assert(x1 >= 0 && x1 <= lenx-1 && y1 >= 0 && y1 <= leny-1);
		grid[y1][x1] = '.';
		memset(already, 0, sizeof(already));
		minPath = minPathOrig;
		nextNoVec(sx, sy, ex, ey, 0, noCheatMinPath);
		//printf("minPath %lld\n", minPath);
		long long save = noCheatMinPath - minPath;
		mp[save]++;
		if (save >= 100) { count++; }
		resetGrid();
	}
	//printf("count is %d\n", count);
	for (auto it = mp.begin(); it != mp.end(); it++) {
		printf("%lld: %lld\n", (*it).first, (*it).second);
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %lld\n", count);
		
}

void copyGrid() {
	for (int y = 0; y < leny; y++) {
		strcpy(gridTmp[y], grid[y]);
	}
}
	
void resetGrid() {
	for (int y = 0; y < leny; y++) {
		strcpy(grid[y], gridTmp[y]);
	}
}
int next(int x, int y, int ex, int ey, int path, vector <pair<int, int>> ve) {
	
	if (x < 0 || y < 0 || ex > lenx-1 || ey > leny -1 || grid[y][x] == '#') {return 55;}
	
	if (x == ex && y == ey) {
		printf("path found %d\n", path);
		if (path < minPath) {minPath = path; for (auto pa: ve) {se.insert(pa);}return 22;}
		return 22;
	}
	
	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		ve.push_back({x,y});
		//vector <pair<int, int>> ve1 = ve; vector <pair<int, int>> ve2 = ve;
		//vector <pair<int, int>> ve3 = ve; vector <pair<int, int>> ve4 = ve;
//		ve1.push_back({x, y}); ve2.push_back({x, y});
//		ve3.push_back({x, y}); ve4.push_back({x, y});
		if (22 == next(x, y-1, ex, ey, path+1, ve)) {return 22;}
		if (22 == next(x+1, y, ex, ey, path+1, ve)) {return 22;}
		if (22 == next(x, y+1, ex, ey, path+1, ve)) {return 22;}
		if (22 == next(x-1, y, ex, ey, path+1, ve)) {return 22;}
	}
	return 56;
}
void nextNoVec(int x, int y, int ex, int ey, int path, int noCheatPath) {
	if (path > noCheatPath) {return;}
	
	if (x < 0 || y < 0 || ex > lenx-1 || ey > leny -1 || grid[y][x] == '#') {return;}
	
	if (x == ex && y == ey) {
		//printf("path found %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}
	
	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		nextNoVec(x, y-1, ex, ey, path+1, noCheatPath);
		nextNoVec(x+1, y, ex, ey, path+1, noCheatPath);
		nextNoVec(x, y+1, ex, ey, path+1, noCheatPath);
		nextNoVec(x-1, y, ex, ey, path+1, noCheatPath);
	}
}
	
void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}
