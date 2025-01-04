#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <signal.h>
#include <stack>

#include <unistd.h>

#define getchar()
using namespace std;

#define SIZE 16000
#undef _DEBUG_
char line1[SIZE];
unsigned long tot = 0;
///#define getchar()
char dirs[SIZE];

#define SI  10000

int grid[SI][SI] = {0};
int lens[SI][SI] = {0};

stack <pair<int, int>> mystack;

void signal_handler(int) {

	char ans[5];
	fgets(ans, 4, stdin);
	if (ans[0] == 'y') {
		printf("..continueing...\n");
	} else {
		printf("no probs... continueing...\n");
	}

	time_t t; time(&t);
	printf("current time is %s (continueing...)\n", ctime(&t));
}

int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day20.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	signal(SIGTSTP, &signal_handler);
	int leny = 0;

	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		strcpy(dirs, line1);
		leny++;
	}
	fclose(a);

	
	int cur = 0; int longest(0);
	int x = SI/20; int y = SI/2;
	for (int i = 0; i < (int)strlen(dirs); i++) {
		if (lens[y][x] < cur && lens[y][x] != 0) {
			cur = lens[y][x];
		}
		lens[y][x] = cur;

		switch(dirs[i]) {
			case 'N': y--; cur++; break;
			case 'S': y++; cur++; break;
			case 'E': x++; cur++; break;
			case 'W': x--; cur++; break;
			case '(': mystack.push({x, y}); break;
			case ')': {auto p = mystack.top(); x = p.first; y = p.second; mystack.pop(); break;}
			case '|': {auto p = mystack.top(); x = p.first; y = p.second; break;}
			default: printf("just ^ and $ (%c)\n", dirs[i]); break;
		}
		if (cur > longest) {longest = cur;}
	}
	int res(0);
	for (int y = 0; y<SI; y++) {
		for (int x = 0; x<SI; x++) {
			if (lens[y][x] != 0) {
				printf("lens[y][x] %d\n", lens[y][x]);
			}
			if (lens[y][x] >= 1000) {
				res++;
			}
		}
	}
	
	fflush(stdout); dup2(fd, 1);
	printf("PART1: ANS: [[[ %d ]]]\n", longest);
	exit(0);
	printf("PART2: ANS: [[[ %d ]]]\n", res);
}
