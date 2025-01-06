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
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SeX 220
char grid[SeX][SeX];

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
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 22 part1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];

	if (argc == 3) {hide = 1;}
	if (hide == 1) {
		fd = dup(1); close(1);
	}

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

	for (int y = 0; y < leny; y++) {
		int first = 1;
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '\0') {break;} 
			if (first == 1 && (grid[y][x] == '.' || grid[y][x] == '#')) {first = 0; RowStae[y].st = x;}
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

	int stx = RowStae[0].st; int sty = 0;
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
		dup2(fd, 1);
	}
	printit(crx, cry, dir);
	int posDir = dir;
	posDir--;
	posDir += 4;
	posDir %= 4;
	printf("crx is %d\n", crx);
	printf("cry is %d\n", cry);

	fflush(stdout); dup2(fd, 1);
	printf("ans: %d\n", (1000 * (cry+1)) + (4 * (crx+1)) + posDir);

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
	printf("\n");
	getchar();
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
