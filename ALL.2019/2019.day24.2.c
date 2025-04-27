#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>

using namespace std;
#include <unistd.h>

#define getchar()

int lenx, leny;
#define DAY "		2019 day24 part2\n"
#undef _DEBUG_
#define LINE 50
#define getchar()

#define SZ 6

#define DEPTH 251
#define TIME 200
char grid[DEPTH+2][SZ][SZ];
char gridTmp[DEPTH+2][SZ][SZ];
char gridOrig[SZ][SZ];
void printit(int depth);
void printitTmp(int depth);
void swi(int count, int gr, int x, int y);
void checkGrid(int gr);

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
while(1) {

        fgets(line1, LINE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif
	strcpy(gridOrig[leny], line1);
	printf("lenx %d - leny %d\n", lenx, leny);
	leny++;
}
fclose(a);
	lenx = strlen(gridOrig[0]);

	for (int i = 0; i < DEPTH; i++) {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (x == 2 && y == 2) {
				gridTmp[i][2][2] = '?';
			} else {
				gridTmp[i][y][x] = '.';
			}
		}
	}
	}

	for (int i = 0; i < DEPTH; i++) {
		if (DEPTH/2 == i) {continue;}
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				if (x==2 && y==2) {
					grid[i][2][2] = '?';
				} else {
					grid[i][y][x] = '.';
				}
			}
		}
	}

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			grid[DEPTH/2][y][x] = gridOrig[y][x];
		}
	}
		
	printit(DEPTH/2); getchar();
	int t = 0;
	while (1) {
		printf("After %d minutes:\n", t);
		checkGrid(DEPTH/2);
		for (int gr = (DEPTH/2)+1; gr < DEPTH; gr++) {
			checkGrid(gr);
			if (gr == 7) {
				printit(gr);
				printitTmp(gr);
			}

		}
		for (int gr = (DEPTH/2)-1; gr > 0; gr--) {
			checkGrid(gr);
		}
			
		t++;
		
		//printit(DEPTH/2); getchar();
		for (int i = 0; i < DEPTH; i++) {
		for (int y = 0; y < leny; y++) {
			for (int x = 0; x < lenx; x++) {
				grid[i][y][x] = gridTmp[i][y][x];
			}
		}
		}
		if (t == TIME) {break;}
	}

	for (int i = 0; i < DEPTH; i++) {
		printit(i);
	}

	/// FINISH with a count:
	int count2 = 0;
	for (int i = 0; i < DEPTH; i++) {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (grid[i][y][x] == '#') {
					count2++;
				}
			}
		}
	}
	printf("**ans is [ %d ]\n", count2);
	fflush(stdout); dup2(fd, 1);
	printf("**ans:  %d \n", count2);
		
}
void printitTmp(int depth) {
	printf("-TMP--- %d ----\n", depth);

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", gridTmp[depth][y][x]);
		}
		printf("\n");
	}
	printf("\n");
}
void printit(int depth) {
	printf("---- %d ----\n", depth);

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			printf("%c", grid[depth][y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

void swi(int count, int de, int x, int y) 
{
	if (grid[de][y][x] != '#' && grid[de][y][x] != '.') {
		printf("ERROR\n"); exit(0);
	}
	if (x == 2 && y ==2) {
		printf("ERR\n"); exit(0);
	}

	switch(grid[de][y][x]) {
		case '#': 
			//if (de == 7) {printf("count is %d (%c)\n", count, grid[de][y][x]); getchar();}
			if (count == 1) {
				gridTmp[de][y][x] = '#';
			} else {
				gridTmp[de][y][x] = '.';
			}
			break;
		case '.':
			//if (de == 7) {printf("count is %d (%c)\n", count, grid[de][y][x]); getchar();}
			if (count == 1 || count == 2) {
				gridTmp[de][y][x] = '#';
				//if (de == 7) { printf(" count is one or two -- setting to hash -- de is %d %d,%d\n", de, x,y); }
			} else {
				//if (de == 7) { printf(" count is not one or two -- setting to dot -- de is %d\n", de); }
				gridTmp[de][y][x] = '.';
			}
			break;

	}
}
void checkGrid(int gr) {
	printf("calling checkGrid %d\n", gr); getchar();
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (x == 2 && y == 2) {continue;}

			if (x == 2 && y == 1) {continue;}
			if (x == 2 && y == 3) {continue;}
			if (x == 1 && y == 2) {continue;}
			if (x == 3 && y == 2) {continue;}

			int count = 0;
			if (grid[gr][y-1][x] == '#') {count++;} 
			if (grid[gr][y][x+1] == '#') {count++;}
			if (grid[gr][y+1][x] == '#') {count++;}
			if (grid[gr][y][x-1] == '#') {count++;}

			swi(count, gr, x, y);
		}
	}

	{int y = 0; int x = 0;
	{
		int count = 0;
		if (grid[gr-1][1][2] == '#') {count++;} 
		if (grid[gr-1][2][1] == '#') {count++;}

		if (grid[gr][y][x+1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}
		swi(count, gr, x, y);
	}
	}

	{int y = 0; 
	for (int x = 1; x< 4; x++) {
		int count = 0;
		if (grid[gr-1][1][2] == '#') {count++;} 

		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}

		swi(count, gr, x, y);
	}
	}

	{int y = 0; int x = 4;
	{
		int count = 0;
		if (grid[gr-1][2][3] == '#') {count++;} 
		if (grid[gr-1][1][2] == '#') {count++;}

		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}

		swi(count, gr, x, y);
	}
	}

	{int x = 4;
	for (int y = 1; y<4; y++) {
		int count = 0;
		if (grid[gr-1][2][3] == '#') {count++;}

		if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}

		swi(count, gr, x, y);
	}
	}

	{int y = 4; int x = 4;
	{
		int count = 0;
		if (grid[gr-1][2][3] == '#') {count++;}

		if (grid[gr-1][3][2] == '#') {count++;}

		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y-1][x] == '#') {count++;}
		swi(count, gr, x, y);

	}
	}

	{
	int y = 4;
	for (int x = 3; x > 0; x--) {
		int count = 0;

		if (grid[gr-1][3][2] == '#') {count++;}

		if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		swi(count, gr, x, y);
	}
	}
	
	{
	int y = 4; int x = 0;
	{
		int count = 0;

		if (grid[gr-1][2][1] == '#') {count++;}
		if (grid[gr-1][3][2] == '#') {count++;}

		if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		swi(count, gr, x, y);
	}
	}

	{int x = 0;
	for (int y = 3; y > 0; y--) 
	{
		int count = 0;

		if (grid[gr-1][2][1] == '#') {count++;}

		if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		swi(count, gr, x, y);
	}
	}
	
	/// INSIDE....

	{int x = 2; int y = 1;
	{
		int count = 0;
		if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		if (grid[gr][y][x-1] == '#') {count++;}
		//if (grid[gr][y+1][x] == '#') {count++;}

		int y1 = 0;
		for (int x1 = 0; x1 <= 4; x1++) {
			if (grid[gr+1][y1][x1] == '#') {count++;}	
		}


		swi(count, gr, x, y);
		
	}
	}

	{int x = 3; int y = 2; //N
	{
		int count = 0;
		if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		//if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}

		int x1 = 4;
		for (int y1 = 0; y1 <= 4; y1++) {
			if (grid[gr+1][y1][x1] == '#') {count++;}	
		}

		swi(count, gr, x, y);
		
	}
	}

	{int x = 2; int y = 3;
	{
		int count = 0;
		//if (grid[gr][y-1][x] == '#') {count++;}
		if (grid[gr][y][x+1] == '#') {count++;}
		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}

		int y1 = 4;
		for (int x1 = 0; x1 <= 4; x1++) {
			if (grid[gr+1][y1][x1] == '#') {count++;}	
		}

		swi(count, gr, x, y);
		
	}
	}

	{int x = 1; int y = 2;
	{
		int count = 0;
		if (grid[gr][y-1][x] == '#') {count++;}
		//if (grid[gr][y][x+1] == '#') {count++;}
		if (grid[gr][y][x-1] == '#') {count++;}
		if (grid[gr][y+1][x] == '#') {count++;}

		int x1 = 0;
		for (int y1 = 0; y1 <= 4; y1++) {
			if (grid[gr+1][y1][x1] == '#') {count++;}	
		}
		swi(count, gr, x, y);
		
	}
	}



}
