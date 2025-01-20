#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

char instr[100][30];
#define printf2 printf
//#pragma GCC poison printf
//#define printf(fmt, ...) (0)
//int printf(const char *__restrict, ...)  {  return 0; }
int fd;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("Day23.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	int leny = 0;
	int  regs[27] = {0};
	while (1) {

		fgets(line1, 900, a); if (feof(a)) {break;}
		line1[strlen(line1) -1] = '\0';
		// printf("line1 %s", line1);

		strcpy(instr[leny], line1);
		leny++;
	}
	fclose(a);

	for (int i = 0; i < leny; i++) {
		char reg; int ret = 0; int num1;
		printf("instr[i] is %s\n", instr[i]);
		ret = sscanf(instr[i], "hlf %c", &reg);
		if (ret == 1) { printf("here1"); regs[reg-97] /= 2; continue;}
		ret = sscanf(instr[i], "tpl %c", &reg);
		if (ret == 1) { printf("here2"); regs[reg-97] *= 3; continue;}
		ret = sscanf(instr[i], "inc %c", &reg);
		if (ret == 1) {regs[reg-97]++; printf("inc.. %d", regs[reg-97]); continue;}
		ret = sscanf(instr[i], "jmp %d", &num1);
		if (ret == 1) { printf("here3"); i = i +num1-1; continue;}
		ret = sscanf(instr[i], "jie %c, %d", &reg, &num1);
		if (ret == 2) {printf("here4"); if (regs[reg-97] %2 == 0) {i = i + num1 -1; continue;}}
		ret = sscanf(instr[i], "jio %c, %d", &reg, &num1);
		if (ret == 2) {printf("here5"); if (regs[reg-97] == 1) {i = i + num1 -1; continue;}}
	}

	 //while
	printf2("*** a is %d\n", regs[0]);
	fflush(stdout); dup2(fd, 1);
	printf2("*** b is %d\n", regs[1]);
}


