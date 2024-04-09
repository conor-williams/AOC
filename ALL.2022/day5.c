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

        a = fopen(argv[1], "r"); printf("2022 Day3\n"); fflush(stdout);
        char line1[1000];

//int lenx = 0;
int leny = 0;
int stacks[10][100];
int stacksPos[10] = {0};
int maxStacks = 0;
while (1) {
        fgets(line1, 50, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1)-1] = '\0';	
	if (line1[0] == '\0') {break; }
	for (int i = 0; i < strlen(line1); i++) {
		int s = 0;
		if ((i - 1) % 4 == 0) {
			s = (i-1)/4;	
			if (s > maxStacks) {maxStacks = s;}
		}
		if (line1[i] != ' ' && isupper((int)line1[i])) {
			stacks[s][stacksPos[s]] = line1[i];
			stacksPos[s]++;
		}
	}

	leny++;
}
for (int i = 0; i <= maxStacks; i++) {
	int tmpStack[100];
	for (int j = 0; j < stacksPos[i]; j++) {
		tmpStack[j] = stacks[i][j];
	}
	for (int j = 0; j < stacksPos[i]; j++) {
		stacks[i][j] = tmpStack[stacksPos[i]-1-j];
	}
}

for (int i = 0; i <= maxStacks; i++) {
	for (int j = 0; j< stacksPos[i]; j++) {
		printf("%c ", stacks[i][j]);
	}
	printf("\n");
}


while (1) {
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1)-1] = '\0';	
	int howmany, from, to;
	sscanf(line1, "move %d from %d to %d", &howmany, &from, &to);
	from--; to--;
	
	for (int k = 0; k < howmany; k++) {
		stacks[to][stacksPos[to]] = stacks[from][stacksPos[from]-1]; 
		stacksPos[from]--;
		stacksPos[to]++;
	}
		
}

fclose(a);
printf("ANS:\n");
for (int i = 0; i <= maxStacks; i++) {
	printf("%c", stacks[i][stacksPos[i]-1]);
}
printf("\n");
}
