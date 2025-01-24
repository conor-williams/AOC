#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
#define LINE 1000
#define getchar()

#define GX 10
int grid[GX][GX] = {0};
int gridtmp[GX][GX] = {0};
int gridfl[GX][GX] = {0};
int leny = 0, lenx = 0;
int ROUNDS;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day11.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	//if (argc == 3) {ROUNDS = atoi(argv[2]);}
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		for (int i = 0; i < (int)strlen(line1); i++) {
			grid[leny][i] = line1[i]-48;
		}

		leny++;
	}
	fclose(a);
	lenx = (int)strlen(line1);


	printf("Before any steps:\n");
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%d", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n\n"); getchar();

	//int totFlashes = 0;
	int var_ans;
	for (int r = 1; ; r++) {
		int flashesPerRound = 0;
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				gridtmp[y][x] = grid[y][x] + 1;
			}
		}

reflash:
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (gridtmp[y][x] > 9 && gridfl[y][x] == 0) {
					gridfl[y][x] = 1;
					flashesPerRound++;
					//totFlashes++;
					if (y-1 >= 0) {gridtmp[y-1][x]++;}
					if (y-1 >= 0 && x+1 < lenx) {gridtmp[y-1][x+1]++;}
					if (x+1 < lenx) {gridtmp[y][x+1]++;}
					if (x+1 < lenx && y+1 < leny) {gridtmp[y+1][x+1]++;}
					if (y+1 < leny) {gridtmp[y+1][x]++;}
					if (y+1 < leny && x-1 >= 0) {gridtmp[y+1][x-1]++;}
					if (x-1 >= 0) {gridtmp[y][x-1]++;}
					if (y-1 >= 0 && x-1 >= 0) {gridtmp[y-1][x-1]++;}
					gridtmp[y][x] = 0;
				}
			}
		}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (gridtmp[y][x] > 9 && gridfl[y][x] == 0) {
					goto reflash;
				}
			}
		}
		if (flashesPerRound == leny*lenx) {
			var_ans = r;
			fflush(stdout); dup2(fd, 1);
			printf("going to end...\n");
			close(1);
			goto end;
		}

		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (gridfl[y][x] == 1) {
					grid[y][x] = 0;
					gridfl[y][x] = 0;
				} else {
					grid[y][x] = gridtmp[y][x];			
				}
			}
		}
		printf("After step %d:\n", r);
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				printf("%d", grid[y][x]);
			}
			printf("\n");
		}
		printf("\n"); getchar();
	}
	//printf("tot flashes is %d\n", totFlashes);
end:

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", var_ans);

}
