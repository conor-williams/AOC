#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;
char grid[52][52];
char gridNew[52][52];
char gridOrig[52][52];
#define MEMSZ 5000000
char mem[3][52][52];
void printit();
void check(int x, int y, char tre);
int cou(int x, int y, char tre);
int leny = 0;
int lenx = 0;
void giveAns();
int fd;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day18.2\n"); fflush(stdout);
	
	fflush(stdout); fd = dup(1); close(1);

	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';

		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);
	for (int y = 0; y< leny; y++) {
		strcpy(gridOrig[y], grid[y]);
	}
	printf("%llu\n", (unsigned long long)1000000000/(unsigned long long)1000); getchar();
	//printit(); getchar();
	int iter = 1;
	for (unsigned long long kk = 0; kk < (unsigned long long) 1000000000; kk++) {
		if (kk % 10000 == 0) {printf("kk: %llu\n", kk);}
		for (int y = 0; y < leny; y++) {
			strcpy(gridNew[y], grid[y]);
		}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				check(x, y, grid[y][x]);
			}
		}
		for (int y = 0; y < leny; y++) {
			strcpy(grid[y], gridNew[y]);
		}
		//printit(); getchar();

		if (iter == 2 && kk>0) {
			printf("here1\n");
			int found = 0;
			for (int y = 0; y < leny; y++) {
				if (strcmp(mem[0][y], grid[y]) == 0) {
					found++;
				}
			}
			if (found == leny) {
				printf("mem[1012] matches %llu\n", kk); //getchar();
				if (kk == 999999999) {printf("------\n"); giveAns();}
			}
/*
			if (kk < 999999993 - 999999) {
				kk+= (9999 * 28) - 1;
			} else if (kk < 999997993) {
				kk+= (28 * 100) - 1;
			}
*/
			giveAns(); //getchar();
		} else if (kk == 999 && iter == 1) {
			for (int y = 0; y < leny; y++) {
				strcpy(mem[0][y], gridNew[y]);
			}
			if (iter == 1) {iter = 2;}
			giveAns(); getchar(); kk+= (35714230 * 28);
			//for (int y = 0; y< leny; y++) {
			//	strcpy(grid[y], gridOrig[y]);
			//}
		}
			
	}

}
	
void giveAns() {		
	tot = 0;
	int countL = 0;
	int countT = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '#') {
				countL++;
			} else if (grid[y][x] == '|') {
				countT++;
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ansP %d\n", countT*countL);
	exit(0);
}
void printit() {
	for (int y = 0; y < leny; y++) {
		printf("%s\n", grid[y]);
	}
	printf("\n");
}
void check(int x, int y, char tre) {
	int count = 0;
	int count2 = 0;
	switch (tre) {
		case '.':
			count = cou(x, y, '|');
			if (count >=3) {gridNew[y][x] = '|';}
			break;
		case '|':
			count = cou(x, y, '#');
			if (count >=3) {gridNew[y][x] = '#';}
			break;
		case '#':
			count = cou(x, y, '#');
			count2 = cou(x, y, '|');
			if (count >= 1 && count2 >= 1) {} else {gridNew[y][x] = '.';}
			break;
	}	
}

int cou(int x, int y, char tre) {
	int count = 0;
	if (y-1 >= 0) {if (grid[y-1][x] == tre) {count++;}}
	if (y-1 >= 0 && x+1 < lenx) {if (grid[y-1][x+1] == tre) {count++;}}
	if (x+1 < lenx) {if (grid[y][x+1] == tre) {count++;}}
	if (y+1 < leny && x+1 < lenx) {if (grid[y+1][x+1] == tre) {count++;}}
	if (y+1 < leny) {if (grid[y+1][x] == tre) {count++;}}
	if (y+1 < leny && x-1 >= 0) {if (grid[y+1][x-1] == tre) {count++;}}
	if (x-1 >=0) {if (grid[y][x-1] == tre) {count++;}}
	if (y-1 >= 0 && x-1 >=0) {if (grid[y-1][x-1] == tre) {count++;}}
	
	return count;
}
