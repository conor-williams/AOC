#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 1000

#define GX 300
#define GY 20000
#define getchar()
//#define GX 100
//#define GY 100
int grid[GY][GX];
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day17.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	for (int y = 0; y < GY; y++) {
		for (int x = 0; x < GX; x++) {
			grid[y][x] = '.';
		}
	}
	int leny = 0;
	int sx = 0, sy=0;
	int xfrom, xto, yfrom, yto;
	char Sxfrom[10], Sxto[10], Syfrom[10], Syto[10];
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		printf("LINE: %s\n", line1);
		line1[strlen(line1)-1] = '\0';

		//target area: x=150..193, y=-136..-86
		sscanf(line1, "target area: x=%[^.]..%[^,], y=%[^.]..%[^\0]", Sxfrom, Sxto, Syto, Syfrom);
		printf("read %s %s %s %s\n", Sxfrom, Sxto, Syto, Syfrom); getchar();
		xfrom = atoi(Sxfrom);
		xto = atoi(Sxto);
		yfrom = abs(atoi(Syfrom));
		yto = abs(atoi(Syto));

		yfrom+=GY-300;
		yto+=GY-300;
		sy+=GY-300;

		printf("%d -> %d ... %d -> %d\n", xfrom, xto, yfrom, yto);
		leny++;
	}
	fclose(a);
	//int fd = dup(1); close(1);
	for (int y = yfrom; y <= yto ; y++) {
		for (int x = xfrom; x <= xto; x++) {
			grid[y][x] = 'T';
		}
	}

	for (int y = 0; y < GY; y++) {
		for (int x = 0; x < GX; x++) {
			if (x == sx && y == sy) {
				printf("S");
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");

	int maxy = 0;
	int maxsvx, maxsvy;
	int countTot = 0;
	for (int ovx = 2; ovx < 599; ovx++) {
		for (int ovy = -800; ovy < 6000; ovy++) {
			//printf("ovx ovy %d %d\n", ovx, ovy);
			int vx = ovx;
			int vy = ovy;
			int x1 = sx;
			int y1 = sy;
			int lx[100] = {0};
			int ly[100] = {0};
			int grav;
			if (ovy < 0) {grav = 1;} else {grav = 0;}
			int interimmaxy = 0;
			int t = 0;
			while (1) {
				//for (int t = 0; t < 1000; t++) {
				//printf("vx is %d\n", vx); printf("vy is %d\n", vy); 
				x1 += vx; vx--;
				if (vx < 0) {vx = 0;}
				int height = 0;
				if (vy == 0) {height = sy - y1;}
				y1 -= vy; vy--;

				if (x1 < 0 || y1 < 0) {break;}

				/*
				   lx[t] = x1;
				   ly[t] = y1;
				   for (int y = 0; y < GY; y++) {
				   for (int x = 0; x < GX; x++) {
				   int found = 0;
				   for (int i = 0; i <= t; i++) {
				   if (x == lx[i] && y == ly[i]) {
				   found = 1;
				   printf("#");
				   break;
				   }	
				   }
				   if (found == 0) {
				   if (x == sx && y == sy) {
				   printf("S");
				   } else {
				   printf("%c", grid[y][x]);
				   }
				   }
				   }
				   printf("\n");
				   }
				   printf("\n");
				   */

				//int height = 0; if (y1 < sy) {height = sy - y1;}

				if (height > interimmaxy) {/*printf("interimmaxy %d\n", interimmaxy); */interimmaxy = height;}
				//printf("sy is %d, y1 is %d\n", sy, y1);
				//printf("height is %d\n", height); getchar();
				if (x1 >= xfrom && x1 <= xto && y1 >= yfrom && y1 <= yto) {
					printf("yay height is %d\n", height);
					printf("yay...---------------\n");
					if (interimmaxy > maxy) {maxsvx = ovx; maxsvy = ovy; maxy = interimmaxy;}
					countTot++;
					break;
				}
				if (x1 > xto) {
					printf("out but height is %d\n", height);
					//if (height > 4560 && height < 4590) {printf("height %d\n", height);}
					printf("out xto------------------\n"); break;
				}
				if (y1 > yto) {
					printf("out but height is %d\n", height);
					//if (height > 4560 && height < 4590) {printf("height %d\n", height);}
					printf("out yfrom-----------------\n"); break;
				}
			}
			t++;
			}
		}
		printf("**countTot is  %d\n", countTot);
		fflush(stdout); dup2(fd,1);
		printf("**ans: %d\n", countTot);
		exit(0);
	}

	/*
	   target area: x=20..30, y=-10..-5
	   */
