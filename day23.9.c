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
//#define getchar()
//max(2)(500)[912]:[55374522,41094987,42923183]MAN:[[[(139392692)]]]]
//man: [138702692] yaa semitot is 917 54374522 41749987 42578183

//max (       5000)(    1000000) [917]: [   53374522,   40749987,   41578183]
//MAN: [[[(   135702692 )]]]] 138702692



long long minman = 138702692;
int	maxsemitot = 916;
long long frmx=  54374522;
long long tox;
long long frmy = 41749987;
long long toy;
long long frmz = 42578183;
long long toz;
long long x4;
long long y4;
long long z4;
long long myincft = 1000000;
long long myinc = 10000;
long long mymaxx4 = 0, mymaxy4 = 0, mymaxz4 = 0;

static void signal_handler(int sig){
	printf("signal caught:::\n");
	printf("max (%11lld) [%3d]: [%12lld,%12lld,%12lld]\n", myinc, maxsemitot, mymaxx4, mymaxy4, mymaxz4);
	printf("cur: %12lld,%12lld,%12lld (myinc: %12lld)\n", x4, y4, z4, myinc);
}

int main(int argc, char **argv)
{
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

	//maxsemitot = 917;

	frmx = frmx-myincft; tox = frmx+(2*myincft);
	frmy = frmy-myincft; toy = frmy+(2*myincft);
	frmz = frmz-myincft; toz = frmz+(2*myincft);
andagain:
	mymaxx4 = frmx;
	mymaxy4 = frmy;
	mymaxz4 = frmz;
	for (x4 = frmx; x4 <= tox; x4+=myinc) {
	long counter = 0; counter++; if (counter %20 == 0) {printf("x4:: %lld\n", x4);}
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
		//printf("semitot is %d\n", semitot);
		//if (x4+y4+z4 <= 139393492 && semitot > maxsemitot) {printf("yaa %d\n", semitot);}

		if (semitot > maxsemitot) {printf("special %d\n", semitot);
			printf("man: [%lld] yaa semitot is %d %lld %lld %lld\n", tmpman, semitot, x4, y4, z4);
		}
		if (semitot > maxsemitot) {minman = tmpman; printf("%lld yaa semitot is %d %lld %lld %lld\n", tmpman, semitot, x4, y4, z4); maxsemitot = semitot; mymaxx4 = x4; mymaxy4 = y4; mymaxz4 = z4;}
		else if (tmpman < minman && semitot == maxsemitot) {minman = tmpman; printf("%lld yaa semitot is %d\n", tmpman, semitot); maxsemitot = semitot; mymaxx4 = x4; mymaxy4 = y4; mymaxz4 = z4;};
	}
	}
	}

next:
	printf("max (%11lld)(%11lld) [%3d]: [%11lld,%11lld,%11lld]\n", myinc, myincft, maxsemitot, mymaxx4, mymaxy4, mymaxz4); 
	printf("MAN: [[[( %11lld )]]]] %lld\n",  mymaxx4 + mymaxy4+mymaxz4, minman);
	frmx= mymaxx4 - myincft;
	tox = mymaxx4 + myincft;
	frmy= mymaxy4 - myincft;
	toy = mymaxy4 + myincft;
	frmx= mymaxz4 - myincft;
	tox = mymaxz4 + myincft;
	myincft =  (myincft*7)/9;
	if (myincft <= 2000) { myincft = 1000;}
	myinc = (myinc*7)/9;
	if (myinc <= 2) {myinc = 1; myincft = 300;}
	goto andagain;
}

void printit() {
	for (int i = 0; i < leny; i++) {
		printf("%d: %lld --- %lld --- %lld --- %lld\n", i, xyzr[i].x1, xyzr[i].y1, 
			xyzr[i].z1, xyzr[i].r1);
	} 
}
