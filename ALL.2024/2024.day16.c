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
#include <queue>
#include <unistd.h>
#include <algorithm>
#include <map>
#include <iostream>
#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
int lenx;
int leny;
char grid[200][200];
int minPath = 9999999;
int sx, sy, ex, ey;
void deadend(int xx, int yy);
void next5(int x, int y, int ex, int ey, int dir);
void sigfunc(int a) { printf(" sig: \n"); }

int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);

	a = fopen(argv[1], "r"); printf("		2024 Day 16 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		strcpy(grid[leny], line1);
		leny++;
	}
	fclose(a);
	lenx = (int)strlen(grid[0]);
	sx = -1, sy = -1, ex = -1, ey = -1;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'S') {
				sx = x; sy = y;
				grid[y][x] = '.';
				if (sy != -1 && ey != -1) {goto after;}
			} else if (grid[y][x] == 'E') {
				ex = x; ey = y;
				grid[y][x] = '.';
				if (sy != -1 && ey != -1) {goto after;}
			}
		}
	}

after:

	for (int yy = 1; yy < leny-1; yy++) {
		for (int xx = 1; xx < lenx-1; xx++) {
			if ((xx == sx && yy == sy) || (xx == ex && yy == ey)) {
			} else {
				deadend(xx, yy);
			}
		}
	}
	printf("after deadend sealing...\n");

	minPath = 9999999;
	next5(sx, sy, ex, ey, 1);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
	printf("%d", minPath);
	printf("\n");

}

struct Node2 {
	int x, y;
	int path;
	int dir;
	vector <tuple <int, int, int, int>> already;

	Node2(int x, int y, int dir, int path, vector <tuple<int, int, int, int>> already ) {
		this->x = x;
		this->y = y;
		this->dir = dir;
		this->path = path;
		this->already = already;
	}
	bool operator==(const Node2& other) const {
		return x == other.x && y == other.y && dir == other.dir;
	}
};

struct Compare2 {
	bool operator()(const Node2& a, const Node2& b) {
		return a.path > b.path;
	}
};

void next5(int x, int y, int ex, int ey, int dir) {
	minPath = 9999999;
	priority_queue<struct Node2, vector<struct Node2>, Compare2> Q;
	//set<struct Node> seen1;
	vector<struct Node2> seen1;
	vector<tuple<int, int, int, int>> al;
	Q.push(Node2(x, y, dir, 0, al));

	while (!Q.empty()) {
		auto current = Q.top();
		Q.pop();

		if (find(seen1.begin(), seen1.end(), current) != seen1.end()) {
			continue;
		}
		seen1.push_back(current);

		if (current.x == ex && current.y == ey) {
			//printf("end: %d\n", current.path);
			if (ex == sx && ey == sy && (current.dir == 0 || current.dir == 2)) {
				current.path += 1000;
			}
			minPath = current.path;
			//alreadyG = current.already;
			break;

		}
		int ignoreDir = (((current.dir-2) + 4) % 4);
		for (int i = 0; i < 4; i++) {
			int newPath = current.path;
			auto alal = current.already;
			if (i == ignoreDir) {continue;}
			if (abs(current.dir - i) == 1 || abs(current.dir -i) == 3) {
				if (alal.size() > 0) {
					auto al = alal;
					auto el = al.back();
					al.pop_back();
					get<2>(el) = i;
					al.push_back(el);
					alal = al;
				}
				newPath+=1000;
			}

			if (i == 0 && grid[current.y-1][current.x] != '#') {
				auto al1 = alal;
				al1.push_back(make_tuple(current.x, current.y-1, i, newPath+1));
				Q.push(Node2(current.x, current.y-1, i, newPath+1, al1));
			} else if (i == 1 && grid[current.y][current.x+1] != '#') {
				auto al1 = alal;
				al1.push_back(make_tuple(current.x+1, current.y, i, newPath+1));
				Q.push(Node2(current.x+1, current.y, i, newPath+1, al1));
			} else if (i == 2 && grid[current.y+1][current.x] != '#') {
				auto al1 = alal;
				al1.push_back(make_tuple(current.x, current.y+1, i, newPath+1));
				Q.push(Node2(current.x, current.y+1, i, newPath+1, al1));
			} else if (i == 3 && grid[current.y][current.x-1] != '#') {
				auto al1 = alal;
				al1.push_back(make_tuple(current.x-1, current.y, i, newPath+1));
				Q.push(Node2(current.x-1, current.y, i, newPath+1, al1));
			}
		}
	}
}

void deadend(int xx, int yy) {
	if (grid[yy][xx] == '#') {return;}
	if ((xx == sx && yy == sy) || (xx == ex && yy == ey)) {return;}
	vector <int> dirs;
	if (grid[yy-1][xx] == '.') {
		dirs.push_back(0);
	}
	if (grid[yy][xx+1] == '.') {
		dirs.push_back(1);
	}
	if (grid[yy+1][xx] == '.') {
		dirs.push_back(2);
	}
	if (grid[yy][xx-1] == '.') {
		dirs.push_back(3);
	}
	if (dirs.size() == 1) {
		grid[yy][xx] = '#';
		if (yy-1 >0) {
			deadend(xx, yy-1);
		}
		if (xx+1 < lenx+1) {
			deadend(xx+1, yy);
		}
		if (yy+1 < leny+1) {
			deadend(xx, yy+1);
		}
		if (xx-1 > 0) {
			deadend(xx-1, yy);
		}
	}
}
