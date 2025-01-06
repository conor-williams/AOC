#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 1000
#define PAD 50
#define SX 110
#define getchar()

int grid[SX][SX][SX] = {0};

int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 22.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	char Sxfrom[10], Sxto[10], Syfrom[10], Syto[10], Szfrom[10], Szto[10];
	int xfrom, xto, yfrom, yto, zfrom, zto;
	int off = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);

		off = 0;
		int ret = sscanf(line1, "on x=%[^.]..%[^,],y=%[^.]..%[^,],z=%[^.]..%[^\0]", Sxfrom, Sxto, Syfrom, Syto, Szfrom, Szto);
		if (ret != 6) {
			off = 1;
			sscanf(line1, "off x=%[^.]..%[^,],y=%[^.]..%[^,],z=%[^.]..%[^\0]", Sxfrom, Sxto, Syfrom, Syto, Szfrom, Szto);
		}
		printf("read %s %s %s %s %s %s\n", Sxfrom, Sxto, Syfrom, Syto, Szfrom, Szto); getchar();
		xfrom = atoi(Sxfrom); xto = atoi(Sxto);
		yfrom = atoi(Syfrom); yto = atoi(Syto);
		zfrom = atoi(Szfrom); zto = atoi(Szto);

		xfrom += PAD; xto += PAD; 
		yfrom += PAD; yto += PAD; 
		zfrom += PAD; zto += PAD; 

		assert (xfrom <= xto);
		xfrom = xfrom < 0 ? 0 : xfrom;
		xto = xto < 100 ? xto : 100;
		assert (yfrom <= yto);
		yfrom = yfrom < 0 ? 0 : yfrom;
		yto = yto < 100 ? yto : 100;
		assert (zfrom <= zto);
		zfrom = zfrom < 0 ? 0 : zfrom;
		zto = zto < 100 ? zto : 100;
		for (int z = zfrom; z <= zto; z++) {
			printf("z is %d\n", z);
			for (int y = yfrom; y <= yto; y++) {
				printf("y is %d\n", y);
				for (int x = xfrom; x <= xto; x++) {
					printf("x is %d\n", x); fflush(stdout);

					if (off == 0) {grid[z][y][x] = 1;} else {grid[z][y][x] = 0;}
					printf("after assign...\n"); fflush(stdout);
				}
			}
		}
		leny++;
	}
	fclose(a);
	printf("after load...\n"); getchar();
	int cropFrom = -50 + PAD;
	int cropTo = +50 + PAD;

	int count = 0;
	for (int z = cropFrom; z <= cropTo; z++) {
		for (int y = cropFrom; y <= cropTo; y++) {
			for (int x = cropFrom; x <= cropTo; x++) {
				if (grid[z][y][x] == 1) {
					count++;
				}
			}
		}
	}

	printf("** count %d\n", count);
	dup2(fd, 1);
	printf("**ans: %d\n", count);
}
