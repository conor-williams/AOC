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
char grid[100][100];
int already[100][100];
int minPath = 10000000;
int SIZE = 71;
int NUMFALL = 1024;
void next(int x, int y, int ex, int ey, int path);
void printit();
int main(int argc, char **argv)
{
        //signal(SIGTSTP, &sigfunc);
	if (argc >= 3) {SIZE = atoi(argv[2]);}
	if (argc >= 4) {NUMFALL = atoi(argv[3]);}
	memset(grid, '.', sizeof(grid));
	memset(already, 0, sizeof(already));
        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 18 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int x1, y1;
	sscanf(line1, "%d,%d", &x1, &y1);
	if (leny < NUMFALL) { 
		grid[y1][x1] = '#';
	}
	leny++;
}
fclose(a);
	printf("using SIZE %d\n", SIZE);
	lenx = SIZE; leny = SIZE; //assume square
	printit();

	next(0, 0, lenx-1, leny-1, 0);

	printf("minPath is %d\n", minPath);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minPath);
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

void next(int x, int y, int ex, int ey, int path) {

	if (x < 0 || y < 0 || x > lenx-1 || y > leny-1 || grid[y][x] == '#' ) {
		return;
	}
	if (x == ex && y == ey) {
		//printf("found path %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		next(x, y-1, ex, ey, path+1);
		next(x+1, y, ex, ey, path+1);
		next(x, y+1, ex, ey, path+1);
		next(x-1, y, ex, ey, path+1);
	}
}
