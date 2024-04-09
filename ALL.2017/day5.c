#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2017 Day5.1\n"); fflush(stdout);

        char line1[3000];

int NUMS = 1070;
int nums[NUMS];
int leny = 0;
while (1) 
{
        fgets(line1, 3000, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
 	line1[strlen(line1)-1] = '\0';
        sscanf(line1, "%d", &nums[leny]);
	leny++;
}
	int pos = 0;
	int steps = 0;
	while(pos < leny) {
		int prevPos = pos;
		pos += nums[pos];
		nums[prevPos]++;
		steps++;
	}
	printf("***steps is [%d]\n", steps);
}

