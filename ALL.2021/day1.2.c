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
int calcfuel(int fuelin);
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day1 Part2\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

	char line1[1000];

	long tot = 0;
	int numarr[10000];
	int pos = 0;
	while (1) {
		fgets(line1, 50, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		numarr[pos++] = atoi(line1);
	}
	fclose(a);
	numarr[pos] = -1;

	for (int i = 0; i < pos - 3; i++)
	{
		int num1 = numarr[i+2] + numarr[i+1] + numarr[i];
		int num2 = numarr[i+3] + numarr[i+2] + numarr[i+1];
		printf("comparing %d v %d\n", num1, num2);
		if (num2 > num1) tot++;
	}
	printf("***TOT %ld\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", tot);
}
