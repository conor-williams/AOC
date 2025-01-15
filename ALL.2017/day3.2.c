#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define X 10000
#define Y 10000
int grid[X][Y] = {0};
int main(int argc, char **argv)
{
/*
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day3.2\n"); fflush(stdin); fflush(stdout);


        char line1[3000];
*/
        printf("2017 Day3.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

/*
while (1) 
{
        fgets(line1, 3000, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
*/
	
/*
}
*/
	grid[(Y/2)][(X/2)] = 1;
	grid[(Y/2)][(X/2)+1] = 1;
	grid[(Y/2)-1][(X/2)+1] = 2;
	grid[(Y/2)-1][(X/2)] = 4;
	grid[(Y/2)-1][(X/2)-1] = 5;
	grid[(Y/2)][(X/2)-1] = 10;
	grid[(Y/2)+1][(X/2)-1] = 11;
	grid[(Y/2)+1][(X/2)] = 23;
	grid[(Y/2)+1][(X/2)+1] = 25;

	int dir = 1; 
	int x = (X/2)+1; int y = (Y/2)+1;
start:
	printf("grid x y %d %d is (%d) dir:%d\n", x, y, grid[y][x], dir);
	int count = 0;
	int val = 0;
	if (grid[y][x+1] == 0) {
		count++; } else { val += grid[y][x+1];}
	if (grid[y][x-1] == 0) {
		count++;}else { val += grid[y][x-1];}
	if (grid[y+1][x] == 0) {
		count++;} else {val += grid[y+1][x];}
	if (grid[y+1][x+1] == 0) {
		count++;} else { val += grid[y+1][x+1];}
	if (grid[y+1][x-1] == 0) {
		count++;} else { val += grid[y+1][x-1];}
	if (grid[y-1][x] == 0) {
		count++;} else { val += grid[y-1][x]; }
	if (grid[y-1][x+1] == 0) {
		count++;} else { val += grid[y-1][x+1];}
	if (grid[y-1][x-1] == 0) {
		count++;} else { val += grid[y-1][x-1];}
	printf("count: %d\n", count);
	if (count == 7 || count == 8) {
		if (dir == 1) {x = x-1;} else if (dir == 0) {y=y+1;} else if (dir == 3) {x=x+1;} else if (dir == 2) {y=y-1;}
		dir = (4 + dir - 1)%4;	
	} else {
		grid[y][x] = val;
		//{printf("%d ", val); }
		if (val > 277678) {dup2(fd, 1); printf("**ans: %d\n", val);exit(0);}
	}
	if (dir == 1) {x = x+1;} else if (dir == 0) {y=y-1;} else if (dir == 3) {x=x-1;} else if (dir == 2) {y=y+1;}
	goto start;

	for (int x = X/2; x < X; x++) {
		for (int y = Y/2; y< Y; y++) {
		}
	}
	for (int y = 0; y< Y; y++) {
		int found = 0;
		for (int x = 0; x < X; x++) {
			if (grid[y][x] != 0) {
				printf("[%3d]", grid[y][x]);
				found = 1;
			}
		}
		if (found == 1) { printf("\n");}
	}

}

