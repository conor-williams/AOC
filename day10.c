#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <map>

#include <unistd.h>

#define getchar()
using namespace std;

#undef _DEBUG_
#define SIZE 400
char line1[SIZE];
unsigned long tot = 0;
#define Y 60000
#define X 60000
#define XAND -50 
#define YAND -150 
#define SCALE 60000

#define UP 30000
struct pos {
	int x1;
	int y1;
	int vx;
	int vy;
	int xs[UP];
	int ys[UP];
};
struct pos posit[500] = {0};
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day10.1\n"); fflush(stdout);

	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		int x1, y1, vx, vy;
		char sx1[10], sy1[10], svx[10], svy[10];
		int ret = sscanf(line1, "position=< %[^,], %[^>]> velocity=< %[^,], %[^>]>", sx1, sy1, svx, svy);
		if (ret != 4) {printf("ERROR"); exit(0);}
		x1 = atoi(sx1); vx = atoi(svx);
		y1 = atoi(sy1); vy = atoi(svy);
		
		//printf("%d: %d %d, %d %d\n", leny, x1, y1, vx, vy);
		
		posit[leny].x1 = XAND + ((double)x1*SCALE/(double)X);// printf("x1 is %d\n", posit[leny].x1);
		posit[leny].y1 = YAND + ((double)y1*SCALE/(double)Y);// printf("y1 is %d\n", posit[leny].y1); //getchar();
		posit[leny].vx = vx;
		posit[leny].vy = vy;
		leny++;
	}
	fclose(a);

	for (int z = 0; z < leny; z++) {
		for (int i = 0; i < UP-2; i++) {
			posit[z].ys[i] = posit[z].y1 + (posit[z].vy*i);
			posit[z].xs[i] = posit[z].x1 + (posit[z].vx*i);
			//if (posit[z].ys[i] < 0) {printf("error1\n");}
			//if (posit[z].xs[i] < 0) {printf("error2\n");}
		}
	}


//	for (int i = 10887; i < UP; i++) {
	map <int, int> countx;
	int boardCon;
	for (int i = 0; i < UP; i++) {
		countx.clear();
		//printf("AGAINTOP? %d:", i);
		for (int z = 0; z < leny; z++) {
			///printf("\x1b[H#");
			//printf("%d \n", posit[z].xs[i]);
			countx[posit[z].ys[i]]++;
			//if (posit[z].xs[i] > sz1) {printf("too big.. \n"); fflush(stdout);exit(0);}
			//if (posit[z].xs[i] < 0) {printf("too small.. \n"); fflush(stdout);exit(0);}
			//countx[posit[z].xs[i]]++;
			if (countx[posit[z].ys[i]] > 40) {
				boardCon = i;
				printf("boardCon is %d\n", boardCon);
				goto after;
			}
			///printf("\x1b[%dB", posit[z].ys[i]); //printf("%d", posit[z].ys[i]); getchar();
			///printf("\x1b[%dC#", posit[z].xs[i]);
//			printf(";%dH#", posit[z].ys[i], posit[z].xs[i]);
		}
		//printf("BOTTOM? %d:", i);
		//printf("\x1b[H#");
		//printf("TOP?:", i);
		//getchar();
		//printf("\x1b[2J");
	}
after:
	printf("after...\n");
	int minX = 999999999;
	int maxX = 0;
	int minY = 999999999;
	int maxY = 0;
	for (int z = 0; z < leny; z++) {
		if (posit[z].xs[boardCon] > maxX) {maxX = posit[z].xs[boardCon];}
		if (posit[z].xs[boardCon] < minX) {minX = posit[z].xs[boardCon];}
		if (posit[z].ys[boardCon] > maxY) {maxY = posit[z].ys[boardCon];}
		if (posit[z].ys[boardCon] < minY) {minY = posit[z].ys[boardCon];}
	}
	printf("%d,%d -> %d,%d\n", minX, minY, maxX, maxY);
	printf("\x1b[2J");
	for (int z = 0; z < leny; z++) {
		printf("\x1b[H");
		printf("\x1b[%dB", posit[z].ys[boardCon]-minY);
		printf("\x1b[%dC#", posit[z].xs[boardCon]-minX);
		//printf("%d\n", posit[z].ys[boardCon]);
		//printf("%d\n", posit[z].xs[boardCon]);
	}
	printf("\n\n\n");
	//printf("**tot %lu\n", tot);
}
			
