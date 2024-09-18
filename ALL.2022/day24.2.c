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
#include <stack>

using namespace std;

map <tuple<int, int, int>, int> mpALL;
map <tuple<int, int, int>, int> mp;
map <tuple<int, int, int>, int> mpTmp;
map <tuple<int, int, int>, int> mpTmp2;
map <tuple<int, int, int>, int> mpTmp3;
map <tuple<int, int, int>, int> visited;

map <tuple<int, int, int, int, int>, int> mpSE;
stack <tuple<int, int, int>> mp2;

int count123 = 0;
int minPathTot = 0;
//Been there at the same depth...
FILE *a;
#define LINE 1000
#define getchar()
int minPath = 99999;
int minminPath = 99999;
int dep = 1000;
int hide = 0;
int fd;
int dijk2(int conSX, int conSY, int conEX, int conEY, int mmpp);
//void sigfunc(int a) { if (count123 % 2 == 0) {dup2(fd,1);}if (hide==1) {dup2(fd, 1);} printf("[[ %s %d]]\n", "signal hand..\n", minPath); if (hide==1) {fd=dup(1); close(1);} }
//void sigfunc(int a) { dup2(fd,1); printf("in sig\n"); /*fd=dup(1); close(1);*/ count123++; if (count123 % 2 == 0) {dup2(fd,1);} else if (count123 % 2 == 1) {fd=dup(1); close(1);} }
int PASS = 0;
void sigfunc(int a) { printf("minminPath %d -- cur minPath is %d\n", minPath, minminPath); printf("PASS %d\n", PASS);}

/*
   struct al_s {
   int path;
   };

   struct al_s already[120][120];
 */
/*
   struct visited_s {
   int path;
   };
   struct visited_s visited[120][120];
 */


//int already[120][120];
#define SX 105
char grid[SX][SX];
int gridNum[1001][SX][SX];
int gridNumInter[SX][SX];
//int already[SX][SX] = {0};
int leny = 0;
int lenx = 0;

void printit(int depth);
void makeMovesAll(int xyz);
void next(int x, int y, int path, int ex, int ey, int depth);
void dikjstra(int conSX, int conSY, int conEX, int conEY, int mmPP);

int main(int argc, char **argv)
{
	//memset(already, 0, sizeof(already));
	//memset(visited, 0, sizeof(visited));
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
		//printf("LINE: %s\n", line1);
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

	//printit(0); //getchar();
	printf("---------------\n");
	for (int i = 1; i < dep; i++) {
		memset(gridNum[i], 0, sizeof(gridNum[i]));
		makeMovesAll(i);
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

		gridNum[i][0][1] = 0;
		gridNum[i][leny-1][lenx-2] = 0;
	}

	int tot = 0;
	dijk2(1, 0, lenx-2, leny-1, 0); 
	printf("minPath is %d\n", minPath);

	tot += minPath;
	dijk2(lenx-2, leny-1, 1, 0, minPath); 
	printf("minPath now %d\n", minPath);
	tot += minPath;
	dijk2(1, 0, lenx-2, leny-1, minPath); 
	printf("minPath now %d\n", minPath);
	tot += minPath;

	printf("**ans %d\n", tot);

}

int dijk2(int conSX, int conSY, int conEX, int conEY, int mmpp) {

	minPath = 99999;
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

	visited.clear();
	while (mp2.size() != 0) {
		mp2.pop();
	}
	assert(mp2.size() == 0);
	//assert(conSX == 1); assert(conSY == 0);
	mp2.push({conSX, conSY, 0});
	mp2.push({conSX, conSY, 1});
	mp2.push({conSX, conSY, 2});
	mp2.push({conSX, conSY, 3});

	while (1) {
egg:
		if (mp2.size() == 0) { break; }
		tuple fir = mp2.top(); mp2.pop();

		int x = get<0>(fir); int y = get<1>(fir); int pa = get<2>(fir);

		if (pa < 350) {
			if (visited.find({x, y, pa}) == visited.end() && gridNum[pa][y][x] == 0) { 
				visited[{x, y, pa}] = 1;
				if (x == conEX && y == conEY) {
					if (pa < minPath) {minPath = pa;}
					goto egg;
				}

				if (y-1 >= 0) {
					for (int aa = 1; aa < 5; aa++) {
						if (gridNum[pa+aa][y-1][x] != 0) {break;}
						if (gridNum[pa+aa][y-1][x] == 0) {
							int newPa = pa+aa;
							mp2.push({x, y-1, newPa});
						}
					}
				}
				if (x+1 < lenx) {
					for (int bb = 1; bb < 5; bb++) {
						if (gridNum[pa+bb][y][x+1] != 0){break;}
						if (gridNum[pa+bb][y][x+1] == 0) {
							int newPa = pa+bb;
							mp2.push(make_tuple(x+1, y, newPa));
						}
					} 
				}
				if (y+1 < leny) {
					for (int cc = 1; cc < 5; cc++) {
						if (gridNum[pa+cc][y+1][x] != 0) {break;}
						if (gridNum[pa+cc][y+1][x] == 0) {
							int newPa = pa+cc;
							mp2.push({x, y+1, newPa});
						}
					}
				}
				if (x-1 >= 0) {
					for (int dd = 1; dd < 5; dd++) {
						if (gridNum[pa+dd][y][x-1] != 0) {break;}
						if (gridNum[pa+dd][y][x-1] == 0) {
							int newPa = pa+dd;
							mp2.push(make_tuple(x-1, y, newPa));
						}
					}
				}
			}
		}
	}
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
	//mpALL[{conSX, conSY, path}] = 1;
	//memset(visited, 0, sizeof(visited));
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

	//printf("mpTmp size (%d)\n", (int)mpTmp.size());

	/*
	   mpTmp3.clear();
	   for (auto it = mpTmp.begin(); it != mpTmp.end(); it++) {
	   tuple fir = it->first;
	   int cx = get<0>(fir); int cy = get<1>(fir); int pa = get<2>(fir);
	   tuple abcd = make_tuple(cx, cy, pa); //if (mpALL.find(abcd) != mpALL.end()) {continue;} else {mpALL[abcd] = 1;} 
	   if (mpALL.find(abcd) == mpALL.end()) {
	   mpTmp3.insert({abcd, 1});
	   mpALL.insert({abcd, 1});
	//printf("NOT THERE mpTmp %d %d %d\n", cx, cy, pa);
	}
	}
	mpTmp = mpTmp3;
	 */
	for (auto it = mpTmp.begin(); it != mpTmp.end(); it++) {
		tuple fir = it->first;
		int cx = get<0>(fir); int cy = get<1>(fir); int pa = get<2>(fir);
		//printf("Trying %d %d %d\n", cx, cy, pa);
		//tuple abcd = make_tuple(cx, cy, pa); //if (mpALL.find(abcd) != mpALL.end()) {continue;} else {mpALL[abcd] = 1;} 

		//for (int ey1 = 0; ey1 < leny; ey1++) {
		//	for (int ex1 = 1; ex1 < lenx-1; ex1++) {

		//if (ey1 == 0 && ex1 != 1) {continue;} else if (ey1 == leny-1 && ex1 != lenx -2) {continue;}
		//memset(already, 0, sizeof(already));

		//int found22 = 0; for (int zz2 = pa+1; zz2 < dep; zz2++) { if (gridNum[zz2][ey1][ex1] == 0) { found22 = 1; break; } } if (found22 == 0) {continue;}

		minPath = 99999;
		next(cx, cy, pa, conEX, conEY, pa);

		if (minPath != 99999) {
			//if (ex1 == conEX && ey1 == conEY) {
			if (minPath < minminPath) {minminPath = minPath;}
			cout << "yatzee... minPath:" << minPath << endl;
			//} else {
			//mp[{ex1, ey1, minPath+1}] = 1;
			//}
		}
		//	}
		//}
	}
	goto again;
end:
	minPath = minminPath;
	minPathTot += minPath;
	printf("leaving dikjstra -- minPath: ( %d )\n", minPath);
}

void next(int x, int y, int path, int ex, int ey, int depth) 
{
ag221:
	int e = dep < 300 ? dep : 300;
	if (depth >= e) {return;}
	//if (gridNum[depth][y][x] != 0) {return;}
	if (path >= minPath) {return;}
	if (x == ex && y == ey) {
		//printf("**End reached minPath:%d Start: %d,%d (END:%d,%d) depth is %d\n", path, vsx, vsy, ex, ey, depth); getchar();
		printf("**End reached path %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}

	//if (path < already[y][x] || already[y][x] == 0) {
	if (visited.find({x, y, path}) == visited.end()) 
	{
		visited[{x, y, path}] = 1;

		int found = 0;
		if (y-1 >= 0) {
			found++;
			next(x, y-1, path+1, ex, ey, depth+1);
		}
		if (x+1 < lenx) {
			found++;
			next(x+1, y, path+1, ex, ey, depth+1);
		}
		if (y+1 < leny) {
			found++;
			next(x, y+1, path+1, ex, ey, depth+1);
		}
		if (x-1 >= 0) {
			found++;
			next(x-1, y, path+1, ex, ey, depth+1);
		}
		if (found == 0) {
			path++;
			goto ag221;
		}
	} else {
		//printf("visited %d %d %d \n", x, y, path);
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
