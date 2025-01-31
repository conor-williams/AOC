#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <signal.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <thread>

using namespace std;
#include <unistd.h>

#define getchar()
int lenx = 0;
int leny = 0;
int LINE = 1000;
//long long ST = (long long)100000000000000;
long long ST = (long long)1000;
//long long ST = 1000;
long long *ll;
int vInc;

long long mp = 1;
struct bus_s {
	int val;
	int offset;
};
vector <struct bus_s> busbus;
int fd;
void myCode(int zzz);

bool sorter(struct bus_s l, struct bus_s r) {
	return l.val > r.val;
}
int endend;
int var_off;
int zMax;

void sigfunc(int a) {
	fflush(stdout); dup2(fd, 1);
	printf("numThreads: %d\n", zMax-1);
	for (int iii = 0; iii < zMax; iii++) {
		printf("current: [[thread:%d %016lld ]]\n", iii+1, ll[iii+1]);
	}
	printf("------------------------------\n");
	close(1);
}
int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);
	printf("SLOW ~15minutes\n");
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("2020 Day13 Part2\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];

	int var_ts;
	int busI[100] = {0};
	int busPos = 0;
	int off = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		//line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);
		if (leny == 0) {
			sscanf(line1, "%d", &var_ts);
		} else if (leny == 1) {
			char *buses = strtok(line1, ",\n");
			busPos = 0;
			do {
				if (strcmp(buses, "x") != 0) {
					busI[busPos] = atoi(buses);
					struct bus_s bb;
					bb.offset = off;		
					bb.val = atoi(buses);
					busbus.push_back(bb);
				} else {
					busI[busPos] = -1;
				}
				off++; busPos++;
			} while ((buses = strtok(NULL, ",\n"))!=NULL);
		}
		leny++;
	}

	if (argc > 2) {ST=atoi(argv[2]);}

	printf("busPos is %d\n", busPos);
	for (int i = 0; i < busPos; i++) {
		printf("%d: %d\n", i, busI[i]);
	}

	endend = busbus.size();
	printf("before...\n");
	for (int zz = 0; zz < endend; zz++) {
		printf("zz: %d - %d - off: %d\n", zz, busbus[zz].val, busbus[zz].offset);
	}

	int max = 0; int mzz;
	for (int zz = 0; zz < endend; zz++) {
		if (busbus[zz].val > max) {mzz = zz; max = busbus[zz].val;}
	}

	printf("max is %d\n", max);
	int sub = busbus[mzz].offset;
	for (int zz = 0; zz < endend; zz++) {
		busbus[zz].offset -= sub;
	}
	printf("after...\n");
	for (int zz = 0; zz < endend; zz++) {
		printf("zz: %d - %d - off: %d\n", zz, busbus[zz].val, busbus[zz].offset);
	}
	var_off = busbus[0].offset;
	vInc = busbus[mzz].val;
	sort(busbus.begin(), busbus.end(), sorter);

	long long ST2 = 1;
	for (int qq = 0; qq < endend-1; qq++) {
		ST2 *= busbus[qq].val-1;
	}


	//printf("maxPossible %lld\n", maxPossible);
	printf("ST2 : %lld\n", ST2);

	//for (long long kk = ST2-100; ; kk++) { if (kk % vInc == 0) {ST2 = kk; break;} }
	for (long long kk = ST-100; ; kk++) { if (kk % vInc == 0) {ST = kk; break;} }
	for (int i = 0; i < endend; i++) {
		printf("%d %d\n", busbus[i].val, busbus[i].offset);
	}
	printf("busbus[1].val is %d\n", busbus[1].val);
	//long long ST3;

	//clock_t startT, endT; double cpu_time_used; 

	for (int qq = 0; qq < endend-1; qq++) { mp *= busbus[qq].val; }

	printf("mp is %lld\n", mp);
	long long * mulwithout = (long long*) malloc( sizeof(long long) * (endend+2));


	for (int rr = 0; rr < endend; rr++) {
		mulwithout[rr] = 1;
		for (int qq = 0; qq < endend; qq++) {
			if (qq == rr) {continue;}
			mulwithout[rr] *= busbus[qq].val;
		}
		printf("mulwithout is %lld\n", mulwithout[rr]);
	}

	long long allmul1 = 1;
	for (int rr = 0; rr < endend; rr++) { allmul1 *= busbus[rr].val; }
	printf("allmul1 is %lld\n", allmul1);
	double left = 1; //allmul1;
	for (int rr = 0; rr < endend; rr++) {
		printf("left before is %f\n", left);
		left -= (double)(1/(double)(mulwithout[rr]));
		printf("left now %.50g\n", left);
	}
	printf("left is %f\n", left);
	double right = 0;
	for (int rr = 0; rr < endend; rr++) {
		right += ((double)busbus[rr].offset / (double)mulwithout[rr]);
		printf("right now %.50g\n", right);
	}
	printf("right is %.50g\n", right);
	printf("left is %.50g\n", left);
	double aa = (((double)right) / ((double)left));
	printf("**ans: %.50g\n", aa);
	double bb = (double)25/(double)0.666;
	printf("**ans: %.50g\n", bb);

	
	
	vector<thread> thr;//thr[busbus[endend-1].val];
	int half = (busbus[endend-1].val)/2;
	printf("half is %d\n", half);
	ll = (long long *)malloc(sizeof(long long)*
			(busbus[endend-1].val+2));
	zMax = busbus[endend-1].val;
//	for (int zzz = half ; zzz > 0; zzz--) 
	/*
	for (int zzz = half ; zzz >= 0; zzz--) {
		printf("YYYrunning normal zzz %d\n", zzz); getchar();
//	for (int zzz = 1 ; zzz < half; zzz++) 
		//printf("starting thread %d\n", zzz);
		myCode(zzz);
		//thr.push_back(thread(myCode, zzz));
		printf("after myCode zzz %d\n", zzz);
	}
	printf("here1..after.\n"); getchar();
	for (int zzz = half+1 ; zzz < busbus[endend-1].val; zzz++) {
	//for (auto &th: thr) { th.join(); }
		printf("running normal zzz %d\n", zzz);
//	for (int zzz = 1 ; zzz < half; zzz++) 
		myCode(zzz);
	}
	*/
	/*
	for (int zzz = 0; zzz < half ; zzz++) {
		printf("running normal zzz %d\n", zzz);
		myCode(zzz);
	}
	*/

	//hif (half == busbus[endend-1].val) {exit(0);}
	thr.clear();

	//solve (N+01)(N+02)(N+03)(N+04)(N+05)(N+06)(N+07)(N+08)(N+09) ==
	//	N*W1*W2*W3*W4*W5*W6*W7*W8*W9; (gsl:odot)
	for (int kkk = half; kkk >= 0; kkk-=2) {
		for (int zzz = kkk; zzz >= kkk-1; zzz--) {
			thr.push_back(thread(myCode, zzz));
		}

		for (auto &th: thr) {
			th.join();
		}
		thr.clear();
	}
	thr.clear();
	for (int zzz = half; zzz < busbus[endend-1].val; zzz++) {
		//printf("starting thread %d\n", zzz);
		thr.push_back(thread(myCode, zzz));
	}
	for (auto &th: thr) {
		th.join();
	}

	if (ll != NULL) {free(ll);}
//end2:
	fflush(stdout); dup2(fd, 1);
	//printf("**ans: %lld\n", ll+var_off);
}

void myCode(int zzz) {
	printf("kicking off %d\n", zzz);
	clock_t startT, endT; double cpu_time_used; 
	startT = clock();
	long long stPossible  = mp *   (zzz); 
	long long maxPossible = mp * (zzz+1);
	for (long long kk = maxPossible; ; kk++) {
		if (kk % vInc == 0) {
			maxPossible = kk;
			break;
		}
	}
	//printf("thread %d -- %lld -> maxPossible (%lld)\n", zzz, stPossible, maxPossible);
	printf("thread %d -- maxPossible (%lld) -> %lld\n", zzz, maxPossible, stPossible);
//	for (ll[zzz] = stPossible; ll[zzz] < maxPossible; ll[zzz] += vInc) { 
	for (ll[zzz] = maxPossible; ll[zzz] >= stPossible; ll[zzz] -= vInc) { 
	
		for (int j = 1; j < endend; j++) {
			if ((ll[zzz]+busbus[j].offset) % busbus[j].val != 0) {
				goto ne;
			}
		}
		fflush(stdout); dup2(fd, 1);
		printf("**ans:%lld\n", ll[zzz]+var_off); fflush(stdout); free(ll); exit(0);
ne:
		continue;
	}
	endT = clock();
	cpu_time_used = ((double) (endT - startT)) / CLOCKS_PER_SEC;
	printf("time %f seconds\n", cpu_time_used);
	printf("leaving thread %d...\n", zzz);
}
//printf("j is %d offset is %d\n", j, busbus[j].offset);
//if (found == 0) {
//}
//if (kk % busbus[0].val != 0) {continue;}
//int found = 0;
/*
   int diff1 = busbus[j].val - (kk % busbus[j].val);
   if (j != 0) {
   if (diff1 == busbus[j].offset) {
   } else {
   found = 1; break;
   }
   } else if (j == 0) {
   if (diff1 == busbus[j].val) {
   } else {
   found = 1; break;
   }
   }
   */
//int minTime = var_ts; int minBus;
/*
   long long va = busbus[0].val;

   for (int ii = 1; ii < (int)busbus.size(); ii++) {
   va *= (busbus[ii].val + busbus[ii].offset);
   printf("va now %lld\n", va);
   }
   printf("va???: %lld\n", va);
   */

/*
   for (long long kk = ST-1000; ; kk++) {
   if (kk % busbus[0].val == 0) {
   ST = kk; break;
   }
   }
   printf("Starting at: %lld\n", ST);
   */

/*
   sort(busbus.begin(), busbus.end(), sorter);
   int tmp1v = busbus[0].val; int tmp1o = busbus[0].offset;
   int tmp2v = busbus[mzz].val; int tmp2o = busbus[mzz].offset;
   */

/*
   busbus[mzz].val = tmp1v;
   busbus[mzz].offset = tmp1o;
   busbus[0].val = tmp2v;
   busbus[0].offset = tmp2o;
   */
