#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

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
int next(int x, int y, int ex, int ey, int path);
void printit();
struct point_s {
	int x,y;
};
struct point_s point[4000];
int szleny;
int szlenx;
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
	point[leny].x = x1; point[leny].y = y1;
	leny++; //number of points
}
fclose(a);
	printf("using SIZE %d\n", SIZE);
	szlenx = SIZE; szleny = SIZE; //assume square
	printit();

	int minORIG = 999999;
	for (int kk = NUMFALL; kk < leny; kk++) {
		struct point_s p1 = point[kk];
		printf("p1.x p1.y %d, %d\n", p1.x, p1.y);
		grid[p1.y][p1.x] = '#';
		memset(already, 0, sizeof(already));
		minPath = minORIG;
		next(0, 0, szlenx-1, szleny-1, 0);
		if (minPath == minORIG) {
			printf("kk bad: %d\n", kk);
			printf("**ans [ %d,%d ]\n", p1.x, p1.y);
			exit(0);
		} else {
			printf("kk: %d ok\n", kk);
		}
	}

	printf("minPath is %d\n", minPath);
}

void printit() {
	for (int y = 0; y < szleny; y++) {
		for (int x = 0; x < szlenx; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

int next(int x, int y, int ex, int ey, int path) {

	if (x < 0 || y < 0 || x > szlenx-1 || y > szleny-1 || grid[y][x] == '#' ) {
		return -1;
	}
	if (x == ex && y == ey) {
		//printf("found path %d\n", path);
		if (path < minPath) {minPath = path;}
		return 2;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
/*
		next(x, y-1, ex, ey, path+1);
		next(x+1, y, ex, ey, path+1);
		next(x, y+1, ex, ey, path+1);
		next(x-1, y, ex, ey, path+1);
*/

		if (next(x, y-1, ex, ey, path+1) == 2) {return 2;}
		if (next(x+1, y, ex, ey, path+1) == 2) {return 2;}
		if (next(x, y+1, ex, ey, path+1) == 2) {return 2;}
		if (next(x-1, y, ex, ey, path+1) == 2) {return 2;}

	}
	return 1;
}
