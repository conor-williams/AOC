#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long tot = 0;
long totPrev[100000];
int totPrevPos = 0;
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];

long tot = 0;
int numarr[10000];
int pos = 0;
while (1) {
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
        if (line1[0] == '\0' || line1[0] == ' ' || line1[0] == '\n') {
	    pos++;
        } else {
            numarr[pos] += atoi(line1);
        }
}
fclose(a);
numarr[pos] = -1;

int biggest = 0;
for (int k = 0; k < pos; k++)
{
    printf("comparing %d v big: %d\n", numarr[k], biggest);
    if (numarr[k] > biggest) {biggest = numarr[k];}
}
printf("***BIG %d\n", biggest);
}
