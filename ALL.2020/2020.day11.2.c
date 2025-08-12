#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
char grid[120][120];
char gridTmp[120][120];
#define getchar()
int lenx = 0;
int leny = 0;
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2020 Day11 part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	int leny = 0;
	while (1) {
		fgets(line1, 500, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);

	lenx = strlen(grid[0]);
	int sx = lenx;
	int sy = leny;
	int co = 0;
	printf("sx, sy: %d %d\n", sx, sy);
	while (true) {
		co++;
		memcpy(gridTmp, grid, sizeof(grid));
		for (int y = 0; y < sy; y++) {
			for (int x = 0; x < sx; x++) {
				int countOcc = 0;
				for (int xx = 1, yy=1; xx < sx && yy < sy; xx++, yy++) {
					if (y-yy >= 0 && x-xx >=0) {
						if (grid[y-yy][x-xx] == '#') {
							countOcc++;
							goto aft1;
						} else if (grid[y-yy][x-xx] == 'L') {
							goto aft1;
						}
					} else {
						goto aft1;
					}
				}
aft1:
				for (int yy=1; yy < sy; yy++) {
					if (y-yy >= 0) {
						if (grid[y-yy][x] == '#') {
							countOcc++;
							goto aft2;
						} else if (grid[y-yy][x] == 'L') {
							goto aft2;
						}
					} else {
						goto aft2;
					}
				}
aft2:
				for (int xx = 1, yy=1; xx < sx && yy < sy; xx++, yy++) {
					if (y-yy >= 0 && x+xx < sx) {
						if (grid[y-yy][x+yy] == '#') {
							countOcc++;
							goto aft3;
						} else if (grid[y-yy][x+yy] == 'L') {
							goto aft3;
						}
					} else {
						goto aft3;
					}
				}
aft3:
				for (int xx = 1; xx < sx; xx++) {
					if (x+xx < sx) {
						if (grid[y][x+xx] == '#') {
							countOcc++;
							goto aft4;
						} else if (grid[y][x+xx] == 'L') {
							goto aft4;
						}
					} else {
						goto aft4;
					}
				}
aft4:
				for (int xx = 1; xx < sx; xx++) {
					if (x-xx >= 0) {
						if (grid[y][x-xx] == '#') {
							countOcc++;
							goto aft5;
						} else if (grid[y][x-xx] == 'L') {
							goto aft5;
						}
					} else {
						goto aft5;
					}
				}
aft5:
				for (int xx = 1, yy=1; xx < sx && yy < sy; xx++, yy++) {
					if (y+yy < sy && x+xx < sx) {
						if (grid[y+yy][x+xx] == '#') {
							countOcc++;
							goto aft6;
						} else if (grid[y+yy][x+xx] == 'L') {
							goto aft6;
						}
					} else {
						goto aft6;
					}
				}
aft6:
				for (int xx = 1, yy=1; xx < sx && yy < sy; xx++, yy++) {
					if (y+yy < sy && x-xx >= 0) {
						if (grid[y+yy][x-xx] == '#') {
							countOcc++;
							goto aft7;
						} else if (grid[y+yy][x-xx] == 'L') {
							goto aft7;
						}
					} else {
						goto aft7;
					}
				}

aft7:
				for (int yy=1; yy < sy; yy++) {
					if (y+yy < sy) {
						if (grid[y+yy][x] == '#') {
							countOcc++;
							goto aft8;
						} else if (grid[y+yy][x] == 'L') {
							goto aft8;
						}
					} else {
						goto aft8;
					}
				}
aft8:
				if (grid[y][x] == 'L' && countOcc == 0) {
					gridTmp[y][x] = '#';
				} else if (grid[y][x] == '#' && countOcc >= 5) {
					gridTmp[y][x] = 'L';
				}
			}
		}
		//if ( Arrays.deepEquals(gridTmp, grid)) {break;}
		if (memcmp(gridTmp, grid, sizeof(grid)) == 0) {break;}
		//grid = Arrays.stream(gridTmp).map(char[]::clone).toArray(char[][]::new);
		memcpy(grid, gridTmp, sizeof(grid));

	}

	int count = 0;
	for (int yy = 0; yy < sy; yy++) {
		for (int xx = 0; xx < sx; xx++) {
			if (grid[yy][xx] == '#') {
				count++;
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	printf("%d\n", count);
}
