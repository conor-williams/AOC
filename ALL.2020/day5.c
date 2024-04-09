#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];

int leny = 0;
int idmax = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int from = 0;
	int to = 127;
	for (int i = 0; i < 7; i++) {
		if (line1[i] == 'F') {
			to = (from + ((to+1) - from)/2)-1;
			from = from;
		} else if (line1[i] == 'B') {
			from = (from + ((to+1) - from)/2);
			to = to;
		}	
		printf("%d -> %d\n", from, to);
	}
	printf("seat: %d -> %d\n", from, to);

	int fromc = 0;
	int toc = 7;
	for (int i = 7; i < 10; i++) {
		if (line1[i] == 'L') {
			toc = (fromc + ((toc+1) - fromc)/2)-1;
			fromc = fromc;
		} else if (line1[i] == 'R') {
			fromc = (fromc + ((toc+1) - fromc)/2);
			toc = toc;
		}	
	
	}
	
	printf("col: %d -> %d\n", fromc, toc);
	int id = 0;
	if (fromc == toc && from == to) {
		id = (from*8)+fromc;
		if (id > idmax) {idmax = id;}
		printf("id: %d\n", id);
	} else {
		printf("ERROR"); exit(0);
	}
	leny++;
}
fclose(a);
	printf("**idmax: %d\n", idmax);
}
