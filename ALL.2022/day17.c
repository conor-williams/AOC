#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include <iostream>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
#define LINE 20200
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SX 10000
char grid[10100][8];
void drawMinus();
void drawPlus();
void drawEll();
void drawPipe();
void drawSquare();
int bottomIt();
int jetPos = 0;
char line1[LINE];
int vBottom;
int canIMoveMinus(int startX, int startY, int xM, int yM);
int canIMovePlus(int startX, int startY, int mX, int mY);
int canIMoveEll(int startX, int startY, int mX, int mY);
int canIMovePipe(int startX, int startY, int xM, int yM);
int canIMoveSq(int startX, int startY, int xM, int yM); 

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day day17 part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	memset(grid, '.', sizeof(grid));
	for (int y = 0; y < SX; y++) {
		for (int x = 0; x < 7; x++) {
			assert(grid[y][x] == '.');
		}
	}
	vBottom = SX-10;
	for (int x = 0; x < 7; x++) {
		grid[vBottom][x] = '#';
	}
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		leny++;
	}
	fclose(a);

	for (int j = 0; j < 2022; j++) {
		int shape = j % 5;
		switch(shape) {
			case 0: //-
				drawMinus();
				break;
			case 1: //+
				drawPlus();
				break;
			case 2: //_|
				drawEll();
				break;
			case 3: //|
				drawPipe();
				break;
			case 4: //|=|
				drawSquare();
				break;
		}
	}


	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", vBottom - bottomIt());
}


int bottomIt() {
	int bottom[8];
	int bottomSrt[8];
	int found0 = 0;
	int found1 = 0;
	int found2 = 0;
	int found3 = 0;
	int found4 = 0;
	int found5 = 0;
	int found6 = 0;
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < vBottom+5; y++) {
			if (x == 0 && grid[y][x] == '#' && found0 == 0) {
				bottom[0] = y;
				found0 = 1;
			} else if (x == 1 && grid[y][x] == '#' && found1 == 0) {
				bottom[1] = y;
				found1 = 1;
			} else if (x == 2 && grid[y][x] == '#' && found2 == 0) {
				bottom[2] = y;
				found2 = 1;
			} else if (x == 3 && grid[y][x] == '#' && found3 == 0) {
				bottom[3] = y;
				found3 = 1;
			} else if (x == 4 && grid[y][x] == '#' && found4 == 0) {
				bottom[4] = y;
				found4 = 1;
			} else if (x == 5 && grid[y][x] == '#' && found5 == 0) {
				bottom[5] = y;
				found5 = 1;
			} else if (x == 6 && grid[y][x] == '#' && found6 == 0) {
				bottom[6] = y;
				found6 = 1;
			}
		}
	}

	for (int i = 0; i < 7; i++) {
		//printf("Bottom %d is %d\n", i, bottom[i]);
		bottomSrt[i] = bottom[i];
	}
	getchar();

	sort(bottomSrt, bottomSrt+7);
	assert(bottomSrt[0] <= bottomSrt[1]);

	int highest = bottomSrt[0];
	return highest;
}

int canIMoveSq(int startX, int startY, int xM, int yM) 
{
	if (xM == 7 && yM == 7) {
		grid[startY-1][startX] = '#'; grid[startY-1][startX+1] = '#';
		grid[startY][startX] = '#'; grid[startY][startX+1] = '#';
		return 1;
	}

	int var_sx = startX+xM;
	int var_sy = startY+yM;
	if (grid[var_sy-1][var_sx] == '.' && grid[var_sy-1][var_sx+1] == '.' &&
			grid[var_sy][var_sx] == '.' && grid[var_sy][var_sx+1] == '.') {
		return 1;
	}
	return 0;

}


int canIMovePipe(int startX, int startY, int xM, int yM)
{
	if (xM == 7 && yM == 7) {
		grid[startY  ][startX] = '#';
		grid[startY-1][startX] = '#';
		grid[startY-2][startX] = '#';
		grid[startY-3][startX] = '#';
		return 0;
	}

	int var_sx = startX+xM;
	int var_sy = startY+yM;
	if (grid[var_sy][var_sx] == '.' &&
			grid[var_sy-1][var_sx] == '.' &&
			grid[var_sy-2][var_sx] == '.' &&
			grid[var_sy-3][var_sx] == '.') {
		return 1;
	}
	return 0;
}


void drawSquare()
{
	cout << "DrawSquare..." << endl;

	int highest = bottomIt();
	int startY = highest-4;

	int startX = 2;
	int endX = 3;

	jetPos = jetPos % ((int) strlen(line1));

	while (1) {
		if (line1[jetPos] == '>') {
			printf("move right");
			if (endX != 6 && canIMoveSq(startX, startY, 1, 0)) {
				startX++;	
				endX++;
			} else {
				printf(" -- no move right\n");
			}

			if (canIMoveSq(startX, startY, 0, +1))  {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		} else if (line1[jetPos] == '<') {
			printf("move left\n");
			if (startX != 0 &&  canIMoveSq(startX, startY, -1, 0)) {
				startX--;
				endX--;
			} else {
				printf(" -- no move left\n");
			}
			if (canIMoveSq(startX, startY, 0, +1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		}
		jetPos = (jetPos+1) % ((int) strlen(line1));
	}
	jetPos = (jetPos+1) % ((int) strlen(line1));
	if (canIMoveSq(startX, startY, 0, 0)) {
		canIMoveSq(startX, startY, 7, 7);
	} else {
		perror("square...\n"); exit(0);
	}
}


void drawPipe()
{
	cout << "DrawPipe..." << endl;
	int highest = bottomIt();
	int startY = highest-4;

	printf("starting off y: %d\n",  startY);
	int startX = 2;
	int endX = 2;

	jetPos = jetPos % ((int) strlen(line1));


	while (1) {
		if (line1[jetPos] == '>') {
			printf("move right");
			if (endX != 6 && canIMovePipe(startX, startY, 1, 0)) {
				startX++;	
				endX++;
			} else {
				printf(" -- no move right\n");
			}
			if (canIMovePipe(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		} else if (line1[jetPos] == '<') {
			printf("move left\n");
			if (startX != 0 && canIMovePipe(startX, startY, -1, 0)) {
				startX--;
				endX--;
			} else {
				printf(" -- no move left\n");
			}
			if (canIMovePipe(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");	
				break;
			}
		}
		jetPos = (jetPos+1) % ((int) strlen(line1));
	}
	jetPos = (jetPos+1) % ((int) strlen(line1));
	if (canIMovePipe(startX, startY, 0, 0)) {
		canIMovePipe(startX, startY, 7, 7);
	}
}


int canIMoveMinus(int startX, int startY, int xM, int yM) {
	if (xM == 7 && yM == 7) {
		grid[startY][startX] = '#'; grid[startY][startX+1] = '#'; grid[startY][startX+2] = '#'; grid[startY][startX+3] = '#';
		return 0;
	}


	int var_sY = startY+yM;
	int var_sX = startX+xM;

	if (grid[var_sY][var_sX] == '.' && grid[var_sY][var_sX+1] == '.' && grid[var_sY][var_sX+2] == '.' && grid[var_sY][var_sX+3] == '.') {
		return 1;
	}
	return 0;

}
void drawMinus()
{
	cout << "DrawMinus..." << endl;
	int highest = bottomIt();
	int startY = highest-4;

	int startX = 2;
	int endX = 5;

	jetPos = jetPos % ((int) strlen(line1));


	while (1) {
		if (line1[jetPos] == '>') {
			printf("move right");
			if (endX != 6 && canIMoveMinus(startX, startY, 1, 0)) {
				startX++;	
				endX++;
			} else {
				printf(" -- no move right\n");
			}
			if (canIMoveMinus(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}	
		} else if (line1[jetPos] == '<') {
			printf("move left\n");
			if (startX != 0 && canIMoveMinus(startX, startY, -1, 0)) {
				startX--;
				endX--;
			} else {
				printf(" -- no move left\n");
			}
			if (canIMoveMinus(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		}
		jetPos = (jetPos+1) % ((int) strlen(line1));
	}
	jetPos = (jetPos+1) % ((int) strlen(line1));

	if (canIMoveMinus(startX, startY, 0, 0)) {
		canIMoveMinus(startX, startY, 7, 7);
	}
}

int canIMovePlus(int startX, int startY, int xM, int yM)
{
	if(xM == 7 && yM == 7) {
		grid[startY-2][startX+1] = '#';
		grid[startY-1][startX] = '#'; 	grid[startY-1][startX+1] = '#'; grid[startY-1][startX+2] = '#';
		grid[startY  ][startX+1] = '#';
		return 0;
	} 

	if (						grid[startY-2+yM][startX+1+xM] == '.' && 
			grid[startY-1+yM][startX+xM] == '.' && 	grid[startY-1+yM][startX+1+xM] == '.' && grid[startY-1+yM][startX+2+xM] == '.' &&
			grid[startY  +yM][startX+1+xM] == '.') {
		return 1;

	}
	return 0;
}
void drawPlus()
{
	cout << "DrawPlus..." << endl;
	int highest = bottomIt();
	int startY = highest-4;

	int startX = 2;
	int endX = 4;

	jetPos = jetPos % ((int) strlen(line1));

	while (1) {
		if (line1[jetPos] == '>') {
			printf("move right"); //+
			if (endX != 6 &&  canIMovePlus(startX, startY, 1, 0)) {
				startX++;	
				endX++;
			} else {
				printf(" -- no move right\n");
			}

			if (canIMovePlus(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		} else if (line1[jetPos] == '<') {
			printf("move left\n");
			if (startX != 0 && canIMovePlus(startX, startY, -1, 0)) {
				startX--;
				endX--;
			} else {
				printf(" -- no move left\n");
			}

			if (canIMovePlus(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		}
		jetPos = (jetPos+1) % ((int) strlen(line1));
	}
	jetPos = (jetPos+1) % ((int) strlen(line1));
	if (canIMovePlus(startX, startY, 0, 0)) {
		canIMovePlus(startX, startY, 7, 7);
	} else {
		perror("error plus\n"); exit(0);
	}
}
int canIMoveEll(int startX, int startY, int mX, int mY) 
{

	if (mX == 7 && mY == 7) {
		grid[startY-2][startX+2] = '#';
		grid[startY-1][startX+2] = '#';
		grid[startY][startX] = '#';	grid[startY][startX+1] = '#';  	grid[startY  ][startX+2] = '#';
		return 0;
	}
	if (										       grid[startY-2+mY][startX+2+mX] == '.' &&
			grid[startY-1+mY][startX+2+mX] == '.' &&
			grid[startY+mY][startX+mX] == '.' && 	grid[startY+mY][startX+1+mX] == '.' && grid[startY  +mY][startX+2+mX] == '.') {
		return 1;
	}
	return 0;




}
void drawEll()
{
	cout << "DrawEll..." << endl;
	int highest = bottomIt();
	int startY = highest-4;

	int startX = 2;
	int endX = 4;

	jetPos = jetPos % ((int) strlen(line1));


	while (1) {

		if (line1[jetPos] == '>') { //_|
			printf("move right"); //+
			if (endX != 6 && canIMoveEll(startX, startY, 1, 0)) {
				startX++;	
				endX++;
			} else {
				printf(" -- no move right\n");
			}

			if (canIMoveEll(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		} else if (line1[jetPos] == '<') {
			printf("move left\n");
			if (startX != 0 && canIMoveEll(startX, startY, -1, 0)) {
				startX--;
				endX--;
			} else {
				printf(" -- no move left\n");
			}

			if (canIMoveEll(startX, startY, 0, 1)) {
				printf("dropping...");
				startY++;
			} else {
				printf("not dropping...\n");
				break;
			}
		}
		jetPos = (jetPos+1) % ((int) strlen(line1));
	}
	jetPos = (jetPos+1) % ((int) strlen(line1));

	if (canIMoveEll(startX, startY, 0, 0)) {
		canIMoveEll(startX, startY, 7, 7);
	} else {
		perror("error ell backwards\n"); exit(0);
	}
}
