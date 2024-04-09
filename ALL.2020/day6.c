#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

FILE *a;
int answers[3000][30] = {0};
int answersPos = 0;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day6 part1\n"); fflush(stdout);
        char line1[2000];

int leny = 0;
while (1) {
        fgets(line1, 1000, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1); fflush(stdout);
	if (line1[0] == '\0') {
		answersPos++;
	} else {
		for (int i = 0; i < strlen(line1); i++) {
			if (!islower((int)line1[i])) {printf("ERROR"); exit(0);}
			printf("%d \n", (int)line1[i]-97); fflush(stdout);
			answers[answersPos][(int)line1[i]-97]++;
		}
	}
	leny++;
}

	if (line1[0] != '\0') {
		answersPos++;
	}
	int tot = 0;
	for (int i = 0; i <= answersPos; i++) {
		for (int j = 0; j < 26; j++) {
			if (answers[i][j] > 0) {
				printf("%d(%d)", answers[i][j],j);
				tot++;
			}
		}
		printf("_____\n");
	}
	printf("tot is  %d\n", tot);
}
