#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
/*

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;


struct hash_function
{
        size_t operator()(const tuple<int , int , int, int>&x) const
        {
                unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
        }
};

*/

//char grid[5][5]  = {{' ', ' ', ' ', ' ', ' '}, {' ', '1', '2', '3', ' '}, {' ', '4', '5', '6', ' '}, {' ', '7', '8', '9', ' '}, {' ', ' ', ' ', ' ', ' '}};
char grid[7][7]  = {{' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', '1', ' ', ' ', ' '}, {' ', ' ', '2', '3', '4', ' ', ' '}, {' ', '5', '6', '7', '8', '9', ' '}, {' ', ' ', 'A', 'B', 'C', ' ', ' '}, {' ', ' ', ' ', 'D', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

int main(int argc, char **argv)
{
        clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        //printf("        time: %f seconds\n", cpu_time_used);

        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        //printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2016 Day 2 Part 2\n"); fflush(stdout);
        char line1[LINE];
	fflush(stdout); int fd = dup(1); close(1);

	leny = 0;
	int sx = 1;
	int sy = 3;
	char code[100];
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	for (int ii = 0; ii < (int)strlen(line1); ii++) {
		switch (line1[ii]) {
			case 'U':
				if (grid[sy-1][sx] != ' ') {
					sy--;
				}
				break;
			case 'R':
				if (grid[sy][sx+1] != ' ') {
					sx++;
				}
				break;
			case 'D':
				if (grid[sy+1][sx] != ' ') {
					sy++;
				}
				break;
			case 'L':
				if (grid[sy][sx-1] != ' ') {
					sx--;
				}
				break;
		}
	}
	code[leny] = grid[sy][sx];
	leny++;
}
fclose(a);
	code[leny] = '\0';

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %s\n", code);
}
