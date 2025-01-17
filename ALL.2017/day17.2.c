#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

deque <long int> circle2;
void rotateClock(int d);
void rotateClock(int d)
{
    for (int i = 0; i < d; i++) {
        long int val = circle2.front();
        circle2.pop_front();
        circle2.push_back(val);
    }
}
void rotate(int d);
void rotate(int d)
{
    // Push first d elements
    // from last to the beginning
    for (int i = 0; i < d; i++) {
        long int val = circle2.back();
        circle2.pop_back();
        circle2.push_front(val);
    }
}


int tot = 0;
#define SIZE 50
char line1[SIZE];

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
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day17.2\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
int leny = 0;
int spin;
	circle2.clear();
	circle2.push_back(0);
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
// 	printf("line1 %s\n", line1);
	
	spin = atoi(line1);
	leny++;
}
	fclose(a);
        int newSpin;
        for (long int i = 1; i <= 50000000; i++) {
		if (i % 1000000 == 0) {printf("i is %ld\n", i);
	for (auto it = circle2.begin(); it != circle2.end(); it++) { if (*it == 0) {it++; printf("** %ld\n", *it); break;}} }
                if (i < spin) {
                        newSpin = spin % circle2.size();
                } else {
                        newSpin = spin;
                }
                rotateClock(newSpin);
                circle2.push_back(i);
	}
//	for (auto it = circle2.begin(); it != circle2.end(); it++) { printf(" [%ld] ", *it); } printf("\n"); getchar();}

	fflush(stdout); fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	for (auto it = circle2.begin(); it != circle2.end(); it++) { if (*it == 0) {it++; printf("** %ld\n", *it); break;}} 
	printf("\n");

	return 0;
}
