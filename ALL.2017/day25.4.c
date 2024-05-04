#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
#define SIZE 20
char line1[SIZE];
int leny = 0;
#define SZ 50
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

char start; int steps;
int num = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);
	int ret;
	ret = sscanf("Begin in state %c\n", &start);
	if (ret == 1) {continue;}
	ret = sscanf("Perform a diagnostic checksum after %d steps.", &steps);
	if (ret == 1) {continue;}

	if (strlen(line1) == 0) {continue;}

	ret = sscanf("In state %c:", &inst[num].oldstate);
	if (ret == 1) {continue;}
	ret = sscanf("  If the current value is %d:", &inst[num].from);
	if (ret == 1) {continue;}
	ret = sscanf("    - Write the value %d.", &inst[num].to);
	if (ret == 1) {continue;}
	ret = sscanf("    - Move one slot to the %s.", inst[num].rightorleft);
	if (ret == 1) {continue;}
	ret = sscanf("    - Continue with state %c.", &inst[num].newstate);
	if (ret == 1) {num++; inst[num].oldstate = inst[num-1].oldstate; continue;}

	ret = sscanf("  If the current value is %d:", &inst[num].from);
	if (ret == 1) {continue;}
	ret = sscanf("    - Write the value %d.", &inst[num].to);
	if (ret == 1) {continue;}
	ret = sscanf("    - Move one slot to the %s.", inst[num].rightorleft);
	if (ret == 1) {continue;}
	ret = sscanf("    - Continue with state %c.", &inst[num].newstate);
	if (ret == 1) {num++; continue;}
}
fclose(a);
	int pos = SZ; int state = start;
	for (int i = 0; i < steps; i++) {
		int instr = 0;
		for (int i = 0;  i < num; i++) {
			if (inst[i].oldstate == state && inst[i].from == tape[pos]) {
				instr = i; break;
			}
		}
		if (state 
		switch (state) {
			case 'A':
				if (tape[pos] == 0) {tape[pos] = 1; pos++;}
				else if (tape[pos] == 1) {tape[pos] = 0; pos--;}
				state = 'B';
				break;

			case 'B':
				if (tape[pos] == 0) {tape[pos] = 1; pos--;}
				else if (tape[pos] == 1) {tape[pos] = 1; pos++;}
				state = 'A';
				break;
		}
		printf("Tape: ");
		for (int z = SZ-3; z < SZ+4; z++) {
			printf("%d ", tape[z]);
		}
		printf("\n"); getchar();
	}
	
}
