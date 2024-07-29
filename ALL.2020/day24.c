#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

int LINE = 1000;

#define GX 400

int leny = 0;
int grid[GX][GX] = {0}; //0 white // 1 black
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day24\n"); fflush(stdout);
        char line1[LINE];

while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);

	int len = (int)strlen(line1);
	int x1 = GX/2;
	int y1 = GX/2;
	for (int i = 0; i < len; i++) {
		if (i != len-1 && line1[i] == 'n' && line1[i+1] == 'e') {
			//printf("ne\n");
			x1++;
			y1--;
			i++;
		} else if (i!=len-1 && line1[i] == 'n' && line1[i+1] == 'w') {
			//printf("nw\n");
			y1--;
			i++;
		} else if (i!=len-1 && line1[i] == 's' && line1[i+1] == 'e') {
			///printf("se\n");
			y1++;
			i++;
		} else if (i!=len-1 && line1[i] == 's' && line1[i+1] == 'w') {
			///printf("sw\n");
			x1--;
			y1++;
			i++;
		} else if (line1[i] == 'e') {
			//printf("e\n");
			x1++;
		} else if (line1[i] == 'w') {
			///printf("w\n");
			x1--;
		} 
	}
	if (grid[y1][x1] == 0) {grid[y1][x1] = 1;} else if (grid[y1][x1] == 1) {grid[y1][x1] = 0;}
	leny++;
}
	int count = 0;
	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			if (grid[y][x] == 1) {
				count++;
			}
		}
	}
	printf("**ans %d\n", count);
}

