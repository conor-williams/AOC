#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
unsigned long long tot = 0;
#define SIZE 22000
char line1[SIZE];
int main(int argc, char **argv)
{
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day11.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
int leny = 0;
int coords[4] = {0};
int max = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1: %s\n", line1);
	char *first = strtok(line1, ",");
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

		int tosort[4];
		//biggest
		int ind1, ind2;
		if (abs(coords[0]) >= abs(coords[1]) && abs(coords[0]) >= abs(coords[2])) {
			tosort[2] = coords[0];
			ind1 = 1;
			ind2 = 2;
		} else if (abs(coords[1]) >= abs(coords[2]) && abs(coords[1]) >= abs(coords[0])) {
			tosort[2] = coords[1];
			ind1 = 0;
			ind2 = 2;
		} else if (abs(coords[2]) >= abs(coords[0]) && abs(coords[2]) >= abs(coords[1])) {
			tosort[2] = coords[2];
			ind1 = 0;
			ind2 = 1;
		}

		if (abs(coords[ind1]) >= abs(coords[ind2])) {
			tosort[1] = coords[ind1];
		} else {
			tosort[1] = coords[ind2];
		}
		
		if (tosort[2] > 0 && tosort[1] > 0) {
			int sum = tosort[2] + tosort[1];
			if (sum > max) {max = sum;}
		} else if (tosort[2] < 0 && tosort[1] < 0) {
			int sum = abs(tosort[2] +tosort[1]);
			if (sum > max) {max = sum;}
		}
	} while ((first = strtok(NULL, ",")) != NULL);
	leny++;
}
	printf("coords: n:%d ne:%d nw:%d\n", coords[0], coords[1], coords[2]);

	printf("***max: %d\n" , max);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n" , max);
	
	//printf("\nEND\n");

}
