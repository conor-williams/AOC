#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
FILE *a;
#define LINE 4000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 3 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

int leny = 0;
unsigned long long ans = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	char *fir = strtok(line1, "m");
	char next[4000];
	do {
		sprintf(next, "m%s", fir);
		printf("next is %s\n", next);
		int one, two; char closeB;
		int ret = sscanf(next, "mul(%d,%d%c", &one, &two, &closeB);
		printf("ret is %d\n", ret);
		if (ret == 3 && closeB == ')') {
			printf("using %s - %d*%d\n\n", next, one, two);
			ans += one*two;
		}
		
	} while ((fir = strtok(NULL, "m")) != NULL);
	leny++;
}
fclose(a);

	
	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", ans);
}
