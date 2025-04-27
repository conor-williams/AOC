#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 50
char line1[SIZE];
int leny = 0;

int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2018 Day16.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int numBlanks = 0;
	int regb[5];
	int op, regA, regB, regC;
	int ans[17][5];
	int rega[5];
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[(int)strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);
	int ret = sscanf(line1, "Before: [%d, %d, %d, %d]", &regb[0], &regb[1], &regb[2], &regb[3]);
	if (ret == 4) {numBlanks = 0; printf("%d %d %d %d]\n", regb[0], regb[1], regb[2], regb[3]); continue;}

	ret = sscanf(line1, "%d %d %d %d", &op, &regA, &regB, &regC);
	if (ret == 4) {
		int regbOrig[5];
		for (int i = 0; i < 4; i++) {
			regbOrig[i] = regb[i];
		}
		
		for (int i = 0; i < 16; i++) {
			for (int i = 0; i < 4; i++) {
				regb[i] = regbOrig[i];
			}
			switch(i) {
				case 0: //addr
					regb[regC] = regb[regA] + regb[regB];
					break;
				case 1: //addi
					regb[regC] = regb[regA] + regB;
					break;
				case 2: //mulr
					regb[regC] = regb[regA] * regb[regB];
					break;
				case 3: //muli
					regb[regC] = regb[regA] * regB;
					break;
				case 4: //banr
					regb[regC] = regb[regA] & regb[regB];
					break;
				case 5: //bani
					regb[regC] = regb[regA] & regB;
					break;
				case 6: //borr
					regb[regC] = regb[regA] | regb[regB];
					break;
				case 7: //bori
					regb[regC] = regb[regA] | regB;
					break;
				case 8: //setr
					regb[regC] = regb[regA];
					break;
				case 9: //seti
					regb[regC] = regA;
					break;
				case 10: //gtir
					if (regA > regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				case 11: //gtir
					if (regb[regA] > regB) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				case 12: //gtrr
					if (regb[regA] > regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				case 13: //eqir
					if (regA == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				case 14:
					if (regb[regA] == regB) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				case 15:
					if (regb[regA] == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				default:
					printf("ERR\n"); exit(0);
			}
			ans[i][0] = regb[0];
			ans[i][1] = regb[1];
			ans[i][2] = regb[2];
			ans[i][3] = regb[3];
		}
		numBlanks = 0;
		continue;
	}

	ret = sscanf(line1, "After: [%d, %d, %d, %d]", &rega[0], &rega[1], &rega[2], &rega[3]);

	if (ret == 4) {
		int count = 0;
		for (int i = 0; i < 16; i++) {
			if (ans[i][0] == rega[0] && ans[i][1] == rega[1] && ans[i][2] == rega[2] && ans[i][3] == rega[3]) {
				printf("match i: %d\n", i);
				count++;
			}
		}
		if (count >= 3) {
			tot++;
		}
		numBlanks = 0;
		continue;
	}	
	if (strlen(line1) == 0) {
		numBlanks++;
		if (numBlanks > 2) {fflush(stdout); dup2(fd, 1); printf("**tot %d\n", tot); exit(0);}
		continue;
	}
	leny++;
}
fclose(a);
	printf("\n");
}
	
