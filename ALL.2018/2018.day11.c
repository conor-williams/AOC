#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 40
char line1[SIZE];
long long max = 0;
int serNum = 0;
int grid[300][300];
int main(int argc, char **argv)
{
	///printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day11.1\n"); fflush(stdout);
	fflush(stdout); int fd = dup(1); close(1);
	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		sscanf(line1, "%d", &serNum);
		leny++;
	}
	fclose(a);
	int rid = 0;
	for (int x = 0; x < 300; x++) {
		rid = (x+1)+10;	
		for (int y = 0; y < 300; y++) {
			int power = rid*(y+1);
			power+= serNum;
			power *= rid;
			power = power % 1000;
			power = power / 100;
			power -= 5;
			grid[y][x] = power;
		}
	}

	long long threethree = 0;
	int x1, y1;
	for (int y = 0; y < 300-2; y++) {
		for (int x = 0; x < 300-2; x++) {
			threethree = grid[y][x] + grid[y][x+1] + grid[y][x+2] 
					+ grid[y+1][x] + grid[y+1][x+1] + grid[y+1][x+2]
					+ grid[y+2][x] + grid[y+2][x+1] + grid[y+2][x+2];
			if (threethree > max) {x1 = x+1; y1 = y+1; max = threethree;}
		}
	}

	printf("**max %lld x1,y1 %d,%d\n", max, x1, y1);
	fflush(stdout); dup2(fd, 1);
	printf("**ans %d,%d\n", x1, y1);
}
