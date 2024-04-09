#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define DAY "2023 Day14 Part1"

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
int main(int argc, char **argv)
{
	tot = 0;
        printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);

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
	line[linenum][strlen(line1)-1] = '\0';
	linenum++;

} //while 
fclose(a);

	printf("LINENUM: %d strlen(line[0]): %ld\n", linenum, strlen(line[0]));
#ifdef _DEBUG_
	printf("LINENUM: %d strlen(line[0]): %ld\n", linenum, strlen(line[0]));
#endif
{
	someDebug();
}
#define CYCLES 1000000000
for (int i = 0; i< CYCLES;i++)
{
	tilttowardNorth();
	tilttowardWest();
	tilttowardSouth();
	tilttowardEast();
}
{
	printpuzzle(linenum);
}
	for (int x = 0; x < strlen(line[0]); x++) {
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
}
void tilttowardWest()
{
	for (int y=0; y < linenum; y++) {
	for (int x = 1; x < strlen(line[0]); x++) {
			moveleft(y, x);
		}
	}
//	printpuzzle(linenum);
}
void tilttowardEast()
{
	for (int y=0; y < linenum; y++) {
	for (int x = strlen(line[0]); x > 0; x--) {
			moveright(y, x);
		}
	}
//	printpuzzle(linenum);
}
void tilttowardSouth()
{
	for (int x = 0; x < strlen(line[0]); x++) {
		for (int y=linenum-1; y >= 0; y--) {
			movedown(y, x);
		}
	}
//	printpuzzle(linenum);
}
void tilttowardNorth()
{
	for (int x = 0; x < strlen(line[0]); x++) {
		for (int y=1; y < linenum; y++) {
			moveup(y, x);
		}
	}
	//printpuzzle(linenum);
}
void someDebug() {
	int totDots = 0;
	int totO1 = 0;
	for (int x = 0; x < strlen(line[0]); x++) {
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
	while (myx < strlen(line[0])) {
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

