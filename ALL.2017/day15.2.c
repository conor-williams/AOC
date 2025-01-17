#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define SIZE 200
char line1[SIZE];
//compile: -Wl,--stack,999777666
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day15.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

//Generator A starts with 703
//Generator B starts with 516
int leny = 0;
int num1, num2;
struct num_s {
	unsigned long long num1L;
	unsigned long long num2L;
};
struct num_s ar[5000000];
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1: %s\n", line1);
	
	sscanf(line1, "Generator A starts with %d", &num1);
	sscanf(line1, "Generator B starts with %d", &num2);
	
	tot = 0;
	leny++;
}
fclose(a);
	printf("num1 %d num2 %d\n", num1, num2);
	unsigned long long int num1L = num1;
	unsigned long long int num2L = num2;
	unsigned long int const2 =  65535 << 16;
	printf("const2: %lu\n", const2);
	int pos1 = 0;
	for (int i = 0; pos1 < 5000000; i++) {
		num1L = ((unsigned long long)num1L * (unsigned long long)16807 ) % (unsigned long long)2147483647;
		if (num1L % 4 == 0) {
			ar[pos1++].num1L = num1L;
		}
	}
	
	int pos2 = 0;	
	for (int i = 0; pos2 < 5000000; i++) {
		num2L = ((unsigned long long)num2L * (unsigned long long)48271 ) % (unsigned long long)2147483647;
		if (num2L %8 == 0) {
			ar[pos2++].num2L = num2L;
		}
	}

	
	tot = 0;
	for (int i = 0; i < 5000000; i++) {
		//printf("%llu V %llu\n", num1L, num2L); getchar();
		if ((ar[i].num1L & 65535) == (ar[i].num2L & 65535)) {
			//printf("%llu V %llu (%d)\n", num1L, num2L, i); getchar();
			//printf("match");
			tot++;
		} else if ((num1L & const2) == (num2L & const2)) {
			//tot++; 
		}
	}

	printf("**tot is %d\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);
	
}

