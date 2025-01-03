#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day18 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 120

#define SX 120
#define SY 400020
char grid[SY][SX];
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SIZE];
	strcpy(grid[0], "......................................................................................................");
	leny++;
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	
	grid[1][0] = '.';
	for (int i = 0; i < (int)strlen(line1); i++) {
		grid[1][i+1] = line1[i];
	}
	grid[leny][(int)strlen(line1) +1] = '.';
	
	int y = 1;
	do {
		for (int x = 1; x < strlen(grid[0])-1; x++) {
			if (grid[y][x-1] == '^' && grid[y][x] == '^' && grid[y][x+1] == '.') {
				grid[y+1][x] = '^';
			} else if (grid[y][x-1] == '.' && grid[y][x] == '^' && grid[y][x+1] == '^') {
				grid[y+1][x] = '^';
			} else if (grid[y][x-1] == '^' && grid[y][x] == '.' && grid[y][x+1] == '.') {
				grid[y+1][x] = '^';
			} else if (grid[y][x-1] == '.' && grid[y][x] == '.' && grid[y][x+1] == '^') {
				grid[y+1][x] = '^';
			} else {
				grid[y+1][x] = '.';
			}
		}
		grid[y+1][0] = '.'; grid[y+1][(int)strlen(grid[0])-1] = '.';
		if (y == SY+2) {break;}
		y++;
	} while (1);
	
	tot = 0;
//	for (int y = 1; y <= (int)strlen(grid[0])-2; y++) {
/*
	for (int y = 1; y <= 400000; y++) {
		for (int x = 1; x < (int)strlen(grid[0])-1; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
*/
//	for (int y = 1; y <= (int)strlen(grid[0])-2; y++) {
	for (int y = 1; y <= 400000; y++) {
		for (int x = 1; x < (int)strlen(grid[0])-1; x++) {
			if (grid[y][x] == '.') {
				tot++;
			}
		}
	}
			
	
	printf("***tot %ld END\n", tot); fflush(stdout);
	leny++; getchar();
}
fclose(a);
	
	dup2(fd, 1);
	printf("***tot %ld END\n", tot); fflush(stdout);
} 
