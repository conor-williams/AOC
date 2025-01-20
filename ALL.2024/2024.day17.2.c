#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;
FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
long long regs[4];
long long regsOrig[4];
//static void *array[] = { &&zero, &&one,&&two,&&three, &&four, &&five, &&six, &&seven,&&eight };
int loop(unsigned long long st, unsigned long long en, int times);

struct inst_s {
	long long oper;
	long long operand;
};
vector <long long> poss;
struct inst_s ops[100];
vector <pair<long long, long long>> ve;
/*Register A: 729
  Register B: 0
  Register C: 0

Program: 0,1,5,4,3,0
 */
char programLine[1000];
long long initial[20];
int numInitial;
#define A 0
#define B 1
#define C 2

int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 17 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	int numInst = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			continue;
		} else if (line1[0] == 'R') {
			char reg; long long val;
			int ret1 = sscanf(line1, "Register %c: %lld", &reg, &val);
			if (ret1 == 2) {
				regs[reg - 65] = val;
			}
		} else if (line1[0] == 'P') {

			char *fir1 = strtok(line1, " ");
			fir1 = strtok(NULL, " ");
			strcpy(programLine, fir1);
			printf("programLine %s\n", fir1);
			char *fir = strtok(fir1, ",\0");
			int pos = 0;
			long long int oper;
			long long int operand;
			char *blah;
			do {
				if ((pos % 2) == 1) {
					operand = strtoll(fir, &blah, 10);	
					struct inst_s tmp;
					tmp.operand = operand;
					tmp.oper = oper;
					ops[pos/2] = tmp;
					initial[pos] = operand;
					numInst++;
				} else {
					oper = strtoll(fir, &blah, 10);
					initial[pos] = oper;
					printf("oper is %lld fir is %s\n", oper, fir);
				}
				pos++;
				
			} while ((fir = strtok(NULL, ",\0")) != NULL);
			numInitial = pos;
		}

		leny++;
	}
	fclose(a);
	printf("numInst is %d\n", numInst);
	//int inp = 0; 
	printf("numInitial: %d\n", numInitial);
	for (int i = 0; i < numInitial; i++) {
		printf(" %lld ", initial[i]);
	}
	printf("\n");
	//14123000000 in 1million
	//28940000000 in 10million
	//48360000000
	int ok;
	//for (unsigned long long zz = 117440; zz <= 117440; zz++) //ex7.txt
	//for (unsigned long long zz = 0; zz <= 14124000000; zz++) 
	//for (unsigned long long zz = 14124000000; ; zz++) 

//Program: 2,4,1,1,7,5,1,5,4,1,5,5,0,3,3,0
	regsOrig[A] = regs[A];
	regsOrig[B] = regs[B];
	regsOrig[C] = regs[C];

	int ch = 1; if (argc == 3) {ch = 0;}
	//for (unsigned long long zz = 17323786; zz <= 17323786*10; zz++) { //Part1
	unsigned long long szz = pow(8, numInitial-1) - 3;
	unsigned long long ezz = pow(8, numInitial) + 100;
	
	//for (unsigned long long zz = pow(8, numInitial-1)-1000000/* - 30786325577728*/; /*zz <= 17323786*10*/ zz <= pow(8, numInitial+1); zz++) 
	//for (unsigned long long zz = szz; zz < ezz; zz++) { //Part1
	//for (unsigned long long zz = 17323786; zz <= 17323786; zz++) { //Part1
	//unsigned long long st = 37*8;
	//unsigned long long en = 38*8-1;
	//unsigned long long st = 9791776;
	//unsigned long long en = 9791776+8;
	unsigned long long st = 0;
	unsigned long long en = 8;
	int times = 0;
	loop(st, en, times);

	printf("Check: \n");
        //for (int kk = 0; kk < pos_var; kk++) { printf("%lld,", current[kk]); }
	printf("looking at possibles...\n");
	
	int pos_var;
	long long current[20];
	long long minzz = 99999999999999999;
	for (auto it = poss.begin(); it != poss.end(); it++) {

		long long zz = *it;
		regs[A] = *it;

		//printf("trying %lld\n", *it);
		pos_var = 0;
		int qq;
		int found;
		memset(current, -1, sizeof(current));
		for (qq = 0; qq < numInitial; qq++) {
			regs[B] = regs[A] % 8; 
			regs[B] ^= 1; //regs[B] = regs[B]^1; 
			assert(regs[B] >= 0 || regs[B] <= 7);
			regs[C] = regs[A]/pow(2,regs[B]);
			regs[B] ^= 5; 
			regs[B] ^= regs[C];
			{ //5,5 
				current[pos_var] = regs[B]%8;
				//printf("(pos_var:%d) %lld V %lld\n", pos_var, current[pos_var], initial[numInitial-(pos_var+1)]);
				//printf("(pos_var:%d) %lld V %lld\n", pos_var, current[pos_var], initial[pos_var]);
				if (pos_var >= numInitial || current[pos_var] != initial[pos_var]) {
					//printf("going @ qq:%d pos_var %d\n", qq, pos_var);
					goto nextRegA;
				}
				pos_var++;
			}
			regs[A] /= 8;
			if (regs[A] == 0) {
				break;
			}
		}
		found = 0;
		if (regs[A] == 0 && pos_var == numInitial) {
			printf("looks good %lld\n", zz);
			if (zz < minzz) {minzz = zz;}
		}
		if (found == 1) {
			//printf("zz is %lld times:%d\n", zz, times);
		}
		memset(current, -1, sizeof(current));
		
nextRegA:
		continue;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %lld\n", minzz);
}

int loop(unsigned long long st, unsigned long long en, int times) {
//again:
	int pos_var;
	long long current[20];
	vector <unsigned long long> ofgoodzz;
	for (unsigned long long zz = st; zz < en; zz++) {

		regs[A] = zz; //regs[A] = regsOrig[A];

		pos_var = 0;
		//printf("setting regsA %lld\n", regs[A]);
		// 2,, 1,, 7,, 1,, 4,, 5,, 0,, 3
		// 2,4,1,1,7,5,1,5,4,1,5,5,0,3,3,0
		// START START START
//one:
		int qq;
		//printf("times now %d\n", times);
		memset(current, -1, sizeof(current));
		int stages[30];
		for (qq = 0; qq <= times; qq++) {
			regs[B] = regs[A] % 8; 
			regs[B] ^= 1; //regs[B] = regs[B]^1; 
			assert(regs[B] >= 0 || regs[B] <= 7);
			regs[C] = regs[A]/pow(2,regs[B]);
			regs[B] ^= 5; 
			regs[B] ^= regs[C];
			{ //5,5 
				current[pos_var] = regs[B]%8;
				//printf("zz is %lld regb is %lld\n", zz, regs[B]);
								
				/*if (ch == 1) {
					if (pos_var >= numInitial || initial[pos_var] != current[pos_var]) {
						goto nextRegA;
					}
				}
				*/
				pos_var++;
			}
			regs[A] /= 8;
			if (regs[A] == 0) {
				break;
			}
		}
		//assert(numInitial - times > 0);

		//printf("that one: %d\n", numInitial-times-1);
		//printf("zz is %lld reg[B] %lld\n", 
		//printf("regs[A] %lld regs[B] V initial : %lld V %lld --- qq V times %d V %d\n", regs[A], regs[B], initial[numInitial-times-1], qq, times);
		int found = 0;
		for (int pp = 0, ii = numInitial-times-1; pp <= times; ii++, pp++) {
			if (regs[A] == 0 && current[pp] == initial[ii] && qq == times) {
				found = 1;
			} else {
				found = 0;
				break;
			}
		}
		if (found == 1) {
			//printf("zz is %lld times:%d\n", zz, times);
			ofgoodzz.push_back(zz);
			getchar();
		}
		memset(current, -1, sizeof(current));
		
		if (found == 1 && times >= 15) {
			printf("poss ans %lld\n", zz);
			poss.push_back(zz);
			//int tmptimes = times;
		}

	}
	for (auto it = ofgoodzz.begin(); it != ofgoodzz.end(); it++) {
		long long tmp1 = *it;
		loop(tmp1*8, (tmp1+1)*8, times+1);
	}
}
			//if (loop(zz*8, (zz+1)*8, tmptimes) == 0) {printf("great"); if (tmptimes > initialNum-2) {printf("wahey"); getchar(); } else {printf("oh no...\n");}
//		if (qq == times && regs[B] == initial[numInitial-times-1]) {printf("zz: %lld\n", zz); st = zz/2; en = 8*((7<<((times+1)*3))+zz); st = 0; en = pow(2, 3*(times+4)); times++; printf("setting st:%lld en:%lld\n", st, en); getchar(); goto again;}
			//if (regs[A] == 0 && current[pp] == initial[ii] && qq == times) {
