#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <signal.h>
#include <map>
#include <assert.h>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2019 day20 part1\n"
#undef _DEBUG_
#define SZ 140
char grid[SZ][SZ];
int already[SZ][SZ];

#define getchar()
void ne(int x, int y, int eX, int eY, int path);
void getsecond(char one1, char two1, int px1, int py1);

int minPath = 99999;
void signal_hand(int xx) {
	printf("in sig...\n");
}
struct to_s {
	int x;
	int y;
};
map <pair<int, int>, struct to_s> mp;
map <string, int> mpLets;

int main(int argc, char **argv)
{
	signal(SIGTSTP, signal_hand);
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); 
	       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SZ];
while(1) {
        fgets(line1, SZ-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif
	strcpy(grid[leny], line1);
	leny++;
}
lenx = (int)strlen(line1);
fclose(a);



	int stX = 0;
	int stY = 0;
	int endX = 0;
	int endY = 0;
	for (int y = 0; y < leny-1; y++) {
		for (int x = 0; x < lenx-1; x++) {
			char fc1, sc1; int posX1, posY1;
			
			int found = 0;
			if ((isupper(grid[y][x])) && (isupper(grid[y+1][x]))) {
				fc1 = grid[y][x];
				sc1 = grid[y+1][x];
				string var_str2;
				var_str2.push_back(fc1);
				var_str2.push_back(sc1);
				if (mpLets.find(var_str2) != mpLets.end()) {continue;}
				printf("fc1,sc1 is %c%c \n", fc1, sc1);
				if (y+2 == leny) {
					posX1 = x; posY1 = y-1;
				} else if (y == 0) {
					posX1 = x; posY1 = y+2;
				} else if (grid[y+2][x] == '.') {
					posX1 = x; posY1 = y+2;
				} else if (grid[y-1][x] == '.') {
					posX1 = x; posY1 = y-1;
				}
				found = 1;
			} else if ((fc1 = isupper(grid[y][x])) && (sc1 = isupper(grid[y][x+1]))) {
				fc1 = grid[y][x];
				sc1 = grid[y][x+1];
				string var_str2;
				var_str2.push_back(fc1);
				var_str2.push_back(sc1);
				if (mpLets.find(var_str2) != mpLets.end()) {continue;}
				printf("fc1,sc1 is %c%c \n", fc1, sc1);
				if (x+2 == lenx)  {
					posX1 = x-1; posY1 = y;
				} else if (x == 0) {
					posX1 = x+2; posY1 = y;
				} else if (grid[y][x+2] == '.') {
					posX1 = x+2; posY1 = y;
				} else if (grid[y][x-1] == '.') {
					posX1 = x-1; posY1 = y;
				}
				found = 1;
			}
			if (found == 1) {
				if (fc1 == 'A' && sc1 == 'A') {
					printf("found AA\n");
					stX = posX1; stY = posY1;
				} else if (fc1 == 'Z' && sc1 == 'Z') {
					endX = posX1; endY = posY1;
					printf("found ZZ\n");
				} else {
					getsecond(fc1, sc1, posX1, posY1);
				}
			}
		}
	}
	memset(already, -1, SZ*SZ*sizeof(int));
	for (int y = 0; y < SZ; y++) {
		for (int x = 0; x < SZ; x++) {
			assert(already[y][x] == -1);
		}
	}
	//printf("after assert... getchar\n"); getchar();
	//already[stY][stX] = 0;
	int path = 0;
	printf("%d,%d -> %d,%d\n", stX, stY, endX, endY);
	ne(stX, stY, endX, endY, path);

	fflush(stdout); dup2(fd, 1);
	printf("**minPath: %d\n", minPath);
}
void ne(int x, int y, int eX, int eY, int path) {
	if (x == eX && y == eY) {
		printf("found an end %d\n", path);
		if (path < minPath) {minPath = path; }
		return;
	}
	if (grid[y][x] != '.') {return;}

	if (x < 0 || x >= lenx || y < 0|| y>= leny) {return;}

	auto iter = mp.find({x,y});
	if (iter == mp.end()) {} else {path++; x = iter->second.x; y = iter->second.y; /*printf("newx,newy %d,%d\n", x, y);*/}


	if (already[y][x] == -1 || path < already[y][x]) {
		already[y][x] = path;
		ne(x+1, y, eX, eY, path+1);
		ne(x-1, y, eX, eY, path+1);
		ne(x, y+1, eX, eY, path+1);
		ne(x, y-1, eX, eY, path+1);
	}

}
void getsecond(char one1, char two1, int px1, int py1) {
	char fc2, sc2; int posX2, posY2;
	for (int y = 0; y < leny-1; y++) {
		for (int x = 0; x < lenx-1; x++) {
			if ((isupper(grid[y][x])) && (isupper(grid[y+1][x]))) {
				fc2 = grid[y][x]; sc2 = grid[y+1][x];
				if (fc2 == one1 && sc2 == two1) {
					if (y+2 == leny) {
						posX2 = x; posY2 = y-1;
					} else if (y == 0) {
						posX2 = x; posY2 = y+2;
					} else if (grid[y+2][x] == '.') {
						posX2 = x; posY2 = y+2;
					} else if (grid[y-1][x] == '.') {
						posX2 = x; posY2 = y-1;
					}
					if (posX2 == px1 && posY2 == py1) {continue;} else {printf("fc2,sc2 is %c%c \n", fc2, sc2); goto end;}
				}
			} else if ((isupper(grid[y][x])) && (isupper(grid[y][x+1]))) {
				fc2 = grid[y][x]; sc2 = grid[y][x+1];
				
				if (fc2 == one1 && sc2 == two1) {
					if (x+2 == lenx)  {
						posX2 = x-1; posY2 = y;
					} else if (x == 0) {
						posX2 = x+2; posY2 = y;
					} else if (grid[y][x+2] == '.') {
						posX2 = x+2; posY2 = y;
					} else if (grid[y][x-1] == '.') {
						posX2 = x-1; posY2 = y;
					}
					if (posX2 == px1 && posY2 == py1) {continue;} else {printf("fc2,sc2 is %c%c \n", fc2, sc2); goto end;}
				}
			}
		}
	}
end:
	struct to_s to1;
	to1.x = px1; to1.y = py1;
	struct to_s to2;
	to2.x = posX2; to2.y = posY2;

	mp[{px1, py1}] =  to2;
	printf("px1,py1: %d,%d to2,x to2.y:%d,%d (%d,%d)\n", px1,py1, to2.x, to2.y, posX2, posY2);
	mp[{posX2, posY2}] = to1;
	printf("posX2,posY2: %d,%d to1,x to1.y:%d,%d (%d,%d)\n", posX2, posY2, to1.x, to1.y, posX2, posY2);
	getchar();
	string var_str;
	var_str.push_back(one1);
	var_str.push_back(two1);
	mpLets[var_str] = 1;
	return;
}

