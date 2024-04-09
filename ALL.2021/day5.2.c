#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *a;
#define getchar()
int board[1000][1000] = {0};
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];

int maxx = 0; int maxy = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int x1, x2, y1, y2;
	sscanf(line1, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
	printf("got %d %d -> %d %d\n", x1, y1, x2, y2);
	if (x2>maxx) {maxx=x2;}
	if (y2>maxy) {maxy=y2;}
	if (x1>maxx) {maxx=x1;}
	if (y1>maxy) {maxy=y1;}

	if (x1 == x2 || y1 == y2) {

		if (x1 == x2) {
			int start = y2>y1?y1:y2;
			int end =   y2>y1?y2:y1;
			for (int y = start; y <= end; y++) {
				board[y][x1]++;
			}
		} else if (y1 == y2) {
			int start = x2>x1?x1:x2;
			int end =   x2>x1?x2:x1;
			for (int x = start; x <= end; x++) {
				board[y1][x]++;
			}
		}

	} else if (abs(x2-x1) == abs(y2-y1)) {
		//printf("got diag %d %d -> %d %d\n", x1, y1, x2, y2); getchar();
		int y, ystart;
		int start = x2 > x1? x1: x2;
		if (x1 == start) {ystart = y1;} else {ystart = y2;}
		int end = x2 > x1? x2: x1;
		///printf("MOD: got diag %d %d -> %d \n", start, ystart, end); getchar();
		y = ystart;
		for (int x = start; x <= end; x++) {
			if (y == 0 && x == 0 ) {
				//printf("zero zero\n"); getchar();
			}
			board[y][x]++;	
			if (ystart  == y1) {
				y1 > y2? y--: y++;
			} else if (ystart == y2) {
				y2 > y1? y--: y++;
			}
		}
	}
}
fclose(a);
printf("***maxx %d\n", maxx);
printf("***maxy %d\n", maxy); getchar();
int count = 0;
for (int x = 0; x <= maxx; x++) {
	for (int y = 0; y <= maxy; y++) {
		if (board[y][x] > 1) {
			count++;
		}
	}
}
printf("***count %d\n", count); getchar();
#ifdef _DEBUG_
for (int y = 0; y <= maxy; y++) {
	for (int x = 0; x <= maxx; x++) {
		printf("%d", board[y][x]);
	}
	printf("\n");
}
printf("\n");
#endif
}
