#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

char grid[LINE][LINE];
char grid2[LINE][LINE];
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 4 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
	

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	strcpy(grid[leny], line1);
	leny++;
}
fclose(a);
	
	int lenx = strlen(grid[0]);
	char alldots[1000];
	for (int i = 0; i < lenx; i++) {
		alldots[i] = '.';
		alldots[i+1] = '\0';
	}

	for (int i = 0; i < 3; i++) {
		sprintf(grid2[i], "...%s...", alldots);
	}
	for (int i = 3; i < leny+3; i++) {
		sprintf(grid2[i], "...%s...", grid[i-3]);
	}
	for (int i = leny+3; i < leny+6; i++) {
		sprintf(grid2[i], "...%s...", alldots);
	}
		
	unsigned long long ans = 0;
	for (int y = 3; y < leny+3; y++) {
		for (int x = 3; x < lenx+3; x++) { 
			//printf("%c", grid2[y][x]); } printf("\n");


			/*
			M M	M S    S M    S S
			 A       A      A      A
			S S     M S    S M    M M
			*/

			if (grid2[y][x] == 'M' && grid2[y+1][x+1] == 'A' && grid2[y+2][x+2] == 'S' &&
				grid2[y][x+2] == 'M' && grid2[y+2][x] == 'S') {
				ans++;
			}
			if (grid2[y][x] == 'M' && grid2[y+1][x+1] == 'A' && grid2[y+2][x+2] == 'S' &&
				grid2[y][x+2] == 'S' && grid2[y+2][x] == 'M') {
				ans++;
			}
			if (grid2[y][x] == 'S' && grid2[y+1][x+1] == 'A' && grid2[y+2][x+2] == 'M' &&
				grid2[y][x+2] == 'M' && grid2[y+2][x] == 'S') {
				ans++;
			}
			if (grid2[y][x] == 'S' && grid2[y+1][x+1] == 'A' && grid2[y+2][x+2] == 'M' &&
				grid2[y][x+2] == 'S' && grid2[y+2][x] == 'M') {
				ans++;
			}
		}
			
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", ans);

}
