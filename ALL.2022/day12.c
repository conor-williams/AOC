#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SX 200

char grid[SX][SX];
int already[SX][SX];
int lenx = 0;
void next(int x, int y, int path, int ex, int ey);
int minPath = 99999;
int leny = 0;
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 12 - 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

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

	int stx, sty;
	int enx, eny;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'S') {
				stx = x; sty = y;
				grid[y][x] = 'a';
			} else if (grid[y][x] == 'E') {
				enx = x; eny = y;
				grid[y][x] = 'z';
			}
		}
	}
	next(stx, sty, 0, enx, eny);

	printf("**minPath %d\n", minPath);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minPath);
}


void next(int x, int y, int path, int ex, int ey) {
	if (x == ex && y == ey) {
		if (path < minPath) {minPath = path;}
		return;
	}

	if (already[y][x] > path || already[y][x] == 0) {
		already[y][x] = path;

		if (grid[y-1][x] - grid[y][x] <= 1) {
			if (y-1 >= 0) {next(x, y-1, path+1, ex, ey);}
		}
		if (grid[y][x+1] - grid[y][x] <= 1) {
			if (x+1 < lenx) {next(x+1, y, path+1, ex, ey);}
		}
		if (grid[y+1][x] - grid[y][x] <= 1) {
			if (y+1 < leny) {next(x, y+1, path+1, ex, ey);}
		}
		if (grid[y][x-1] - grid[y][x] <= 1) {
			if (x-1 >= 0) {next(x-1, y, path+1, ex, ey);}
		}
	}

}
