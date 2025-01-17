#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>

#include <unistd.h>

#define getchar()
#define assert(asdf)
//60 cycle pos 40
using namespace std;

vector <char> V;
int tot = 0;
#define SIZE 50000
char line1[SIZE];
char line1Orig[SIZE];
#ifdef EX1
char start[] = "abcde";
#else
char start[] = "abcdefghijklmnop";
#endif

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
	FILE * a = fopen(argv[1], "r"); printf("2017 Day16.2\n"); fflush(stdout);

	printf("broken...\n"); exit(0);
	fflush(stdout); fd = dup(1); close(1);
	printf("%s\n", start);
	V.clear();
	for (int i = 0; i < (int)strlen(start); i++) {
		V.push_back(start[i]);	
	}

	int leny = 0;
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		// 	printf("line1 %s\n", line1);


		//s1,x3/4,pe/b
		strcpy(line1Orig, line1);
		for (int i = 0; i < 1000000000; i++) {
			if ((i % 1000000) == 0) {printf("%d\n", i);}
			char *first = strtok(line1, ",\0");
			char num1S[10]; int num1, num2;
			char let1, let2;
			char tmp1; char tmp2;
			do {
				switch (first[0]) {
					case 's':
						first[0] = ' ';
						rotate(V.begin(), V.begin()+V.size()-atoi(first), V.end());
						break;
					case 'x':
						sscanf(first, "x%[^/]/%d", num1S, &num2);
						num1 = atoi(num1S);
						//printf("num1 is %d]\n", num1);
						//printf("num2 is %d]\n", num2);
						tmp1 = V[num1];
						V[num1] = V[num2];
						V[num2] = tmp1;
						break;
					case 'p':
						sscanf(first, "p%c/%c", &let1, &let2);
						int pos1, pos2;
						int pos = 0;
						for (auto it = V.begin(); it != V.end(); it++) {
							if (*it == let1) {pos1 = pos;}
							if (*it == let2) {pos2 = pos;}
							pos++;
						}
						tmp2 = V[pos2];
						V[pos2] = V[pos1];
						V[pos1] = tmp2;
						break;	
				}
			} while ( (first = strtok(NULL, ",\0")) != NULL);
			for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); 
			strcpy(line1, line1Orig);
		}
		leny++;
	}
	fclose(a);

	fflush(stdout); fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	for (auto it = V.begin(); it != V.end(); it++) { printf("%c", *it); } printf("\n"); 
	return 0;
}
