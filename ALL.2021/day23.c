#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

FILE *a;
#define LINE 1000
#define getchar()
#define SCOREA 1
#define SCOREB 10
#define SCOREC 100
#define SCORED 1000
int minScore = 99999;
int origA1x, origA1y; int origA2x, origA2y;
int origB1x, origB1y; int origB2x, origB2y;
int origC1x, origC1y; int origC2x, origC2y;
int origD1x, origD1y; int origD2x, origD2y;
#define SX 30
#define SY 30
int fd;
/*
#...........#
###B#C#B#D###
  #A#D#C#A#
*/

struct pos_s {
	int x;
	int y;
};


struct pos_s all[] = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0},
		{3,1},{5,1},{7,1},{9,1},
		{3,2},{5,2},{7,2},{9,2}};

struct pos_s land[] = {{1,0},{2,0},{4,0},{6,0},{8,0},{10,0},{11,0},
		{3,1},{5,1},{7,1},{9,1},
		{3,2},{5,2},{7,2},{9,2}};

struct pos_s notCorridor[] = {{3,0}, {5,0}, {7,0}, {9,0}};
int notCorridorLen = sizeof(notCorridor)/sizeof(struct pos_s);

struct pos_s corridor[] = {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
int corridorLen = sizeof(corridor)/sizeof(struct pos_s);
struct pos_s aend[] = {{3,2}, {3,1}};
struct pos_s bend[] = {{5,2}, {5,1}};
struct pos_s cend[] = {{7,2}, {7,1}};
struct pos_s dend[] = {{9,2}, {9,1}};

struct grid_s {
	struct pos_s A1;
	struct pos_s A2;
	struct pos_s B1;
	struct pos_s B2;
	struct pos_s C1;
	struct pos_s C2;
	struct pos_s D1;
	struct pos_s D2;
	int ignore;
	int score;
	//char grid[SY][SX];
	//int cantmove;
};
int makemove(int g, char wat);
int endgame(int gnum, int abcd);
	
#define MAXNUMGRID 10000000
struct grid_s *grid;
int numgrids = 0;
int inCorridor(int gr, char wat);
int blockedFromHomeCorr(int gr, char wat);
int inHomeTop(int gr, char wat);
int inHomeBottom(int gr, char wat);
void makeMoveHome(int gr, char wat);
void dupGrid(int gr);
int isfree(int gr, int xv);
int blankBottom(int gr, char wat);
int blankTop(int gr, char wat);
int inHomeOther(int gr, char wat);
int blockedToCorr(int gr, char  wat);
void makeMoveCorridor(int gr, char wat, int which);
int inHome(int gr, char wat);
void printGrid(int gr);
int inHomeOtherBottom(int gr, char wat);
int blankHomeOtherTop(int g, char wat);
int inHomeOtherTop(int gr, char wat);
void makeMoveStraitHome(int gr, char wat);

char gridInitial[SY][SX];
int samePoses(int gr);
int isEnd(int gr);
int main(int argc, char **argv)
{
	grid = (struct grid_s *)malloc(MAXNUMGRID * sizeof(struct grid_s));
	if (grid == NULL) {printf("no mem\n"); exit(0);}
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day 23 - 1\n"); fflush(stdout);
        char line1[LINE];
	fd = dup(1); close(1);

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	if (leny == 0 || leny == 4) {
	} else {
		strcpy(gridInitial[leny-1], line1);
	}
	leny++;
}

fclose(a);
	for (int y = 0; y < SY; y++) {
		for (int x = 0; x < SX; x++) {
			printf("%c", gridInitial[y][x]);
			
		}
		printf("\n");
	}
	int fA = 0, fB = 0, fC = 0, fD = 0;
	for (int y = 0; y < SY; y++) {
		for (int x = 0; x < SX; x++) {
			if (gridInitial[y][x] == 'A') {
				if (fA == 1) {
					grid[0].A1.x = x; grid[0].A1.y = y;
					origA1x = x; origA1y = y;
				} else {
					grid[0].A2.x = x; grid[0].A2.y = y;
					origA2x = x; origA2y = y;
					fA = 1;
				}
			} else if (gridInitial[y][x] == 'B') {
				if (fB == 1) {
					origB1x = x; origB1y = y;
					grid[0].B1.x = x; grid[0].B1.y = y;
				} else {
					origB2x = x; origB2y = y;
					grid[0].B2.x = x; grid[0].B2.y = y;
					fB = 1;
				}
			} else if (gridInitial[y][x] == 'C') {
				if (fC == 1) {
					origC1x = x; origC1y = y;
					grid[0].C1.x = x; grid[0].C1.y = y;
				} else {
					origC2x = x; origC2y = y;
					grid[0].C2.x = x; grid[0].C2.y = y;
					fC = 1;
				}
			} else if (gridInitial[y][x] == 'D') {
				if (fD == 1) {
					origD1x = x; origD1y = y;
					grid[0].D1.x = x; grid[0].D1.y = y;
				} else {
					origD2x = x; origD2y = y;
					grid[0].D2.x = x; grid[0].D2.y = y;
					fD = 1;
				}
			}
		}
	}
	numgrids = 1;

again:
	int endGrid = numgrids;
	int changed = 0;
	printf("\n\n\n\n\nnumgrids: %d\n", numgrids);
	for (int i = 0; i < endGrid; i++) {
		if (grid[i].ignore != 1) {
			printGrid(i); getchar();
			assert(samePoses(i) == 0);
			if (makemove(i, 'A')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'a')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'B')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'b')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'C')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'c')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'D')) {if (changed != 1) {changed = 1;}}
			if (makemove(i, 'd')) {if (changed != 1) {changed = 1;}}
			if (isEnd(i)) {
				printf("\n\n\nis an end -- %d\n", grid[i].score);
				if (grid[i].score < minScore) {minScore = grid[i].score;}
				grid[i].ignore = 1; getchar(); 
			} else {
				//printf("\n\n\nnot an end - grid %d\n", i);
			}
		}
                if (grid[i].ignore != 1) {grid[i].ignore = 1;}
	}

	if (changed) {goto again;}

	dup2(fd,1);
	printf("\n\n\n\n\nnumgrids %d\n", numgrids);
	printf("\n\n\n\n\n**minScore %d\n", minScore);
	free(grid);
}
int isEnd(int gr) {
	if (
		((grid[gr].A1.x == aend[0].x && grid[gr].A1.y == aend[0].y &&
		grid[gr].A2.x == aend[1].x && grid[gr].A2.y == aend[1].y) ||
		(grid[gr].A2.x == aend[0].x && grid[gr].A2.y == aend[0].y &&
		grid[gr].A1.x == aend[1].x && grid[gr].A1.y == aend[1].y))
		&&

		((grid[gr].B1.x == bend[0].x && grid[gr].B1.y == bend[0].y &&
		grid[gr].B2.x == bend[1].x && grid[gr].B2.y == bend[1].y) ||
		(grid[gr].B2.x == bend[0].x && grid[gr].B2.y == bend[0].y &&
		grid[gr].B1.x == bend[1].x && grid[gr].B1.y == bend[1].y))
		&&

		((grid[gr].C1.x == cend[0].x && grid[gr].C1.y == cend[0].y &&
		grid[gr].C2.x == cend[1].x && grid[gr].C2.y == cend[1].y) ||
		(grid[gr].C2.x == cend[0].x && grid[gr].C2.y == cend[0].y &&
		grid[gr].C1.x == cend[1].x && grid[gr].C1.y == cend[1].y))
		&&

		((grid[gr].D1.x == dend[0].x && grid[gr].D1.y == dend[0].y &&
		grid[gr].D2.x == dend[1].x && grid[gr].D2.y == dend[1].y) ||
		(grid[gr].D2.x == dend[0].x && grid[gr].D2.y == dend[0].y &&
		grid[gr].D1.x == dend[1].x && grid[gr].D1.y == dend[1].y))
	) {
		return 1;	
	}
	return 0;


}
int samePoses(int gr) {
	int xxes[8];
	int yyes[8];

	printf("\n\n\n\n\nnumgrids %d\n", numgrids);

	xxes[0] = grid[gr].A1.x;
	xxes[1] = grid[gr].A2.x;
	xxes[2] = grid[gr].B1.x;
	xxes[3] = grid[gr].B2.x;
	xxes[4] = grid[gr].C1.x;
	xxes[5] = grid[gr].C2.x;
	xxes[6] = grid[gr].D1.x;
	xxes[7] = grid[gr].D2.x;

	yyes[0] = grid[gr].A1.y;
	yyes[1] = grid[gr].A2.y;
	yyes[2] = grid[gr].B1.y;
	yyes[3] = grid[gr].B2.y;
	yyes[4] = grid[gr].C1.y;
	yyes[5] = grid[gr].C2.y;
	yyes[6] = grid[gr].D1.y;
	yyes[7] = grid[gr].D2.y;

	printf("\n\n\n\n%d %d %d\n", inCorridor(gr, 'A'), ((grid[gr].A1.x ==  origA1x && grid[gr].A1.y == origA1y) || (grid[gr].A2.x == origA1x && grid[gr].A2.y == origA1x)), inHome(gr, 'A'));
	printf("grid[gr].A1.x is %d\n", grid[gr].A1.x);
	printf("grid[gr].A1.y is %d\n", grid[gr].A1.y);
	assert ((inCorridor(gr, 'A')  || (grid[gr].A1.x ==  origA1x && grid[gr].A1.y == origA1y) || inHome(gr, 'A')) == 1); 
	assert ((inCorridor(gr, 'a')  || (grid[gr].A2.x ==  origA2x && grid[gr].A2.y == origA2y) || inHome(gr, 'a')) == 1); 
	assert ((inCorridor(gr, 'B')  || (grid[gr].B1.x ==  origB1x && grid[gr].B1.y == origB1y) || inHome(gr, 'B')) == 1); 
	assert ((inCorridor(gr, 'b')  || (grid[gr].B2.x ==  origB2x && grid[gr].B2.y == origB2y) || inHome(gr, 'b')) == 1); 
	assert ((inCorridor(gr, 'C')  || (grid[gr].C1.x ==  origC1x && grid[gr].C1.y == origC1y) || inHome(gr, 'C')) == 1); 
	assert ((inCorridor(gr, 'c')  || (grid[gr].C2.x ==  origC2x && grid[gr].C2.y == origC2y) || inHome(gr, 'c')) == 1); 
	assert ((inCorridor(gr, 'D')  || (grid[gr].D1.x ==  origD1x && grid[gr].D1.y == origD1y) || inHome(gr, 'D')) == 1); 
	assert ((inCorridor(gr, 'd')  || (grid[gr].D2.x ==  origD2x && grid[gr].D2.y == origD2y) || inHome(gr, 'd')) == 1); 
	

	for (int i = 0; i < notCorridorLen; i++) {
		assert (!(grid[gr].A1.x == notCorridor[i].x && grid[gr].A1.y == notCorridor[i].y));
		assert (!(grid[gr].A2.x == notCorridor[i].x && grid[gr].A2.y == notCorridor[i].y));
		assert (!(grid[gr].B1.x == notCorridor[i].x && grid[gr].B1.y == notCorridor[i].y));
		assert (!(grid[gr].B2.x == notCorridor[i].x && grid[gr].B2.y == notCorridor[i].y));
		assert (!(grid[gr].C1.x == notCorridor[i].x && grid[gr].C1.y == notCorridor[i].y));
		assert (!(grid[gr].C2.x == notCorridor[i].x && grid[gr].C2.y == notCorridor[i].y));
		assert (!(grid[gr].D1.x == notCorridor[i].x && grid[gr].D1.y == notCorridor[i].y));
		assert (!(grid[gr].D2.x == notCorridor[i].x && grid[gr].D2.y == notCorridor[i].y));
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == j) {continue;}
			assert(yyes[i] >=0 && yyes[i] <= 2);
			assert(xxes[i] >=1 && xxes[i] <= 11);
			if (xxes[i] == xxes[j] && yyes[i] == xxes[j]) {
				return 1;
			}
		}
	}
	return 0;
}
void printGrid(int gr) {
	int xxes[10]; int yyes[10];
	xxes[0] = grid[gr].A1.x;
	xxes[1] = grid[gr].A2.x;
	xxes[2] = grid[gr].B1.x;
	xxes[3] = grid[gr].B2.x;
	xxes[4] = grid[gr].C1.x;
	xxes[5] = grid[gr].C2.x;
	xxes[6] = grid[gr].D1.x;
	xxes[7] = grid[gr].D2.x;

	yyes[0] = grid[gr].A1.y;
	yyes[1] = grid[gr].A2.y;
	yyes[2] = grid[gr].B1.y;
	yyes[3] = grid[gr].B2.y;
	yyes[4] = grid[gr].C1.y;
	yyes[5] = grid[gr].C2.y;
	yyes[6] = grid[gr].D1.y;
	yyes[7] = grid[gr].D2.y;
	
	int pOffset = 2;
        printf("\x1b[2J");
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBA", grid[gr].A1.x+pOffset, grid[gr].A1.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBa", grid[gr].A2.x+pOffset, grid[gr].A2.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBB", grid[gr].B1.x+pOffset, grid[gr].B1.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBb", grid[gr].B2.x+pOffset, grid[gr].B2.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBC", grid[gr].C1.x+pOffset, grid[gr].C1.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBc", grid[gr].C2.x+pOffset, grid[gr].C2.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBD", grid[gr].D1.x+pOffset, grid[gr].D1.y+pOffset);
        printf("\x1b[H");
	printf("\x1b[%dC \x1b[%dBd", grid[gr].D2.x+pOffset, grid[gr].D2.y+pOffset);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == j) {continue;}
			if (xxes[i] == xxes[j]) {
				if (yyes[i] == yyes[j]) {
					printf("\n\n\n\n\nERR %d V %d same %d %d %d %d\n", i, j, xxes[i], xxes[j], yyes[i], yyes[j]); exit(0);
				}
			}
		}
	}
}

int makemove(int g, char wat) {
	char fir;
	char sec;
	switch(wat) {
		case 'A':
			fir = 'A'; sec = 'a';
			break;
		case 'a':
			fir = 'a'; sec = 'A';
			break;
		case 'B':
			fir = 'B'; sec = 'b';
			break;
		case 'b':
			fir = 'b'; sec = 'B';
			break;
		case 'C':
			fir = 'C'; sec = 'c';
			break;
		case 'c':
			fir = 'c'; sec = 'C';
			break;
		case 'D':
			fir = 'D'; sec = 'd';
			break;
		case 'd':
			fir = 'd'; sec = 'D';
			break;
	}

/*
	if (inHomeOther(g, fir) && inHomeBottom(g, sec) && blankHomeOtherTop(g, fir) && !blockedFromHomeCorr(g, fir)) {
		dupGrid(g);
		makeMoveStraitHome(numgrids-1, fir);
		return 1;
	} else if (inHomeOther(g, fir) && blankBottom(g, fir) && !blockedFromHomeCorr(g, fir)) {
		dupGrid(g);
		makeMoveStraitHome(numgrids-1, fir);
		return 1;
	} else */

	if (inCorridor(g, fir) && inHomeBottom(g, sec) && blankTop(g, fir) && !blockedFromHomeCorr(g, fir)) {
		dupGrid(g);
		makeMoveHome(numgrids-1, fir);
		return 1;
	}
	if (inCorridor(g, fir)  && blankTop(g, fir) && (inHomeBottom(g, sec) || blankBottom(g, fir)) && !blockedFromHomeCorr(g, fir)) {
		dupGrid(g);
		makeMoveHome(numgrids-1, fir);
		return 1;
	} 
	if ((inHomeTop(g, fir) && inHomeBottom(g, sec)) || inHomeBottom(g, fir)) {
		return 0;
	}
	if (inHomeTop(g, fir) && !inHomeBottom(g, sec)) {
		int retBlock = blockedToCorr(g, fir);
		int ans;
		int ret = 0;
		for (int i = 0; i < 7; i++) {
			if ((ans = (retBlock & (1 << i))) > 0) {
				dupGrid(g);
				assert(ans == 1 || ans == 2 || ans == 4 || ans == 8 || ans == 16 || ans == 32 || ans == 64);
				makeMoveCorridor(numgrids-1, fir, ans);
				if (ret != 1) {ret = 1;}
			}
		}
		return ret;
	}

	if (inHomeOther(g, fir) || (inHomeOther(g, fir) && inHomeOtherBottom(g, fir) && blankHomeOtherTop(g, fir))) {
		int retBlock = blockedToCorr(g, fir);
		int ans;
		int ret = 0;
		for (int i = 0; i < 7; i++) {
			if ((ans = (retBlock & (1 << i))) > 0) {
				dupGrid(g);
				assert(ans == 1 || ans == 2 || ans == 4 || ans == 8 || ans == 16 || ans == 32 || ans == 64);
				makeMoveCorridor(numgrids-1, fir, ans);
				if (ret != 1) {ret = 1;}
			}
		}
		return ret;
	}
		
	return 0;
}

int blankHomeOtherTop(int gr, char wat) {
	int val_x;
	int val_y; 
	switch (wat) {
		case 'A':
			val_x = grid[gr].A1.x; val_y = grid[gr].A1.y;
			break;
		case 'a':
			val_x = grid[gr].A2.x; val_y = grid[gr].A2.y;
			break;
		case 'B':
			val_x = grid[gr].B1.x; val_y = grid[gr].B1.y;
			break;
		case 'b':
			val_x = grid[gr].B2.x; val_y = grid[gr].B2.y;
			break;
		case 'C':
			val_x = grid[gr].C1.x; val_y = grid[gr].C1.y;
			break;
		case 'c':
			val_x = grid[gr].C2.x; val_y = grid[gr].C2.y;
			break;
		case 'D':
			val_x = grid[gr].D1.x; val_y = grid[gr].D1.y;
			break;
		case 'd':
			val_x = grid[gr].D2.x; val_y = grid[gr].D2.y;
			break;
	}

	assert(val_y == 2);
	if ((grid[gr].A1.x == val_x && grid[gr].A1.y == val_y-1) ||
		(grid[gr].A2.x == val_x && grid[gr].A2.y == val_y-1) ||
		(grid[gr].B1.x == val_x && grid[gr].B1.y == val_y-1) ||
		(grid[gr].B2.x == val_x && grid[gr].B2.y == val_y-1) ||
		(grid[gr].C1.x == val_x && grid[gr].C1.y == val_y-1) ||
		(grid[gr].C2.x == val_x && grid[gr].C2.y == val_y-1) ||
		(grid[gr].D1.x == val_x && grid[gr].D1.y == val_y-1) ||
		(grid[gr].D2.x == val_x && grid[gr].D2.y == val_y-1)) {
			return 0;
	} else {
		return 1;
	}

}
void makeMoveCorridor(int gr, char wat, int which) {
	int x_pos = 0;
	switch (which) {
		case 1:
			x_pos = 1;
			break;
		case 2:
			x_pos = 2;
			break;
		case 4:
			x_pos = 4; 
			break;
		case 8:
			x_pos = 6;
			break;
		case 16:
			x_pos = 8;
			break;
		case 32:
			x_pos = 10;
			break;
		case 64:
			x_pos = 11;
			break;
		default:
			perror("not here\n");
			exit(0);
			break;
		
	}
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	int prevScore = grid[gr].score;
	int xscore = 0; int yscore = 0;
	switch (wat) {
		case 'A':
			{
			int xdist = abs(grid[gr].A1.x - x_pos);
			xscore = xdist * SCOREA;	
			int ydist = abs(grid[gr].A1.y); 
			yscore = ydist * SCOREA;

			grid[gr].A1.x = x_pos; grid[gr].A1.y = 0;
			assert(ydist == 2 || ydist == 1);
			}
			break;
		case 'a':
			{
			int xdist = abs(grid[gr].A2.x - x_pos);
			xscore = xdist * SCOREA ;	
			int ydist = abs(grid[gr].A2.y); 
			yscore = ydist * SCOREA;
			grid[gr].A2.x = x_pos; grid[gr].A2.y = 0;
			assert(ydist == 2 || ydist == 1);
			}
			break;
		case 'B':
			{
			int xdist = abs(grid[gr].B1.x - x_pos);
			xscore = xdist * SCOREB;	
			int ydist = abs(grid[gr].B1.y); 
			yscore = ydist * SCOREB;
			grid[gr].B1.x = x_pos; grid[gr].B1.y = 0;
			assert(ydist == 2 || ydist == 1);
			}
			break;
		case 'b':
			{
			int xdist = abs(grid[gr].B2.x - x_pos);
			xscore = xdist * SCOREB;	
			int ydist = abs(grid[gr].B2.y); 
			yscore = ydist * SCOREB;
			grid[gr].B2.x = x_pos; grid[gr].B2.y = 0;
			assert(ydist == 2 || ydist == 1);
			}
			break;
		case 'C':
			{
			int xdist = abs(grid[gr].C1.x - x_pos);
			xscore = xdist * SCOREC;	
			int ydist = abs(grid[gr].C1.y); 
			yscore = ydist * SCOREC;
			grid[gr].C1.x = x_pos; grid[gr].C1.y = 0;
			assert(ydist == 2 || ydist == 1);
			}
			break;
		case 'c':
			{
			int xdist = abs(grid[gr].C2.x - x_pos);
			xscore = xdist * SCOREC;	
			int ydist = abs(grid[gr].C2.y); 
			yscore = ydist * SCOREC;
			assert(ydist == 2 || ydist == 1);
			grid[gr].C2.x = x_pos; grid[gr].C2.y = 0;
			}
			break;
		case 'D':
			{
			int xdist = abs(grid[gr].D1.x - x_pos);
			xscore = xdist * SCORED;	
			int ydist = abs(grid[gr].D1.y); 
			yscore = ydist * SCORED;
			assert(ydist == 2 || ydist == 1);
			grid[gr].D1.x = x_pos; grid[gr].D1.y = 0;
			}
			break;
		case 'd':
			{
			int xdist = abs(grid[gr].D2.x - x_pos);
			xscore = xdist * SCORED;	
			int ydist = abs(grid[gr].D2.y); 
			assert(ydist == 2 || ydist == 1);
			yscore = ydist * SCORED;
			grid[gr].D2.x = x_pos; grid[gr].D2.y = 0;
			}
			break;
	}
	grid[gr].score += xscore + yscore;
	for (int i = 0; i < numgrids-1; i++) {
		if (		(((grid[i].A1.x == grid[gr].A1.x && grid[i].A1.y == grid[gr].A1.y) &&
				(grid[i].A2.x == grid[gr].A2.x && grid[i].A2.y == grid[gr].A2.y)) ||
				((grid[i].A2.x == grid[gr].A1.x && grid[i].A2.y == grid[gr].A1.y) &&
				(grid[i].A1.x == grid[gr].A2.x && grid[i].A1.y == grid[gr].A2.y))) 
				&& 
	
				(((grid[i].B1.x == grid[gr].B1.x && grid[i].B1.y == grid[gr].B1.y) &&
				(grid[i].B2.x == grid[gr].B2.x && grid[i].B2.y == grid[gr].B2.y)) ||
				((grid[i].B2.x == grid[gr].B1.x && grid[i].B2.y == grid[gr].B1.y) &&
				(grid[i].B1.x == grid[gr].B2.x && grid[i].B1.y == grid[gr].B2.y))) 
				&&

				(((grid[i].C1.x == grid[gr].C1.x && grid[i].C1.y == grid[gr].C1.y) &&
				(grid[i].C2.x == grid[gr].C2.x && grid[i].C2.y == grid[gr].C2.y)) ||
				((grid[i].C2.x == grid[gr].C1.x && grid[i].C2.y == grid[gr].C1.y) &&
				(grid[i].C1.x == grid[gr].C2.x && grid[i].C1.y == grid[gr].C2.y)))
				 &&
				(((grid[i].D1.x == grid[gr].D1.x && grid[i].D1.y == grid[gr].D1.y) &&
				(grid[i].D2.x == grid[gr].D2.x && grid[i].D2.y == grid[gr].D2.y)) ||
				((grid[i].D2.x == grid[gr].D1.x && grid[i].D2.y == grid[gr].D1.y) &&
				(grid[i].D1.x == grid[gr].D2.x && grid[i].D1.y == grid[gr].D2.y)))  ) 
		{

			if (grid[i].score >= grid[gr].score) {grid[i].ignore = 1;} else {grid[gr].ignore = 1;}
		}
	}
	assert(prevScore != grid[gr].score);
}

int blockedToCorr(int gr, char  wat) {
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	int val_x;
	//int val_y; 
	switch (wat) {
		case 'A':
			val_x = grid[gr].A1.x; //val_y = grid[gr].A1.y;
			break;
		case 'a':
			val_x = grid[gr].A2.x; //val_y = grid[gr].A2.y;
			break;
		case 'B':
			val_x = grid[gr].B1.x; //val_y = grid[gr].B1.y;
			break;
		case 'b':
			val_x = grid[gr].B2.x; //val_y = grid[gr].B2.y;
			break;
		case 'C':
			val_x = grid[gr].C1.x; //val_y = grid[gr].C1.y;
			break;
		case 'c':
			val_x = grid[gr].C2.x; //val_y = grid[gr].C2.y;
			break;
		case 'D':
			val_x = grid[gr].D1.x; //val_y = grid[gr].D1.y;
			break;
		case 'd':
			val_x = grid[gr].D2.x; //val_y = grid[gr].D2.y;
			break;
	}

	//free to move to 1,0 is +1
	//free to move to 2,0 is +2 
	//free to move to 4,0 is +4
	//free to move to 6,0 is +8
	//free to move to 8,0 is +16
	//free to move to 10,0 is +32
	//free to move to 11,0 is +64

	int retVal = 0;
	if (val_x == 3) {
		if (isfree(gr, 1) && isfree(gr, 2)) {retVal += 1;} 
		if (isfree(gr, 2)) {retVal += 2;} 
		if (isfree(gr, 4)) {retVal += 4;} 
		if (isfree(gr, 6) && isfree(gr, 4)) {retVal += 8;} 
		if (isfree(gr, 8) && isfree(gr, 6) && isfree(gr, 4)) {retVal += 16;} 
		if (isfree(gr, 10) && isfree(gr, 8) && isfree(gr, 6) && isfree(gr, 4)) {retVal += 32;} 
		if (isfree(gr, 11) && isfree(gr, 10) && isfree(gr, 8) && isfree(gr, 6) && isfree(gr, 4)) {retVal += 64;} 
	} else if (val_x == 5) {
		if (isfree(gr, 1) && isfree(gr, 2) && isfree(gr, 4)) {retVal += 1;} 
		if (isfree(gr, 2) && isfree(gr, 4)) {retVal += 2;} 
		if (isfree(gr, 4)) {retVal += 4;} 
		if (isfree(gr, 6)) {retVal += 8;} 
		if (isfree(gr, 8) && isfree(gr, 6)) {retVal += 16;} 
		if (isfree(gr, 10) && isfree(gr, 8) && isfree(gr, 6)) {retVal += 32;} 
		if (isfree(gr, 11) && isfree(gr, 10) && isfree(gr, 8) && isfree(gr, 6)) {retVal += 64;} 
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},   HE   {10,0}, {11,0}};
	} else if (val_x == 7) {
		if (isfree(gr, 1) && isfree(gr, 2) && isfree(gr, 4) && isfree(gr, 6)) {retVal += 1;} 
		if (isfree(gr, 2) && isfree(gr, 4) && isfree(gr, 6)) {retVal += 2;} 
		if (isfree(gr, 4) && isfree(gr, 6)) {retVal += 4;} 
		if (isfree(gr, 6)) {retVal += 8;} 
		if (isfree(gr, 8))  {retVal += 16;} 
		if (isfree(gr, 10) && isfree(gr, 8)) {retVal += 32;} 
		if (isfree(gr, 11) && isfree(gr, 10) && isfree(gr, 8)) {retVal += 64;} 
	} else if (val_x == 9) {
		if (isfree(gr, 1) && isfree(gr, 2) && isfree(gr, 4) && isfree(gr, 6) && isfree(gr, 8)) {retVal += 1;} 
		if (isfree(gr, 2) && isfree(gr, 4) && isfree(gr, 6) && isfree(gr, 8)) {retVal += 2;} 
		if (isfree(gr, 4) && isfree(gr, 6) && isfree(gr, 8)) {retVal += 4;} 
		if (isfree(gr, 6) && isfree(gr, 8)) {retVal += 8;} 
		if (isfree(gr, 8))  {retVal += 16;} 
		if (isfree(gr, 10)) {retVal += 32;} 
		if (isfree(gr, 11) && isfree(gr, 10)) {retVal += 64;} 
	}
	return retVal;

}
int isfree(int gr, int xv) {
		if (grid[gr].A1.x == xv
			|| grid[gr].A2.x == xv
			|| grid[gr].B1.x == xv 
			|| grid[gr].B2.x == xv 
			|| grid[gr].C1.x == xv 
			|| grid[gr].C2.x == xv 
			|| grid[gr].D1.x == xv 
			|| grid[gr].D2.x == xv) {
			return 0;
		} else {
			return 1;
		}
}

void dupGrid(int gr) {
	if (numgrids+3000 > MAXNUMGRID) {dup2(fd,1); free(grid);perror("GRID"); printf("numgrids:%d minScore:%d\n", numgrids, minScore); dup2(fd, 1);exit(0);}
	grid[numgrids].A1.x = grid[gr].A1.x;
	grid[numgrids].A1.y = grid[gr].A1.y;

	grid[numgrids].A2.x = grid[gr].A2.x;
	grid[numgrids].A2.y = grid[gr].A2.y;

	grid[numgrids].B1.x = grid[gr].B1.x;
	grid[numgrids].B1.y = grid[gr].B1.y;

	grid[numgrids].B2.x = grid[gr].B2.x;
	grid[numgrids].B2.y = grid[gr].B2.y;

	grid[numgrids].C1.x = grid[gr].C1.x;
	grid[numgrids].C1.y = grid[gr].C1.y;

	grid[numgrids].C2.x = grid[gr].C2.x;
	grid[numgrids].C2.y = grid[gr].C2.y;

	grid[numgrids].D1.x = grid[gr].D1.x;
	grid[numgrids].D1.y = grid[gr].D1.y;

	grid[numgrids].D2.x = grid[gr].D2.x;
	grid[numgrids].D2.y = grid[gr].D2.y;
	
	grid[numgrids].score = grid[gr].score;
	grid[numgrids].ignore = 0;
	
	numgrids++;
}

void makeMoveStraitHome(int gr, char wat) {
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	int xscore = 0, yscore = 0;
	int prevScore = grid[gr].score;
	switch (wat) {
		case 'A':
			printf("\n\n\n\nmaking A move HOME\n");
			{
			int xdist = abs(grid[gr].A1.x - 3); xscore = xdist * SCOREA;
			int ydist = grid[gr].A1.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist += 2;
				grid[gr].A1.x = aend[0].x;
				grid[gr].A1.y = aend[0].y;
			} else if (inHome(gr, 'a')) {
				ydist += 1;
				grid[gr].A1.x = aend[1].x;
				grid[gr].A1.y = aend[1].y;
			}
			yscore = ydist * SCOREA;
			}
			break;
		case 'a':
			{
			int xdist = abs(grid[gr].A2.x - 3); xscore = xdist * SCOREA;
			int ydist = grid[gr].A2.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist += 2;
				grid[gr].A2.x = aend[0].x;
				grid[gr].A2.y = aend[0].y;
			} else if (inHome(gr, 'A')) {
				ydist += 1;
				grid[gr].A2.x = aend[1].x;
				grid[gr].A2.y = aend[1].y;
			}
			yscore = ydist * SCOREA;
			}
			break;
		case 'B':
			{
			int xdist = abs(grid[gr].B1.x - 5); xscore = xdist * SCOREB;
			int ydist = grid[gr].B1.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist+=2;
				grid[gr].B1.x = bend[0].x;
				grid[gr].B1.y = bend[0].y;
			} else if (inHome(gr, 'b')) {
				ydist += 1;
				grid[gr].B1.x = bend[1].x;
				grid[gr].B1.y = bend[1].y;
			}
			yscore = ydist * SCOREB;
			}
			break;
		case 'b':
			{
			int xdist = abs(grid[gr].B2.x - 5); xscore = xdist * SCOREB;	
			int ydist = grid[gr].B2.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist+=2;
				grid[gr].B2.x = bend[0].x;
				grid[gr].B2.y = bend[0].y;
			} else if (inHome(gr, 'B')) {
				ydist += 1;
				grid[gr].B2.x = bend[1].x;
				grid[gr].B2.y = bend[1].y;
			}
			yscore = ydist * SCOREB;
			}
			break;
		case 'C':
			{
			int xdist = abs(grid[gr].C1.x - 7); xscore = xdist * SCOREC;	
			int ydist = grid[gr].C1.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist+=2;
				grid[gr].C1.x = cend[0].x;
				grid[gr].C1.y = cend[0].y;
			} else if (inHome(gr, 'c')) {
				ydist += 1;
				grid[gr].C1.x = cend[1].x;
				grid[gr].C1.y = cend[1].y;
			}
			yscore = ydist * SCOREC;
			}
			break;
		case 'c':
			{
			int xdist = abs(grid[gr].C2.x - 7);xscore = xdist * SCOREC;
			int ydist = grid[gr].C2.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist+=2;
				grid[gr].C2.x = cend[0].x;
				grid[gr].C2.y = cend[0].y;
			} else if (inHome(gr, 'C')) {
				ydist += 1;
				grid[gr].C2.x = cend[1].x;
				grid[gr].C2.y = cend[1].y;
			}
			yscore = ydist * SCOREC;
			}
			break;
		case 'D':
			{
			int xdist = abs(grid[gr].D1.x - 9); xscore = xdist * SCORED;	
			int ydist =  grid[gr].D1.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist+=2;
				grid[gr].D1.x = dend[0].x;
				grid[gr].D1.y = dend[0].y;
			} else if (inHome(gr, 'd')) {
				ydist += 1;
				grid[gr].D1.x = dend[1].x;
				grid[gr].D1.y = dend[1].y;
			}
			yscore = ydist * SCORED;
			}
			break;
		case 'd':
			{
			int xdist = abs(grid[gr].D2.x - 9); xscore = xdist * SCORED;
			int ydist = grid[gr].D2.y;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				ydist+=2;
				grid[gr].D2.x = dend[0].x;
				grid[gr].D2.y = dend[0].y;
			} else if (inHome(gr, 'D')) {
				ydist += 1;
				grid[gr].D2.x = dend[1].x;
				grid[gr].D2.y = dend[1].y;
			}
			yscore = ydist * SCORED;
			}
			break;
	}
	grid[gr].score += xscore + yscore;
	for (int i = 0; i < numgrids-1; i++) {
		if (		(((grid[i].A1.x == grid[gr].A1.x && grid[i].A1.y == grid[gr].A1.y) &&
				(grid[i].A2.x == grid[gr].A2.x && grid[i].A2.y == grid[gr].A2.y)) ||
				((grid[i].A2.x == grid[gr].A1.x && grid[i].A2.y == grid[gr].A1.y) &&
				(grid[i].A1.x == grid[gr].A2.x && grid[i].A1.y == grid[gr].A2.y))) 
				&& 
	
				(((grid[i].B1.x == grid[gr].B1.x && grid[i].B1.y == grid[gr].B1.y) &&
				(grid[i].B2.x == grid[gr].B2.x && grid[i].B2.y == grid[gr].B2.y)) ||
				((grid[i].B2.x == grid[gr].B1.x && grid[i].B2.y == grid[gr].B1.y) &&
				(grid[i].B1.x == grid[gr].B2.x && grid[i].B1.y == grid[gr].B2.y))) 
				&&

				(((grid[i].C1.x == grid[gr].C1.x && grid[i].C1.y == grid[gr].C1.y) &&
				(grid[i].C2.x == grid[gr].C2.x && grid[i].C2.y == grid[gr].C2.y)) ||
				((grid[i].C2.x == grid[gr].C1.x && grid[i].C2.y == grid[gr].C1.y) &&
				(grid[i].C1.x == grid[gr].C2.x && grid[i].C1.y == grid[gr].C2.y)))
				 &&
				(((grid[i].D1.x == grid[gr].D1.x && grid[i].D1.y == grid[gr].D1.y) &&
				(grid[i].D2.x == grid[gr].D2.x && grid[i].D2.y == grid[gr].D2.y)) ||
				((grid[i].D2.x == grid[gr].D1.x && grid[i].D2.y == grid[gr].D1.y) &&
				(grid[i].D1.x == grid[gr].D2.x && grid[i].D1.y == grid[gr].D2.y)))  ) 
		{

			if (grid[i].score >= grid[gr].score) {grid[i].ignore = 1;} else {grid[gr].ignore = 1;}
		}
	}
	assert(prevScore != grid[gr].score);
}
void makeMoveHome(int gr, char wat) {
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	int xscore = 0, yscore = 0;
	int prevScore = grid[gr].score;
	switch (wat) {
		case 'A':
			{
			int xdist = abs(grid[gr].A1.x - 3); xscore = xdist * SCOREA;
			int ydist = 2;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].A1.x = aend[0].x;
				grid[gr].A1.y = aend[0].y;
			} else if (inHome(gr, 'a')) {
				ydist = 1;
				grid[gr].A1.x = aend[1].x;
				grid[gr].A1.y = aend[1].y;
			}
			yscore = ydist * SCOREA;
			}
			break;
		case 'a':
			{
			int xdist = abs(grid[gr].A2.x - 3); xscore = xdist * SCOREA;
			int ydist = 2;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].A2.x = aend[0].x;
				grid[gr].A2.y = aend[0].y;
			} else if (inHome(gr, 'A')) {
				ydist = 1;
				grid[gr].A2.x = aend[1].x;
				grid[gr].A2.y = aend[1].y;
			}
			yscore = ydist * SCOREA;
			}
			break;
		case 'B':
			{
			int xdist = abs(grid[gr].B1.x - 5); xscore = xdist * SCOREB;
			int ydist = 2;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].B1.x = bend[0].x;
				grid[gr].B1.y = bend[0].y;
			} else if (inHome(gr, 'b')) {
				ydist = 1;
				grid[gr].B1.x = bend[1].x;
				grid[gr].B1.y = bend[1].y;
			}
			yscore = ydist * SCOREB;
			}
			break;
		case 'b':
			{
			int xdist = abs(grid[gr].B2.x - 5); xscore = xdist * SCOREB;	
			int ydist = 2; 
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].B2.x = bend[0].x;
				grid[gr].B2.y = bend[0].y;
			} else if (inHome(gr, 'B')) {
				ydist = 1;
				grid[gr].B2.x = bend[1].x;
				grid[gr].B2.y = bend[1].y;
			}
			yscore = ydist * SCOREB;
			}
			break;
		case 'C':
			{
			int xdist = abs(grid[gr].C1.x - 7); xscore = xdist * SCOREC;	
			int ydist = 2;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].C1.x = cend[0].x;
				grid[gr].C1.y = cend[0].y;
			} else if (inHome(gr, 'c')) {
				ydist = 1;
				grid[gr].C1.x = cend[1].x;
				grid[gr].C1.y = cend[1].y;
			}
			yscore = ydist * SCOREC;
			}
			break;
		case 'c':
			{
			int xdist = abs(grid[gr].C2.x - 7); xscore = xdist * SCOREC;
			int ydist = 2;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].C2.x = cend[0].x;
				grid[gr].C2.y = cend[0].y;
			} else if (inHome(gr, 'C')) {
				ydist = 1;
				grid[gr].C2.x = cend[1].x;
				grid[gr].C2.y = cend[1].y;
			}
			yscore = ydist * SCOREC;
			}
			break;
		case 'D':
			{
			int xdist = abs(grid[gr].D1.x - 9); xscore = xdist * SCORED;	
			int ydist = 2; 
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].D1.x = dend[0].x;
				grid[gr].D1.y = dend[0].y;
			} else if (inHome(gr, 'd')) {
				ydist = 1;
				grid[gr].D1.x = dend[1].x;
				grid[gr].D1.y = dend[1].y;
			}
			yscore = ydist * SCORED;
			}
			break;
		case 'd':
			{
			int xdist = abs(grid[gr].D2.x - 9); xscore = xdist * SCORED;
			int ydist = 2;
			if (blankTop(gr, wat) && blankBottom(gr, wat)) {
				grid[gr].D2.x = dend[0].x;
				grid[gr].D2.y = dend[0].y;
			} else if (inHome(gr, 'D')) {
				ydist = 1;
				grid[gr].D2.x = dend[1].x;
				grid[gr].D2.y = dend[1].y;
			}
			yscore = ydist * SCORED;
			}
			break;
	}
	grid[gr].score += xscore + yscore;
	for (int i = 0; i < numgrids-1; i++) {
		if (		(((grid[i].A1.x == grid[gr].A1.x && grid[i].A1.y == grid[gr].A1.y) &&
				(grid[i].A2.x == grid[gr].A2.x && grid[i].A2.y == grid[gr].A2.y)) ||
				((grid[i].A2.x == grid[gr].A1.x && grid[i].A2.y == grid[gr].A1.y) &&
				(grid[i].A1.x == grid[gr].A2.x && grid[i].A1.y == grid[gr].A2.y))) 
				&& 
	
				(((grid[i].B1.x == grid[gr].B1.x && grid[i].B1.y == grid[gr].B1.y) &&
				(grid[i].B2.x == grid[gr].B2.x && grid[i].B2.y == grid[gr].B2.y)) ||
				((grid[i].B2.x == grid[gr].B1.x && grid[i].B2.y == grid[gr].B1.y) &&
				(grid[i].B1.x == grid[gr].B2.x && grid[i].B1.y == grid[gr].B2.y))) 
				&&

				(((grid[i].C1.x == grid[gr].C1.x && grid[i].C1.y == grid[gr].C1.y) &&
				(grid[i].C2.x == grid[gr].C2.x && grid[i].C2.y == grid[gr].C2.y)) ||
				((grid[i].C2.x == grid[gr].C1.x && grid[i].C2.y == grid[gr].C1.y) &&
				(grid[i].C1.x == grid[gr].C2.x && grid[i].C1.y == grid[gr].C2.y)))
				 &&
				(((grid[i].D1.x == grid[gr].D1.x && grid[i].D1.y == grid[gr].D1.y) &&
				(grid[i].D2.x == grid[gr].D2.x && grid[i].D2.y == grid[gr].D2.y)) ||
				((grid[i].D2.x == grid[gr].D1.x && grid[i].D2.y == grid[gr].D1.y) &&
				(grid[i].D1.x == grid[gr].D2.x && grid[i].D1.y == grid[gr].D2.y)))  ) 
		{

			if (grid[i].score >= grid[gr].score) {grid[i].ignore = 1;} else {grid[gr].ignore = 1;}
		}
	}
	assert(prevScore != grid[gr].score);
}

int blockedFromHomeCorr(int gr, char wat) {//blocked from going home
	assert(inCorridor(gr, wat));
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};

	switch (wat) {
		case 'A': 
			{
			int var_x = grid[gr].A1.x, var_y = grid[gr].A1.y;
			///if any others are in certain corr places then (also depends on where i am in corr)
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A2.x == 2 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
					return 0;
			} else if (var_x == 4 && var_y == 0) { //cant be blocked
					return 0;
			} else if (var_x == 6 && var_y == 0) {
				if ((grid[gr].A2.x == 4 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 8 && var_y == 0) {
				if ((grid[gr].A2.x == 4 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A2.x == 6 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 10 && var_y == 0) {
				if ((grid[gr].A2.x == 4 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A2.x == 6 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A2.x == 8 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A2.x == 4 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A2.x == 6 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A2.x == 8 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A2.x == 10 && grid[gr].A2.y == 0) 
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'a':
			{
			int var_x = grid[gr].A2.x, var_y = grid[gr].A2.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
					return 0;
			} else if (var_x == 4 && var_y == 0) { //cant be blocked
					return 0;
			} else if (var_x == 6 && var_y == 0) {
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 8 && var_y == 0) {
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 10 && var_y == 0) {
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'B':
			{
			int var_x = grid[gr].B1.x, var_y = grid[gr].B1.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 2 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 4 && var_y == 0) { //cant be blocked
				return 0;
			} else if (var_x == 6 && var_y == 0) { //cant be blocked
				return 0;
			} else if (var_x == 8 && var_y == 0) {
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 10 && var_y == 0) {
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 10 && grid[gr].A2.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'b':
			{
			int var_x = grid[gr].B2.x, var_y = grid[gr].B2.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 2 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 4 && var_y == 0) { //cant be blocked
				return 0;
			} else if (var_x == 6 && var_y == 0) { //cant be blocked
				return 0;
			} else if (var_x == 8 && var_y == 0) {
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 10 && var_y == 0) {
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 10 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'C':
			{
			int var_x = grid[gr].C1.x, var_y = grid[gr].C1.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 2 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 4 && var_y == 0) { 
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 6 && var_y == 0) {
				return 0;
			} else if (var_x == 8 && var_y == 0) {
				return 0;
			} else if (var_x == 10 && var_y == 0) {
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 10 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'c':
			{
			int var_x = grid[gr].C2.x, var_y = grid[gr].C2.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 2 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 4 && var_y == 0) { 
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 6 && var_y == 0) {
				return 0;
			} else if (var_x == 8 && var_y == 0) {
				return 0;
			} else if (var_x == 10 && var_y == 0) {
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 10 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'D':
			{
			int var_x = grid[gr].D1.x, var_y = grid[gr].D1.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 2 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 2 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 4 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 4 && var_y == 0) { 
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 6 && grid[gr].D2.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 6 && var_y == 0) {
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 8 && grid[gr].D2.y == 0)) {
					return 1;
				}
			} else if (var_x == 8 && var_y == 0) {
				return 0;
			} else if (var_x == 10 && var_y == 0) {
				return 0;
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 10 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D2.x == 10 && grid[gr].D2.y == 0)) {
					return 1;
				}
			}
			}
			break;
		case 'd':
			{
			int var_x = grid[gr].D2.x, var_y = grid[gr].D2.y;
			if (var_x == 1 && var_y == 0) {
				if ((grid[gr].A1.x == 2 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 2 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 2 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 2 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 2 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 2 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 2 && grid[gr].D1.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)) {
					return 1;
				}
			} else if (var_x == 2 && var_y == 0) { //cant be blocked
				if ((grid[gr].A1.x == 4 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 4 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 4 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 4 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 4 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 4 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 4 && grid[gr].D1.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)) {
					return 1;
				}
			} else if (var_x == 4 && var_y == 0) { 
				if ((grid[gr].A1.x == 6 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 6 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 6 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 6 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 6 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 6 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 6 && grid[gr].D1.y == 0)) {
					return 1;
				}
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)) {
					return 1;
				}
			} else if (var_x == 6 && var_y == 0) {
				if ((grid[gr].A1.x == 8 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 8 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 8 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 8 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 8 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 8 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 8 && grid[gr].D1.y == 0)) {
					return 1;
				}
			} else if (var_x == 8 && var_y == 0) {
				return 0;
			} else if (var_x == 10 && var_y == 0) {
				return 0;
			} else if (var_x == 11 && var_y == 0) {
				if ((grid[gr].A1.x == 10 && grid[gr].A1.y == 0) 
					|| (grid[gr].A2.x == 10 && grid[gr].A2.y == 0)
					|| (grid[gr].B1.x == 10 && grid[gr].B1.y == 0)
					|| (grid[gr].B2.x == 10 && grid[gr].B2.y == 0)
					|| (grid[gr].C1.x == 10 && grid[gr].C1.y == 0)
					|| (grid[gr].C2.x == 10 && grid[gr].C2.y == 0)
					|| (grid[gr].D1.x == 10 && grid[gr].D1.y == 0)) {
					return 1;
				}
			}
			}
			break;
		}
	return 0;
}
	

int inHome(int gr, char wat) {
	switch(wat) {
		case 'A': if ((grid[gr].A1.x == aend[0].x && grid[gr].A1.y == aend[0].y) || ((grid[gr].A1.x == aend[1].x && grid[gr].A1.y == aend[1].y) 
				&& (grid[gr].A2.x == aend[0].x && grid[gr].A2.y == aend[0].y)) ) {return 1;}
			break;
		case 'a': if ((grid[gr].A2.x == aend[0].x && grid[gr].A2.y == aend[0].y) || ((grid[gr].A2.x == aend[1].x && grid[gr].A2.y == aend[1].y)
				&& (grid[gr].A1.x == aend[0].x && grid[gr].A1.y == aend[0].y)) ) {return 1;}
			break;
		case 'B': if ((grid[gr].B1.x == bend[0].x && grid[gr].B1.y == bend[0].y) || ((grid[gr].B1.x == bend[1].x && grid[gr].B1.y == bend[1].y)
				&& (grid[gr].B2.x == bend[0].x && grid[gr].B2.y == bend[0].y)) ) {return 1;}
			break;
		case 'b': if ((grid[gr].B2.x == bend[0].x && grid[gr].B2.y == bend[0].y) || ((grid[gr].B2.x == bend[1].x && grid[gr].B2.y == bend[1].y)
				&& (grid[gr].B1.x == bend[0].x && grid[gr].B1.y == bend[0].y)) ) {return 1;}
			break;
		case 'C': if ((grid[gr].C1.x == cend[0].x && grid[gr].C1.y == cend[0].y) || ((grid[gr].C1.x == cend[1].x && grid[gr].C1.y == cend[1].y)
				&& (grid[gr].C2.x == cend[0].x && grid[gr].C2.y == cend[0].y)) ) {return 1;}
			break;
		case 'c': if ((grid[gr].C2.x == cend[0].x && grid[gr].C2.y == cend[0].y) || ((grid[gr].C2.x == cend[1].x && grid[gr].C2.y == cend[1].y)
				&& (grid[gr].C1.x == cend[0].x && grid[gr].C1.y == cend[0].y)) ) {return 1;}
			break;
		case 'D': if ((grid[gr].D1.x == dend[0].x && grid[gr].D1.y == dend[0].y) || ((grid[gr].D1.x == dend[1].x && grid[gr].D1.y == dend[1].y)
				&& (grid[gr].D2.x == dend[0].x && grid[gr].D2.y == dend[0].y)) ) {return 1;}
			break;
		case 'd': if ((grid[gr].D2.x == dend[0].x && grid[gr].D2.y == dend[0].y) || ((grid[gr].D2.x == dend[1].x && grid[gr].D2.y == dend[1].y)
				&& (grid[gr].D1.x == dend[0].x && grid[gr].D1.y == dend[0].y)) ) {return 1;}
			break;
	}
	return 0;
}

int inHomeOtherTop(int gr, char wat) {
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	switch(wat) {
		case 'A':
			if ((grid[gr].A1.x == 5 || grid[gr].A1.x == 7 || grid[gr].A1.x == 9) && grid[gr].A1.y == 1) {return 1;}
			break;
		case 'a':
			if ((grid[gr].A2.x == 5 || grid[gr].A2.x == 7 || grid[gr].A2.x == 9) && grid[gr].A2.y == 1) {return 1;}
			break;
		case 'B':
			if ((grid[gr].B1.x == 3 || grid[gr].B1.x == 7 || grid[gr].B1.x == 9) && grid[gr].B1.y == 1) {return 1;}
			break;
		case 'b':
			if ((grid[gr].B2.x == 3 || grid[gr].B2.x == 7 || grid[gr].B2.x == 9) && grid[gr].B2.y == 1) {return 1;}
			break;
		case 'C':
			if ((grid[gr].C1.x == 3 || grid[gr].C1.x == 5 || grid[gr].C1.x == 9) && grid[gr].C1.y == 1) {return 1;}
			break;
		case 'c':
			if ((grid[gr].C2.x == 3 || grid[gr].C2.x == 5 || grid[gr].C2.x == 9) && grid[gr].C2.y == 1) {return 1;}
			break;
		case 'D':
			if ((grid[gr].D1.x == 3 || grid[gr].D1.x == 5 || grid[gr].D1.x == 7) && grid[gr].D1.y == 1) {return 1;}
			break;
		case 'd':
			if ((grid[gr].D2.x == 3 || grid[gr].D2.x == 5 || grid[gr].D2.x == 7) && grid[gr].D2.y == 1) {return 1;}
			break;
	}
	return 0;
}
int inHomeOtherBottom(int gr, char wat) {
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	switch(wat) {
		case 'A':
			if ((grid[gr].A1.x == 5 || grid[gr].A1.x == 7 || grid[gr].A1.x == 9) && grid[gr].A1.y == 2) {return 1;}
			break;
		case 'a':
			if ((grid[gr].A2.x == 5 || grid[gr].A2.x == 7 || grid[gr].A2.x == 9) && grid[gr].A2.y == 2) {return 1;}
			break;
		case 'B':
			if ((grid[gr].B1.x == 3 || grid[gr].B1.x == 7 || grid[gr].B1.x == 9) && grid[gr].B1.y == 2) {return 1;}
			break;
		case 'b':
			if ((grid[gr].B2.x == 3 || grid[gr].B2.x == 7 || grid[gr].B2.x == 9) && grid[gr].B2.y == 2) {return 1;}
			break;
		case 'C':
			if ((grid[gr].C1.x == 3 || grid[gr].C1.x == 5 || grid[gr].C1.x == 9) && grid[gr].C1.y == 2) {return 1;}
			break;
		case 'c':
			if ((grid[gr].C2.x == 3 || grid[gr].C2.x == 5 || grid[gr].C2.x == 9) && grid[gr].C2.y == 2) {return 1;}
			break;
		case 'D':
			if ((grid[gr].D1.x == 3 || grid[gr].D1.x == 5 || grid[gr].D1.x == 7) && grid[gr].D1.y == 2) {return 1;}
			break;
		case 'd':
			if ((grid[gr].D2.x == 3 || grid[gr].D2.x == 5 || grid[gr].D2.x == 7) && grid[gr].D2.y == 2) {return 1;}
			break;
	}
	return 0;
}
int inHomeOther(int gr, char wat) {
	//pos_s corridor[] {{1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}};
	//pos_s corridor[] {{1,0}, {2,0},        {4,0},        {6,0},        {8,0},        {10,0}, {11,0}};
	switch(wat) {
		case 'A':
			if (grid[gr].A1.x == 5 || grid[gr].A1.x == 7 || grid[gr].A1.x == 9) {return 1;}
			break;
		case 'a':
			if (grid[gr].A2.x == 5 || grid[gr].A2.x == 7 || grid[gr].A2.x == 9) {return 1;}
			break;
		case 'B':
			if (grid[gr].B1.x == 3 || grid[gr].B1.x == 7 || grid[gr].B1.x == 9) {return 1;}
			break;
		case 'b':
			if (grid[gr].B2.x == 3 || grid[gr].B2.x == 7 || grid[gr].B2.x == 9) {return 1;}
			break;
		case 'C':
			if (grid[gr].C1.x == 3 || grid[gr].C1.x == 5 || grid[gr].C1.x == 9) {return 1;}
			break;
		case 'c':
			if (grid[gr].C2.x == 3 || grid[gr].C2.x == 5 || grid[gr].C2.x == 9) {return 1;}
			break;
		case 'D':
			if (grid[gr].D1.x == 3 || grid[gr].D1.x == 5 || grid[gr].D1.x == 7) {return 1;}
			break;
		case 'd':
			if (grid[gr].D2.x == 3 || grid[gr].D2.x == 5 || grid[gr].D2.x == 7) {return 1;}
			break;
	}
	return 0;
}
int inHomeTop(int gr, char wat) {
	switch(wat) {
		case 'A': if (grid[gr].A1.x == aend[1].x && grid[gr].A1.y == aend[1].y) {return 1;}
			break;
		case 'a': if (grid[gr].A2.x == aend[1].x && grid[gr].A2.y == aend[1].y) {return 1;}
			break;
		case 'B': if (grid[gr].B1.x == bend[1].x && grid[gr].B1.y == bend[1].y) {return 1;}
			break;
		case 'b': if (grid[gr].B2.x == bend[1].x && grid[gr].B2.y == bend[1].y) {return 1;}
			break;
		case 'C': if (grid[gr].C1.x == cend[1].x && grid[gr].C1.y == cend[1].y) {return 1;}
			break;
		case 'c': if (grid[gr].C2.x == cend[1].x && grid[gr].C2.y == cend[1].y) {return 1;}
			break;
		case 'D': if (grid[gr].D1.x == dend[1].x && grid[gr].D1.y == dend[1].y) {return 1;}
			break;
		case 'd': if (grid[gr].D2.x == dend[1].x && grid[gr].D2.y == dend[1].y) {return 1;}
			break;
	}
	return 0;
}

int blankTop(int gr, char wat) {
	switch(wat) {
		case 'A': 
		case 'a':
			if (grid[gr].A1.x == aend[1].x && grid[gr].A1.y == aend[1].y) {return 0;}
			if (grid[gr].A2.x == aend[1].x && grid[gr].A2.y == aend[1].y) {return 0;}
			if (grid[gr].B1.x == aend[1].x && grid[gr].B1.y == aend[1].y) {return 0;}
			if (grid[gr].B2.x == aend[1].x && grid[gr].B2.y == aend[1].y) {return 0;}
			if (grid[gr].C1.x == aend[1].x && grid[gr].C1.y == aend[1].y) {return 0;}
			if (grid[gr].C2.x == aend[1].x && grid[gr].C2.y == aend[1].y) {return 0;}
			if (grid[gr].D1.x == aend[1].x && grid[gr].D1.y == aend[1].y) {return 0;}
			if (grid[gr].D2.x == aend[1].x && grid[gr].D2.y == aend[1].y) {return 0;}
			break;
		case 'B':
		case 'b':
			if (grid[gr].A1.x == bend[1].x && grid[gr].A1.y == bend[1].y) {return 0;}
			if (grid[gr].A2.x == bend[1].x && grid[gr].A2.y == bend[1].y) {return 0;}
			if (grid[gr].B1.x == bend[1].x && grid[gr].B1.y == bend[1].y) {return 0;}
			if (grid[gr].B2.x == bend[1].x && grid[gr].B2.y == bend[1].y) {return 0;}
			if (grid[gr].C1.x == bend[1].x && grid[gr].C1.y == bend[1].y) {return 0;}
			if (grid[gr].C2.x == bend[1].x && grid[gr].C2.y == bend[1].y) {return 0;}
			if (grid[gr].D1.x == bend[1].x && grid[gr].D1.y == bend[1].y) {return 0;}
			if (grid[gr].D2.x == bend[1].x && grid[gr].D2.y == bend[1].y) {return 0;}
			break;
		case 'C':
		case 'c':
			if (grid[gr].A1.x == cend[1].x && grid[gr].A1.y == cend[1].y) {return 0;}
			if (grid[gr].A2.x == cend[1].x && grid[gr].A2.y == cend[1].y) {return 0;}
			if (grid[gr].B1.x == cend[1].x && grid[gr].B1.y == cend[1].y) {return 0;}
			if (grid[gr].B2.x == cend[1].x && grid[gr].B2.y == cend[1].y) {return 0;}
			if (grid[gr].C1.x == cend[1].x && grid[gr].C1.y == cend[1].y) {return 0;}
			if (grid[gr].C2.x == cend[1].x && grid[gr].C2.y == cend[1].y) {return 0;}
			if (grid[gr].D1.x == cend[1].x && grid[gr].D1.y == cend[1].y) {return 0;}
			if (grid[gr].D2.x == cend[1].x && grid[gr].D2.y == cend[1].y) {return 0;}
			break;
		case 'D':
		case 'd':
			if (grid[gr].A1.x == dend[1].x && grid[gr].A1.y == dend[1].y) {return 0;}
			if (grid[gr].A2.x == dend[1].x && grid[gr].A2.y == dend[1].y) {return 0;}
			if (grid[gr].B1.x == dend[1].x && grid[gr].B1.y == dend[1].y) {return 0;}
			if (grid[gr].B2.x == dend[1].x && grid[gr].B2.y == dend[1].y) {return 0;}
			if (grid[gr].C1.x == dend[1].x && grid[gr].C1.y == dend[1].y) {return 0;}
			if (grid[gr].C2.x == dend[1].x && grid[gr].C2.y == dend[1].y) {return 0;}
			if (grid[gr].D1.x == dend[1].x && grid[gr].D1.y == dend[1].y) {return 0;}
			if (grid[gr].D2.x == dend[1].x && grid[gr].D2.y == dend[1].y) {return 0;}
			break;
	}
	return 1;
}
int blankBottom(int gr, char wat) {
	switch(wat) {
		case 'A': 
		case 'a':
			if (grid[gr].A1.x == aend[0].x && grid[gr].A1.y == aend[0].y) {return 0;}
			if (grid[gr].A2.x == aend[0].x && grid[gr].A2.y == aend[0].y) {return 0;}
			if (grid[gr].B1.x == aend[0].x && grid[gr].B1.y == aend[0].y) {return 0;}
			if (grid[gr].B2.x == aend[0].x && grid[gr].B2.y == aend[0].y) {return 0;}
			if (grid[gr].C1.x == aend[0].x && grid[gr].C1.y == aend[0].y) {return 0;}
			if (grid[gr].C2.x == aend[0].x && grid[gr].C2.y == aend[0].y) {return 0;}
			if (grid[gr].D1.x == aend[0].x && grid[gr].D1.y == aend[0].y) {return 0;}
			if (grid[gr].D2.x == aend[0].x && grid[gr].D2.y == aend[0].y) {return 0;}
			break;
		case 'B':
		case 'b':
			if (grid[gr].A1.x == bend[0].x && grid[gr].A1.y == bend[0].y) {return 0;}
			if (grid[gr].A2.x == bend[0].x && grid[gr].A2.y == bend[0].y) {return 0;}
			if (grid[gr].B1.x == bend[0].x && grid[gr].B1.y == bend[0].y) {return 0;}
			if (grid[gr].B2.x == bend[0].x && grid[gr].B2.y == bend[0].y) {return 0;}
			if (grid[gr].C1.x == bend[0].x && grid[gr].C1.y == bend[0].y) {return 0;}
			if (grid[gr].C2.x == bend[0].x && grid[gr].C2.y == bend[0].y) {return 0;}
			if (grid[gr].D1.x == bend[0].x && grid[gr].D1.y == bend[0].y) {return 0;}
			if (grid[gr].D2.x == bend[0].x && grid[gr].D2.y == bend[0].y) {return 0;}
			break;
		case 'C':
		case 'c':
			if (grid[gr].A1.x == cend[0].x && grid[gr].A1.y == cend[0].y) {return 0;}
			if (grid[gr].A2.x == cend[0].x && grid[gr].A2.y == cend[0].y) {return 0;}
			if (grid[gr].B1.x == cend[0].x && grid[gr].B1.y == cend[0].y) {return 0;}
			if (grid[gr].B2.x == cend[0].x && grid[gr].B2.y == cend[0].y) {return 0;}
			if (grid[gr].C1.x == cend[0].x && grid[gr].C1.y == cend[0].y) {return 0;}
			if (grid[gr].C2.x == cend[0].x && grid[gr].C2.y == cend[0].y) {return 0;}
			if (grid[gr].D1.x == cend[0].x && grid[gr].D1.y == cend[0].y) {return 0;}
			if (grid[gr].D2.x == cend[0].x && grid[gr].D2.y == cend[0].y) {return 0;}
			break;
		case 'D':
		case 'd':
			if (grid[gr].A1.x == dend[0].x && grid[gr].A1.y == dend[0].y) {return 0;}
			if (grid[gr].A2.x == dend[0].x && grid[gr].A2.y == dend[0].y) {return 0;}
			if (grid[gr].B1.x == dend[0].x && grid[gr].B1.y == dend[0].y) {return 0;}
			if (grid[gr].B2.x == dend[0].x && grid[gr].B2.y == dend[0].y) {return 0;}
			if (grid[gr].C1.x == dend[0].x && grid[gr].C1.y == dend[0].y) {return 0;}
			if (grid[gr].C2.x == dend[0].x && grid[gr].C2.y == dend[0].y) {return 0;}
			if (grid[gr].D1.x == dend[0].x && grid[gr].D1.y == dend[0].y) {return 0;}
			if (grid[gr].D2.x == dend[0].x && grid[gr].D2.y == dend[0].y) {return 0;}
			break;
	}
	return 1;
}
int inHomeBottom(int gr, char wat) {
	switch(wat) {
		case 'A': if (grid[gr].A1.x == aend[0].x && grid[gr].A1.y == aend[0].y) {return 1;}
			break;
		case 'a': if (grid[gr].A2.x == aend[0].x && grid[gr].A2.y == aend[0].y) {return 1;}
			break;
		case 'B': if (grid[gr].B1.x == bend[0].x && grid[gr].B1.y == bend[0].y) {return 1;}
			break;
		case 'b': if (grid[gr].B2.x == bend[0].x && grid[gr].B2.y == bend[0].y) {return 1;}
			break;
		case 'C': if (grid[gr].C1.x == cend[0].x && grid[gr].C1.y == cend[0].y) {return 1;}
			break;
		case 'c': if (grid[gr].C2.x == cend[0].x && grid[gr].C2.y == cend[0].y) {return 1;}
			break;
		case 'D': if (grid[gr].D1.x == dend[0].x && grid[gr].D1.y == dend[0].y) {return 1;}
			break;
		case 'd': if (grid[gr].D2.x == dend[0].x && grid[gr].D2.y == dend[0].y) {return 1;}
			break;
	}
	return 0;
}

int inCorridor(int gr, char wat) {
	for (int i = 0; i < corridorLen; i++) {
		switch (wat) {
			case 'A':
				if (grid[gr].A1.x == corridor[i].x && grid[gr].A1.y == corridor[i].y) {return 1;}
				break;
			case 'a':
				if (grid[gr].A2.x == corridor[i].x && grid[gr].A2.y == corridor[i].y) {return 1;}
				break;
			case 'B':
				if (grid[gr].B1.x == corridor[i].x && grid[gr].B1.y == corridor[i].y) {return 1;}
				break;
			case 'b':
				if (grid[gr].B2.x == corridor[i].x && grid[gr].B2.y == corridor[i].y) {return 1;}
				break;
			case 'C':
				if (grid[gr].C1.x == corridor[i].x && grid[gr].C1.y == corridor[i].y) {return 1;}
				break;
			case 'c':
				if (grid[gr].C2.x == corridor[i].x && grid[gr].C2.y == corridor[i].y) {return 1;}
				break;
			case 'D':
				if (grid[gr].D1.x == corridor[i].x && grid[gr].D1.y == corridor[i].y) {return 1;}
				break;
			case 'd':
				if (grid[gr].D2.x == corridor[i].x && grid[gr].D2.y == corridor[i].y) {return 1;}
				break;
		}
	}
	return 0;
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
