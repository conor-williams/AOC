#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

int lenx, leny;
#define DAY "2023 day17 part1\n"
#undef _DEBUG_
int tot;
struct posit {
	int x;	
	int y;
	int dir;
	long tot;
};
//struct posit savearray[100000];
vector<posit> savearray; 
vector<posit>::iterator iter;
//int savearrayLen;

char puzzle[200][200];
char puzzlecopy[200][200];
void printpuzzle();
void printpuzzlecopy();
void everyPath(int sX, int sY, int sD, long tot);
void saveit(int x1, int y1, int dir1, long tot);
int existsP(int x1, int y1, int dir1, long tot);

int main(int argc, char **argv)
{
	//savearrayLen = 0;
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
/*for (int i = 0; i < savearrayLen;i++) */
    for (iter = savearray.begin(); iter != savearray.end(); ++iter) {
	//printf("%d, %d, tot: %d\n", savearray[i].x, savearray[i].y, savearray[i].tot);	
	if (((*iter).x) == lenx -1 && ((*iter).y == leny - 1)) {
		printf("****tot path %ld\n", (*iter).tot);
	}
    }
}
void saveit(int x1, int y1, int dir1, long tot)
{
	int found = 0;
if (dir1 > 1) {
	dir1 -= 2;
}
	for (iter = savearray.begin(); iter != savearray.end(); ++iter) {
		if ((*iter).x == x1 && (*iter).y == y1 && (*iter).dir == dir1) {
			found = 1;
			if (tot < (*iter).tot) { 
				(*iter).tot = tot;
			}
			break;
		}
	}
	if (!found) {
struct posit tmpposit;
		//printf("adding.to save array..\n");
tmpposit.x = x1;
tmpposit.y = y1;
tmpposit.tot = tot;
tmpposit.dir = dir1;
		savearray.push_back(tmpposit);
/*
		savearray[savearrayLen].x = x1;
		savearray[savearrayLen].y = y1;
		savearray[savearrayLen].tot = tot;
		savearray[savearrayLen].dir = dir1;
		savearrayLen++;
*/
	}
	//printf("savearrayLen now  %d\n", savearrayLen); fflush(stdout);
	
}
int existsP(int x1, int y1, int dir1, long tot)
{
	int found = 0;
if (dir1 > 1) {
	dir1 -= 2;
}
	for (iter = savearray.begin(); iter != savearray.end(); ++iter) {
		if ((*iter).x == x1 && (*iter).y == y1 && (*iter).dir == dir1) {
			if (tot >= (*iter).tot) {
				//printf("already there.existsP..\n");
				found = 1;
			} else if (tot < (*iter).tot) {
				found = 2;
			}
			break;
		}
	}
	return found;
}
void everyPath(int sX, int sY, int sD, long tot)
{
	int discontinue = 0; //false
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

			if (stop == 1 || discontinue == 1) {

			} else {
			 	int myretval = existsP(startx, starty, dir, starttot);
				if (myretval == 2) {/*printf("GOTRETVAL2\n");*/ /*discontinue = 1*/saveit(startx, starty, dir, starttot); everyPath(startx, starty, dir, starttot);}
				else if (myretval == 0) {saveit(startx, starty, dir, starttot); everyPath(startx, starty, dir, starttot);}
				
#ifdef _DEBUG_
    printf("calling %d,%d Plus %d\n", startx, starty, (int)(puzzle[starty][startx] - '0')); getchar();
    char savedchar = puzzle[starty][startx]; puzzle[starty][startx] = 'Q'; printpuzzle(); getchar(); puzzle[starty][startx] = savedchar;
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
