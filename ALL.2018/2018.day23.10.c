#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <signal.h>

#undef _DEBUG_
#define SIZE 200
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
//man: [138702692] yaa semitot is 917 53654522 42469987 42578183
//138702692 yaa semitot is 917 53654522 42469987 42578183


//[138697281] here1.. yaa semitot is 917 53651812 42469906 42575563
//man: [138697281] yaa semitot is 918 53651564 42470156 42575561
//man: [138697281] yaa semitot is 919 53651322 42470406 42575553
//[138697279] here1.. yaa semitot is 926 53651365 42470406 42575508
//[138697278] here1.. yaa semitot is 934 53651146 42470656 42575476
int	maxsemitot = 934;
long long frmx=  53651146;
long long tox;
long long frmy = 42470656;
long long toy;
long long frmz = 42575476;
long long toz;
long long minman;
long long x4;
long long y4;
long long z4;
long long myincft = 300;
long long myinc = 2;
long long mymaxx4 = 0, mymaxy4 = 0, mymaxz4 = 0;

static void signal_handler(int sig){
	printf("signal caught:::\n");
	printf("max (%11lld) [%3d]: [%12lld,%12lld,%12lld]\n", myinc, maxsemitot, mymaxx4, mymaxy4, mymaxz4);
	printf("cur: %12lld,%12lld,%12lld (myinc: %12lld)\n", x4, y4, z4, myinc);
}

int main(int argc, char **argv)
{
	minman = frmx + frmy + frmz;
	signal(SIGTSTP, signal_handler);


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
	volatile int i;
	printf("leny is %d\n", leny); 



andagain:
	mymaxx4 = frmx; mymaxy4 = frmy; mymaxz4 = frmz;
	frmx = frmx-myincft; tox = frmx+(2*myincft);
	frmy = frmy-myincft; toy = frmy+(2*myincft);
	frmz = frmz-myincft; toz = frmz+(2*myincft);
	int changed = 0;
	long counter = 0;
	for (x4 = frmx; x4 <= tox; x4+=myinc) {
		counter++; if (counter %20 == 0) {printf("x4:: %lld\n", x4);}
	for (y4 = frmy; y4 <= toy; y4+=myinc) {
	for (z4 = frmz; z4 <= toz; z4+=myinc) {
		long long tmpman = x4+y4+z4;
		if (tmpman > minman) {break;}
		volatile int semitot = 0;
		for (i = 0; i < 1000; i++) {
			if ( (abs(xyzr[i].x1 - x4) + abs(xyzr[i].y1 - y4) + abs(xyzr[i].z1 - z4) <= abs(xyzr[i].r1) ) ) 
			{
				semitot++;
			}
		}

		if (semitot > maxsemitot) {printf("special %d\n", semitot);
			changed = 1;printf("man: [%lld] yaa semitot is %d %lld %lld %lld\n", tmpman, semitot, x4, y4, z4);
		}

		if (semitot > maxsemitot) {
			changed = 1; minman = tmpman;
			printf("%lld h2 yaa semitot is %d %lld %lld %lld\n", tmpman, semitot, x4, y4, z4);
			maxsemitot = semitot;
			mymaxx4 = x4; mymaxy4 = y4; mymaxz4 = z4;
			//goto next;
		} else if ((tmpman < minman) && (semitot == maxsemitot)) {
			changed = 1;
			minman = tmpman;
			printf("[%lld] h1.. yaa semitot is %d %lld %lld %lld\n", tmpman, semitot, x4, y4, z4);
			maxsemitot = semitot;
			mymaxx4 = x4; mymaxy4 = y4; mymaxz4 = z4;
			//goto next;
		} else if (tmpman == minman && (semitot == maxsemitot)) {
			printf("equal %d\n", semitot);
		}
	}
	}
	}

next:
	if (changed == 1) {
		printf("max (%11lld)(%11lld) [%3d]: [%11lld,%11lld,%11lld]\n", myinc, myincft, maxsemitot, mymaxx4, mymaxy4, mymaxz4); 
		printf("MAN: [[[( %11lld )]]]] %lld\n",  mymaxx4 + mymaxy4+mymaxz4, minman);
	} else {
		printf("no more..\n");
		exit(0);
	}
	frmx= mymaxx4;
	frmy= mymaxy4;
	frmz= mymaxz4;
	//myincft =  (myincft*7)/9;
	//if (myincft <= 2000) { myincft = 1000;}
	//myinc = (myinc*7)/9;
	//if (myinc <= 2) {myinc = 1; myincft = 300;}
	if (changed == 1) { goto andagain;}
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} 
}
