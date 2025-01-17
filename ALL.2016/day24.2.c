#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2016 day24 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 1000000

#ifdef EX1
#define GX 11
#define GY 5
#define NUMS 5
#else
#define GX 183
#define GY 45
#define NUMS 8
#endif

int mymin = 9999;

char grid[GY+1][GX+1];
int already[GY+1][GX+1];

void next(int x, int y, int dx, int dy, int steps, int first);
int sDist(int fr, int to);

int distGrid[NUMS+1][NUMS+1];
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	for (int y = 0; y < NUMS; y++) {
		for (int x = 0; x < NUMS; x++) {
			distGrid[y][x] = -1;
		}
	}
	char line1[SIZE];
	while(1) 
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		//	printf("LINE: %s\n", line1);
#endif
		strcpy(grid[leny], line1);

		leny++;
	}
	fclose(a);

	for (int fr = 0; fr < NUMS-1; fr++) {
		for (int to = fr+1; to < NUMS; to++) {
			int tmp = sDist(fr, to); 
			distGrid[fr][to] = tmp;
			distGrid[to][fr] = tmp;
		}
	}
	int tosort[NUMS];
	for (int i = 0; i < NUMS; i++) {
		tosort[i] = i;
	}
	sort(tosort, tosort+NUMS);

	int minSumDist = 9999;
	do {
		if (tosort[0] != 0) {continue;}
		int sumDist = 0;
		for (int j = 0; j < NUMS-1; j++) {
			sumDist += distGrid[tosort[j]][tosort[j+1]];	
		}
		sumDist+= distGrid[tosort[NUMS-1]][tosort[0]];
		if (sumDist < minSumDist) {minSumDist = sumDist;}
	} while (next_permutation(tosort, tosort+NUMS));

	printf("***minSumDist %d\n", minSumDist); fflush(stdout);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minSumDist); fflush(stdout);
	//printf("***tot %ld END\n", tot); fflush(stdout);
} 

int sDist(int fr, int to) {

	int Gfry, Gfrx, Gtoy, Gtox;
	for (int y = 0; y < GY; y++) {
		for (int x = 0; x < GX; x++) {
			if (grid[y][x] == fr+48 ) {
				Gfry = y; Gfrx = x; goto next;
			}
		}
	}
next:
	for (int y = 0; y < GY; y++) {
		for (int x = 0; x < GX; x++) {
			if (grid[y][x] == to+48 ) {
				Gtoy = y; Gtox = x; goto next2;
			}
		}

	}
next2:

	for (int y = 0; y< GY; y++) {
		for (int x = 0; x < GX; x++) {
			already[y][x] = -1;
		}
	}
	already[Gfry][Gfrx] = 0;
	mymin = 9999;

	//printf("next: %d %d -> %d %d\n", Gfrx, Gfry, Gtox, Gtoy);
	next(Gfrx, Gfry, Gtox, Gtoy, 0, 1);
	return mymin;
}

void next(int x, int y, int dx, int dy, int steps, int first) {
	if (grid[y][x] == '#') {return;}
	if (x == dx && y == dy) {
		if (steps < mymin) {mymin = steps;}
		//printf("dest reached steps: %d (mymin: %d)\n", steps, mymin);
		return;
	}

	if (first == 1 || steps < already[y][x] || already[y][x] == -1 ) {
		already[y][x] = steps;
		if (y-1 >= 0)  {next(x, y-1, dx, dy, steps+1, 2);}
		if (x+1 <= GX) {next(x+1, y, dx, dy, steps+1, 2);}
		if (y+1 <= GY) {next(x, y+1, dx, dy, steps+1, 2);}
		if (x-1 >= 0)  {next(x-1, y, dx, dy, steps+1, 2);}
	}
}
