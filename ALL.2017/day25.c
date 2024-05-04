#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
#define SIZE 200
char line1[SIZE];
int leny = 0;
#define SZ 70000000
int tape[SZ*2] = {0};

struct inst_s {
	char oldstate;
	int from;
	int to;
	char rightorleft[10];
	char newstate;
};	
struct inst_s inst[100];

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);

char start = ' '; int steps = 0;
int num = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[(int)strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1); 
	if ((int)strlen(line1) > 0) {
 		line1[(int)strlen(line1)-1] = '\0';
	}
	int ret;
	ret = sscanf(line1, "Begin in state %c\n", &start);
	if (ret == 1) {continue;}
	ret = sscanf(line1, "Perform a diagnostic checksum after %d steps", &steps);
	if (ret == 1) {continue;}

	if (strlen(line1) == 0) {continue;}

	ret = sscanf(line1, "In state %c", &inst[num].oldstate);
	if (ret == 1) {continue;}
	ret = sscanf(line1, "  If the current value is %d", &inst[num].from);
	if (ret == 1) {continue;}
	ret = sscanf(line1, "    - Write the value %d", &inst[num].to);
	if (ret == 1) {continue;}
	ret = sscanf(line1, "    - Move one slot to the %s", inst[num].rightorleft);
	if (ret == 1) {continue;}
	ret = sscanf(line1, "    - Continue with state %c", &inst[num].newstate);
	if (ret == 1) {num++; if (num % 2 == 1) {inst[num].oldstate = inst[num-1].oldstate;} continue;}
}
fclose(a);
	int pos = SZ; int state = start;
	printf("steps: %d\n", steps);
	printf("startstate: %c\n", state); getchar();
	for (int i = 0; i < steps; i++) {
		int instr = 0;
		for (int i = 0;  i < num; i++) {
			if (inst[i].oldstate == state && inst[i].from == tape[pos]) {
				instr = i; break;
			}
		}
		if (tape[pos] == inst[instr].from) {
			tape[pos] = inst[instr].to;
			if (strcmp("right", inst[instr].rightorleft) == 0) {pos++;} else {pos--;}
		
		} else if (tape[pos] == inst[instr].from) {tape[pos] = inst[instr].to; 
			if (strcmp("right", inst[instr].rightorleft) == 0) {pos++;} else {pos--;}
		}
		state = inst[instr].newstate;

		if (pos >= 2*SZ) {printf("ERR bSZ\n"); exit(0);}
		else if (pos < 0) {printf("ERR sSZ\n"); exit(0);}
	}
	long sum = 0;
	for (int z = 0; z < SZ*2; z++) {
		if (tape[z] == 1) {
			sum++;
		}
	}
	printf("**checksum: %ld ", sum);
}
