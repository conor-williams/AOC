#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
int lenx = 0;
int leny = 0;
int lenz = 0;

int LINE = 1000;

#define GX 200

char gridInitial[GX][GX];

char grid[GX][GX][GX];
char gridtmp[GX][GX][GX];
int countActive(int x, int y, int z);

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day17 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	for (int z = 0; z < GX; z++) {
		for (int y = 0; y < GX; y++) {
			for (int x = 0; x < GX; x++) {
				grid[z][y][x] = '.';
				gridtmp[z][y][x] = '.';
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
			grid[GX/2][sY+y][sX+x] = gridInitial[y][x];
			printf("%d %d <- %d %d (%c)\n", sX+x, sY+y, x, y, grid[0][sY+y][sX+x]);
		}
	}
	int countANS = 0;
	for (int t = 0; t < 6; t++) {
		for (int z = 1; z < GX-1; z++) {
			for (int y = 1; y < GX-1; y++) {
				for (int x = 1; x < GX-1; x++) {
					if (grid[z][y][x] == '#') {
						int cA = countActive(x, y, z);
						if (cA == 2 || cA == 3) {
							gridtmp[z][y][x] = '#';
						} else {
							gridtmp[z][y][x] = '.';
						}
					} else if (grid[z][y][x] == '.') {
						int cA = countActive(x, y, z);
						if (cA == 3) {
							gridtmp[z][y][x] = '#';
						} else {
							gridtmp[z][y][x] = '.';
						}
							
					}
				}
			}
		}
		printf("GX/2\n");
		{
			int z1 = GX/2;
			for (int y = GX/2 -1; y < GX/2 + 2; y++) {
				for (int x = GX/2 -1; x < GX/2 + 2; x++) {
					printf("%c", gridtmp[z1][y][x]);
					printf("[[%d %d %d]]", x, y, z1);
				}
				printf("\n");
			}
		}
		printf("\n");
		printf("GX/2+1\n");
		{
			int z1 = (GX/2)+1;
			for (int y = GX/2 -1; y < GX/2 + 2; y++) {
				for (int x = GX/2 -1; x < GX/2 + 2; x++) {
					printf("%c", gridtmp[z1][y][x]);
				}
				printf("\n");
			}
		}
		printf("\n");
		printf("GX/2-1\n");
		{
			int z1 = (GX/2)-1;
			for (int y = GX/2 -1; y < GX/2 + 2; y++) {
				for (int x = GX/2 -1; x < GX/2 + 2; x++) {
					printf("%c", gridtmp[z1][y][x]);
				}
				printf("\n");
			}
		}
		printf("\n");
	
		getchar();
		int countHash = 0;
		for (int z = 0; z < GX; z++) {
			for (int y = 0; y < GX; y++) {
				for (int x = 0; x < GX; x++) {
					if (gridtmp[z][y][x] == '#') {
						countHash++;
					}
					grid[z][y][x] = gridtmp[z][y][x];
				}
			}
		}
		printf("CYCLE %d -- active: %d\n", t, countHash);
		countANS = countHash;
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", countANS);

}

int countActive(int x, int y, int z) {
	int count = 0;
	if (grid[z][y-1][x] == '#') {count++;}
	if (grid[z][y-1][x+1] == '#') {count++;}
	if (grid[z][y][x+1] == '#') {count++;}
	if (grid[z][y+1][x+1] == '#') {count++;}
	if (grid[z][y+1][x] == '#') {count++;}
	if (grid[z][y+1][x-1] == '#') {count++;}
	if (grid[z][y][x-1] == '#') {count++;}
	if (grid[z][y-1][x-1] == '#') {count++;} //8 middle face

	if (grid[z-1][y][x] == '#') {count++;}
	if (grid[z-1][y-1][x] == '#') {count++;}
	if (grid[z-1][y-1][x+1] == '#') {count++;}
	if (grid[z-1][y][x+1] == '#') {count++;}
	if (grid[z-1][y+1][x+1] == '#') {count++;}
	if (grid[z-1][y+1][x] == '#') {count++;}
	if (grid[z-1][y+1][x-1] == '#') {count++;}
	if (grid[z-1][y][x-1] == '#') {count++;}
	if (grid[z-1][y-1][x-1] == '#') {count++;} //9 back face

	if (grid[z+1][y][x] == '#') {count++;}
	if (grid[z+1][y-1][x] == '#') {count++;}
	if (grid[z+1][y-1][x+1] == '#') {count++;}
	if (grid[z+1][y][x+1] == '#') {count++;}
	if (grid[z+1][y+1][x+1] == '#') {count++;}
	if (grid[z+1][y+1][x] == '#') {count++;}
	if (grid[z+1][y+1][x-1] == '#') {count++;}
	if (grid[z+1][y][x-1] == '#') {count++;}
	if (grid[z+1][y-1][x-1] == '#') {count++;} //9 back face

	return count;

}

/*
	grid[0][sY][sX] = gridInitial[0][0];
	grid[0][sY][sX+1] = gridInitial[0][1];
	grid[0][sY][sX+2] = gridInitial[0][2];

	grid[0][sY+1][sX] = gridInitial[1][0];
	grid[0][sY+1][sX+1] = gridInitial[1][1];
	grid[0][sY+1][sX+2] = gridInitial[1][2];

	grid[0][sY+2][sX] = gridInitial[2][0];
	grid[0][sY+2][sX+1] = gridInitial[2][1];
	grid[0][sY+2][sX+2] = gridInitial[2][2];
*/

