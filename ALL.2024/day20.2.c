#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <deque>
#include <unordered_set>
//#include <f_set>
#include <string>
#include <iostream>
#include <time.h>
#include <bits/stdc++.h>

/* slowish (sort takes a while) -- need some optims... */
/* compile with -Wl,--stack,999777666 */
using namespace std;
FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

char grid[142][142];
char gridTmp[142][142];
int already[142][142];

int minPath;
int minPathOrig = 9999999;
int next(int x, int y, int ex, int ey, int path, deque <tuple<int, int, int>> de);
void nextNoVec(int x, int y, int ex, int ey, int path);
void calcLen(tuple <int, int, int, int> bla);

void printit();
deque <tuple<int, int, int>> deAns;
map <int, int> mp;
int sx, sy, ex, ey;
struct hash_function
{
	size_t operator()(const tuple<int , int , int, int>&x) const
	{
		unsigned int hash = 
get<0>(x);
hash *= 37;
hash += get<1>(x);
hash *= 37;
hash += get<2>(x);
hash *= 37;
hash += get<3>(x);
		return hash;
//		return get<0>(x) ^ get<1>(x) ^ get<2>(x) ^ get<3>(x);
	}
};

/*
bool operator==(const tuple<int, int, int, int> &lhs, const tuple<int, int, int, int>&rhs)
{
	return (get<0>(lhs) == get<0>(rhs)) && (get<1>(lhs) == get<1>(rhs)) && (get<2>(lhs) == get<2>(rhs)) &&
		(get<3>(lhs) == get<3>(rhs)); 
};
*/
/*
struct Ineq
{
};
*/

/*
	bool operator==(const tuple<int, int, int, int> &lhs, const tuple<int, int, int, int>&rhs)
	{
    		return (get<0>(lhs) == get<0>(rhs)) && (get<1>(lhs) == get<1>(rhs)) && (get<2>(lhs) == get<2>(rhs>)) &&
			(get<3>(lhs) == get<3>(rhs)); 
	}
*/

/*
	size_t operator-(const tuple<int , int , int, int>&x) const
	{
		return 1;
	}
*/
int noCheatMinPath = 0;
map <pair<int, int>, int> distToStart;
deque <tuple<int, int, int, int>> de4;
unordered_set <tuple<int, int, int, int>, hash_function> se4;

//set <tuple<int, int, int, int>, hash_function> de4_check;
//map <tuple<int, int, int, int>, int> dupMap;
//set <tuple<int, int, int, int, int, int, int, int>> fourPoints;
//map <pair<int, int>, int> disttoend;
//set <pair<int, int>> se;
//map <tuple<int, int, int, int>, int> preComputedLens;

int gcount = 0;

void generateAllCheatPaths();
void generateAllCheatPaths() {
	printf("Generating all Cheat Paths...\n");
	int ii = 0;
	memset(already, -1, sizeof(already));
	for (auto se1: deAns) {
		ii++;
		int x2 = get<0>(se1);
		int y2 = get<1>(se1); 
#ifdef _DEBUG_
		if (ii % 1000 == 0) { printf("(%d of %d) checking circle around: %d,%d\n", ii, noCheatMinPath, x2, y2); }
#endif
		for (int end = 20; end >= 0; end--) {
			for (int radiusY = end; radiusY >= 0; radiusY--) {
				int radiusX = end - abs(radiusY);
				{
					//for (int radiusX = end; radiusX >= 0; radiusX--)  
					if (abs(radiusX) + abs(radiusY) != end) {continue;}
					int x1p = x2 + radiusX;
					int x1n = x2 - radiusX;
					int y1p = y2 + radiusY;
					int y1n = y2 - radiusY;
					//top right quad
					if (x1p >= 0 && x1p <= lenx-1 && y1n >= 0 && y1n <= leny-1 && grid[y1n][x1p] == '.') {
						//tuple <int, int, int, int> tu11 = make_tuple(x2, y2, x1p, y1n);
						/*
						   if (se4.find({x2, y2, x1p, y1n}) == se4.end()) {
						   se4.insert({x2, y2, x1p, y1n});
						   {de4.push_back({x2, y2, x1p, y1n});}
						   }
						 */
						
						if (se4.find({x2, y2, x1p, y1n}) == se4.end()) {
						   	se4.insert({x2, y2, x1p, y1n});
							{de4.push_back({x2, y2, x1p, y1n});}
						}
					}
					if (x1p >= 0 && x1p <= lenx-1 && y1p >= 0 && y1p <= leny-1 && grid[y1p][x1p] == '.') {
						//tuple <int, int, int, int> tu11 = make_tuple(x2, y2, x1p, y1p);
						/*
						   if (se4.find({x2, y2, x1p, y1p}) == se4.end()) {
						   se4.insert({x2, y2, x1p, y1p});
						   {de4.push_back({x2, y2, x1p, y1p});}
						   }
						 */
						if (se4.find({x2, y2, x1p, y1p}) == se4.end()) {
						   	se4.insert({x2, y2, x1p, y1p});
							{de4.push_back({x2, y2, x1p, y1p});}
						}
					}
					if (x1n >= 0 && x1n <= lenx-1 && y1p >= 0 && y1p <= leny-1 && grid[y1p][x1n] == '.') {
						//tuple <int, int, int, int> tu11 = make_tuple(x2, y2, x1n, y1p);
						/*
						   if (se4.find({x2, y2, x1n, y1p}) == se4.end()) {
						   se4.insert({x2, y2, x1n, y1p});
						   {de4.push_back({x2, y2, x1n, y1p});}
						   }
						 */
						if (se4.find({x2, y2, x1n, y1p}) == se4.end()) {
						   	se4.insert({x2, y2, x1n, y1p});
							{de4.push_back({x2, y2, x1n, y1p});}
						}

					}
					if (x1n >= 0 && x1n <= lenx-1 && y1n >= 0 && y1n <= leny-1 && grid[y1n][x1n] == '.') {
						//tuple <int, int, int, int> tu11 = make_tuple(x2, y2, x1n, y1n);
						/*
						   if (se4.find({x2, y2, x1n, y1n}) == se4.end()) {
						   se4.insert({x2, y2, x1n, y1n});
						   {de4.push_back({x2, y2, x1n, y1n});}
						   }
						 */
						if (se4.find({x2, y2, x1n, y1n}) == se4.end()) {
						   	se4.insert({x2, y2, x1n, y1n});
							{de4.push_back({x2, y2, x1n, y1n});}
						}
					}
				}
			}
		}
	}
}

void saveinsave(int pathLen) {
	if (pathLen <= noCheatMinPath) {
		int save = noCheatMinPath - pathLen;
		mp[save]++;
		if (save >= 100) {gcount++;}
		/*
		   if (save < 0) {	
		   printf("ERR(save)\n");
		   } else {
		//if (mp[76] > 3) {printf("oh no...\n");getchar();}
		mp[save]++;
		if (save >= 100) {gcount++;}
		}
		 */
	}
}

/*
int getPathLength(tuple <int, int, int, int> bla);
int getPathLength(tuple <int, int, int, int> bla) {
	//dEPRECATED
	int x1 = get<0>(bla);
	int y1 = get<1>(bla);
	int x2 = get<2>(bla);
	int y2 = get<3>(bla);
	if (preComputedLens.find({x1, y1, x2, y2}) != preComputedLens.end()) {
		int ans = preComputedLens[{x1, y1, x2, y2}];
		return ans;
	} else {
		printf("never here...\n");
		memset(already, 0, sizeof(already));
		minPath = minPathOrig;
		nextNoVec(x1, y1, x2, y2, 0);
		int m1 = minPath;
		preComputedLens[{x1, y1, x2, y2}] = m1;
		preComputedLens[{x2, y2, x1, y1}] = m1;
		return m1;
	}

}
*/

int main(int argc, char **argv)
{
	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2024 Day 20 Part 2\n"); fflush(stdout);
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
	clock_t start, end;
	double cpu_time_used;

	lenx = strlen(grid[0]);
{
	start = clock();
	int foundS = 0, foundE = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (foundS == 1 && foundE == 1) {
				goto after;
			} else if (grid[y][x] == 'S') {
				foundS = 1;
				sx = x; sy = y;
				grid[sy][sx] = '.';
			} else if (grid[y][x] == 'E') {
				foundE = 1;
				ex = x; ey = y;
				grid[ey][ex] = '.';
			}
		}
	}
after:
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("	time finding start and end took: %f seconds\n", cpu_time_used);
	//assert(foundS == 1 && foundE == 1);
}

	{
		start = clock();
		memset(already, 0, sizeof(already));
		minPath = minPathOrig;
		deque <tuple<int, int, int>> de;
		next(sx, sy, ex, ey, 0, de);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("	time finding minpath: %f seconds\n", cpu_time_used);
		noCheatMinPath = minPath;	
	}

	printf("deAns.size() %d\n", (int) deAns.size()); fflush(stdout);
	printf("noCheatMinPath %d\n", noCheatMinPath); fflush(stdout); 

	{
		start = clock();
		generateAllCheatPaths();
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("	time generating: %f seconds\n", cpu_time_used);
	}

/*DEPRECATED as using unordered_set
	printf("sizebefore %d\n", (int)de4.size());
	{//sort (quicker than using a set for no dups)
		printf("calling sort (slow)(%d):\n", (int)de4.size());
		start = clock();
		sort(de4.begin(), de4.end());
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("	time sorting: %f seconds\n", cpu_time_used);
	}
	{//unique (quicker than set)
		printf("calling unique (%d):\n", (int)de4.size());
		start = clock();
		auto it = unique(de4.begin(), de4.end());
		de4.resize(distance(de4.begin(), it));
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("	time unique: %f seconds\n", cpu_time_used);
	}
	printf("sizeafter %d\n", (int)de4.size());

*/
	//printf("se4.size is %d\n", (int) se4.size()); fflush(stdout); 
	printf("de4.size is %d\n", (int) de4.size()); fflush(stdout); 

	int bb = 0;
#ifdef _DEBUG_
	int szde4 = (int)de4.size();
#endif
	printf("Looping tru all cheats...\n");
	start = clock();
	for (auto tu5: de4) {
		bb++;
		int fx1 = get<0>(tu5); int fy1 = get<1>(tu5); int tx1 = get<2>(tu5); int ty1 = get<3>(tu5);
#ifdef _DEBUG_
		if (bb % 100000 == 0) {printf("(%d of %d) cheats checks (%d,%d -> %d,%d -> %d,%d -> %d,%d)\n", bb, szde4, sx, sy, fx1, fy1, tx1, ty1, ex, ey);}
#endif

		int abs_var = abs(fx1-tx1) + abs(fy1-ty1);

		int pathLen3 = distToStart[{fx1, fy1}] + abs_var + noCheatMinPath - distToStart[{tx1, ty1}];

		saveinsave(pathLen3);
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("	time Looping: %f seconds\n", cpu_time_used);

#ifdef _DEBUG_
	for (auto it = mp.begin(); it != mp.end(); it++) {
		if ((*it).first >= 50) {
			printf("There are %d cheats that save %d picoseconds.\n", (*it).second, (*it).first);
		} else {
			//printf("There are %d cheats that save %d picoseconds.\n", (*it).second, (*it).first);
		}
	}
#endif
	printf("**ans %d\n", gcount);
}


int next(int x, int y, int ex, int ey, int path, deque <tuple<int, int, int>> de) {


	if (x < 0 || y < 0 || x > lenx-1 || y > leny -1 || grid[y][x] == '#') {return 55;}

	if (x == ex && y == ey) {
		printf("min (of 1) path found %d\n", path);
		if (path < minPath) {
			minPath = path;
			deAns = de; 
			de.push_back({x,y, path});
			for (auto pa: de) {
				int x2 = get<0>(pa);
				int y2 = get<1>(pa);
				int d1 = get<2>(pa);
				distToStart[{x2, y2}] = d1;
			}
		}

		return 22;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		de.push_back({x,y, path});
		if (22 == next(x, y-1, ex, ey, path+1, de)) {return 22;}
		if (22 == next(x+1, y, ex, ey, path+1, de)) {return 22;}
		if (22 == next(x, y+1, ex, ey, path+1, de)) {return 22;}
		if (22 == next(x-1, y, ex, ey, path+1, de)) {return 22;}
	}
	return 56;
}

void nextNoVec(int x, int y, int ex, int ey, int path) {
	if (path > noCheatMinPath) {return;}

	if (x < 0 || y < 0 || x > lenx-1 || y > leny -1 || grid[y][x] == '#') {return;}

	if (x == ex && y == ey) {
		//printf("path found %d\n", path);
		if (path < minPath) {minPath = path;}
		return;
	}

	if (already[y][x] == 0 || path < already[y][x]) {
		already[y][x] = path;
		nextNoVec(x, y-1, ex, ey, path+1);
		nextNoVec(x+1, y, ex, ey, path+1);
		nextNoVec(x, y+1, ex, ey, path+1);
		nextNoVec(x-1, y, ex, ey, path+1);
	}
}

void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (x == sx && y == sy) {
				printf("S");
			} else if (x == ex && y == ey) {
				printf("E");
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
