#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
#define SIZE 200
char line1[SIZE];

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);

//Generator A starts with 703
//Generator B starts with 516
int leny = 0;
int num1, num2;
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
	tot = 0;
	unsigned long long int num1L = num1;
	unsigned long long int num2L = num2;
	unsigned long int const2 =  65535 << 16;
	printf("const2: %lu\n", const2);
	for (int i = 0; i < 40000000; i++) {
		//printf("%llu V %llu\n", num1L, num2L); getchar();
		num1L = ((unsigned long long)num1L * (unsigned long long)16807 ) % (unsigned long long)2147483647;
		num2L = ((unsigned long long)num2L * (unsigned long long)48271 ) % (unsigned long long)2147483647;

		if ((num1L & 65535) == (num2L & 65535)) {
			//printf("match");
			tot++;
		} else if ((num1L & const2) == (num2L & const2)) {
			//tot++; 
		}
	}
	printf("**tot is %d\n", tot);
	
}

