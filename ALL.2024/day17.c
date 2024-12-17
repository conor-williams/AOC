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
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 17 Part 1\n"); fflush(stdout);
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
		
		char *fir1 = strtok(line1, ":");
		fir1 = strtok(NULL, ":");
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
				numInst++;
			} else {
				oper = strtoll(fir, &blah, 10);
				printf("oper is %lld fir is %s\n", oper, fir);
			}
			pos++;
		} while ((fir = strtok(NULL, ",\0")) != NULL);
	}
	
	leny++;
}
fclose(a);
	printf("numInst is %d\n", numInst);
	int inp = 0;
	char out_var[2000] = "";
	for (int i = inp; i < numInst; i++) {
		struct inst_s tmp = ops[i];
		long long oper = tmp.oper; 
		long long operand = tmp.operand;
		long long comboval; 
		long long literalval; 
		literalval = operand;
		switch (operand) {
			case 0:
			case 1:
			case 2:
			case 3:
				comboval = operand;
				break;
			case 4:
				comboval =  regs[0];
				break;
			case 5:
				comboval = regs[1];
				break;
			case 6:
				comboval = regs[2];
				break;
			case 7:
				comboval = 7;
				break;
		}
		printf("%lld,%lld (comboval:%lld) (literalval:%lld)\n", oper, operand, comboval, literalval);

		switch (oper) {
			case 0:
				//adv
				regs[0] = regs[0]/pow(2,comboval);
				break;
			case 1:
				//bxl
				regs[1] = regs[1]^literalval;
				break;
			case 2:
				//bst	
				regs[1] = comboval % 8;
				break;
			case 3:
				//jnz
				if (regs[0] == 0) {
					//nothing
				} else {
					i = literalval-1;	
				}
				break;
			case 4:
				//bxc
				regs[1] = regs[1] ^ regs[2];
				break;
			case 5:
				//out
				//printf("%lld,", combovalval%8);
				sprintf(out_var, "%s%lld,", out_var, comboval%8);
				break;
			case 6:
				//bdv
				regs[1] = regs[0]/pow(2,comboval);
				break;
			case 7:
				//cdv
				regs[2] = regs[0]/pow(2,comboval);
				break;
		}
	}
	
	printf("\nAfter: regs: %lld %lld %lld\n", regs[0], regs[1], regs[2]);
	out_var[(int)strlen(out_var)-1] = '\0';
	printf("**ans %s\n", out_var);
}
