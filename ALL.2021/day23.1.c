#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

FILE *a;
#define LINE 1000
//#define getchar()

#define Aen 1
#define Ben 10
#define Cen 100
#define Den 1000
#define SX 13
#define SY 3
//char grid[SY][SX];

/*
#...........#
###B#C#B#D###
  #A#D#C#A#
*/

struct pos_s {
	int x;
	int y;
};

struct pos_s positions[1000000][9];

struct pos_s all[] = {{1,0},{2,0},{3,0},{4,0},{5,0},{6.0},{7,0},{8,0},{9,0},{10,0},{11,0},
		{3,1},{5,1},{7,1},{9,1},
		{3,2},{5,2},{7,2},{9,2}};

struct pos_s land[] = {{1,0},{2,0},{4,0},{6.0},{8,0},{10,0},{11,0},
		{3,1},{5,1},{7,1},{9,1},
		{3,2},{5,2},{7,2},{9,2}};

struct pos_s aend[] = {{3,1}, {3,2}};
struct pos_s bend[] = {{5,1},{5,2}};
struct pos_s cend[] = {{7,1}, {7,2}};
struct pos_s dend[] = {{9,1}, {9,2}};

struct grid_s {
	struct pos_s A1;
	struct pos_s A2;
	struct pos_s B1;
	struct pos_s B2;
	struct pos_s C1;
	struct pos_s C2;
	struct pos_s D1;
	struct pos_s D2;
	char grid[SY][SX];
	int ignore;
	int cantmove;
	int score;
};
void makemove(int g);
int endgame(int gnum, int abcd);
	
struct grid_s grid[10000];
int numgrids = 1;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day 23\n"); fflush(stdout);
        char line1[LINE];

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
//        printf("LINE: %s\n", line1);
	if (leny == 0 || leny == 4) {
	} else {
		strcpy(grid[0].grid[leny-1], line1);
	}
	leny++;
}

fclose(a);
	for (int y = 0; y < SY; y++) {
		for (int x = 0; x < SX; x++) {
			printf("%c", grid[0].grid[y][x]);
			
		}
		printf("\n");
	}
	int fA = 0, fB = 0, fC = 0, fD = 0;
	for (int y = 0; y < SY; y++) {
		for (int x = 0; x < SX; x++) {
			if (grid[0].grid[y][x] == 'A') {
				if (fA == 1) {
					grid[0].A1.x = x; grid[0].A1.y = y;
				} else {
					grid[0].A2.x = x; grid[0].A2.y = y;
					fA = 1;
				}
			} else if (grid[0].grid[y][x] == 'B') {
				if (fB == 1) {
					grid[0].B1.x = x; grid[0].B1.y = y;
				} else {
					grid[0].B2.x = x; grid[0].B2.y = y;
					fB = 1;
				}
			} else if (grid[0].grid[y][x] == 'C') {
				if (fC == 1) {
					grid[0].C1.x = x; grid[0].C1.y = y;
				} else {
					grid[0].C2.x = x; grid[0].C2.y = y;
					fC = 1;
				}
			} else if (grid[0].grid[y][x] == 'D') {
				if (fD == 1) {
					grid[0].D1.x = x; grid[0].D1.y = y;
				} else {
					grid[0].D2.x = x; grid[0].D2.y = y;
					fD = 1;
				}
			}
		}
	}

	for (int i = 0; i < numgrids; i++) {
		makemove(i);
		if (endgame(i, 0) && endgame(i, 1) && endgame(i, 2) && endgame(i, 3)) {
			printf("is an end\n");
			grid[i].ignore = 1;
		} else {
			printf("not an end - grid %d\n", i);
		}
		getchar();
	
	}

	int min = 99999;

	for (int i = 0; i < numgrids; i++) {
		if (grid[i].cantmove != 1) {
			if (grid[i].score < min) {min = grid[i].score;}
		}
	}

	printf("**min %d\n", min);
}

void makemove(int g) {
	int size = (int)sizeof(land)/(int)sizeof(struct pos_s);
	for (int i = 0; i < size; i++) {
		
	}
}

int endgame(int gnum, int abcd) {
	if (abcd == 0) {
		int size = (int)sizeof(aend)/(int)sizeof(struct pos_s);
		int found = 0;
		for (int i = 0; i < size; i++) {
			if ((grid[gnum].A1.x == aend[i].x && grid[gnum].A1.y == aend[i].y) || (grid[gnum].A2.x == aend[i].x  && grid[gnum].A2.y == aend[i].y)) {
				found = 1;
			} else {
				found = 0;
				break;
			}
		}
		return found;
	} else if (abcd == 1) {
		int size = (int)sizeof(bend)/(int)sizeof(struct pos_s);
		int found = 0;
		for (int i = 0; i < size; i++) {
			if ((grid[gnum].B1.x == bend[i].x && grid[gnum].B1.y == bend[i].y) || (grid[gnum].B2.x == bend[i].x  && grid[gnum].B2.y == bend[i].y)) {
				found = 1;
			} else {
				found = 0;
				break;
			}
		}
		return found;
	} else if (abcd == 2) {
		int size = (int)sizeof(cend)/(int)sizeof(struct pos_s);
		int found = 0;
		for (int i = 0; i < size; i++) {
			if ((grid[gnum].C1.x == cend[i].x && grid[gnum].C1.y == cend[i].y) || (grid[gnum].C2.x == cend[i].x  && grid[gnum].C2.y == cend[i].y)) {
				found = 1;
			} else {
				found = 0;
				break;
			}
		}
		return found;
	} else if (abcd == 3) {
		int size = (int)sizeof(dend)/(int)sizeof(struct pos_s);
		int found = 0;
		for (int i = 0; i < size; i++) {
			if ((grid[gnum].D1.x == dend[i].x && grid[gnum].D1.y == dend[i].y) || (grid[gnum].D2.x == dend[i].x  && grid[gnum].D2.y == dend[i].y)) {
				found = 1;
			} else {
				found = 0;
				break;
			}
		}
		return found;
	}
	
	return 0;
}