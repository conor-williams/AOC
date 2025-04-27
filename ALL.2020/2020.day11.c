#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
char grid[102][102];
char gridNew[102][102];
#define getchar()
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2020 Day11 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
	
int leny = 0;
strcpy(grid[0], "....................................................................................................");
leny++;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	grid[leny][0] = '.';
	int i;
	for (i = 0; i < (int)strlen(line1); i++) {
		grid[leny][i+1] = line1[i];
	}
	grid[leny][i+1] = '.'; grid[leny][i+2] = '\0';
	leny++;
}
fclose(a);
	strcpy(grid[leny], "....................................................................................................");
	leny++;
	int lenx = (int)strlen(grid[0]);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			gridNew[y][x] = grid[y][x];
		}
	}

	int prevSeatCount = 0;	
	int seatCount = 0;
next: 
	
	prevSeatCount = seatCount;
	seatCount = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			grid[y][x] = gridNew[y][x];
			if (grid[y][x] == '#') {
				seatCount++;
			}
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n"); getchar();
	if (prevSeatCount == seatCount && seatCount != 0) {
		printf("SAME at %d\n", seatCount);

		fflush(stdout); dup2(fd, 1);
		printf("**ans: %d\n", seatCount); exit(0);
	}
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == 'L' &&
				(grid[y-1][x] == 'L' || grid[y-1][x] == '.') &&
				(grid[y+1][x] == 'L' || grid[y+1][x] == '.') &&
				(grid[y][x+1] == 'L' || grid[y][x+1] == '.') &&
				(grid[y][x-1] == 'L' || grid[y][x-1] == '.') &&
				(grid[y-1][x-1] == 'L' || grid[y-1][x-1] == '.') &&
				(grid[y-1][x+1] == 'L' || grid[y-1][x+1] == '.') &&
				(grid[y+1][x-1] == 'L' || grid[y+1][x-1] == '.') &&
				(grid[y+1][x+1] == 'L' || grid[y+1][x+1] == '.')) {
					gridNew[y][x] = '#';
			} else if (grid[y][x] == '#') {
				int count = 0;
				if (grid[y-1][x] == '#') {
					count++;
				}
				if (grid[y+1][x] == '#') {
					count++;
				}
				if (grid[y][x+1] == '#') {
					count++;
				}
				if (grid[y][x-1] == '#') {
					count++;
				}
				if (grid[y-1][x-1] == '#') {
					count++;
				}
				if (grid[y-1][x+1] == '#') {
					count++;
				}
				if (grid[y+1][x-1] == '#') {
					count++;
				}
				if (grid[y+1][x+1] == '#') {
					count++;
				}
				if (count >= 4) {
					gridNew[y][x] = 'L';
				}
			}
		}
	}
	goto next;
}
