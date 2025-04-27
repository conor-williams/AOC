#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 1000
char algo[LINE];
#define GX 200
int lenx = 0;
char grid[GX+20][GX+20];
char grid3[GX+20][GX+20];
char gridtmp[GX+20][GX+20];

#define PAD 20
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day20.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			grid[y][x] = '.';
			gridtmp[y][x] = '.';
		}
		grid[y][GX] = '\0';
		gridtmp[y][GX] = '\0';
	}


	int leny = 0;
	int imagePos = PAD;

	int g3co = 0;
	int numlines = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			continue;		
		} else if (leny == 0) {
			strcpy(algo, line1);
		} else {
			strcpy(grid3[g3co++], line1);
			char line2[GX+30] = "...................."; //PAD
			strcat(line2, line1);
			for (int i = (int)strlen(line2); i < GX; i++) {
				line2[i] = '.';
			}
			//strcat(line2, "..........");

			strcpy(grid[imagePos], line2);
			grid[imagePos][GX] = '\0';
			imagePos++;
			numlines++;
		}
		leny++;
	}
	int co3 = 0;
	for (int y = 0; y < g3co; y++) {
		for (int x = 0; x < (int)strlen(line1); x++) {
			if (grid3[y][x] == '#') {
				co3++;
			}
		}
	}

	imagePos+= PAD;
	lenx = (int)strlen(grid[0]);
	leny = imagePos;
	printf("lenx: %d\n", lenx); getchar();
	fclose(a);
	printf("GRID:\n");
	for (int i = 0; i < leny; i++) {
		printf("%s\n", grid[i]);
	} getchar();

	int count1 = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			gridtmp[y][x] = grid[y][x];
			if (gridtmp[y][x] == '#') {
				count1++;
			}
		}
	}

	printf("count1 is %d\n", count1); getchar();
	assert(count1 == co3);
	{
		int minx = 9999;
		int maxx = 0;
		int miny = 9999;
		int maxy = 0;
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (grid[y][x] == '#') {
					if (x > maxx) {maxx = x;}
					if (y > maxy) {maxy = y;}
					if (x < minx) {minx = x;}
					if (y < miny) {miny = y;}
				}
			}
		}
		printf("**minx: %d\n", minx);
		printf("**miny: %d\n", miny); getchar();

	}

	for (int r = 0; r < 2; r++) {
		int starty, endy;
		int startx, endx;
		if (r == 0) {
			starty = PAD-1; endy = starty + numlines+2;
			startx = PAD-1; endx = startx + (int)strlen(line1)+2;
			printf("First Round: %d %d -- %d %d\n", starty, endy, startx, endx); getchar();
		} else if (r == 1) {
			starty--; endy++;
			startx--; endx++;
			printf("Second Round: %d %d -- %d %d\n", starty, endy, startx, endx); getchar();
		} 

		if (r == 0) {
			int minx = 9999;
			int maxx = 0;
			int miny = 9999;
			int maxy = 0;
			for (int y = 0; y < leny; y++) {
				for (int x = 0; x < lenx; x++) {
					if (grid[y][x] == '#') {
						if (x > maxx) {maxx = x;}
						if (y > maxy) {maxy = y;}
						if (x < minx) {minx = x;}
						if (y < miny) {miny = y;}
					}
				}
			}
			printf("**minx: %d\n", minx);
			printf("**miny: %d\n", miny); getchar();
			assert(minx-1 == startx); assert(maxx+2 == endx); assert(miny-1 == starty); assert(maxy+2 == endy);

			startx = minx-1; endx = maxx+2; starty = miny-1; endy = maxy+2;

		} 
		/*
		   for (int y = starty; y < endy; y++) {
		   for (int x = startx; x < endx; x++) {
		   */
		for (int y = 1; y < GX; y++) {
			for (int x = 1; x < GX; x++) {
				int var_bit = 0;
				if (grid[y-1][x-1] == '#') { var_bit |= 1 << 8;} 	
				if (grid[y-1][x] == '#') { var_bit |= 1 << 7;}
				if (grid[y-1][x+1] == '#') { var_bit |= 1 << 6;}
				if (grid[y][x-1] == '#') { var_bit |= 1 << 5;}
				if (grid[y][x] == '#') { var_bit |= 1 << 4;}
				if (grid[y][x+1] == '#') { var_bit |= 1 << 3;}
				if (grid[y+1][x-1] == '#') { var_bit |= 1 << 2;}
				if (grid[y+1][x] == '#') { var_bit |= 1 << 1;}
				if (grid[y+1][x+1] == '#') { var_bit |= 1 << 0;}

				/*
				   if (i % 2 == 1 && (x <= minX + 5 || x >= maxX - 5 || y <= minY + 5 || y >= maxY - 5)) {
				   newNodes.put(x + "," + y, new Node(x, y, '.'));
				   } else {
				   newNodes.put(x + "," + y, new Node(x, y, imageEnhancementAlgorithm.charAt(decimalPosition)));
				   }
				   */
				gridtmp[y][x] = algo[var_bit];
				/*
				   assert(var_bit < 512);
				   if (var_bit == 0) {printf("var_bit: %d (x:%d y:%d)\n", var_bit, x, y);}
				   if (r == 0 ) {
				   if (var_bit == 0 && (y <= starty)) {
				   gridtmp[y][x] = algo[var_bit];
				   } else if (var_bit == 0 && (x <= startx)) {
				   gridtmp[y][x] = algo[var_bit];
				   } else if (var_bit == 0 && (y >= endy-1)) {
				   gridtmp[y][x] = algo[var_bit];
				   } else if (var_bit == 0 && (x >= endx-1)) {
				   gridtmp[y][x] = algo[var_bit];
				   } else {
				   gridtmp[y][x] = algo[var_bit];
				   }
				   } else if (r == 1) {
				   if (var_bit == 0 && (y <= starty+1)) {
				   gridtmp[y][x] = '.';
				   } else if (var_bit == 0 && (x <= startx+1)) {
				   gridtmp[y][x] = '.';
				   } else if (var_bit == 0 && (y >= endy-2)) {
				   gridtmp[y][x] = '.';
				   } else if (var_bit == 0 && (x >= endx-2)) {
				   gridtmp[y][x] = '.';
				   } else {
				   gridtmp[y][x] = algo[var_bit];
				   }
				   } else {
				   gridtmp[y][x] = algo[var_bit];
				   }
				   */
				if (x == 22 && y == 22) {printf("var_bit is %d\n", var_bit);}
				if (x == 22 && y == 22) {printf("g is %c\n", gridtmp[y][x]);}
			}
		}

		{
			int minx = 9999;
			int miny = 9999;
			for (int y = 0; y < leny; y++) {
				for (int x = 0; x < lenx; x++) {
					if (grid[y][x] == '#') {
						if (x < minx) {minx = x;}
						if (y < miny) {miny = x;}
					}
				}
			}
			printf("**minx: %d\n", minx);
			printf("**miny: %d\n", miny); getchar();

		}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				grid[y][x] = gridtmp[y][x];
			}
		}
		printf("GRID:\n");
		for (int i = 0; i < leny; i++) {
			printf("%s\n", grid[i]);
		} getchar();
	}

	int count = 0;
	for (int y = 5; y < leny-5; y++) {
		for (int x = 5; x < lenx-5; x++) {
			if (grid[y][x] == '#') {
				count++;
			}
		}
	}

	printf("**count is %d\n", count);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);

}
