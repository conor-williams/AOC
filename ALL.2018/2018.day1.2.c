#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
void checkIsTotInTotPrev(int totNow);
int pos = 0;
long tot = 0;
long totPrev[100000];
int totPrevPos = 0;
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	printf("SLOW ~30seconds\n");
        a = fopen(argv[1], "r"); printf("2018 Day1.2\n"); fflush(stdin); fflush(stdout);

        char line1[1000];

loopit:
while (1) {
int num = 0;
        fgets(line1, 50, a);
        if (feof(a)) break;
totPrev[totPrevPos] = tot;
totPrevPos++;
        if (line1[0] == '+') {
           sscanf(line1, "+%d", &num);
           tot += num;
	} else if (line1[0] == '-') {
           sscanf(line1, "-%d", &num);
           tot -= num;
	}
        checkIsTotInTotPrev(tot); 
}
fseek(a, 0, SEEK_SET);
goto loopit;
	printf("****TOT %ld ", tot);
fclose(a);
}
void checkIsTotInTotPrev(int totNow) {
     for (int h = 0; h < totPrevPos; h++) {
	if (totNow == totPrev[h]) {
                printf("****Found: %d\n", totNow);
		fclose(a);
		exit(0);
        }
     }
     
}
