#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2016 day8 part1 \n"
#define _DEBUG_
long tot;

#define XM 50
#define YM 6
char grid[YM][XM] = {0};
void printGrid();
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[220];
while(1) 
{
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
//	printGrid(); getchar();
	char first[10];
	int f = 0; int s = 0; int r = 0; int c = 0;
	int ret = 0;
	ret = sscanf(line1, "rect %[^x]x%d", first, &s);
	printf("ret X is %d\n", ret);
	if (ret == 2) {
		f = atoi(first);
		printf("f [%d], s %d\n", f, s); 
		for (int y = 0; y < s; y++) {
			for (int x = 0; x < f; x++) {
				printf("y x %d %d\n", y, x);
				grid[y][x] = 1;				
			}
		} 
		printGrid(); 
		goto end;
	}
	ret = sscanf(line1, "rotate row y=%d by %d", &r, &f);
	printf("ROT ROW: ret is %d\n", ret);
	if (ret == 2) {
		printf("row %d, f %d\n", r, f);
		int y = r; 
		int tmpX[XM];
		for (int x1 = 0; x1 < XM; x1++) {
			tmpX[x1] = grid[y][x1];
		}
		for (int x = 0; x < XM ; x++) {
			int pos = (x+f) % XM;
			grid[y][pos] = tmpX[x];
		}
		printGrid(); 
		goto end;
	}
	ret = sscanf(line1, "rotate column x=%d by %d", &c, &f);
	printf("ROT COL: ret is %d\n", ret);
	if (ret == 2) {
	printf("column %d, f %d\n", c, f);
		int x = c;
		int tmpCol[YM];
		for (int y1 = 0; y1 < YM; y1++) {
			tmpCol[y1] = grid[y1][x];
		}
		for (int y = 0; y < YM ; y++) {
			int pos = (y+f) % YM;
			grid[pos][x] = tmpCol[y]; 
			printf("y x %d %d\n", pos, x); 
		}
		printGrid(); 
		goto end;
	}

end:
	leny++;
}
fclose(a);
	int count = 0;
	for (int x = 0; x < XM; x++) {
		for (int y = 0; y < YM; y++) {
			if (grid[y][x] == 1) {
				count++;
			}
		}
	}	
	printf("***count %d\n", count);
	printf("END\n");
} 
void printGrid() {
	for (int y = 0; y < YM; y++) {
		for (int x = 0; x < XM; x++) {
			if (grid[y][x] == 1) {
				printf("%d", grid[y][x]);
			} else {
				printf(" ");
			}
			if ((x+1) % 5 == 0) {
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}
