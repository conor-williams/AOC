#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
struct prize_s {
	long long x1, y1;
	long long x2, y2;
	long long px, py;
};
//struct prize_s prizes[500];
deque <struct prize_s> de;

int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 13 Part 1\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	struct prize_s pr;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		if (line1[0] == '\0') {
			continue;
		} else {
			long long x1, y1;
			int ret1 = sscanf(line1, "Button A: X+%lld, Y+%lld", &x1, &y1);
			if (ret1 == 2) {
				pr.x1 = x1; pr.y1 = y1;	
				continue;
			} 

			long long x2, y2;
			int ret2 = sscanf(line1, "Button B: X+%lld, Y+%lld", &x2, &y2);
			if (ret2 == 2) {
				pr.x2 = x2; pr.y2 = y2;	
				continue;
			}

			long long px, py;
			int ret3 = sscanf(line1, "Prize: X=%lld, Y=%lld", &px, &py);
			if (ret3 == 2) {
				pr.px = px;
				pr.py = py;
				pr.px = px+(long long)10000000000000;
				pr.py = py+(long long)10000000000000;
				de.push_back(pr);
				continue;
			}
		}
		leny++;
	}
	fclose(a);

	{
		long long totCost = 0;
		for (auto it = de.begin(); it != de.end(); it++) {
			struct prize_s p2 = *it;
			printf("---------\n");

			int minCost = 9999999;
			int minCostOrig = minCost;
			for (int b1 = 0; b1 <= 100; b1++) {
				for (int b2 = 0; b2 <= 100; b2++) {
					long long sumx = (b1 * p2.x1 + b2 *p2.x2);
					long long sumy = (b1 * p2.y1 + b2 *p2.y2);
					if (sumx == p2.px && sumy == p2.py) {
						int cost = (3 * b1) + (1 * b2);
						printf("b1: %d b2: %d\n", b1, b2);
						if (cost < minCost) {minCost = cost;}
					}

				}
			}
			if (minCost != minCostOrig) {
				printf("minCost = %d\n", minCost);
				totCost += minCost;
			} else {
				printf("NONE....\n");
			}
		}
		printf("**ans %lld\n", totCost);

	}getchar();


	long long totCost = 0;
	for (auto it = de.begin(); it != de.end(); it++) {
		struct prize_s pr = *it;

		long long minCost = 9999999999999999;
		long long minCostOrig = minCost;

		printf("%lld %lld %lld %lld %lld %lld\n", pr.px, pr.py, pr.x1, pr.y1, pr.x2, pr.y2);
		
		long long topb2 = (pr.px * pr.y1) - (pr.py * pr.x1);
		long long bottomb2 = (pr.x2*pr.y1) - (pr.x1 * pr.y2);
		long long b2 = -1;
		long long remb2 = -1;
		if (bottomb2 != 0) {
			b2 = topb2 / bottomb2;
			remb2 = topb2 % bottomb2;
			
		}

		long long topb1 = (pr.px * pr.y2) - (pr.py * pr.x2);
		long long bottomb1 = (pr.x1*pr.y2) - (pr.x2 * pr.y1);
		long long b1 = -1;
		long long remb1 = -1;
		if (bottomb1 != 0) {
			b1 = topb1 / bottomb1;
			remb1 = topb1 % bottomb1;
		}

		//long long b22 = (pr.px - b2*pr.x2)/pr.x1;
		//long long b11 = (pr.py - b1*pr.y1)/pr.y2;
		//printf("b1 %lld b2: %lld b22:%lld b11:%lld\n", b1, b2, b22, b11);

		if (b2 != -1 && remb2 == 0 && b1 != -1 && remb1 == 0) {
			minCost = 3*b1 + 1*b2;
		}

		/*
		   long long tbx1 = (pr.px / pr.x1) + 1;
		   long long tbx2 = (pr.px / pr.x2) + 1;
		   long long tby1 = (pr.px / pr.y1) + 1;
		   long long tby2 = (pr.px / pr.y2) + 1;
		   for (long long b1 = tbx1; b1 >= 0; b1--) {
		   long long diffx = pr.px - (b1 * pr.x1);
		   long long sb2 = (diffx / pr.x2) -2;
		   long long eb2 = (diffx / pr.x2) +2;

		   for (long long b2 = sb2; b2 <= eb2; b2++) {
		   long long sumx = (b1 * pr.x1 + b2 *pr.x2);
		   long long sumy = (b1 * pr.y1 + b2 *pr.y2);
		   if (sumx == pr.px && sumy == pr.py) {
		   long long cost = (3 * b1) + (1 * b2);
		   if (cost < minCost) {minCost = cost;}
		   }

		   }
		   }
		 */
		if (minCost != minCostOrig) {
			printf("minCost = %lld\n", minCost);
			totCost += minCost;
		} else {
			printf("NONE....\n");
		}
	}
	printf("**ans %lld\n", totCost);
}
