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
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SX 40
char grid[SX][SX][SX];
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day18 part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];
	char line2[LINE];

	int leny = 0;
	memset(grid, '.', sizeof(grid));
	for (int z = 0; z < SX; z++) {
		for (int y = 0; y < SX; y++) {
			for (int x = 0; x < SX; x++) {
				assert(grid[z][y][x] == '.');
			}
		}
	}
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		int x1, y1, z1;
		int ret1 = sscanf(line1, "%d,%d,%d", &x1, &y1, &z1);
		if (x1 > SX || y1 > SX || z1 > SX) {
			perror ("size"); exit(0);
		}
		sprintf(line2, "%d,%d,%d", x1, y1, z1);
		assert(strcmp(line1, line2) == 0);
		assert(ret1 == 3);
		grid[z1+1][y1+1][x1+1] = '#';
		leny++;
	}
	fclose(a);

	int surfaceS = 0;
	{
		for (int xRay = SX-2; xRay >= 0; xRay--) {
			for (int z = 0; z < SX; z++) {
				for (int y = 0; y < SX; y++) {
					if (grid[z][y][xRay] == '#' && grid[z][y][xRay+1] == '.') {
						surfaceS++;
					}
				}
			}
		}
		for (int xRay = 1; xRay < SX; xRay++) {
			for (int z = 0; z < SX; z++) {
				for (int y = 0; y < SX; y++) {
					if (grid[z][y][xRay] == '#' && grid[z][y][xRay-1] == '.') {
						surfaceS++;
					}
				}
			}
		}
	}
	{
		for (int yRay = SX-2; yRay >= 0; yRay--) {
			for (int z = 0; z < SX; z++) {
				for (int x = 0; x < SX; x++) {
					if (grid[z][yRay][x] == '#' && grid[z][yRay+1][x] == '.') {
						surfaceS++;
					}
				}
			}
		}
		for (int yRay = 1; yRay < SX; yRay++) {
			for (int z = 0; z < SX; z++) {
				for (int x = 0; x < SX; x++) {
					if (grid[z][yRay][x] == '#' && grid[z][yRay-1][x] == '.') {
						surfaceS++;
					}
				}
			}
		}
	}
	{ 
		for (int zRay = SX-2; zRay >= 0; zRay--) {
			for (int y = 0; y < SX; y++) {
				for (int x = 0; x < SX; x++) {
					if (grid[zRay][y][x] == '#' && grid[zRay+1][y][x] == '.') {
						surfaceS++;
					}
				}
			}
		}
		for (int zRay = 1; zRay < SX; zRay++) {
			for (int y = 0; y < SX; y++) {
				for (int x = 0; x < SX; x++) {
					if (grid[zRay][y][x] == '#' && grid[zRay-1][y][x] == '.') {
						surfaceS++;
					}
				}
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", surfaceS);
}
