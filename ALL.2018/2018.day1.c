#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int pos = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2018 Day1.1\n"); fflush(stdin); fflush(stdout);
        char line1[1000];
long tot = 0;
while (1) {
int num = 0;
        fgets(line1, 50, a);
        if (feof(a)) break;
        if (line1[0] == '+') {
           sscanf(line1, "+%d", &num);
           tot += num;
	} else if (line1[0] == '-') {
           sscanf(line1, "-%d", &num);
           tot -= num;
	}
}
	printf("****TOT %ld\n ", tot);
fclose(a);
}
