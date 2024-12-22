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
#include <algorithm>


/* slow -- need some optims... */
/* compile with -Wl,--stack,999777666 */
using namespace std;
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

char grid[142][142];
char gridTmp[142][142];
int already[142][142];

int minPath;
int minPathOrig = 9999999;
int next(int x, int y, int ex, int ey, int path, vector <tuple<int, int, int>>ve);
void nextNoVec(int x, int y, int ex, int ey, int path);
void calcLen(tuple <int, int, int, int> bla);

void printit();
set <pair<int, int>> se;
map <int, int> mp;
int sx, sy, ex, ey;

int noCheatMinPath = 0;
map <tuple<int, int, int, int>, int> preComputedLens;
map <pair<int, int>, int> distToStart;
map <pair<int, int>, int> disttoend;
set <tuple<int, int, int, int>> se4;
set <tuple<int, int, int, int, int, int, int, int>> fourPoints;

int gcount = 0;

void generateAllCheatPaths();
void generateAllCheatPaths() {
	int ii = 0;
	for (auto se1: se) {
		ii++;
		int x2 = se1.first; int y2 = se1.second;
		if (ii % 1000 == 0) {
			printf("(%d of %d) checking circle around: %d,%d\n", ii, noCheatMinPath, x2, y2);
		}
		for (int end = 20; end >= 0; end--) {
			for (int radiusY = end; radiusY >= 0; radiusY--) {
				int radiusX = end - abs(radiusY);
				{
				//for (int radiusX = end; radiusX >= 0; radiusX--)  
					if (abs(radiusX) + abs(radiusY) != end) {continue;}
					int x1p = x2 + radiusX;
					int x1n = x2 - radiusX;
					int y1p = y2 + radiusY;
					int y1n = y2 - radiusY;
					//top right quad
					if (x1p >= 0 && x1p <= lenx-1 && y1n >= 0 && y1n <= leny-1 && grid[y1n][x1p] == '.') {
						if (se4.find({x2, y2, x1p, y1n}) == se4.end()) {se4.insert({x2, y2, x1p, y1n});}
					}
					if (x1p >= 0 && x1p <= lenx-1 && y1p >= 0 && y1p <= leny-1 && grid[y1p][x1p] == '.') {
                                                if (se4.find({x2, y2, x1p, y1p}) == se4.end()) {se4.insert({x2, y2, x1p, y1p});}
					}
					if (x1n >= 0 && x1n <= lenx-1 && y1p >= 0 && y1p <= leny-1 && grid[y1p][x1n] == '.') {
                                                if (se4.find({x2, y2, x1n, y1p}) == se4.end()) {se4.insert({x2, y2, x1n, y1p});}
					}
					if (x1n >= 0 && x1n <= lenx-1 && y1n >= 0 && y1n <= leny-1 && grid[y1n][x1n] == '.') {
						//if (se.find({x1n, y1n}) == se.end()) {continue;}
						if (se4.find({x2, y2, x1n, y1n}) == se4.end()) {se4.insert({x2, y2, x1n, y1n});}
					}
				}
			}
		}
	}
}

void saveinsave(int pathLen) {
	if (pathLen <= noCheatMinPath) {
		int save = noCheatMinPath - pathLen;
		if (save < 0) {	
			printf("ERR(save)\n");
		} else {
			//if (mp[76] > 3) {printf("oh no...\n");getchar();}
			mp[save]++;
			if (save >= 100) {gcount++;}
		}
	}
}

int getPathLength(tuple <int, int, int, int> bla);
int getPathLength(tuple <int, int, int, int> bla) {
	int x1 = get<0>(bla);
	int y1 = get<1>(bla);
	int x2 = get<2>(bla);
	int y2 = get<3>(bla);
	if (preComputedLens.find({x1, y1, x2, y2}) != preComputedLens.end()) {
		int ans = preComputedLens[{x1, y1, x2, y2}];
		return ans;
	} else {
		memset(already, 0, sizeof(already));
		minPath = minPathOrig;
		nextNoVec(x1, y1, x2, y2, 0);
		int m1 = minPath;
		preComputedLens[{x1, y1, x2, y2}] = m1;
		preComputedLens[{x2, y2, x1, y1}] = m1;
		return m1;
	}

}

int main(int argc, char **argv)
{
	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 20 Part 2\n"); fflush(stdout);
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
	vector <tuple<int, int, int>> ve;
	next(sx, sy, ex, ey, 0, ve);
	noCheatMinPath = minPath;	

	printf("se.size() %d\n", (int) se.size()); fflush(stdout);
	printf("noCheatMinPath %d\n", noCheatMinPath); fflush(stdout); 

	generateAllCheatPaths();

	printf("se4.size is %d\n", (int) se4.size()); fflush(stdout); 

	int bb = 0;
	int szse4 = (int)se4.size();
	for (auto se5: se4) {
		bb++;
		int fx1 = get<0>(se5); int fy1 = get<1>(se5); int tx1 = get<2>(se5); int ty1 = get<3>(se5);
		if (bb % 10000 == 0) {printf("(%d of %d) cheats checks (%d,%d -> %d,%d -> %d,%d -> %d,%d)\n", bb, szse4, sx, sy, fx1, fy1, tx1, ty1, ex, ey);}

		int abs_var = abs(fx1-tx1) + abs(fy1-ty1);

		///int pathLen2 = getPathLength({sx, sy, fx1, fy1}) + getPathLength({tx1, ty1, ex, ey}) + abs_var;
		int pathLen3 = distToStart[{fx1, fy1}] + abs_var + noCheatMinPath - distToStart[{tx1, ty1}];
		//assert (pathLen2 == pathLen3);

/*
		if (fourPoints.find({sx, sy, fx1, fy1, tx1, ty1, ex, ey}) != fourPoints.end()) {
			printf("ERR already\n"); exit(0);
		} else {
			fourPoints.insert({sx, sy, fx1, fy1, tx1, ty1, ex, ey});
		}
*/
		saveinsave(pathLen3);
	}
	//printf("fourPoints.size() is %d\n", (int)fourPoints.size());

	for (auto it = mp.begin(); it != mp.end(); it++) {
		if ((*it).first >= 50) {
			printf("There are %d cheats that save %d picoseconds.\n", (*it).second, (*it).first);
		} else {
			//printf("There are %d cheats that save %d picoseconds.\n", (*it).second, (*it).first);
		}
	}
	printf("**ans %d\n", gcount);
}


int next(int x, int y, int ex, int ey, int path, vector <tuple<int, int, int>> ve) {

	if (x < 0 || y < 0 || x > lenx-1 || y > leny -1 || grid[y][x] == '#') {return 55;}

	if (x == ex && y == ey) {
		printf("path found %d\n", path);
		if (path < minPath) {minPath = path; ve.push_back({x,y, path}); for (auto pa: ve) {int x2 = get<0>(pa); int y2 = get<1>(pa);
			int d1=get<2>(pa); pair <int, int> pa2; pa2.first = x2; pa2.second=y2; distToStart[{x2, y2}] = d1; se.insert(pa2);} return 22;}
		return 22;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		ve.push_back({x,y, path});
		if (22 == next(x, y-1, ex, ey, path+1, ve)) {return 22;}
		if (22 == next(x+1, y, ex, ey, path+1, ve)) {return 22;}
		if (22 == next(x, y+1, ex, ey, path+1, ve)) {return 22;}
		if (22 == next(x-1, y, ex, ey, path+1, ve)) {return 22;}
	}
	return 56;
}

void nextNoVec(int x, int y, int ex, int ey, int path) {
	if (path > noCheatMinPath) {return;}

	if (x < 0 || y < 0 || x > lenx-1 || y > leny -1 || grid[y][x] == '#') {return;}

	if (x == ex && y == ey) {
		//printf("path found %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		nextNoVec(x, y-1, ex, ey, path+1);
		nextNoVec(x+1, y, ex, ey, path+1);
		nextNoVec(x, y+1, ex, ey, path+1);
		nextNoVec(x-1, y, ex, ey, path+1);
	}
}

void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (x == sx && y == sy) {
				printf("S");
			} else if (x == ex && y == ey) {
				printf("E");
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
