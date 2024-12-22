#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>

using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
deque <unsigned long long> secrets;
int TIMES = 2000;
void printit(deque <unsigned long long> s1);
unsigned long long mix(unsigned long long secret, unsigned long long in);
unsigned long long prune(unsigned long long in);
int main(int argc, char **argv)
{
	if (argc == 3) {TIMES = atoi(argv[2]);}

        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 22 Part 1\n"); fflush(stdout);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	char *bla;
	unsigned long long pu = strtoull(line1, &bla, 10);
	secrets.push_back(pu);
	leny++;
}
fclose(a);
	for (int i = 0; i < TIMES; i++) {
		deque <unsigned long long> secretsTmp;
		for (auto snum: secrets) {
			unsigned long long mul1 = snum *64;
			snum = mix(snum, mul1);
			snum = prune(snum);
			unsigned long long div1 = snum / 32;
			snum = mix(snum, div1);
			snum = prune(snum);
			unsigned long long mul2 = snum * 2048;
			snum = mix(snum, mul2);
			snum = prune(snum);
			secretsTmp.push_back(snum);
		}
		secrets = secretsTmp;
		secretsTmp.clear();		
	}
	printit(secrets);
	unsigned long long sum = 0;
	for (auto one: secrets) {
		sum += one;
	}
	printf("**ans %llu\n", sum);
}
void printit(deque <unsigned long long> s1) {
	for (auto n1: s1) {
		printf("%llu " , n1);
	}
	printf("\n");
}
unsigned long long mix(unsigned long long secret, unsigned long long inin) {
	return inin ^ secret;
	
}
unsigned long long prune(unsigned long long inin) {
	return inin % 16777216;
}
