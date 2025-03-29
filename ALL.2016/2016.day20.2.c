#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <algorithm>

using namespace std;

int lenx, leny;
#define DAY "2016 day20 part2"
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
#ifdef _ACCOLADE_
	printf("ta nullmove on reddit\n");
#endif
	//
	//TimerSet(60*130);
	tot = 0;lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf("		%s\n", DAY); fflush(stdout);

	fd = dup(1); close(1);

	char line1[SIZE];
	vector<pair<unsigned long long, unsigned long long>> record;

	while(1) 
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		printf("line1: %s\n", line1);

		char from[100]; char to[100];
		sscanf(line1, "%[^-]-%s", from, to);
		char *end;
		struct ran tmp1;	
		tmp1.from = strtoull(from, &end, 10);
		tmp1.to = strtoull(to, &end, 10);
		record.emplace_back(tmp1.from, tmp1.to);
		leny++;
	}
	printf("leny is %d\n", leny); getchar();
	fclose(a);

	printf("after while...\n"); fflush(stdout);
	sort(record.begin(), record.end());
	//unsigned long long total = 0, ip = 0;
	unsigned long long total = 0, ip = 0;
	int index = 0;

	unsigned long long END = pow(2, 32)-1;
	printf("END is %lld\n", END);
	while (ip <= END) {
		//printf("index is %d\n", index);
		auto [lower, upper] = record[index];
		if (ip >= lower) {
			if (ip <= upper) {
				ip = upper+1;
				continue;
			}
			index++;
		} else {
			total++;
			ip++;
		}

	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", total);
} 
