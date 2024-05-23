#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#undef _DEBUG_
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;
#define SZ 50
int leny = 0;
int lenx = 0;
char grid[SZ][SZ];
char gridOrig[SZ][SZ];
int ELVES_HIT;
int numG = 0, numE = 0;
struct point_s {
	int x;
	int y;
	int GE;
	int hitpoints;
	int remove;
	int which;
	int shotAL;
};
	int round123 = 0;
//#define getchar()
struct point_s point[1000];
struct point_s pointOrig[1000];
int pointPos = 0;
int pointPosOrig = 0;
void orderPointsTOPLEFT();
int next(int po);
void printit();
void getMinDist(int fx, int fy, int path, int po, int fm, int tox, int toy);
int already[100][100];
void attack(int po);
int minPath = 9999;
int moved;
int getULRD (int po);
void endCheck(int chI);
int main(int argc, char **argv)
{
	//int fd = dup(1);
	//close(1);
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day15.1\n"); fflush(stdout);

	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'G') {
				numG++;
				grid[y][x] = '.';
				point[pointPos].x = x;
				point[pointPos].y = y;
				point[pointPos].GE = 1;
				point[pointPos].hitpoints = 200;
				point[pointPos].remove = 0;
				pointPos++;
			} else if (grid[y][x] == 'E') {
				numE++;
				grid[y][x] = '.';
				point[pointPos].x = x;
				point[pointPos].y = y;
				point[pointPos].GE = 2;
				point[pointPos].hitpoints = 200;
				point[pointPos].remove = 0;
				pointPos++;
			}
		}
	}
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			gridOrig[y][x] = grid[y][x];
		}
	}
	for (int i = 0; i < pointPos; i++) {
		pointOrig[i] = point[i];
	}	
	int pointPosOrig = pointPos;	
	int es, esA;
	if (argc != 3) {perror("give ELVES_HIT\n"); exit(0);}
for (ELVES_HIT = atoi(argv[2]); ELVES_HIT < 35; ELVES_HIT++) {
printf("ELVES_HIT is %d\n", ELVES_HIT);
	round123 = 0;
	pointPos = pointPosOrig;
	for (int y = 0; y < leny; y++) { for (int x = 0; x < lenx; x++) { grid[y][x] = gridOrig[y][x]; } }
	for (int i = 0; i < pointPos; i++) { point[i] = pointOrig[i]; }	
	
	printit();
	//int gs, es;
	int gs;
nextmove:
	
again3:
	for (int i = 0; i < pointPos; i++) {
		if (point[i].remove == 1) {
			for (int j = i+1; j < pointPos; j++) {
				point[i] = point[j];
			}
			pointPos--;
			goto again3;
		}
		point[i].shotAL = 0;
	}
		
	moved = 0;
	orderPointsTOPLEFT();

	round123++;
auto int isittheend();
	for (int i = 0; i < pointPos; i++) {
		next(i);
		//if (i!= pointsPos-1) {isittheend()==1) {break;}}
		if (i!= pointPos-1) {if (isittheend()==1) {printf("found the end...\n");getchar(); round123--; break;}}
	}
	if (round123 > 14) {getchar();}
	orderPointsTOPLEFT();
	for (int i = 0; i < pointPos; i++) {
		if (point[i].shotAL == 0) {
			endCheck(i);
		}
	}

	printf("\nROUND (AFTER) is %d vvvvvvv\n", round123); printit();
	int prevY = 0; int num = 0;
	printf("\x1b[2J");
	printf("\x1b[H");
	printit();
	for (int i = 0; i < pointPos; i++) {
		if (point[i].remove == 1) {continue;}
		printf("\x1b[H");
		if (point[i].GE == 1) {
			if (prevY == point[i].y) {
				num++;
			} else {
				num = 0;
			}
			printf("\x1b[%dC \x1b[%dB [G: %3d] \x1b[H\x1b[%dB", 37+(num*9), point[i].y, point[i].hitpoints, 35);
			//printf("\x1b[H\x1b[%dB", 35);
			prevY = point[i].y;
		} else {
			if (prevY == point[i].y) {
				num++;
			} else {
				num = 0;
			}
			printf("\x1b[%dC \x1b[%dB [E: %3d]\x1b[H\x1b[%dB", 37+(num*9), point[i].y, point[i].hitpoints, 35);
			//printf("\x1b[H\x1b[%dB", 35);
			prevY = point[i].y;
		}
	}
	printf("\x1b[H");
	printf("\x1b[%dB", 33);
	printf("   --------- ROUND: %d ------------\n", round123);
	printf("\x1b[H\x1b[%dB", 35);
	gs = 0; es = 0; int curnume = 0;

int isittheend() {
	gs = 0; es = 0;
	for (int i = 0; i < pointPos; i++) {
		if (point[i].remove == 1) {continue;}
		if (point[i].GE == 1) {
			gs += point[i].hitpoints;
			//printf("gs now %d\n", gs);
		} else if (point[i].GE == 2) {
			curnume++;
			es += point[i].hitpoints;
			//printf("es now %d\n", es);
		}
	}		
	if (gs == 0 || es == 0) {
		return 1;
	} else {
		return 0;
	}
}
	if (isittheend() == 1) {} else {goto nextmove;}
	//if (curnume != numE) {printf("lost an Elf -- continue upping ELVES_HIT from %d\n", ELVES_HIT); getchar(); continue;}	
	//dup2(fd, 1);
	printf("tots: gs is %d es is %d\n", gs, es);
	int gsA;

	gsA = gs *round123;
	esA = es *round123;
	printf("round123: gs is %d es is %d\n", gsA, esA);
	gsA = gs *(round123-1);
	esA = es *(round123-1);
	printf("round123-1: gs is %d es is %d\n", gsA, esA); printf("UPPING ELVES_HIT was %d\n", ELVES_HIT); getchar();
	printf("\x1b[2J");
	{printf("\n\n\nELVES_HIT is %d\nOUTCOME: %d \nOUT: %d ROUNDS %d es: %d\n", ELVES_HIT, gsA, gs*round123, round123, gs); getchar();}
	if (gs == 0 && curnume == numE) {printf("\n\n\nELVES_HIT is %d\nOUTCOME: %d \nOUT: %d ROUNDS %d es: %d\n", ELVES_HIT, esA, es*round123, round123, es); break;}
}
}

void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			int found = 0;
			for (int i = 0; i < pointPos; i++) {
				if (point[i].x == x && point[i].y == y && point[i].GE == 1 && point[i].remove != 1) {
					printf("G"); found = 1; break;
				} else if  (point[i].x == x && point[i].y == y && point[i].GE == 2 && point[i].remove != 1) {
					printf("E"); found = 1; break;
				}
			}
			if (found == 0) {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void getMinDist(int fx, int fy, int path, int po, int fm, int tox, int toy) {
	if (fx == tox && fy == toy) {
		if (path < minPath) {minPath = path;}
		return;
	}

	if (grid[fy][fx] == '#') {return;}

	if (fx >= lenx) {return;}
	if (fx < 0) {return;}
	if (fy >= leny) {return;}
	if (fy < 0) {return;}

	for (int i = 0; i < pointPos; i++) {
		if (i == po) {continue;}
		if (i == fm) {continue;}
		if (point[i].x == fx && point[i].y == fy &&point[i].remove != 1) { return; }
	}

	if (already[fy][fx] == -1 || path < already[fy][fx] || path == 0) {
		already[fy][fx] = path;
		{ getMinDist(fx, fy-1, path+1, po, fm, tox, toy);}
		{ getMinDist(fx+1, fy, path+1, po, fm, tox, toy);}
		{ getMinDist(fx, fy+1, path+1, po, fm, tox, toy);}
		{ getMinDist(fx-1, fy, path+1, po, fm, tox, toy);}
	}
		
}
	
int getULRD (int po) {

	int myx = point[po].x;
	int myy = point[po].y;
	int myPath = minPath -1;
	if (myy-1>= 0 && grid[myy-1][myx] != '#' && already[myy-1][myx] == myPath) {
		//if (po == 3 || po == 2) {printf("(%d) returning 0", po);}
			return 0;
	} else if (myx-1 >= 0 && grid[myy][myx-1] != '#' && already[myy][myx-1] == myPath) {
		//if (po == 3 || po == 2) {printf("(%d) returning 1", po);}
			return 1;
	} else if (myx+1 < lenx && grid[myy][myx+1] != '#' && already[myy][myx+1] == myPath) {
		//if (po == 3 || po == 2) {printf("(%d) returning 2", po);}
			return 2;
	} else if (myy+1 < leny && grid[myy+1][myx] != '#' && already[myy+1][myx] == myPath) {
		//if (po == 3 || po == 2) {printf("(%d) returning 3", po);}
			return 3;
	}
	//printf("minPath is %d al %d %d %d %d\n", minPath, already[myy-1][myx], already[myy][myx-1],
	//		already[myy][myx+1], already[myy+1][myx]);
	printf("ERR"); exit(0);
	return -1;
}
void endCheck(int chI) {
	for (int k = 0; k < pointPos; k++) {
		if (k == chI) {continue;}
		if (point[chI].GE == point[k].GE) {continue;}
		if (point[k].remove == 1) {continue;}
		if (point[chI].remove == 1) {continue;}
		if (point[chI].y -1 == point[k].y && point[chI].x == point[k].x) {
			printf("yes (%d) y-1: %d %d\n", chI, point[chI].shotAL, point[k].shotAL); 
		}
		if (point[chI].y == point[k].y && point[chI].x -1 == point[k].x) {
			printf("yes (%d) x-1: %d %d\n", chI, point[chI].shotAL, point[k].shotAL);
		}
		if (point[chI].y == point[k].y && point[chI].x +1 == point[k].x) {
			printf("SIM:\n");
			printf("yes (%d) x+1: %d %d\n", chI, point[chI].shotAL, point[k].shotAL);
			//if (point[k].GE == 1) { point[k].hitpoints -= ELVES_HIT; } else { point[k].hitpoints -= 3; }
		}
		if (point[chI].y +1 == point[k].y && point[chI].x == point[k].x) {
			printf("yes (%d) y+1: %d %d\n", chI, point[chI].shotAL, point[k].shotAL);
		}
	}

}
int next(int po) {
	
	int move = 1;
	int once = 1;
restartNext:
	auto void lessmin();
	struct dists_s {
		int dist;
		int itsi;
		int hits;
		int ulrd;
	};
#define DSZ 2000
	struct dists_s dists[DSZ];
	int myPP = 0;

	void lessmin(int px1, int py1,  int i) {
		if (i == po) {return;}
		for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
		already[point[i].y+py1][point[i].x+px1] = 0;
		already[point[i].y][point[i].x] = 0;
		minPath = 9999;
		getMinDist(point[i].x+px1, point[i].y+py1, 0, po, i, point[po].x, point[po].y);
				
		if (round123 > 9 && (po == 2 || po == 3 || po == 4) && minPath != 9999) {
			//printf("(%d) minPath: %d to pos: %d\n", po, minPath, i);
		}
		if (minPath < dists[myPP].dist) {
			dists[myPP].ulrd = getULRD(po);
			assert(dists[myPP].ulrd >= 0 && dists[myPP].ulrd <= 3);
			dists[myPP].dist = minPath; dists[myPP].itsi = i;  
			dists[myPP].hits = point[i].hitpoints;myPP++;
		if (round123 > 9 && (po == 2 || po == 3 || po == 4)) {
			//printf("(%d) mP: %d to %d ul: %d di:%d itsi:%d hits:%d\n", po, minPath, i,
				//dists[myPP-1].ulrd, dists[myPP-1].dist, dists[myPP-1].itsi,
				//dists[myPP-1].hits);
		}


		}
	}

	for (int i = 0; i < DSZ; i++) {
		dists[i].dist = 9999;
		dists[i].hits = -10;
		dists[i].itsi = -1;
		dists[i].ulrd = -1;
	}
	//printf("po:%d now is type:(%d) (%d,%d)\n", po, point[po].GE, point[po].x, point[po].y);
auto void calcdists(int GE);
void calcdists(int GE) {
			//printf("in calc dists...\n");
			for (int i = 0; i < pointPos; i++) {
				if (po == i) {continue;}
				if (point[i].remove == 1) {continue;}
				if (point[i].GE == GE) {continue;}
	
				if (grid[point[i].y-1][point[i].x] != '#') {
					lessmin(0, -1, i);
				}
				if (grid[point[i].y][point[i].x-1] != '#') {
					lessmin(-1, 0, i);
				}
				if (grid[point[i].y][point[i].x+1] != '#') {
					lessmin(1, 0, i);
				}
				if (grid[point[i].y+1][point[i].x] != '#') {
					lessmin(0, 1, i);
				}
			}
}
	for (int GE = 1; GE <= 2; GE++) {
		if (point[po].GE != GE) {continue;}
		if (point[po].remove == 1) {continue;}

		myPP = 0;
		if (point[po].GE == GE) { //TOP
			calcdists(GE);
		}
		int mypos = myPP;
		if (mypos == 0) {return 0;}
again4:
		for (int i = 0; i < mypos; i++) {
			if (dists[i].dist == -1 || dists[i].dist == 9999) {
				for (int j = i; j < mypos; j++) {
					dists[j] = dists[j+1];
				}
				mypos--;
				goto again4;
			}
		}

		struct dists_s tmpdists[DSZ];
		for (int i = 0; i < mypos; i++) {
			tmpdists[i].itsi = dists[i].itsi;
			tmpdists[i].dist = dists[i].dist;
			tmpdists[i].hits = dists[i].hits;
			tmpdists[i].ulrd = dists[i].ulrd;
		}

		int changed;
again:
		changed = 0;
		for (int i = 0; i <mypos-1; i++) {
			if (tmpdists[i].dist > tmpdists[i+1].dist) {
				int tmpD = tmpdists[i].dist;
				int tmpI = tmpdists[i].itsi;
				int tmpH = tmpdists[i].hits;
				int tmpU = tmpdists[i].ulrd;
				tmpdists[i].dist = tmpdists[i+1].dist;
				tmpdists[i].itsi = tmpdists[i+1].itsi;
				tmpdists[i].hits = tmpdists[i+1].hits;
				tmpdists[i].ulrd = tmpdists[i+1].ulrd;
				tmpdists[i+1].dist = tmpD;
				tmpdists[i+1].itsi = tmpI;
				tmpdists[i+1].hits = tmpH;
				tmpdists[i+1].ulrd = tmpU;
				changed = 1;
				}
			if (changed == 1) {
				goto again;
			}
		}
		
		struct dists_s ntmpdists[DSZ];
		int mypos3 = 0;
		assert(mypos != 0);
		if (mypos > 1) {
			assert(tmpdists[0].dist <= tmpdists[1].dist);
		}
		if (mypos == 1 || (tmpdists[0].dist != tmpdists[1].dist)) {ntmpdists[0] = tmpdists[0]; mypos3 = 1;} else {
			ntmpdists[0] = tmpdists[0]; mypos3 = 1;
			for (int i = 1; i < mypos; i++) {
				if (tmpdists[0].dist == tmpdists[i].dist) {
					ntmpdists[mypos3++] = tmpdists[i];
				}
			}
		}
			
again5:
		changed = 0;
		for (int i = 0; i <mypos3-1; i++) {
			if (ntmpdists[i].ulrd > ntmpdists[i+1].ulrd) {
				int tmpD = ntmpdists[i].dist;
				int tmpI = ntmpdists[i].itsi;
				int tmpH = ntmpdists[i].hits;
				int tmpU = ntmpdists[i].ulrd;
				ntmpdists[i].dist = ntmpdists[i+1].dist;
				ntmpdists[i].itsi = ntmpdists[i+1].itsi;
				ntmpdists[i].hits = ntmpdists[i+1].hits;
				ntmpdists[i].ulrd = ntmpdists[i+1].ulrd;
				ntmpdists[i+1].dist = tmpD;
				ntmpdists[i+1].itsi = tmpI;
				ntmpdists[i+1].hits = tmpH;
				ntmpdists[i+1].ulrd = tmpU;

				changed = 1;
			}
			if (changed == 1) {
				goto again5;
			}
		}
		for (int i = 0; i < mypos3; i++) {
			//printf("(po:%d) D:%d I:%d H:%d U:%d\n", po, ntmpdists[i].dist, ntmpdists[i].itsi, ntmpdists[i].hits, ntmpdists[i].ulrd);
		}

auto int getquickDist(int min, int po);
int getquickDist(int mi, int po) {
	for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
	already[point[po].y][point[po].x] = 0;
	//getMinDist(point[po].x, point[po].y, 0, po, dists[mi].itsi, point[dists[mi].itsi].x, point[dists[mi].itsi].y);
	getMinDist(point[po].x, point[po].y, 0, po, mi, point[mi].x, point[mi].y);
	// = minPath;
	//printf("minPath is %d\n", minPath); getchar();
	if (minPath == 1) {return 0;} else {
		return minPath;
	}
}

int qdist = -1;
if (move == 1 && ntmpdists[0].dist != 0) {
				move = 2;
				moved = 0;
				if (ntmpdists[0].ulrd == 0) {
					moved = 1;
					point[po].y--; 
	if (round123 == 16) {
					printf("po(%d) moved up...\n", po);
	}
					//printf("y--dist: %d\n", ntmpdists[0].dist);
					ntmpdists[0].dist = getquickDist(ntmpdists[0].itsi, po);
					//printf("y--dist: %d\n", ntmpdists[0].dist);
			//printf("**(po:%d) D:%d I:%d H:%d U:%d\n", po, ntmpdists[0].dist, ntmpdists[0].itsi, ntmpdists[0].hits, ntmpdists[0].ulrd);
					qdist = ntmpdists[0].dist;
				} else if (ntmpdists[0].ulrd == 1) {
					moved = 1;
					point[po].x--;
					ntmpdists[0].dist = getquickDist(ntmpdists[0].itsi, po);
					qdist = ntmpdists[0].dist;
				} else if (ntmpdists[0].ulrd == 2) {
					moved = 1;
					if (round123 == 10) {printf("here1\n");}
					point[po].x++;
					//printf("x++dist: %d\n", dists[ntmpdists[0].itsi].dist);
					//printf("distbef(%d): ntmpdists[0].itsi: %d should be ??\n",  ntmpdists[0].dist, ntmpdists[0].itsi);
					ntmpdists[0].dist = getquickDist(ntmpdists[0].itsi, po);
					//printf("distaft(%d): ntmpdists[0].itsi: %d should be ??\n",  ntmpdists[0].dist, ntmpdists[0].itsi);
					//printf("x++dist: %d\n", dists[ntmpdists[0].itsi].dist);
					qdist = ntmpdists[0].dist;
				} else if (ntmpdists[0].ulrd == 3) {
					moved = 1;
					point[po].y++;
					//printf("y++dist: %d\n", dists[ntmpdists[0].itsi].dist);
					ntmpdists[0].dist = getquickDist(ntmpdists[0].itsi, po);
					//printf("y++dist: %d\n", dists[ntmpdists[0].itsi].dist);
					
					qdist = ntmpdists[0].dist;
				}
		for (int i = 0; i < mypos; i++) {
			if (ntmpdists[0].itsi == dists[i].itsi) {
				dists[i].dist = qdist; break;
			}
		}
			
		if (qdist != 0) {return 0;}
}
		
		//printf("qdist:%d moved:%d once:%d Mypos:%d\n", qdist, moved, once, mypos); getchar();
		
		if (qdist == 0) {if (round123 == 16) {printf("should go in\n");}}
		if ((qdist == 0) && moved == 1 && once == 1 && mypos > 0) {
			once++;
			//printf("---- just moved... po:%d moved is %d \n", po, moved); 
			myPP = 0;
			mypos = 0;
			if (round123 == 16) {
				printf("(po:%d)mypos before calcdist...%d goto restartNEXT\n",
					po, mypos);
			}
			move = 0;
			moved = 0;
			goto restartNext;
			mypos = myPP;
			//printf("**my pos after calcdist:...%d\n", mypos); 

again98:
			for (int i = 0; i < mypos; i++) {
				if (dists[i].dist == -1 || dists[i].dist == 9999) {
					for (int j = i; j < mypos; j++) {
						dists[j] = dists[j+1];
					}
					mypos--;
					goto again98;
				}
			}
		}

		mypos = myPP;
		int pos = 0;
		for (int i = 0; i < mypos; i++) {
			if (dists[i].dist == 0) {
				tmpdists[pos].itsi = dists[i].itsi;
				tmpdists[pos].dist = dists[i].dist;
				tmpdists[pos].hits = dists[i].hits;
				tmpdists[pos].ulrd = dists[i].ulrd;
				pos++;
			}
		}
		///printf(" after === just moved...after pos is %d\n", pos); 
			
		if (pos > 0 && tmpdists[0].dist == 0) {
again2:
			changed = 0;
			for (int i = 0; i < pos-1; i++) {
				//printf("hits %d V %d\n", tmpdists[i].hits, tmpdists[i+1].hits);
				if (tmpdists[i].hits > tmpdists[i+1].hits) {
					int tmpD = tmpdists[i].dist;
					int tmpI = tmpdists[i].itsi;
					int tmpH = tmpdists[i].hits;
					int tmpU = tmpdists[i].ulrd;
					tmpdists[i].dist = tmpdists[i+1].dist;
					tmpdists[i].itsi = tmpdists[i+1].itsi;
					tmpdists[i].hits = tmpdists[i+1].hits;
					tmpdists[i].ulrd = tmpdists[i+1].ulrd;
					tmpdists[i+1].dist = tmpD;
					tmpdists[i+1].itsi = tmpI;
					tmpdists[i+1].hits = tmpH;
					tmpdists[i+1].ulrd = tmpU;
					changed = 1;
				}
				if (changed == 1) {
					goto again2;
				}
			}
		} else {return 0;}
		
		auto void attack(int mi);
		struct dists_s newtmpdists[4];
		int mynewpos;
		if (pos > 3 && tmpdists[0].hits == tmpdists[1].hits && tmpdists[0].hits == tmpdists[2].hits 
			&& tmpdists[0].hits == tmpdists[3].hits ) {
			newtmpdists[0].dist = tmpdists[0].dist; newtmpdists[0].itsi = tmpdists[0].itsi;
			newtmpdists[0].hits = tmpdists[0].hits; newtmpdists[0].ulrd = tmpdists[0].ulrd;

			newtmpdists[1].dist = tmpdists[1].dist; newtmpdists[1].itsi = tmpdists[1].itsi;
			newtmpdists[1].hits = tmpdists[1].hits; newtmpdists[1].ulrd = tmpdists[1].ulrd;

			newtmpdists[2].dist = tmpdists[2].dist; newtmpdists[2].itsi = tmpdists[2].itsi;
			newtmpdists[2].hits = tmpdists[2].hits; newtmpdists[2].ulrd = tmpdists[2].ulrd;

			newtmpdists[3].dist = tmpdists[3].dist; newtmpdists[3].itsi = tmpdists[3].itsi;
			newtmpdists[3].hits = tmpdists[3].hits; newtmpdists[3].ulrd = tmpdists[3].ulrd;
			mynewpos = 4;
		} else if (pos > 2 && tmpdists[0].hits == tmpdists[1].hits && tmpdists[0].hits == tmpdists[2].hits) {
			newtmpdists[0].dist = tmpdists[0].dist; newtmpdists[0].itsi = tmpdists[0].itsi;
			newtmpdists[0].hits = tmpdists[0].hits; newtmpdists[0].ulrd = tmpdists[0].ulrd;

			newtmpdists[1].dist = tmpdists[1].dist; newtmpdists[1].itsi = tmpdists[1].itsi;
			newtmpdists[1].hits = tmpdists[1].hits; newtmpdists[1].ulrd = tmpdists[1].ulrd;

			newtmpdists[2].dist = tmpdists[2].dist; newtmpdists[2].itsi = tmpdists[2].itsi;
			newtmpdists[2].hits = tmpdists[2].hits; newtmpdists[2].ulrd = tmpdists[2].ulrd;

			mynewpos = 3;
		} else if (pos > 1 && tmpdists[0].hits == tmpdists[1].hits ) {
			///printf("two equal...\n");
			newtmpdists[0].dist = tmpdists[0].dist; newtmpdists[0].itsi = tmpdists[0].itsi;
			newtmpdists[0].hits = tmpdists[0].hits; newtmpdists[0].ulrd = tmpdists[0].ulrd;

			newtmpdists[1].dist = tmpdists[1].dist; newtmpdists[1].itsi = tmpdists[1].itsi;
			newtmpdists[1].hits = tmpdists[1].hits; newtmpdists[1].ulrd = tmpdists[1].ulrd;
			mynewpos = 2;
		} else if (tmpdists[0].dist == 0) {
			attack(tmpdists[0].itsi);
			return 0;
		}
		void attack(int mi) {
			if (point[po].remove == 1) {printf("ERR attack po:%d\n", po);getchar();}
			if (point[mi].remove == 1) {printf("ERR attack mi: %d\n", po);getchar();}
			if (point[po].shotAL != 1 && point[po].GE == 1 && point[mi].remove != 1 && point[po].remove != 1) {
				point[po].shotAL = 1;
				point[mi].hitpoints -= 3; if (point[mi].hitpoints <= 0) {point[mi].remove = 1; } 
				return;
			} else if (point[po].shotAL != 1 && point[po].GE == 2 && point[mi].remove != 1 && point[po].remove != 1) {
				point[po].shotAL = 1;
				point[mi].hitpoints -= ELVES_HIT; if (point[mi].hitpoints <= 0) {point[mi].remove = 1; } 
				return;
			}
		}

		int changed1;
again101:
		changed1 = 0;
		for (int i = 0; i < mynewpos-1; i++) {
			int mii = newtmpdists[i].itsi;
			int miiP1 = newtmpdists[i+1].itsi;
			if (point[mii].y > point[miiP1].y) {
				int tmpD = newtmpdists[i].dist;
				int tmpI = newtmpdists[i].itsi;
				int tmpH = newtmpdists[i].hits;
				int tmpU = newtmpdists[i].ulrd;
				newtmpdists[i].dist = newtmpdists[i+1].dist;
				newtmpdists[i].itsi = newtmpdists[i+1].itsi;
				newtmpdists[i].hits = newtmpdists[i+1].hits;
				newtmpdists[i].ulrd = newtmpdists[i+1].ulrd;
				newtmpdists[i+1].dist = tmpD;
				newtmpdists[i+1].itsi = tmpI;
				newtmpdists[i+1].hits = tmpH;
				newtmpdists[i+1].ulrd = tmpU;
				changed1 = 1;
			}
			if (changed1 == 1) {
				goto again101;
			}
		}

again102:
		int changed2 = 0;
		for (int i = 0; i < mynewpos-1; i++) {
			int mii = newtmpdists[i].itsi;
			int miiP1 = newtmpdists[i].itsi;
			if (point[mii].y == point[miiP1].y) {
				if (point[mii].x > point[miiP1].x) {
					int tmpD = newtmpdists[i].dist;
					int tmpI = newtmpdists[i].itsi;
					int tmpH = newtmpdists[i].hits;
					int tmpU = newtmpdists[i].ulrd;
					newtmpdists[i].dist = newtmpdists[i+1].dist;
					newtmpdists[i].itsi = newtmpdists[i+1].itsi;
					newtmpdists[i].hits = newtmpdists[i+1].hits;
					newtmpdists[i].ulrd = newtmpdists[i+1].ulrd;
					newtmpdists[i+1].dist = tmpD;
					newtmpdists[i+1].itsi = tmpI;
					newtmpdists[i+1].hits = tmpH;
					newtmpdists[i+1].ulrd = tmpU;
					changed2 = 1;
				}
			}
			if (changed2 == 1) {
				goto again102;
			}
		}

		if (round123 == 16) {
			printf("attacking %d\n", newtmpdists[0].itsi);
			for (int i = 0; i < mynewpos; i++) {
				int mi = newtmpdists[i].itsi;
				printf("--%d %d,%d\n", mi, point[mi].x, point[mi].y);
			}
					
				
		}
		attack(newtmpdists[0].itsi);
		return 0;
				
/*
		for (int i = 0; i < mynewpos; i++) {
			int mii = newtmpdists[i].itsi;
			if (point[po].GE == point[mii].GE) {continue;}
			if (round123 == 16) {
				printf("point[po].x point[%d].y %d, %d\n",po,  point[po].x, point[po].y);
				printf("point[%d].x point[%d].y %d, %d\n", mii, mii,  point[mii].x, point[mii].y);
			}
			if (point[po].y -1 == point[mii].y && point[po].x == point[mii].x) {
				if (round123 == 16) {printf("should be here\n"); getchar();}
				attack(mii);
				return 0;
			} else if (point[po].y == point[mii].y && point[po].x-1 == point[mii].x) {
				if (round123 == 16) {
printf("NEWTMPDISTS\n");
for (int i = 0; i < pos; i++) {
			printf("D:%d H:%d ULRD:%d I:%d\n", newtmpdists[i].dist, newtmpdists[i].hits, newtmpdists[i].ulrd, newtmpdists[i].itsi);
}
printf("DISTS:\n");
for (int i = 0; i < mypos; i++) {
		if (dists[i].dist == 0) {
		printf("D:%d H:%d ULRD:%d I:%d\n", dists[i].dist, dists[i].hits, dists[i].ulrd, dists[i].itsi);
		}
}


printf("pos: %d mynewpos:(%d)am here i:%d\n", pos, mynewpos, i); getchar();}
				attack(mii);
				return 0;
			} else if (point[po].y  == point[mii].y && point[po].x+1 == point[mii].x) {
				attack(mii);
				return 0;
			} else if (point[po].y+1  == point[mii].y && point[po].x == point[mii].x) {
				attack(mii);
				return 0;
			}
		}
*/
		printf("should not be here\n"); exit(0);
					
	}
	return 0;
}

void orderPointsTOPLEFT() {
	int changed;
next:
	changed = 0;
	for (int i = 0; i < pointPos-1; i++) {
		//if (point[i].remove == 1) {continue;}

		int j = i+1;
		{
			//if (point[j].remove == 1) {continue;}
			//printf("%d V %d\n", point[i].y, point[j].y);
			if (point[i].y > point[j].y) {
				//printf("swap: %d V %d\n", point[i].y, point[j].y); printf("point[i].y (%d) > point[j].y (%d)\n", point[i].y, point[j].y);
				struct point_s ptmp;
				ptmp = point[i];
				point[i] = point[j];
				point[j] = ptmp;
				changed = 1;
			} else if (point[i].y == point[j].y) {
				if (point[i].x > point[j].x) {
					struct point_s ptmp;
					ptmp = point[i];
					point[i] = point[j];
					point[j] = ptmp;
					changed = 1;
				}
			}
			if  (changed == 1) {
				goto next;
			}
		}
	}
}
