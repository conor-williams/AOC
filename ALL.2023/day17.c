#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2023 day17 part1\n"
#define _DEBUG_
int tot;
struct posit {
	int x;	
	int y;
	int dir;
	long tot;
};
struct posit savearray[100000];
int savearrayLen;

char puzzle[200][200];
char puzzlecopy[200][200];
void printpuzzle();
void printpuzzlecopy();
void everyPath(int sX, int sY, int sD, long tot);
void saveit(int x1, int y1, int dir1, long tot);
int existsP(int x1, int y1, int dir1, long tot);

int main(int argc, char **argv)
{
	savearrayLen = 0;
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[200];
while(1) {
        fgets(line1, 150, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	strcpy(puzzle[leny], line1);
        leny++;
}
fclose(a);
printf("lenx: %d leny: %d\n", lenx, leny);


everyPath(0, 0, 0, 0);
printpuzzle();
for (int i = 0; i < savearrayLen;i++) {
	//printf("%d, %d, tot: %d\n", savearray[i].x, savearray[i].y, savearray[i].tot);	
	if ((savearray[i].x) == lenx -1 && (savearray[i].y == leny - 1)) {
		printf("****tot path %ld\n", savearray[i].tot);
	}
}
}
void saveit(int x1, int y1, int dir1, long tot)
{
	int found = 0;
if (dir1 == 2 || dir1 == 3) {
	dir1 -= 2;
}
	for (int i = 0; i < savearrayLen; i++) {
		if (savearray[i].x == x1 && savearray[i].y == y1 && savearray[i].dir == dir1) {
			found = 1;
			if (tot < savearray[i].tot) { 
				savearray[i].tot = tot;
			}
			break;
		}
	}
	if (!found) {
		//printf("adding.to save array..\n");
		savearray[savearrayLen].x = x1;
		savearray[savearrayLen].tot = tot;
		savearray[savearrayLen].y = y1;
		savearray[savearrayLen].dir = dir1;
		savearrayLen++;
	}
	//printf("savearrayLen now  %d\n", savearrayLen); fflush(stdout);
	
}
int existsP(int x1, int y1, int dir1, long tot)
{
	int found = 0;
if (dir1 == 2 || dir1 == 3) {
	dir1 -= 2;
}
	for (int i = 0; i < savearrayLen; i++) {
		if (savearray[i].x == x1 && savearray[i].y == y1 && savearray[i].dir == dir1) {
			if (savearray[i].tot <= tot) {
				//printf("already there.existsP..\n");
				found = 1;
			} else if (savearray[i].tot > tot) {
			}
			break;
		}
	}
	return found;
}
void everyPath(int sX, int sY, int sD, long tot)
{
	//printf("in everyPath %d %d %d %ld\n", sX, sY, sD, tot);
	if (sX == lenx-1 && sY == leny -1) {
		//printf("We reached end point - getchar tot %ld\n", tot); fflush(stdout); //getchar();
		//printf("****tot %d\n", tot);
		return;
	}

	for (int i = 1; i <= 3; i++) {
		for (int z = -1; z <= 1; z++) {
		    if (z != 0) {
			int startx = sX; int starty = sY; long starttot = tot; int stop = 0; int dir = ((sD + z) + 4) % 4;
			switch (dir) {
				case 0:
					if (starty - i <= -1) {stop = 1;} else {starty -= i;
						for (int j = 0; j < i; j++) {
							starttot += (int)(puzzle[starty+j][startx] - '0');
						}
					}
					break;
				case 1:
					if (startx + i >= lenx) {stop = 1;} else {startx += i;
						for (int j = 0; j < i; j++) {
							starttot += puzzle[starty][startx - j] - '0';
						}

					}
					break;
				case 2:
					if (starty + i >= leny) {stop = 1;} else {starty += i;

						for (int j = 0; j < i; j++) {
							starttot += puzzle[starty -j][startx] - '0';
						}

					}
					break;
				case 3:
					if (startx - i <= -1) {stop = 1;} else {startx -= i;
						for (int j = 0; j < i; j++) {
							starttot += puzzle[starty][startx + j] - '0';
						}

					}
					break;
				default:
					printf("ERROR unknown dir getchar()\n"); getchar();
					break;
			}

			if (stop == 1) {

			} else {
			 	if (!existsP(startx, starty, dir, starttot)) {saveit(startx, starty, dir, starttot); everyPath(startx, starty, dir, starttot);}
#ifdef _DEBUG_
				//printf("calling %d,%d Plus %d\n", startx, starty, (int)(puzzle[starty][startx] - '0')); getchar();
				//char savedchar = puzzle[starty][startx]; puzzle[starty][startx] = 'Q'; printpuzzle(); getchar(); puzzle[starty][startx] = savedchar;
#endif
				
			}
		}
	    }
	}

}
void printpuzzle()
{
    for (int y = 0; y < leny; y++) {
	printf("%s\n", puzzle[y]);
    }
}
