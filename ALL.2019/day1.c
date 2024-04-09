#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void checkIsTotInTotPrev(int totNow);
int pos = 0;
long tot = 0;
long totPrev[100000];
int totPrevPos = 0;
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2019 Day1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

loopit:
long tot = 0;
while (1) {
int num = 0;
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;

	printf("num: %d fuel: %d\n", num, fuel);
        fuel = calcfuel(line1); tot += fuel;
	while (fuel != 0) {
		fuel = calcfuel(fuel);
		tot += fuel;
	}

}
printf("*****Total %ld\n", tot);
fclose(a);
}

int calcfuel(char *line1)
{
        num = atoi(line1);
        return = (num/3) - 2;
}
