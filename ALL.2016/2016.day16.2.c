#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <unistd.h>
#include <deque>
#include <sys/time.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
using namespace std;

deque<int> b1;
deque<int> b2;
int lenx, leny;
#define DAY "2016 day16 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 200
#define CDISK 35651584
//#define CDISK 272
#define getchar()

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
int main(int argc, char **argv)
{
	TimerSet(1200);
	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf("\nSLOW ~<1min\n");
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[SIZE];
	while(1) 
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		//	printf("LINE: %s\n", line1);
#endif
		deque <int> in;
		for (int i = 0; i < (int)strlen(line1); i++) {
			if (line1[i] == '1') {
				in.push_back(1);
			} else {
				in.push_back(0);
			}
		}

		b1 = in;	
		do {
			//printf("in while %d\n", in.size());
			b1.push_back(0);
			for (auto it = in.rbegin(); it != in.rend(); it++)  {
				if (*it == 0) {
					b1.push_back(1);
				} else {
					b1.push_back(0);
				}
			}
			in = b1;
			for (auto it = in.begin(); it != in.end(); it++)  {
				printf("%d", *it);
			}
			printf("\n"); getchar();
		} while (b1.size() < CDISK);

		//printf("after while %d\n", in.size());
		while (b1.size() > CDISK) {b1.pop_back();}
		printf("20:\n");
		for (auto it = b1.begin(); it != b1.end(); it++)  {
			printf("%d", *it);
		}

		printf(" here1 (%s) b1.size() is %d\n", line1, (int)b1.size()); getchar();
again:
		b2.clear();
		int sz = (int)b1.size();
		for (int i = 0; i < sz; i++) {
			int c1 = b1.front(); b1.pop_front();
			int c2 = b1.front(); b1.pop_front();
			b2.push_back(c1 == c2);
			i++;
		}
		b1 = b2;
		printf("b1.size is %d\n", (int)b1.size());
		printf("b2.size is %d\n", (int)b1.size());
		if ((b1.size() % 2) == 0) {
			printf("agagin "); getchar();
			goto again;
		} else {
			printf("odd...\n"); getchar();
		}

		fflush(stdout); dup2(fd, 1);
		printf("**ans: ");
		for (auto it = b1.begin(); it < b1.end(); it++) {
			printf("%d", *it);
		}
		printf("\n");
		leny++;

	}
	fclose(a);


	//printf(" ***tot %ld END\n", tot); fflush(stdout);
} 

