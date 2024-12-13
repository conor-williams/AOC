#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 2 part1\n"); fflush(stdout);
        char line1[LINE];

int leny = 0;
	unsigned long long num = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	char *first = strtok(line1, " \0");
	char *secon = strtok(NULL, " \0");
	int pos = 0, posPrev;
	int bad = 0;
	int init = 1;
	do {
		int fir = atoi(first);
		int sec = atoi(secon);
		//int val = atoi(first) - atoi(secon);
		int val = fir - sec;
		printf("%s -- %s val is %d\n", first, secon, val);
		//sign
		if (init == 1) {
			if (val > 0) {
				pos = 1;
			} else if (val < 0) {
				pos = 0;
			}
		} else if (init == 0) {
			posPrev = pos;
			if (val > 0) {
				pos = 1;
			} else if (val < 0) {
				pos = 0;
			}

			if (posPrev != pos) {
				bad = 1;
				break;
			}
		}
		if (abs(val) >= 1 && abs(val) <= 3) {
			//ok
		} else {
			bad = 1; break;
		}
		first = secon;
		init = 0;
	} while ((secon = strtok(NULL, " \0")) != NULL);
	if (bad == 0) {
		num++;
	}	
	leny++;
}
	printf("**ans %lld\n", num);
fclose(a);

}
