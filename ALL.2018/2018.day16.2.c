#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 500
char line1[SIZE];
int leny = 0;
struct ops_s {
	int op;
	int couldbe[50];
	int couldbePos;
};
struct ops_s ops[3000];
char instr[1000][20];
int instNum =0;
int opsReal[16];
int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day16.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int numBlanks = 0;
	int regb[5];
	int op, regA, regB, regC;
	int ans[17][5];
	int rega[5];
	int times = 0;
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[(int)strlen(line1)-1] = '\0';
		printf("line1 %s\n", line1);
		int ret = sscanf(line1, "Before: [%d, %d, %d, %d]", &regb[0], &regb[1], &regb[2], &regb[3]);
		if (ret == 4) {numBlanks = 0; printf("%d %d %d %d]\n", regb[0], regb[1], regb[2], regb[3]); continue;}

		ret = sscanf(line1, "%d %d %d %d", &op, &regA, &regB, &regC);
		if (ret == 4 && numBlanks == 0) {

			int regbOrig[5];
			for (int i = 0; i < 4; i++) {
				regbOrig[i] = regb[i];
			}
			//ops[times].op = op; times++;
			for (int ii = 0; ii < 16; ii++) {
				for (int i = 0; i < 4; i++) {
					regb[i] = regbOrig[i];
				}

				switch(ii) {
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
				ans[ii][0] = regb[0];
				ans[ii][1] = regb[1];
				ans[ii][2] = regb[2];
				ans[ii][3] = regb[3];
			}
			numBlanks = 0;
			continue;
		}

		ret = sscanf(line1, "After: [%d, %d, %d, %d]", &rega[0], &rega[1], &rega[2], &rega[3]);

		if (ret == 4) {
			int count = 0;
			for (int ii = 0; ii < 16; ii++) {
				if (ans[ii][0] == rega[0] && ans[ii][1] == rega[1] && ans[ii][2] == rega[2] && ans[ii][3] == rega[3]) {
					int found = 0;
					for (int zzz = 0; zzz < ops[op].couldbePos; zzz++) {
						if (ii == ops[op].couldbe[zzz]) {
							found = 1;
							break;
						}
					}
					if (found == 0) {
						ops[op].couldbe[ops[op].couldbePos] = ii;
						ops[op].couldbePos++;
						printf("match i: %d\n", ii);
					}
				}
			}
			numBlanks = 0;
			continue;
		}	
		if (strlen(line1) == 0) {
			numBlanks++;
			//if (numBlanks > 2) {printf("**tot %d\n", tot); goto next;}
		} else {
			printf("line1:::: %s\n", line1);
			strcpy(instr[instNum++], line1);
		}

		leny++;
	}
	fclose(a);
	for (int ii = 0; ii < 16; ii++) {
		int count = 0;
		for (int zzz = 0; zzz < ops[ii].couldbePos; zzz++) {
			printf("ops[ii].couldbe[zzz] %d\n", ops[ii].couldbe[zzz]);
			if (ops[ii].couldbe[zzz] != -99) {
				count++;
			}
		}
		printf("-----count: %d----------\n", count);
		getchar();

		printf("ii: %d count %d\n", ii, count);
		if (count == 1) {
			printf("here1.here22222");
			int rem = 0;
			for (int zzz = 0; zzz < ops[ii].couldbePos; zzz++) {
				if (ops[ii].couldbe[zzz] != -99) {
					rem = ops[ii].couldbe[zzz];
					ops[ii].couldbe[zzz] = -99;
				}
			}
			printf("rem for ii(%d) is %d\n", ii, rem);
			opsReal[ii] = rem;
			for (int jj = 0; jj < 16; jj++) {
				int ind = 0;
				if (ii == jj) {continue;}
				for (int kk = 0; kk < ops[jj].couldbePos; kk++) {
					if (ops[jj].couldbe[kk] == rem) {
						printf("setting to minus 1\n");
						ops[jj].couldbe[kk] = -99;
						//break;
					}
				}
			}
		}
		if (ii == 15) {
			int found = 0;
			for (int kk = 0; kk < 16; kk++) {
				for (int zzz = 0; zzz < ops[kk].couldbePos; zzz++) {
					if (ops[kk].couldbe[zzz] != -99) {
						found = 1;
						goto aft;
					}
				}
			}
aft:
			if (found == 0) {break;} else {ii = -1;}
		}
		//getchar();


	}

	//ret = sscanf(line1, "%d %d %d %d", &op, &regA, &regB, &regC);
	{
		int regb[5] = {0};
		int regA, regB, regC, in;
		for (int k = 0; k < instNum; k++) {	
			sscanf(instr[k], "%d %d %d %d", &in, &regA, &regB, &regC);
			printf("inst: %d (%d %d %d)\n", in, regA, regB, regC); fflush(stdout); 
			switch(opsReal[in]) {
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
		}
		printf("**regb[0] is %d\n", regb[0]);
		fflush(stdout); dup2(fd,1);
		printf("**ans: %d\n", regb[0]);
		exit(0);
	}
}

