#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <map>
#include <unordered_map>

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
	int touched;
	int lower;
};
unordered_map<string, posit> savearray;
unordered_map<string, posit>::iterator iter;

char puzzle[200][200];
char puzzlecopy[200][200];
void printpuzzle();
void printpuzzlecopy();
void everyPath(int sX, int sY, int sD, long tot);
int saveit(int x1, int y1, int dir1, long tot);
void endCheck();

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
        char line1[200];
//---------------------------------
while(1) {
        fgets(line1, 160, a);
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
//---------------------------------


	cout << "everyPath all the zeroes" << endl; everyPath(0, 0, 0, 0); printpuzzle(); endCheck();
	cout << "everyPath going south with the rest, all zeroes" << endl; everyPath(0, 0, 1, 0); printpuzzle(); endCheck();

}


//-------------------------------
void endCheck() {
	int found = 0;
	struct posit tmpstruct;
	for (auto itr = savearray.begin(); itr != savearray.end(); ++itr) {
		tmpstruct = itr->second;
		if (tmpstruct.x == lenx -1 && tmpstruct.y == leny -1) {
			printf("%d, %d, tot: %d\n", tmpstruct.x, tmpstruct.y, tmpstruct.tot);	
		}
	}
        if (found == 0) { cout << "end NOT FOUND...." << endl;}
}

int saveit(int x1, int y1, int dir1, long tot)
{
	int found = 0;
if (dir1 > 1) {
	dir1 -= 2;
}
	//sprintf(mapKey, "%02d%02d%02d", x1, y1, dir1);
	string tmpstring = to_string(x1) + to_string(y1) + to_string(dir1);
#ifdef _DEBUG_
	cout << tmpstring << endl;
#endif

	struct posit tmpstruct;
	if (savearray.find(tmpstring) != savearray.end()) {
		tmpstruct = savearray[tmpstring];
		if (tmpstruct.x == x1 && tmpstruct.y == y1 && tmpstruct.dir == dir1) {
				found = 1;
				if (tot < tmpstruct.tot) { 
					found = 2;
					tmpstruct.tot = tot;
					tmpstruct.touched++;
				}
		}
	} else if (!found) {
		struct posit tmpposit;
		tmpposit.x = x1;
		tmpposit.y = y1;
		tmpposit.tot = tot;
		tmpposit.dir = dir1;
		tmpposit.touched = 0;
		savearray.insert({tmpstring, tmpposit});
		found = 0;
	}
	return found;
	
}

void everyPath(int sX, int sY, int sD, long tot)
{
#ifdef _DEBUG_
	printf("in everyPath %d %d %d %ld\n", sX, sY, sD, tot);
#endif
	if (sX == lenx-1 && sY == leny -1) {
#ifdef _DEBUG_
		printf("We reached end point - getchar tot %ld\n", tot); fflush(stdout);// getchar();
#endif
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

				if (myretval == 2) {everyPath(startx, starty, dir, starttot);}
				else if (myretval == 0) {everyPath(startx, starty, dir, starttot);}
				/* myretval == 1 -- already there and higher */
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
	printf("_-----------___----------------------------__\n");
    for (int y = 0; y < leny; y++) {
	printf("%s\n", puzzle[y]);
    }
}
