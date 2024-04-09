#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2015 day10 part1\n"
#define _DEBUG_

int tot = 0;
#define SIZE 100000000

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	char ans[SIZE] = "";
	double perc = 0; int lenprev = 0;
	for (int z = 0; z<40; z++) {
		for (int i = 0; i < (int)strlen(line1); i++) {
			int count = 1;
			for (int j = i+1; j < (int)strlen(line1); j++) {
				if (line1[i] == line1[j]) {
					count++;
				} else if (line1[i] != line1[j]) {
					break;	
				}
			}
			//printf("%d%c", count, line1[i]);
			sprintf(ans, "%s%d%c", ans, count, line1[i]);
			i += count-1;
		}
		printf("\n");
		
		if (lenprev != 0) {
			perc = (double)strlen(ans) / (double)lenprev;
			printf("LEN: %d z:%d (%f)", (int)strlen(ans), z, perc);
		} else {
			printf("LEN: %d z:%d", (int)strlen(ans), z);
		}
		if ((int)strlen(ans)+10000 > SIZE) {
			printf("WARNING SIZE...exit\n"); exit(0);
		}
		lenprev = (int)strlen(ans);
		strcpy(line1, ans);
	}

}
fclose(a);

}
