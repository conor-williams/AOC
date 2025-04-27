#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define getchar()
#define LINE 1000
#define GX 105
int grid[GX*5][GX*5];
int minPath = 99999;
int already[GX*5][GX*5] = {0};
void next(int x, int y, int path, int dx, int dy);
int lenx = 0;
int leny = 0;
struct al_s {
	int already[GX*5][GX*5];
};
void buildNewGrid();

int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day15.2\n"); fflush(stdout);
	printf("	Expand the stack (deep recursion)\n");
	printf("	SLOW ~1.5mins\n");

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	lenx = 0;
	leny = 0;
	int once = 1;
	while (1) {
		fgets(line1, LINE-1, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		if (once == 1) {
			lenx = (int)strlen(line1);
			once = 0;
		}
		for (int i = 0; i < lenx; i++) {
			grid[leny][i] = line1[i] - 48;
		}

		leny++;
	}
	fclose(a);

	buildNewGrid();
	int dx = lenx - 1;
	int dy = leny - 1;
	int sx = 0, sy = 0;

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%d", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");

	printf("lenx: %d -- leny: %d\n", lenx, leny);
	printf("sx: %d -- sy: %d --- dx: %d -- dy: %d\n", sx, sy, dx, dy);
	next(0, 0, 0, dx, dy);
	printf("**minPath: %d\n", minPath);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minPath);
}

void buildNewGrid() {
	//toprow...
	for (int xx = 1; xx < 5; xx++) {
		//
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				int val = grid[y][x]+xx;
				if (val >= 10) {
					val++;
					val = val % 10;
				}
				grid[y][(xx*lenx)+x] = val;
			}
		}
	}

	for (int yy = 1; yy < 5; yy++) {
	for (int xx = 0; xx < 5; xx++) {
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				int val = grid[y][x]+(xx+yy);
				if (val >= 10) {
					val++;
					val %= 10;
				}
				grid[(yy*leny)+y][(xx*lenx)+x] = val;
			}
		}
	}
	}

	lenx *= 5; leny *= 5;
	for (int y = 0; y < leny; y++) {
		grid[y][lenx] = '\0';
	}
	printf("built grid..\n");
}


void next(int x, int y, int path, int dx, int dy) {
	if (path >= minPath) {return;}
	if (x == dx && y == dy) {
		printf("path is %d\n", path);
		if (path < minPath) {
			minPath = path;
		}
		return;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		if (y-1 >=0) {next(x, y-1, path+grid[y-1][x], dx, dy);}
		if (x+1 < lenx) {next(x+1, y, path+grid[y][x+1], dx, dy);}
		if (y+1 < leny) {next(x, y+1, path+grid[y+1][x], dx, dy);}
		if (x-1 >= 0) {next(x-1, y, path+grid[y][x-1], dx, dy);}
	}
}

















/*
   if (already[y][x] == 0 || path < already[y][x]) {
   already[y][x] = 1;
   int al1[GX][GX] = {0};
   for (int y = 0; y < GX; y++) {
   for (int x = 0; x < GX; x++) {
   al1[y][x] = already[y][x];
   }
   }
   if (y-1 >=0) {next(x, y-1, path+grid[y-1][x], dx, dy, al1);}
   int al2[GX][GX] = {0};
   for (int y = 0; y < GX; y++) {
   for (int x = 0; x < GX; x++) {
   al2[y][x] = already[y][x];
   }
   }
   if (x+1 < lenx) {next(x+1, y, path+grid[y][x+1], dx, dy, al2);}
   int al3[GX][GX] = {0};
   for (int y = 0; y < GX; y++) {
   for (int x = 0; x < GX; x++) {
   al3[y][x] = already[y][x];
   }
   }
   if (y+1 < leny) {next(x, y+1, path+grid[y+1][x], dx, dy, al3);}
   int al4[GX][GX] = {0};
   for (int y = 0; y < GX; y++) {
   for (int x = 0; x < GX; x++) {
   al4[y][x] = already[y][x];
   }
   }
   if (x-1 >= 0) {next(x-1, y, path+grid[y][x-1], dx, dy, al4);}
   }
   */
