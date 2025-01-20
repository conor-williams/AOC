#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>

using namespace std;
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
long long regs[4];
struct inst_s {
	long long oper;
	long long operand;
};
struct inst_s ops[100];
vector <pair<long long, long long>> ve;
/*Register A: 729
  Register B: 0
  Register C: 0

Program: 0,1,5,4,3,0
 */
char programLine[1000];
int initial[20];
int numInitial;
#define A 0
#define B 1
#define C 2

int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 17 Part 2\n"); fflush(stdout);
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
	int inp = 0; 
	printf("numInitial: %d\n", numInitial);
	for (int i = 0; i < numInitial; i++) {
		printf(" %d ", initial[i]);
	}
	printf("\n");
	long long current[20];
	//14123000000 in 1million
	//28940000000 in 10million
	//48360000000
	int ok;
	int pos_var;
	//for (unsigned long long zz = 117440; zz <= 117440; zz++) //ex7.txt
	//for (unsigned long long zz = 0; zz <= 14124000000; zz++) 
	//for (unsigned long long zz = 14124000000; ; zz++) {
	for (unsigned long long zz = 729; zz <= 729; zz++) {
	//for (unsigned long long zz = 17323786; zz <= 17323786; zz++)  //ex1.txt
		if (zz % 10000000 == 0) {printf("regA: %lld\n", zz);} 
		regs[A] = zz;
		inp = 0;
		pos_var = 0;
		for (int i = inp; i < numInst; i++) {
			struct inst_s tmp = ops[i];
			long long oper = tmp.oper; 
			long long operand = tmp.operand;
			long long comboval; 
			long long literalval; 
			literalval = operand;
			comboval = operand;
			if (comboval >= 4 && comboval <= 6) {
				comboval = regs[comboval -4];
			}

			switch (oper) {
				case 0:
					//adv
					regs[A] = regs[A]/pow(2,comboval);
					break;
				case 1:
					//bxl
					regs[B] = regs[B]^literalval;
					break;
				case 2:
					//bst	
					regs[B] = comboval % 8;
					break;
				case 3:
					//jnz
					if (regs[A] != 0) {
						i = literalval-1;	
					}
					break;
				case 4:
					//bxc
					regs[B] = regs[B] ^ regs[C];
					break;
				case 5:
					//out
					current[pos_var] = comboval%8;
					//if (pos_var >= numInitial || initial[pos_var] != current[pos_var]) {
					//	goto nextRegA;
					//}
					pos_var++;
					
					break;
				case 6:
					//bdv
					regs[B] = regs[A]/pow(2,comboval);
					break;
				case 7:
					//cdv
					regs[C] = regs[A]/pow(2,comboval);
					break;
			}
		}
		ok = 0;
		if (pos_var == numInitial) {
			ok = 1;
		}
			
		if (ok == 1) {
			for (int kkk = 0; kkk < numInitial; kkk++) {
				if (current[kkk] != initial[kkk]) {		
					ok = 0;
					break;
				}
			}
		}
		if (ok == 1) {
			printf("**ans %lld\n", zz);
			break;
		}
nextRegA:
		continue;
	}

	printf("Check: \n");
        for (int kk = 0; kk < pos_var; kk++) {
                printf("%lld,", current[kk]);
        }
	printf("end...\n");
}
	//printf("%lld,%lld (comboval:%lld) (literalval:%lld)\n", oper, operand, comboval, literalval);
		//out_var[(int)strlen(out_var)-1] = '\0';
		//printf("out_var [%s]\n", out_var);
		//printf("programLine [%s]\n", programLine);
	//printf("\nAfter: regs: %lld %lld %lld\n", regs[0], regs[1], regs[2]);
	//printf("**ans %s\n", out_var);
