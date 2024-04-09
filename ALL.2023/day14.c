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
void moverightup(int y, int x);
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
//vertical lookup
	for (int x = 0; x < strlen(line[0]); x++) {
		for (int y=1; y < linenum; y++) {
			moverightup(y, x);
		}
	}
//tot
//printpuzzle(linenum);
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

void moverightup(int myy, int myx) {
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

