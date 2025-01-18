#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 1000
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define GX 200
char grid[GX][GX];
char gridtmp[GX][GX];

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 25\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	int lenx = (int)strlen(grid[0]);

	printf("Initial state:\n");
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");

	int round = 1;
	while (1) {
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				gridtmp[y][x] = grid[y][x];
			}
		}

		//--e facing
		int found = 0;
		for (int y = leny -1; y>= 0; y--) {
			for (int x = lenx - 1; x >= 1; x--) {
				if (grid[y][x-1] == '>' && grid[y][x] == '.') {
					found = 1;
					gridtmp[y][x-1] = '.'; gridtmp[y][x] = '>';
				}
				if (x == lenx-1 && grid[y][x] == '>' && grid[y][0] == '.') {
					found = 1;
					gridtmp[y][lenx-1] = '.';
					gridtmp[y][0] = '>';
				}

			}
		}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				//printf("%c", gridtmp[y][x]);
				grid[y][x] = gridtmp[y][x];
			}
			//printf("\n");
		}
		//printf("\n");

		//--s facing
		for (int y = leny -1; y>= 1; y--) {
			for (int x = lenx - 1; x >= 0; x--) {
				if (grid[y-1][x] == 'v' && grid[y][x] == '.') {
					found = 1;
					gridtmp[y-1][x] = '.'; gridtmp[y][x] = 'v';
				}
				if (y == leny-1 && grid[y][x] == 'v' && grid[0][x] == '.') {
					found = 1;
					gridtmp[y][x] = '.';
					gridtmp[0][x] = 'v';
				}

			}
		}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				//printf("%c", gridtmp[y][x]);
				grid[y][x] = gridtmp[y][x];
			}
			//printf("\n");
		}
		//printf("\n");

		if (found == 0) {fflush(stdout); dup2(fd, 1); printf("last round %d\n", round); break;}
		printf("After %d step:\n", round);
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				//printf("%c", grid[y][x]);
			}
			printf("\n");
		}
		printf("\n");
		round++;
	}

}
