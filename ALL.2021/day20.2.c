#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

FILE *a;
#define LINE 1000
char algo[LINE];
#define GX 500
int lenx = 0;
char grid[GX+20][GX+20];
char gridtmp[GX+20][GX+20];

#define PAD 200
#define getchar()
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day20 part2\n"); fflush(stdout);
        char line1[LINE];

	for (int y = 0; y < GX; y++) {
		for (int x = 0; x < GX; x++) {
			grid[y][x] = '.';
			gridtmp[y][x] = '.';
		}
		grid[y][GX] = '\0';
		gridtmp[y][GX] = '\0';
	}
	

int leny = 0;
int imagePos = PAD;

while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);

	if (line1[0] == '\0') {
		continue;		
	} else if (leny == 0) {
		strcpy(algo, line1);
	} else {
		//char line2[GX+30] = "...................."; //PAD
		char line2[GX+30];
		int i;
		for (i = 0; i < PAD; i++) {
			line2[i] = '.';
		}
		line2[i] = '\0';
		
		strcat(line2, line1);
		for (int i = (int)strlen(line2); i < GX; i++) {
			line2[i] = '.';
		}
		
		strcpy(grid[imagePos], line2);
		grid[imagePos][GX] = '\0';
		imagePos++;
	}
	leny++;
}
	
imagePos+= PAD;
lenx = (int)strlen(grid[0]);
leny = imagePos;
printf("lenx: %d\n", lenx); getchar();
fclose(a);


	for (int r = 0; r < 50; r++) {
		for (int y = 1; y < GX-1; y++) {
			for (int x = 1; x < GX-1; x++) {
				int var_bit = 0;
				if (grid[y-1][x-1] == '#') { var_bit |= 1 << 8;} 	
				if (grid[y-1][x] == '#') { var_bit |= 1 << 7;}
				if (grid[y-1][x+1] == '#') { var_bit |= 1 << 6;}
				if (grid[y][x-1] == '#') { var_bit |= 1 << 5;}
				if (grid[y][x] == '#') { var_bit |= 1 << 4;}
				if (grid[y][x+1] == '#') { var_bit |= 1 << 3;}
				if (grid[y+1][x-1] == '#') { var_bit |= 1 << 2;}
				if (grid[y+1][x] == '#') { var_bit |= 1 << 1;}
				if (grid[y+1][x+1] == '#') { var_bit |= 1 << 0;}

				gridtmp[y][x] = algo[var_bit];
				//assert(var_bit < 512);
			}
		}

		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				grid[y][x] = gridtmp[y][x];
			}
		}
	}

	int count = 0;
	for (int y = 50; y < GX-50; y++) {
		for (int x = 50; x < GX-50; x++) {
			printf("%c", grid[y][x]);
			if (grid[y][x] == '#') {
				count++;
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("**count is %d\n", count);

}
