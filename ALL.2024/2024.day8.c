#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <map>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

char grid[100][100];

vector <pair<int, int>> sixtytwo[63];
map <int, map<int, int>> mp;
void printit();
int lenx, leny;


int main(int argc, char **argv)
{
	//mp[2][2] = 1;
        signal(SIGTSTP, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 8 Part 1\n"); fflush(stdout);

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

	lenx = strlen(grid[0]);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] >= '0' && grid[y][x] <= '9') {
				sixtytwo[grid[y][x] - '0'].push_back({x, y});
				//mp[x][y] = -1;
			} else if (grid[y][x] >= 'a' && grid[y][x] <= 'z') {
				sixtytwo[10+grid[y][x] - 'a'].push_back({x, y});
				//mp[x][y] = -2;
			} else if (grid[y][x] >= 'A' && grid[y][x] <= 'Z') {
				sixtytwo[36+grid[y][x] - 'A'].push_back({x, y});
				//mp[x][y] = -3;
			}
			
		}
	}

	for (int i = 0; i < 62; i++) {
		int sz = sixtytwo[i].size();
		if (sz > 1) {
			printf("--- %d ---\n", i);
			for (int k = 0; k < sz-1; k++) {
				for (int j = k+1; j < sz; j++) {
					printf("%d,%d V %d,%d\n", sixtytwo[i][k].first, sixtytwo[i][k].second, sixtytwo[i][j].first, sixtytwo[i][j].second);
					int x1 = sixtytwo[i][k].first + (sixtytwo[i][k].first - sixtytwo[i][j].first);
					int y1 = sixtytwo[i][k].second + (sixtytwo[i][k].second - sixtytwo[i][j].second);
					if (x1 == 3 && y1 == 1) {printf("found\n");}
					if (x1 >= 0 && x1 < lenx && y1 >= 0 && y1 < leny) {
						auto it = mp.find(x1);
						auto sz1 = (it == mp.end() ? 0 : it->second.size());
						int sz2 = 0;
						if (sz1 != 0) {
							auto it2 = mp[x1].find(y1);
							sz2 = (int)(it2 == mp[x1].end() ? 0 : 1);
						}
						if (sz2 == 0) {
							mp[x1][y1] = 1;
						} else if (sz2 > 0 && mp[x1][y1] > 0) {
							mp[x1][y1]++;
						} else if (sz2 > 0 && mp[x1][y1] < 0) {
						}
					}

					int x2 = sixtytwo[i][j].first + (sixtytwo[i][j].first - sixtytwo[i][k].first);
					int y2 = sixtytwo[i][j].second + (sixtytwo[i][j].second - sixtytwo[i][k].second);
					if (x2 == 3 && y2 == 1) {printf("found\n");}
					if (x2 >= 0 && x2 < lenx && y2 >= 0 && y2 < leny) {
						auto it = mp.find(x2);
						auto sz1 = (it == mp.end() ? 0 : it->second.size());
						int sz2 = 0;
						if (sz1 != 0) {
							auto it2 = mp[x2].find(y2);
							sz2 = (int)(it2 == mp[x2].end() ? 0 : 1);
						}
						if (sz2 == 0) {
							mp[x2][y2] = 1;
						} else if (sz2 > 0 && mp[x2][y2] > 0) {
							mp[x2][y2]++;
						} else if (sz2 > 0 && mp[x2][y2] < 0) {
						}
					}
				}
			}
		}
	}
	int count = 0;
	for (auto const &subject : mp) {
		printf("%d, ", subject.first);
		for (auto const &objective : subject.second) {
			printf(" %d\n", objective.first);
			if (objective.second >= 1) {
				//grid[objective.first][subject.first] = '0'+objective.second;
				grid[objective.first][subject.first] = '#';
				count ++;
			}
		}
	}
	printit();

	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", count);
}
void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
}
