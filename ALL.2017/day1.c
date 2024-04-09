#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int pos = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day8.2\n"); fflush(stdin); fflush(stdout);

        char line1[3000];
        fgets(line1, 3000, a);
        fclose(a);
printf("line1 %s\n", line1);

int tot = 0;
        int bprev = line1[0] - '0';
        for (int f = 1; f < 3000; f++)  {
	     char bChar = line1[f];
	     if (bChar == '\0' || bChar == '\n') {break;}
	     int bNum = line1[f] - '0';
	     if (bprev == bNum) {
		tot += bprev;
	     }
             bprev = bNum;
        }
        printf("******TOT: %d\n", tot);
}

