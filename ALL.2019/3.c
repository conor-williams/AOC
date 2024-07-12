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
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[25000];
while(1) {
        fgets(line1, 25000-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';

	char *first = strtok(line1, "*");
	int x1;
	int y1;
	char wat;	
	do {
		sscanf(first, " (%d, %d): \'%c\'", &y1, &x1, &wat);
		//printf("first is %s\n", first);
		//printf(" %d %d %c\n", y1, x1, wat);
		
		if (x1 == 0 && y1 == 0) {printf("wat was %c\n", wat); getchar(); wat = 'X';}
		grid[(SZ/2)+y1][(SZ/2)+x1] = wat;
	} while ((first = strtok(NULL, "*")) != NULL);
}
fclose(a);

	printit();
}
