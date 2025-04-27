#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 20000
char line1[SIZE];
#define ST 1000
char grid[ST*2+10][ST*2+10];
char gridtmp[ST*2+10][ST*2+10];
int startx = ST;
int starty = ST;
void next(int x, int y, int dir);
int leny = 0;
void expandgrid();
int fd;
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day22.1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);

while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(gridtmp[leny], line1);
	leny++;
}
fclose(a);
	expandgrid();
	next(ST, ST, 0);

	fflush(stdout); dup2(fd, 1);
	printf("***tot is ^^ [%d]\n", tot);
	return 0;
}
void expandgrid() {
	for (int y=0; y < (ST - leny/2); y++) {
		for (int x = 0; x < ST*2; x++) {
			grid[y][x] = '.';
		}
	}
	for (int y= (ST + leny/2); y< ST*2; y++) {
		for (int x = 0; x < ST*2; x++) {
			grid[y][x] = '.';
		}
	}
	//printf("GRID1: \n"); for (int y = 0; y < ST*2; y++) { printf("%s\n", grid[y]); } printf("\n"); getchar();
	int stx1 = ST - (int)strlen(gridtmp[0])/2;
	int stx2 = ST + (int)strlen(gridtmp[0])/2 + 1;
	for (int y=(ST -leny/2); y <= (ST+leny/2); y++) {
		for (int x = 0; x < stx1; x++) {
			grid[y][x] = '.';
		}
		for (int x = stx1; x < stx2; x++) {
			grid[y][x] = gridtmp[y-(ST-leny/2)][x-stx1];
		}
		for (int x = stx2; x < 2*ST; x++) {
			grid[y][x] = '.';
		}
		
	}
	
	//printf("GRID: \n"); for (int y = 0; y < ST*2; y++) { printf("%s\n", grid[y]); } printf("\n"); getchar();
}

int ind = 0;
void next(int x, int y, int DIR) {
	ind++;
	if (ind == 10000) {
		
		fflush(stdout); dup2(fd, 1);
		printf("**tot = %d\n", tot);
		exit(0);
	}
	//printf("GRID1: \n"); for (int y1 = 0; y1 < ST*2; y1++) { for (int x1 = 0; x1 < ST*2; x1++) { if (y1 == y && x1==x) { printf("S"); } else { printf("%c", grid[y1][x1]); } } printf("\n"); } printf("\n"); getchar();
	if (x < 0) {printf("ERR MX\n"); exit(0);}
	if (y < 0) {printf("ERR MY\n"); exit(0);}
	if (x >= ST*2) {printf("ERR BX\n"); exit(0);}
	if (y >= ST*2) {printf("ERR BY\n"); exit(0);}
	int newdir; int newx, newy;
	if (grid[y][x] == '#') {
		grid[y][x] = '.';
		newdir = (DIR+1)%4;
		switch (newdir) {
			case 0:
				newx = x;
				newy = y-1;
				break;
			case 1:
				newx = x+1;
				newy = y;
				break;
			case 2:
				newx = x;
				newy = y+1;
				break;
			case 3:
				newx = x-1;
				newy = y;
				break;
		}
	} else {
		grid[y][x] = '#';
		tot++;
		newdir = ((DIR-1)+4)%4;
		switch (newdir) {
			case 0:
				newx = x;
				newy = y-1;
				break;
			case 1:
				newx = x+1;
				newy = y;
				break;
			case 2:
				newx = x;
				newy = y+1;
				break;
			case 3:
				newx = x-1;
				newy = y;
				break;
		}
	}
	next(newx, newy, newdir);
}
