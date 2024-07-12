#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "plot grid for a py day15 2019\n"
#undef _DEBUG_
#define SZ 44
char grid[SZ][SZ];

void printit();
void printit() {
	for (int y = 0; y < SZ; y++) {
		for (int x = SZ-1 ; x >= 0; x--) {
			if (grid[y][x] == '#' || grid[y][x] == '.' || grid[y][x] == 'X') {
				printf("%c", grid[y][x]);
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
        FILE * b = fopen(argv[2], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[200];
        char line2[200];
while(1) {
        fgets(line1, 200-1, a);
        fgets(line2, 200-1, b);
        if (feof(a)) break;
        if (feof(b)) break;
	line1[strlen(line1) -1]='\0';
	line1[strlen(line2) -1]='\0';

	for (int i = 0; i < (int) strlen(line2); i++) {
		if (line2[i] == '#') {
			if (line1[i] != '#') {printf("diff hash\n");}
		} else if (line2[i] == '.' || line2[i] == 'D') {
			if (line1[i] != '.') {printf("diff dot\n");}
		}
	}
}
fclose(a);
fclose(b);

//	printit();
}
