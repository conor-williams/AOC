#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 100

using namespace std;
char line1[SIZE];
unsigned long tot = 0;
struct xyzr_s {
	long long x1;
	long long y1;
	long long z1;
	long long r1;
};
int maxBeacons = 0;

long long mx1;
long long my1;
long long mz1;
struct xyzr_s xyzr[1010];
void printit();
int leny = 0;
int hone(long long x, int incrx, long long y, int incry, long long z, int incrz);
int totit (long long x1, long long y1, long long z1, long long r1);
int fd;
int main(int argc, char **argv)
{
	//printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day23.2\n"); fflush(stdout);
	printf("	SLOW ~5minutes 50seconds\n"); fflush(stdout);
	fd = dup(1); close(1);

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
	//printit();
	long long max = 0;
	int maxi;
	for (int i = 0; i < leny; i++) {
		if (abs(xyzr[i].r1) > max) {max = abs(xyzr[i].r1); maxi = i;}
	}

	printf("max: %lld maxi %d\n", max, maxi); getchar();
	//if ((abs(xyzr[i].x1 -xyzr[maxi].x1) + abs(xyzr[i].y1 - xyzr[maxi].y1) + abs(xyzr[i].z1 - xyzr[maxi].z1)) <= max) 
	tot = totit(xyzr[maxi].x1, xyzr[maxi].y1, xyzr[maxi].z1, abs(xyzr[maxi].r1));
	printf("COORDS: %lld %lld %lld\n", xyzr[maxi].x1, xyzr[maxi].y1, xyzr[maxi].z1);

	//COORDS or best beacon: 66874149 45054384 46952893
	//NEAR ANS[138697278] here1.. yaa semitot is 934 53651146 42470656 42575476
	int tot2 = 0;
	tot2 = hone(xyzr[maxi].x1, 17000000, xyzr[maxi].y1, 5000000, xyzr[maxi].z1, 5000000);
	printf("%lld %lld %lld\n", mx1, my1, mz1);
	printf("man: %lld\n", abs(mx1) + abs(my1) + abs(mz1));

	printf("**tot %lu(from %d) tot2: %d\n", tot, maxi, tot2);
}

int totit (long long x1, long long y1, long long z1, long long radius) {
	int tot = 0;
	for (int i = 0; i < leny; i++) {
		//if (maxi == i) {tot++; continue;}
		//if ((abs(xyzr[i].x1 -xyzr[maxi].x1) + abs(xyzr[i].y1 - xyzr[maxi].y1) + abs(xyzr[i].z1 - xyzr[maxi].z1)) <= max) 
		if ((abs(xyzr[i].x1 -x1) + abs(xyzr[i].y1 - y1) + abs(xyzr[i].z1 - z1)) <= radius) {
			tot++;
		} else {
			//printf("not in range %d\n", i);
		}
	}
	return tot;
}

int totithone (long long x1, long long y1, long long z1) {
	int tot = 0;
	for (int i = 0; i < leny; i++) {
		//if (maxi == i) {tot++; continue;}
		//if ((abs(xyzr[i].x1 -xyzr[maxi].x1) + abs(xyzr[i].y1 - xyzr[maxi].y1) + abs(xyzr[i].z1 - xyzr[maxi].z1)) <= max) 
		if ((abs(xyzr[i].x1 -x1) + abs(xyzr[i].y1 - y1) + abs(xyzr[i].z1 - z1)) <= xyzr[i].r1) {
			tot++;
		} else {
			//printf("not in range %d\n", i);
		}
	}
	return tot;
}

int hone(long long x, int incrx, long long y, int incry, long long z, int incrz) {
	//COORDS or best beacon: 66874149 45054384 46952893
	if (abs(mx1) + abs(my1) + abs(mz1) == 138697281) {printf("got it...\n"); exit(0);}
	//int maxmax = 0;
	int origBeacons = 0;
	//int trytry = 1;
	//int incrxOrig = incrx; int incryOrig = incry; int incrzOrig = incrz;
	int divs = 15;
	int twomiltwo = 2200000;
	int onemiltwo = 1200000;
	int onemilthree = 1300000;
	int thirtytho = 30000;
	int fivehun = 500;
	int twenty = 21;
	int nearly = 0;
again:
	if (divs < 22) {
		printf("divs < 22\n");
		if (incrx < twomiltwo) {incrx = twomiltwo;}
		if (incry < twomiltwo) {incry = onemiltwo;}
		if (incrz < twomiltwo) {incrz = onemiltwo;}
	} else if (divs >= 22 && divs < 49) {
		if (divs == 22) {divs = 42;}
		printf("divs 22 2 47\n");
		{incrx = onemilthree;}
		{incry = onemilthree;}
		{incrz = onemilthree;}
	}  else if (divs >= 49 && divs < 51) {
		printf("divs 47 -> 49 \n");
		if (divs == 51) {divs = 49;} else {thirtytho--;}
		incrx = thirtytho/100;
		incry = thirtytho;
		incrz = thirtytho;
	} else if (divs >= 51 && divs < 53) {
		printf("divs > 51\n");
		incrx = fivehun/2;
		incry = fivehun;
		incrz = fivehun;
	} else if (divs == 53) {
		nearly = 1;
		incrx = twenty;
		incry = twenty;
		incrz = twenty;
		divs = twenty;
	}

	for (long long x1 = x+incrx; x1 >= x-incrx; x1-=(incrx/divs)) {
		for (long long y1 = y+incry; y1 >= y-incry; y1-=(incry/divs)) {
			for (long long z1 = z+incrz; z1 >= z-incrz; z1-=(incrz/divs)) {
				int bla = totithone(x1, y1, z1);
				if (bla > maxBeacons) {
					mx1 = x1, my1 = y1, mz1 = z1;
					maxBeacons = bla;
				}
			}
		}
	}
	printf("man: (%d) (%lld) -- %lld %lld %lld\n", maxBeacons, abs(mx1) + abs(my1) + abs(mz1), mx1, my1, mz1);
	printf("dist: %lld %lld %lld\n", mx1 - 53643034, my1 - 42478762, mz1 - 42575485);
	x = mx1, y = my1, z = mz1;
	divs++;
	incrx = incrx/2; incry = incry/2; incrz = incrz/2;
	if (nearly == 1) {fflush(stdout); dup2(fd, 1); printf("**ans: %lld\n", abs(mx1) + abs(my1) + abs(mz1)); exit(0);}

	if (origBeacons != maxBeacons) {
		printf("*divs now %d\n", divs);
		origBeacons = maxBeacons;
		goto again;
	} else {
		printf("divs now %d\n", divs);
		goto again;
		/*
		   trytry++;
		//if (trytry == 2) {incrx = incrxOrig; incry = incryOrig; incrz = incrzOrig;}
		printf("incx was %d \n", incrx);
		//incrx = incrx/trytry;
		//incry = incry/trytry;
		//incrz = incrz/trytry;
		printf("trying second TRY: %d hone..incrx %d.\n", incrx, trytry);
		hone(mx1, incrx, my1, incry, mz1, incrz);
		//hone(mx1, my1, mz1, 5000000 - 5000000/trytry, 4000000 - 4000000/trytry, 4000000 - 4000000/trytry);
		//exit(0);
		*/
	}

	return maxBeacons;

}
void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
				xyzr[i].z1, xyzr[i].r1);
	} getchar();
}
//man: (940) (139804261) -- 54196533 42478761 43128967

