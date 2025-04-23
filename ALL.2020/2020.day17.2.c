#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

int lenx = 0;
int leny = 0;
int lenz = 0;

int LINE = 1000;
#define getchar()

#define GX 20

char gridInitial[GX][GX];

char grid[GX][GX][GX][GX];
//char ****grid;
char gridtmp[GX][GX][GX][GX];
//char ****gridtmp;
int countActive(int x, int y, int z, int w);

///char (*grid)[tX+10] = malloc(sizeof(char[tY+10][tX+10]));
//if (grid == NULL) {perror("gridE\n"); exit(0);}


int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day17 Part2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	for (int z = 0; z < GX; z++) {
		for (int y = 0; y < GX; y++) {
			for (int x = 0; x < GX; x++) {
				for (int w = 0; w < GX; w++) {
					grid[z][y][x][w] = '.';
					gridtmp[z][y][x][w] = '.';
				}
			}
		}
	}

	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);
		strcpy(gridInitial[leny], line1);

		leny++;
	}
	int ld2 = leny/2;
	int sY = (GX/2) - ld2;
	int sX = (GX/2) - ld2;

	lenx = leny;
	lenz = leny;

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			grid[GX/2][sY+y][sX+x][GX/2] = gridInitial[y][x];
			printf("%d %d <- %d %d (%c)\n", sX+x, sY+y, x, y, grid[0][sY+y][sX+x][0]);
		}
	}

	int ans = 0;
	for (int t = 0; t < 6; t++) {
		for (int z = 1; z < GX-1; z++) {
			for (int y = 1; y < GX-1; y++) {
				for (int x = 1; x < GX-1; x++) {
					for (int w = 1; w < GX-1; w++) {
						if (grid[z][y][x][w] == '#') {
							int cA = countActive(x, y, z, w);
							if (cA == 2 || cA == 3) {
								gridtmp[z][y][x][w] = '#';
							} else {
								gridtmp[z][y][x][w] = '.';
							}
						} else if (grid[z][y][x][w] == '.') {
							int cA = countActive(x, y, z, w);
							if (cA == 3) {
								gridtmp[z][y][x][w] = '#';
							} else {
								gridtmp[z][y][x][w] = '.';
							}

						}
					}
				}
			}
		}
		getchar();
		int countHash = 0;
		for (int z = 0; z < GX; z++) {
			for (int y = 0; y < GX; y++) {
				for (int x = 0; x < GX; x++) {
					for (int w = 0; w < GX; w++) {
						if (gridtmp[z][y][x][w] == '#') {
							countHash++;
						}
						grid[z][y][x][w] = gridtmp[z][y][x][w];
					}
				}
			}
		}
		printf("CYCLE %d -- active: %d\n", t, countHash);
		if (t == 5) {ans = countHash;}
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", ans);
	fflush(stdout);
}

int countActive(int x, int y, int z, int w) {
	int count = 0;
	//// w = w...
	if (grid[z][y-1][x][w] == '#') {count++;}
	if (grid[z][y-1][x+1][w] == '#') {count++;}
	if (grid[z][y][x+1][w] == '#') {count++;}
	if (grid[z][y+1][x+1][w] == '#') {count++;}
	if (grid[z][y+1][x][w] == '#') {count++;}
	if (grid[z][y+1][x-1][w] == '#') {count++;}
	if (grid[z][y][x-1][w] == '#') {count++;}
	if (grid[z][y-1][x-1][w] == '#') {count++;} //8 middle face

	if (grid[z-1][y][x][w] == '#') {count++;}
	if (grid[z-1][y-1][x][w] == '#') {count++;}
	if (grid[z-1][y-1][x+1][w] == '#') {count++;}
	if (grid[z-1][y][x+1][w] == '#') {count++;}
	if (grid[z-1][y+1][x+1][w] == '#') {count++;}
	if (grid[z-1][y+1][x][w] == '#') {count++;}
	if (grid[z-1][y+1][x-1][w] == '#') {count++;}
	if (grid[z-1][y][x-1][w] == '#') {count++;}
	if (grid[z-1][y-1][x-1][w] == '#') {count++;} //9 back face

	if (grid[z+1][y][x][w] == '#') {count++;}
	if (grid[z+1][y-1][x][w] == '#') {count++;}
	if (grid[z+1][y-1][x+1][w] == '#') {count++;}
	if (grid[z+1][y][x+1][w] == '#') {count++;}
	if (grid[z+1][y+1][x+1][w] == '#') {count++;}
	if (grid[z+1][y+1][x][w] == '#') {count++;}
	if (grid[z+1][y+1][x-1][w] == '#') {count++;}
	if (grid[z+1][y][x-1][w] == '#') {count++;}
	if (grid[z+1][y-1][x-1][w] == '#') {count++;} //9 back face

	//// w = w-1...
	if (grid[z][y][x][w-1] == '#') {count++;}
	if (grid[z][y-1][x][w-1] == '#') {count++;}
	if (grid[z][y-1][x+1][w-1] == '#') {count++;}
	if (grid[z][y][x+1][w-1] == '#') {count++;}
	if (grid[z][y+1][x+1][w-1] == '#') {count++;}
	if (grid[z][y+1][x][w-1] == '#') {count++;}
	if (grid[z][y+1][x-1][w-1] == '#') {count++;}
	if (grid[z][y][x-1][w-1] == '#') {count++;}
	if (grid[z][y-1][x-1][w-1] == '#') {count++;} //9 middle face

	if (grid[z-1][y][x][w-1] == '#') {count++;}
	if (grid[z-1][y-1][x][w-1] == '#') {count++;}
	if (grid[z-1][y-1][x+1][w-1] == '#') {count++;}
	if (grid[z-1][y][x+1][w-1] == '#') {count++;}
	if (grid[z-1][y+1][x+1][w-1] == '#') {count++;}
	if (grid[z-1][y+1][x][w-1] == '#') {count++;}
	if (grid[z-1][y+1][x-1][w-1] == '#') {count++;}
	if (grid[z-1][y][x-1][w-1] == '#') {count++;}
	if (grid[z-1][y-1][x-1][w-1] == '#') {count++;} //9 back face

	if (grid[z+1][y][x][w-1] == '#') {count++;}
	if (grid[z+1][y-1][x][w-1] == '#') {count++;}
	if (grid[z+1][y-1][x+1][w-1] == '#') {count++;}
	if (grid[z+1][y][x+1][w-1] == '#') {count++;}
	if (grid[z+1][y+1][x+1][w-1] == '#') {count++;}
	if (grid[z+1][y+1][x][w-1] == '#') {count++;}
	if (grid[z+1][y+1][x-1][w-1] == '#') {count++;}
	if (grid[z+1][y][x-1][w-1] == '#') {count++;}
	if (grid[z+1][y-1][x-1][w-1] == '#') {count++;} //9 back face
							//// w = w+1...
	if (grid[z][y][x][w+1] == '#') {count++;}
	if (grid[z][y-1][x][w+1] == '#') {count++;}
	if (grid[z][y-1][x+1][w+1] == '#') {count++;}
	if (grid[z][y][x+1][w+1] == '#') {count++;}
	if (grid[z][y+1][x+1][w+1] == '#') {count++;}
	if (grid[z][y+1][x][w+1] == '#') {count++;}
	if (grid[z][y+1][x-1][w+1] == '#') {count++;}
	if (grid[z][y][x-1][w+1] == '#') {count++;}
	if (grid[z][y-1][x-1][w+1] == '#') {count++;} //9 middle face

	if (grid[z-1][y][x][w+1] == '#') {count++;}
	if (grid[z-1][y-1][x][w+1] == '#') {count++;}
	if (grid[z-1][y-1][x+1][w+1] == '#') {count++;}
	if (grid[z-1][y][x+1][w+1] == '#') {count++;}
	if (grid[z-1][y+1][x+1][w+1] == '#') {count++;}
	if (grid[z-1][y+1][x][w+1] == '#') {count++;}
	if (grid[z-1][y+1][x-1][w+1] == '#') {count++;}
	if (grid[z-1][y][x-1][w+1] == '#') {count++;}
	if (grid[z-1][y-1][x-1][w+1] == '#') {count++;} //9 back face

	if (grid[z+1][y][x][w+1] == '#') {count++;}
	if (grid[z+1][y-1][x][w+1] == '#') {count++;}
	if (grid[z+1][y-1][x+1][w+1] == '#') {count++;}
	if (grid[z+1][y][x+1][w+1] == '#') {count++;}
	if (grid[z+1][y+1][x+1][w+1] == '#') {count++;}
	if (grid[z+1][y+1][x][w+1] == '#') {count++;}
	if (grid[z+1][y+1][x-1][w+1] == '#') {count++;}
	if (grid[z+1][y][x-1][w+1] == '#') {count++;}
	if (grid[z+1][y-1][x-1][w+1] == '#') {count++;} //9 back face
	return count;

}

