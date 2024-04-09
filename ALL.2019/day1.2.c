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
int calcfuel(int fuelin);
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2019 Day1.2\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

long tot = 0;
while (1) {
        int num = 0;
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;

        int fuel = calcfuel(atoi(line1)); tot += fuel;
	printf("num: %d fuel: %d\n", num, fuel);
	while (fuel != 0 && fuel > 0) {
		fuel = calcfuel(fuel);
		printf("fuel %d\n", fuel);
		tot += fuel;
	}

}
printf("*****Total %ld\n", tot);
fclose(a);
}

int calcfuel(int fuelin)
{
printf("in calcfuel...");
        int f = fuelin/3; if (f > 2) {f = f -2;} else {f=0;}
        return f;

}
