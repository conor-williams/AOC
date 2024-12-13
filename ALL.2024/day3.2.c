#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

FILE *a;
#define LINE 4000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 3 Part 2\n"); fflush(stdout);
        char line1[LINE];

int leny = 0;
unsigned long long ans = 0;
int doit = 1;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	char *end_tok1;
	char *fir = strtok_r(line1, "m", &end_tok1);
	char next[4000];
	do {
		sprintf(next, "m%s", fir);
		printf("next is %s\n", next);
		int one, two; char closeB;
		int ret = sscanf(next, "mul(%d,%d%c", &one, &two, &closeB);

		if (ret == 3 && closeB == ')' && doit == 1) {
			printf("using %s - %d*%d\n\n", next, one, two);
			ans += one*two;
		}

		char *end_tok2;
		char *ne = strtok_r(next, "d", &end_tok2);
		char ne2[4000];
		do {
			sprintf(ne2, "d%s", ne);
			char br;
			int ret2 = sscanf(ne2, "do(%c", &br); 
			if (ret2 == 1 && br == ')') {
				doit = 1;
				printf("got a do...\n");
			}
			int ret3 = sscanf(ne2, "don't(%c", &br);
			if (ret3 == 1 && br == ')') {
				doit = 0;
				printf("got a dont\n");
			}
			
		} while ((ne = strtok_r(NULL, "d", &end_tok2)) != NULL); 
		
	} while ((fir = strtok_r(NULL, "m", &end_tok1)) != NULL);
	leny++;
}
fclose(a);

	printf("**ans %llu\n", ans);
}
