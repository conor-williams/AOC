#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2023 day18 part1 \n"
#undef _DEBUG_
long tot;

//compile: widen stack: -Wl,--stack,999777666
#define GRIDX 4000
#define GRIDY 4000
char puzzle[GRIDY][GRIDX];
void printpuzzle();
struct instruction {
	char inst;
	int nummoves;
};	
int startx; int starty;
void takemove(struct instruction instr);
void controllerfloodpuzzle(char what);
void floodpuzzle(int myx, int myy, char what);
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
	///printf("%d", argc); printf("%s", argv[1]);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
	printf("	make sure the stack is widened\n");

	fflush(stdout); int fd = dup(1); close(1);
	char line1[220];
	startx = 1800; starty = 1800;
	for (int x = 0; x < GRIDX; x++) {
		for (int y = 0; y < GRIDY; y++) {
			puzzle[y][x] = '.';
		}
	}
	while(1) 
	{
		fgets(line1, 200, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif

		//-------------------------
		lenx = GRIDX; leny = GRIDY;
#ifdef _DEBUG_
		printf("lenx: %d leny: %d\n", lenx, leny);
#endif
		struct instruction instr;
		sscanf(line1, "%c %d", &instr.inst, &instr.nummoves);

		takemove(instr);
	}
	/*
	   int smallestX = 1000;; int smallestY = 2000;
	   int maxX = 0; int maxY = 0;
	   for (int y = 0; y< leny; y++) {
	   for (int x = 0; x< lenx; x++) {
	   if(puzzle[y][x] == '#') {
	   if (y > maxY) {maxY = y;} if (y < smallestY) {smallestY = y;}
	   if (x > maxX) {maxX = x;} if (x < smallestX) {smallestX = x;}
	   }
	   }
	   }
	   printf("from: %d,%d to:%d,%d\n", smallestX, smallestY, maxX, maxY);
	   */
	//        printpuzzle();
	{
		controllerfloodpuzzle('o');
		//printpuzzle();

		for (int y = 0; y< leny; y++) {
			for (int x = 0; x< lenx; x++) {
				if(puzzle[y][x] == '#' || puzzle[y][x] == '.') {
					tot++;
				}
			}
		}
		//printpuzzle();
	} 
	printpuzzle();
	printf("********* tot %ld\n", tot);
	fclose(a);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", tot);
}

void floodpuzzle(int myx, int myy, char what) 
{
	if (puzzle[myy][myx] == '.') {
		puzzle[myy][myx] = what;
		if (myx+1 < lenx) {floodpuzzle(myx+1, myy, what);}
		if (myx-1 > 0) {floodpuzzle(myx-1, myy, what);} 
		if (myy+1 < leny) {floodpuzzle(myx, myy+1, what);}
		if (myy-1 > 0) {floodpuzzle(myx, myy-1, what);}
	}

}
void controllerfloodpuzzle(char what) 
{

	int y = 0; int x = 0;
	for (x = 0; x< lenx; x++) {
		floodpuzzle(x, y, what);	
	}

	y = leny -1;
	for (x = 0; x< lenx; x++) {
		floodpuzzle(x, y, what);	
	}
	x = 0;
	for (y = 0; y< leny; y++) {
		floodpuzzle(x, y, what);	
	}
	x = lenx -1;
	for (y = 0; y< leny; y++) {
		floodpuzzle(x, y, what);	
	}
	printf("\n");
}

void printpuzzle() 
{
	for (int y = 0; y< leny; y++) {
		for (int x = 0; x< lenx; x++) {
			printf("%c", puzzle[y][x]);
		}
		printf("\n");
	}
}
void takemove(struct instruction instr)
{
	switch (instr.inst) {
		case 'L':
			for (int i = 1; i <= instr.nummoves; i++) {
				if (startx - 1 > -1) {startx--;
					puzzle[starty][startx] = '#';
				} else {break;}
			} 
			break;
		case 'R':
			for (int i = 1; i <= instr.nummoves; i++) {
				if (startx + 1 < lenx) {startx++;
					puzzle[starty][startx] = '#';
				} else {break;}
			} 
			break;
		case 'U':
			for (int i = 1; i <= instr.nummoves; i++) {
				if (starty - 1 > -1) {starty--;
					puzzle[starty][startx] = '#';
				} else {break;}
			} 
			break;
		case 'D':
			for (int i = 1; i <= instr.nummoves; i++) {
				if (starty + 1 < leny) {starty++;
					puzzle[starty][startx] = '#';
				} else {break;}
			} 
			break;
		default:
			printf("ERROR: Unknown instruction - getchar"); getchar();
			break;
	}

}
