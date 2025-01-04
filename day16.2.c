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
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2018 Day16.2\n"); fflush(stdout);

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
		ops[times].op = op;
		times++;
		for (int i = 0; i < 16; i++) {
			for (int i = 0; i < 4; i++) {
				regb[i] = regbOrig[i];
			}

			switch(i) {
				case 9: //addr
					regb[regC] = regb[regA] + regb[regB];
					break;
				case 11: //addi
					regb[regC] = regb[regA] + regB;
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
				ops[times-1].couldbe[ops[times-1].couldbePos++] = i;
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
		//if (numBlanks > 2) {printf("**tot %d\n", tot); goto next;}
	} else {
		printf("line1:::: %s\n", line1);
		strcpy(instr[instNum++], line1);
	}
		
	leny++;
}
fclose(a);
	printf("\n");
	printf("here1\n"); fflush(stdout);

//next:
	int donear[50]; for (int p = 0; p < 16; p++) {donear[p] = 33;}
	int changed =0;

again:
	for (int op1 = 0; op1 < 16; op1++) {
		if (donear[op1] != 33) {continue;}
		int commonBetween[16]; for (int p = 0; p < 16; p++) {commonBetween[p] = -1;}
		for (int i = 0; i < times; i++) {
			if (ops[i].op == op1) {
				for (int j = 0; j < ops[i].couldbePos; j++) {
					if (ops[i].couldbe[j] != 55) {
						commonBetween[ops[i].couldbe[j]]++;	
					}
				}
			}
		}

		printf("op1: %d -- ", op1);
		int max = 0; int maxi = 0;
		for (int l = 0; l < 16; l++) {
			if (commonBetween[l] > max){max = commonBetween[l]; maxi = l;}
		}
		int num = 0;
		for (int l = 0; l < 16; l++) {
			if (max > 0) {
				if (commonBetween[l] == max) {num++; printf(" %d ", l);}
			}
		}
		printf("\n"); 
		if (num == 1) {
			changed++;
			printf("setting %d to %d\n", op1, maxi); 
			donear[op1] = maxi;
			for (int m = 0; m < times; m++) {
				for (int n = 0; n < ops[m].couldbePos; n++) {
					if (ops[m].couldbe[n] == maxi) {
						ops[m].couldbe[n] = 55;
					}
				}
			}
		} else {
				printf("num is %d\n", num); 
		}
		
	}
	if (changed < 16) {
		//for (int z = 0; z < 16; z++) {printf("op: %d is %d\n", z, done[z]);} 
		goto again;
	}
	for (int i = 0; i < 16; i++) {
		printf("op: %d is %d\n", i, donear[i]);
	}


	//ret = sscanf(line1, "%d %d %d %d", &op, &regA, &regB, &regC);
	{
		int regb[5] = {0};
		int regA, regB, regC, in;
		for (int k = 0; k < instNum; k++) {	
			sscanf(instr[k], "%d %d %d %d", &in, &regA, &regB, &regC);
			printf("inst: %d (%d %d %d)\n", in, regA, regB, regC); fflush(stdout); 
			switch(in) {
				case 9: //addr
					regb[regC] = regb[regA] + regb[regB];
					break;
				case 11: //addi
					regb[regC] = regb[regA] + regB;
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
					if (regb[regA] == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					break;
				default:
					printf("ERR\n"); exit(0);
			}
		}
		dup2(fd,1);
		printf("**regb[0] is %d\n", regb[0]);
		exit(0);
	}
}
	
