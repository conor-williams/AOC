#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int buckets[100];
int lenx, leny;
#define DAY "2015 day18 part2\n"
#undef _DEBUG_
char grid[105][105];
char gridtmp[105][105];
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
       
	char line1[1000];
	//strcpy(grid[0], "........");
	strcpy(grid[0], "......................................................................................................");
	leny++;
while(1) {
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	grid[leny][0] = '.';
	for (int i = 0; i < (int)strlen(line1); i++) {
		grid[leny][i+1] = line1[i];
	}
	grid[leny][(int)strlen(line1)+1] = '.';
	grid[leny][(int)strlen(line1)+2] = '\0';
	leny++;
}
	//strcpy(grid[leny], "........");
	strcpy(grid[leny], "......................................................................................................");
	leny++;
lenx = strlen(grid[0]);
	grid[1][1] = '#';
	grid[leny-2][1] = '#';
	grid[leny-2][lenx-2] = '#';
	grid[1][lenx-2] = '#';
fclose(a);
	for (int y = 0; y < leny; y++) {
		strcpy(gridtmp[y], grid[y]);
	}

	int TIMES = 100;
	for (int i = 0; i < TIMES; i++) {
		grid[1][1] = '#';
		grid[leny-2][1] = '#';
		grid[leny-2][lenx-2] = '#';
		grid[1][lenx-2] = '#';
		for (int y = 1; y < leny -1; y++) {
			for (int x = 1; x < lenx -1; x++) {
				int counton = 0;
				int countoff = 0;
				if (grid[y-1][x] == '#') { counton++;} else {countoff++;}
				if (grid[y-1][x+1] == '#') { counton++;} else {countoff++;}
				if (grid[y][x+1] == '#') { counton++;} else {countoff++;}
				if (grid[y+1][x+1] == '#') { counton++;} else {countoff++;}
				if (grid[y+1][x] == '#') { counton++;} else {countoff++;}
				if (grid[y+1][x-1] == '#') { counton++;} else {countoff++;}
				if (grid[y][x-1] == '#') { counton++;} else {countoff++;}
				if (grid[y-1][x-1] == '#') { counton++;} else {countoff++;}
				if (grid[y][x] == '#') {
					if (counton == 2 || counton == 3) {gridtmp[y][x] = '#';} else {gridtmp[y][x] = '.';}
				} else if (grid[y][x] == '.') {
					if (counton == 3) {gridtmp[y][x] = '#';} else {gridtmp[y][x] = '.';}
				}
			}
		}
		gridtmp[1][1] = '#';
		gridtmp[leny-2][1] = '#';
		gridtmp[leny-2][lenx-2] = '#';
		gridtmp[1][lenx-2] = '#';
		for (int y = 1; y < leny-1; y++) {
			strcpy(grid[y], gridtmp[y]);
		}
		for (int y = 0; y < leny; y++) {
			printf("%s\n", grid[y]);
		}
		getchar();
		
	}
	
	
	int tot = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '#') {
				tot++;
			}
		}
	}

	printf("****tot %d\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);

}
