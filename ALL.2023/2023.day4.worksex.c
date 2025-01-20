#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
void main(int argc, char **argv)
{
        printf("%d", argc);
        printf("%s", argv[1]);
        fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r");
        printf("Day4.1\n");
        fflush(stdin); fflush(stdout);
        char line1[1000];
        int linenum = 0;

	int win[5] = {0};
	int me[8] = {0};
	int cardnum = 0;
	int score = 0;
        while (1) {
            fgets(line1, 1000, a);
printf("%s", line1);
            if (feof(a)) break;
            linenum++;
//Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
	    sscanf(line1, "Card %d: %d %d %d %d %d | %d %d %d %d %d %d %d %d",
		&cardnum, 
		&win[0], &win[1], &win[2], &win[3], &win[4],
		&me[0], &me[1], &me[2], &me[3], &me[4], &me[5], &me[6], &me[7]);
	    printf(" %d %d\n", win[4], me[7]);

		int match = -1;
		for (int w = 0; w < 5; w++) {
			for (int m = 0; m < 8; m++) {
				if (win[w] == me[m]) { match++; break;}
			}
		}
		if (match != -1) {score += pow(2, match);}
        }
        fflush(stdin); fflush(stdout);
        fclose(a);
printf("*** Score:  %d ****\n", score);
printf("%d", linenum);
}

