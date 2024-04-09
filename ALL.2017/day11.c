#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

unsigned long long tot = 0;
#define SIZE 22000
char line1[SIZE];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day11.1\n"); fflush(stdout);

int leny = 0;
int pos = 0;
int coords[4] = {0};
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1: %s\n", line1);
	char *first = strtok(line1, ",");
	char secondLast[10];
	do {
		if (strcmp(first, "n") == 0) {
			coords[0]++;
		} else if (strcmp(first, "s") == 0) {
			coords[0]--;
		} else if (strcmp(first, "ne") == 0) {
			coords[1]++;
		} else if (strcmp(first, "sw") == 0) {
			coords[1]--;
		} else if (strcmp(first, "nw") == 0) {
			coords[2]++;
		} else if (strcmp(first, "se") == 0) {
			coords[2]--;
		}
		printf("first: %s\n", first);
		strcpy(secondLast, first);
	} while ((first = strtok(NULL, ",")) != NULL);
	printf("LAST %s\n", secondLast); getchar();
	leny++;
}
	printf("coords: n:%d ne:%d nw:%d\n", coords[0], coords[1], coords[2]);
	
	printf("\nEND\n");

}
