#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <unistd.h>
#include <string>

using namespace std;
#define getchar()
FILE *a;
#define LINE 100 
#define getchar()
int sx = 0;
int sy = 0;
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day13.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); //close(1);
	char line1[LINE];

	vector <string> blah;
	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		string line2 = line1;
		blah.push_back(line2);
		leny++;
	}
	fclose(a);

	int maxx = 0;
	int maxy = 0;
	for (int i = 0; i < (int)blah.size(); i++) {
		if (blah[i].length() == 0) {break;}
		int one, two;
		sscanf(blah[i].c_str(), "%d,%d", &one, &two);
		if (one > maxx) {maxx = one;}
		if (two > maxy) {maxy = two;}
	}

	sx = maxx+1;
	sy = maxy+1;
	char grid[sy][sx];
	char gridTmp[sy][sx];
	memset(grid, '.', sizeof(grid));

	bool folds = false;
	vector <pair<char, int>> ve;
	for (int i = 0; i < (int)blah.size(); i++) {
		if (blah[i].length() == 0) {
			folds =  true;
			continue;
		}
		if (folds == false) {
			int xx;
			int yy;
			sscanf(blah[i].c_str(), "%d,%d", &xx, &yy);
			grid[yy][xx] = '#';
			continue;
		} else {
			char exory; int value;
			sscanf(blah[i].c_str(), "fold along %c=%d", &exory, &value);
			//printf("%c\n", exory); printf("%d\n", value); fflush(stdout);
			pair<int, int> tu1 = make_pair(exory, value);
			ve.push_back(tu1);
		}
	}

	for (int qqq = 0; qqq < (int)ve.size(); qqq++) {
		auto fir = ve[qqq];
		char xory = fir.first;
		int val = fir.second;
		if (xory == 'x') {
			for (int yy = 0; yy < sy; yy++) {
				for (int xx = 0; xx < val; xx++) {
					gridTmp[yy][xx] = grid[yy][xx];
				}
			}
			for (int yy = 0; yy < sy; yy++) {
				int tr = 2;
				for (int xx = val+1; xx < sx; xx++) {
					if (grid[yy][xx] == '#') {
						gridTmp[yy][xx-tr] = '#';
					}
					tr+=2;
				}
			}
			sx = val;
		} else {
			for (int xx = 0; xx < sx; xx++) {
				for (int yy = 0; yy < val; yy++) {
					gridTmp[yy][xx] = grid[yy][xx];
				}
			}
			for (int xx = 0; xx < sx; xx++) {
				int tr = 2;
				for (int yy = val+1; yy < sy; yy++) {
					if (grid[yy][xx] == '#') {
						gridTmp[yy-tr][xx] = '#';
					}
					tr+=2;
				}
			}
			sy = val;
		}
		memcpy(grid, gridTmp, sizeof(grid));
	}

	printf("**ans: \n");
	for (int yy = 0; yy < sy; yy++) {
		for (int xx = 0; xx < sx; xx++) {
			if (grid[yy][xx] == '.') {
				printf(" ");
			} else {
				printf("%c", grid[yy][xx]);
			}
		}
		printf("\n");
	}
	printf("\n");

}
