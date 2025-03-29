#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <vector>
#include <algorithm>
#include <sys/time.h>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
int y22;

clock_t start, end1;
double cpu_time_used;
#define SX 2000
//char grid[SX][SX];
//char gridDia[SX][SX];
map <int, map <int, int>> grid, gridDia;
#define SZ2 4000000
#ifdef _EX1_ 
#	define SZ 20
	int DIST = 2;
#else 
#	define SZ 4000000
	int DIST = 1000;
#endif

vector <int> rr;	
int fd;
void sigfunc(int a) {
	fflush(stdout); dup2(fd, 1);
	printf("[[ currentval: %d of %d rr.size:%d]]\n", y22, SZ, (int)rr.size());
	end1 = clock();
	printf("time: %f\n",  ((double) (end1 - start)) / CLOCKS_PER_SEC);
	start = clock();
	close(1);
}

//#define SZ 20
//char oGrid[SZ][SZ];
int lenx = 0;
int leny = 0;
unsigned long long findit();
struct sb_s {
	int senX;
	int senY;
	int beaX;
	int beaY;
	int man;
};

//#define PAD 200000000
#define PAD 0

struct sb_s sb[1000];

//void populateDia(int x, int y, int);
void printit();
int maxSenX = 0;
int minSenX = 9999999;
int maxBeaX = 0;
int minBeaX = 9999999;
int maxSenY = 0;
int minSenY = 9999999;
int maxBeaY = 0;
int minBeaY = 9999999;

//int yline = 2000000;
int yline = 0;
int withinDiamond(int ll, int iswithinX, int iswithinY);
int moveToRightEdge(int ll, int y);

int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);

#ifdef _EX1_
	printf("compiled with _EX1_\n");
#endif
	a = fopen(argv[1], "r"); printf("2022 Day 15-2\n"); fflush(stdout);
	printf("SLOW ~1minute and change\n");
	fd = dup(1); close(1);
	char line1[LINE];

	if (argc > 2) {DIST = atoi(argv[2]);}
	printf("using random DIST %d\n", DIST);

	//system("date");
	/*
	   for (int y = 0; y < 4000000; y++) {
	   for (int x = 0; x < 4000000; x++) {
	   }
	   }
	   */
	//system("date");
	//printf("after..loop .\n");
	int numBeacon = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		int senX, senY;
		int beaX, beaY;
		sscanf(line1, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
				&senX, &senY, &beaX, &beaY); 
#ifdef _DEBUG_
		printf("leny: %d %d %d %d %d\n", leny, senX, senY, beaX, beaY); getchar();
#endif
		sb[leny].senX = senX;
		sb[leny].senY = senY;
		sb[leny].beaX = beaX;
		sb[leny].beaY = beaY;
		sb[leny].man = abs(beaX- senX) + abs(beaY - senY);

		grid[senY][senX] = 'S';	
		grid[beaY][beaX] = 'B';	

		if (senX > maxSenX) {maxSenX = senX;}
		if (senX < minSenX) {minSenX = senX;}
		if (beaX > maxBeaX) {maxBeaX = beaX;}
		if (beaX < minBeaX) {minBeaX = beaX;}

		if (senY > maxSenY) {maxSenY = senY;}
		if (senY < minSenY) {minSenY = senY;}
		if (beaY > maxBeaY) {maxBeaY = beaY;}
		if (beaY < minBeaY) {minBeaY = beaY;}

		numBeacon++;
		leny++;
	}
	fclose(a);
	getchar();
	leny = leny;
	lenx = maxSenX;

	vector <int> veAll;
	for (int ll = 0; ll < numBeacon; ll++) {
		veAll.push_back(ll);
	}
	vector <int> ve;
	srand(time(NULL));
	printf("SZ is %d\n", SZ);
	int y; 
	while (1) {
				
		//for (int y = 0; y < SZ; y++) 
		do {
			y = rand()%SZ;
		} while (find(rr.begin(), rr.end(), y) != rr.end());
		
		//printf("y now %d\n", y);
		int syy = y-DIST;
		syy = syy < 0? 0: syy;
		int eyy = y+DIST;
		eyy = eyy > SZ? SZ: eyy;
		//printf("syy eyy %d %d\n", syy, eyy);
		for (y22 = syy; y22 <= eyy; y22++) {
		//for (y22 = 0; y22 <= SZ; y22++) {
			//printf("y is %d\n", y);
			//if (find(rr.begin(), rr.end(), y) != rr.end()) {continue;}
			rr.push_back(y22);
			//y22 = y;
			for (int x = 0; x < SZ; x++) {
				ve.clear();
again:
				for (auto ll: veAll) {
					//printf("ll is %d\n", ll);
					//if (ll == -33) {continue;}
					if (find(ve.begin(), ve.end(), ll) != ve.end()) {continue;}
					int xold = x;
					x = withinDiamond(ll, x, y22);
					if (xold != x) {
						if (x > SZ) {
							/*
							 int yIn = sb[ll].senY;
							 int m1 = sb[ll].man;
							 if (y>=m1 + yIn) {printf("1removed %d\n", ll); veAll[ll] = -33;}
							 */
							//sprintf("going to next\n");
							goto next;
						} else {
							/*
							   int yIn = sb[ll].senY;
							   int m1 = sb[ll].man;
							   if (y>=m1 + yIn) {printf("2removed %d\n", ll); veAll[ll] = -33;}
							   else { ve.push_back(ll); }
							   */
							{ ve.push_back(ll); }
							goto again;
						}
					}
				}
				printf("rr.size() is %d\n", (int)rr.size());
				printf("ans: %llu %d %d\n", (unsigned long long)(((unsigned long long)x*4000000)+y22), x, y22);
				fflush(stdout); dup2(fd, 1); 
				printf("**ans: %llu\n", (unsigned long long)(((unsigned long long) x * SZ)+y22));
				exit(0);
			}
next:
			continue;
		}
	}
	printf("ERR after\n");
	exit(0);

	int count = 0;
	//int y2 = yline;
	int count2 = 0;

	for (int y = 0; y < SZ; y++) {
		for (int x = 0; x < SZ; x++) {
			char cval = gridDia[y][x];
			printf("val is %c\n", cval);
			if (cval != '#' && cval != 'B') {
				fflush(stdout); dup2(fd, 1);
				printf("**ans: %llu\n", (unsigned long long) ((SZ2*x)+y));
				exit(0);
			}
		}
	}


	unsigned long long ans = findit();
	printf("**count is %d\n", count);
	printf("**count2 is %d\n", count2);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", ans);
}
unsigned long long findit() {
	/*
	   unsigned long long ans = 0;
	   for (int y = 0; y < SZ; y++) {
	   for (int x = 0; x < SZ; x++) {
	   if (oGrid[y][x] == 'X') {
	   ans = (unsigned long long)( (SX * x) + y);
	   return ans;
	//printf("**ans: %d\n", (SX*x)+y); exit(0);
	}
	}
	}
	*/
	return (unsigned long long) 1;
}

void printit() {
	printf("in printit...lenx %d leny %d\n", lenx, leny);
	//for (int y = 0; y < leny-PAD; y++) {
	//for (int x = 0; x < lenx-PAD; x++) {
	for (int y = 0; y < SZ; y++) {
		for (int x = 0; x < SZ; x++) {
			//printf("%c", oGrid[y][x]);
			//printf("%c", gridDia[y][x]); fflush(stdout);
		}
		printf("\n");
	}
	printf("\n");
	printf("leaving printit...\n");
}

/*
   int moveToRightEdge(int ll, int iswithinY)	
   {
//int xIn = sb[ll].senX;
int yIn = sb[ll].senY;
int m1 = sb[ll].man;
for (int y = -m1; y <= +m1; y++) {
if (y + yIn != iswithinY) {continue;}
if (y+yIn < 0)     {continue;}
if (y+yIn > SZ)    {continue;}

int xEnd = m1-abs(y);
return xEnd+1; +xIn
}
printf("ERR should be in diamond...\n"); exit(0);

}
*/

int withinDiamond(int ll, int iswithinX, int iswithinY) {
	//printf("in within di:%d x:%d, y:%d \n", ll, iswithinX, iswithinY); fflush(stdout);
	int xIn = sb[ll].senX;
	int yIn = sb[ll].senY;
	int m1  = sb[ll].man;

	int y = iswithinY-yIn;
	int xEnd  = m1-abs(y);
	int xStart  = -(m1-abs(y));
	int x = iswithinX-xIn;
	//return iswithinY >= -m1+yIn && iswithinY <= m1+yIn ? xEnd+xIn+1:iswithinX;
	if (iswithinY >= -m1+yIn && iswithinY <= m1+yIn && y+yIn >= 0 && y+yIn <= SZ &&
			x >= xStart && x <= xEnd && x+xIn >= 0 && x+xIn <= SZ) {
		//printf("larger: %d V %d\n", xEnd+xIn+1, iswithinX);
	        return xEnd+xIn+1;
	} else {
		return iswithinX;
	}
	/*
//	
	for (int y = -m1; y <= +m1; y++) {
		if (y + yIn != iswithinY) {continue;}
		assert(y == iswithinY-yIn);
		if (y+yIn < 0)     {continue;}
		if (y+yIn > SZ)    {continue;}

		int xEnd    =   m1-abs(y);
		int xStart  = -(m1-abs(y));
		assert(xEnd == m1-abs(iswithinY-yIn));
		assert(xEnd == m1-abs(y));
		assert(iswithinY >= -m1+yIn);
		assert(iswithinY <= +m1+yIn);
		assert(y+yIn >= 0);
		assert(y+yIn <= SZ);

		printf("here1...\n");
		//printf("for %d -> %d\n", xStart, xEnd);
		for (int x = xStart; x <= xEnd; x++) {
			if (x+xIn != iswithinX) {continue;}
			if (x+xIn < 0)  {continue;}
			if (x+xIn > SZ) {continue;}
			assert(x == iswithinX-xIn);
			assert(x+xIn >= 0);
			assert(x+xIn <= SZ);

			//printf("is within diamond: %d y:%d edge: %d\n", ll, y+yIn, xEnd);
			return xEnd+xIn+1;
			//return 1;
		}
	}
	*/
	//printf("not within...\n");
	//return iswithinX;
}
/*
//if (inner_it->first-PAD <= 20 && inner_it->first-PAD >= 0) {
////	if (it->first-PAD <=20 && it->first-PAD >= 0) {

if (gridDia[it->first][inner_it->first] == '#') {
printf("HASH %d %d\n", inner_it->first-PAD, it->first-PAD);
//printf("#");
count++;
} else if (gridDia[it->first][inner_it->first] == 'B') {
printf("B %d %d\n", inner_it->first-PAD, it->first-PAD);
//printf("B");
} else {
//printf("OTHER: %d %d\n", inner_it->first-PAD, it->first-PAD);
printf("O");
count2++;
//exit(0);
}
//	}
//}
//}
*/
//Sensor at x=21PAD774, y=3136587: closest beacon is at x=2561642, y=2914773
//Sensor at x=3983829, y=2469869: closest beacon is at x=3665790, y=2180751
//memset(grid,  46 /*.*/, sizeof(grid));
//memset(gridDia, 46 /*.*/, sizeof(gridDia));
