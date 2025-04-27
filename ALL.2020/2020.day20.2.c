#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>

#include <vector>
#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;
int lenx = 0;
int leny = 0;
int lenz = 0;
//#define getchar()

int LINE = 1000;

#define GX 10
int getPos(string p1, string p2);
int printGridANSI(int num, int sx, int sy);

char gridInitial[GX+10][GX+10];
int NUMG;

struct grid_s {
	int num;
	vector <vector <char>> gr;
};
struct grid_s grid[200];
struct grid_s gridG2[200];

struct grid_s gridtmp;
struct grid_s gridtmpg2;
struct grid_s gridtmpG2;
struct grid_s gridOrig[200];

vector <int> sidesMap;
vector <int> sar[200];
vector <struct grid_s> ways[200][4];
void rotate(int );

void saveOrig(int i);
void recoverOrig(int i);
void saveg2(int i);
void recoverg2(int i);

void save(int i);
void recover(int i);
void rotate(int );
void HFlipArray(int gridNum);
void VFlipArray(int gridNum);

//////////////////////
int countMax = 0;
int roughM = 0;
void transfer2MG();
void trans(int num, int sx, int sy);
char gridtmpMG[200][200];
char gridMG[200][200];
void saveMG();
void recoverMG();
void rotateMG();
void HFlipArrayMG();
void VFlipArrayMG();
void checkMG66();
int blahMG66();
void printGridMG();
void swap(char *x, char *y);
void reverse();
void transpose();
vector <pair<int, int>> mammoth;
char seaM[3][50] = {
	{"                  # "}, 
	{"#    ##    ##    ###"}, 
	{" #  #  #  #  #  #   "}};
int LEN;
int lenrow;
void printit();
//////////////////////

void check(int i);
int printGrid(int num);

int check66(int first, int second, string pos1, string pos2, int moveFirst, int moveSecond);
int blah66(int first, int second, string pos1, string pos2, int moveFirst, int moveSecond);
int checkGRIDcur(int g1, int g2, string pos1, string pos2, int moveFirst, int moveSecond);

int checkGRIDsides33333(int g1, int g2, int g3, string pos1, string pos2, string pos3, string pos4, int moveFirst, int moveSecond, int moveThird);
int checkGRIDsides2(int g1, int g2, string pos1, string pos2, int moveFirst, int moveSecond);
int checkGRIDsides3(int g1, int g2, int g3, string pos1, string pos2, string pos3, string pos4, int moveFirst, int moveSecond, int moveThird);
int checkGRIDsides4(int g1, int g2, int g3, int g4, string pos1, string pos2, string pos3, string pos4, string pos5, string pos6, int moveFirst, int moveSecond, int moveThird, int moveFourth);
int checkGRIDsides5(int g1, int g2, int g3, int g4, int g5, string pos1, string pos2, string pos3, string pos4, string pos5, string pos6, string pos7, string pos8, int moveFirst, int moveSecond, int moveThird, int moveFourth, int moveFifth);
int printGridG2(int num);

void saveOrigG2(int i);
void recoverOrigG2(int i);
void saveG2(int i);
void recoverG2(int i);
void HFlipArrayG2(int gridNum);
void VFlipArrayG2(int gridNum);
void checkG2(int i);
void rotateG2(int );

#define TOPLEFT 0
#define TOPRIGHT 1
#define BOTTOMLEFT 2
#define BOTTOMRIGHT 3

#define TOP 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 3

int gg[200];
void corner(int wat, int pos, int pp);
void edge(int wat, int pos, int pp);
void nonEdge(int XX, int pp);
void printGG();
void initGG();

operator ==(struct grid_s l, struct grid_s r) {
	bool ok = true;
	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			if (l.gr[y][x] != r.gr[y][x]) {
				ok = false; goto aft1;
			}
		}
	}
aft1:
	return ok;

}
int POS = 0;

int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day20 Part2\n"); fflush(stdout);
	printf("	SLOW ~3minutes\n");

	
	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	//Tile 2477:
	leny = -1;
	//int lin = 0;
	vector <char> ve;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		//printf("LINE: %s\n", line1);
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);
		if (line1[0] == '\0') {
			continue;
		} else if (line1[0] == 'T') {
			leny++;
			char snum[100];
			sscanf(line1, "Tile %[^:]:", snum);
			grid[leny].num   = atoi(snum);
			gridG2[leny].num = atoi(snum);
			cout << grid[leny].num << endl;
			//printf("%d %d leny %d\n", grid[leny].num, grid[leny].num, leny);
			ve.clear();
		} else {
			for (int i = 0; i < (int)strlen(line1); i++) {
				ve.push_back(line1[i]);
			}
			grid[leny].gr.push_back(ve);
			gridG2[leny].gr.push_back(ve);
			ve.clear();
		}
	}
	leny++;
	NUMG = leny;
	lenrow = (int)sqrt(NUMG);
	//assert(NUMG = 9);
	for (int kk = 0; kk < leny; kk++) { saveOrig(kk); saveOrigG2(kk); }

	unsigned long long mul = 1;
	for (int i = 0; i < leny; i++) {
		POS = 0;
		sidesMap.clear();
		//saveOrig(i);

		checkG2(i); rotateG2(i); checkG2(i); saveG2(i); VFlipArrayG2(i); checkG2(i); rotateG2(i); checkG2(i); rotateG2(i); checkG2(i); recoverG2(i); HFlipArrayG2(i); checkG2(i); rotateG2(i); checkG2(i); rotateG2(i); checkG2(i); rotateG2(i); checkG2(i); recoverG2(i); VFlipArrayG2(i); HFlipArrayG2(i); checkG2(i); rotateG2(i); checkG2(i); rotateG2(i); checkG2(i); rotateG2(i); checkG2(i); recoverG2(i); checkG2(i);

		checkG2(i); rotateG2(i); checkG2(i); saveG2(i); VFlipArrayG2(i); checkG2(i); recoverG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); VFlipArrayG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); checkG2(i);
		checkG2(i); rotateG2(i); checkG2(i); saveG2(i); VFlipArrayG2(i); checkG2(i); recoverG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); VFlipArrayG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); checkG2(i);
		checkG2(i); rotateG2(i); checkG2(i); saveG2(i); VFlipArrayG2(i); checkG2(i); recoverG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); VFlipArrayG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); checkG2(i);
		checkG2(i); rotateG2(i); checkG2(i); saveG2(i); VFlipArrayG2(i); checkG2(i); recoverG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); VFlipArrayG2(i); HFlipArrayG2(i); checkG2(i); recoverG2(i); checkG2(i);

		recoverOrigG2(i);

		sidesMap.insert(sidesMap.begin(), i);
		sar[i] = sidesMap;
		if (sidesMap.size() == 3) {
			mul *= grid[i].num;
			//printf("sides 2 -- %d\n", grid[i].num);
		} else {
			//printf("sides %d -- %d\n", (int)sidesMap.size(), grid[i].num);
		}
	}
	printf("mul is %llu\n", mul);

	//set <int> se;
	for (int kkk = 0; kkk < NUMG; kkk++) {
		for (int lll = 0; lll < NUMG; lll++) {
			if (kkk == lll) {continue;}
			checkGRIDsides2(kkk, lll, "left", "right", 1, 1);
			checkGRIDsides2(kkk, lll, "right", "left", 1, 1);
			checkGRIDsides2(kkk, lll, "top", "bottom", 1, 1);
			checkGRIDsides2(kkk, lll, "bottom", "top", 1, 1);
		}
	}

	printf("starting...\n"); fflush(stdout);

	initGG();
	printGG();

	//gg[0] = "1951";
	int pos = 0;
	{ ///TOPROW
		corner(-1, TOPLEFT, 0);
		for (int zz = 0; zz < sqrt(NUMG)-2; zz++) {
			edge(gg[zz+1], TOP, zz+1);
		}
		corner(gg[(int)sqrt(NUMG)-1], TOPRIGHT, (int)(sqrt(NUMG)-1));
	}
	printit();
		
	{////MIDROWS
		// 3(LEFT) 4(MIDDLE) 5 (RIGHT)
		for (int yy = 1; yy < (int)(sqrt(NUMG))-1; yy++) {
			int lenrowbyyy = lenrow * yy;
			printf("lenrowbyyy is %d\n", lenrowbyyy);
			edge(gg[lenrowbyyy], LEFT, lenrowbyyy);
			int xx;
			for (xx = 1; xx < lenrow-1; xx++) {
				nonEdge(gg[lenrowbyyy+xx], lenrowbyyy+xx);
			}
			edge(gg[lenrowbyyy+xx], RIGHT, lenrowbyyy+xx);
			printit();
		}
	}

	{//BOTTOMROW
		// 6 7 8
		corner(gg[lenrow*(lenrow-1)], BOTTOMLEFT, lenrow*(lenrow-1));
		for (int zz = 1; zz < sqrt(NUMG)-2; zz++) {
			edge(gg[lenrow*(lenrow-1)+zz], BOTTOM, lenrow*(lenrow-1)+zz);
		}
		corner(gg[NUMG-1], BOTTOMRIGHT, NUMG-1);
	}

	LEN = (GX-2)*sqrt(NUMG);
	transfer2MG();

	checkMG66();

	pos = 0;
	printf("\x1b[2J");
	for (int y = 0; y < sqrt(NUMG); y++) {
		for (int x = 0; x < sqrt(NUMG); x++) {
			if (gg[pos] != -1) {
				printGridANSI(gg[pos], (x*11)+3, (y*13)+3);
			} else {
				printf("0000");
			}
			pos++;
		}
	}
	printGridMG();

	printf("countMax is %d\n", countMax);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", roughM);
}
void printit() {
	int pos = 0;
	printf("\x1b[2J");
	for (int y = 0; y < sqrt(NUMG); y++) {
		for (int x = 0; x < sqrt(NUMG); x++) {
			if (gg[pos] != -1) {
				printGridANSI(gg[pos], (x*11)+3, (y*13)+3);
			} else {
				printf("0000");
			}
			pos++;
		}
	}
}
void transfer2MG() {
	int pos = 0;
	for (int y = 0; y < sqrt(NUMG); y++) {
		for (int x = 0; x < sqrt(NUMG); x++) {
			if (gg[pos] != -1) {
				trans(gg[pos], (x*8)+0, (y*8)+0);
			} else {
				printf("0000");
			}
			pos++;
		}
	}
}
void trans(int num, int sx, int sy) {
	int y; int x;
	for (y = 1; y < GX-1; y++) {
		for (x = 1; x < GX-1; x++) {
			gridMG[(y-1)+sy][(x-1)+sx] = grid[num].gr[y][x];
		}
	}
}

void printGridMG() {
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			printf("%c", gridMG[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

int printGridANSI(int num, int sx, int sy) {
	for (int y = 0; y < GX; y++) {
		if (y==0) {
			printf("\x1b[HZ");
			printf("\x1b[%dC", sx);
			printf("\x1b[%dB", sy+y);
			printf("Tile %d", grid[num].num);
			printf("\x1b[HZ");
			printf("\x1b[%dC", sx);
			printf("\x1b[%dB", sy+y+1);
		} else {
			printf("\x1b[HZ");
			printf("\x1b[%dC", sx);
			printf("\x1b[%dB", sy+y+1);
		}
		for (int x = 0; x < GX; x++) {
			printf("%c", grid[num].gr[y][x]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

void printGG() {
	for (int ii = 0; ii < NUMG; ii++) {
		if (gg[ii] == -1) {
			printf("0000 ");
		} else {
			printf("%d ", grid[gg[ii]].num);
		}
		if ((ii+1) % (int)sqrt(NUMG) == 0) {printf("\n");}
	}
	printf("\n");
}
void initGG() {
	for (int ii = 0; ii < NUMG; ii++) {
		gg[ii] = -1;
	}
}

void edge(int XX, int pos, int pp)
{
	if (pos == TOP)    {printf("TOP\n");}
	if (pos == LEFT)   {printf("LEFT\n");}
	if (pos == RIGHT)  {printf("RIGHT\n");}
	if (pos == BOTTOM) {printf("BOTTOM\n");}

	string a = "123";
	for (int kkk = 0; kkk < NUMG; kkk++) {
		//int first = 0;
		if ((int)sar[kkk].size() == 4) {
			switch (pos) {
				case TOP:
					{
						sort(a.begin(), a.end());
						do {
							int side1, side2, side3;
							for (int i = 1; i <= 3; i++) {
								switch(a[i-1]) {
									case '1':
										side1 = sar[kkk][i];
										break;
									case '2':
										side2 = sar[kkk][i];
										break;
									case '3':
										side3 = sar[kkk][i];
										break;
								}

							}
							assert(side1 != side2);
							assert(side2 != side3);
							//assert(pp == 1);
							if (sar[kkk][0] != gg[pp]) {goto NEXT;}
							//printf("calling checkGRIDsides4...\n");

							if (checkGRIDsides4(sar[kkk][0], side1, side2, side3, "right", "left", "top", "bottom", "left", "right", 0, 0, 0, 0) == 1) {
								//printf("return is 1....\n");
								assert(sar[kkk][0] == gg[pp]);	
								if (gg[pp-1] != side1) {goto TOPLAB;}
								gg[pp+1] = side3;
								gg[pp+lenrow] = side2; 

								printf("got T0P\n");
								return;
							}
TOPLAB:
							continue;
						} while (next_permutation(a.begin(), a.end()));
						break;
					}
				case LEFT:
					{
						assert(pp%12 == 0);
						//printf("in LEFT\n"); getchar();
						sort(a.begin(), a.end());
						do {
							int side1, side2, side3;
							for (int i = 1; i <= 3; i++) {
								switch(a[i-1]) {
									case '1':
										side1 = sar[kkk][i];
										break;
									case '2':
										side2 = sar[kkk][i];
										break;
									case '3':
										side3 = sar[kkk][i];
										break;
								}

							}
							assert(side1 != side2);
							assert(side2 != side3);
							if (sar[kkk][0] != gg[pp]) {goto NEXT;}
							if (checkGRIDsides4(sar[kkk][0], side1, side2, side3, "bottom", "top", "left", "right", "top", "bottom", 0, 0, 0, 0) == 1) {
								assert(sar[kkk][0] == gg[pp]);
								printf("warning...\n");
								if (side1 != gg[pp-lenrow]) {goto np;}
								assert(side1 == gg[pp-lenrow]);
								gg[pp+1] = side2;
								gg[pp+lenrow] = side3;
								printf("got LEFT\n");
								return;
							} else {
								printf("correct PP but not LEFT match...\n");
							}
np:
							continue;
						} while (next_permutation(a.begin(), a.end()));
						break;
					}
				case RIGHT:
					{
						assert((pp+1) % 12 == 0);
						sort(a.begin(), a.end());
						do {
							int side1, side2, side3;
							for (int i = 1; i <= 3; i++) {
								switch(a[i-1]) {
									case '1':
										side1 = sar[kkk][i];
										break;
									case '2':
										side2 = sar[kkk][i];
										break;
									case '3':
										side3 = sar[kkk][i];
										break;
								}

							}
							assert(side1 != side2);
							assert(side1 != side3);
							assert(side2 != side3);
							//assert(pp == 2);
							if (sar[kkk][0] != gg[pp]) {goto NEXT;}
							if (checkGRIDsides4(sar[kkk][0], side1, side2, side3, "bottom", "top", "right", "left", "top", "bottom", 0, 0, 0, 0) == 1) {
								assert(sar[kkk][0] == gg[pp]);
								////////////////WARNING//assert(side1 == gg[pp-lenrow]);
								if (side1 != gg[pp-lenrow]) {goto ag222;}
								printf("WARNING...\n");
								assert(gg[pp-1] == side2);
								gg[pp+lenrow] = side3;
								printf("got RIGHT\n");
								return;
							}
ag222:
							continue;
						} while (next_permutation(a.begin(), a.end()));
						break;
					}
				case BOTTOM:
					{
						sort(a.begin(), a.end());
						do {
							int side1, side2, side3;
							for (int i = 1; i <= 3; i++) {
								switch(a[i-1]) {
									case '1':
										side1 = sar[kkk][i];
										break;
									case '2':
										side2 = sar[kkk][i];
										break;
									case '3':
										side3 = sar[kkk][i];
										break;
								}

							}
							assert(side1 != side2);
							assert(side2 != side3);
							//assert(pp == 7);
							if (sar[kkk][0] != gg[pp]) {goto NEXT;}
							if (checkGRIDsides4(sar[kkk][0], side1, side2, side3, "right", "left", "bottom", "top", "left", "right", 0, 0, 0, 0) == 1) {
								assert(sar[kkk][0] == gg[pp]);
								if (side1 != gg[pp-1]) {goto BOTTOMLABEL;}
								assert(side1 == gg[pp-1]);
								if (side2 != gg[pp-lenrow]) {goto BOTTOMLABEL;}
								assert(side2 == gg[pp-lenrow]);
								gg[pp+lenrow] = side3;
								printf("got BOTTOM\n");
								return;
							}
BOTTOMLABEL:
							continue;
						} while (next_permutation(a.begin(), a.end()));
						break;
					}
			}
		}
NEXT:
		continue;
	}
}

void corner(int wat, int pos, int pp) {
	if (pos == TOPLEFT)     {printf("TOPLEFT\n");}
	if (pos == TOPRIGHT)    {printf("TOPRIGHT\n");}
	if (pos == BOTTOMLEFT)  {printf("BOTTOMLEFT\n");}
	if (pos == BOTTOMRIGHT) {printf("BOTTOMRIGHT\n");}

	for (int kkk = 0; kkk < NUMG; kkk++) {
		//int first = 0;
		if ((int)sar[kkk].size() == 3) {
			switch (pos) {
				case TOPLEFT:
					{
						if (checkGRIDsides3(sar[kkk][0], sar[kkk][1], sar[kkk][2], "left", "right", "top", "bottom", 0, 0, 0) == 1) {
							gg[0] = sar[kkk][0];
							gg[1] = sar[kkk][1];
							gg[lenrow] = sar[kkk][2];

							printf("got TOPLEFT\n");
							return;
						} else {
							if (checkGRIDsides3(sar[kkk][0], sar[kkk][2], sar[kkk][1], "left", "right", "top", "bottom", 0, 0, 0) == 1) {
								gg[0] = sar[kkk][0];
								gg[1] = sar[kkk][2];
								gg[lenrow] = sar[kkk][1];
								printf("got TOPLEFT\n");
								return;
							}
						}
						break;
					}
				case TOPRIGHT:
					{
						int swi = 0;
						//assert(pp == 2);
						if (sar[kkk][0] != gg[pp]) {goto NEC;}
						if (checkGRIDsides3(sar[kkk][0], sar[kkk][1], sar[kkk][2], "right", "left", "top", "bottom", 0, 0, 0) == 1) {
							assert(sar[kkk][0] == gg[pp]);
							if (gg[pp-1] != sar[kkk][1]) {swi = 1; goto TOPRIGHTLABEL;}
							//gg[1] = sar[kkk][1];
							gg[pp+lenrow] = sar[kkk][2];
							printf("got TOPRIGHT\n");
							return;
						} else {
							swi = 1;
						}
TOPRIGHTLABEL:

						if (swi == 1) {
							if (checkGRIDsides3(sar[kkk][0], sar[kkk][2], sar[kkk][1], "right", "left", "top", "bottom", 0, 0, 0) == 1) {
								if (sar[kkk][0] != gg[pp]) {goto NEC;}
								assert(sar[kkk][0] == gg[pp]);
								assert(gg[pp-1] == sar[kkk][2]);
								gg[pp+lenrow] = sar[kkk][1];
								printf("got TOPRIGHT\n");
								return;
							}
						}

						break;
					}
				case BOTTOMLEFT:
					{
						int swi = 0;
						//assert(pp == 6);
						if (sar[kkk][0] != gg[pp]) {/*printf("trying another kkk\n");*/ goto NEC;}
						//printf("running checkGRIDsides3...\n");
						//printf("%d right:%d top:%d\n", grid[sar[kkk][0]].num, grid[sar[kkk][1]].num, grid[sar[kkk][2]].num);
						//printf("check.%d V %d..\n", gg[3], sar[kkk][2]);
						if (checkGRIDsides3(sar[kkk][0], sar[kkk][1], sar[kkk][2], "left", "right", "bottom", "top", 0, 0, 0) == 1) {
							//printf("non swi ret1 BL\n");
							if (gg[pp-lenrow] != sar[kkk][2]) {swi = 1; /*printf("goto.%d V %d V %d..\n", gg[3], sar[kkk][1], sar[kkk][2]); getchar();*/ goto BOTTOMLEFTLABEL;}

							assert(gg[pp-lenrow] == sar[kkk][2]);
							gg[pp+1] = sar[kkk][1];
							printf("got BOTTOMLEFT\n");
							return;
						} else {
							//printf("BL ret was 0...\n");
							swi = 1;
						}	       
BOTTOMLEFTLABEL:
						if (swi == 1)
						{

							//printf("in switch...\n");
							//printf("%d right:%d top:%d\n", grid[sar[kkk][0]].num, grid[sar[kkk][2]].num, grid[sar[kkk][1]].num);

							if (checkGRIDsides3(sar[kkk][0], sar[kkk][2], sar[kkk][1], "left", "right", "bottom", "top", 0, 0, 0) == 1) { 
								//printf("in switch ret is 1\n");
								if (gg[pp-lenrow] != sar[kkk][1]) {swi = 1; printf("goto.%d V %d V %d..\n", gg[pp-lenrow], sar[kkk][1], sar[kkk][2]); goto NEC;}
								assert(gg[pp-lenrow] == sar[kkk][1]);
								gg[pp+1] = sar[kkk][1];
								printf("got BOTTOMLEFT\n");
								return;
							} else {
								//printf("BL ret was 0...\n");
							}	       
							break;
						}
					}
				case BOTTOMRIGHT:
					{
						int swi = 0;
						if (sar[kkk][0] != gg[pp]) {goto NEC;}
						if (checkGRIDsides3(sar[kkk][0], sar[kkk][1], sar[kkk][2], "right", "left", "bottom", "top", 0, 0, 0) == 1) {
							if (sar[kkk][0] != gg[pp]) {goto NEC;}
							assert(sar[kkk][0] == gg[pp]);
							if (gg[pp-lenrow] != sar[kkk][2]) {swi = 1; goto BOTTOMRIGHTLABEL;}
							if (gg[pp-1] != sar[kkk][1]) {swi = 1; goto BOTTOMRIGHTLABEL;}
							assert(gg[pp-1] == sar[kkk][1]);
							printf("got BOTTOMRIGHT\n"); getchar();
							return;
						}  else {
							swi = 1;
						}
BOTTOMRIGHTLABEL:
						if (swi == 1) {
							if (checkGRIDsides3(sar[kkk][0], sar[kkk][2], sar[kkk][1], "right", "left", "bottom", "top", 0, 0, 0) == 1) {
								if (sar[kkk][0] != gg[pp]) {goto NEC;}
								assert(sar[kkk][0] == gg[pp]);
								assert(gg[pp-lenrow] == sar[kkk][1]);
								assert(gg[pp-1] == sar[kkk][2]);
								printf("got BOTTOMRIGHT\n"); getchar();
								return;
							}
						}

						break;
					}
			}
		}
NEC:
		continue;
	}
}

void nonEdge(int XX, int pp) {
	printf("MIDDLE\n");
	for (int kkk = 0; kkk < leny; kkk++) {
		if ((int)sar[kkk].size() != 5) {continue;}
		string a = "1234"; sort(a.begin(), a.end());
		do {
			int side1, side2, side3, side4;
			for (int i = 1; i <= 4; i++) {
				switch(a[i-1]) {
					case '1':
						side1 = sar[kkk][i];
						break;
					case '2':
						side2 = sar[kkk][i];
						break;
					case '3':
						side3 = sar[kkk][i];
						break;
					case '4':
						side4 = sar[kkk][i];
						break;
				}

			}
			assert(side1 != side2);
			assert(side2 != side3);
			assert(side2 != side4);
			if (sar[kkk][0] != gg[pp]) {goto NEX;}
			if (checkGRIDsides5(sar[kkk][0], side1,
						side2, side3, side4, "right", "left", "top", "bottom", "left", "right", "bottom", "top", 0, 0, 0, 0, 0) == 1) {
				if (gg[pp-1] != side1) {goto MIDDLE;} 
				if (gg[pp-lenrow] != side4) {goto MIDDLE;}
				gg[pp+lenrow] = side2;
				gg[pp+1] = side3;
				printf("got MIDDLE\n");
				return;
			}
MIDDLE:
			continue;
		} while (next_permutation(a.begin(), a.end()));
NEX:
		continue;
	}
}

int printGridG2(int num) {
	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			printf("%c", gridG2[num].gr[y][x]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

void HFlipArrayG2(int gridNum)
{
	vector <vector<char>> ve = gridG2[gridNum].gr;
	int rows = GX;
	for (int row = 0; row < GX/2; row++)
	{
		vector <char> vetmp = ve[row];
		ve[row] = ve[rows-1-row];
		ve[rows-1-row] = vetmp;
	}
	gridG2[gridNum].gr = ve;
}

void VFlipArrayG2(int gridNum)
{
	vector <vector<char>> ve = gridG2[gridNum].gr;

	for (int row = 0; row < GX; row++) {
		for (int col = 0; col < GX/2; col++)
		{
			//0 -> 9;
			//1 -> 8;
			//2 -> 7;
			//3 -> 6;
			//4 -> 5;
			char tmp = ve[row][GX-1-col];
			ve[row][GX-1-col] = ve[row][col];
			ve[row][col] = tmp;
		}
	}
	gridG2[gridNum].gr = ve;
}

int printGrid(int num) {
	//int sq = (int)strlen(grid[num].gr[0]); //is a square

	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			printf("%c", grid[num].gr[y][x]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

void HFlipArray(int gridNum)
{
	vector <vector<char>> ve = grid[gridNum].gr;
	int rows = GX;
	for (int row = 0; row < GX/2; row++)
	{
		vector <char> vetmp = ve[row];
		ve[row] = ve[rows-1-row];
		ve[rows-1-row] = vetmp;
	}
	grid[gridNum].gr = ve;
}

void VFlipArray(int gridNum)
{
	vector <vector<char>> ve = grid[gridNum].gr;

	for (int row = 0; row < GX; row++) {
		for (int col = 0; col < GX/2; col++)
		{
			//0 -> 9;
			//1 -> 8;
			//2 -> 7;
			//3 -> 6;
			//4 -> 5;
			char tmp = ve[row][GX-1-col];
			ve[row][GX-1-col] = ve[row][col];
			ve[row][col] = tmp;
		}
	}
	grid[gridNum].gr = ve;
}


void saveOrigG2(int i) {
	gridOrig[i] = gridG2[i];
}


void recoverOrigG2(int i) {
	gridG2[i] = gridOrig[i];
}

void saveOrig(int i) {
	gridOrig[i] = grid[i];
}


void recoverOrig(int i) {
	grid[i] = gridOrig[i];
}


///////////////
void saveg2(int i) {
	gridtmpg2 = grid[i]; return;
}
void recoverg2(int i) {
	grid[i] = gridtmpg2; return;
}
//////////////
void saveMG() {
	for (int y = 0; y < LEN; y++) {
		strcpy(gridtmpMG[y], gridMG[y]);
	}

}
void recoverMG() {
	for (int y = 0; y < LEN; y++) {
		strcpy(gridMG[y], gridtmpMG[y]);
	}
}

//////////////
void save(int i) {
	gridtmp = grid[i]; return;
}
void recover(int i) {
	grid[i] = gridtmp; return;
}
///////////////
///////////////////
void saveG2(int i) {
	gridtmpG2 = gridG2[i];
}

void recoverG2(int i) {
	gridG2[i] = gridtmpG2;
}
///////////////////

int checkGRIDsides5(int g1, int g2, int g3, int g4, int g5, string pos1, string pos2, string pos3, string pos4, string pos5, string pos6, string pos7, string pos8, int moveFirst, int moveSecond, int moveThird, int moveFourth, int moveFifth) {
	if (moveFirst  == 1) {recoverOrig(g1);}
	if (moveSecond == 1) {recoverOrig(g2);}
	if (moveThird  == 1) {recoverOrig(g3);}
	if (moveFourth == 1) {recoverOrig(g4);}
	if (moveFifth == 1)  {recoverOrig(g5);}

	int ret1 = 0; int ret2; int ret3; int ret4;
	int ii = 0; int ii2; int ii3; int ii4;
	int max1 = (int)ways[g1][getPos(pos1, pos2)].size();
	int max2 = (int)ways[g1][getPos(pos3, pos4)].size();
	int max3 = (int)ways[g1][getPos(pos5, pos6)].size();
	int max4 = (int)ways[g1][getPos(pos7, pos8)].size();

checkAgain5:
	ret1 = 0; ret2 = 0; ret3 = 0; ret4 = 0;
	for (; ii < max1; ii += 2) {
		if (grid[g1].num != ways[g1][getPos(pos1, pos2)][ii].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos1, pos2)][ii].num);
		grid[g1] = ways[g1][getPos(pos1, pos2)][ii];

		if (grid[g2].num != ways[g1][getPos(pos1, pos2)][ii+1].num) {continue; }
		assert(grid[g2].num == ways[g1][getPos(pos1, pos2)][ii+1].num);
		grid[g2] = ways[g1][getPos(pos1, pos2)][ii+1];

		if (checkGRIDsides2(g1, g2, pos1, pos2, moveFirst, moveSecond) == 0) {continue;} else {ret1 = 1; /*printf("side5--g1 g2 match\n");*/ break;}
	}
	//printf("part 2 of sides 3...%d, %d\n", g1, g3);

	if (ret1 != 1) {/*printf("ret1 not one\n");*/ if (ii != max1) {goto checkAgain5;} else {return 0;}}
	ret2 = 0;
	ii2 = 0;
m2:
	for (; ii2 < max2; ii2+=2 ) {
		if (grid[g1].gr != ways[g1][getPos(pos3, pos4)][ii2].gr) {continue;}
		if (grid[g1].num != ways[g1][getPos(pos3, pos4)][ii2].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos3, pos4)][ii2].num);
		//grid[g1] = ways[g1][getPos(pos3, pos4)][ii2];

		if (grid[g3].num != ways[g1][getPos(pos3, pos4)][ii2+1].num) {continue;}
		assert(grid[g3].num == ways[g1][getPos(pos3, pos4)][ii2+1].num);
		grid[g3] = ways[g1][getPos(pos3, pos4)][ii2+1];

		if (checkGRIDsides2(g1, g3, pos3, pos4, moveFirst, moveThird) == 0) {continue;} else {ret2 = 1; /*printf("side5--g1 g3 match\n");*/ break;}
	}

	//recoverOrig(g1);
	//recoverOrig(g4);
	if (ret2 != 1) {/*printf("ret2 not one\n"); */ if (ii < max1) {ii+=2; goto checkAgain5;}}
	ii3 = 0;
m3:
	for (; ii3 < max3; ii3+=2) {
		//printf("conor3.. sides5\n");
		if (grid[g1].gr != ways[g1][getPos(pos5, pos6)][ii3].gr) {continue;}
		if (grid[g1].num != ways[g1][getPos(pos5, pos6)][ii3].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos5, pos6)][ii3].num);
		//grid[g1] = ways[g1][getPos(pos5, pos6)][ii3];

		if (grid[g4].num != ways[g1][getPos(pos5, pos6)][ii3+1].num) {continue;}
		assert(grid[g4].num == ways[g1][getPos(pos5, pos6)][ii3+1].num);
		grid[g4] = ways[g1][getPos(pos5, pos6)][ii3+1];

		if (checkGRIDsides2(g1, g4, pos5, pos6, moveFirst, moveFourth) == 0) {continue;} else {ret3 = 1; /* printf("side5--g1 g4 match\n"); */ break;}
	}

	if (ret3 != 1) {/*printf("ret2 not one\n"); */ if (ii2 < max2) {ii2+=2; goto m2;} else if (ii < max1) {ii+=2; goto checkAgain5;}}

	for (ii4 = 0; ii4 < max4; ii4+=2) {
		if (grid[g1].gr != ways[g1][getPos(pos7, pos8)][ii4].gr) {continue;}
		if (grid[g1].num != ways[g1][getPos(pos7, pos8)][ii4].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos7, pos8)][ii4].num);
		//grid[g1] = ways[g1][getPos(pos7, pos8)][ii4];

		if (grid[g5].num != ways[g1][getPos(pos7, pos8)][ii4+1].num) {continue;}
		assert(grid[g5].num == ways[g1][getPos(pos7, pos8)][ii4+1].num);
		grid[g5] = ways[g1][getPos(pos7, pos8)][ii4+1];

		if (checkGRIDsides2(g1, g5, pos7, pos8, moveFirst, moveFifth) == 0) {continue;} else {ret4 = 1; /*printf("side5--g1 g5 match\n"); */ break;}
	}
	if ((ret1 & ret2 & ret3 & ret4) != 1) {if (ii3 < max3) {ii3+=2; goto m3;} else if (ii2 < max2) {ii2+=2; goto m2;} else if (ii < max1) {ii+=2; goto checkAgain5;} else {return 0;}}
	return ret1 & ret2 & ret3 & ret4;
}

int checkGRIDsides4(int g1, int g2, int g3, int g4, string pos1, string pos2, string pos3, string pos4, string pos5, string pos6, int moveFirst, int moveSecond, int moveThird, int moveFourth) {

	if (moveFirst  == 1) {recoverOrig(g1);}
	if (moveSecond == 1) {recoverOrig(g2);}
	if (moveThird  == 1) {recoverOrig(g3);}
	if (moveFourth == 1) {recoverOrig(g4);}

	int ret1 = 0; int ret2; int ret3;
	int ii = 0; int ii2; int ii3;
	int max1 = (int)ways[g1][getPos(pos1, pos2)].size();
	int max2 = (int)ways[g1][getPos(pos3, pos4)].size();
	int max3 = (int)ways[g1][getPos(pos5, pos6)].size();
checkAgain:
	ret1 = 0; ret2 = 0; ret3 = 0;
	for (; ii < max1; ii += 2) {
		//printf("conor2..1. sides4\n");
		if (grid[g1].num != ways[g1][getPos(pos1, pos2)][ii].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos1, pos2)][ii].num);
		grid[g1] = ways[g1][getPos(pos1, pos2)][ii];

		//assert((int)ways[g1][getPos(pos1, pos2)].size() >= 2);

		if (grid[g2].num != ways[g1][getPos(pos1, pos2)][ii+1].num) {fflush(stdout); continue;} else {}
		assert(grid[g2].num == ways[g1][getPos(pos1, pos2)][ii+1].num);
		{grid[g2] = ways[g1][getPos(pos1, pos2)][ii+1];}

		///if (checkGRIDsides2(g1, g2, pos1, pos2, moveFirst, moveSecond) == 0) {continue;} else {ret1 = 1; /* printf("side4--g1 g2 match\n");*/ break;}
		if (checkGRIDcur(g1, g2, pos1, pos2, moveFirst, moveSecond) == 0) {continue;} else {ret1 = 1;  printf("side4--g1 g2 match\n"); break;}
	}
	//printf("part 2 of sides 3...%d, %d\n", g1, g3);

	if (ret1 != 1) {/*printf("ret1 not one\n");*/ if (ii < max1) {ii+=2; goto checkAgain;} else {return 0;}}
	ii2 = 0;
ca2:
	for (; ii2 < max2; ii2+=2 ) {
		//printf("conor1... sides4\n");
		if (grid[g1].gr != ways[g1][getPos(pos3, pos4)][ii2].gr) {continue;}
		if (grid[g1].num != ways[g1][getPos(pos3, pos4)][ii2].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos3, pos4)][ii2].num);
		//grid[g1] = ways[g1][getPos(pos3, pos4)][ii2];

		if (grid[g3].num != ways[g1][getPos(pos3, pos4)][ii2+1].num) {continue;} else {}
		assert(grid[g3].num == ways[g1][getPos(pos3, pos4)][ii2+1].num);
		{grid[g3] = ways[g1][getPos(pos3, pos4)][ii2+1];}

		//if (checkGRIDsides4(g1, g3, pos3, pos4, moveFirst, moveThird) == 0) {continue;} else {ret2 = 1; printf("side4--g1 g3 match\n"); break;} 
		if (checkGRIDcur(g1, g3, pos3, pos4, moveFirst, moveThird) == 0) {continue;} else {ret2 = 1; printf("side4--g1 g3 match\n"); break;} 
	}

	//recoverOrig(g1);
	//recoverOrig(g4);
	//printf("part3....\n");
	if (ret2 != 1) {/*printf("ret2 not one\n"); */if (ii < max1) {ii+=2; goto checkAgain;}}

	printf("part3...: ways size is %d\n", (int)ways[g1][getPos(pos5, pos6)].size()); fflush(stdout); getchar();

	for (ii3 = 0; ii3 < max3; ii3+=2) {
		//printf("conor3.. sides4\n");
		if (grid[g1].gr != ways[g1][getPos(pos5, pos6)][ii3].gr) {continue;}
		if (grid[g1].num != ways[g1][getPos(pos5, pos6)][ii3].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos5, pos6)][ii3].num);
		//grid[g1] = ways[g1][getPos(pos5, pos6)][ii3];

		if (grid[g4].num != ways[g1][getPos(pos5, pos6)][ii3+1].num) {continue;} else {}
		assert(grid[g4].num == ways[g1][getPos(pos5, pos6)][ii3+1].num);
		{grid[g4] = ways[g1][getPos(pos5, pos6)][ii3+1];}

		//if (checkGRIDsides2(g1, g4, pos5, pos6, moveFirst, moveFourth) == 0) {continue;} else {ret3 = 1; /* printf("side4--g1 g4 match\n"); */ break;}
		if (checkGRIDcur(g1, g4, pos5, pos6, moveFirst, moveFourth) == 0) {continue;} else {ret3 = 1; printf("side4--g1 g4 match\n"); break;}
	}
	if ((ret1 & ret2 & ret3) != 1) {if (ii2 != max2) {ii2+=2; goto ca2;} if (ii < max1) {ii+=2;goto checkAgain;}}
	return ret1 & ret2 & ret3;

}

int getPos(string p1, string p2) {
	if (p1 == "bottom" && p2 == "top") {
		return 0;
	} else if (p1 == "top" && p2 == "bottom") {
		return 1;
	} else if (p1 == "right" && p2 == "left") {
		return 2;
	} else if (p1 == "left" && p2 == "right") {
		return 3;
	}
	return -1;
}

int checkGRIDsides33333(int g1, int g2, int g3, string pos1, string pos2, string pos3, string pos4, int moveFirst, int moveSecond, int moveThird) {
	if (moveFirst ==  1) {recoverOrig(g1);}
	if (moveSecond == 1) {recoverOrig(g2);}
	if (moveThird ==  1) {recoverOrig(g3);}

	//printf("part 1 of sides 3...%d, %d\n", g1, g2);
	//recoverOrig(g1);
	//recoverOrig(g2);
	int ii = 0; int ii2;
	//int max1 = (int)ways[g1][getPos(pos1, pos2)].size();
	//int max2 = (int)ways[g1][getPos(pos3, pos4)].size();
	int ret1 = 0; int ret2; 
	//printf("XXX size %d-----\n", (int)ways[g1][getPos(pos1, pos2)].size());
	int max1 = (int)ways[g1][getPos(pos1, pos2)].size();
	int max2 = (int)ways[g1][getPos(pos3, pos4)].size();

checkAgain33333:
	ret1 = 0; ret2 = 0;
	printf("FIRST: ways[g1][getPos(pos1, pos2)].size() %d ----- \n", (int)ways[g1][getPos(pos1, pos2)].size());
	for (; ii < max1; ii+=2) {
		if (grid[g1].num != ways[g1][getPos(pos1, pos2)][ii].num) {printf("p1, grid1 not right\n"); continue;}
		assert(grid[g1].num == ways[g1][getPos(pos1, pos2)][ii].num);
		grid[g1] = ways[g1][getPos(pos1, pos2)][ii];

		if (grid[g2].num != ways[g1][getPos(pos1, pos2)][ii+1].num) {
			printf("g2 num not right %d V %d\n", grid[g2].num, ways[g1][getPos(pos1, pos2)][ii+1].num);
			continue;
		}
		assert(grid[g2].num == ways[g1][getPos(pos1, pos2)][ii+1].num);
		{grid[g2] = ways[g1][getPos(pos1, pos2)][ii+1];}

		if (checkGRIDcur(g1, g2, pos1, pos2, 1, 1) == 0) {printf("p1 checkGRIDsides2 zero\n"); continue;} else {ret1 = 1; printf("g1 g2 match\n"); break;}
	}

	printf("part 2 of sides 3...%d, %d\n", g1, g3);

	if (ret1 != 1) {/*printf("ret1 not one\n");  printf("ii V max1 %d V %d\n", ii, max1);*/ if (ii < max1) {ii+=2; goto checkAgain33333;} else {return 0;}} else {/*printf("ret1 is 1\n");*/}
	cout << pos3 << " V " << pos4 << endl;
	printf("SECOND: ways[g1][getPos(pos3, pos4)].size() %d ----- \n", (int)ways[g1][getPos(pos3, pos4)].size());
	for (ii2 = 0; ii2 < max2; ii2+=2) {
		if (grid[g1].num != ways[g1][getPos(pos3, pos4)][ii2].num) {printf("p2: num not a match\n"); continue;} else {printf("p2: num a match\n");}
		if (grid[g1].gr != ways[g1][getPos(pos3, pos4)][ii2].gr) {printf("p2: g1 not a match\n"); continue;} else {printf("p2: g1 a match\n");}
		assert(grid[g1].num == ways[g1][getPos(pos3, pos4)][ii2].num); ///grid[g1] = ways[g1][getPos(pos3, pos4)][ii2];

		if (grid[g3].num != ways[g1][getPos(pos3, pos4)][ii2+1].num) {printf("p2: g3 not a match\n"); continue;} else {printf("p2: g3 a match\n");}
		assert(grid[g3].num == ways[g1][getPos(pos3, pos4)][ii2+1].num);
		{grid[g3] = ways[g1][getPos(pos3, pos4)][ii2+1];}

		if (checkGRIDcur(g1, g3, pos3, pos4, 1, 1) == 0) {continue;} else {ret2 = 1; printf("g1 g3 match\n");break;}
	}
	if (ret2 != 1) {/*printf("ret2 not one\n"); printf("ii V max1 %d V %d ii2 %d\n", ii, max1, ii2);*/ if (ii < max1) {ii+=2; goto checkAgain33333;}}
	return ret1 & ret2;
}
int checkGRIDsides3(int g1, int g2, int g3, string pos1, string pos2, string pos3, string pos4, int moveFirst, int moveSecond, int moveThird) {
	if (moveFirst ==  1) {recoverOrig(g1);}
	if (moveSecond == 1) {recoverOrig(g2);}
	if (moveThird ==  1) {recoverOrig(g3);}

	//printf("part 1 of sides 3...%d, %d\n", g1, g2);
	//recoverOrig(g1);
	//recoverOrig(g2);
	int ii = 0; int ii2;
	//int max1 = (int)ways[g1][getPos(pos1, pos2)].size();
	//int max2 = (int)ways[g1][getPos(pos3, pos4)].size();
	int ret1 = 0; int ret2; 
	//printf("XXX size %d-----\n", (int)ways[g1][getPos(pos1, pos2)].size());
	int max1 = (int)ways[g1][getPos(pos1, pos2)].size();
	int max2 = (int)ways[g1][getPos(pos3, pos4)].size();

checkAgain2:
	ret1 = 0; ret2 = 0;
	for (; ii < max1; ii+=2) {
		if (grid[g1].num != ways[g1][getPos(pos1, pos2)][ii].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos1, pos2)][ii].num);
		grid[g1] = ways[g1][getPos(pos1, pos2)][ii];

		if (grid[g2].num != ways[g1][getPos(pos1, pos2)][ii+1].num) {
			//printf("%d V %d\n", grid[g2].num, ways[g1][getPos(pos1, pos2)][ii+1].num);
			continue;
		}
		assert(grid[g2].num == ways[g1][getPos(pos1, pos2)][ii+1].num);
		{grid[g2] = ways[g1][getPos(pos1, pos2)][ii+1];}

		if (checkGRIDsides2(g1, g2, pos1, pos2, moveFirst, moveSecond) == 0) {continue;} else {ret1 = 1;/* printf("g1 g2 match\n");*/ break;}
	}

	//if (checkGRIDsides2(g1, g2, pos1, pos2, moveFirst, moveSecond) == 0) {} else {printf("sides3--g1 g2 match\n");}
	//printf("part 2 of sides 3...%d, %d\n", g1, g3);

	//recoverOrig(g1);
	//recoverOrig(g3);
	if (ret1 != 1) {/*printf("ret1 not one\n"); */ printf("here1... ii V max1 %d V %d\n", ii, max1); if (ii < max1) {ii+=2; goto checkAgain2;}}
	//printf("size %d ----- \n", (int)ways[g1][getPos(pos3, pos4)].size());
	for (ii2 = 0; ii2 < max2; ii2+=2) {
		if (grid[g1].gr != ways[g1][getPos(pos3, pos4)][ii2].gr) {continue;}
		if (grid[g1].num != ways[g1][getPos(pos3, pos4)][ii2].num) {continue;}
		assert(grid[g1].num == ways[g1][getPos(pos3, pos4)][ii2].num);
		///grid[g1] = ways[g1][getPos(pos3, pos4)][ii2];

		if (grid[g3].num != ways[g1][getPos(pos3, pos4)][ii2+1].num) {continue;}
		assert(grid[g3].num == ways[g1][getPos(pos3, pos4)][ii2+1].num);
		{grid[g3] = ways[g1][getPos(pos3, pos4)][ii2+1];}

		if (checkGRIDsides2(g1, g3, pos3, pos4, moveFirst, moveThird) == 0) {continue;} else {ret2 = 1; /*printf("g1 g3 match\n");*/break;}
	}
	//if (checkGRIDsides2(g1, g3, pos3, pos4, moveFirst, moveThird) == 0) {} else {printf("sides3--g1 g3 match\n");}
	if (ret2 != 1) {/*printf("ret2 not one\n");*/ /*printf("here2...ii V max1 %d V %d ii2 %d\n", ii, max1, ii2); */ if (ii < max1) {ii+=2; goto checkAgain2;}}
	return ret1 & ret2;
}

int checkGRIDcur(int g1, int g2, string pos1, string pos2, int moveFirst, int moveSecond) {
	return blah66(g1, g2, pos1, pos2, moveFirst, moveSecond);
}

int checkGRIDsides2(int g1, int g2, string pos1, string pos2, int moveFirst, int moveSecond) {
	int i = g1;
	int ret = 0;
	if (moveFirst ==  1) {recoverOrig(g1);}
	if (moveSecond == 1) {recoverOrig(g2);}

	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;} //one
	if (moveFirst == 0) {return ret;}
	save(i); 
	rotate(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//two
	rotate(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//three
	rotate(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//four
	recover(i);
	rotate(i); 
	VFlipArray(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//five
	recover(i);
	VFlipArray(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//six
	recover(i);
	HFlipArray(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//seven
	recover(i);
	rotate(i); 
	HFlipArray(i);
	if (check66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//eight

	if (moveFirst ==  1) {recoverOrig(g1);}
	if (moveSecond == 1) {recoverOrig(g2);}
	return ret;
}
int check66(int g1, int g2, string pos1, string pos2, int moveFirst, int moveSecond) {
	int i = g2; ////iiiiiii iiiissss g2.....
	int ret = 0;
	if (moveSecond == 1) {recoverOrig(g2);}

	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;} //one
	if (moveFirst == 0) {return ret;}
	saveg2(i); 
	rotate(i); //two
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//two
	rotate(i); //three
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//three
	rotate(i); //four
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//four

	recoverg2(i);
	rotate(i); 
	VFlipArray(i);
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//five

	recoverg2(i);
	VFlipArray(i);
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//six

	recoverg2(i);
	HFlipArray(i);
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//seven

	recoverg2(i);
	rotate(i); 
	HFlipArray(i);
	if (blah66(g1, g2, pos1, pos2, moveFirst, moveSecond) == 1) {ret = 1;}//eight
	if (moveSecond == 1) {recoverOrig(g2);}
	return ret;
}
void checkMG66() {

	mammoth.clear();
	for (int y = 0; y < (int)3; y++) {
		for (int x = 0; x < (int)strlen(seaM[y]); x++) {
			if (seaM[y][x] == '#') {
				mammoth.push_back({x,y});
			}
		}
	}
	printf("mammoth.size() is %d (15)\n", (int)mammoth.size());

	//printf("first\n"); printGridMG(); getchar();
	blahMG66();
	saveMG(); 

	rotateMG();
	//printf("second.(rotate)..\n"); printGridMG(); getchar();

	blahMG66();
	rotateMG();
	blahMG66();
	//printf("third...(rotate)\n"); printGridMG(); getchar();

	rotateMG();
	blahMG66();
	//printf("fourth...(rotate)\n"); printGridMG(); getchar();

	recoverMG();
	rotateMG(); 
	VFlipArrayMG();
	blahMG66();
	printf("fifth...rotate VFlip\n"); printGridMG(); getchar();

	recoverMG();
	VFlipArrayMG();
	blahMG66();
	//printf("sixth..Vflip.\n"); printGridMG(); getchar();

	recoverMG();
	HFlipArrayMG();
	blahMG66();
	//printf("seventh..HFlip.\n"); printGridMG(); getchar();

	recoverMG();
	rotateMG(); 
	HFlipArrayMG();
	//printf("eight.rotate HFlip..\n"); printGridMG(); getchar();
	blahMG66();
	printf("countMax now is %d\n", countMax);

}

int blahMG66() {

	int count = 0;
	int l1 = (int)strlen(seaM[0]);
	for (int y = 0; y <= LEN-3; y++) {
		for (int x = 0; x <= LEN-l1; x++) {
			int found = 0;
			for (auto papa: mammoth) {
				if (gridMG[papa.second+y][papa.first+x] == '#' || gridMG[papa.second+y][papa.first+x] == 'O') {} else {found = 1; break;}
			}
			if (found == 0) {
				for (auto papa: mammoth) {
					if (gridMG[papa.second+y][papa.first+x] == '#') {gridMG[papa.second+y][papa.first+x] = 'O';}
				}

				count++;
			}
		}
	}

	printf("check for sea mammoths.count %d..\n", count);
	int rough = 0;
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			if (gridMG[y][x] == '#') {
				rough++;
			}
		}
	}

	if (count > countMax) {countMax = count; roughM = rough;}
	return count;
}
int blah66(int first, int second, string pos1, string pos2, int moveFirst, int moveSecond) {
	int i = first; int j = second;
	int abber = 0;
	int ret = 0;
	int blah1 = 0;

	//if (grid[first].num == 3079) {blah1 = 1;}

	//printf("first is %d second is %d\n", first, second);
	int pX = getPos(pos1, pos2);
	if (pX == 3 && pos1 == "left" && pos2 == "right") {
		for (int y = 0; y < GX; y++) {
			if (grid[i].gr[y][GX-1] == grid[j].gr[y][0]) {
			} else {
				abber = 1;
				break;
			}
		}
		if (abber == 0) {
			if (blah1 == 1 && grid[second].num == 2473) {
				//printGrid(first);
				//printGrid(second);
				///printf("--------------\n");
			}
			if (moveFirst == 1 && moveSecond == 1) {
				int found = 0;
				for (int ii = 0; ii < (int)ways[first][pX].size(); ii+=2) {
					if (ways[first][pX][ii] == grid[i] && ways[first][pX][ii+1] == grid[j]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					ways[first][pX].push_back(grid[i]);
					ways[first][pX].push_back(grid[j]);
				}
			}
			return 1;
		}
		return 0;
	}

	abber = 0;
	if (pX == 2 && pos1 == "right" && pos2 == "left") {
		for (int y = 0; y < GX; y++) {
			if (grid[i].gr[y][0] == grid[j].gr[y][GX-1]) {
			} else {
				abber = 1;
				break;
			}
		}
		if (abber == 0) {
			if (moveFirst == 1 && moveSecond == 1) {
				int found = 0;
				for (int ii = 0; ii < (int)ways[first][pX].size(); ii+=2) {
					if (ways[first][pX][ii] == grid[i] && ways[first][pX][ii+1] == grid[j]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					ways[first][pX].push_back(grid[i]);
					ways[first][pX].push_back(grid[j]);
				}
			}
			return 1;
		}
		return 0;
	}

	abber = 0;
	if (pX == 1 && pos1 == "top" && pos2 == "bottom") {
		for (int x = 0; x < GX; x++) {
			if (grid[i].gr[GX-1][x] == grid[j].gr[0][x]) {
			} else {
				abber = 1;
				break;
			}
		}

		if (abber == 0) {
			if (moveFirst == 1 && moveSecond == 1) {
				int found = 0;
				for (int ii = 0; ii < (int)ways[first][pX].size(); ii+=2) {
					if (ways[first][pX][ii] == grid[i] && ways[first][pX][ii+1] == grid[j]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					ways[first][pX].push_back(grid[i]);
					ways[first][pX].push_back(grid[j]);
				}
			}
			return 1;
		}
		return 0;
	}

	abber = 0;
	if (pX == 0 && pos1 == "bottom" && pos2 == "top") {
		for (int x = 0; x < GX; x++) {
			if (grid[i].gr[0][x] == grid[j].gr[GX-1][x]) {
				//printf("same tibj\n"); fflush(stdout);
			} else {
				abber = 1;
				break;
			}
		}
		if (abber == 0) {
			if (blah1 == 1 && grid[second].num == 2311) {
				//printGrid(first);
				//printGrid(second);
				//printf("--------------\n");
			}
			if (moveFirst == 1 && moveSecond == 1) {
				int found = 0;
				for (int ii = 0; ii < (int)ways[first][pX].size(); ii+=2) {
					if (ways[first][pX][ii] == grid[i] && ways[first][pX][ii+1] == grid[j]) {
						found = 1; break;
					}
				}
				if (found == 0) {
					ways[first][pX].push_back(grid[i]);
					ways[first][pX].push_back(grid[j]);
				}
			} else {
				//printf("bottom top aber zero\n");
			}
			return 1;
		}
		return 0;
	}

	return ret;
}

//void rotate(vector<vector<int>>& mat)
void rotateG2(int gNum) {
	vector <vector<char>> mat = gridG2[gNum].gr;
	int n = mat[0].size();

	// Initialize the result matrix with zeros
	//vector<vector<char>> res(n, vector<char>(n));
	vector<vector<char>> res = mat;

	// Flip the matrix clockwise using nested loops
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[j][n - i - 1] = mat[i][j];
		}
	}

	gridG2[gNum].gr = res;

}


void HFlipArrayMG()
{
	for (int x = 0; x < (int)LEN; x++) {
		for (int y = 0; y < (int)LEN/2; y++) {
			char tmp = gridMG[y][x];
			char tmp1 = gridMG[LEN-1-y][x];
			//printf("y -> LEN-y %d->%d\n", y, LEN-1-y);
			gridMG[y][x] = tmp1;
			gridMG[LEN-1-y][x] = tmp;
		}
	}
}

void VFlipArrayMG()
{
	for (int y = 0; y < (int)LEN; y++) {
		for (int x = 0 ; x < (int)LEN/2; x++) {
			//0->23
			//1->22
			//23->0
			//22->1
			char tmp = gridMG[y][x];
			char tmp1 = gridMG[y][LEN-1-x];
			//printf("x -> LEN-1-x %d->%d\n", x, LEN-x);
			gridMG[y][x] = tmp1;
			gridMG[y][LEN-1-x] = tmp;

		}
	}
}
void rotateMG() {
	transpose();
	reverse();	
}

void swap(char *x, char *y) {
	int temp = *x;
	*x = *y;
	*y= temp;
}

void transpose() {
	for(int i = 0; i < LEN; i++){
		for(int j = i+1; j < LEN; j++)
			swap(&gridMG[i][j], &gridMG[j][i]);
	}
}

void reverse() {
	for(int i = 0; i < LEN; i++){
		for(int j = 0; j < LEN/2; j++){
			swap(&gridMG[i][j], &gridMG[i][LEN-j-1]);
		}
	}
}

void rotate(int gNum) {
	vector <vector<char>> mat = grid[gNum].gr;
	int n = mat[0].size();

	// Initialize the result matrix with zeros
	//vector<vector<char>> res(n, vector<char>(n));
	vector<vector<char>> res = mat;

	// Flip the matrix clockwise using nested loops
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[j][n - i - 1] = mat[i][j];
		}
	}

	grid[gNum].gr = res;
}

void checkG2(int i) {
	for (int j = 0; j < NUMG; j++) {
		if (i == j) {continue;}
		//printf("checking %d with %d\n", grid[i].num, grid[j].num);
		{//TOP of I with bottom of J
			int abber = 0;

			vector <vector <char>> one = gridG2[i].gr;
			vector <vector <char>> two = gridG2[j].gr;

			//if (grid[i].gr[0][x] == grid[j].gr[GX-2][x]) 
			for (int xx = 0; xx < GX; xx++) {
				if (one[0][xx] == two[GX-1][xx]) {
					//printf("same tibj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			if (abber == 0) {
				if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} 
				//if (find(sidesMap.begin(), sidesMap.end(), i) == sidesMap.end()) {sidesMap.push_back(i);} 
			}
		}
		{//BOTTOM of I with TOP of J
			int abber = 0;
			vector <vector <char>> one = gridG2[j].gr;
			vector <vector <char>> two = gridG2[i].gr;

			for (int xx = 0; xx < GX; xx++) {
				if (one[0][xx] == two[GX-1][xx]) { 
					//printf("same bitj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			if (abber == 0) {
				if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} 
				//if (find(sidesMap.begin(), sidesMap.end(), i) == sidesMap.end()) {sidesMap.push_back(i);} 
			}
		}
		{//LEFT of I with RIGHT of J
			int abber = 0;
			for (int y = 0; y < GX; y++) {
				vector <char> oneone = gridG2[i].gr[y];
				vector <char> twotwo = gridG2[j].gr[y];
				if (oneone[0] == twotwo[GX-1]) {
				} else {
					abber = 1;
					break;
				}
			}

			if (abber == 0) {
				if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} 
				//if (find(sidesMap.begin(), sidesMap.end(), i) == sidesMap.end()) {sidesMap.push_back(i);} 
			}
		}
		{//RIGHT of I with LEFT of J
			int abber = 0;
			for (int y = 0; y < GX; y++) {
				vector <char> oneone = gridG2[j].gr[y];
				vector <char> twotwo = gridG2[i].gr[y];
				if (oneone[0] == twotwo[GX-1]) {
					//printf("same rilj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}

			if (abber == 0) {
				if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} 
				//if (find(sidesMap.begin(), sidesMap.end(), i) == sidesMap.end()) {sidesMap.push_back(i);} 
			}

		}
	}
}

void check(int i) {
	for (int j = 0; j < NUMG; j++) {
		if (i == j) {continue;}
		//printf("checking %d with %d\n", grid[i].num, grid[j].num);
		{//TOP of I with bottom of J
			int abber = 0;

			vector <vector <char>> one = grid[i].gr;
			vector <vector <char>> two = grid[j].gr;

			//if (grid[i].gr[0][x] == grid[j].gr[GX-2][x]) 
			for (int xx = 0; xx < GX; xx++) {
				if (one[0][xx] == two[GX-1][xx]) {
					//printf("same tibj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			if (abber == 0) {if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} /*printf("top of %d == bottom of %d\n", grid[i].num, grid[j].num);*/}
		}
		{//BOTTOM of I with TOP of J
			int abber = 0;
			vector <vector <char>> one = grid[j].gr;
			vector <vector <char>> two = grid[i].gr;

			for (int xx = 0; xx < GX; xx++) {
				if (one[0][xx] == two[GX-1][xx]) { 
					//printf("same bitj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			if (abber == 0) {POS |= (1 << 1); if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} /*printf("bottom of %d == top of %d\n", grid[i].num, grid[j].num);*/}
		}
		{//LEFT of I with RIGHT of J
			int abber = 0;
			for (int y = 0; y < GX; y++) {
				vector <char> oneone = grid[i].gr[y];
				vector <char> twotwo = grid[j].gr[y];
				if (oneone[0] == twotwo[GX-1]) {
				} else {
					abber = 1;
					break;
				}
			}

			if (abber == 0) {POS |= (1 << 2); if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) { sidesMap.push_back(j); }/*printf("left of %d == right of %d\n", grid[i].num, grid[j].num);*/}
		}
		{//RIGHT of I with LEFT of J
			int abber = 0;
			for (int y = 0; y < GX; y++) {
				vector <char> oneone = grid[j].gr[y];
				vector <char> twotwo = grid[i].gr[y];
				if (oneone[0] == twotwo[GX-1]) {
					//printf("same rilj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}

			if (abber == 0) {POS |= (1 << 3); if (find(sidesMap.begin(), sidesMap.end(), j) == sidesMap.end()) {sidesMap.push_back(j);} /*printf("right of %d == left of %d\n", grid[i].num, grid[j].num);*/}
		}
	}
}




/*

   for (int kk = 0; kk < (int)sqrt(leny); kk++) {
   for (int yy = 0; yy < leny; yy++) {
   if (se.find(yy) == se.end()) {
   recoverOrig(yy);
   printf(" %d V %d %d V %d\n", second1, yy, grid[second1].num, grid[yy].num);
   if ((int)sar[yy].size() == 2 && checkGRID(second1, yy, "left", "right", 0) == 1) {
   printf("got left right next 2... %d %d %d %d\n", 
   second1, yy, grid[second1].num, grid[yy].num); getchar();
   printGrid(second1);
   printGrid(yy);
   se.insert(yy);
   }
   }
   }
   }
   }
   recoverOrig(second2);
   if (checkGRID(first, second2, "bottom", "top", 0) == 1) {
   printf("bottom top first, second2...\n");
   }
   recoverOrig(second2);
   if (checkGRID(first, second2, "top", "bottom", 0) == 1) {
   printf("top bottom first, second2...\n");
   }
   printGrid(first); printGrid(second2);
   */

//printf("first is %d second2 is %d top bottom\n", first, second1);
//printf("first is %d second2 is %d top bottom\n", grid[first].num, grid[second1].num);

//if (checkGRID(first, second2, "top", "bottom", 0) == 1) {printf("got it\n");}
//if (checkGRID(first, second2, "bottom", "top", 0) == 1) {printf("got it\n");}

//	printGrid(first);
//	printGrid(second1);
//printGrid(second2);

/*
   int gi = 0;
   for (int y = 0; y < sqrt(leny); y++) {
   for (int x = 0; x < sqrt(leny); x++) {
   gi++;
   }
   }
   */

//fflush(stdout); dup2(fd, 1);
//printf("**ans %llu\n", mul);
/*
   void rotate(int wh) {
   transpose(wh);
   reverse(wh);	
   }
   */

/*
   void swap(char *x, char *y) {
   int temp = *x;
 *x = *y;
 *y= temp;
 }

 void transpose(int wh) {
 for(int i=0; i<GX-1; i++){
 for(int j=i+1; j<GX-1; j++)
 swap(&grid[wh].gr[i][j], &grid[wh].gr[j][i]);
 }
 }

 void reverse(int wh) {
 for(int i=0; i<GX-1; i++){
 for(int j=0; j<(GX-1)/2; j++){
 swap(&grid[wh].gr[i][j], &grid[wh].gr[i][(GX-1)-j-1]);
 }
 }
 }
 */


/*
   void FlipColumn(char (*array)[GX], int column, int rows)
   {
   for (int row = 0; row < rows/2; row++)
   {
   swap2(array[row]+column, array[rows-1-row]+column);
   }
   }
   */


/*
   int swap2(char *a, char *b)
   {
   char temp = *a;
 *a = *b;
 *b = temp; 
 return 0;
 }
 */

/*
   void FlipRow(char *row, int columns)
   {
   for (int index = 0; index < columns / 2; index++)
   {
   swap2(row+index, row+columns-1-index);
   } 
   }
   */


/*
   for (int ii = 0; ii < NUMG-6; ii++) {
   int ppp = getPos("top", "bottom");
   int pp  = gg[ii];
   int pp3 = gg[ii+3];
   printf("ways[pp][1].size() is %d\n", (int)ways[pp][ppp].size());
   int found = 0;
   for (int kk = 0; kk < (int)ways[pp][ppp].size(); kk+=2) {
   if (ways[pp][ppp][kk+1].num == grid[pp3].num) {
   found++;
   grid[pp] = ways[pp][ppp][kk];
   grid[pp3] = ways[pp][ppp][kk+1];
   printGrid(pp);
   printGrid(pp3);
   getchar();
   }
   }
   printf("found is %d\n", found);

   }

   getchar();
   pos = 0;
   printf("\x1b[2J");
   for (int y = 0; y < sqrt(NUMG); y++) {
   for (int x = 0; x < sqrt(NUMG); x++) {
   printGridANSI(gg[pos], (x*11)+3, (y*13)+3);
   pos++;
   }
   }
   */
/*
   check(i); rotate(i); check(i); save(i); VFlipArray(i); check(i); rotate(i); check(i); rotate(i); check(i); recover(i); HFlipArray(i); check(i); rotate(i); check(i); rotate(i); check(i); rotate(i); check(i); recover(i); VFlipArray(i); HFlipArray(i); check(i); rotate(i); check(i); rotate(i); check(i); rotate(i); check(i); recover(i); check(i);

   check(i); rotate(i); check(i); save(i); VFlipArray(i); check(i); recover(i); HFlipArray(i); check(i); recover(i); VFlipArray(i); HFlipArray(i); check(i); recover(i); check(i);
   check(i); rotate(i); check(i); save(i); VFlipArray(i); check(i); recover(i); HFlipArray(i); check(i); recover(i); VFlipArray(i); HFlipArray(i); check(i); recover(i); check(i);
   check(i); rotate(i); check(i); save(i); VFlipArray(i); check(i); recover(i); HFlipArray(i); check(i); recover(i); VFlipArray(i); HFlipArray(i); check(i); recover(i); check(i);
   check(i); rotate(i); check(i); save(i); VFlipArray(i); check(i); recover(i); HFlipArray(i); check(i); recover(i); VFlipArray(i); HFlipArray(i); check(i); recover(i); check(i);

   recoverOrig(i);
   */
//printf("kkk V lll %d V %d\n", kkk, lll);
//printf("%d V %d\n", grid[kkk].num, grid[lll].num);
/*
   if (grid[kkk].num == 3079) {
   if (checkGRIDsides2(kkk, lll, "left", "right", 1, 1) == 1 && grid[lll].num == 2473) {
   printf("yes left right %d %d\n", grid[kkk].num, grid[lll].num);
   getchar();
   } else {
   printf("no... left right 3079 -> 2473\n");
   }
   }
   */
/*
   if (grid[kkk].num == 3079) {
   if (checkGRIDsides2(kkk, lll, "bottom", "top", 1, 1) == 1 && grid[lll].num == 2311) {
   printf("yes bottom top %d %d\n", grid[kkk].num, grid[lll].num);
   getchar();
   } else {
   printf("no... bottom top 3079 -> 2311\n");
   }
   }
   if (grid[kkk].num != 3079) {
   checkGRIDsides2(kkk, lll, "bottom", "top", 1, 1);
   }
   */
/*
   printf("now doing BOTTOMLEFT\n");
   corner(gg[6], BOTTOMLEFT);
   getchar();

   pos = 0;
   printf("\x1b[2J");
   for (int y = 0; y < sqrt(NUMG); y++) {
   for (int x = 0; x < sqrt(NUMG); x++) {
   if (gg[pos] != -1) {
   printGridANSI(gg[pos], (x*11)+3, (y*13)+3);
   } else {
   printf("0000");
   }
   pos++;
   }
   }
   */
