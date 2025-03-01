#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

using namespace std;

int lenx, leny;
#define DAY "2016 day20 part2 \n"
#define _DEBUG_
unsigned long long tot;
#define SIZE 200
//sort -n i1.txt
struct ran {
	unsigned long long from;
	unsigned long long to;
};
vector <struct ran> ranges;
//struct ran ranges[1100];

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
	printf("SLOW ~126 minutes\n");
	//TimerSet(60*130);
	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[SIZE];
	while(1) 
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
		//printf("LINE: %s\n", line1);
#endif

		//fd = dup(1); close(1);
		//919958672-920375477
		char from[100]; char to[100];
		sscanf(line1, "%[^-]-%s", from, to);
		char *end;
		struct ran tmp1;	
		tmp1.from = strtoull(from, &end, 10);
		tmp1.to = strtoull(to, &end, 10);
		//ranges[leny].from = strtoull(from, &end, 10);
		//ranges[leny].to = strtoull(to, &end, 10);
		ranges.push_back(tmp1);

		//printf("from: %llu to: %llu\n", ranges[leny].from, ranges[leny].to);
		//system("head -1 i1.txt");
		//getchar();
		leny++;
	}
	fclose(a);
	//for (auto it = ranges.begin(); it != ranges.end(); it++) { printf("%llu\n", it->from); } printf("\n");

	/*
	   5-8
	   0-2
	   4-7
	 */

	unsigned long long last = ranges[leny-1].to;
	//printf("last is %llu\n", last);
	tot = 0;
	for (unsigned long long i = 0; i<=4294967295; i++) {
		if (i % 25000000 == 0) {/*system("date"); printf("i is %llu\n", i);*/}
		int found = 0;
		int end = ranges.size();
		unsigned long long toremove[500]; int toremovePos = 0;
		for (int z = 0; z < end; z++) {
			if (i > ranges[z].to) {toremove[toremovePos] = z; toremovePos++; continue;}
			if (i >= ranges[z].from  && i <= ranges[z].to) {
				found = 1; break;
			}	
		}
		if (found == 0) {
			tot++;	
			//printf("**lowest is %llu\n", i); break;
		}
		if (toremovePos > 0) {
			for (int r = toremovePos-1; r >= 0; r--) {
				//printf("here1.. %llu\n", toremove[r]); fflush(stdout);
				ranges.erase(ranges.begin()+toremove[r]);
			}
		}

	}
	printf("***tot %llu END\n", tot); fflush(stdout);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", tot); fflush(stdout);
} 
