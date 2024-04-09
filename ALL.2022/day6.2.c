#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char ar[300][60];
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2022 Day6 part1\n"); fflush(stdout);
        char line1[5000];

//int lenx = 0;
int leny = 0;
int stacks[10][100];
int stacksPos[10] = {0};
int maxStacks = 0;
while (1) {
        fgets(line1, 4999, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1)-1] = '\0';	
	if (line1[0] == '\0') {break; }
	char chars5[6];
	int chars5Pos = 0;
	for (int i = 0; i < strlen(line1)-14; i++) {
		int found1 = 0;
		for (int q = 0; q < 14; q++) {
			for (int r = q+1; r < 14; r++) {
				if (line1[i+q] == line1[i+r]) {
					found1 = 1; goto end;
				}
			}
		}
end:
		if (found1 == 0) {
			printf("ANS: %d\n", i+14);
			goto next;
		}
	}
next:
	leny++;
}
}
