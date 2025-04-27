#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define GRIDX 400
#define GRIDY 400
#define COORDS 100
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2018 Day6.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int SIZE = 1000; char line1[SIZE];

	struct coords {
		int x;
		int y;
		int val;
		int count;
	};
	struct coords poses[COORDS];
	int numcoords = 0;
	for (int i = 0; i < COORDS; i++) {
		poses[i].x = 0;
		poses[i].y = 0;
		poses[i].val = 0;
		poses[i].count = 0;
	}

	int grid[GRIDY][GRIDX] = {0};
	for (int y = 0; y < GRIDY; y++) {
		for (int x = 0; x < GRIDX; x++) {
			grid[y][x] = 1000;
		}
	}

int leny = 0;
int maxx = 0; int maxy = 0;
int minx = 1000000; int miny = 1000000;
while (1) 
{
        fgets(line1, SIZE, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
 	line1[strlen(line1)-1] = '\0';
	int x, y;
	sscanf(line1, "%d, %d", &x, &y);
	grid[y][x] = numcoords;
	if (x > maxx) {maxx = x;} if (y > maxy) {maxy = y;}
	if (x < minx) {minx = x;} if (y < miny) {miny = y;}
	poses[numcoords].x = x; poses[numcoords].y = y; poses[numcoords].val = numcoords;
	numcoords++;
	leny++;
	
}
printf("numcoords %d\n", numcoords);
	for (int x = minx-1; x <= maxx+1; x++) {
		for (int y = miny-1; y <= maxy+1; y++) {
			int dist = 0;
			int mindist = 1000000; int winningcoord = 0;
			for (int i = 0; i < numcoords; i++) {
				//distance from x y to coords[i].x and coords[i].y
				//printf("trying coord: %d %d\n", poses[i].x, poses[i].y);
				int x1 = abs(x - poses[i].x);
				int y1 = abs(y - poses[i].y);
				dist = abs(x1+y1);
				if (dist < mindist) {
					mindist = dist; winningcoord = i;
				} else if (dist == mindist) {
					winningcoord = 1000;
				} 
			}
			grid[y][x] = winningcoord;
		}
	}
	int excludeList[1000];
	for (int i = 0; i < 1000; i++) {
		excludeList[i] = 999;
	}
	int xz1 = minx-1; 
	for (int y = miny-1; y <= maxy+1; y++) {
		excludeList[grid[y][xz1]] = grid[y][xz1];
	}
	int xz2 = maxx+1; 
	for (int y = miny-1; y <= maxy+1; y++) {
		excludeList[grid[y][xz2]] = grid[y][xz2] ;
	}
	for (int y = miny; y <= maxy; y++) {
		for (int x = minx; x <= maxx; x++) {
			if (grid[y][x] != 1000 && excludeList[grid[y][x]] == 999) {
				poses[grid[y][x]].count++;
			} 
			
		}
	}
	printf("%d %d\n", maxx, maxy);
	for (int y = 0; y <= maxy; y++) {
		for (int x = 0; x <= maxx; x++) {
			//printf("%d ", grid[y][x]);
		}
		//printf("\n");
	}
	printf("\n");

	int max = 0; int winner = 0; int winnerx = 0; int winnery = 0;
	for (int i = 0; i < numcoords; i++) {
		if (poses[i].count > max) {max = poses[i].count; winner = i; winnerx = poses[i].x; winnery = poses[i].y;}
	}
	printf("***winner [%d] count [%d] x,y[%d,%d]\n", winner, poses[winner].count, winnerx, winnery);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", poses[winner].count);
}

