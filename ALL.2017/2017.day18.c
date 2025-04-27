#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 20
#undef _DEBUG_
char line1[SIZE];
char inst[100][20];
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day18.1\n"); fflush(stdout);

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


	char reg1, reg2; int num1, num2; int ret; long long regs[26] = {0};
	long long lastSound;
	for (int i = 0; i < leny; i++) {
		//printf("BEFORE: regs[a] :%ld\n", regs[0]); getchar();
		//printf("inst[%d] is [%s]\n", i, inst[i]); getchar();

		ret = sscanf(inst[i], "snd %d", &num1);
		if (ret == 1) {printf("hey snd");}
		ret = sscanf(inst[i], "snd %c", &reg1);
		if (ret == 1) {lastSound = regs[reg1-97]; continue;}

		ret = sscanf(inst[i], "set %d %d", &num1, &num2);
		if (ret ==2 ) {printf("hey set");}
		ret = sscanf(inst[i], "set %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] = num1; continue;}
		ret = sscanf(inst[i], "set %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] = regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "add %d %d", &num1, &num2);
		if (ret ==2 ) {printf("hey add");}
		ret = sscanf(inst[i], "add %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] += num1; continue;}
		ret = sscanf(inst[i], "add %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] += regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mul %d %d", &num1, &num2);
		if (ret ==2 ) {printf("hey mul");}
		ret = sscanf(inst[i], "mul %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] *= num1; continue;}
		ret = sscanf(inst[i], "mul %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] *= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "mod %d %d", &num1, &num2);
		if (ret ==2 ) {printf("hey mod");}
		ret = sscanf(inst[i], "mod %c %d", &reg1, &num1);
		if (ret == 2) {regs[reg1-97] %= num1; continue;}
		ret = sscanf(inst[i], "mod %c %c", &reg1, &reg2);
		if (ret == 2) {regs[reg1-97] %= regs[reg2-97]; continue;}

		ret = sscanf(inst[i], "rcv %d", &num1);
		if (ret == 1) {printf("hey rcv");}
		ret = sscanf(inst[i], "rcv %c", &reg1);
		if (ret == 1) {if (regs[reg1-97] != 0) {fflush(stdout); dup2(fd, 1); printf("lastSound: %lld\n", lastSound); exit(0); continue;} else {continue;}}

		ret = sscanf(inst[i], "jgz %d %d", &num1, &num2);
		if (ret ==2 ) {printf("hey jgz");}
		ret = sscanf(inst[i], "jgz %c %d", &reg1, &num1);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += num1 -1; continue;} else {continue;}}
		ret = sscanf(inst[i], "jgz %c %c", &reg1, &reg2);
		if (ret == 2) {if (regs[reg1-97] > 0) {i += regs[reg2-97] -1; continue;} else {continue;}}
		printf("ERROR [%s]\n", inst[i]);
	}
	return 0;
}
