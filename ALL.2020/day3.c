#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char ar[323][31];
int lenx = 0;
int leny = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day3\n"); fflush(stdout);
        char line1[1000];

while (1) {
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1) -1] = '\0';
	lenx = strlen(line1);
	strcpy(ar[leny], line1);
	leny++;
}

printf("lenx leny %d %d\n", lenx, leny);
int x = 0;
int trees = 0;
for (int y = 0; y < leny;)
{
	x=(x+3)%(lenx);
	y=y+1;
	if (ar[y][x] == '#') {trees++;}
}
	printf("**trees %d\n", trees);	
}
