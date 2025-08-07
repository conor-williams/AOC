#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

#define getchar()

void TimerStop(int signum);
void TimerSet(int interval);

#define INTERVAL 12 

void TimerStop(int signum);
void TimerSet(int interval);
FILE *a;
int REG0 = 0;

void TimerStop(int signum) {
	printf("\x1b[H");
	printf("\x1b[%dB", 4);
	printf("Timer ran out! Stopping timer %d\n", REG0);
	fclose(a);
	exit(10);
}

void TimerSet(int interval) {
	//printf("starting timer\n");
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


int tot = 0;
#define SIZE 500
char line1[SIZE];
int leny = 0;

char instr[1000][25];
int instNum =0;
int mycmp(char four[]);
int main(int argc, char **argv)
{
	a = fopen(argv[1], "r"); printf("		2018 Day21.1\n"); fflush(stdout);
	int fd = dup(1); close(1);
	int instREG;

	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[(int)strlen(line1)-1] = '\0';
		//printf("line1 %s\n", line1);
		if (leny == 0) {
			sscanf(line1, "#ip %d", &instREG);
		} else {
			strcpy(instr[leny-1], line1);
			instNum++;
		}

		leny++;
	}
	fclose(a);

	int ans = 0;
	long long regb[10] = {0};
	int regA, regB, regC, in;
	regb[0] = 1;
	for (int k = 0; k < instNum; k++) {

		char four[10];
		int ret = sscanf(instr[k], "%s %d %d %d", four, &regA, &regB, &regC);
		if (ret == 4) { in = mycmp(four); }
		regb[instREG] = k;
		printf("inst: %d (%d %d %d)\n", in, regA, regB, regC); fflush(stdout); getchar();
		switch(in) {
			case 9: //addr
				regb[regC] = regb[regA] + regb[regB];
				break;
			case 11: //addi
				regb[regC] = regb[regA] + regB;
				//printf("addi regb[regC] is %d\n", regb[regC]);
				break;
			case 15: //mulr
				regb[regC] = regb[regA] * regb[regB];
				break;
			case 7: //muli
				regb[regC] = regb[regA] * regB;
				break;
			case 5: //banr
				regb[regC] = regb[regA] & regb[regB];
				break;
			case 1: //bani
				regb[regC] = regb[regA] & regB;
				break;
			case 6: //borr
				regb[regC] = regb[regA] | regb[regB];
				break;
			case 3: //bori
				regb[regC] = regb[regA] | regB;
				break;
			case 8: //setr
				regb[regC] = regb[regA];
				break;
			case 2: //seti
				regb[regC] = regA;
				break;
			case 12: //gtir
				if (regA > regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
				break;
			case 14: //gtir
				if (regb[regA] > regB) {regb[regC] = 1;} else {regb[regC] = 0;}
				break;
			case 13: //gtrr
				if (regb[regA] > regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
				break;
			case 4: //eqir
				if (regA == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
				break;
			case 0:
				if (regb[regA] == regB) {regb[regC] = 1;} else {regb[regC] = 0;}
				break;
			case 10:
				ans = regb[regA];
				goto after;
				//if (regb[regA] == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
				//break;
			default:
				printf("ERR\n"); exit(0);
		}
		if (regC ==  instREG) {k = regb[instREG];}
	}
after:
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", ans);
}

int mycmp(char four[]) {
	if (strcmp(four, "addr") == 0) {return 9;}
	else if (strcmp(four, "addi") == 0) {return 11;}
	else if (strcmp(four, "mulr") == 0) {return 15;}
	else if (strcmp(four, "muli") == 0) {return 7;}
	else if (strcmp(four, "banr") == 0) {return 5;}
	else if (strcmp(four, "bani") == 0) {return 1;}
	else if (strcmp(four, "borr") == 0) {return 6;}
	else if (strcmp(four, "bori") == 0) {return 3;}
	else if (strcmp(four, "setr") == 0) {return 8;}
	else if (strcmp(four, "seti") == 0) {return 2;}
	else if (strcmp(four, "gtir") == 0) {return 12;}
	else if (strcmp(four, "gtri") == 0) {return 14;}
	else if (strcmp(four, "gtrr") == 0) {return 13;}
	else if (strcmp(four, "eqir") == 0) {return 4;}
	else if (strcmp(four, "eqri") == 0) {return 0;}
	else if (strcmp(four, "eqrr") == 0) {return 10;}
	else {printf("ERR\n"); exit(0);}
}
