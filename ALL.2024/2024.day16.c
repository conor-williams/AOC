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
#define assert(asdf)
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
char grid[200][200];
int already[200][200];
int minPath = 9999999;
int next(int x, int y, int ex, int ey,  int path, int dir, int prevDir, int steps);
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 16 Part 1\n"); fflush(stdout);

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

	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", minPath);
}

int next(int x, int y, int ex, int ey, int path, int dir, int prevDir, int steps) {
	if (abs(prevDir - dir) == 1 || abs(prevDir -dir) == 3) {path += 1000;}
	if ((x < 0) || (y > (leny-1)) || (y < 0) || (x > (lenx -1))) {return 0;}
	if (grid[y][x] == '#') {return 0;}

	if (x == ex && y == ey) {
		printf("path: %d steps:(%d)\n", path, steps);
		if (path < minPath) {printf("setting minPath\n"); minPath = path; }
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
