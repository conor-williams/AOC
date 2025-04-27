#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define DAY "		2023 Day14 Part2"

char line1[1000];
char line[1000][1000];
long tot; int linenum;

#undef _DEBUG_ 
void printpuzzle(int lines);
void moveup(int y, int x);
void tilttowardNorth();
void movedown(int y, int x);
void tilttowardSouth();
void moveright(int y, int x);
void tilttowardEast();
void moveleft(int y, int x);
void tilttowardWest();
void someDebug();
#define CYCLES 5000
int nums[CYCLES];
int main(int argc, char **argv)
{
	tot = 0;
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);
	int fd = dup(1); close(1);

	linenum = 0;
	while(1) {
#ifdef _DEBUG_
		printf("---------NEXT LINE----------\n");
#endif
		fgets(line1, 999, a);
		if (feof(a)) {break;}
#ifdef _DEBUG_
		printf("LINE: %s", line1); fflush(stdout);
#endif

		strcpy(line[linenum], line1);
		line[linenum][(int)strlen(line1)-1] = '\0';
		linenum++;

	} //while 
	fclose(a);

	printf("LINENUM: %d (int)strlen(line[0]): %d\n", linenum, (int)strlen(line[0]));
#ifdef _DEBUG_
	printf("LINENUM: %d (int)strlen(line[0]): %d\n", linenum, (int)strlen(line[0]));
#endif
	{
		someDebug();
	}
	//do once first 

	printf("-----------------\n");

	int cycleAt;
	int ss;
	for (int i = 0; i< CYCLES; i++)
	{
		tilttowardNorth();
		tilttowardWest();
		tilttowardSouth();
		tilttowardEast();

		int newtot = 0;
		for (int x = 0; x < (int)strlen(line[0]); x++) {
			for (int y=0; y < linenum; y++) {
				if (line[y][x] == 'O') {
					newtot += linenum -y;
				}
			}
		}
		//printf("%d\n", newtot);
		nums[i] = newtot;
		if (i > 1000) {
			if (nums[i] == nums[1000]) {
				cycleAt = i-1000;
				printf("cycle of %d\n", i-1000);
				break;
			}
		}
	}
	int ii;
	for (ii = 0; ii < 1000+cycleAt-1; ii++) {
		int found = 0;
		for (int jj = 0; jj < 1000+cycleAt; jj++) {
			if (ii == jj) {continue;}
			if (nums[ii] == nums[jj] && nums[ii] == nums[ii+cycleAt]) {
				printf("found start %d\n", nums[ii]);
				found = 1;
			}
		}
		if (found == 1) {ss = ii; break;}
	}

	printf("ss is %d\n", ss);

	//cycles 42 start 52 pos 24 + 52
	int pos = (int) ((unsigned long long)(1000000000-ss-1) % cycleAt);
	printf("pos is %d\n", pos);
	printf("nums[ss+pos-1] %d\n", nums[ss+(pos-1)]);
	printf("nums[ss+pos] %d\n", nums[ss+pos]);
	printf("nums[ss+pos+1] %d\n", nums[ss+(pos+1)]);
	fflush(stdout); dup2(fd, 1); 
	printf("**ans: %d\n", nums[ss+pos]);
	/*
	printf("-----------------\n");
	{
		//printpuzzle(linenum);
	}
	for (int x = 0; x < (int)strlen(line[0]); x++) {
		for (int y=0; y < linenum; y++) {
			if (line[y][x] == 'O') {
				tot += linenum - y;
			}
		}
	}
	printf("tot***  %ld\n", tot);
	{
		someDebug();
	}
	*/
}
void tilttowardWest()
{
	for (int y=0; y < linenum; y++) {
		for (int x = 1; x < (int)strlen(line[0]); x++) {
			moveleft(y, x);
		}
	}
	//	printpuzzle(linenum);
}
void tilttowardEast()
{
	for (int y=0; y < linenum; y++) {
		for (int x = (int)strlen(line[0]); x > 0; x--) {
			moveright(y, x);
		}
	}
	//	printpuzzle(linenum);
}
void tilttowardSouth()
{
	for (int x = 0; x < (int)strlen(line[0]); x++) {
		for (int y=linenum-1; y >= 0; y--) {
			movedown(y, x);
		}
	}
	//	printpuzzle(linenum);
}
void tilttowardNorth()
{
	for (int x = 0; x < (int)strlen(line[0]); x++) {
		for (int y=1; y < linenum; y++) {
			moveup(y, x);
		}
	}
	//printpuzzle(linenum);
}
void someDebug() {
	int totDots = 0;
	int totO1 = 0;
	for (int x = 0; x < (int)strlen(line[0]); x++) {
		for (int y=0; y < linenum; y++) {
			if (line[y][x] == '.') {totDots++;}
			else if (line[y][x] == 'O') {totO1++;}
		}
	}
	printf("totO1: %d\n", totO1);
	printf("totDots: %d\n", totDots);
}

void moveleft(int myy, int myx) {
	while (myx > 0) {
		if ( line[myy][myx] == 'O' && line[myy][myx-1] == '.') {
			line[myy][myx] = '.'; line[myy][myx-1] = 'O';	
			myx--;
		} else {
			break;
		}
	}
}
void moveright(int myy, int myx) {
	while (myx < (int)strlen(line[0])) {
		if ( line[myy][myx-1] == 'O' && line[myy][myx] == '.') {
			line[myy][myx-1] = '.'; line[myy][myx] = 'O';	
			myx++;
		} else {
			break;
		}
	}
}
void movedown(int myy, int myx) {
	if (myy + 1 > linenum) {printf("ERR"); getchar();}

	while (myy < linenum-1) {
		if ( line[myy][myx] == 'O' && line[myy+1][myx] == '.') {
			line[myy][myx] = '.'; line[myy+1][myx] = 'O';	
			myy++;
		} else {
			break;
		}
	}
}
void moveup(int myy, int myx) {
	if (myy - 1 < 0) {printf("ERR"); getchar();}
	while (myy > 0) {
		if ( line[myy][myx] == 'O' && line[myy-1][myx] == '.') {
			line[myy][myx] = '.'; line[myy-1][myx] = 'O';	
			myy--;
		} else {
			break;
		}
	}
}
void printpuzzle(int lines)
{
	for (int i = 0; i < lines; i++) {
		printf("%s\n", line[i]);
	}
}

