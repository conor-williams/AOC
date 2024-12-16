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

using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
char grid[200][200];
int already[200][200];
int minPath = 9999999;
int minSteps = 9999999;
int next(int x, int y, int ex, int ey,  int path, int dir, int prevDir, int steps);
int next2(int x, int y, int ex, int ey, int path, int dir, int prevDir, int steps, vector <pair<int, int>> ve);
set <pair<int, int>> se;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 16 Part 1\n"); fflush(stdout);
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
	int sx, sy = -1, ex, ey = -1;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'S') {
				sx = x; sy = y;
				grid[y][x] = '.';
				if (sy != -1 && ey != -1) {goto after;}
			} else if (grid[y][x] == 'E') {
				ex = x; ey = y;
				grid[y][x] = '.';
				if (sy != -1 && ey != -1) {goto after;}
			}
		}
	}
after:

	memset(already, 0, sizeof(already));
	printf("%d,%d -> %d,%d -- lenx:%d leny:%d\n", sx, sy, ex, ey, lenx, leny);
	next(sx, sy, ex, ey, 0, 1, 1, 0);
	printf("minPath :::: %d\n", minPath);
	printf("minSteps :::: %d\n", minSteps);
	vector <pair<int, int>> ve;
	memset(already, 0, sizeof(already));
	next2(sx, sy, ex, ey, 0, 1, 1, 0, ve);
	printf("**ans %ld\n", se.size()+1);
	
}
int next2(int x, int y, int ex, int ey, int path, int dir, int prevDir, int steps, vector <pair<int, int>> ve) {
	if (steps > minSteps) {return 0;}
	if (path > minPath) {return 0;}
	if (abs(prevDir - dir) == 1 || abs(prevDir -dir) == 3) {path += 1000;}
	if ((x < 0) || (y > (leny-1)) || (y < 0) || (x > (lenx -1))) {return 0;}
	if (grid[y][x] == '#') {return 0;}

	if (x == ex && y == ey) {
		printf("path: %d steps:(%d)\n", path, steps);
		if (path == minPath) {
			for (auto it = ve.begin(); it != ve.end(); it++) {
				pair pa = *it;
				se.insert(make_pair(pa.first, pa.second));
			}
		}
		return 0;
	}
	if (already[y][x] == 0  || steps <= already[y][x]) {
		already[y][x] = steps;
		vector <pair<int, int>> ve1 = ve;
		vector <pair<int, int>> ve2 = ve;
		vector <pair<int, int>> ve3 = ve;
		vector <pair<int, int>> ve4 = ve;
		ve1.push_back({x, y});
		ve2.push_back({x, y});
		ve3.push_back({x, y});
		ve4.push_back({x, y});
		next2(x, y-1, ex, ey, path+1, 0, dir, steps+1, ve1);
		next2(x+1, y, ex, ey, path+1, 1, dir, steps+1, ve2);
		next2(x, y+1, ex, ey, path+1, 2, dir, steps+1, ve3);
		next2(x-1, y, ex, ey, path+1, 3, dir, steps+1, ve4);
	}
	return 0;
}

int next(int x, int y, int ex, int ey, int path, int dir, int prevDir, int steps) {
	if (abs(prevDir - dir) == 1 || abs(prevDir -dir) == 3) {path += 1000;}
	if ((x < 0) || (y > (leny-1)) || (y < 0) || (x > (lenx -1))) {return 0;}
	if (grid[y][x] == '#') {return 0;}

	if (x == ex && y == ey) {
		printf("path: %d steps:(%d)\n", path, steps);
		if (path < minPath) {printf("setting minPath\n"); minPath = path; minSteps = steps;}
		//if (steps < minSteps) {minSteps = steps;}
		return 0;
	}
	if (already[y][x] == 0 || path < already[y][x]) {
		//if (abs(prevDir - dir) == 1) {path += 1000;}
		already[y][x] = path;
		next(x, y-1, ex, ey, path+1, 0, dir, steps+1);
		next(x+1, y, ex, ey, path+1, 1, dir, steps+1);
		next(x, y+1, ex, ey, path+1, 2, dir, steps+1);
		next(x-1, y, ex, ey, path+1, 3, dir, steps+1);
	}
	return 0;
}
