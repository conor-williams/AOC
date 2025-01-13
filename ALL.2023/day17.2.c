#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <functional>
#include <iostream>
#include <queue>
#include <string_view>
#include <vector>
#include <unistd.h>
///#define assert(asf)
//#define getchar()
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;


struct hash_function
{
	size_t operator()(const tuple<int , int , int, int, int>&x) const
	{
		unsigned int hash = get<0>(x); 
		hash *= 37;
		hash += get<1>(x);
		hash *= 37;
		hash += get<2>(x);
		hash *= 37;
		hash += get<3>(x);
		hash*= 37;
		hash += get<4>(x);
		hash*= 37;
		return hash;
	}
};




FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;
priority_queue <tuple<int, int, int, int, int, int>, vector<tuple<int, int, int, int, int, int>>, greater<tuple<int, int, int, int, int, int>>> pr;
char grid[200][200];
void runit(int, int);
int minPath;
int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); if (a == NULL) {printf("BAD file %s\n", argv[1]); exit(0);}
	printf("20YY Day 17 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);

	//     pa, x, y, dirX, dirY, stepsindir, 
	int ex = lenx-1; int ey = leny-1;

	minPath = lenx*leny*9;
	pr.push({0, 0, 0, 0, 1, 0});
	pr.push({0, 0, 0, 1, 0, 0});
	runit(ex, ey);

	printf("ex: %d ey : %d\n", ex, ey);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minPath);
}
void runit(int ex, int ey) {
	unordered_set <tuple<int, int, int, int, int>, hash_function> se;
	while (!pr.empty()) {
		tuple <int, int, int, int, int, int> data = pr.top();
		pr.pop();

		int path = get<0>(data);
		if (path > minPath) {continue;}
		int x = get<1>(data);
		int y = get<2>(data);
		int dirX = get<3>(data);
		int dirY = get<4>(data);
		int ste = get<5>(data);

		if (se.find({x, y, dirX, dirY, ste}) != se.end()) {continue;}
		se.insert({x, y, dirX, dirY, ste});
		if (x == ex && y == ey) {
			printf("poss min: %d\n", path); fflush(stdout);
			if (path < minPath && ste >= 4 && ste <= 10) {
				minPath = path;
				printf("	settingminPath %d ste %d\n", minPath, ste);
				return;
			} else {printf("end reached path(%d)V(%d) %d no good\n", path, minPath, ste);}
			continue;
		}
		{//straight or turn
			pair <int, int> pa[4];
			pa[0].first = 0;  pa[0].second = -1;
			pa[1].first = 1;  pa[1].second = 0;
			pa[2].first = 0;  pa[2].second = 1;
			pa[3].first = -1; pa[3].second = 0;
			//
			//
			//for dx,dy in (0,1) (1,0) (0,-1) (-1,0)
			for (int ii = 0; ii < 4; ii++) {
				int nx = -10; int ny = -10; int numSte = -10;
				if (pa[ii].first - dirX == 0 && pa[ii].second - dirY == 0) {
					if (ste < 10) {
						//same dir
						nx = x + dirX;
						ny = y + dirY;
						numSte = ste+1;
					}
				} else if (pa[ii].first + dirX == 0 && pa[ii].second + dirY == 0) {
					//opposite dir
					continue;
				} else {
					if (ste >= 4 && ste <= 10) {
						//turn if he has gone at least 4 steps not more than 10
						nx = x+ pa[ii].first;	
						ny = y+ pa[ii].second;	
						numSte = 1;
						//if (abs(abs(dirX) - abs(pa[ii].first)) != 1) {printf("ERR2"); exit(0);}
						//if (abs(abs(dirY) - abs(pa[ii].second)) != 1) {printf("ERR3"); exit(0);}

						////	printf("dirX %d V %d pa[ii].first -- dirY %d V %d pa[ii].second\n", 
						////			dirX, pa[ii].first, dirY, pa[ii].second);
						//pr.push(tuFirst);
						//printf("path now %d\n", path); //getchar();
					}
				}
				if (nx < 0 || nx > leny-1 || ny < 0 || ny > leny-1) {
					continue;
				} else {
					pr.push({path+((int)grid[ny][nx]-48), nx, ny, pa[ii].first, pa[ii].second, numSte});
				}
			}
		}

	}
}
