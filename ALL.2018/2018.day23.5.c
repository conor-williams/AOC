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
//pos=<66874149,45054384,46952893>, r=99487886
	long long x3Orig = 66874149;
	long long y3Orig = 45054384;
	long long z3Orig = 46952893;

	long long x3 = x3Orig;
	long long y3 = y3Orig;
	long long z3 = z3Orig;

	long long minman = 99999999;

	for (x3+=100000; x3 >= x3Orig-100000; x3-=1000) {
	for (y3+=100000; y3 >= y3Orig-100000; y3-=1000) {
	for (z3+=100000; z3 >= z3Orig-100000; z3-=1000) {
	
		int semitot = 0;
		for (int i = 0; i < leny; i++) {
			if ((abs(xyzr[i].x1 -x3) 
				+ abs(xyzr[i].y1 - y3) +
				abs(xyzr[i].z1 - z3)) <= 99487886) {
				semitot++;
			}
		}
		printf("semitot is %d\n", semitot);
		if (semitot > 935) {printf("semitot is %d\n", semitot);getchar();}
		if (semitot == 935) {
			if (semitot > 935) {printf("semitot is %d\n", semitot);getchar();}
			printf("good %lld %lld %lld\n", x3, y3, z3);
			if (x3+y3+z3 < minman) {minman = x3+y3+z3;}
			//continue;
		} else {
/*
			printf("out of range %lld %lld %lld\n", x3, y3, z3);
			printf("started %lld %lld %lld\n", x3Orig, y3Orig, z3Orig);
			printf("not out of range %lld %lld %lld\n", x3+1, y3+1, z3+1); getchar();
			long long tmp1 = (abs(x3) + abs(y3) + abs(z3)); getchar();
			int semi = 0;
			for (int i = 0; i < leny; i++) {
				if ((abs(xyzr[i].x1 -(x3)) 
					+ abs(xyzr[i].y1 - fry1) +
					abs(xyzr[i].z1 - (z3+1))) <= abs(xyzr[i].r1)) {
					semi++;
				}
			}
			//assert(semi == 903);
			printf("** ans: %lld\n", tmp1);
			getchar();
///
*/
			//goto resty3;
		}
	
	}
	}
	}

	printf("**minman %lld\n ", minman);
	//, minx2, miny2, minz2);
	//printf("**%lld,%lld,%lld\n", xyzr[minx2].x1, xyzr[miny2].y1, xyzr[minz2].z1);
	//printf("**tot %lu\n", tot);
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} getchar();
}
