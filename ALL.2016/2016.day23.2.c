#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
int lenx, leny;
#define DAY "2016 day23 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 200

char instrs[100][20];

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
	TimerSet(40*60);
	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	printf("SLOW ~35minutes\n");
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
		//	printf("LINE: %s\n", line1);
#endif
		strcpy (instrs[leny], line1);
		leny++;
	}
	fclose(a);
	int regs[26] = {0};
	regs[0] = 12;
	int count = 0;
	for (int i = 0; i < leny; i++) {
		//printf("instrs[%d] is %s\n", i, instrs[i]);
		//printf("reg a %d\n", regs[0]); fflush(stdout);
		//count++; if (count %10000 == 0) { count = 0; printf("inst: %d\n", i);}
		char reg1; char reg2[5]; char reg3; int num1;

		//	int ret1 = sscanf(instrs[i], "cpy %c %c", &reg3, &reg1);
		//	if (ret1 == 2) {regs[reg1-97] = regs[reg3-97]; continue;}
		//	int ret11 = sscanf(instrs[i], "cpy %d %c", &num1, &reg1);
		//	if (ret11 == 2) {regs[reg1-97] = num1; continue;}

		int ret1 = sscanf(instrs[i], "cpy %s %c", reg2, &reg1);
		if (ret1 == 2) {if (strlen(reg2) == 1 && reg2[0] - 97 <= 122 && reg2[0] -97 >= 0) {regs[reg1-97] = regs[reg2[0]-97];} else {regs[reg1-97] = atoi(reg2);} continue;}

		int ret2 = sscanf(instrs[i], "inc %c", &reg1);
		if (ret2 == 1) {regs[reg1-97]++; continue;}

		int ret3 = sscanf(instrs[i], "dec %c", &reg1);
		if (ret3 == 1) {regs[reg1-97]--; continue;}

		int ret44 = sscanf(instrs[i], "jnz %d %c", &num1, &reg1);
		if (ret44 == 2) {if (num1>0) {i+=regs[reg1-97]-1; continue;} else {continue;}}
		//
		int ret4 = sscanf(instrs[i], "jnz %c %d", &reg1, &num1);
		if (ret4 == 2) {if (regs[reg1-97] != 0) {i += num1 -1; continue;} else {continue;}}
		//
		int ret444 = sscanf(instrs[i], "jnz %c %c", &reg1, &reg3);
		if (ret444 == 2) {if (regs[reg1-97] != 0) {i += regs[reg3-97]-1; continue;} else {continue;}}

		int ret5 = sscanf(instrs[i], "tgl %c", &reg1);
		if (ret5 == 1) {
			int tv = regs[reg1-97]+i;
			if (tv > leny) {printf("OUTSIDE -- CONT\n");}
			if (instrs[tv][0] == 'd' && instrs[tv][1] == 'e') {
				instrs[tv][0] = 'i';
				instrs[tv][1] = 'n';
				//instrs[tv][2] = 'c';
			} else if (instrs[tv][0] == 'i' && instrs[tv][1] == 'n') {
				instrs[tv][0] = 'd';
				instrs[tv][1] = 'e';
				//instrs[tv][2] = 'c';
			} else if (instrs[tv][0] == 't' && instrs[tv][1] == 'g') {
				instrs[tv][0] = 'i';
				instrs[tv][1] = 'n';
				instrs[tv][2] = 'c';
			} else if (instrs[tv][0] == 'j' && instrs[tv][1] == 'n') {
				instrs[tv][0] = 'c';
				instrs[tv][1] = 'p';
				instrs[tv][2] = 'y';
			} else if (instrs[tv][0] == 'c' && instrs[tv][1] == 'p') {
				instrs[tv][0] = 'j';
				instrs[tv][1] = 'n';
				instrs[tv][2] = 'z';
			}
			continue;
		}

		printf("INVALID.. CONT\n");
	}

	//printf("***tot %ld END\n", tot); fflush(stdout);
	printf("***reg a %d\n", regs[0]); fflush(stdout);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", regs[0]); fflush(stdout);
} 
