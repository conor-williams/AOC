#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
long tot = 0;
#define MAX_X  145
#define MAX_Y  MAX_X

int newpuzzleP(int curpuzzle, int dir, int *newx, int *y, int fromx, int fromy);
void copypuzzle(int frompuz, int x, int y, int dir);
int amalgamate(int start);
void printpuzzle(int puzzlenum) ;
void printpuzzlemain() ;
int NUM_PUZ;
#undef _DEBUG_

char puzzle[MAX_X][MAX_X];
int beentherepuz[MAX_X][MAX_X];
int dotpuz =0;

struct point {
	int x;
	int y;
};
struct point puzBefore2[MAX_X][MAX_Y]; 
	
struct pD {
	char puz[MAX_X][MAX_X];
	int distance;
};
#define MAX_PUZ 50000
struct pD pz[MAX_PUZ];
void findstart(int *startx, int *starty);

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

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day23part1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

	leny=0, lenx =0;

	NUM_PUZ = 1;
	for (int j = 0; j < MAX_X;j++) {
		for (int k = 0; k< MAX_X; k++) {
		   beentherepuz[j][k] = 0;
		}
	}
	for (int j = 0; j < MAX_X;j++) {
		for (int k = 0; k< MAX_X; k++) {
			   puzBefore2[j][k].x = 0;
			   puzBefore2[j][k].y = 0;
		}
	}
	
while (1)
{
	fgets(line1, 500, a);
	if (feof(a)) {printf("got eof\n"); break;}
#ifdef _DEBUG_
	printf("got %s\n", line1); fflush(stdout);
#endif
        line1[(int)strlen(line1) -1] = '\0';
	lenx = strlen(line1);
	for (int i = 0; i<lenx; i++) {}
	strcpy(puzzle[leny], line1);
        leny++;
}
fclose(a);
printf("*NB lenx: %d leny %d \n", lenx, leny); fflush(stdout);

int sX; int sY;
findstart(&sX, &sY);
puzzle[sY][sX] = '.';
printf("before seeding [%d] puzzles..", MAX_PUZ); fflush(stdout);
 for (int i = 0; i < MAX_PUZ; i++) {
	for (int y=0; y< leny; y++) {
		strcpy(pz[i].puz[y], puzzle[y]);
	}
}
printf("after seeding [%d] puzzles..\n", MAX_PUZ); fflush(stdout);

puzBefore2[0][1].x = 0; /*could be a problem */
puzBefore2[0][1].y = 0;

puzBefore2[1][1].x = 1;
puzBefore2[1][1].y = 0;

/*
puzBefore[1][2][3] = 0;
puzBefore[1][3][3] = 0;
*/


beentherepuz[0][1] = 0;
beentherepuz[1][1] = 1;
//pz[0].puz[1][1] = 'Q';
//pz[0].puz[1][1] = 'Q';
pz[0].distance = 1;
pz[0].puz[sY][sX] = 'Q';
int numfound = 0;
int STEPS=-1;
int MAX_STEPS=6;
 while (1) {
	int found3 = 0;
   for (int c = 0; c < NUM_PUZ; c++) {
	found3 = 0;
	for (int x=0; x<lenx; x++) {
		for (int y=0; y<leny; y++) {
			if (pz[c].puz[y][x] == 'Q') {
				found3 = 1;
			}
		}
	}
	if (c == NUM_PUZ && found3 == 0) {printf("shows over...\n"); exit(0);}
   }
        
	//printf("going in again %d\n", NUM_PUZ); 
	if (NUM_PUZ == 0) {printf("thats it.NUM_PUZ IS zero.."); break;}
if (NUM_PUZ == 1) {
	int foundQq = 0;
	for (int x = 0; x < MAX_X; x++) {
		for (int y = 0; y < MAX_X; y++) {
			if (pz[0].puz[y][x] == 'Q') { foundQq = 1; }
		} }
	if (foundQq == 0) {printf("thats surely it now...\n"); exit(0);}
}

	for (int k = 0; k < NUM_PUZ-1 ; k++) {
		amalgamate(k);
	}
   int puzes = NUM_PUZ;
   for (int c1 = 0; c1 < puzes; c1++) {
	if (c1 == 0) {STEPS++;}
	if (STEPS==MAX_STEPS) {printf("NUM_PUZ (PLOTS) %d\n", NUM_PUZ); getchar();}
	printpuzzle(c1);
	printf("c1 %d puzes %d STEPS %d NUM_PUZ (PLOTS) %d\n", c1, puzes, STEPS, NUM_PUZ); getchar();
	
	for (int y = 0; y < leny; y++) {
		int b = 0;
		for (int x = 0; x < lenx; x++) {
			b = 0;
			if (pz[c1].puz[y][x] == 'Q') {
				dotpuz = 0;
				pz[c1].puz[y][x] = puzzle[y][x];
printf("ccc not Q %c \n", pz[c1].puz[y][x]);
				int ret = 0; int myx; int myy; int found =0;
				int newx = x; int newy = y+1;
				ret = newpuzzleP(c1, 2, &newx,   &newy, x, y);
				if (ret == 1) {myx = newx; myy = newy; ret=0; found = 1;}
				newx = x; newy = y-1;
				ret = newpuzzleP(c1, 0, &newx,   &newy, x, y);
				if (ret == 1) {myx = newx; myy = newy; ret=0; found = 1;}
				newx = x+1; newy = y;
				ret = newpuzzleP(c1, 1, &newx, &newy, x, y);
				if (ret == 1) {myx = newx; myy = newy; ret=0; found = 1;}
				newx = x-1; newy = y;
				ret = newpuzzleP(c1, 3, &newx, &newy, x, y);
				if (ret == 1) {myx = newx; myy = newy; ret=0; found = 1;}
				
				if (found ==1 ) { printf("c1 %d sX sY, %d %d myx myy %d %d x y %d %d\n", c1, sX, sY, myx, myy, x, y); pz[c1].puz[myy][myx] = 'Q';}
				printf("NUM_PUZ now %d\n", NUM_PUZ); getchar();
				b=1;
				break;
			} 
		}
		if (b==1) {break;}
	}
    }
	
  }


	printf("leny is %d\n", leny);
	printf("lenx is %d\n", lenx);
fclose(a);
}
void printpuzzlemain() 
{
	for (int y = 0; y < leny; y++)
	{
		for (int x = 0; x < lenx; x++)
		{
			printf("%c", puzzle[y][x]);
		}
		printf("\n");
	}
}

void printpuzzle(int puzzlenum) 
{
	for (int y = 0; y < leny; y++)
	{
		for (int x = 0; x < lenx; x++)
		{
			printf("%c", pz[puzzlenum].puz[y][x]);
		}
		printf("\n");
	}
}

int amalgamate(int first)
{
        int q_one_blank = 0;
	int found5 = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (pz[first].puz[y][x] == 'Q') {found5 = 1; break;}
		}
		if (found5 == 1) {break;}
	}
	if (found5 == 0) {q_one_blank = 1;}

        if (q_one_blank) { 
		for (int d = first; d < NUM_PUZ; d++) {
			for (int y = 0; y< leny; y++)  {
				pz[d] = pz[d+1];
			}
		}
		NUM_PUZ--;
		return 22;
	} else {
		return 0;
        }
}
void copypuzzle(int frompuz, int x, int y, int dir)
{
	pz[NUM_PUZ].puz[y][x] = 'Q';
	pz[NUM_PUZ].distance = pz[frompuz].distance /*+ pz[NUM_PUZ].distance*/ + 1;
	NUM_PUZ++;
#ifdef _DEBUG_
	if (NUM_PUZ + 50 > MAX_PUZ) {
		printf("WARNING in copypuzzle: [%d] MAX_PUZ:[%d]\n", NUM_PUZ, MAX_PUZ); fflush(stdout);
	}
#endif
	if (NUM_PUZ > 5500 && (NUM_PUZ % 6000 == 0)) {
		for (int k = 1; k < NUM_PUZ-1; k++) {
			amalgamate(k);
		}
	}
	if (NUM_PUZ + 50 > MAX_PUZ) {
		printf("WARNING in copypuzzle: [%d] MAX_PUZ:[%d]\n", NUM_PUZ, MAX_PUZ); fflush(stdout);
	}
#ifdef _DEBUG_
	printf("WARNING after amalgamage: in copypuzzle: [%d] MAX_PUZ:[%d]\n", NUM_PUZ, MAX_PUZ); fflush(stdout);
#endif

}

int newpuzzleP(int curpuzzle, int dir, int *x1, int *y1, int fromx, int fromy) 
{
	if (*x1 < 0) {*x1 = lenx-1;}
	if (*y1 < 0) {*y1 = leny-1;}
	if (*x1 == lenx) {*x1 = 0;}
	if (*y1 == leny) {*y1 = 0;}

int x = *x1; int y = *y1;
			if (      pz[curpuzzle].puz[y][x] == '#') {
				/* game over */
			} else if (pz[curpuzzle].puz[y][x] == '.') {
				dotpuz++;
				if (dotpuz == 1) {
					return 1;
				} else {
					printf("calling copy...\n");
					copypuzzle(curpuzzle, x,y, dir);
				}
			} 
	return 0;
}







void newpuzzlePOLD(int curpuzzle, int dir, int x, int y, int fromx, int fromy) 
{
/*
int goingdir1;
int goingdir2;
int goingdir3;
int goingdir4;
*/

	if (x < 0) {return;}
	if (y < 0) {return;}
	if (x == lenx) {return;}
	if (y == leny) {return;}

/*
	int diffx = fromx - x;
	int diffy = fromy - y;
*/

/*
	if ((puzBefore[fromy][fromx][0] == 1) && (puzBefore[fromy][fromx][1] == 1) &&
		(puzBefore[fromy][fromx][2] == 1) && (puzBefore[fromy][fromx][0] == 1)) {
		//new entry
		if (diffx > 0) {puzBefore[fromy][fromx][3] = 1;}
		if (diffx < 0) {puzBefore[fromy][fromx][1] = 0;}
		if (diffy > 0) {puzBefore[fromy][fromx][2] = 1;}
		if (diffy < 0) {puzBefore[fromy][fromx][0] = 1;}
	}
	if (diffx > 0) {goingdir1 = 3;}
	if (diffx < 0) {goingdir2 = 1;}
	if (diffy > 0) {goingdir3 = 2;}
	if (diffy < 0) {goingdir4 = 0;}
*/

/*
	if ((puzBefore[fromy][fromx][goingdir1] == 1 && dir == goingdir1) ||
		(puzBefore[fromy][fromx][goingdir2] == 1 && dir == goingdir2) ||
		(puzBefore[fromy][fromx][goingdir3] == 1 && dir == goingdir3) ||
		(puzBefore[fromy][fromx][goingdir4] == 1 && dir == goingdir4)) 
		if (pz[curpuzzle].distance < beentherepuz[y][x] || beentherepuz[y][x] == 0)   
*/

	if (puzBefore2[fromy][fromx].x != fromx && puzBefore2[fromy][fromx].y != fromy) {
			puzBefore2[y][x].x = fromx;
			puzBefore2[y][x].y = fromy;
		if (pz[curpuzzle].distance < beentherepuz[y][x] || beentherepuz[y][x] == 0)   {
			beentherepuz[y][x] = pz[curpuzzle].distance;
//puzBefore2[y][x][(dir+2)%4] = 0;

			if (      pz[curpuzzle].puz[y][x] == '#') {
				/* game over */
			} else if (pz[curpuzzle].puz[y][x] == '.') {
				copypuzzle(curpuzzle, x,y, dir);
			} else if (pz[curpuzzle].puz[y][x] == '^' && dir == 0) {
				copypuzzle(curpuzzle, x, y, dir);
			} else if (pz[curpuzzle].puz[y][x] == '>' && dir == 1) {
				copypuzzle(curpuzzle, x, y, dir);
			} else if (pz[curpuzzle].puz[y][x] == 'v' && dir == 2) {
				copypuzzle(curpuzzle, x, y, dir);
			} else if (pz[curpuzzle].puz[y][x] == '<' && dir == 3) {
				copypuzzle(curpuzzle, x, y, dir);
			} 
		}
	}
}






