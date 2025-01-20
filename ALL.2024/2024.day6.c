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
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

char grid[200][200];
char gridA[200][200];
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 6 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
	memset(gridA, '0', sizeof(gridA));
	for (int y = 0; y < 200; y++) {
		for (int x = 0; x < 200; x++) {
			assert(gridA[y][x] == '0');
		}
	}

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	strcpy(grid[leny], line1);
	leny++;
}
fclose(a);

	int lenx = strlen(grid[0]);
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
			

	{
		int x = sx; int y = sy;	
		int dir = 0;
		while (x < lenx && y < leny && x > 0 && y > 0) {
			printf("in while %d,%d -- dir:%d lenx:%d leny:%d\n", x,y, dir, lenx, leny);
			switch (dir) {
				case 0:
					if (grid[y-1][x] != '#') {
						gridA[y-1][x] = 'X';
						y--;
					} else if (grid[y-1][x] == '#') {
						dir = 1;
					}
					break;
				case 1:
					if (grid[y][x+1] != '#') {
						gridA[y][x+1] = 'X';
						x++;
					} else if (grid[y][x+1] == '#') {
						dir = 2;
					}
					break;
				case 2:
					printf("in case 2\n");
					if (grid[y+1][x] != '#') {
						gridA[y+1][x] = 'X';
						y++;
					} else if (grid[y+1][x] == '#') {
						dir = 3;
					}
						
					break;
				case 3:
					if (grid[y][x-1] != '#') {
						gridA[y][x-1] = 'X';
						x--;
					} else if (grid[y][x-1] == '#') {
						dir = 0;
					}
					break;
			}
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
	printf("** ans %llu\n", count);
}
