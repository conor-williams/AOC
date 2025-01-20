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
//141437363.high
	long long frx1 = xyzr[255].x1;
	long long fry1 = xyzr[374].y1;
	long long frz1 = xyzr[87].z1;

//....not out of range 56379452 41112372 43945492
	//long long x3 = 56379452;
//43944533
	long long x3 = 56379452;
	long long y3 = 41112372;
	long long z3 = 43945492;
/*
	for (; x3 >= x3-10000; x3--) {
	for (; y3 >= y3-10000; y3--) {
	for (; z3 >= z3-10000; z3--) {

	long long minman = 141437357;
		int semitot = 0;
		for (int i = 0; i < leny; i++) {
			if ((abs(xyzr[i].x1 -x3) 
				+ abs(xyzr[i].y1 - y3) +
				abs(xyzr[i].z1 - z3)) <= abs(xyzr[i].r1)) {
				semitot++;
			}
		}
		if (semitot >= 903) {
			if (semitot > 904) {printf("semitot is %d\n", semitot);getchar();}
			//printf("good %lld %lld %lld\n", x3, y3, z3);
			if (x3+y3+z3 < minman) {minman = x3+y3+z3;}
			//continue;
		} else {
///
			printf("out of range %lld %lld %lld\n", x3, fry1, z3);
			printf("started %lld %lld %lld\n", frx1, fry1, frz1);
			printf("not out of range %lld %lld %lld\n", x3, fry1, z3);
			long long tmp1 = (abs(x3) + abs(fry1) + abs(frz1));
			int semi = 0;
			for (int i = 0; i < leny; i++) {
				if ((abs(xyzr[i].x1 -(x3)) 
					+ abs(xyzr[i].y1 - fry1) +
					abs(xyzr[i].z1 - (z3+1))) <= abs(xyzr[i].r1)) {
					semi++;
				}
			}
			assert(semi == 903);
			printf("** ans: %lld\n", tmp1);
			getchar();
///
			//goto resty3;
		}
	
	}
resty3:
		continue;
	}
	}
*/
	//printf("%lld %lld %lld\n", xyzr[255].x1, xyzr[374].y1, xyzr[87].z1);
	
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
		//	printf("semitot is %d\n", semitot);
		//	printf("%d %d %d\n", x2, y2, z2);
		//	printf("%lld %lld %lld\n", xyzr[x2].x1, xyzr[y2].y1, xyzr[z2].z1);
			//exit(0);
		//}	
		
	}
	}
	}
/*
	printf("tmpend\n");
	exit(0);
	tot = 0;
	long long max = 0;
	long long minmax;
	clock_t begin = clock();
	int minx2, miny2, minz2;
	for (int x2 = 0; x2 < leny; x2++) {
		//printf("x2 is %d\n", x2);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("time:%d: %f\n", x2, time_spent); 
	for (int y2 = 0; y2 < leny; y2++) {
	for (int z2 = 0; z2 < leny; z2++) {
		int semitot = 0;
		for (int i = 0; i < leny; i++) {
			if ((abs(xyzr[i].x1 -xyzr[x2].x1) + abs(xyzr[i].y1 - xyzr[y2].y1) +
				abs(xyzr[i].z1 - xyzr[z2].z1)) <= abs(xyzr[i].r1)) {
				semitot++;
			}
		}
		if (semitot >= max) {
			long long tmp1 = (abs(xyzr[x2].x1) + abs(xyzr[y2].y1) + abs(xyzr[z2].z1));
			if (semitot > max) {
				max = semitot;
				minmax = tmp1;
			} else if (semitot == max) {
				if (tmp1 < minmax) {
					minmax = tmp1;
					minx2 = x2;
					miny2 = y2;
					minz2 = z2;
				}
				
			}
		}
	}
	}
	}
*/

	//printf("**minmax %lld %d,%d,%d\n", minmax, minx2, miny2, minz2);
	//printf("**%lld,%lld,%lld\n", xyzr[minx2].x1, xyzr[miny2].y1, xyzr[minz2].z1);
	//printf("**tot %lu\n", tot);
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} getchar();
}
