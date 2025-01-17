#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
int tot = 0;
#define SIZE 500
char line1[SIZE];
int leny = 0;

char instr[1000][25];
int instNum =0;
struct insstt_s {
	char four[10];
	int regA;
	int regB;
	int regC;
	int ret;
	int in;
};
struct insstt_s insstt[40];
int mycmp(char four[]);
#define getchar()
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day19.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	//int numBlanks = 0; int regb[5]; int op, regA, regB, regC; int ans[17][5]; int rega[5]; int times = 0;
	while (1) 
	{
		fgets(line1, SIZE -1, a);
		if (feof(a)) break;
		line1[(int)strlen(line1)-1] = '\0';
		//printf("line1 %s\n", line1);
		//printf("line1:::: %s\n", line1);
		strcpy(instr[instNum++], line1);

		leny++;
	}
	fclose(a);
	printf("\n");
	//printf("here1\n"); fflush(stdout);

	{
		int instREG;
		int ret1 = sscanf(instr[0], "#ip %d", &instREG);
		if (ret1 == 1) {
			for (int z = 0; z < instNum-1; z++) {
				strcpy(instr[z], instr[z+1]);
			}
			instNum--;
		}

		{//build up insstt
			for (int k = 0; k < instNum; k++) {	
				char four[10];
				int regA, regB, regC;
				int ret = sscanf(instr[k], "%s %d %d %d", four, &regA, &regB, &regC);
				strcpy(insstt[k].four, four);
				insstt[k].regA = regA;
				insstt[k].regB = regB;
				insstt[k].regC = regC;
				insstt[k].ret = ret;
				insstt[k].in = -1;
				if (ret == 4) {
					insstt[k].in = mycmp(insstt[k].four);
				}

			}
		}
		long long regb[10] = {0};
		int regA, regB, regC;
		regb[0] = 1; //part2 change
			     //printf("instNum is %d\n", instNum); getchar();

		for (int k = regb[instREG]; k < instNum; k++) {	
			//printf("%s\n", instr[k]); fflush(stdout); getchar();
			//char four[10];
			//int ret = sscanf(instr[k], "%s %d %d %d", four, &regA, &regB, &regC);
			regA = insstt[k].regA;
			regB = insstt[k].regB;
			regC = insstt[k].regC;
			//strcpy(four, instt[k].four);
			//in = -1;
			//if (insstt[k].ret == 4) { in = mycmp(insstt[k].four); }
			//in = insstt[k].in;
			regb[instREG] = k;
			//printf("inst: %d (%d %d %d)\n", in, regA, regB, regC); fflush(stdout); 

			if (insstt[k].in != -1) {
				switch(insstt[k].in) {
					case 9: //addr
						regb[regC] = regb[regA] + regb[regB];
						break;
					case 11: //addi
						regb[regC] = regb[regA] + regB;
						//printf("addi regb[regC] is %d\n", regb[regC]);
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
			if (regC ==  instREG) {k = regb[instREG];}
		}
		printf("**regb[0] is %lld\n", regb[0]);
		fflush(stdout); dup2(fd, 1);
		printf("**ans: %lld\n", regb[0]);
		exit(0);
	}
}

int mycmp(char four[]) {
	if (strcmp(four, "addr") == 0) {return 9;}
	else if (strcmp(four, "addi") == 0) {return 11;}
	else if (strcmp(four, "mulr") == 0) {return 15;}
	else if (strcmp(four, "muli") == 0) {return 7;}
	else if (strcmp(four, "banr") == 0) {return 5;}
	else if (strcmp(four, "bani") == 0) {return 1;}
	else if (strcmp(four, "borr") == 0) {return 6;}
	else if (strcmp(four, "bori") == 0) {return 3;}
	else if (strcmp(four, "setr") == 0) {return 8;}
	else if (strcmp(four, "seti") == 0) {return 2;}
	else if (strcmp(four, "gtir") == 0) {return 12;}
	else if (strcmp(four, "gtri") == 0) {return 14;}
	else if (strcmp(four, "gtrr") == 0) {return 13;}
	else if (strcmp(four, "eqir") == 0) {return 4;}
	else if (strcmp(four, "eqri") == 0) {return 0;}
	else if (strcmp(four, "eqrr") == 0) {return 10;}
	else {printf("ERR\n"); exit(0);}
}
