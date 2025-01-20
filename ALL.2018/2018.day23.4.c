#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <assert.h>

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
	
	for (int x2 = 0; x2 < leny; x2++) {
	for (int y2 = 0; y2 < leny; y2++) {
	for (int z2 = 0; z2 < leny; z2++) {
		long long tmp1 = (abs(xyzr[x2].x1) + abs(xyzr[y2].y1) + abs(xyzr[z2].z1));
		///255 374 87
		if (tmp1 == 141437363) {
			int semitot = 0;
			for (int i = 0; i < leny; i++) {
				if ((abs(xyzr[i].x1 -xyzr[x2].x1) 
					+ abs(xyzr[i].y1 - xyzr[y2].y1) +
					abs(xyzr[i].z1 - xyzr[z2].z1)) <= abs(xyzr[i].r1)) {
					semitot++;
				}
			}
			if (semitot >= 935) {
				printf("larger.or equal..\n"); getchar();
			}
		}	
		
	}
	}
	}
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} getchar();
}
