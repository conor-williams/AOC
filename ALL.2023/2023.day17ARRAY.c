#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2023 day17 part1\n"
#define _DEBUG_
int tot;
long savearray[200][200][2];

char puzzle[200][200];
char puzzlecopy[200][200];
void printpuzzle();
void printpuzzlecopy();
void everyPath(int sX, int sY, int sD, long tot);
int saveit(int x1, int y1, int dir1, long tot);
int existsP(int x1, int y1, int dir1, long tot);

int main(int argc, char **argv)
{
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

for (int y = 0; y< leny+10; y++) {
	for (int x = 0; x < lenx+10; x++) {
		savearray[y][x][0] = -1; 
		savearray[y][x][1] = -1; 
	}
}

printf("all the zeroes\n");
everyPath(0, 0, 0, 0);
printpuzzle();
printf("all the zeroes but one\n");
everyPath(0, 0, 1, 0);
printpuzzle();
	printf("****tot path %ld\n", savearray[leny-1][lenx-1][0]);
	printf("****tot path %ld\n", savearray[leny-1][lenx-1][1]);
}

int saveit(int x1, int y1, int dir1, long tot)
{
	int found = 0;
	if (dir1 == 2 || dir1 == 3) {
		dir1 -= 2;
	}
	 if (savearray[y1][x1][dir1] != -1) {
		found = 1;
		if (tot < savearray[y1][x1][dir1]) { 
			found = 2;
			savearray[y1][x1][dir1] = tot;
		}
	}
	if (!found) {
		savearray[y1][x1][dir1] = tot;
	}
}

void everyPath(int sX, int sY, int sD, long tot)
{
	if (sX == lenx-1 && sY == leny -1) {
		//printf("We reached end point - getchar tot %ld\n", tot); fflush(stdout); //getchar();
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
                                int myretval = saveit(startx, starty, dir, starttot);

	 			if (myretval == 2) {
					everyPath(startx, starty, dir, starttot);
				} else if (myretval == 0) {everyPath(startx, starty, dir, starttot);}



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
