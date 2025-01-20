#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
#define SIZE 500
char line1[SIZE];
int leny = 0;

char instr[1000][25];
int instNum =0;
int mycmp(char four[]);
#define getchar()
int main(int argc, char **argv)
{
//        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("//2018 Day21.1\n"); fflush(stdout);

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
//	printf("\n"); printf("here1\n"); fflush(stdout);

	{
		int instREG;
		int ret1 = sscanf(instr[0], "#ip %d", &instREG);
		if (ret1 == 1) {
			for (int z = 0; z < instNum-1; z++) {
				strcpy(instr[z], instr[z+1]);
			}
			instNum--;
		}

		long long regb[10] = {0};
		int regA, regB, regC, in;
		regb[0] = 1;

		printf("#include <stdlib.h>\n");
		printf("#include <stdio.h>\n");
		printf("#include <unistd.h>\n");
		printf("unsigned long long regb[6] = 0;\n");
		printf("void printit();\n");
		printf("static void *array[] = { &&zero, &&one,&&two,&&three, &&four, &&five, &&six, &&seven,&&eight, &&nine, &&ten, &&eleven, &&twelve, &&thirteen,&&fourteen, &&fifteen, &&sixteen, &&seventeen, &&eighteen, &&nineteen, &&twenty, &&twentyone, &&twentytwo, &&twentythree, &&twentyfour, &&twentyfive, &&twentysix, &&twentyseven, &&twentyeight, &&twentynine, &&thirty, &&thirtyone};\n");fflush(stdout);
		printf("int main(void) {\n");
		printf("regb[0] = XYZ;\n");

		for (int k = regb[instREG]; k < instNum; k++) {	
			//printf("%s\n", instr[k]); fflush(stdout);
			char four[10];
			int ret = sscanf(instr[k], "%s %d %d %d", four, &regA, &regB, &regC);
			if (ret == 4) { in = mycmp(four); }
			regb[instREG] = k;
			//printf("inst: %d (%d %d %d)\n", in, regA, regB, regC); fflush(stdout); 
			char myop;
			char myop2[10];
			printf("%d:\n", k);
			
			switch(in) {
				case 9: //addr
					regb[regC] = regb[regA] + regb[regB];
					
					myop = '+';
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c regb[%d];\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 11: //addi
					myop = '+';
					regb[regC] = regb[regA] + regB;
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c %d;\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
					//printf("addi regb[regC] is %d\n", regb[regC]);
					break;
				case 15: //mulr
					myop = '*';
					regb[regC] = regb[regA] * regb[regB];
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c regb[%d];\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 7: //muli
					myop = '*';
					regb[regC] = regb[regA] * regB;
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c %d;\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 5: //banr
					myop = '&';
					regb[regC] = regb[regA] & regb[regB];
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c regb[%d];\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 1: //bani
					myop = '&';
					regb[regC] = regb[regA] & regB;
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c %d;\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 6: //borr
					myop = '|';
					regb[regC] = regb[regA] | regb[regB];
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c regb[%d];\n", regC, regA, myop, regB);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 3: //bori
					myop = '|';
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] = regb[%d] %c %d;\n", regC, regA, myop, regB);
					//regb[regC] = regb[regA] | regB;
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 8: //setr
					myop = '=';
					regb[regC] = regb[regA];
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] %c regb[%d];\n", regC, myop, regA);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 2: //seti
					myop = '=';
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("regb[%d] %c %d;\n", regC, myop, regA);
					//regb[regC] = regA;
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 12: //gtir
					if (regA > regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					myop = '>';
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("if (%d %c regb[%d]) {regb[%d] = 1;} else {regb[%d] = 0;}\n", 
						regA, myop, regB, regC, regC);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 14: //gtir
					if (regb[regA] > regB) {regb[regC] = 1;} else {regb[regC] = 0;}
					myop = '>';
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("if (regb[%d] %c %d) {regb[%d] = 1;} else {regb[%d] = 0;}\n", 
						regA, myop, regB, regC, regC);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 13: //gtrr
					if (regb[regA] > regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					myop = '>';
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("if (regb[%d] %c regb[%d]) {regb[%d] = 1;} else {regb[%d] = 0;}\n", 
						regA, myop, regB, regC, regC);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 4: //eqir
					if (regA == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					strcpy(myop2, "==");
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("if (%d %s regb[%d]) {regb[%d] = 1;} else {regb[%d] = 0;}\n", 
						regA, myop2, regB, regC, regC);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 0:
					if (regb[regA] == regB) {regb[regC] = 1;} else {regb[regC] = 0;}
					strcpy(myop2, "==");
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("if (regb[%d] %s %d) {regb[%d] = 1;} else {regb[%d] = 0;}\n", 
						regA, myop2, regB, regC, regC);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				case 10:
					if (regb[regA] == regb[regB]) {regb[regC] = 1;} else {regb[regC] = 0;}
					strcpy(myop2, "==");
					printf("//%s\n", instr[k]);
					printf("printf(\"%s\");\n", instr[k]);
					printf("if (regb[%d] %s regb[%d]) {regb[%d] = 1;} else {regb[%d] = 0;}\n", 
						regA, myop2, regB, regC, regC);
					printf("regb[4] = regb[4]+1;\n");
					printf("printit();\n");
					break;
				default:
					printf("ERR\n"); exit(0);
			}
			if (regC ==  instREG) {/*k = regb[instREG];*/

				printf("if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirty;}\n");}
		}
		//printf("printf("%llu\n"**regb[0] is %lld\n", regb[0]);
		printf("\n}\n\nvoid printit() { printf(\"%llu [[%llu]] %llu %llu %llu %llu\\n\", regb[0], regb[1], regb[2], regb[3], regb[4], regb[5]); getchar(); }");
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
