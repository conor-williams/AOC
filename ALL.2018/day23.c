#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 100
char line1[SIZE];
unsigned long tot = 0;
struct xyzr_s {
	long long x1;
	long long y1;
	long long z1;
	long long r1;
};

struct xyzr_s xyzr[1010];
void printit();
int leny = 0;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day23.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		sscanf(line1, "pos=<%lld,%lld,%lld>, r=%lld", &xyzr[leny].x1, &xyzr[leny].y1,
			&xyzr[leny].z1, &xyzr[leny].r1);
		leny++;
	}
	fclose(a);
	printit();
	long long max = 0;
	int maxi;
	for (int i = 0; i < leny; i++) {
		if (abs(xyzr[i].r1) > max) {max = abs(xyzr[i].r1); maxi = i;}
	}
		
	printf("max: %lld maxi %d\n", max, maxi); getchar();
	tot = 0;
	for (int i = 0; i < leny; i++) {
		if (maxi == i) {tot++; continue;}
		if ((abs(xyzr[i].x1 -xyzr[maxi].x1) + abs(xyzr[i].y1 - xyzr[maxi].y1) + abs(xyzr[i].z1 - xyzr[maxi].z1)) <= max) {
			tot++;
		} else {
			printf("not in range %d\n", i);
		}
	}

	fflush(stdout); dup2(fd, 1);
	
	printf("**maxi is %d tot %lu\n", maxi, tot);
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} getchar();
}
