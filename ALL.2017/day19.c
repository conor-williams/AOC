#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 400
char line1[SIZE];
char grid[400][400];
int already[400][400] = {0};
void next(int x, int y, char DIR, int frX, int frY);
int leny = 0;
int maxX = 0;
char ANS[2000];
char ANS22[1500];
#define getchar()
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day19.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);


while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(grid[leny], line1);
	leny++;
	if ((int)strlen(line1) > maxX) {maxX = (int)strlen(line1);}
}
fclose(a);

	int startX; int startY;
	int y = 0;
	for (int x = 0; x < (int)strlen(grid[0]); x++) {
		if (grid[y][x] == '|') {
			startX = x;
			startY = y;
			break;
		}
	}
	printf("%d %d\n", startX, startY);
	already[startY][startX] = 1;
	next(startX, startY+1, 'D', startX, startY);
			
	fflush(stdout);
	fflush(stdout); dup2(fd, 1);
	printf("**ANS [ %s ] \n", ANS);
return 0;
}
int ind = 0;
void next(int x, int y, char DIR, int frX, int frY) {

	ind++;
	already[y][x] = 1;
	printf("ind: %d\n", ind);
	printf("[%c]", grid[y][x]);
	switch(grid[y][x]) {
		case '|':
			if (/*grid[frY][frX] == '-' &&*/ (DIR == 'L' || DIR == 'R')) {
				if (DIR == 'L') {
					next(x-1, y, 'L', x, y);
				} else if (DIR == 'R') {
					next(x+1, y, 'R', x, y);
				}
			} else if (DIR == 'D') {
				next(x, y+1, 'D', x, y);
			} else {
				next(x, y-1, 'U', x, y);
			}
			break;
		case '+':
				printf("got plus %c\n", DIR);
			     if (DIR == 'D' && grid[y][x+1] != ' ') {printf("going R\n"); next(x+1, y, 'R', x, y);}
			else if (DIR == 'D' && grid[y][x-1] != ' ') {printf("going L\n"); next(x-1, y, 'L', x, y);}
			else if (DIR == 'U' && grid[y][x+1] != ' ') {printf("going R\n"); next(x+1, y, 'R', x, y);}
			else if (DIR == 'U' && grid[y][x-1] != ' ') {printf("going L\n"); next(x-1, y, 'L', x, y);}
			else if (DIR == 'R' && grid[y-1][x] != ' ') {printf("going U\n"); next(x, y-1, 'U', x, y);}
			else if (DIR == 'R' && grid[y+1][x] != ' ') {printf("going D\n"); next(x, y+1, 'D', x, y);}
			else if (DIR == 'L' && grid[y-1][x] != ' ') {printf("going U\n"); next(x, y-1, 'U', x, y);}
			else if (DIR == 'L' && grid[y+1][x] != ' ') {printf("going D\n"); next(x, y+1, 'D', x, y);}
			break;
		case '-':
			if (/*grid[frY][frX] == '|' && */(DIR == 'U' || DIR == 'D')) {
				if (DIR == 'U') {
					printf("going up");
					next(x, y-1, 'U', x, y);
				} else if (DIR == 'D') {
					printf("going down");
					next(x, y+1, 'D', x, y);
				}
			} else if (DIR == 'R') {next(x+1, y, 'R', x, y);
			} else {next(x-1, y, 'L', x, y);}
			break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			printf("[%c]", grid[y][x]); getchar();
			strcpy(ANS22, ANS);
			sprintf(ANS, "%s%c", ANS22, grid[y][x]);
			printf("Partial [ %s ]\n", ANS);
			if (DIR == 'R') {
				if (x+1 < (int)strlen(grid[y])) {
					printf("g right (let)\n");
					next(x+1, y, 'R', x, y);
				}
			} else if (DIR == 'L') {
					printf("g left (let)\n");
				if (x-1 >= 0) {
					next(x-1, y, 'L', x, y);
				}
			} else if (DIR == 'U') {
				if (y-1 >=0) {
					printf("g up (let)\n");
					next(x, y-1, 'U', x, y);
				}
			} else if (DIR == 'D') {
				if (y+1 < leny) {
					printf("g down (let)\n");
					next(x, y+1, 'D', x, y);
				}
			}
				
			break;
	}
	ind--;
}
