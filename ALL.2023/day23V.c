#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

int lenx, leny;
int foundEND =0;
#define MAX_CON 100
#define MAX_DIST2 100
struct fromto {
	int from;
	int to;
};
struct mybool {
	bool befB[MAX_CON][MAX_CON];
};
int level = -1;
void nextX(int weight1, int from, int to, struct mybool bef, int myfrom, int myto);
int MAXweight = 0;
int myMAX2 = 0;
int myMAX3 = 0;

#define MAX_X  141
#define MAX_Y  MAX_X

int newpuzzleP(int curpuzzle, int newx, int y, int fromx, int fromy);
int newpuzzleP2(int curpuzzle, int newx, int y, int fromx, int fromy);
void amalgamate(int start);
//////////
void printpuzzle(int puzzlenum);
void printQ(int puzzlenum);
void printpuzzlemain();
/////////

int NUM_PUZ;
#undef _DEBUG_
int distanceXYZ(int v1);
int distance2(int v1, int tru, int vert1);

char puzzle[MAX_X][MAX_X];
int beentherepuz[MAX_X][MAX_X];
int dotpuz = 0;

struct con {
	int to;
	int weight;
};
struct pointVect {
	int Iname;
	int x;
	int y;
	int weight;
	int tovert;
	int numCross;
	int throughArray[MAX_CON];
	int distanceto[MAX_DIST2];
	struct con cons[MAX_CON];
	int tmax;
	int conNUM;
};
/*
struct pointV {
	char puzQ[MAX_X][MAX_X];
	int Iname;
	int x;
	int y;
	int weight;
	int tovert;
	int numCross;
	int throughArray[MAX_CON];
	int distanceto[MAX_DIST2];
	struct con cons[MAX_CON];
	int tmax;
	int conNUM;
};
*/
struct pointVect vertex[MAX_CON];

int vertNUM = 0;
struct pD {
	char puzQ[MAX_X][MAX_X];
	int QX;
	int QY;
	int distance;
	int through;
};
#define MAX_PUZ 1000
struct pD pz[MAX_PUZ];
struct pD pB;
struct pD pB2;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day23part2\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

	leny=0, lenx =0;
	for (int j = 0; j < MAX_X;j++) {
		for (int k = 0; k< MAX_X; k++) {
		   beentherepuz[j][k] = 0;
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
////////////////////////////////////
	printf("*NB lenx: %d leny %d \n", lenx, leny); fflush(stdout);


	printf("BEFORE seeding [%d] puzzles..\n", MAX_PUZ); fflush(stdout);
	 for (int i = 0; i < MAX_PUZ; i++) {
		for (int y=0; y< leny; y++) {
			strcpy(pz[i].puzQ[y], puzzle[y]);
		}
		pz[i].QX=0; pz[i].QY=0;pz[i].distance=0; pz[i].through = 0;
	}
	{
		for (int y=0; y< leny; y++) {
			strcpy(pB2.puzQ[y], puzzle[y]);
		}
		pB2.QX = 0; pB2.QY = 0; pB2.distance = 0; pB2.through = 0;
	}
	{
		for (int y=0; y< leny; y++) {
			strcpy(pB.puzQ[y], puzzle[y]);
		}
		pB.QX = 0; pB.QY = 0; pB.distance = 0; pB.through = 0;
	}
	printf("AFTER seeding [%d] puzzles..\n", MAX_PUZ); fflush(stdout);

	beentherepuz[0][1] = 0;
	beentherepuz[1][1] = 1;
	pz[0].QX = 1;
	pz[0].QY = 0;
	pz[0].distance = 0;
	NUM_PUZ = 1;

/////////////////////////////////////////
	vertNUM=0;
	vertex[0].x = 1;
	vertex[0].y = 0;
	vertex[0].weight = 0;
	vertex[0].conNUM = 0;
	vertex[0].Iname = 0;
	vertNUM++;
	for (int x = 0; x < lenx; x++) {
		for (int y = 0; y < leny; y++) {
			char c1, c2, c3, c4;
			int vertpoint = 0;
			if (pB.puzQ[y][x] != '#') {
				if (x+1 < lenx) {c1 = pB.puzQ[y][x+1]; if (c1 == '.' || c1 == '^' || c1 == '>' || c1 == 'v' || c1 == '<') { vertpoint++; }}
				if (x-1 > 0)    {c2 = pB.puzQ[y][x-1]; if (c2 == '.' || c2 == '^' || c2 == '>' || c2 == 'v' || c2 == '<') { vertpoint++; }}
				if (y+1 < leny) {c3 = pB.puzQ[y+1][x]; if (c3 == '.' || c3 == '^' || c3 == '>' || c3 == 'v' || c3 == '<') { vertpoint++; }}
				if (y-1 > 0)    {c4 = pB.puzQ[y-1][x]; if (c4 == '.' || c4 == '^' || c4 == '>' || c4 == 'v' || c4 == '<') { vertpoint++; }}

				if (vertpoint > 2) {vertex[vertNUM].x = x; vertex[vertNUM].y = y; vertex[vertNUM].weight = 0;vertex[vertNUM].Iname = vertNUM; vertex[vertNUM].numCross = vertpoint; vertNUM++;}
			}
		}
	}
	vertex[vertNUM].x = lenx-2;
	vertex[vertNUM].y = leny-1;
	vertex[vertNUM].weight = 0;
	vertex[vertNUM].Iname = vertNUM;
	vertNUM++;
	printf("vertNUM is %d\n", vertNUM);

	for (int iS = 0; iS < vertNUM; iS++) {
			printf("calling distance... iS %d", iS);
			distanceXYZ(iS);
	}
	for (int i = 1; i< vertNUM-1; i++) {
		if (vertex[i].numCross  != vertex[i].conNUM) {
			printf("ERROR with %d not enough crosses\n", i);
			for (int j = 1; j < vertNUM-1; j++) {
				if (vertex[i].throughArray[j] != 0) {
					//printf("vertex:%d  #:%d want:%d\n", i, vertex[i].throughArray[j], j); 
				}
			}
			printf("\n");
		}
	}
	for (int i = 1; i< vertNUM-1; i++) {
		if (vertex[i].numCross  != vertex[i].conNUM) {
			printf("ERROR with %d not enough crosses\n", i);
			for (int j = 1; j < vertNUM-1; j++) {
				if (vertex[i].throughArray[j] != 0) {
					printf("vertex:%d  #:%d want:%d\n", i, vertex[i].throughArray[j], j); 
					distance2(i, vertex[i].throughArray[j], j); 
				}
			}
			printf("\n");
		}
	}
	for (int i = 0; i< vertNUM; i++) {
		printf("vertex %d: %d %d %d tovert: %d X: %d", 
			i, vertex[i].x, vertex[i].y, vertex[i].weight, vertex[i].tovert, vertex[i].numCross); 
		printf(" con: ");
		for  (int l = 0; l < vertex[i].conNUM; l++) {
			printf(" %d ", vertex[i].cons[l].to);
		}
		printf(" to: ");
		for  (int j = 0; j < vertex[i].conNUM; j++) {
			printf(" %d ", vertex[i].cons[j].weight);
		}
		printf("\n");
	}
	for (int i = 1; i< vertNUM-1; i++) {
		if (vertex[i].numCross  != vertex[i].conNUM) {
			printf("ERROR with %d crosses mismatch\n", i);
			for (int j = 0; j < vertNUM; j++) {
				printf(" vertex:%d -> %d %d\n", i, j, vertex[i].throughArray[j]);
			}
			printf("\n");
		} else {
			printf("vertex %d OK\n", i);
		}
	}
	int maxCONNUM = 0;
	for (int i = 0; i < vertNUM; i++ ) {
		if (vertex[i].conNUM > maxCONNUM) {maxCONNUM=vertex[i].conNUM;}
		
	}

	printf("maxCONNUM is %d\n", maxCONNUM);
/*
	vertex[2].cons[vertex[2].conNUM].to = 5;
	vertex[2].cons[vertex[2].conNUM].weight = 38;
	vertex[2].conNUM++;
	vertex[5].cons[vertex[5].conNUM].to = 2;
	vertex[2].cons[vertex[5].conNUM].weight = 38;
	vertex[5].conNUM++;
*/

	NUM_PUZ = 1;
	for (int iS = 0; iS < vertNUM; iS++) {
			pz[0].puzQ[vertex[iS].y][vertex[iS].x] = 48+iS;
	}
	//printpuzzle(0);
	//getchar();

	for (int i = 0; i < vertex[0].conNUM; i++ ) {
		printf("going in \n"); 
		int myweight2 = vertex[0].cons[i].weight;
		int myto = vertex[0].cons[i].to;
		int myfrom = 0;
		struct mybool tmparr;
		for (int x = 0; x < MAX_CON; x++) {
			for (int y = 0; y< MAX_CON; y++) {
				tmparr.befB[y][x] = false;
			}
		}
		nextX(myweight2, myfrom, myto, tmparr, -1, -1);
		
	}

	printf("MAXweight is %d\n", MAXweight);
	printf("**correct (END REACHED) myMAX2 is %d\n", myMAX2);
	printf("**correctP (END REACHED) myMAX3 is %d\n", myMAX3);
	printf("leny is %d\n", leny);
	printf("lenx is %d\n", lenx);
}
void nextX(int w, int from, int to, struct mybool bef, int myfrom, int myto)
{
	level++;
	bef.befB[from][to] = true;
	bef.befB[to][from] = true;
	
	if (myfrom != -1) {
		int tmpcountCONNUM = vertex[from].conNUM;
		if (tmpcountCONNUM == 3) {
			bef.befB[myfrom][myto] = true;
		}
	}

	int weightOrig = w;
	int weightCOPY = w;

	if (to+3 == vertNUM) {
		if (weightCOPY + vertex[vertNUM-1].weight > myMAX3) {myMAX3 = weightCOPY + vertex[vertNUM-1].weight;}
	}


	if (to+1 == vertNUM) {
		foundEND++;
		//printf("reached end: weightCOPY %d\n", weightCOPY);
		if (foundEND % 800000 == 0) {printf(" %d: %d", foundEND, weightCOPY); fflush(stdout);}
		if (weightCOPY > myMAX2) {myMAX2 = weightCOPY;}
		level--;
		return;

	} else {
		int foundAtk = -1;
		int nofurther = 0;
		int arr[3] = {0,1,2};

		int countCONNUM = vertex[to].conNUM;
		if (countCONNUM == 3) {
			int countV3 = 0;
			for (int l = 0; l < countCONNUM; l++) {
				int vertTo2 = vertex[to].cons[l].to;
				if (bef.befB[to][vertTo2]) {foundAtk = l; arr[foundAtk] = -1; countV3++; }
			}
			if (countV3 < 1) {printf("ERRORR counntV3"); fflush(stdout);}
			if (countV3 == 2 ||  countV3 == 3) {nofurther = 1;}
		
		} else if (countCONNUM == 4) {
			int countV4 = 0;
			for (int m = 0; m < countCONNUM; m++) {
				int vertTo3 = vertex[to].cons[m].to;
				if (bef.befB[to][vertTo3]) { countV4++;}
			}
			if (countV4 < 1) {printf("ERROR countV4"); fflush(stdout);}
			if (countV4 == 3 || countV4 == 4) {nofurther = 1;}
		} else if (countCONNUM == 2) {
			//printf("found two... what to do????");
		} else {
			//printf("found one... what to do????");
		}
		
		if (nofurther == 0) {
			for (int j = 0; j < countCONNUM; j++) {
				if (foundAtk == j) {continue;}

				int vertTo = vertex[to].cons[j].to;
				if (bef.befB[to][vertTo]) { continue; }

				weightCOPY = weightOrig + vertex[to].cons[j].weight;

				int myfrom2 = -1; int myto2 = -1;
				if (countCONNUM == 3 && foundAtk != -1) {
					int mycount = 0;
					int jpos;
					arr[j] = -1; jpos = j;
					for (int r = 0; r < 3; r++) {
						if (arr[r] != -1) {mycount++;}
					}
					//if (mycount != 1) {printf("%d", mycount);getchar();}
					for (int r = 0; r < 3; r++) {
						if (arr[r] != -1) {
							myto2 = vertex[to].cons[r].to;
							myfrom2 = to;
							break;
						}
					}
					arr[jpos] = jpos;
					//printf("*3 from to myfrom2 myto2 %d %d %d %d\n", to, vertTo, myfrom2, myto2);
					//for (int i = 0; i < level; i++) {printf ("	");}
					//printf(" %d -> %d \n", to, vertTo);
					nextX(weightCOPY, to, vertTo, bef, myfrom2, myto2);
				} else {
					//printf("*4 from to myfrom2 myto2 %d %d %d %d\n", to, vertTo, myfrom2, myto2);
					//for (int i = 0; i < level; i++) {printf ("	");}
					//printf(" %d -> %d \n", to, vertTo);
					nextX(weightCOPY, to, vertTo, bef, -1, -1);
				}
			}
		}
	}	
	level--;
}

int newpuzzleP2(int curpuzzle, int x, int y, int fromx, int fromy)
{
	if (x < 0 || y < 0 || x == lenx || y == leny) {pz[curpuzzle].puzQ[y][x] = 'R';return 0;}

	if (pz[curpuzzle].distance < beentherepuz[y][x] || beentherepuz[y][x] == 0) {
		beentherepuz[y][x] = pz[curpuzzle].distance;

		char c1 = pB2.puzQ[y][x];
		if (c1 == '#') {
			/* game over */
			return 0;
		} else if (c1 == '.' || c1 == '^' 
			|| c1 == '>' || c1 == 'v' || c1 == '<') {
			dotpuz++; 
			if (dotpuz == 1) {
				return 1;
			} else {
				if (pz[curpuzzle].puzQ[y][x] != 'R') {
					pz[NUM_PUZ] = pz[curpuzzle];
					pz[NUM_PUZ].QX= x;
					pz[NUM_PUZ].QY= y;
					pz[NUM_PUZ].distance = pz[curpuzzle].distance + 1;
					NUM_PUZ++;
					if (NUM_PUZ+50 == MAX_PUZ) {
						printf("WARNING WARNING... MAX_PUZ"); fflush(stdout);
						exit(1);
					}
				}
				return 0;
			}
		}
	}
	return 0;
}


int distance2(int v1, int tru, int vert1) {
printf("----------vvv %d---------------\n", v1);
	for (int iZ= 0; iZ< NUM_PUZ; iZ++) {
		for (int y1=0; y1< leny; y1++) {
			strcpy(pz[iZ].puzQ[y1], puzzle[y1]);
		}
		pz[iZ].QX=0; pz[iZ].QY=0; pz[iZ].distance=0; pz[iZ].through = 0;
	}
	
	for (int j = 0; j < MAX_X;j++) {
		for (int k = 0; k< MAX_X; k++) {
		   beentherepuz[j][k] = 0;
		}
	}
	int foundfirst = 0; int fD; int nD = 0;

	beentherepuz[0][1] = 0;
	//beentherepuz[1][1] = 1;
	pz[0].QX = vertex[v1].x;
	pz[0].QY = vertex[v1].y;
	int myx = vertex[tru].x;
	int myy = vertex[tru].y;
	pB2.puzQ[myy][myx] = '#';
	//printpuzzle(0);
	pz[0].distance = 0;
	pz[0].through = 0;
	NUM_PUZ = 1;
while (NUM_PUZ!=0) {
                for (int k = 0; k <= NUM_PUZ - 1; k++) {
                        amalgamate(k);
                }

	for (int i = 0; i< NUM_PUZ; i++) {
		pz[i].puzQ[myy][myx] = '#';
	}

	int puzNUM = NUM_PUZ;
	for (int c = 0; c < puzNUM; c++) {
		int x = pz[c].QX;
		int y = pz[c].QY;
		if (x==-1) {continue;}
		for (int i1 = 0; i1 < vertNUM; i1++) {
			if (vertex[i1].x == x && vertex[i1].y == y) {
				if (i1 == 5 && v1 == 2) {
//					printf("***found vertex for %d -> %d pz[c].through %d c is %d\n", v1, i1, pz[c].through, c); getchar();
				}
				if (i1 != tru) {
					if (pz[c].through == 0) {
						if (i1 == 5 && v1 == 2) {
							//printf("***half (totru)processing vertex for %d -> %d pz[c].through %d c is %d\n", v1, i1, pz[c].through, c);
							//printf("vert1 is %d\n", vert1 );

						}
						foundfirst = 1;
						nD = pz[c].distance;
						vertex[v1].distanceto[i1] = nD;
						printf("vert1 is %d\n", vert1 );
						if (i1 == vert1) {
							//printf("***tru %d->%d next distance: [%d] %d %d\n", v1, i1, nD, pz[c].QX, pz[c].QY); getchar();
							fD = 0;
							if (foundfirst == 1) { 
								if (vertex[v1].weight > abs(nD - fD) || vertex[v1].weight == 0) {
									//if (vertex[v1].weight!=0) {printf("changed from... %d\n", vertex[v1].weight); }
									vertex[v1].weight = abs(nD - fD); 
									vertex[v1].tovert = i1;
								}
							}
							if (v1 != i1) {vertex[v1].cons[vertex[v1].conNUM].to = i1; 
								vertex[v1].cons[vertex[v1].conNUM].weight = nD; vertex[v1].conNUM++;
							}
						}
						if (v1 != i1) {pz[c].through = 1+i1; printf("setting through to 1 for %d v1, i1 %d, %d\n", c, v1, i1); }
						
					}
				}
			}
		}

		if (pz[c].puzQ[y][x] != 'R') {
			dotpuz = 0;
			pz[c].QX = -1;
			pz[c].puzQ[y][x] = 'R';
			int ret = 0; int myx; int myy; int found1 = 0;
			ret = newpuzzleP2(c, x,   y+1, x, y);
			if (ret == 1) {myx = x; myy = y+1; found1 = 1;}
			ret = newpuzzleP2(c, x,   y-1, x, y);
			if (ret == 1) {myx = x; myy = y-1; found1 = 1;}
			ret = newpuzzleP2(c, x+1, y, x, y);
			if (ret == 1) {myx = x+1; myy = y; found1 = 1;}
			ret = newpuzzleP2(c, x-1, y, x, y);
			if (ret == 1) {myx = x-1; myy = y; found1 = 1;}
			
			if (found1 == 1) {
				if (pz[c].puzQ[myy][myx] != 'R') {
					pz[c].QX = myx;
					pz[c].QY = myy;
					pz[c].distance++;
				}
			} else {
				printf("never found1 %d x, y %d, %d\n", found1, x, y);
				pz[c].QX = -1;
				pz[c].through = 0;
			}
			continue;
		} else {
			pz[c].QX = -1;
			pz[c].through = 0;
			continue;
		}
	}
}
	pB2.puzQ[myy][myx] = pB.puzQ[myy][myx];
	return 1;
}
int distanceXYZ(int v1) {
printf("----------vvv %d---------------\n", v1);
	for (int iZ= 0; iZ< NUM_PUZ; iZ++) {
		for (int y1=0; y1< leny; y1++) {
			strcpy(pz[iZ].puzQ[y1], puzzle[y1]);
		}
		pz[iZ].QX=0; pz[iZ].QY=0; pz[iZ].distance=0; pz[iZ].through = 0;
	}
	
	for (int j = 0; j < MAX_X;j++) {
		for (int k = 0; k< MAX_X; k++) {
		   beentherepuz[j][k] = 0;
		}
	}
	int foundfirst = 0; int fD; int nD = 0;

	beentherepuz[0][1] = 0;
	//beentherepuz[1][1] = 1;
	pz[0].QX = vertex[v1].x;
	pz[0].QY = vertex[v1].y;
	pz[0].distance = 0;
	pz[0].through = 0;
	NUM_PUZ = 1;
while (NUM_PUZ!=0) {
                for (int k = 0; k <= NUM_PUZ - 1; k++) {
                        amalgamate(k);
                }


	int puzNUM = NUM_PUZ;
	for (int c = 0; c < puzNUM; c++) {
		int x = pz[c].QX;
		int y = pz[c].QY;
		if (x==-1) {continue;}
		for (int i1 = 0; i1 < vertNUM; i1++) {
			if (vertex[i1].x == x && vertex[i1].y == y) {
				if (i1 == 5 && v1 == 2) {
					printf("found vertex for %d -> %d pz[c].through %d c is %d\n", v1, i1, pz[c].through, c);
				}
				{
					if (pz[c].through == 0) {
						if (i1 == 5 && v1 == 2) {
							printf("processing vertex for %d -> %d pz[c].through %d c is %d\n", v1, i1, pz[c].through, c);
						}
						foundfirst = 1;
						nD = pz[c].distance;
						printf("tru next distance: [%d] %d %d\n", nD, pz[c].QX, pz[c].QY); 
						vertex[v1].distanceto[i1] = nD;
						fD = 0;
						if (foundfirst == 1) { 
							if (vertex[v1].weight > abs(nD - fD) || vertex[v1].weight == 0) {
								//if (vertex[v1].weight!=0) {printf("changed from... %d\n", vertex[v1].weight); }
								vertex[v1].weight = abs(nD - fD); 
								vertex[v1].tovert = i1;
							}
						}
						if (v1 != i1) {pz[c].through = 1+i1; printf("setting through to 1 for %d v1, i1 %d, %d\n", c, v1, i1); }
						if (v1 != i1) {vertex[v1].cons[vertex[v1].conNUM].to = i1; 
							vertex[v1].cons[vertex[v1].conNUM].weight = nD; vertex[v1].conNUM++;}
						
					} else {
						vertex[i1].throughArray[v1] = pz[c].through -1;
					}
				}
			}
		}

		if (pz[c].puzQ[y][x] != 'R') {
			dotpuz = 0;
			pz[c].QX = -1;
			pz[c].puzQ[y][x] = 'R';
			int ret = 0; int myx; int myy; int found1 = 0;
			ret = newpuzzleP(c, x,   y+1, x, y);
			if (ret == 1) {myx = x; myy = y+1; found1 = 1;}
			ret = newpuzzleP(c, x,   y-1, x, y);
			if (ret == 1) {myx = x; myy = y-1; found1 = 1;}
			ret = newpuzzleP(c, x+1, y, x, y);
			if (ret == 1) {myx = x+1; myy = y; found1 = 1;}
			ret = newpuzzleP(c, x-1, y, x, y);
			if (ret == 1) {myx = x-1; myy = y; found1 = 1;}
			
			if (found1 == 1) {
				if (pz[c].puzQ[myy][myx] != 'R') {
					pz[c].QX = myx;
					pz[c].QY = myy;
					pz[c].distance++;
				}
			} else {
				printf("never found1 %d x, y %d, %d\n", found1, x, y);
				pz[c].QX = -1;
				pz[c].through = 0;
			}
			continue;
		} else {
			pz[c].QX = -1;
			pz[c].through = 0;
			continue;
		}
	}
}
	return 1;
}

void amalgamate(int first)
{
	int found5 = 0;
	if (pz[first].QX != -1) {found5 = 1;}

        if (found5 == 0) { 
		for (int d = first; d < NUM_PUZ-1; d++) {
			pz[d] = pz[d+1];
		}
		if (NUM_PUZ-1 >=0) {pz[NUM_PUZ-1] = pB;}

		NUM_PUZ--;
        }
}

int newpuzzleP(int curpuzzle, int x, int y, int fromx, int fromy)
{
	if (x < 0 || y < 0 || x == lenx || y == leny) {pz[curpuzzle].puzQ[y][x] = 'R';return 0;}

	if (pz[curpuzzle].distance < beentherepuz[y][x] || beentherepuz[y][x] == 0) {
		beentherepuz[y][x] = pz[curpuzzle].distance;

		char c1 = pB.puzQ[y][x];
		if (c1 == '#') {
			/* game over */
			return 0;
		} else if (c1 == '.' || c1 == '^' 
			|| c1 == '>' || c1 == 'v' || c1 == '<') {
			dotpuz++; 
			if (dotpuz == 1) {
				return 1;
			} else {
				if (pz[curpuzzle].puzQ[y][x] != 'R') {
					pz[NUM_PUZ] = pz[curpuzzle];
					pz[NUM_PUZ].QX= x;
					pz[NUM_PUZ].QY= y;
					pz[NUM_PUZ].distance = pz[curpuzzle].distance + 1;
					NUM_PUZ++;
					if (NUM_PUZ+50 == MAX_PUZ) {
						printf("WARNING WARNING... MAX_PUZ"); fflush(stdout);
						exit(1);
					}
				}
				return 0;
			}
		}
	}
	return 0;
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

void printQ(int puzzlenum) 
{
	for (int y = 0; y < leny; y++)
	{
		for (int x = 0; x < lenx; x++)
		{
			printf("%c", pz[puzzlenum].puzQ[y][x]);
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
			printf("%c", pz[puzzlenum].puzQ[y][x]);
		}
		printf("\n");
	}
}

