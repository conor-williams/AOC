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

        a = fopen(argv[1], "r"); printf("2020 Day1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

long tot = 0;
int numarr[300];
int pos = 0;
while (1) {
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
        numarr[pos++] = atoi(line1);
}
numarr[pos] = -1;
fclose(a);

for (int i = 0; i < pos; i++)
{
    int firstnum = numarr[i];
    for (int j = i; j < pos; j++) {
        int secondnum = numarr[j];
        if (firstnum + secondnum == 2020) {
		printf("Yatzee: %d,%d prod: %d\n", 
			firstnum, secondnum, firstnum*secondnum);
	}
    }
}
}
