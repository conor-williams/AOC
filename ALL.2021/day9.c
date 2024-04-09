#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *a;
int grid[120][120] = {{-1}};
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day8\n"); fflush(stdout);
        char line1[5000];
	int tot = 0;
	int leny = 0;
	int lenx = 0;
while (1) {
        fgets(line1, 4999, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';

	for (int i = 0; i < strlen(line1); i++) {
		grid[leny][i] = line1[i] - 48;
	}
	leny++;
	lenx = strlen(line1);
}
fclose(a);


	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (x == 0 && y == 0) {
				if (grid[y+1][x] > grid[y][x]  && grid[y][x+1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else if (x == 0 && y == leny-1) {
				if (grid[y-1][x] > grid[y][x]  && grid[y][x+1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else if (x == lenx - 1 && y==0) {
				if (grid[y+1][x] > grid[y][x]  && grid[y][x-1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else if (x == lenx - 1 && y==leny-1) {
				if (grid[y-1][x] > grid[y][x]  && grid[y][x-1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else if (x == 0) {
				if (grid[y+1][x] > grid[y][x] && grid[y-1][x] > grid[y][x] && grid[y][x+1] > grid[y][x] ) { tot+=grid[y][x]+1;}
			} else if (y == 0) {
				if (grid[y+1][x] > grid[y][x] && grid[y][x+1] > grid[y][x] && grid[y][x-1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else if (x == lenx -1) {
				if (grid[y+1][x] > grid[y][x] && grid[y-1][x] > grid[y][x] && grid[y][x-1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else if (y == leny-1) {
				if (grid[y-1][x] > grid[y][x] && grid[y][x+1] > grid[y][x] && grid[y][x-1] > grid[y][x]) { tot+=grid[y][x]+1;}
			} else { //the middle
				if (grid[y+1][x] > grid[y][x] && grid[y-1][x] > grid[y][x] && grid[y][x+1] > grid[y][x] && grid[y][x-1] > grid[y][x]) { tot+= grid[y][x]+1; }
			}
		}
	}
	printf("***tot %d\n", tot);
}
