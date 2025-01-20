#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#undef _DEBUG_
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;
#define SZ 50
int leny = 0;
int lenx = 0;
char grid[SZ][SZ];
struct point_s {
	int x;
	int y;
	int GE;
	int hitpoints;
	int remove;
	int which;
};
#define getchar()
struct point_s point[1000];
int pointPos = 0;
void orderPointsTOPLEFT();
void next(int po);
void printit();
void getMinDist(int fx, int fy, int path, int po, int fm, int tox, int toy);
int already[100][100];
void attack(int po);
int minPath = 9999;
int moved;
int main(int argc, char **argv)
{
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
				grid[y][x] = '.';
				point[pointPos].x = x;
				point[pointPos].y = y;
				point[pointPos].GE = 1;
				point[pointPos].hitpoints = 200;
				point[pointPos].remove = 0;
				pointPos++;
			} else if (grid[y][x] == 'E') {
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

	printit(); getchar();
	int gs, es;
	int round = 0;
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
	}
		
	moved = 0;
	orderPointsTOPLEFT();

	round++;
	for (int i = 0; i < pointPos; i++) {
		next(i);
	}

	orderPointsTOPLEFT();

	printf("\nROUND (AFTER) is %d vvvvvvv\n", round); printit();
	for (int i = 0; i < pointPos; i++) {
		if (point[i].remove == 1) {continue;}
		if (point[i].GE == 1) {
			printf("G: %d (%d,%d)\n", point[i].hitpoints, point[i].x, point[i].y);
		} else {
			printf("E: %d (%d,%d)\n", point[i].hitpoints, point[i].x, point[i].y);
		}
	}  getchar();
	gs = 0; es = 0;
	for (int i = 0; i < pointPos; i++) {
		if (point[i].remove == 1) {continue;}
		if (point[i].GE == 1) {
			gs += point[i].hitpoints;
			//printf("gs now %d\n", gs);
		} else if (point[i].GE == 2) {
			es += point[i].hitpoints;
			//printf("es now %d\n", es);
		}
	}		
	
	if (gs==0 || es == 0) {} else {goto nextmove;}
	printf("tots: gs is %d es is %d\n", gs, es);
	int gsA, esA;

	gsA = gs *round;
	esA = es *round;
	printf("round: gs is %d es is %d\n", gsA, esA);

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
	
void next(int po) {

	struct dists_s {
		int dist;
		int itsi;
		int hits;
		int ulrd;
	};
	struct dists_s dists[4];

	for (int i = 0; i < 4; i++) {
		dists[i].dist = 9999;
		dists[i].hits = -10;
		dists[i].itsi = -1;
		dists[i].ulrd = 0;
	}
	//printf("po:%d now is type:(%d) (%d,%d)\n", po, point[po].GE, point[po].x, point[po].y);
	for (int GE = 1; GE <= 2; GE++) {
		if (point[po].GE != GE) {continue;}
		if (point[po].remove == 1) {continue;}
		if (point[po].GE == GE) { //TOP
			for (int i = 0; i < pointPos; i++) {
				if (po == i) {continue;}
				if (point[i].remove == 1) {continue;}
				if (point[i].GE == GE) {continue;}
	
				int man[4] = {0};
				if (grid[point[i].y-1][point[i].x] != '#') {
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[i].y-1][point[i].x] = 0;
					already[point[i].y][point[i].x] = 0;
					minPath = 9999;
					getMinDist(point[i].x, point[i].y-1, 0, i, po, point[po].x, point[po].y);
					man[0] = minPath;

					if (man[0] < dists[0].dist) {
					printf("minPath 0 is %d\n", minPath); getchar();

					printf("po (%d) AL: %d ", po, already[point[po].y-1][point[po].x]);
					printf("%d ", already[point[po].y][point[po].x+1]);
					printf("%d ", already[point[po].y][point[po].x-1]);
					printf("%d \n ", already[point[po].y+1][point[po].x]);
					if (already[point[po].y-1][point[po].x] -minPath == 0) {
						dists[0].ulrd = 0;
					} else if (already[point[po].y][point[po].x-1]-minPath == 0) {
						dists[0].ulrd = 1;
					} else if (already[point[po].y][point[po].x+1]-minPath == 0) {
						dists[0].ulrd = 2;
					} else if (already[point[po].y+1][point[po].x]-minPath == 0) {
						dists[0].ulrd = 3;
					}
					dists[0].dist = man[0]; dists[0].itsi = i;  dists[0].hits = point[i].hitpoints;}
				}
				if (grid[point[i].y][point[i].x-1] != '#') {
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[i].y][point[i].x-1] = 0;
					already[point[i].y][point[i].x] = 0;
					minPath = 9999;
					getMinDist(point[i].x-1, point[i].y, 0, i, po, point[po].x, point[po].y);
					printf("minPath 1 is %d\n", minPath); getchar();
					man[1] = minPath;
					if (man[1] < dists[1].dist) {
					printf("minPath 1 is %d\n", minPath); getchar();
					printf("po (%d) AL: %d ", po, already[point[po].y-1][point[po].x]);
					printf("%d ", already[point[po].y][point[po].x+1]);
					printf("%d ", already[point[po].y][point[po].x-1]);
					printf("%d \n ", already[point[po].y+1][point[po].x]);
					if (already[point[po].y-1][point[po].x] -minPath == 0) {
						dists[1].ulrd = 0;
					} else if (already[point[po].y][point[po].x-1] -minPath == 0) {
						dists[1].ulrd = 1;
					} else if (already[point[po].y][point[po].x+1] -minPath == 0) {
						dists[1].ulrd = 2;
					} else if (already[point[po].y+1][point[po].x] -minPath == 0) {
						dists[1].ulrd = 3;
					}
					dists[1].dist = man[1]; dists[1].itsi = i; dists[1].hits = point[i].hitpoints;}
				}
				if (grid[point[i].y][point[i].x+1] != '#') {
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[i].y][point[i].x+1] = 0;
					already[point[i].y][point[i].x] = 0;
					minPath = 9999;
					getMinDist(point[i].x+1, point[i].y, 0, i, po, point[po].x, point[po].y);
					printf("minPath 2 is %d\n", minPath); getchar();
					printf("po (%d) AL: %d ", po, already[point[po].y-1][point[po].x]);
					printf("%d ", already[point[po].y][point[po].x+1]);
					printf("%d ", already[point[po].y][point[po].x-1]);
					printf("%d \n ", already[point[po].y+1][point[po].x]);
					man[2] = minPath;
					if (man[2] < dists[2].dist) {
/*
					int al[4];
					al[0] = already[point[po].y-1][point[po].x];
					al[1] = already[point[po].y][point[po].x-1];
					al[2] = already[point[po].y][point[po].x+1];
					al[3] = already[point[po].y+1][point[po].x];
					sort(al, al+4);
*/
					if (already[point[po].y-1][point[po].x] -minPath == 0) {
						dists[2].ulrd = 0;
					} else if (already[point[po].y][point[po].x-1] -minPath == 0) {
						dists[2].ulrd = 1;
					} else if (already[point[po].y][point[po].x+1] -minPath == 0) {
						dists[0].ulrd = 2;
					} else if (already[point[po].y+1][point[po].x] -minPath == 0) {
						dists[0].ulrd = 3;
					}
					dists[2].dist = man[2]; dists[2].itsi = i; dists[2].hits = point[i].hitpoints;}
				}
				if (grid[point[i].y+1][point[i].x] != '#') {
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[i].y+1][point[i].x] = 0;
					already[point[i].y][point[i].x] = 0;
					minPath = 9999;
					getMinDist(point[i].x, point[i].y+1, 0, i, po, point[po].x, point[po].y);
					printf("minPath 3 is %d\n", minPath); getchar();
					printf("po (%d) AL: %d ", po, already[point[po].y-1][point[po].x]);
					printf("%d ", already[point[po].y][point[po].x+1]);
					printf("%d ", already[point[po].y][point[po].x-1]);
					printf("%d \n ", already[point[po].y+1][point[po].x]);
					man[3] = minPath;
					if (man[3] < dists[3].dist) {

					if (already[point[po].y-1][point[po].x]  -minPath == 0) {
						dists[3].ulrd = 0;
					} else if (already[point[po].y][point[po].x-1]  -minPath == 0) {
						dists[3].ulrd = 1;
					} else if (already[point[po].y][point[po].x+1] -minPath == 0) {
						dists[3].ulrd = 2;
					} else if (already[point[po].y+1][point[po].x]  -minPath == 0) {
						dists[3].ulrd = 3;
					}
					dists[3].dist = man[3]; dists[3].itsi = i; dists[3].hits = point[i].hitpoints;}
				}
				
			}
		}
		
		struct dists_s tmpdists[4];
		for (int i = 0; i < 4; i++) {
			tmpdists[i].itsi = dists[i].itsi;
			tmpdists[i].dist = dists[i].dist;
			tmpdists[i].hits = dists[i].hits;
		}

		int changed;
again:
		changed = 0;
		for (int i = 0; i <4-1; i++) {
			if (tmpdists[i].dist > tmpdists[i+1].dist) {
				int tmpD = tmpdists[i].dist;
				int tmpI = tmpdists[i].itsi;
				tmpdists[i].dist = tmpdists[i+1].dist;
				tmpdists[i].itsi = tmpdists[i+1].itsi;
				tmpdists[i+1].dist = tmpD;
				tmpdists[i+1].itsi = tmpI;
				changed = 1;
			}
			if (changed == 1) {
				goto again;
			}
		}

		for (int i = 0; i < 4; i++) { //movement
			if (tmpdists[0].dist == 9999) {break;}
			if (tmpdists[0].dist == 0) {break;} 

			if (dists[i].dist == tmpdists[0].dist) {
				printf("%d ulrd is \n", dists[i].ulrd); getchar();
				moved = 1;
				if (dists[i].ulrd == 0) {
					point[po].y--; 
					dists[i].dist--;
					//if (point[po].remove == 0) {dists[i].dist--;}
/*
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[po].y][point[po].x] = 0;
					already[point[po].y+1][point[po].x] = 0;
					getMinDist(point[po].x, point[po].y, 0, po, dists[i].itsi, point[dists[i].itsi].x, point[dists[i].itsi].y);
					printf("dists[i].dist now %d was %d\n", dists[i].dist, minPath);
					dists[i].dist = minPath;
*/
				} else if (dists[i].ulrd == 1) {
					point[po].x--;
					dists[i].dist--;
					//if (point[po].remove == 0) {dists[i].dist--;}
/*
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[po].y][point[po].x] = 0;
					already[point[po].y][point[po].x+1] = 0;
					getMinDist(point[po].x, point[po].y, 0, po, dists[i].itsi, point[dists[i].itsi].x, point[dists[i].itsi].y);
					printf("dists[i].dist now %d was %d\n", dists[i].dist, minPath);
					dists[i].dist = minPath;
*/
				} else if (dists[i].ulrd == 2) {
					point[po].x++;
					//if (point[po].remove == 0) {dists[i].dist--;}
					dists[i].dist--;
/*
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[po].y][point[po].x] = 0;
					already[point[po].y][point[po].x-1] = 0;
					getMinDist(point[po].x, point[po].y, 0, po, dists[i].itsi, point[dists[i].itsi].x, point[dists[i].itsi].y);
					printf("dists[i].dist now %d was %d\n", dists[i].dist, minPath);
					dists[i].dist = minPath;
*/
				} else if (dists[i].ulrd == 3) {
					point[po].y++;
					//if (point[po].remove == 0) {dists[i].dist--;}
					dists[i].dist--;
/*
					for (int y = 0; y<100; y++) { for (int x = 0; x < 100; x++) { already[y][x] = -1; } }
					already[point[po].y][point[po].x] = 0;
					already[point[po].y-1][point[po].x] = 0;
					getMinDist(point[po].x, point[po].y, 0, po, dists[i].itsi, point[dists[i].itsi].x, point[dists[i].itsi].y);
					printf("dists[i].dist now %d was %d\n", dists[i].dist, minPath);
					dists[i].dist = minPath;
*/
				}
				break;
			}
		}
		
		int pos = 0;
		for (int i = 0; i < 4; i++) {
			if (dists[i].dist == 0) {
				tmpdists[pos].itsi = dists[i].itsi;
				tmpdists[pos].dist = dists[i].dist;
				tmpdists[pos].hits = dists[i].hits;
				pos++;
			}
		}
		//printf("for ps %d\n", po);
		for (int i = 0; i < 4; i++) {
			//printf("dists[i].hits is %d\n", dists[i].hits);
			//printf("dists[i].itsi is %d\n", dists[i].itsi);
			///printf("dists[i].dist is %d\n", dists[i].dist);
		}
			
		for (int i = 0; i < pos; i++) {
			//printf("tmpdists[i].hits is %d\n", tmpdists[i].hits);
		}

		if (tmpdists[0].dist == 0) {
again2:
			changed = 0;
			for (int i = 0; i < pos-1; i++) {
				printf("hits %d V %d\n", tmpdists[i].hits, tmpdists[i+1].hits);
				if (tmpdists[i].hits > tmpdists[i+1].hits) {
					int tmpD = tmpdists[i].dist;
					int tmpI = tmpdists[i].itsi;
					int tmpH = tmpdists[i].hits;
					tmpdists[i].dist = tmpdists[i+1].dist;
					tmpdists[i].itsi = tmpdists[i+1].itsi;
					tmpdists[i].hits = tmpdists[i+1].hits;
					tmpdists[i+1].dist = tmpD;
					tmpdists[i+1].itsi = tmpI;
					tmpdists[i+1].itsi = tmpH;
					changed = 1;
				}
				if (changed == 1) {
					goto again2;
				}
			}

			//printf("%d,%d attacks %d,%d\n", point[po].x, point[po].y, point[tmpdists[0].itsi].x, point[tmpdists[0].itsi].y);
			if (point[tmpdists[0].itsi].remove != 1 && point[po].remove != 1) {
				point[tmpdists[0].itsi].hitpoints -= 3; if (point[tmpdists[0].itsi].hitpoints <= 0) {point[tmpdists[0].itsi].remove = 1; } 
			}
		}
		
	}
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
