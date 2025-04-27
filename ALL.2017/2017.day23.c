#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 30
char line1[SIZE];
char inst[100][50];
int main(int argc, char **argv)
{
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day23.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
int leny = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(inst[leny], line1);
	leny++;
}
fclose(a);
	long long regs[26] = {0}; 
	int mul = 0;
	for (int i = 0; i < leny; i++) {
		char reg1, reg2;
		int num1, num2; int ret = 0;
		printf("inst[%d] %s\n", i, inst[i]);

		ret = sscanf(inst[i], "set %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] = num1; continue;}
		ret = sscanf(inst[i], "set %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] = regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "sub %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] -= num1; continue;}
		ret = sscanf(inst[i], "sub %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] -= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mul %c %d", &reg1, &num1);
		if (ret == 2) {printf("in mul\n"); mul++; regs[reg1-97] *= num1; continue;}
		ret = sscanf(inst[i], "mul %c %c", &reg1, &reg2);
		if (ret == 2) {printf("in mul\n"); mul++; regs[reg1-97] *= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "jnz %d %d", &num1, &num2);
		if (ret == 2) {if (num1 != 0) {i += num2-1;} continue;}
		ret = sscanf(inst[i], "jnz %c %d", &reg1, &num2);
		if (ret == 2) {if (regs[reg1-97] != 0) {i += num2-1;} continue;}
	}
	printf("***tot is ^^ [%d]\n", tot);
	
	fflush(stdout); dup2(fd, 1);
	printf("**mul is %d\n", mul);
	return 0;
}
