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
//Been there at the same depth...
FILE *a;
#define LINE 1000
#define getchar()
int minPath = 99999;
int dep = 240;
int hide = 1;
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
int gridNum[10001][SX][SX];
int gridNumInter[SX][SX];
//int already[SX][SX] = {0};
int leny = 0;
int lenx = 0;

void printit(int depth);
void printit2(int depth, int cx, int cy);
void makeMovesAll(int xyz);
void next(int x, int y, int path, int ex, int ey, int depth);

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

        a = fopen(argv[1], "r"); printf("2021 Day 24 Part1 \n"); fflush(stdout);
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

	printit(0); getchar();
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
		//printit(i);
		//printf(";;;;;;;;;;;;;;\n"); getchar();
	}
		
	int curx = 1; int cury = 0;
	int path = 0;

	mp[{curx, cury, 0}] = 1;
again:
	printf("here again...\n");
	if ((int)mp.size() != 0) {mpTmp2 = mp;} mpTmp = mp; mp.clear();
	if (mpTmp.size() == 0) {
		printf("mpTmp.szie is zero\n");
		printf("mpTmp2.szie is %d\n", (int)mpTmp2.size()); getchar();
		for (map<tuple<int, int, int>, int>::iterator it = mpTmp2.begin(); it != mpTmp2.end(); it++) {
		//for (int zz = 0; zz < (int)mpTmp2.size(); zz++) 
		//for (auto const & [key, val]: mpTmp2) 
			printf("here2...\n"); getchar();
			tuple fir = it->first;
			int cx = get<0>(fir);
			int cy = get<1>(fir);
			int pa = get<2>(fir);
			pa++;
			mpTmp[{cx, cy, pa}] = 1;
		}
		mpTmp2.clear();
		printf("mpTmp.size() now %d (was empty)\n", (int)mpTmp.size());
	}

	if ((int)mpTmp.size() == 0) {printf("mpTmp.size is zero\n");}
	//int vf = 1;
	for (auto it = mpTmp.begin(); it != mpTmp.end(); it++) {
		tuple fir = it->first;
		int cx = get<0>(fir);
		int cy = get<1>(fir);
		int pa = get<2>(fir);
		tuple abcd = make_tuple(cx, cy, pa);
		printf("checking %d %d %d\n", cx, cy, pa);
		if (mpALL.find(abcd) != mpALL.end()) {printf("found\n");continue;} else {printf("not found\n"); mpALL[abcd] = 1;/*mpALL.emplace(abcd, 1);*/} fflush(stdout);
		//mpALL(abcd, 1);
		//if (vf == 1) { mpALL[{cx, cy, pa}] = 1; vf = 0; }
		cout << "IN mpALL: " << endl; fflush(stdout);
		for (auto it88 = mpALL.begin(); it88 != mpALL.end(); it88++) {
			cout << get<0>(it88->first) << " " << get<1>(it88->first) << " " << get<2>(it88->first) << endl;
		}
		cout << "^^^^^^" << endl;

		printf("cx cy pa --- %d %d %d\n", cx, cy, pa);
	        for (int ey1 = 1; ey1 < leny; ey1++) {
			for (int ex1 = 1; ex1 < lenx; ex1++) {
                        	//int path = 0;
                        	for (int y = 0; y < SX; y++) {
                                	for (int x = 0; x < SX; x++) {
                                        	already[y][x].depth = -1;
                    	                	already[y][x].path = 0;
                       		        }
                        	}

	                        minPath = 99999;
				//if (mpSE[{cx, cy, ex1, ey1, pa}] == 1) {continue;}
				int found22 = 0;
				for (int zz2 = pa+1; zz2 < dep; zz2++) {
					if (gridNum[zz2][ey1][ex1] == 0) {
						found22 = 1;
						break;
					}
				}
				if (found22 == 0) {continue;}
				
       		                next(cx, cy, pa, ex1, ey1, pa);
				//if (cx == ex1 && cy == ey1) {continue;}
				///if (cx == ex1 && cy == ey1) {printf("con-pa is %d\n", pa);}
				
	
                        	if (minPath != 99999) {
					//mpSE[{cx, cy, ex1, ey1, minPath}] = 1;
                                	mp[{ex1, ey1, minPath+1}] = 1;
					//mpALL[{ex1, ey1, minPath+1}] = 1;
 	                        	printf("minPath %d,%d to: %d,%d is %d\n", cx, cy, ex1, ey1, minPath); getchar();
					if (ex1 == lenx-2 && ey1 == leny-1) {
						dup2(fd,1); printf("yatzee:: minPath: %d\n", minPath); fd=dup(1); close(1);exit(0);}
				}
                        }
                }
        }
	printf("going again\n");
	getchar();
	goto again;

	

	if (hide == 1) {
		dup2(fd, 1);
	}
        for (int y = 0; y < SX; y++) {
        	for (int x = 0; x < SX; x++) {
			already[y][x].depth = -1;
			already[y][x].path = 0;
		}
	}
	path = 0;
	next(curx, cury, path, lenx-2, leny-1, 0);
	printf("ans: %d\n", minPath);
	//goto again;
}

int ind = 0;
int firstInd[1000] = {0};
void next(int x, int y, int path, int ex, int ey, int depth) 
{
ag:
	if (depth > dep-3) {return;}
	//printf("in next -- depth %d\n", depth);
	if (x == ex && y == ey) {
		//printf("**End reached minPath:%d (END:%d,%d)\n", path, ex, ey); getchar();
		if (path < minPath) {minPath = path;}
		return;
	}

	//printf("%d,%d :%d\n", x, y, gridNum[0][y][x]);
	if (depth != 0) {
		if (x == 1 && y == 0) {/*ok*/} else {
			if (x > 0 && x < lenx-1) {/*ok*/} else {return;}
			if (y > 0 && y < leny-1) {/*ok*/} else {return;}
		}
	}

	if (gridNum[depth][y][x] != 0) { /*printf("returning here?\n"); */return; }
	//printf("calling printit2\n"); printf("Minute: %d\n", depth);printit2(depth, x, y); getchar();

	//printf("already[y][x].path: %d V %d :path already[y][x].depth %d V %d\n",
	//	already[y][x].path, path, already[y][x].depth, depth);

	//if ((path <= already[y][x].path && already[y][x].depth <= depth) || already[y][x].depth == -1) {  
	//if (already[y][x].depth <= depth || already[y][x].depth == -1) {  
	if (path < already[y][x].path || already[y][x].path == 0) {
		already[y][x].path = path;
		already[y][x].depth = depth;

		int found = 0;
		if (y-1 >= 0 && gridNum[depth+1][y-1][x] == 0) {
			found++;
			next(x, y-1, path+1, ex, ey, depth+1);
		}
		if (x+1 < lenx && gridNum[depth+1][y][x+1] == 0) {
			found++;
			next(x+1, y, path+1, ex, ey, depth+1);
		}
		if (y+1 < leny && gridNum[depth+1][y+1][x] == 0) {
			found++;
			next(x, y+1, path+1, ex, ey, depth+1);
		}
		if (x-1 >= 0 && gridNum[depth+1][y][x-1] == 0) {
			found++;
			next(x-1, y, path+1, ex, ey, depth+1);
		}

		if (found == 0) {
			//printf("found is %d (zero)\n", found); getchar();
			return;
			depth++;
			path++;
			goto ag;
		}

/*
		if (y-1 >= 1   && gridNum[depth][y-1][x] == 0 ) {
			next(x, y-1, path+1, ex, ey, depth+1);
		}
		if (x+1 < lenx && gridNum[depth][y][x+1] == 0) {
			next(x+1, y, path+1, ex, ey, depth+1);
		}
		if (y+1 < leny && gridNum[depth][y+1][x] == 0) {
			next(x, y+1, path+1, ex, ey, depth+1);
		}
		if (x-1 >= 1   && gridNum[depth][y][x-1] == 0) {
			next(x-1, y, path+1, ex, ey, depth+1);
		}
*/
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

void printit2(int gridX, int cx, int cy)
{
	printf("in printit2 cx:%d cy:%d\n", cx, cy);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (y == 0 && x == 1) {
				printf("S");
			} else if (y == leny-1 && x == lenx-2) {
				printf("E");
			} else if (x == cx && y == cy) {
				printf("X");
			} else if (y == 0) {
				printf("#");
			} else if (x == 0) {
				printf("#");
			} else if (y == leny-1) {
				printf("#");
			} else if (x == lenx-1) {
				printf("#");
			} else if (gridNum[gridX][y][x] == 0) {
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
