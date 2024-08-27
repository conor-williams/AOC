#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SX 2000
//char grid[SX][SX];
//char gridDia[SX][SX];
map <int, map <int, int>> grid, gridDia;

int lenx = 0;
int leny = 0;
struct sb_s {
	int senX;
	int senY;
	int beaX;
	int beaY;
	int man;
};

#define PAD 200000000

struct sb_s sb[1000];

void populateDia(int x, int y, int);
void printit();
int maxSenX = 0;
int minSenX = 9999999;
int maxBeaX = 0;
int minBeaX = 9999999;
int maxSenY = 0;
int minSenY = 9999999;
int maxBeaY = 0;
int minBeaY = 9999999;

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day 15-1\n"); fflush(stdout);
        char line1[LINE];


//Sensor at x=21PAD774, y=3136587: closest beacon is at x=2561642, y=2914773
//Sensor at x=3983829, y=2469869: closest beacon is at x=3665790, y=2180751
	//memset(grid,  46 /*.*/, sizeof(grid));
	//memset(gridDia, 46 /*.*/, sizeof(gridDia));
	int numBeacon = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int senX, senY;
	int beaX, beaY;
	sscanf(line1, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
		&senX, &senY, &beaX, &beaY); 
	printf("leny: %d %d %d %d %d\n", leny, senX, senY, beaX, beaY); getchar();
	sb[leny].senX = senX+PAD;
	sb[leny].senY = senY+PAD;
	sb[leny].beaX = beaX+PAD;
	sb[leny].beaY = beaY+PAD;
	sb[leny].man = abs(beaX- senX) + abs(beaY - senY);
	
	grid[senY+PAD][senX+PAD] = 'S';	
	grid[beaY+PAD][beaX+PAD] = 'B';	
		
	if (senX+PAD > maxSenX) {maxSenX = senX+PAD;}
	if (senX+PAD < minSenX) {minSenX = senX+PAD;}
	if (beaX+PAD > maxBeaX) {maxBeaX = beaX+PAD;}
	if (beaX+PAD < minBeaX) {minBeaX = beaX+PAD;}

	if (senY+PAD > maxSenY) {maxSenY = senY+PAD;}
	if (senY+PAD < minSenY) {minSenY = senY+PAD;}
	if (beaY+PAD > maxBeaY) {maxBeaY = beaY+PAD;}
	if (beaY+PAD < minBeaY) {minBeaY = beaY+PAD;}

	numBeacon++;
	leny++;
}
fclose(a);
/*
	printf("X: minSen:%d maxSen:%d minBea:%d maxBea:%d\n", minSenX, maxSenX, minBeaX, maxBeaX);
	printf("Y: minSen:%d maxSen:%d minBea:%d maxBea:%d\n", minSenY, maxSenY, minBeaY, maxBeaY);
*/
	getchar();
	//lenx = (int)strlen(grid[0]);
	leny = leny   + PAD+ PAD; 
	lenx = maxSenX+ PAD+PAD;

	for (int i = 0; i < numBeacon; i++) {
		printf("%d %d %d\n", sb[i].senX, sb[i].senY, sb[i].man);
		populateDia(sb[i].senX, sb[i].senY, sb[i].man);
		//printit(); getchar();
	}
/*
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			//printf("%c", grid[y][x]);
			if (grid[y][x] == 'S') {
				printf("found S\n"); getchar();
				populateDia(x, y);
				printit(); getchar();
			}
		}
	printf("\n");
	}
	printf("\n");
*/

	for (auto it = gridDia.begin(); it != gridDia.end(); it++) {
		auto inner_map = it->second;
		for (auto inner_it = inner_map.begin(); inner_it != inner_map.end(); inner_it++) {
			if (grid[it->first][inner_it->first] == 'B') {
				gridDia[it->first][inner_it->first] = 'B';
			}
		}
	}
				
/*
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'B') {
				gridDia[y][x] = 'B';
			} else if (grid[y][x] == 'S') {
				gridDia[y][x] = 'S';
			}
		}
	}
	printit(); getchar();
*/

	int count = 0;
	int y2 = 2000000+PAD;
	for (auto it = gridDia.begin(); it != gridDia.end(); it++) {
		auto inner_map = it->second;
		for (auto inner_it = inner_map.begin(); inner_it != inner_map.end(); inner_it++) {
			if (it->first == y2) {
				if (gridDia[it->first][inner_it->first] == '#') {
					count++;
				}
			}
		}
	}
	printf("**count is %d\n", count);
}

void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", gridDia[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

void populateDia(int xIn, int yIn, int m1) {
	printf("in pop \n"); fflush(stdout);
	//for (int y = yIn-9; y <= yIn+9; y++) //for (int x = 
	
	for (int y = -m1; y <= +m1; y++) {
		if (y +yIn != 2000000+PAD) {continue;}
		printf("here1\n");
		int xEnd    =   m1-abs(y);
		int xStart  = -(m1-abs(y));
		if (y+yIn < 0)     {continue;}
		if (y+yIn >= leny) {continue;}
		for (int x = xStart; x <= xEnd; x++) {
			if (x+xIn < 0) {continue;}
			if (x+xIn >=lenx) {continue;}

			gridDia[y+yIn][x+xIn] = '#';
		}
	}
//	at abs(yIn) == 9 x is 0
//	at abs(yIn) == 8 x is 1
//	at abs(yIn) == 7 x is 2
//	at abs(yIn) == 6 x is 3
//	at abs(yIn) == 5 x is 4
//	at abs(yIn) == 4 x is 5
//	at abs(yIn) == 3 x is 6
}
