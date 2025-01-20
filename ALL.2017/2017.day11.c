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
struct xyz_s {
	int x;
	int y;
	int z;
};
struct xyz_s co;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2017 Day11.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	int leny = 0;
	co.x = 0; co.y = 0; co.z = 0;
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
				co.y++;
				co.z--;
			} else if (strcmp(first, "s") == 0) {
				co.y--;
				co.z++;
			} else if (strcmp(first, "ne") == 0) {
				co.x++;
				co.z--;
			} else if (strcmp(first, "sw") == 0) {
				co.x--;
				co.z++;
			} else if (strcmp(first, "nw") == 0) {
				co.x--;
				co.y++;
			} else if (strcmp(first, "se") == 0) { 
				co.x++;
				co.y--;
			} else {
				printf("ERR"); exit(0);
			}
			printf("first: %s\n", first);
			strcpy(secondLast, first);
		} while ((first = strtok(NULL, ",")) != NULL);
		printf("LAST %s\n", secondLast); getchar();
		leny++;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", (abs(co.x) + abs(co.y) + abs(co.z))/2);

}
