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
int lenx;
int leny;
char grid[70][70];
map <pair <int, int>, int> mp;
map <tuple <int, int, int, int>, int> mpAns;
int count = 0;
void loop (int x, int y, int nVal, int sx, int sy);
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 10 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	strcpy(grid[leny], line1);
	
	for (int x = 0; x < (int)strlen(line1); x++) {
		if (line1[x] == '0') {
			printf("putting: %d, %d\n", x, leny);
			mp[{x, leny}] = 1;
		}
	}
			
	leny++;
}
	lenx = (int) strlen(grid[0]);
fclose(a);

	for (auto it = mp.begin(); it != mp.end(); it++) {
		pair pa = it->first;
		
		printf("loop %d, %d\n", pa.first, pa.second);
		loop(pa.first, pa.second, 0, pa.first, pa.second);
	}
	long ans = 0;
	for (auto it = mpAns.begin(); it != mpAns.end(); it++) {
		ans += it->second;
	}
	printf("**ans (mpAns size is) %d\n", (int)mpAns.size());
	//printf("count is %d\n", count);

	fflush(stdout); dup2(fd, 1);
	printf("**ans %ld\n", ans);

}
void loop (int x, int y, int nVal, int sx, int sy) {

	//printf("nVal is %d\n", nVal);
	if (grid[y][x] != nVal+48) {
		//printf("grid %d,%d should be %c is:%c\n", x, y, nVal+48, grid[y][x]);
		return;
	}

	if (nVal == 9 && grid[y][x] == '9') {
		count++;
		//printf("got a 999999\n");
		if (mpAns.find(make_tuple(x, y, sx, sy)) == mpAns.end()) {
			mpAns[{x, y, sx, sy}] = 1;
		} else {
			mpAns[{x, y, sx, sy}]++;
		}
		return;
	}

	if (y-1 >= 0 && grid[y-1][x] == nVal+48+1) {
		loop(x, y-1, nVal+1, sx, sy);
		//printf("loop %d %d, %d\n", x, y-1, nVal+1);
	}
	if (x+1 < lenx && grid[y][x+1] == nVal+48+1) {
		loop(x+1, y, nVal+1, sx, sy);
		//printf("loop %d %d, %d\n", x+1, y, nVal+1);
	}
	if (y+1 < leny && grid[y+1][x] == nVal+48+1) {
		loop(x, y+1, nVal+1, sx, sy);
		//printf("loop %d %d, %d\n", x, y+1, nVal+1);
	}
	if (x-1 >= 0 && grid[y][x-1] == nVal+48+1) {
		loop(x-1, y, nVal+1, sx, sy);
		//printf("loop %d %d, %d\n", x-1, y, nVal+1);
	}
	
}
