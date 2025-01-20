#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
FILE *a;
#define LINE 1000
//#define getchar()
int stuck = 0;
void sigfunc(int a) { printf("[[ %d ]]\n", stuck); }

char grid[200][200];
char gridA[200][200];
int gridA2[200][200];
void printit(int xin, int yin);
int leny = 0;
int lenx = 0;
int main(int argc, char **argv)
{
        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 6 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
	memset(gridA, '0', sizeof(gridA));
	memset(gridA2, 0, sizeof(gridA));
	for (int y = 0; y < 200; y++) {
		for (int x = 0; x < 200; x++) {
			assert(gridA[y][x] == '0');
		}
	}

while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	strcpy(grid[leny], line1);
	leny++;
}
fclose(a);

	lenx = strlen(grid[0]);
	int sx, sy;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '^') {
				sy = y; sx = x;
				grid[y][x] = '.';
				gridA[y][x] = 'X';
				goto fin;
			}
		}
	}
fin:
			

	stuck = 0;
	for (int y1 = 0; y1 < leny; y1++) {
		for (int x1 = 0; x1 < lenx; x1++) {
			if (y1 %2 == 0 && x1 %2 == 0) {
				//printf("%d,%d\n", x1, y1);
			}
			printf("%d,%d\n", x1, y1);
			if (grid[y1][x1] == '#') {
				continue;	
			} else {
				grid[y1][x1] = '#';
				memset(gridA2, 0, sizeof(gridA2));
			}
			{
				int x = sx; int y = sy;	
				int dir = 0;
				while (x < lenx && y < leny && x >= 0 && y >= 0) {
					//if (x1 == 12 && y1 == 19) {
						//printf("in while %d,%d -- dir:%d lenx:%d leny:%d\n", x,y, dir, lenx, leny);
						//for (int y3 = 0; y3 < leny; y3++) {
						//	for (int x3 = 0; x3 < lenx; x3++) {
						//		if (gridA2[y3][x3] > 3) {
						//			stuck++; goto ne;
						////		}
						//	}
						//}
						//printit(x, y); getchar();
					//}
			
/*
					if (gridA2[y1-1][x1] > 4) {
						printf("stuck@ %d %d\n", x1, y1-1);
						stuck++; goto ne;
					} else if (gridA2[y1][x1+1] > 4) {
						printf("stuck@ %d %d\n", x1+1, y1);
						stuck++; goto ne;
					} else if (gridA2[y1+1][x1] > 4) {
						printf("stuck@ %d %d\n", x1, y1+1);
						stuck++; goto ne;
					} else if (gridA2[y1][x1-1] > 4) {
						printf("sturck@ %d %d\n", x1-1, y1);
						stuck++; goto ne;
					}
*/
					if (y1-1 >= 0 && gridA2[y1-1][x1] > 4) {
						if (x1==12 && y1==19) {printf("stuck@ %d %d\n", x1, y1-1);}
						stuck++; goto ne;
					} else if (x1+1 < lenx && gridA2[y1][x1+1] > 4) {
						if (x1==12 && y1==19) {printf("stuck@ %d %d\n", x1+1, y1);}
						stuck++; goto ne;
					} else if (y1+1 < leny && gridA2[y1+1][x1] > 4) {
						if (x1==12 && y1==19) {printf("stuck@ %d %d\n", x1, y1+1);}
						stuck++; goto ne;
					} else if (x1-1 >= 0 && gridA2[y1][x1-1] > 4) {
						if (x1==12 && y1==19) {printf("sturck@ %d %d\n", x1-1, y1);}
						stuck++; goto ne;
					}
					switch (dir) {
						case 0:
							if (y-1 < 0 || grid[y-1][x] != '#') {
								if (y-1 >= 0) {
									gridA[y-1][x] = 'X';
									gridA2[y-1][x]++;
									if (gridA2[y-1][x] > 4) {stuck++; goto ne;}
								}
								y--;
							} else if (grid[y-1][x] == '#') {
								dir = 1;
							}
							break;
						case 1:
							if (x+1 >= lenx || grid[y][x+1] != '#') {
								if (x+1 < lenx) {
									gridA[y][x+1] = 'X';
									gridA2[y][x+1]++;
									if (gridA2[y][x+1] > 4) {stuck++; goto ne;}
								}
								x++;
							} else if (grid[y][x+1] == '#') {
								dir = 2;
							}
							break;
						case 2:
							if (y+1 >= leny || grid[y+1][x] != '#') {
								if (y+1 < leny) {
									gridA[y+1][x] = 'X';
									gridA2[y+1][x]++;
									if (gridA2[y+1][x] > 4) {stuck++; goto ne;}
								}
								y++;
							} else if (grid[y+1][x] == '#') {
								dir = 3;
							}
								
							break;
						case 3:
							if (x-1 < 0 || grid[y][x-1] != '#') {
								if (x-1 >= 0) {
									gridA[y][x-1] = 'X';
									gridA2[y][x-1]++;
									if (gridA2[y][x-1] > 4) {stuck++; goto ne;}
								}
								x--;
							} else if (grid[y][x-1] == '#') {
								dir = 0;
							}
							break;
					}
				}
				if (x1 == 7 && y1 == 19) {
					printf("breakout...\n");
				}
			}
ne:
			grid[y1][x1] = '.';
		}
	}
	unsigned long long count = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (gridA[y][x] == 'X') {
				count++;
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("** ans %d\n", stuck);
}
void printit(int xin, int yin) {
	int stx, sty, ex, ey;
	printf("%d %d\n", xin, yin);
	stx = xin - 10 < 0? 0: xin-10;
	sty = yin - 10 < 0? 0: yin-10;
	ex = xin + 10 > lenx? lenx: xin+10;
	ey = yin + 10 > leny? leny: yin+10;
	printf("%d %d %d %d\n", stx, ex, sty, ey);
	
for (int y2 = sty; y2 < ey; y2++) {
	for (int x2 = stx; x2 < ex; x2++) {
		if (x2 == xin && y2 == yin) {
			printf("0");
		} else {
			printf("%c", grid[y2][x2]);
		}
	}
	printf("\n");
}
printf("\n");
}
