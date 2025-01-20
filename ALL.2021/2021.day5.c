#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
int board[1000][1000] = {0};
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day5 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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
		if (x1 > x2) {int tmp = x2; x2 = x1; x1 = tmp;}
		if (y1 > y2) {int tmp = y2; y2 = y1; y1 = tmp;}
		if (x2 > maxx) {maxx=x2;} if (y2>maxy) {maxy=y2;}
		if (x1 == x2 || y1 == y2) {
			for (int x = x1; x <= x2; x++) {
				for (int y = y1; y <= y2; y++) {
					board[y][x]++;
					if (y == 9 && x==0) {printf("her1...\n"); printf("%d\n", board[y][x]);}
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

	printf("***count %d\n", count);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}
