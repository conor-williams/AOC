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

#define getchar()
/*
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

*/


void next (int x, int y, int ex, int ey, int path, int dir, int timesInDir);

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

char grid[200][200];
struct al_s {
	int path[4][5];
	//int timesInDir[5];
};

struct al_s already[200][200];

int minPath = 0;
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
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); if (a == NULL) {printf("BAD file %s\n", argv[1]); exit(0);}
	printf("		2023 Day 17 Part 1\n"); fflush(stdout);
	printf("	SLOW: approx < 1min\n");

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
	int sx = 0; int sy = 0;
	int ex = lenx-1; int ey = leny-1;

	memset(already, 0, sizeof(already));
	printf("end: %c\n", grid[ey][ex]); getchar();
	printf("start: %c\n", grid[sy][sx]); getchar();

	int minmin = lenx*leny*9;
	{
		minPath = leny*lenx*9;
		memset(already, 0, sizeof(already));
		next(sx, sy, ex, ey, - (grid[sy][sx] -48) , 1, 0);
		printf("gone east minPath %d\n", minPath);
		if (minPath < minmin) {minmin = minPath;}

		//minPath = lenx*leny*9; 
		memset(already, 0, sizeof(already));
		next(sx, sy, ex, ey, - (grid[sy][sx] -48) , 2, 0);
		printf("**gone south minPath: %d\n", minPath);
		if (minPath < minmin) {minmin = minPath;}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minmin);
}

void next (int x, int y, int ex, int ey, int path, int dir, int timesInDir) {
	if (x > lenx -1 || y > leny -1 || x < 0 || y < 0) {
		return;
	}
	if (timesInDir > 3) {return;}

	path += grid[y][x] - 48;
	//printf("path is %d\n", path);
	if (path >= minPath) {return;}

	if (x == ex && y == ey) {
		///printf("got end path %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}

	if (already[y][x].path[dir][timesInDir] == 0 || path < already[y][x].path[dir][timesInDir])
	{
		already[y][x].path[dir][timesInDir] = path;

		if (dir == 0) {
			next(x, y-1, ex, ey, path, 0, timesInDir+1);
			next(x-1, y, ex, ey, path, 3, 1);
			next(x+1, y, ex, ey, path, 1, 1);
		} else if (dir == 1) {
			next(x+1, y, ex, ey, path, 1, timesInDir+1);
			next(x, y-1, ex, ey, path, 0, 1);
			next(x, y+1, ex, ey, path, 2, 1);
		} else if (dir == 2) {
			next(x, y+1, ex, ey, path, 2, timesInDir+1);
			next(x+1, y, ex, ey, path, 1, 1);
			next(x-1, y, ex, ey, path, 3, 1);
		} else if (dir == 3) {
			next(x-1, y, ex, ey, path, 3, timesInDir+1);
			next(x, y+1, ex, ey, path, 2, 1);
			next(x, y-1, ex, ey, path, 0, 1);
		}
	}
}













		/*
		if (already[y][x].path == 0) {already[y][x].path = path; already[y][x].timesInDir[dir] = timesInDir; }
		if (path < already[y][x].path) {already[y][x].path = path;}
		if (path > already[y][x].path) {
			if (timesInDir < already[y][x].timesInDir[dir]) {already[y][x].timesInDir[dir] = timesInDir;}
		}
		if (already[y][x].timesInDir[dir] == 0) {already[y][x].timesInDir[dir] = timesInDir;}
		*/
