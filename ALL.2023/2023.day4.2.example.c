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
        int games[300];
        int card[10000];

fseek(a, 0, SEEK_SET);
        while (1) {
	    fseek(a, 49*(5 - linenum), SEEK_SET);
            fgets(line1, 1000, a);
printf("LINE: %s\n", line1);
            if (feof(a)) break;
            linenum++;
//Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
	    sscanf(line1, "Card %d: %d %d %d %d %d | %d %d %d %d %d %d %d %d",
		&cardnum, 
		&win[0], &win[1], &win[2], &win[3], &win[4],
		&me[0], &me[1], &me[2], &me[3], &me[4], &me[5], &me[6], &me[7]);
	    //printf(" %d %d\n", win[4], me[7]);

		int match = 0;
		for (int w = 0; w < 5; w++) {
			for (int m = 0; m < 8; m++) {
				if (win[w] == me[m]) { match++; break;}
			}
		}
                //if (match != 0) {score += match; card[cardnum] = match;}
                if (match != 0) {for (int k = 1; k <= match; k++) {card[cardnum] += card[cardnum + k];} card[cardnum]++;} 
		else (card[cardnum] = 1);
	printf("card[cardnum] (%d) set to %d\n", cardnum, card[cardnum]);
		if (cardnum == 1) break;
        }
fseek(a, 0, SEEK_SET);
int tot = 0;
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

		int match = 0;
		for (int w = 0; w < 5; w++) {
			for (int m = 0; m < 8; m++) {
				if (win[w] == me[m]) { match++; break;}
			}
		}
printf("LOOP-------\n");
                if (match != 0) {for (int k = 1; k <= match; k++) {printf("tot %d + card %d\n", tot, card[cardnum+k]); tot += card[cardnum + k];} tot++;}
		if (match == 0) {tot++;}
printf("LOOP-------\n");
        }
printf("------------");
for (int i=1 ; i < 7; i++) {
	printf("%d..", card[i]);
}
printf("------------");
        fflush(stdin); fflush(stdout);
        fclose(a);
printf("*** Score:  %d ****\n", tot);
printf("%d", linenum);
}

