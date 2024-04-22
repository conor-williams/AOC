#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2016 day8 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 100
#define GRID 80
char grid[GRID][GRID];
int already[GRID][GRID];
int countSetBits(unsigned int n);
int next(int x, int y, int prev);

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
	for (int y = 0; y < GRID; y++) {
		for (int x = 0; x < GRID; x++) {
			already[y][x] = -1;
		}
	}
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	leny++;
}
fclose(a);

	//int fav = 10;
	int fav = 1362;
	for (int y = 0; y < GRID; y++) {
		for (int x = 0; x < GRID; x++) {
			unsigned int ans = x*x + 3*x + 2*x*y + y + y *y + fav;
			if (countSetBits(ans) % 2 == 0) {
				grid[y][x] = '.';
			} else {
				grid[y][x] = '#';
			}
		}
	}		
	for (int y = 0; y < GRID; y++) {
		for (int x = 0; x < GRID; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}

	int sX = 1; int sY = 1;
	already[sY][sX] = 0;	
	
	int y = sY; int x = sX;
	if (y -1 < 0)    {} else { next(x, y-1, already[y][x]);}
	if (x+1 >= GRID) {} else { next(x+1, y, already[y][x]);}
	if (y+1 >= GRID) {} else { next(x, y+1, already[y][x]);}
	if (x -1 < 0)    {} else { next(x-1, y, already[y][x]);}

	for (int y = 0; y < GRID; y++) {
		for (int x = 0; x < GRID; x++) {
			if (already[y][x] > -1) {
				tot++;
			}
		}
	}
	printf("\n");
	printf("***tot %ld END\n", tot); fflush(stdout);
} 

int next(int x, int y, int prev)
{
	if (grid[y][x] == '#') {
		return 0;
	} else if (grid[y][x] == '.') {
		if (already[y][x] == -1 || already[y][x] > prev+1) {
			already[y][x] = prev+1;
			if (prev+1 == 50) {return 0;}
			if (y == 39 && x == 31) {
				printf("a path is %d\n", already[y][x]); getchar();
			}

			if (y -1 < 0)    {} else { next(x, y-1, already[y][x]);}
			if (x+1 >= GRID) {} else { next(x+1, y, already[y][x]);}
			if (y+1 >= GRID) {} else { next(x, y+1, already[y][x]);}
			if (x -1 < 0)    {} else { next(x-1, y, already[y][x]);}

		}
	}
	return 1;

}
int countSetBits(unsigned int n)
{
  unsigned char lookup_t[256] = {0}; 
  int i, count = 0;
 
  // generate the lookup table
  for (i = 0; i < 256; i++)
  {
    lookup_t[i] = (i & 1) + lookup_t[i / 2];
  }
 
  /* Get sie of int program by size of operator. 
     It makes the solution consistent for different word sizes */
  for (i = 1; i <= sizeof(int) && n; i++)
  {
    count += lookup_t[n & 255];
    n >>= 8;
  }
 
  return count;
}
