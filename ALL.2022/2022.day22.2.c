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
FILE *a;
#define LINE 6000
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SeX 220
char grid[SeX][SeX];
char gridNumbering[SeX][SeX];

struct startend_s {
	int st;
	int en;
};

struct startend_s RowStae[300];
struct startend_s ColStae[300];

char mands[6000];
char mandsOrig[6000];

struct mands2_s {
	char rl;
	int val;
};

struct mands2_s mands2[6000];
int numPos = 0;
void printit(int crx, int cry, int dir);
int leny = 0;
int hide = 0;
int fd;
//will be LEN1
void rotate90C(int N);
void rotate90AC(int N);

char mat[300][300];

void rotate90C(int N) {
	char res[N][N];
	memset(res, '0', sizeof(res));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			res[j][N-i-1] = mat[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			mat[i][j] = res[i][j];
		}
	}
}

void rotate90AC(int N) {
	char res[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			res[N-j-1][i] = mat[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			mat[i][j] = res[i][j];
		}
	}
}

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 22 part2\n"); fflush(stdout);
	///printf("convoluted to get it working with examples\n");

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];

	int lenx = 0;
	int f1 = 1;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			f1 = 0;
			continue;
		} else if (f1 == 1) {
			strcpy(grid[leny], line1);
			if ((int)strlen(grid[leny]) > lenx) {lenx = (int)strlen(grid[leny]);}
		} else if (f1 == 0) {
			strcpy(mands, line1);
		}

		leny++;
	}

	fclose(a);

#ifdef _EX1_
	/*
	for (int yy = 0; yy < 16; yy++) {
		strcpy(mat[yy], grid[yy]);
	}
	for (int yy = 0; yy < leny; yy++) {
		printf("%s\n", mat[yy]);
	}
	fflush(stdout); printf("calling rotate90AC\n");
	rotate90AC(16);
	for (int yy = 0; yy < leny; yy++) {
		printf("%s\n", mat[yy]);
		strcpy(grid[yy], mat[yy]);
	}
	getchar();
	*/
	int LEN1 = 4;
	int startX = 0;

#else 
	int startX = 0;
	{
		int y = 0;
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == ' ' && grid[y][x+1] == '.') {startX = x+1; break;}
		}
	}
	printf("startX is %d\n", startX);

	//////////////////////
	int posesX[leny];
	memset(posesX, 0, sizeof(posesX));

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx-3; x++) {
			if (grid[y][x] == ' ' && grid[y][x+1] != ' ') {
				posesX[y] = x;
				printf("setting poses[y] to x:%d\n", x);
				goto nextY;
			}
		}
nextY:
		continue;
	}

	int min1 = lenx;
	int sidesXY = -1;
	for (int ii = 0; ii < leny; ii++ ) {
		printf("%d\n", posesX[ii]);
		if (posesX[ii] != 0 && posesX[ii] < min1) {
			sidesXY = posesX[ii];
		}

	}
	/////////////////////////////////////////
	printf("NOW THE YYYYYYYYYYYYYYleny %dYY\n", leny);
	int posesY[lenx];
	memset(posesY, 0, sizeof(posesY));

	for (int x = 0; x < lenx; x++) {
		for (int y = 0; y < leny-3; y++) {
			if (grid[y][x] == ' ' && grid[y+1][x] != ' ') {
				posesY[x] = y;
				printf("setting posesY[%d] to y:%d\n", x, y);
				goto nextX;
			}
		}
nextX:
		continue;
	}

	min1 = sidesXY;
	for (int ii = 0; ii < lenx; ii++ ) {
		printf("%d\n", posesY[ii]);
		if (posesY[ii] != 0 && posesY[ii] < min1) {
			sidesXY = posesY[ii];
		}

	}
	//////////////////////
	int LEN1 = sidesXY+1;	
	printf("LEN1 == %d\n", LEN1);
#endif


	memset(gridNumbering, '0', sizeof(gridNumbering));

	char numbering = '1';
	for (int y = 0; y < leny; y+=LEN1) {
		for (int x = 0; x < lenx; x+=LEN1) {
			if (grid[y][x] != ' ' && grid[y][x] != '\0' && grid[y][x] != '\n') {
				for (int yy = y; yy < y+LEN1; yy++) {
					for (int xx = x; xx<x+LEN1; xx++) {
						gridNumbering[yy][xx] = numbering;
					}
				}
				numbering++;
			}
		}
	}
#ifdef _EX1_
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", gridNumbering[y][x]);
		}
		printf("\n");
	}
	printf("\n");
#endif

#ifndef _EX1_
	{
		//char mat4[LEN1][LEN1];
		int mat4x = -1; int mat4y = -1;
		for (int yy = 0; yy < leny; yy++) {
			for (int xx = 0; xx < lenx; xx++) {
				if (gridNumbering[yy][xx] == '4' && mat4x == -1 && mat4y == -1) {
					mat4x = xx; mat4y = yy;
					//printf("zero zero for mat4 is %d %d\n", mat4x, mat4y);
				}
				if (gridNumbering[yy][xx] == '4') {
					mat[yy-mat4y][xx-mat4x] = grid[yy][xx];
					//printf("%d %d\n", xx-mat4x, yy-mat4y);
					grid[yy][xx] = ' ';
				}
			}
		}
		rotate90C(LEN1);
		rotate90C(LEN1);

		for (int yy = 0; yy < LEN1; yy++) {
			for (int xx = 0; xx < LEN1; xx++) {
				grid[yy][xx] = mat[yy][xx];
			}
		}
	}

	{
		//char mat6[LEN1][LEN1];
		int mat6x = -1; int mat6y = -1;
		for (int yy = 0; yy < leny; yy++) {
			for (int xx = 0; xx < lenx; xx++) {
				if (gridNumbering[yy][xx] == '6' && mat6x == -1 && mat6y == -1) {
					mat6x = xx; mat6y = yy;
				}
				if (gridNumbering[yy][xx] == '6') {
					mat[yy-mat6y][xx-mat6x] = grid[yy][xx];
					grid[yy][xx] = ' ';
				}
			}
		}
		rotate90AC(LEN1);

		for (int yy = 3*LEN1; yy < 4*LEN1; yy++) {
			for (int xx = LEN1; xx < 2*LEN1; xx++) {
				assert(yy-(3*LEN1) >= 0 && yy-(3*LEN1) <= LEN1);
				assert(xx-LEN1 >= 0 && xx-LEN1 <= LEN1);
				grid[yy][xx] = mat[yy-(3*LEN1)][xx-LEN1];
			}
		}
	}


	memset(gridNumbering, '0', sizeof(gridNumbering));
	numbering = '1';
	for (int y = 0; y < leny; y+=LEN1) {
		for (int x = 0; x < lenx; x+=LEN1) {
			if (grid[y][x] != ' ' && grid[y][x] != '\0' && grid[y][x] != '\n') {
				for (int yy = y; yy < y+LEN1; yy++) {
					for (int xx = x; xx<x+LEN1; xx++) {
						gridNumbering[yy][xx] = numbering;
					}
				}
				numbering++;
			}
		}
	}
#endif
	strcpy(mandsOrig, mands);
	char *cmds = strtok(mands, "RL\0");

	numPos = 0;
	do {
		mands2[numPos++].val = atoi(cmds);
	} while ((cmds = strtok(NULL, "RL\0")) != NULL);

	strcpy(mands, mandsOrig);
	int newPos = 0;
	for (int i = 0; i < (int)strlen(mands); i++) {
		if (mands[i] == 'R') {
			mands2[newPos].rl = 'R';
			newPos++;
		} else if (mands[i] == 'L') {
			mands2[newPos].rl = 'L';
			newPos++;
		}
	}

	printf("----COMMANDS--------\n");
	for (int i = 0; i < numPos; i++) {
		printf("%c: %d\n", mands2[i].rl, mands2[i].val);
	}
	printf("---------------------\n");

	int dir = 1;
	int stx = startX; int sty = 0;
	int crx = stx; int cry = sty;
	printf("crx is %d cry is %d\n", crx, cry);
	//exit(0);
	/* all like this
	   - - -
	     |
	     |
	     |
	   */
	int kk = 0;
	//printf("LEN1 is %d\n", LEN1); exit(0);
	int eSZ1 = (1*LEN1)-1; //the end pos...
	int eSZ2 = (2*LEN1)-1;
	int eSZ3 = (3*LEN1)-1;
	int eSZ4 = (4*LEN1)-1;
	int sSZ1 = 1*LEN1;
	int sSZ2 = 2*LEN1;
	int sSZ3 = 3*LEN1;
	//int sSZ4 = 4*LEN1;
	// X--0-49 50-99 100-149 --the xxes  starts are 0, 50, 100  ends are 49, 99, 149
	// Y--0-49 50-99 100-149 150-199 the yyes  -- starts are 0, 50, 100, 150  ends are 49, 99, 149, 199
	int ar[12] = {0};
	for (int i = 0; i < numPos; i++) {
		printf("i: %d - numSteps: %d dir:%d\n", i, mands2[i].val, dir);
		//printit(crx, cry, dir); 
		switch(dir) {
			case(0): { //^^^ y --
c0:
					 for (; kk < mands2[i].val; kk++) {
						 printit(crx, cry, dir); 
						 if (gridNumbering[cry][crx] == '2' || gridNumbering[cry][crx] == '4'
								 || gridNumbering[cry][crx] == '5' || gridNumbering[cry][crx] == '6') {
							 if (cry == 0 && grid[eSZ4][crx] != '#') {
								 cry = eSZ4;
							 } else if (cry == 0 && grid[eSZ4][crx] == '#') {
								 break;
							 } else if (grid[cry-1][crx] == '.') {
								 cry--;
							 } else if (grid[cry-1][crx] == '#') {
								 break;
							 } else {
								 printf("NOT HERE ^^1 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '1') {
							 int bit1 = eSZ1 - crx;
							 assert(bit1 <= 49 && bit1 >= 0);
							 //assert(grid[sSZ4-bit1][sSZ1-1] == ' ');
							 if (cry == 0 && grid[eSZ4-bit1][sSZ1] != '#') {
								 kk++;
								 dir = 1;
								 cry = eSZ4-bit1;
								 crx = sSZ1;
								 printf("up on 1 right on 6 -> crx: %d cry %d (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[0] == 0) {
									 ar[0] = 1;
									 getchar();
								 }
								 goto c1; //up on 1 right on 6
							 } else if (cry == 0 && grid[eSZ4-(bit1)][sSZ1] == '#') {
								 break;
							 } else if (grid[cry-1][crx] == '.') {
								 cry--;
							 } else if (grid[cry-1][crx] == '#') {
								 break;
							 } else {
								 printf("NOT HERE ^^2 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '3') {
							 int bit1 = crx-sSZ2;
							 assert(bit1 <= 49 && bit1 >= 0);
							 //assert(grid[sSZ4-bit1][sSZ2] == ' ');
							 if (cry == 0 && grid[eSZ4-bit1][eSZ2] != '#') {
								 kk++;
								 dir = 3;
								 cry = eSZ4-bit1;
								 crx = eSZ2;
								 printf("up on 3 left on 6 %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[2] == 0) {
									 ar[2] = 1;
									 getchar();
								 }
								 goto c3; //up on 3 left on 6
							 } else if (cry == 0 && grid[eSZ4-bit1][eSZ2] == '#') {
								 break;
							 } else if (grid[cry-1][crx] == '.') {
								 cry--;
							 } else if (grid[cry-1][crx] == '#') {
								 break;
							 } else {
								 printf("NOT HERE ^^3 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 }
					 }
					 kk=0;
					 break;
				 }
			case(1): { //x++ >>>
c1:
					 for (; kk < mands2[i].val; kk++) {
						 printit(crx, cry, dir);
						 if (gridNumbering[cry][crx] == '1' || gridNumbering[cry][crx] == '2'
								 || gridNumbering[cry][crx] == '3') {
							 int bit1 = eSZ1-cry;
							 assert(bit1 <= 49 && bit1 >= 0);
							 if (crx == eSZ3 && grid[sSZ2+bit1][eSZ2] != '#') {
								 kk++;
								 dir = 3;
								 cry = sSZ2+bit1;
								 crx = eSZ2;
								 printf("right on 3 left on 5 -> %d %d -- (%c)\n", cry, crx, gridNumbering[cry][crx]);
								 if (ar[4] == 0) {
									 ar[4] = 1;
								 	getchar();
								 }
								 goto c3; //right on 3 left on 5
							 } else if (crx == eSZ3 && grid[sSZ2+bit1][eSZ2] == '#') {
								 break;
							 } else if (grid[cry][crx+1] == '.') {
								 crx++;
							 } else if (grid[cry][crx+1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE >>1 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '4') {
							 int bit1 = cry-sSZ1;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == eSZ2 && grid[eSZ1][sSZ2+bit1] != '#') {
								 kk++;
								 dir = 0;
								 cry = eSZ1;
								 crx = sSZ2+bit1;
								 printf("right on 4 up on 3 %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[5] == 0) {
									 ar[5] = 1;
									 getchar();
								 }
								 goto c0;//right on 4 up on 3
							 } else if (crx == eSZ2 && grid[eSZ1][sSZ2+bit1] == '#') {
								 break;
							 } else if (grid[cry][crx+1] == '.') {
								 crx++;
							 } else if (grid[cry][crx+1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE >>2 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '5') {
							 int bit1 = cry-sSZ2;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == eSZ2 && grid[eSZ1-bit1][eSZ3] != '#') {
								 dir = 3;
								 kk++;
								 cry = eSZ1-bit1;
								 crx = eSZ3;
								 printf("right on 5 left on 3 %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[6] == 0) {
									 ar[6] = 1;
									 getchar();
								 }
								 goto c3; //right on 5 left on 3
							 } else if (crx == eSZ2 && grid[eSZ1-bit1][eSZ3] == '#') {
								 break;
							 } else if (grid[cry][crx+1] == '.') {
								 crx++;
							 } else if (grid[cry][crx+1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE >>3 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '6') {
							 //int bit1 = cry-sSZ3;
							 int bit1 = eSZ4-cry;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == eSZ2 && grid[0][sSZ2+bit1] != '#') {
								 dir = 2;
								 kk++;
								 cry = 0;
								 crx = sSZ2+bit1;
								 printf(" right on 6 down on 3 %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[7] == 0) {
									 ar[7] = 1;
									 getchar();
								 }
								 goto c2; //right on 6 down on 3
							 } else if (crx == eSZ2 && grid[0][sSZ2+bit1] == '#') {
								 break;
							 } else if (grid[cry][crx+1] == '.') {
								 crx++;
							 } else if (grid[cry][crx+1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE >>4 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 }

					 }
					 kk = 0;
					 break;
				 }
			case(2): { //y++
c2:
					 for (; kk < mands2[i].val; kk++) {
						 printit(crx, cry, dir); 
						 if (gridNumbering[cry][crx] == '2' || gridNumbering[cry][crx] == '4'
								 || gridNumbering[cry][crx] == '5' || gridNumbering[cry][crx] == '6') {
							 if (cry == eSZ4 && grid[0][crx] != '#') {
								 cry = 0;
							 } else if (cry == eSZ4 && grid[0][crx] == '#') {
								 break;
							 } else if (grid[cry+1][crx] == '.') {
								 cry++;
							 } else if (grid[cry+1][crx] == '#') {
								 break;
							 } else {
								 printf("NOT HERE vv1 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '1') {
							 int bit1 = eSZ1-crx;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (cry == eSZ1 && grid[sSZ1+bit1][sSZ1] != '#') {
								 dir = 1;
								 kk++;
								 cry = sSZ1+bit1;
								 crx = sSZ1;
								 printf("down on 1 right on 4-> %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[1] == 0) {
									 ar[1] = 1;
									 getchar();
								 }
								 goto c1; //down on 1 right on 4
							 } else if (cry == eSZ1 && grid[sSZ1+bit1][sSZ1] == '#') {
								 break;
							 } else if (grid[cry+1][crx] == '.') {
								 printf("here2...\n");
								 cry++;
							 } else if (grid[cry+1][crx] == '#') {
								 printf("here3...\n");
								 break;
							 } else {
								 printf("NOT HERE vv2 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '3') {
							 int bit1 = crx-sSZ2;
							 assert(bit1>=0 && bit1 <= 49);
							 //if (grid[crx-(2*LEN1)+LEN1-1][2*LEN1] != '#') 
							 if (cry == eSZ1 && grid[sSZ1+bit1][eSZ2] != '#') {
								 kk++;
								 dir = 3;
								 cry = sSZ1+bit1;
								 crx = eSZ2;
								 printf("down on 3 left on 4 --> %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[3] == 0) {
									 ar[3] = 1;
									 getchar();
								 }
								 goto c3; //down on 3 left on 4
							 } else if (cry == eSZ1 && grid[sSZ1+bit1][eSZ2] == '#') {
								 break;
							 } else if (grid[cry+1][crx] == '.') {
								 cry++;
							 } else if (grid[cry+1][crx] == '#') {
								 break;
							 } else {
								 printf("NOT HERE vv3 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 }
					 }
					 kk = 0;
					 break;
				 }
			case(3): {
c3:
					 //x-- <<
					 for (; kk < mands2[i].val; kk++) {
						 printit(crx, cry, dir);
						 if (gridNumbering[cry][crx] == '1' || gridNumbering[cry][crx] == '2'
								 || gridNumbering[cry][crx] == '3') {
							 int bit1 = eSZ1-cry;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == 0 && grid[sSZ2+bit1][sSZ1] != '#') {
								 dir = 1;
								 kk++;
								 cry = sSZ2+bit1;
								 crx = sSZ1;
								 printf("left on 1 right on 5 -- cry %d crx %d-- (%c)\n", cry, crx, gridNumbering[cry][crx]);
								 if (ar[8] == 0) {
									 ar[8] = 1;
									 getchar();
								 }
								 goto c1; //left on 1 right on 5
							 } else if (crx == 0 && grid[sSZ2+bit1][sSZ1] == '#') {
								 break;
							 } else if (grid[cry][crx-1] == '.') {
								 crx--;
							 } else if (grid[cry][crx-1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE <<1 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '4') {
							 int bit1 = cry-sSZ1;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == sSZ1 && grid[eSZ1][eSZ1-bit1] != '#') {
								 dir = 0;
								 kk++;
								 cry = eSZ1;
								 crx = eSZ1-bit1;
								 printf("left on 4 up on 1--> %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[9] == 0) {
									 ar[9] = 1;
									 getchar();
								 }
								 goto c0; //left on 4 up on 1
							 } else if (crx == sSZ1 && grid[eSZ1][eSZ1-bit1] == '#') {
								 break;
							 } else if (grid[cry][crx-1] == '.') {
								 crx--;
							 } else if (grid[cry][crx-1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE <<2 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '5') {
							 int bit1 = cry-sSZ2;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == sSZ1 && grid[eSZ1-bit1][0] != '#') {
								 kk++;
								 dir = 1;
								 cry = eSZ1-bit1;
								 crx = 0;
								 printf("left on 5 right on 1 -> %d %d-- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[10] == 0) {
									 ar[10] = 1;
									 getchar();
								 }
								 goto c1; //left on 5 right on 1
							 } else if (crx == sSZ1 && grid[eSZ1-bit1][0] == '#') {
								 break;
							 } else if (grid[cry][crx-1] == '.') {
								 crx--;
							 } else if (grid[cry][crx-1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE <<3 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 } else if (gridNumbering[cry][crx] == '6') {
							 int bit1 = cry-sSZ3;
							 assert(bit1 >= 0 && bit1 <= 49);
							 if (crx == sSZ1 && grid[0][bit1] != '#') {
								 kk++;
								 dir = 2;
								 cry = 0;
								 crx = bit1;
								 printf("left on 6 down on 1 -> crx %d cry %d -- (%c)\n", crx, cry, gridNumbering[cry][crx]);
								 if (ar[11] == 0) {
									 ar[11] = 1;
									 getchar();
								 }
								 goto c2; //left on 6 down on 1
							 } else if (crx == sSZ1 && grid[0][bit1] == '#') {
								 break;
							 } else if (grid[cry][crx-1] == '.') {
								 crx--;
							 } else if (grid[cry][crx-1] == '#') {
								 break;
							 } else {
								 printf("NOT HERE <<4 [%c]", grid[cry][crx]); exit(0);
								 break;
							 }
						 }
					 }
					 kk = 0;
					 break;
				 }
		}
		if (     mands2[i].rl == 'R')      {printf("turning R\n"); dir++; dir %= 4;}
		else if (mands2[i].rl == 'L') {printf("turning L\n"); dir--; dir+= 4; dir %= 4;}

	}
	printf("crx is %d\n", crx);
	printf("cry is %d\n", cry);
	printf("gridNumbering[cry][crx] is %c\n", gridNumbering[cry][crx]);
	if (gridNumbering[cry][crx] == '1') {
		printf("in grid 1 (manip)\n");
		//char mat4[LEN1][LEN1];
		memset(mat, ' ', LEN1*LEN1);
		mat[cry%LEN1][crx%LEN1] = '9';

		rotate90AC(LEN1);
		rotate90AC(LEN1);
		dir--;
		dir--;
		dir += 4;
		dir %= 4;
		for (int yy = 0; yy < LEN1; yy++) {
			for (int xx = 0; xx < LEN1; xx++) {
				if (mat[yy][xx] == '9') {
					crx = xx;
					cry = (2*LEN1)+yy;
					printf("crx %d cry %d\n", crx, cry);
				}
			}
		}
	} else  if (gridNumbering[cry][crx] == '6') {
		printf("in grid six (manip)\n");
		//char mat6[LEN1][LEN1];
		memset(mat, ' ', sizeof(mat));
		mat[cry%LEN1][crx%LEN1] = '9';

		rotate90C(LEN1);
		dir++;
		dir += 4;
		dir %= 4;

		for (int yy = 0; yy < LEN1; yy++) {
			for (int xx = 0; xx < LEN1; xx++) {
				if (mat[yy][xx] == '9') {
					crx = xx;
					cry = (3*LEN1)+yy;
					printf("crx %d cry %d\n", crx, cry);
				}
			}
		}

	}
	int posDir = dir;
	posDir--;
	posDir += 4;
	posDir %= 4;

	fflush(stdout); dup2(fd, 1);
	int ans1 = (1000 * (cry+1)) + (4 * (crx+1)) + posDir;
	printf("**ans: %d\n", ans1);

}
void printit(int crx, int cry, int dir) {
	int sx, sy;
	int ex, ey;

	sx = crx-5 <                      0 ? 0                      : crx-5;
	ex = crx+5 > (int)strlen(grid[cry]) ? (int)strlen(grid[cry]) : crx+5;

	sy = cry-5 <    0 ? 0    : cry-5;
	ey = cry+5 > leny ? leny : cry+5;

	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			if (y == cry && x == crx) {
				switch(dir) {
					case 0:
						printf("%c", '^'); break;
					case 1:
						printf("%c", '>'); break;
					case 2:
						printf("%c", 'v'); break;
					case 3:
						printf("%c", '<'); break;

				}
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("gridNumbering[%d][%d] is %c\n", cry, crx, gridNumbering[cry][crx]);
	//getchar();
}
void printit2(int crx, int cry, int dir) {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < (int)strlen(grid[y]); x++) {
			if (y == cry && x == crx) {
				switch(dir) {
					case 0:
						printf("%c", '^'); break;
					case 1:
						printf("%c", '>'); break;
					case 2:
						printf("%c", 'v'); break;
					case 3:
						printf("%c", '<'); break;

				}
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
	getchar();
}

/*

///int stx = RowStae[0].st; int sty = 0;
int stx = startX; int sty = 0;
int dir = 1;
int crx = stx; int cry = sty;

for (int i = 0; i < numPos; i++) {
printf("forward %d\n", mands2[i].val);
switch(dir) {
case(0):
{
//y-- ^^^^
for (int kk = 0; kk < mands2[i].val; kk++) {
if (cry == ColStae[crx].st || grid[cry-1][crx] == '\0' || grid[cry-1][crx] == ' ') {
if (grid[ColStae[crx].en][crx] != '#') {cry = ColStae[crx].en;} else {break;}
} else if (grid[cry-1][crx] == '.') {cry--;}
else if (grid[cry-1][crx] == '#') {break;}
else {printf("NOT HERE ^^"); exit(0); break;}
printit(crx, cry, dir);
}
break;
}
case(1):
{
//x++ >>>>>
for (int kk = 0; kk < mands2[i].val; kk++) {
if (crx == RowStae[cry].en || grid[cry][crx+1] == '\0' || grid[cry][crx+1] == ' ') {
if (grid[cry][RowStae[cry].st] != '#') {crx = RowStae[cry].st;} else {break;}
} else if (grid[cry][crx+1] == '.') {crx++;}
else if (grid[cry][crx+1] == '#') {break;}
else {printf("NOT HERE >> [[%c]] [[%c]]", grid[cry][crx], grid[cry][crx+1]); exit(0); break;}
printit(crx, cry, dir);
}
break;
}
case(2):
{
for (int kk = 0; kk < mands2[i].val; kk++) {
if (cry == ColStae[crx].en || grid[cry+1][crx] == '\0' || grid[cry+1][crx] == ' ') {
if (grid[ColStae[crx].st][crx] != '#') {cry = ColStae[crx].st;} else {break;}
} else if (grid[cry+1][crx] == '.') {cry++;}
else if (grid[cry+1][crx] == '#') {break;}
else {printf("NOT HERE vv [[%c]%c]", grid[cry][crx], grid[cry+1][crx]); exit(0); break;}
printit(crx, cry, dir);
}
//y++ vvvvvv
break;
}
case(3):
{
//x-- <<<<<<
for (int kk = 0; kk < mands2[i].val; kk++) {
if (crx == RowStae[cry].st || grid[cry][crx-1] == '\0' || grid[cry][crx-1] == ' ') {
if (grid[cry][RowStae[cry].en] != '#') {crx = RowStae[cry].en;} else {break;}
} else if (grid[cry][crx-1] == '.') {crx--;}
else if (grid[cry][crx-1] == '#') {break;}
else {printf("NOT HERE << [[%c]][%c]]", grid[cry][crx-1], grid[cry][crx]); exit(0); break;}
printit(crx, cry, dir);
}
break;
}
}
if (     mands2[i].rl == 'R')      {printf("turning R\n"); dir++; dir %= 4;}
else if (mands2[i].rl == 'L') {printf("turning L\n"); dir--; dir+= 4; dir %= 4;} 
else (assert(i == numPos-1));
}
if (hide == 1) {
fflush(stdout); dup2(fd, 1);
}
printit(crx, cry, dir);
*/
/*
   for (int y = 0; y < leny; y++) {
   int first = 1;
   for (int x = 0; x < lenx; x++) {
   if (grid[y][x] == '\0') {break;} 
   else if (first == 0 && (grid[y][x] == ' ' || grid[y][x+1] =='\0')) {RowStae[y].en = x; break;}
   }
   }

   for (int x = 0; x < lenx; x++) {
   int first = 1;
   for (int y = 0; y < leny; y++) {
   if (first == 1 && (grid[y][x] == '.' || grid[y][x] == '#')) {first = 0; ColStae[x].st = y;}
   else if (first == 0 && (grid[y][x] == ' ' || y+1 ==leny)) {ColStae[x].en = y-1; break;}
   }
   }

   printf("--------ROWS---------\n");
   for (int y = 0; y < leny; y++) {
   printf("RoW %d :: From: %d To: %d\n", y, RowStae[y].st, RowStae[y].en);
   }

   getchar();
   printf("--------COLS-----------\n");
   for (int x = 0; x < lenx; x++) {
   printf("Col %d :: From: %d To: %d\n", x, ColStae[x].st, ColStae[x].en);
   }
   getchar();
   */
	/*
	   for (int yy = 0; yy< leny; yy++) {
	   for (int xx = 0; xx < lenx; xx++) {
	   if (gridNumbering[yy][xx] != '0') {
	   printf("%c", gridNumbering[yy][xx]);
	   } else {
	   printf("%c", ' ');
	   }
	   }
	   printf("\n");
	   }
	   printf("\n");
	   */
	//turninto(); //|---
	//N = LEN1;

	//rotate6antiandmoveright();
	//rotate4clockTWOandmoveUPTwo();
