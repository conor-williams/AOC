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
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SX 200

char grid[SX][SX];
int already[SX][SX];
int lenx = 0;
void next(int x, int y, int path, int ex, int ey);
int minPath = 99999;
int leny = 0;

#include <sys/time.h>
#include <signal.h>
void TimerStop(int signum);
void TimerSet(int interval);

void TimerSet(int interval) {
    printf("starting timer\n");
    struct itimerval it_val;

    it_val.it_value.tv_sec = interval;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;

    if (signal(SIGALRM, TimerStop) == SIG_ERR) {
        perror("Unable to catch SIGALRM");
        exit(1);
    }
    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        perror("error calling setitimer()");
        exit(1);
    }
}

int fd;
void TimerStop(int signum) {

	fflush(stdout); dup2(fd, 1);
    printf("Timer ran out! Stopping timer\n");
	FILE *f = fopen("out.tim", "a");
	fprintf(f, "Timer ran out! Stopping timer timestamp@%s\n", "out.tim");
	fclose(f);
    exit(10);
}
//main:::if (argc == 3) {printf("SETTING TIME TO [%d]\n", atoi(argv[2])); TimerSet(atoi(argv[2]));}
int main(int argc, char **argv)
{
	//TimerSet(30);
	signal(SIGTSTP, &sigfunc);
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 12.2\n"); fflush(stdout);
	printf("	SLOW ~15seconds\n");

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];

	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);

	int stx[3000], sty[3000];
	int enx, eny;
	int pos = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'S' || grid[y][x] == 'a') {
				stx[pos] = x; sty[pos] = y;
				pos++;
				if (grid[y][x] == 'S') {grid[y][x] = 'a';}
				if (pos+3 > 3000) {perror("pos"); exit(0);}
			} else if (grid[y][x] == 'E') {
				enx = x; eny = y;
				grid[y][x] = 'z';
			}
		}
	}
	for (int i = 0; i < pos; i++) {
		memset(already, 0, sizeof(already));
		assert(already[5][5] == 0);
		next(stx[i], sty[i], 0, enx, eny);
	}
	printf("**minPath %d\n", minPath);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minPath);
}


void next(int x, int y, int path, int ex, int ey) {
	if (x == ex && y == ey) {
		if (path < minPath) {minPath = path;}
		return;
	}

	if (already[y][x] > path || already[y][x] == 0) {
		already[y][x] = path;

		if (grid[y-1][x] - grid[y][x] <= 1) {
			if (y-1 >= 0) {next(x, y-1, path+1, ex, ey);}
		}
		if (grid[y][x+1] - grid[y][x] <= 1) {
			if (x+1 < lenx) {next(x+1, y, path+1, ex, ey);}
		}
		if (grid[y+1][x] - grid[y][x] <= 1) {
			if (y+1 < leny) {next(x, y+1, path+1, ex, ey);}
		}
		if (grid[y][x-1] - grid[y][x] <= 1) {
			if (x-1 >= 0) {next(x-1, y, path+1, ex, ey);}
		}
	}

}
