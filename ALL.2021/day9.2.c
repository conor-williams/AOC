#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

struct xy {
	int x;
	int y;
};
struct xy Q[1000];
int Qpos = 0;
FILE *a;
int grid[120][120] = {{-1}};
int gridAlready[120][120] = {{-1}};
int basinSize = 0;
int basinSizesPos = 0;
int basinSizes[1000];
void next(int x, int y);
int check(int x, int y, int x1, int y1);
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day9.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

        char line1[5000];
	int tot = 0;
	int leny = 0;
	int lenx = 0;
while (1) {
        fgets(line1, 4999, a);
        if (feof(a)) break;
        line1[(int)strlen(line1)-1] = '\0';

	if (leny == 0) {
		for (int i = 0; i < (int)strlen(line1)+2; i++) {
			grid[leny][i] = '9' - 48;
		}
		leny++;
	}
	grid[leny][0] = '9' -48;
	for (int i = 0; i < (int)strlen(line1)+1; i++) {
		grid[leny][i+1] = line1[i] - 48;
	}
	grid[leny][(int)strlen(line1)+1] = '9' -48;
	leny++;
}
fclose(a);
	lenx = (int)strlen(line1)+2;
	for (int i = 0; i < (int)strlen(line1)+2; i++) {
		grid[leny][i] = '9' - 48;
	}
	leny++;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%d", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n"); getchar();


	tot = 0;
	basinSizesPos = 0;
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			
			if (grid[y+1][x] > grid[y][x] && grid[y-1][x] > grid[y][x] && grid[y][x+1] > grid[y][x] && grid[y][x-1] > grid[y][x]) {
				basinSize = 1;
				for (int y1 = 0; y1 < leny; y1++) {
					for (int x1 = 0; x1 < lenx; x1++) {
						gridAlready[y1][x1] = -1;
					}
				}
				gridAlready[y][x] = 1;
				Qpos = 0;
				next(x, y);
				for (int i = 0; i < Qpos; i++) {
					if (Q[i].x == -1) {continue;}
					next(Q[i].x, Q[i].y);
					Q[i].x = -1; Q[i].y = -1;
				}
				printf("basinSize is %d\n", basinSize);
				basinSizes[basinSizesPos] = basinSize; basinSizesPos++;
			}
		}
	}
	for (int i = 0; i < basinSizesPos; i++) {
		printf("%d: %d\n", i, basinSizes[i]);
	}
	sort(basinSizes, basinSizes+basinSizesPos);
	
	printf("***MUL %d\n", basinSizes[basinSizesPos-1]*basinSizes[basinSizesPos-2]*basinSizes[basinSizesPos-3]);
	printf("***tot %d\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", basinSizes[basinSizesPos-1]*basinSizes[basinSizesPos-2]*basinSizes[basinSizesPos-3]);
}

int check(int x, int y, int x1, int y1) {
	if (gridAlready[y1][x1] != 1 && grid[y1][x1] != 9) {
		if (grid[y1][x1] > grid[y][x]) { 
			gridAlready[y1][x1] = 1;
			basinSize++;
			return 1;
		}
	}
	//gridAlready[y1][x1] = 1;
	return 0;
		
}
void next(int x, int y) {
	gridAlready[y][x] = 1;
	if (check(x, y, x, y+1) == 1) { Q[Qpos].x = x;   Q[Qpos].y = y+1; Qpos++;}
	if (check(x, y, x, y-1) == 1) { Q[Qpos].x = x;   Q[Qpos].y = y-1; Qpos++;}
	if (check(x, y, x+1, y) == 1) { Q[Qpos].x = x+1; Q[Qpos].y = y;   Qpos++;}
	if (check(x, y, x-1, y) == 1) { Q[Qpos].x = x-1; Q[Qpos].y = y;   Qpos++;}
}
