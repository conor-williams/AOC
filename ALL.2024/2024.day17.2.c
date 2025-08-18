#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <string>
#include <vector>
#include <set>
#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
unsigned long long regs[4];
struct inst_s {
	unsigned long long oper;
	unsigned long long operand;
};
struct inst_s ops[100];
vector <pair<unsigned long long, unsigned long long>> ve;
/*Register A: 729
  Register B: 0
  Register C: 0

Program: 0,1,5,4,3,0
*/
unsigned long long part2(unsigned long long A, int PP);
string machine(unsigned long long incomingREG0);
string theProg;
int numInst = 0;
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	/////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2024 Day 17 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); //close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			continue;
		} else if (line1[0] == 'R') {
			char reg; unsigned long long val;
			int ret1 = sscanf(line1, "Register %c: %lld", &reg, &val);
			if (ret1 == 2) {
				regs[reg - 65] = val;
			}
		} else if (line1[0] == 'P') {

			char *fir1 = strtok(line1, ":");
			fir1 = strtok(NULL, ":");
			theProg = fir1;
			theProg += ",";
			theProg.erase(0, 1);
			
			char *fir = strtok(fir1, ",\0");
			int pos = 0;
			unsigned long long int oper;
			unsigned long long int operand;
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
					//printf("oper is %lld fir is %s\n", oper, fir);
				}
				pos++;
			} while ((fir = strtok(NULL, ",\0")) != NULL);
		}

		leny++;
	}
	fclose(a);

	part2(0, 1);
	//printf("theProg [%s]\n", theProg.c_str());

	//printf("ans: %s\n", machine(236539226447469LL).c_str());
}
unsigned long long part2(unsigned long long A, int PP) {
	set <unsigned long long> result;
	for (int n = 0; n < 8; n++) {
		unsigned long long A2 = (A << 3) | n;
		string output = machine(A2);
		/*
		printf("output = %s\n", output.c_str());
		printf("theProg = [%s]\n", theProg.c_str());
		printf("sub = [%s]\n", theProg.substr(theProg.length() - (PP*2)).c_str());
		*/

		if (output == theProg.substr(theProg.length() -(PP*2))) {
			if (output == theProg) {
				result.insert(A2);
			} else {
				unsigned long long possible = part2(A2, PP+1);
			}
		}
	}
	if (result.size() > 0) {

		printf("**ans: ");
		printf("%ld", *result.begin());
		printf("\n");
		exit(0);
	}
	return 0;
}
string machine(unsigned long long incomingREG0) {
	string out_var = "";
	string vv = "";
	regs[0] = incomingREG0;
	regs[1] = 0;
	regs[2] = 0;
	unsigned long long xx, yy, zz;
	for (int i = 0; i < numInst; i++) {
		struct inst_s tmp = ops[i];
		unsigned long long oper = tmp.oper; 
		unsigned long long operand = tmp.operand;
		unsigned long long comboval = 0; 
		unsigned long long literalval; 
		literalval = operand;
		switch ((int)operand) {
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
		//printf("%lld,%lld (comboval:%lld) (literalval:%lld)\n", oper, operand, comboval, literalval);

		switch ((int)oper) {
			case 0:
				//adv
				xx = (regs[0]/(long)pow(2, comboval));// & 0x00000000FFFFFFFF;
				regs[0] = xx;
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
				//sprintf(out_var, "%s%lld,", out_var, comboval%8);
				vv = to_string(comboval % 8);
				out_var = out_var + vv + ',';
				break;
			case 6:
				//bdv
				yy = (regs[0]/(long)pow(2, comboval));// & 0x00000000FFFFFFFF;
				regs[1] = yy;
				break;
			case 7:
				//cdv
				zz = (regs[0]/(long)pow(2, comboval));// & 0x00000000FFFFFFFF;
				regs[2] = zz;
				break;
		}
	}
	return out_var;
}
