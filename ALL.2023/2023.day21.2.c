#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
int leny;
int lenx;
#define DAY "2023 Day21 Part2"

char puzzle[132][132];
int puzzlealready[132][132];
#undef _DEBUG_ 
int gcountO;
FILE *a;
#define MAX_STEPS 10 + 1
void findstart(int *startx, int *starty);
void printpuzzle();
int countOinpuzzle();
void nextandcheck(int startx, int starty, int steps);
int numspawn;

int main(int argc, char **argv)
{

	a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);

	printf("broken...\n"); exit(0);
	fflush(stdout); int fd = dup(1); //close(1);
	char line1[1000];

	leny = 0; lenx = 0;  numspawn = 0;
	{
		for (int x = 0; x < 132; x++) {
			for (int y = 0; y < 132; y++) {
				puzzlealready[y][x] = 0;
			}
		}
	}

	while(1) {
		fgets(line1, 999, a);
		if (feof(a)) break;
#ifdef _DEBUG_
		printf("LINE: %s", line1); fflush(stdout);
#endif
		fflush(stdout);
		line1[strlen(line1) -1] = '\0';
		strcpy(puzzle[leny], line1);
#ifdef _DEBUG_ 
		printf("----------------\n");
#endif
		leny++;       

	} lenx = strlen(line1);
	int startx = 0; int starty = 0; gcountO = 0;

	
	fflush(stdout); dup2(fd, 1);
	{
		findstart(&startx, &starty);
		printpuzzle();
		puzzle[starty][startx] = '.';
		nextandcheck(startx, starty, 0);
		printf("*****gcountO %d\n", gcountO);
		printf("**ans: %d\n", gcountO);

	}
	//printpuzzle(puzzle);
	fclose(a);
}
void nextandcheck(int startx, int starty, int steps)
{
	numspawn++; //printf("numspawn %d\n", numspawn);
	steps++;
	if (steps == MAX_STEPS) {	
		if (puzzle[starty][startx] != '#') {
			if (puzzlealready[starty][startx] != 1) {
				gcountO++; puzzlealready[starty][startx] = 1;
				return;
			}
		}
		return;
	}
	if (puzzle[starty][startx] == '#') {return;}

	//puz[starty][startx] = '.';

	if (startx == 0) {startx=lenx;}
	if (startx == lenx -1) {startx=-1;}
	if (starty == 0) {starty=leny;}
	if (starty == leny -1) {starty=-1;}
	if (startx -1 > 0   ) {nextandcheck(startx -1, starty, steps); } else { gcountO++; puzzlealready[starty][startx] = 1;}
	if (startx +1 < lenx) {nextandcheck(startx +1, starty, steps); } else { gcountO++; puzzlealready[starty][startx] = 1;}
	if (starty -1 > -1  ) {nextandcheck(startx, starty -1, steps); } else { gcountO++; puzzlealready[starty][startx] = 1;}
	if (starty +1 < leny) {nextandcheck(startx, starty +1, steps); } else { gcountO++; puzzlealready[starty][startx] = 1;}
}


void findstart(int *startx, int *starty)
{
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (puzzle[y][x] == 'S') {
				*startx = x;
				*starty = y;
				return;
			}
		}
	}
}

void printpuzzle()
{
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (puzzlealready[y][x] == 1) {
				printf("%c", 'x');
			} else {
				printf("%c", puzzle[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
