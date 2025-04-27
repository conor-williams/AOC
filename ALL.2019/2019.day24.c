#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>


#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "		2019 day24 part1\n"
#undef _DEBUG_
#define LINE 50

#define SZ 10

char grid[SZ][SZ];
char gridTmp[SZ][SZ];
void printit();
map <int, int> mp;
int calcbio();

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
	strcpy(grid[0], ".......");
	leny++;
while(1) {

        fgets(line1, LINE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif
	strcpy(grid[leny], "");
	strcat(grid[leny], ".");
	strcat(grid[leny], line1);
	strcat(grid[leny], ".");
	printf("lenx %d - leny %d\n", lenx, leny);
	leny++;
}
	lenx = strlen(grid[0]);
	strcpy(grid[leny], ".......");
	leny++;
fclose(a);

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			gridTmp[y][x] = '.';
		}
	}

	int t = 0;
	mp[calcbio()] = 1;
	while (1) {
		printf("After %d minutes:\n", t);
		printit(); //getchar();
		for (int y = 1; y < leny-1; y++) {
			for (int x = 1; x < lenx-1; x++) {
				int count = 0;
				if (grid[y-1][x] == '#') {count++;} 
				if (grid[y][x+1] == '#') {count++;}
				if (grid[y+1][x] == '#') {count++;}
				if (grid[y][x-1] == '#') {count++;}
	
				switch(grid[y][x]) {
					case '#': 
						if (count == 1) {
							gridTmp[y][x] = '#';
						} else {
							gridTmp[y][x] = '.';
						}
						break;
					case '.':
						if (count == 1 || count == 2) {
							gridTmp[y][x] = '#';
						} else {
							gridTmp[y][x] = '.';
						}
						break;

				}
			}
		}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				grid[y][x] = gridTmp[y][x];
			}
		}
		int var_bio = calcbio();
		printf("var_bio is %d\n", var_bio);
		if (mp.find(var_bio) == mp.end()) {
			printf("not found\n");
			mp[var_bio] = 1; 
		} else {
			printf("found\n");
			printf("** var_bio %d\n", var_bio);
			fflush(stdout); dup2(fd, 1);
			printf("**ans: %d\n", var_bio);
			break;
		}
		t++;
	}
		
}
int calcbio() {
	int bio = 0;
	int pos = 0;
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			
			if (grid[y][x] == '#') {	
				bio |= 1 << pos;
			}
			pos++;
		}
	}

	return bio;
}
void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}
