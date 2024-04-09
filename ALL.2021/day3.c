#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char ar[1000][50];
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];

int leny = 0;
while (1) {
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
	strcpy(ar[leny], line1);
	leny++;
}
fclose(a);

char numG[strlen(ar[0])];
char numE[strlen(ar[0])];
for (int x = 0; x < strlen(ar[0]); x++) {
	int count0 = 0;
	int count1 = 0;
	for (int y = 0; y < leny; y++)
	{
		if (ar[y][x] == '0') {count0++;} else {count1++;}
	}
	       if (count0 > count1) {
		numG[x] = '0';
		numE[x] = '1';
	} else if (count0 < count1) {
		numG[x] = '1';
		numE[x] = '0';
	} else {
		printf("error..."); exit(0);
	}
}
printf("numG: ");
for (int x = 0; x < strlen(ar[0]); x++) {
	printf("%c", numG[x]);
}
printf("\n");
printf("numE: ");
for (int x = 0; x < strlen(ar[0]); x++) {
	printf("%c", numE[x]);
}
printf("\n");

unsigned int num1 = 0, num2 = 0;
for (int x = 0; x < strlen(ar[0]); x++) {
	if (numG[x] == '1') {
		num1 = num1 | (1 << (strlen(ar[0]) - 1 - x));
	}
	if (numE[x] == '1') {
		num2 = num2 | (1 << (strlen(ar[0]) - 1 - x));
	}
}
printf("***num1 %u num2 %u\n", num1, num2);
printf("***num1 * num2: %u\n", num1*num2);
}
