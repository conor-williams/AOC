#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day12 part1 \n"
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
	int count = 0;
	for (int i = 0; i < leny; i++) {
		count++; if (count %200 == 0) { count = 0; printf("inst: %d\n", i);}
		char reg1; char reg2[5];
		int ret1 = sscanf(instrs[i], "cpy %s %c", reg2, &reg1);
		if (ret1 == 2) {if (strlen(reg2) == 1 && reg2[0] - 97 <= 122 && reg2[0] -97 >= 0) {regs[reg1-97] = regs[reg2[0]-97];} else {regs[reg1-97] = atoi(reg2);} continue;}

		int num1;
		int ret2 = sscanf(instrs[i], "inc %c", &reg1);
		if (ret2 == 1) {regs[reg1-97]++; continue;}

		int ret3 = sscanf(instrs[i], "dec %c", &reg1);
		if (ret3 == 1) {regs[reg1-97]--; continue;}

		int ret4 = sscanf(instrs[i], "jnz %c %d", &reg1, &num1);
		if (ret4 == 2) {if (regs[reg1-97] != 0) {i += num1 -1; continue;} else {continue;}}
	}

	//printf("***tot %ld END\n", tot); fflush(stdout);

	fflush(stdout); dup2(fd, 1);
	printf("***reg a %d\n", regs[0]); fflush(stdout);
} 
