#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <map>

#include <unistd.h>

#define getchar()
using namespace std;

int tot = 0;
#define SIZE 299
char line1[SIZE];
int leny = 0;

#define getchar()
#define SZ 8000
char grid[SZ][SZ];
char gridOrig[SZ][SZ];

int minx = 99999; int maxx = 0;
int miny = 99999; int maxy = 0;
void printit(int val);
struct save_s {
	int x;
	int y;
}; 
struct save_s save[50000];
map<pair<int, int>,int> mp;
int drilldown(int x1, int y1);
int comeup(int frmx1, int frmy1, int tox1, int toy1, int drillit);

int savePos = 0;
int EX1 = 0;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day17.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	if (strcmp(argv[1], "ex1.txt") == 0) {
		EX1 = 1;
	}
	for (int y = 0; y < SZ; y++) {
		for (int x  =0; x < SZ; x++) {
			grid[y][x] = '.';
		}
	}
	grid[0][500] = '+';
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[(int)strlen(line1)-1] = '\0';
		printf("line1 %s\n", line1);

		int x1, x2;
		int y1, y2;
		int ret = sscanf(line1, "x=%d, y=%d..%d", &x1, &y1, &y2);	
		if (ret == 3) {
			if (y1 > y2) {int tmp; tmp = y1; y1 = y2; y2 = tmp;}
			if (x1 < minx) {minx = x1;} if (x1 > maxx) {maxx = x1;}
			if (y1 < miny) {miny = y1;} if (y2 > maxy) {maxy = y2;}
			int x = x1; 
			for (int y = y1; y <= y2; y++) {
				grid[y][x] = '#';
			}
			continue;
		}
		ret = sscanf(line1, "y=%d, x=%d..%d", &y1, &x1, &x2);	
		if (ret == 3) {
			if (x1>x2) {int tmp; tmp = x1; x1 = x2; x2 = tmp;}
			if (y1 < miny) {miny = y1;} if (y1 > maxy) {maxy = y1;}
			if (x1 < minx) {minx = x1;} if (x2 > maxx) {maxx = x2;}
			int y = y1;
			for (int x = x1; x <= x2; x++) {
				grid[y][x] = '#';
			}
			continue;
		}	


		leny++;
	}
	miny = 0;
	int origMaxy = maxy;
	maxy += 5;
	minx -= 5;
	maxx += 5;
	printf("miny maxy :%d,%d minx, maxx %d,%d origmaxy is %d\n", miny, maxy, minx, maxx, origMaxy); 
	//int fd = dup(1); close(1);
	fclose(a);



	for (int y = miny; y <= origMaxy; y++) {
		for (int x = minx; x<= maxx; x++) {
			gridOrig[y][x] = grid[y][x];
		}
	}
	printit(23);
	int sx = 500;
	int sy = 0;
	//int bottom;
	grid[sy][sx] = '+';
	mp.insert({{sx, sy},1});
	save[0].x = sx; save[0].y = sy; savePos++;
	drilldown(sx, sy+1);
	printf("after drilldown\n"); printit(0); 
	printf("SAVES: \n");
	for (int i = 0; i < savePos; i++) {
		printf("%d, %d\n", save[i].x, save[i].y);
	}
	printf("-------\n");
	int i = savePos-1;

	comeup(save[i].x, save[i].y, 500, 0, 1);
	//comeup(save[i].x, save[i].y, save[i-1].x, save[i-1].y);


	//tidy up -- spurious R.L or L.R

	int Ftot = 0;
	for (int y = miny; y <= origMaxy; y++) {
		for (int x = minx; x<= maxx-2; x++) {
			if (grid[y][x] == 'R' && grid[y][x+1] == '.' && grid[y][x+2] == 'L') {
				grid[y][x+1] = 'F';
				Ftot++;
			} else if (grid[y][x] == 'L' && grid[y][x+1] == '.' && grid[y][x+2] == 'R') {
				grid[y][x+1] = 'F';
				Ftot++;
			}
		}
	}
	printit(23);
	printf("Ftot is %d\n", Ftot);			

	int susperr = 0;
	for (int x = minx; x<= maxx; x++) {
		for (int y = miny; y <= origMaxy; y++) {
			if (grid[y][x] == 'L' && grid[y+1][x] == '.') {
				susperr++;
				printf("ERRL.\n");
			} else if (grid[y][x] == 'R' && grid[y+1][x] == '.') {
				susperr++;
				printf("ERRR.\n");
			} else if (grid[y][x] == '|' && grid[y+1][x] == '.') {
				susperr++;
				printf("ERR|\n");
			}
		}
	}

	printf("susperr is %d\n", susperr);
	int hasherr =0;
	for (int x = minx; x<= maxx; x++) {
		for (int y = miny; y <= origMaxy; y++) {
			if (grid[y][x] == '#' && gridOrig[y][x] != '#') {
				printf("ERRoR HASH\n");
				hasherr++;
			}
			if (gridOrig[y][x] == '#' && grid[y][x] != '#') {
				printf("ERROR 2 HASH\n");
				hasherr++;
			}
		}
	}
	printf("hasherr is %d\n", hasherr);
	//fflush(stdout); dup2(fd, 1);
	grid[sy][sx] = '+';
	tot = 0;
	for (int y = miny+8; y <= origMaxy; y++) {
		for (int x = minx; x<= maxx; x++) {
			if (grid[y][x] == '|' || grid[y][x] == 'R' || grid[y][x] == 'L' || grid[y][x] == 'F') {
				tot++;
			}
		}
	}
	fflush(stdout); dup2(fd, 1);
	printf("*** tot is %d\n", tot);
	//printit(22);
}

int drilldown(int x1, int y1) {
	//printf("in drilldown %d, %d maxy is %d\n", x1, y1, maxy);
	if (y1 >= maxy) {printit(23); printf("end reached...return 55\n"); getchar(); return 55;}
	int myret = 0; int bot; 

	for (int y = y1; y <= maxy; y++) {
		if (grid[y][x1] != '#') {
			printf("adding pipe %d %d\n", x1, y); 
			grid[y][x1] = '|';
			if (y == maxy) {bot = maxy; printit(23); printf("end2 reached -- return 55\n"); getchar(); return 55;}
			continue;
		} else {
			bot = y-1;
			break;
		}
	}

	printf("found very bottom %d,%d\n", x1, bot);
	if (mp.find({x1, bot}) != mp.end()) {
		return 11;
	}

	save[savePos].x = x1; save[savePos].y = bot; savePos++;
	mp.insert({{x1, bot}, 1});
	return myret;

}

int comeup(int frmx1, int frmy1, int tox1, int toy1, int drillit) {
	if (frmy1 == maxy || toy1 == maxy) {return 55;}
	//printf("in comeup... %d %d %d %d\n", frmx1, frmy1, tox1, toy1); 

	//left

	int breakit = 0;
	for (int y = frmy1; y>toy1;y--) {
		//printf("comeup: y is %d\n", y); fflush(stdout);

/*
...LLLLRRRRRRRRRRRRRRRRRRRRRRRRRR......
...||#RRRRRRRRRRRRRRRRRRRRRRRRR#|....
...||#RRRRRRRRRRRRRRRRRRRRRRRRR#|.....
...||###########################|......
...||...........................|......
...||...........................|.......
*/
		int itsx = frmx1+1;
		for (int x = frmx1-1; x >= minx ; x--) {
			//printf("comeup: Lx is %d\n", x); fflush(stdout); 
			if (grid[y][x] == '#') { //found wall left
				itsx = x+1;
				break;
			} else {
				grid[y][x] = 'L';
				if ((y+1 <= frmy1 && grid[y+1][x] == '#') || (grid[y+1][x] == '.')) {
					if (grid[y+1][x-1] == '.') {
						if (grid[y+1][x] != '.') {
							 printf("L: found top of wall @ %d %d\n", x, y+1);
							grid[y][x-1] = 'L';
							int ret1  = drilldown(x-1, y+1);
							printf("ret1 is %d\n", ret1);
							if (ret1 == 55) {printf("55 R\n"); breakit = 1; break;}
							else if (ret1 == 11) {printf("got 11 L\n"); breakit=1; break;}
							else {if (33 == comeup(save[savePos-1].x, save[savePos-1].y, save[savePos-1].x, 1, 1)) {/*return 44;*/}printit(0);}
							breakit = 1;
							break;
						} else {
							breakit = 1;
							break;
						}
					} else if (grid[y+1][x-1] == '|' && grid[y+1][x-2] == '.') {
						breakit = 1; break;
					}

				}
			}
		}

		//right
		for (int x = itsx /*frmx1+1*/; x <= maxx ;x++) {
			//printf("comeup: Rx is %d\n", x); fflush(stdout);
			if (grid[y][x] == '#') { //found wall right
				break;
			} else {
				grid[y][x] = 'R';
				if ((y+1 <= frmy1 && grid[y+1][x] == '#' )|| (grid[y+1][x] == '.')) {
					if (grid[y+1][x+1] == '.') {
						printf("found wall ...%d V %d %c\n", y+1, frmy1, grid[y+1][x]);
						grid[y][x+1] = 'R';
						printf("RRR: found top of wall @ %d %d\n", x, y+1); 
						printf("RRR: drill down @ %d %d\n", x+1, y+1); 
						int ret2  = drilldown(x+1, y+1);
						printf("ret2 is %d\n", ret2);
						if (ret2 == 55) {printf("55 L\n"); breakit = 1; break;}
						else if (ret2 == 11) {printf("got 11 R\n");  breakit = 1; break;}
						else {if (comeup(save[savePos-1].x, save[savePos-1].y, save[savePos-1].x, 1, 1) == 33) {/*return 44;*/} printit(0);}
						breakit = 1;
						break;
					} else if (grid[y+1][x+1] == '|' && grid[y+1][x+2] == '.') {
						breakit = 1; break;
					}
				} else {
					printf("did I not find wall...%d V %d (y+1 <= frmy1) %c\n", y+1, frmy1, grid[y+1][x]);
					//if (frmy1 == 1948 && grid[y+1][x] == '#') {grid[y][x] = 'Z';}
				}
			}
		}

		if (breakit == 1) {printf("ret 33\n"); return 33;}
	}
	printit(23); getchar();
	return 0;
}

void printit(int p) {
	if (p == 22 || p == 23) {} else {return;}
	int st, end;
	if (EX1 == 1) {
		st = miny; end = maxy;
	} else {
		//st = miny; end = maxy;
		//st = maxy  = 800; end = 900;
		st = 800 ; end = 900;
	}

	if (p == 23) {
		st = 0; end = maxy;
	}
	for (int y = st; y<=end; y++) {
		for (int x = minx; x<= maxx; x++) {
			if (grid[y][x] == '.') {
				printf(" ");
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("%d\n", y);
	}
	printf("\n");
}

