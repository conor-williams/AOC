#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
int main(int argc, char **argv)
{
	printf("%d", argc);
	printf("%s", argv[1]);
	fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r");
	printf("2023 Day4.2\n");

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	int linenum = 0;

	int win[10] = {0};
	int me[25] = {0};
	int cardnum = 0;
	int score = 0;
	int games[300];
	int card[10000];
	while (1) {
		fseek(a, 117*(222 - linenum), SEEK_SET);
		fgets(line1, 1000, a);
		printf("%s", line1);
		if (feof(a)) break;
		linenum++;
		//Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
		sscanf(line1, "Card %d: %d %d %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&cardnum, 
				&win[0], &win[1], &win[2], &win[3], &win[4], &win[5],
				&win[6], &win[7], &win[8], &win[9], 
				&me[0], &me[1], &me[2], &me[3], &me[4], &me[5], &me[6], &me[7],
				&me[8], &me[9], &me[10], &me[11], &me[12], &me[13], &me[14], &me[15],
				&me[16], &me[17], &me[18], &me[19], &me[20], &me[21], &me[22], &me[23],
				&me[24]);
		printf(" %d %d\n", win[4], me[7]);

		int match = 0;
		for (int w = 0; w < 10; w++) {
			for (int m = 0; m < 25; m++) {
				if (win[w] == me[m]) { match++; break;}
			}
		}
		//if (match != -1) {score += match; card[cardnum] = match;}
		if (match != 0) {if (match+cardnum > 223) {match = 223-cardnum;} for (int k = 1; k <= match; k++) {card[cardnum] += card[cardnum + k];} card[cardnum]++;}
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
		sscanf(line1, "Card %d: %d %d %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&cardnum, 
				&win[0], &win[1], &win[2], &win[3], &win[4], &win[5],
				&win[6], &win[7], &win[8], &win[9], 
				&me[0], &me[1], &me[2], &me[3], &me[4], &me[5], &me[6], &me[7],
				&me[8], &me[9], &me[10], &me[11], &me[12], &me[13], &me[14], &me[15],
				&me[16], &me[17], &me[18], &me[19], &me[20], &me[21], &me[22], &me[23],
				&me[24]);
		printf(" %d %d\n", win[4], me[7]);

		int match = 0;
		for (int w = 0; w < 10; w++) {
			for (int m = 0; m < 25; m++) {
				if (win[w] == me[m]) { match++; break;}
			}
		}
		//		if (match != -1) {for (int k = 1; k <= match; k++) {tot += card[cardnum + k];}}
		if (match != 0) {for (int k = 1; k <= match; k++) {printf("tot %d + card %d\n", tot, card[cardnum+k]); tot += card[cardnum + k];} tot++;}
		if (match == 0) {tot++;}

	}

	fflush(stdin); fflush(stdout);
	fclose(a);
	printf("*** Score:  %d ****\n", tot);
	printf("%d", linenum);

	fflush(stdout); dup2(fd, 1);
	printf("***ans:  %d\n", tot);
}

