#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
void checkIsTotInTotPrev(int totNow);
int pos = 0;
long tot = 0;
long totPrev[100000];
int totPrevPos = 0;
FILE *a;
int calcfuel(char *line1);
int main(int argc, char **argv)
{
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2019 Day1.1\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	long tot = 0;
	while (1) {
		fgets(line1, 50, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;

		int fuel = calcfuel(line1); 
		printf("fuel: %d\n", fuel);

		if (fuel != 0) {
			tot += fuel;
		}

	}
	fclose(a);

	fflush(stdout); dup2(fd, 1);
	printf("***Total %ld\n", tot);
}

int calcfuel(char *l1)
{
	int num = atoi(l1);
	return (num/3) - 2;
}
