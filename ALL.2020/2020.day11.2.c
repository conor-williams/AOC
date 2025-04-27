#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
char grid[104][104];
char gridNew[104][104];
#define getchar()
int LENW = 98;
int LENH = 100;
int LEN = 100;
int main(int argc, char **argv)
{
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2020 Day11 part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
	
int leny = 0;
for (int k = 0; k < LENW; k++) {
	grid[leny][k] = '.';
}
grid[leny][LENW] = '\0';
printf("%s\n", grid[leny]); getchar();
leny++;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	grid[leny][0] = '.';
	int i;
	printf("strlen(line1) is %d\n", (int)strlen(line1));
	for (i = 0; i < (int)strlen(line1); i++) {
		grid[leny][i+1] = line1[i];
	}
	grid[leny][i+1] = '.'; grid[leny][i+2] = '\0';
	printf("i+1 is %d\n", i+1);
	printf("i+2 is %d\n", i+2); getchar();
	leny++;
}
fclose(a);
for (int l = 0; l < LENW; l++) {
	grid[leny][l] = '.';
}
grid[leny][LENW] = '\0';
	leny++;
	int lenx = (int)strlen(grid[0]);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			gridNew[y][x] = grid[y][x];
		}
		gridNew[y][LENW] = '\0';
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
		printf("**ans: %d\n", seatCount);
		exit(0);
	}
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == 'L') {
				for (int n = 1; n < LEN; n++) {
					if (y-n > 0) {
						if (grid[y-n][x] == '.') {
						} else if (grid[y-n][x] == 'L') {goto next1;
						} else {goto no;}
					}
				}
next1:
				for (int n = 1; n < LEN; n++) {
					if (y+n < leny) {
						if (grid[y+n][x] == '.') {
						} else if (grid[y+n][x] == 'L') {goto next2;
						} else {goto no;}
					}
				}
next2:
				for (int n = 1; n < LEN; n++) {
					if (x+n < lenx) {
						if (grid[y][x+n] == '.') {
						} else if (grid[y][x+n] == 'L') {goto next3;
						} else {goto no;}
					}
				}
next3:
				for (int n = 1; n < LEN; n++) {
					if (x-n > 0) {
						if (grid[y][x-n] == '.') {
						} else if (grid[y][x-n] == 'L') {goto next4;
						} else {goto no;}
					}
				}
next4:
				for (int n = 1; n < LEN; n++) {
					if (x-n > 0 && y-n > 0) {
						if (grid[y-n][x-n] == '.') {
						} else if (grid[y-n][x-n] == 'L') {goto next5;
						} else {goto no;}
					}
				}
next5:
				for (int n = 1; n < LEN; n++) {
					if (x+n < lenx && y-n > 0) {
						if (grid[y-n][x+n] == '.') {
						} else if (grid[y-n][x+n] == 'L') {goto next6;
						} else {goto no;}
					}
				}
next6:
				for (int n = 1; n < LEN; n++) {
					if (x-n > 0  && y+n <leny) {
						if (grid[y+n][x-n] == '.') {
						} else if (grid[y+n][x-n] == 'L') {goto next7;
						} else {goto no;}
					}
				}
next7:
				for (int n = 1; n < LEN; n++) {
					if (x+n < lenx && y+n < leny) {
						if (grid[y+n][x+n] == '.') {
						} else if (grid[y+n][x+n] == 'L') {goto next8;
						} else {goto no;}
					}
				}
next8:
				gridNew[y][x] = '#';
no:
				continue;
			} else if (grid[y][x] == '#') {
				int count = 0;
				for (int n = 1; n < LEN; n++) {
					if (y-n > 0) {
						if (grid[y-n][x] == '#') {
							goto n1b;
						} else if (grid[y-n][x] == 'L') {goto n1;
						} else {continue;}
					} else {goto n1;}
				}
n1b:
				if (x==1 && y==1) {printf("incr1 count\n");}
				count++;
n1:
				for (int n = 1; n < LEN; n++) {
					if (y+n < leny) {
						if (grid[y+n][x] == '#') {
							goto n2b;
						} else if (grid[y+n][x] == 'L') {goto n2;
						} else {continue;}
					} else {goto n2;}
				}
n2b:
				if (x==1 && y==1) {printf("incr2 count\n");}
				count++;
n2:
				for (int n = 1; n < LEN; n++) {
					if (x+n < lenx) {
						if (grid[y][x+n] == '#') {
							goto n3b;
						} else if (grid[y][x+n] == 'L') {goto n3;
						} else {continue;}
					} else {goto n3;}
				}
n3b:
				if (x==1 && y==1) {printf("incr3 count\n");}
				count++;
n3:
				for (int n = 1; n < LEN; n++) {
					if (x-n > 0) {
						if (grid[y][x-n] == '#') {
							goto n4b;
						} else if (grid[y][x-n] == 'L') {goto n4;
						} else {continue;}
					} else {goto n4;}
				}
n4b:
				if (x==1 && y==1) {printf("incr4 count\n");}
				count++;
n4:
				for (int n = 1; n < LEN; n++) {
					if (x-n > 0 && y-n > 0) {
						if (grid[y-n][x-n] == '#') {
							goto n5b;
						} else if (grid[y-n][x-n] == 'L') {goto n5;
						} else {continue;}
					} else {goto n5;}
				}
n5b:
				if (x==1 && y==1) {printf("incr5 count\n");}
				count++;
n5:
				for (int n = 1; n < LEN; n++) {
					if (x+n < lenx && y-n > 0) {
						if (grid[y-n][x+n] == '#') {
							goto n6b;
						} else if (grid[y-n][x+n] == 'L') {goto n6;
						} else {continue;}
					} else {goto n6;}
				}
n6b:
				if (x==1 && y==1) {printf("incr6 count\n");}
				count++;
n6:
				for (int n = 1; n < LEN; n++) {
					if (x-n > 0  && y+n < leny) {
						if (grid[y+n][x-n] == '#') {
							goto n7b;
						} else if (grid[y+n][x-n] == 'L') {goto n7;
						} else {continue;}
					} else {goto n7;}
				}
n7b:
				if (x==1 && y==1) {printf("incr7 count\n");}
				count++;
n7:
				for (int n = 1; n < LEN; n++) {
					if (x+n < lenx && y+n < leny) {
						if (grid[y+n][x+n] == '#') {
							goto n8b;
						} else if (grid[y+n][x+n] == 'L') {goto n8;
						} else {continue;}
					} else {goto n8;}
				}
n8b:
				if (x==1 && y==1) {printf("incr8 count\n");}
				count++;
n8:
				if (count >= 5) {
					gridNew[y][x] = 'L';
				}
			}
		}
	}
	goto next;
}
