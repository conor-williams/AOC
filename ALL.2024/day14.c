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
//map <pair<int, int>, pair<int, int>> mp;
//map <int, <map <int, pair<int, int>>>> mp;
struct point_s {
	int x[200];
	int y[200];
	int vx, vy;
};
deque <struct point_s> de;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 14 Part 1\n"); fflush(stdout);
        char line1[LINE];

	leny = 0;
	struct point_s tmp;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	
	sscanf(line1, "p=%d,%d v=%d,%d", &tmp.x[0], &tmp.y[0], &tmp.vx, &tmp.vy);
	de.push_back(tmp);
	
	leny++;
}
fclose(a);

	int floorx = 101; int floory = 103;
	//int floorx = 11; int floory = 7;
	for (int times = 1; times <= 100; times++) {
		for (auto it = de.begin(); it != de.end(); it++) {
			struct point_s tmp1 = *it;
			tmp1.x[times] = (tmp1.x[times -1] + (tmp1.vx) + (2 * floorx)) % floorx;
			tmp1.y[times] = (tmp1.y[times -1] + (tmp1.vy) + (2 * floory)) % floory;
			//printf("%d %d \n", tmp1.x[times], tmp1.y[times]);
			*it = tmp1;
		}

	}
	int count[5] = {0};
	//printf("0: %d %d\n", 0, floorx/2); printf("1: %d %d\n", floorx/2, floorx); printf("2: %d %d\n", 0, floory/2); printf("3: %d %d\n", floory/2, floory);
	for (auto it = de.begin(); it != de.end(); it++) {
		struct point_s tmp2 = *it;
		//printf("%d %d %d %d\n", tmp2.x[100], tmp2.y[100], tmp2.vx, tmp2.vy);
		if (tmp2.x[100] >= 0 && tmp2.x[100] < floorx/2 &&
			tmp2.y[100] >= 0 && tmp2.y[100] < floory/2) {
			count[0]++;
		} else if (tmp2.x[100] > floorx/2 && tmp2.x[100] < floorx &&
			tmp2.y[100] > floory/2 && tmp2.y[100] < floory) {
			count[1]++;
		} else if (tmp2.x[100] >= 0 && tmp2.x[100] < floorx/2 &&
			tmp2.y[100] > floory/2 && tmp2.y[100] < floory) {
			count[2]++;
		} else if (tmp2.x[100] > floorx/2 && tmp2.x[100] < floorx &&
			tmp2.y[100] >= 0 && tmp2.y[100] < floory/2) {
			count[3]++;
		}
	}
	unsigned long long ans = count[0] * count[1] * count[2] * count[3];
	printf("**ans %llu\n",  ans);
	
}
