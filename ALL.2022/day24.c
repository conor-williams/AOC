#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <iostream>

using namespace std;

map <tuple<int, int, int>, int> mpALL;
map <tuple<int, int, int>, int> mp;
map <tuple<int, int, int>, int> mpTmp;
map <tuple<int, int, int>, int> mpTmp2;

map <tuple<int, int, int, int, int>, int> mpSE;

int count123 = 0;
int minPathTot = 0;
//Been there at the same depth...
FILE *a;
#define LINE 1000
#define getchar()
int minPath = 99999;
int minminPath = 99999;
int dep = 90;
int hide = 0;
int fd;
//void sigfunc(int a) { if (count123 % 2 == 0) {dup2(fd,1);}if (hide==1) {dup2(fd, 1);} printf("[[ %s %d]]\n", "signal hand..\n", minPath); if (hide==1) {fd=dup(1); close(1);} }
void sigfunc(int a) { dup2(fd,1); printf("in sig\n"); /*fd=dup(1); close(1);*/ count123++; if (count123 % 2 == 0) {dup2(fd,1);} else if (count123 % 2 == 1) {fd=dup(1); close(1);} }

struct al_s {
	int depth;
	int path;
};
struct al_s already[120][120];

#define SX 105
char grid[SX][SX];
int gridNum[100][SX][SX];
int gridNumInter[SX][SX];
//int already[SX][SX] = {0};
int leny = 0;
int lenx = 0;

void printit(int depth);
void makeMovesAll(int xyz);
void next(int x, int y, int path, int ex, int ey, int depth, int vsx, int vsy);
void dikjstra(int conSX, int conSY, int conEX, int conEY, int mmPP);

int main(int argc, char **argv)
{
	for (int y = 0; y < SX; y++) {
		for (int x = 0; x < SX; x++) {
			already[y][x].depth = -1;
			already[y][x].path = 0;
		}
	}
	if (argc == 3) {dep = atoi(argv[2]); printf("using depth %d\n", dep);}

	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2022 Day 24 Part2 \n"); fflush(stdout);
	if (hide == 1) {
		fd = dup(1); close(1);
	}
	char line1[LINE];

	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);

	memset(gridNum[0], 0, sizeof(gridNum[0]));
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			switch(grid[y][x]) {
				case '^':
					gridNum[0][y][x] = 1;
					break;
				case '>':
					gridNum[0][y][x] = 2;
					break;
				case 'v':
					gridNum[0][y][x] = 4;
					break;
				case '<':
					gridNum[0][y][x] = 8;
					break;
				case '.':
					gridNum[0][y][x] = 0;
					break;
			}
		}
	}
	////////////////////////////////////////////////////

	printit(0); //getchar();
	printf("---------------\n");
	for (int i = 1; i < dep; i++) {
		memset(gridNum[i], 0, sizeof(gridNum[i]));
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (x == 0) {
					gridNum[i][y][x] = -1;
				} else if (x == lenx -1) {
					gridNum[i][y][x] = -1;
				} else if (y == 0) {
					gridNum[i][y][x] = -1;
				} else if (y == leny-1) {
					gridNum[i][y][x] = -1;
				}
				gridNum[i][0][1] = 0;
				gridNum[i][leny-1][lenx-2] = 0;
			}
		}

		makeMovesAll(i);
	}

	minPathTot = 0;
	dikjstra(1, 0, lenx-2, leny-1, 0); 

/*
	if (strcmp(argv[1], "ext2.txt") == 0) {assert(minPath == 18);}
	dikjstra(lenx-2, leny-1, 1, 0, minPath);

	if (strcmp(argv[1], "ext2.txt") == 0) {if (minPath != 23) {printf("ADJ ADJ %d\n", minPath);} minPath = 23; minPathTot = 18+23;}
	dikjstra(1, 0, lenx-2, leny-1, minPath);

	if (hide == 1) {dup2(fd, 1);}
*/
	printf("**ans %d\n", minPathTot);

}
void dikjstra(int conSX, int conSY, int conEX, int conEY, int mmpp)
{ 
	minminPath = 99999;
	printf("in dikj %d %d %d %d %d\n", conSX, conSY, conEX, conEY, mmpp); fflush(stdout);
	if (mmpp != 0) {
		for (int i = mmpp; i < dep; i++) {
			for (int y = 0; y < leny; y++) {
				for (int x = 0; x < lenx; x++) {
					gridNum[i-mmpp][y][x] = gridNum[i][y][x];
				}
			}
		}
		dep -= mmpp;
		printf("after mmpp shift\n");
	} else {
		printf("no mmpp shift\n");
	}

	//int curx = conSX; int cury = conSY;

	mpALL.clear(); mp.clear(); mpTmp2.clear(); mpTmp.clear(); minPath = 99999; int path = 0;
	mp[{conSX, conSY, path}] = 1;
again:
	if ((int)mp.size() != 0) {mpTmp2 = mp;} mpTmp = mp; mp.clear();
	if (mpTmp.size() == 0 && mpTmp2.size() == 0) {goto end;}
	if (mpTmp.size() == 0) {
		for (map<tuple<int, int, int>, int>::iterator it = mpTmp2.begin(); it != mpTmp2.end(); it++) {
			tuple fir = it->first;
			int cx = get<0>(fir); int cy = get<1>(fir); int pa = get<2>(fir); pa++;
			mpTmp[{cx, cy, pa}] = 1;
		}
		mpTmp2.clear();
	}

	for (auto it = mpTmp.begin(); it != mpTmp.end(); it++) {
		tuple fir = it->first;
		int cx = get<0>(fir); int cy = get<1>(fir); int pa = get<2>(fir);
		tuple abcd = make_tuple(cx, cy, pa);
		if (mpALL.find(abcd) != mpALL.end()) {continue;} else {mpALL[abcd] = 1;} 

		for (int ey1 = 0; ey1 < leny; ey1++) {
			for (int ex1 = 1; ex1 < lenx-1; ex1++) {

				if (ey1 == 0 && ex1 != 1) {continue;} else
				if (ey1 == leny-1 && ex1 != lenx -2) {continue;}
				for (int y = 0; y < SX; y++) {
					for (int x = 0; x < SX; x++) {
						already[y][x].depth = -1;
						already[y][x].path = 0;
					}
				}

				minPath = 99999;
				//int found22 = 0; for (int zz2 = pa+1; zz2 < dep; zz2++) { if (gridNum[zz2][ey1][ex1] == 0) { found22 = 1; break; } } if (found22 == 0) {continue;}

				next(cx, cy, pa, ex1, ey1, pa, cx, cy);

				if (minPath != 99999) {
					mp[{ex1, ey1, minPath+1}] = 1;
					//printf("**minPath %d,%d to: %d,%d is %d\n", cx, cy, ex1, ey1, minPath); //getchar();
					if (ex1 == conEX && ey1 == conEY) {
						///minPathTot += minPath;
						if (hide == 1) {dup2(fd,1); } /*printf("yatzee:: minPath: %d\n", minPath);*/ if (hide == 1) {fd=dup(1); close(1);} getchar();/*return;*/ //goto ag4;
						if (minPath < minminPath) {minminPath = minPath;}
					}
				}
			}
		}
	}
	goto again;
end:
	minPath = minminPath;
	minPathTot += minPath;
	printf("leaving dikjstra -- minPath: ( %d )\n", minPath);
}

void next(int x, int y, int path, int ex, int ey, int depth, int vsx, int vsy)
{
	if (depth > dep-3) {return;}
	if (gridNum[depth][y][x] != 0) {return;}
	if (x == ex && y == ey) {
		//printf("**End reached minPath:%d Start: %d,%d (END:%d,%d) depth is %d\n", path, vsx, vsy, ex, ey, depth); getchar();
		if (path < minPath) {minPath = path;}
		return;
	}

	if (path < already[y][x].path || already[y][x].path == 0) {
		already[y][x].path = path;
		already[y][x].depth = depth;

		int found = 0;
		if (y-1 >= 0 && gridNum[depth+1][y-1][x] == 0) {
			found++;
			next(x, y-1, path+1, ex, ey, depth+1, vsx, vsy);
		}
		if (x+1 < lenx && gridNum[depth+1][y][x+1] == 0) {
			found++;
			next(x+1, y, path+1, ex, ey, depth+1, vsx, vsy);
		}
		if (y+1 < leny && gridNum[depth+1][y+1][x] == 0) {
			found++;
			next(x, y+1, path+1, ex, ey, depth+1, vsx, vsy);
		}
		if (x-1 >= 0 && gridNum[depth+1][y][x-1] == 0) {
			found++;
			next(x-1, y, path+1, ex, ey, depth+1, vsx, vsy);
		}

		if (found == 0) { return; }
	}

	return;
}

void makeMovesAll(int gridX) 
{
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (gridNum[gridX-1][y][x] != 0) {
				if (gridNum[gridX-1][y][x] & (1 << 0)) { 
					//printf("setting Inter\n");
					//case '^':
					if (y == 1) {
						gridNumInter[leny-2][x] |= 1 << 0;
					} else {
						gridNumInter[y-1][x] |= 1 << 0;
					}
					//gridNumInter[y][x] ^= 1 << 0;
				}

				if (gridNum[gridX-1][y][x] & (1 << 1)) { 
					//case '>':
					//printf("setting Inter >\n");
					//printf("here6 > x,y: %d,%d\n", x, y);
					if (x == lenx-2) {
						//printf("here6...\n");
						gridNumInter[y][1] |= 1 << 1;
					} else {
						gridNumInter[y][x+1] |= 1 << 1;
						//printf("here6 %d\n", gridNumInter[y][x+1]);
					}
					//gridNumInter[y][x] ^= 1 << 1;
				}

				if (gridNum[gridX-1][y][x] & (1 << 2)) { 
					//printf("setting Inter v \n");
					//case 'v':
					//printf("here2 x,y %d,%d\n", x, y);
					if (y == leny-2) {
						gridNumInter[1][x] |= 1 << 2;
						//printf("here7 %d\n", gridNumInter[1][x]);
					} else {
						gridNumInter[y+1][x] |= 1 << 2;
						//printf("here8: %d\n", gridNumInter[y+1][x]);
					}
					//gridNumInter[y][x] ^= 1 << 2;
				}

				if (gridNum[gridX-1][y][x] & (1 << 3)) { 
					///printf("setting Inter\n");
					//case '<':
					if (x == 1) {
						gridNumInter[y][lenx-2] |= 1 << 3;
					} else {
						gridNumInter[y][x-1] |= 1 << 3;
					}
					//gridNumInter[y][x] ^= 1 << 3;
				}
			} else {
			}
		}
	}

	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			gridNum[gridX][y][x] = gridNumInter[y][x];
		}
	}

	//printit(gridX);
	memset(gridNumInter, 0, sizeof(gridNumInter));
}

void printit(int gridX)
{
	//printf("in printit %d %d\n", lenx, leny);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (y == 0 || y == leny-1 || x == 0 || x == lenx-1) {
				if (y == 0 && x == 1) {
					printf("S");
				} else if (y == leny-1 && x == lenx-2) {
					printf("E");
				} else {
					printf("#");
				}
			} else if (gridNum[y][x] == 0) {
				printf(".");
			} else {
				if (gridNum[gridX][y][x] < 10) {
					printf("%d", gridNum[gridX][y][x]);
				} else {
					switch(gridNum[gridX][y][x]) {
						case 10:
							printf("a");
							break;
						case 11:
							printf("b");
							break;
						case 12:
							printf("c");
							break;
						case 13:
							printf("d");
							break;
						case 14:
							printf("e");
							break;
						case 15:
							printf("f");
							break;
					}
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}
