#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <map>

#include <unistd.h>

#define getchar()
using namespace std;
int lenx = 0;
int leny = 0;
int lenz = 0;
//#define getchar()

int LINE = 1000;

#define GX 11

char gridInitial[GX][GX];
#define NUMG 144

struct grid_s {
	int num;
	char gr[GX][GX];
};
struct grid_s grid[NUMG];
char gridtmp[GX][GX];
char gridOrig[GX][GX];
map <int, int> sidesMap;

void rotate(int );
void swap(char *x, char *y);
void transpose(int );
void reverse(int );
void saveOrig(int i);
void recoverOrig(int i);
void save(int i);
void recover(int i);
void VFlipArray(char (*array)[GX]);
void FlipColumn(char (*array)[GX], int column, int rows);
void HFlipArray(char (*array)[GX]);
void FlipRow(char *row, int columns);
int swap2(char *a, char *b);
void check(int i);

int POS = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day20 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

//Tile 2477:
	leny = -1;
	int lin = 0;
while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);
	if (line1[0] == '\0') {
		continue;
	} else if (line1[0] == 'T') {
		leny++;
		char snum[100];
		sscanf(line1, "Tile %[^:]:", snum);
		grid[leny].num = atoi(snum);
		lin = 0;
	} else {
		strcpy(grid[leny].gr[lin++], line1);
	}
}
	leny++;
/*
	for (int i = 0; i < NUMG; i++) {
		printf("Tile %d:\n", grid[i].num);
		for (int y = 0; y < GX-1; y++) {
			for (int x = 0; x < GX-1; x++) {
				printf("%c", grid[i].gr[y][x]);
			}
			printf("\n");
		}
		printf("\n");
	}
*/
	
	assert(leny == NUMG);

	unsigned long long mul = 1;
	for (int i = 0; i < NUMG; i++) {
		POS = 0;
		sidesMap.clear();
		saveOrig(i);

		check(i); rotate(i); check(i); save(i); VFlipArray(grid[i].gr); check(i); recover(i); HFlipArray(grid[i].gr); check(i); recover(i); VFlipArray(grid[i].gr); HFlipArray(grid[i].gr); check(i); recover(i); check(i);
		check(i); rotate(i); check(i); save(i); VFlipArray(grid[i].gr); check(i); recover(i); HFlipArray(grid[i].gr); check(i); recover(i); VFlipArray(grid[i].gr); HFlipArray(grid[i].gr); check(i); recover(i); check(i);
		check(i); rotate(i); check(i); save(i); VFlipArray(grid[i].gr); check(i); recover(i); HFlipArray(grid[i].gr); check(i); recover(i); VFlipArray(grid[i].gr); HFlipArray(grid[i].gr); check(i); recover(i); check(i);
		check(i); rotate(i); check(i); save(i); VFlipArray(grid[i].gr); check(i); recover(i); HFlipArray(grid[i].gr); check(i); recover(i); VFlipArray(grid[i].gr); HFlipArray(grid[i].gr); check(i); recover(i); check(i);

		recoverOrig(i);

		//if (POS == 10 || POS == 5 || POS == 6 || POS == 9) {
		if (sidesMap.size() == 2) {
			mul *= grid[i].num;
			printf("sides 2 -- %d\n", grid[i].num);
		} else {
			printf("sides %d -- %d\n", (int)sidesMap.size(), grid[i].num);
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", mul);
}
int swap2(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp; 
    return 0;

}

void FlipRow(char *row, int columns)
{
    for (int index = 0; index < columns / 2; index++)
    {
        swap2(row+index, row+columns-1-index);
    } 
}

void HFlipArray(char (*array)[GX])
{
    int columns = GX-1;
    int rows = GX-1;
    for (int row = 0; row < rows; row++)
    {
        FlipRow(array[row], columns);
    }
}
void FlipColumn(char (*array)[GX], int column, int rows)
{
    for (int row = 0; row < rows/2; row++)
    {
        swap2(array[row]+column, array[rows-1-row]+column);
    }
}

void VFlipArray(char (*array)[GX])
{
    int columns = GX-1;
    int rows = GX-1;
    for (int column = 0; column < columns; column++)
    {
        FlipColumn(array, column, rows);
    }
}
void saveOrig(int i) {
	for (int y = 0; y < GX-1; y++) {
		for (int x = 0; x < GX-1; x++) {
			gridOrig[y][x] = grid[i].gr[y][x];
		}
	}
}
void recoverOrig(int i) {
	for (int y = 0; y < GX-1; y++) {
		for (int x = 0; x < GX-1; x++) {
			grid[i].gr[y][x] = gridOrig[y][x];
		}
	}
}

void save(int i) {
	for (int y = 0; y < GX-1; y++) {
		for (int x = 0; x < GX-1; x++) {
			gridtmp[y][x] = grid[i].gr[y][x];
		}
	}
}
void recover(int i) {
	for (int y = 0; y < GX-1; y++) {
		for (int x = 0; x < GX-1; x++) {
			grid[i].gr[y][x] = gridtmp[y][x];
		}
	}
}

void check(int i) {
	for (int j = 0; j < NUMG; j++) {
		if (i == j) {continue;}
		//printf("checking %d with %d\n", grid[i].num, grid[j].num);
		{//TOP of I with bottom of J
			int abber = 0;
			
			for (int x = 0; x < GX-1; x++) {
				if (grid[i].gr[0][x] == grid[j].gr[GX-2][x]) {
					//printf("same tibj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			if (abber == 0) {/*POS |= (1 << 0); */sidesMap[j] = 1; /*printf("top of %d == bottom of %d\n", grid[i].num, grid[j].num);*/}
		}
		{//BOTTOM of I with TOP of J
			int abber = 0;
			for (int x = 0; x < GX-1; x++) {
				if (grid[i].gr[GX-2][x] == grid[j].gr[0][x]) {
					//printf("same bitj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			if (abber == 0) {POS |= (1 << 1); sidesMap[j] = 1; /*printf("bottom of %d == top of %d\n", grid[i].num, grid[j].num);*/}
		}
		{//LEFT of I with RIGHT of J
			int abber = 0;
			for (int y = 0; y < GX-1; y++) {
				if (grid[i].gr[y][0] == grid[j].gr[y][GX-2]) {
					//printf("same lirj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			
			if (abber == 0) {POS |= (1 << 2); sidesMap[j] = 1; /*printf("left of %d == right of %d\n", grid[i].num, grid[j].num);*/}
		}
		{//RIGHT of I with LEFT of J
			int abber = 0;
			for (int y = 0; y < GX-1; y++) {
				if (grid[i].gr[y][GX-2] == grid[j].gr[y][0]) {
					//printf("same rilj\n"); getchar();
				} else {
					abber = 1;
					break;
				}
			}
			
			if (abber == 0) {POS |= (1 << 3); sidesMap[j] = 1; /*printf("right of %d == left of %d\n", grid[i].num, grid[j].num);*/}
		}
	}
}

					

void rotate(int wh) {
	transpose(wh);
	reverse(wh);	
}

void swap(char *x, char *y) {
    int temp = *x;
    *x = *y;
    *y= temp;
}

void transpose(int wh) {
  for(int i=0; i<GX-1; i++){
     for(int j=i+1; j<GX-1; j++)
         swap(&grid[wh].gr[i][j], &grid[wh].gr[j][i]);
    }
}

void reverse(int wh) {
  for(int i=0; i<GX-1; i++){
     for(int j=0; j<GX-1/2; j++){
        swap(&grid[wh].gr[i][j], &grid[wh].gr[i][(GX-1)-j-1]);
     }
   }
}
