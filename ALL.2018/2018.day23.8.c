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
volatile int leny = 0;
#define getchar()

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
//max is 903: 255 374 87
//max is 903: 56379458 41112372 43945533
//        long long frx1 = xyzr[255].x1;
 //       long long fry1 = xyzr[374].y1;
  ////      long long frz1 = xyzr[87].z1;
//141437363.high

	//printf("%lld %lld %lld\n", frx1, fry1, frz1);
//....not out of range 56379452 41112372 43945492

	//long long x3Orig = 56379458;
	///long long y3Orig = 41112372;
	//long long z3Orig = 43945533;

	//long long minman = 99999999;

	long long minx3 = 99999999;
	long long miny3 = 99999999;
	long long minz3 = 99999999;

//	long long x3Orig = 55389458;
//	long long y3Orig = 41102372;
//	long long z3Orig = 42945533;

 //	long long x3Orig = 55379958;
//	long long y3Orig = 41101872;
//	long long z3Orig = 42935533;

	
//**minx3 55389458
// **miny3 41102372
// **minz3 42945533
//
//**minx3 55379988
// **miny3 41101372
// **minz3 42935033

// 	long long x3Orig = 55379988;
//	long long y3Orig = 41101372;
//	long long z3Orig = 42935033;
//**minx3 55379962
// **miny3 41101147
// **minz3 42934783
// 	long long x3Orig = 55379962;
////	long long y3Orig = 41101147;
//	long long z3Orig = 42934783;

	long long manmin2 = 999999999;
//**minx3 55379962
// **miny3 41101047
// **minz3 42934683
//**manmin2 139415692
// 	long long x3Orig = 55379962;
//	long long y3Orig = 41101047;
//	long long z3Orig = 42934683;
//**minx3 55375962
// **miny3 41095047
// **minz3 42924683
//**manmin2 139395692
// 	long long x3Orig = 55375962;
//	long long y3Orig = 41095047;
//	long long z3Orig = 42924683;


//**minx3 55375022
// **miny3 41094987
// **minz3 42923683
//**manmin2 139393692
// 	long long x3Orig = 55375022;
//	long long y3Orig = 41094987;
//	long long z3Orig = 42923683;
//max is 903: 56379458 41112372 43945533

        //long long x3Orig = xyzr[255].x1;
        //long long y3Orig = xyzr[374].y1;
        //long long z3Orig = xyzr[87].z1;

	//long long x3 = x3Orig;
	//long long y3 = y3Orig;
	//long long z3 = z3Orig;
//	for (x3+=100000; x3 >= x3Orig-100000; x3-=100) {
//	for (y3+=100000; y3 >= y3Orig-100000; y3-=100) {
//	for (z3+=100000; z3 >= z3Orig-100000; z3-=100) {
	volatile int i;
	printf("leny is %d\n", leny); getchar();

	long long maxx = 0; long long maxy = 0; long long maxz = 0;
	long long minx = 99999999; long long miny = 99999999; long long minz = 99999999;
//	for (volatile int x4 = 0; x4 < leny; x4++) {
////	for (volatile int y4 = 0; y4 < 1000; y4++) {
//	for (volatile int z4 = 0; z4 < 1000; z4++) {
	int x4 = 0; int y4 = 0; int z4 = 0;
	for (; x4 < 1000; x4++, y4++, z4++) {
	{
	{
		if (xyzr[x4].x1 > maxx) {maxx = xyzr[x4].x1;}
		if (xyzr[y4].y1 > maxy) {maxy = xyzr[y4].y1;}
		if (xyzr[z4].z1 > maxz) {maxz = xyzr[z4].z1;}

		if (xyzr[x4].x1 < minx) {minx = xyzr[x4].x1;}
		if (xyzr[y4].y1 < miny) {miny = xyzr[y4].y1;}
		if (xyzr[z4].z1 < minz) {minz = xyzr[z4].z1;}
/*
		volatile int semitot = 0;
		for (i = 0; i < 1000; i++) {
			if ((abs(xyzr[i].x1 - xyzr[x4].x1) + abs(xyzr[i].y1 - xyzr[y4].y1) 
				+ abs(xyzr[i].z1 - xyzr[z4].z1)) <= abs(xyzr[i].r1))
			{
				semitot++;
			}
		}

		printf("s: [%4d] ((%3d,%3d,%3d))\n", semitot, x4, y4, z4);
*/
	}
	}
	}

	printf("max %12lld %12lld %12lld\n", maxx, maxy, maxz);
	printf("min %12lld %12lld %12lld\n", minx, miny, minz);
	printf("**minx3 %lld\n ", minx3);
	printf("**miny3 %lld\n ", miny3); printf("**minz3 %lld\n ", minz3);
	printf("after...\n"); fflush(stdout);
	printf("**manmin2 %lld\n ", manmin2);
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} 
}
/* if (x3 < minx3) {minx3 = x3;} if (y3 < minx3) {miny3 = y3;} if (z3 < minz3) {minz3 = z3;} */
/*
	int max123 = 0; int xmax, ymax, zmax;
	for (int x = 0; x < leny; x++) {
	for (int y = 0; y < leny; y++) {
	for (int z = 0; z < leny; z++) {
		int semitot = 0;
		if (141437363 == abs(xyzr[x].x1) + abs(xyzr[y].y1) + abs(xyzr[z].z1)) {
			for (int i = 0; i < leny; i++) {
				if ((abs(xyzr[i].x1 - xyzr[x].x1) 
					+ abs(xyzr[i].y1 - xyzr[y].y1) +
					abs(xyzr[i].z1 - xyzr[z].z1)) <= abs(xyzr[i].r1)) {
					semitot++;
				}
			}
			if (semitot > max123) {max123 = semitot; xmax = x; ymax = y; zmax = z;}
			printf("semitot is %d\n", semitot); 
		}
	}
	}
	}
	
	printf("max is %d: %d %d %d\n", max123, xmax, ymax, zmax); 
	printf("max is %d: %lld %lld %lld\n", max123, xyzr[xmax].x1, xyzr[ymax].y1, xyzr[zmax].z1); 
*/
