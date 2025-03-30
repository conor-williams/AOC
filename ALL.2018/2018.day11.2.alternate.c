#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
#undef _DEBUG_
#define SIZE 40
char line1[SIZE];
long long max = 0;
int serNum = 0;
int grid[300][300];

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
	TimerSet(1200);
	printf("%d", argc); printf("@%s\n", argv[1]); fflush(stdout);
	printf("SLOW ~7minutes\n");
	FILE * a = fopen(argv[1], "r"); printf("2018 Day11.2\n"); fflush(stdout);


	fflush(stdout); fd = dup(1); close(1);

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
	int sz = 0;
	for (int y = 0; y < 300-2; y++) {
		for (int x = 0; x < 300-2; x++) {
			for (int size = 3; (y+size <= 300) && (x+size <= 300); size++) {
				threethree = 0;
				for (int zy = 0; zy < size; zy++) {
					for (int zx = 0; zx < size; zx++) {
						threethree += grid[y+zy][x+zx];
					}
				}
				if (threethree > max) {x1 = x+1; y1 = y+1; sz = size; max = threethree;}
			}
		}
	}
	printf("**max %lld x1,y1 %d,%d,%d\n", max, x1, y1, sz);
	
	printf("**max %lld x1,y1 %d,%d,%d\n", max, x1, y1, sz);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d,%d,%d\n", x1, y1, sz);
}
