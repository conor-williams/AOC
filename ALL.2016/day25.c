#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day25 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 200

char instrs[100][20];

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SIZE];
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	strcpy (instrs[leny], line1);
	leny++;
}
fclose(a);
	int regs[26] = {0};
	for (int i = 0; i < 1000; i++) {
		regs[0] = i;
		//int count = 0;
		
		int first = 1; int outprev; int count = 0;
		
		for (int i = 0; i < leny; i++) {
			///printf("instrs[%d] is %s\n", i, instrs[i]);
			//printf("reg a %d\n", regs[0]); fflush(stdout);
			//count++; if (count %10000 == 0) { count = 0; printf("inst: %d\n", i);}
			char reg1; char reg2[5]; char reg3; int num1; int num2;
			
		//	int ret1 = sscanf(instrs[i], "cpy %c %c", &reg3, &reg1);
		//	if (ret1 == 2) {regs[reg1-97] = regs[reg3-97]; continue;}
		//	int ret11 = sscanf(instrs[i], "cpy %d %c", &num1, &reg1);
		//	if (ret11 == 2) {regs[reg1-97] = num1; continue;}

			int ret1 = sscanf(instrs[i], "cpy %s %c", reg2, &reg1);
			if (ret1 == 2) {if (strlen(reg2) == 1 && reg2[0] - 97 <= 122 && reg2[0] -97 >= 0) {regs[reg1-97] = regs[reg2[0]-97];} else {regs[reg1-97] = atoi(reg2);} continue;}

			int ret2 = sscanf(instrs[i], "inc %c", &reg1);
			if (ret2 == 1) {regs[reg1-97]++; continue;}

			int ret3 = sscanf(instrs[i], "dec %c", &reg1);
			if (ret3 == 1) {regs[reg1-97]--; continue;}

			int itmp;
			int ret4444 = sscanf(instrs[i], "jnz %d %d", &num1, &num2);
			if (ret4444 == 2) {if (num1 != 0) {itmp = i+num2-1;  if (itmp >=0 && itmp < leny) {i=itmp;} continue;} else {continue;}}
			int ret44 = sscanf(instrs[i], "jnz %d %c", &num1, &reg1);
			if (ret44 == 2) {if (num1>0) {itmp= i+regs[reg1-97]-1; if (itmp >=0 && itmp < leny) {i=itmp;} continue;} else {continue;}}
			int ret4 = sscanf(instrs[i], "jnz %c %d", &reg1, &num1);
			if (ret4 == 2) {if (regs[reg1-97] != 0) {itmp = i+num1 -1;  if (itmp >=0 && itmp < leny) {i=itmp;} continue;} else {continue;}}
			int ret444 = sscanf(instrs[i], "jnz %c %c", &reg1, &reg3);
			if (ret444 == 2) {if (regs[reg1-97] != 0) {itmp = i+regs[reg3-97]-1;  if (itmp >=0 && itmp < leny) {i=itmp;} continue;} else {continue;}}

			int ret66 = sscanf(instrs[i], "out %d", &num1);
			if (ret66 == 1) {//printf("OUT: %d\n", num1); 
				if (first == 1) {
					first = 2;
					outprev = num1;
					continue;
				} else {
					if (outprev == 1 && num1 == 0) {
						count++;
						if (count == 10000) {break;}
					} else if (outprev == 0 && num1 == 1) {
						if (count == 10000) {break;}
						count++;
					} else {
						break;
					}
					outprev = num1;
					continue;
				}
			}
			int ret6 = sscanf(instrs[i], "out %c", &reg1);
			if (ret6 == 1) {//printf("OUT: %d\n", regs[reg1-97]); 
				if (first == 1) {
					first = 2;
					outprev = num1;
					continue;
				} else {
					if (outprev == 1 && regs[reg1-97] == 0) {
						count++;
						if (count == 1000) {break;}
					} else if (outprev == 0 && regs[reg1-97] == 1) {
						if (count == 1000) {break;}
						count++;
					} else {
						break;
					}
					outprev = regs[reg1-97];
					continue;
				}
			}
			int ret5 = sscanf(instrs[i], "tgl %c", &reg1);
			if (ret5 == 1) {
				int tv = regs[reg1-97]+i;
				if (tv > leny) {printf("OUTSIDE -- CONT\n");}
				if (instrs[tv][0] == 'd' && instrs[tv][1] == 'e') {
					instrs[tv][0] = 'i';
					instrs[tv][1] = 'n';
					//instrs[tv][2] = 'c';
				} else if (instrs[tv][0] == 'i' && instrs[tv][1] == 'n') {
					instrs[tv][0] = 'd';
					instrs[tv][1] = 'e';
					//instrs[tv][2] = 'c';
				} else if (instrs[tv][0] == 't' && instrs[tv][1] == 'g') {
					instrs[tv][0] = 'i';
					instrs[tv][1] = 'n';
					instrs[tv][2] = 'c';
				} else if (instrs[tv][0] == 'j' && instrs[tv][1] == 'n') {
					instrs[tv][0] = 'c';
					instrs[tv][1] = 'p';
					instrs[tv][2] = 'y';
				} else if (instrs[tv][0] == 'c' && instrs[tv][1] == 'p') {
					instrs[tv][0] = 'j';
					instrs[tv][1] = 'n';
					instrs[tv][2] = 'z';
				} else if (instrs[tv][0] == 'o' && instrs[tv][1] == 'u') {
					instrs[tv][0] = 'i';
					instrs[tv][1] = 'n';
					instrs[tv][2] = 'c';
				}
				continue;
			}
				
			printf("INVALID.. CONT [%s]\n", instrs[i]);
		}
		if (count == 1000) {dup2(fd, 1); printf("i:[%d] is good\n", i); exit(0);} else {/*printf("i:%d bad\n", i);*/}
	}

	//printf("***tot %ld END\n", tot); fflush(stdout);

	dup2(fd, 1);
	printf("***reg a %d\n", regs[0]); fflush(stdout);
} 
