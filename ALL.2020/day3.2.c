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
long long trees[5] = {0};
int right[] = {1, 3, 5, 7, 1};
int down[] = {1, 1, 1, 1, 2};

for (int z = 0; z < 5; z++) {
	int x = 0;
	for (int y = 0; y < leny;)
	{
		x=(x+right[z])%(lenx);
		y=y+down[z];
		if (ar[y][x] == '#') {trees[z]++;}
	}
}

	printf("**trees MUL %lld %lld %lld %lld %lld %llu\n", trees[0], trees[1], trees[2], trees[3], trees[4], trees[0]*trees[1]*trees[2]*trees[3]*trees[4]);	
}
