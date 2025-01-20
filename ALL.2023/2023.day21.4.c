#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
long tot = 0;
#define MAX_X  145
#define MAX_Y  MAX_X
struct upleft {
	int cR;
	int cD;
};
	struct p {
		int val;
		int count;
	};
	
void BubbleSort(int a[], int array_size);
int newpuzzleP(int curpuzzle, int *newx, int *y, struct upleft *blah);
void copypuzzle(int frompuz, int x, int y, int cR, int cD);
int amalgamate(int start);
void printpuzzle(int puzzlenum) ;
void printpuzzlemain() ;
int NUM_PUZ;
#undef _DEBUG_

char puzzle[MAX_X][MAX_X];
int dotpuz =0;

struct pD {
	int R;
	int D;
	int QX;
	int QY;
	int ignore;
};
#define MAX_PUZ 1000000
struct pD pz[MAX_PUZ];
#define T 30 
#define M 12 
#define MAXX 100

void findstart(int *startx, int *starty);
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day23part1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

	leny=0, lenx =0;

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

pz[0].QX = sX;
pz[0].QY = sY;
NUM_PUZ = 1;
pz[0].R = M;
pz[0].D = M;
int MAX_STEPS=6;
if (argc > 2) {MAX_STEPS = atoi(argv[2]);}
int STEPS=0;
 while (NUM_PUZ != 0) {
	for (int k = 0; k < NUM_PUZ-1 ; k++) {
		for (int l = k+1; l < NUM_PUZ ; l++) {
			if (pz[k].R == pz[l].R && pz[k].D == pz[l].D &&
			    pz[k].QX == pz[l].QX && pz[k].QY == pz[l].QY) {
				pz[k].QX = -1;
			}
		}
	}

	for (int k = 0; k < NUM_PUZ ; k++) {
		if (amalgamate(k) == 22) {k--;}
	}
{
	int maxR = 0; int minR = M;
	int maxD = 0; int minD = M;
	for (int k = 0; k < NUM_PUZ-1 ; k++) {
		if (pz[k].R > maxR) {maxR = pz[k].R;}	
		if (pz[k].R < minR) {minR = pz[k].R;}	
		if (pz[k].D > maxD) {maxD = pz[k].D;}	
		if (pz[k].D < minD) {minD = pz[k].D;}	
	}
	//printf("maxR: %d minR: %d maxD: %d minD %d\n", maxR, minR, maxD, minD);
	int RDvals[T][T] = {0};
	int QXList[T][T][MAXX] = {0};
	int QYList[T][T][MAXX] = {0};
	int QXListpos[T][T] = {0};
	int QYListpos[T][T] = {0};
	int PzListpos[T][T]={0}; 
	int PzList[T][T][MAXX] = {0};
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			for (int k = 0; k < NUM_PUZ ; k++) {
				if (pz[k].R == Rval && pz[k].D == Dval) {
					RDvals[Rval][Dval]++;
					QXList[Rval][Dval][QXListpos[Rval][Dval]] = pz[k].QX;
					                   QXListpos[Rval][Dval]++;

					QYList[Rval][Dval][QYListpos[Rval][Dval]] = pz[k].QY;
						           QYListpos[Rval][Dval]++;
					PzList[Rval][Dval][PzListpos[Rval][Dval]] = k;
						           PzListpos[Rval][Dval]++;
					
				}
			}
		}
	}
	
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			BubbleSort(QXList[Rval][Dval], MAXX);
			BubbleSort(QYList[Rval][Dval], MAXX);
		}
	}	
	int players[T*T] = {0};
	int playersNum = 0;
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			int found = 0;
			for (int i = 0; i < playersNum; i++) {
				if (players[i] == RDvals[Rval][Dval]) {
					found = i;
					break;
				}
			} 
			if (found == 0) {players[playersNum] = RDvals[Rval][Dval]; playersNum++;} 
		}
	}

	struct p RDvalsCount[T][T] = {0};
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			RDvalsCount[Rval][Dval].count = 1;	
			RDvalsCount[Rval][Dval].val = RDvals[Rval][Dval];	
		}
	}

	//printf("%d is %d\n", M, RDvals[M][M]);
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			for (int Rval2 = 0; Rval2 < T; Rval2++) {
				for (int Dval2 = 0; Dval2 < T; Dval2++) {
					if (Rval2 == Rval && Dval2 == Dval) {continue;}
					if (RDvals[Rval][Dval] == RDvals[Rval2][Dval2] && RDvals[Rval][Dval]>0) {
						int found = 0;
						for (int i = 0; i < MAXX; i++) {
							if (QXList[Rval][Dval][i] != QXList[Rval2][Dval2][i]) {
								found = 1;	
							}
							if (QYList[Rval][Dval][i] != QYList[Rval2][Dval2][i]) {
								found = 1;	
							}
						}
						if (found == 0) {RDvalsCount[Rval][Dval].val = RDvals[Rval][Dval]; RDvalsCount[Rval][Dval].count++; RDvals[Rval2][Dval2] = -2; RDvalsCount[Rval2][Dval2].val = RDvals[Rval][Dval]; RDvalsCount[Rval2][Dval2].count = -2;} /*else {RDvalsCount[Rval2][Dval2].val = RDvals[Rval2][Dval2]; RDvalsCount[Rval2][Dval2].count = -1;} */
					}
				} 
			}
		}
		//printf("\n");
	}
	//printf("\n");

/*
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			if (RDvalsCount[Rval][Dval].val == 0 && RDvalsCount[Rval][Dval].count == 1) {
				printf("      ");
			} else {
				printf("%2d:%2d ", RDvalsCount[Rval][Dval].val, RDvalsCount[Rval][Dval].count);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("PLOTS %d STEPS %d\n", NUM_PUZ, STEPS);
*/

	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			if (RDvalsCount[Rval][Dval].val == 42 || RDvalsCount[Rval][Dval].val == 39) {
				for (int k1 = 0; k1 < PzListpos[Rval][Dval]; k1++) {
					pz[PzList[Rval][Dval][k1]].ignore = 1; 
				}
			}
		}
	}
/*

	for (int k = 0; k < NUM_PUZ ; k++) {
		if (amalgamate(k) == 22) {k--;}
	}
*/
/*
	for (int Rval = 0; Rval < T; Rval++) {
		for (int Dval = 0; Dval < T; Dval++) {
			if (Rval == M && Dval == M) {
				printf("C  ");
			} else {
				printf("%2d ", RDvals[Rval][Dval]);
			}
		}
		printf("\n");
	}
	printf("\n");
*/
}

	if (STEPS%10==0) { printf("[%s] PLOTS %d STEPS %d\n", argv[1], NUM_PUZ, STEPS);}
   	int puzes = NUM_PUZ;
	if (STEPS == MAX_STEPS) { printf("[%s] PLOTS %d STEPS %d\n", argv[1], puzes, STEPS); exit(0);}
	for (int c1 = 0; c1 < puzes; c1++) {
		if (c1 == 0) {STEPS++;}
		if (pz[c1].ignore == 1) {continue;}
		int x = pz[c1].QX;
		int y = pz[c1].QY;
		dotpuz = 0;
		//printpuzzle(c1); getchar();
		pz[c1].QX = -1;

		struct upleft uple; int myx; int myy;
		int newx = x; int newy = y+1; int ret;
		ret = newpuzzleP(c1, &newx, &newy, &uple);
		if (ret == 1) {myx = newx; myy = newy;}

		newx = x; newy = y-1;
		ret = newpuzzleP(c1, &newx, &newy, &uple);
		if (ret == 1) {myx = newx; myy = newy;}

		newx = x+1; newy = y;
		ret = newpuzzleP(c1, &newx, &newy, &uple);
		if (ret == 1) {myx = newx; myy = newy;}

		newx = x-1; newy = y;
		ret = newpuzzleP(c1, &newx, &newy, &uple);
		if (ret == 1) {myx = newx; myy = newy;}
		
		if (dotpuz >= 1) {
			pz[c1].R = uple.cR; pz[c1].D = uple.cD; 
			pz[c1].QX = myx; pz[c1].QY = myy;}
		}
	
	}


	printf("leny is %d\n", leny);
	printf("lenx is %d\n", lenx);
}

void BubbleSort(int a[], int array_size)
{
    int i, j, temp;
    for (i = 0; i < (array_size - 1); ++i)
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
            if (a[j] > a[j+1])
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
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

void printpuzzle(int puzzlenum) 
{
	for (int y = 0; y < leny; y++)
	{
		for (int x = 0; x < lenx; x++)
		{
			if (x == pz[puzzlenum].QX && y == pz[puzzlenum].QY) {
				printf("Q");
			} else {
				printf("%c", puzzle[y][x]);
			}
		}
		printf("\n");
	}
}

int amalgamate(int first)
{
	
        if (pz[first].QX == -1) { 
		for (int d = first; d < NUM_PUZ; d++) {
			for (int y = 0; y< leny; y++)  {
				pz[d] = pz[d+1];
			}
		}
		pz[NUM_PUZ-1].R = 12;
		pz[NUM_PUZ-1].D = 12;
		pz[NUM_PUZ-1].QX = 0;
		pz[NUM_PUZ-1].QY = 0;
		NUM_PUZ--;
		return 22;
	} else {
		return 0;
        }
}

void copypuzzle(int frompuz, int x, int y, int cR, int cD)
{
	pz[NUM_PUZ].QX = x;
	pz[NUM_PUZ].QY = y;
	pz[NUM_PUZ].R = cR;
	pz[NUM_PUZ].D = cD;
	NUM_PUZ++;
	if (NUM_PUZ + 50 > MAX_PUZ) {
		printf("WARNING in copypuzzle: [%d] MAX_PUZ:[%d]\n", NUM_PUZ, MAX_PUZ); fflush(stdout);
	}
}

int newpuzzleP(int curpuzzle, int *x1, int *y1, struct upleft *blah) 
{
	int cR = pz[curpuzzle].R; int cD = pz[curpuzzle].D;
	if (*x1 < 0) {*x1 = lenx-1; cR = pz[curpuzzle].R; cR++;}
	if (*x1 == lenx) {*x1 = 0; cR = pz[curpuzzle].R; cR--;}
	if (*y1 < 0) {*y1 = leny-1; cD = pz[curpuzzle].D; cD++;}
	if (*y1 == leny) {*y1 = 0; cD = pz[curpuzzle].D; cD--;}

	int x = *x1; int y = *y1;
	if (      puzzle[y][x] == '#') {
		/* game over */
	} else if (puzzle[y][x] == '.') {
		dotpuz++;
		if (dotpuz == 1) {
			blah->cR = cR;
			blah->cD = cD;	
			return 1;
		} else {
			copypuzzle(curpuzzle, x, y, cR, cD);
		}
	} 
	return 0;
}


