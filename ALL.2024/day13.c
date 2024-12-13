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
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
struct prize_s {
	int x1, y1;
	int x2, y2;
	int px, py;
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
		int x1, y1;
		int ret1 = sscanf(line1, "Button A: X+%d, Y+%d", &x1, &y1);
		if (ret1 == 2) {
			pr.x1 = x1; pr.y1 = y1;	
			continue;
		} 

		int x2, y2;
		int ret2 = sscanf(line1, "Button B: X+%d, Y+%d", &x2, &y2);
		if (ret2 == 2) {
			pr.x2 = x2; pr.y2 = y2;	
			continue;
		}

		int px, py;
		int ret3 = sscanf(line1, "Prize: X=%d, Y=%d", &px, &py);
		if (ret3 == 2) {
			pr.px = px; pr.py = py;
			de.push_back(pr);
			continue;
		}
	}
	leny++;
}
fclose(a);


	unsigned long long totCost = 0;
	for (auto it = de.begin(); it != de.end(); it++) {
		struct prize_s p2 = *it;
		
		int minCost = 9999999;
		int minCostOrig = minCost;
		for (int b1 = 0; b1 <= 100; b1++) {
			for (int b2 = 0; b2 <= 100; b2++) {
				int sumx = (b1 * p2.x1 + b2 *p2.x2);
				int sumy = (b1 * p2.y1 + b2 *p2.y2);
				if (sumx == p2.px && sumy == p2.py) {
					int cost = (3 * b1) + (1 * b2);
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
	printf("**ans %llu\n", totCost);
}
