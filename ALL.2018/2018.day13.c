#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

int tot = 0;
#define SIZE 299
char line1[SIZE];
char grid[300][300];
void next(int sPos);
int leny = 0;
void checkCollision();
struct starts_s {
	int x;
	int y;
	int DIR;
	char c;
	int turnsPos;
	int already;
};

struct starts_s starts[40];
int startsPos = 0;
void printit();
		struct po_s {
			int y;
			int x;
		};

		struct po_s po[20];
		int poPos = 0;
void mysort(); 
int fd;
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2018 Day13.1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[(int)strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(grid[leny], line1);
	for (int i = 0; i < (int)strlen(line1); i++) {
		switch(line1[i]) {
			case '>':
				starts[startsPos].x = i;
				starts[startsPos].y = leny;
				starts[startsPos].c = '>';
				starts[startsPos].DIR = 1;
				starts[startsPos].turnsPos = 0;
				startsPos++;
				grid[leny][i] = '-';
				break;
			case '<':
				starts[startsPos].x = i;
				starts[startsPos].y = leny;
				starts[startsPos].c = '<';
				starts[startsPos].DIR = 3;
				starts[startsPos].turnsPos = 0;
				startsPos++;
				grid[leny][i] = '-';
				break;
			case '^':
				starts[startsPos].x = i;
				starts[startsPos].y = leny;
				starts[startsPos].c = '^';
				starts[startsPos].DIR = 0;
				starts[startsPos].turnsPos = 0;
				startsPos++;
				grid[leny][i] = '|';
				break;
			case 'v':
				starts[startsPos].x = i;
				starts[startsPos].y = leny;
				starts[startsPos].c = 'v';
				starts[startsPos].DIR = 2;
				starts[startsPos].turnsPos = 0;
				startsPos++;
				grid[leny][i] = '|';
				break;
		}
	}
	leny++;
}
fclose(a);

	printf("startsPos is %d\n", startsPos);
	while (1) {
							
		for (int i = 0; i < startsPos; i++) {
			for (int j = 0; j < startsPos; j++) {
				if (po[i].y == starts[j].y && po[i].x == starts[j].x) {
					checkCollision();
					//printit(); getchar();
					next(j);
				}
			}
		}
		mysort();
		checkCollision();
	}

return 0;
}
void mysort() {
		int posY[20];
		for (int i = 0; i < startsPos; i++) {
			posY[i] = starts[i].y;
		}
		sort(posY, posY+startsPos);

		int posX[20];
		for (int i = 0; i < startsPos; i++) {
			posX[i] = starts[i].x;
		}
		sort(posX, posX+startsPos);

		poPos = 0;
		for (int i = 0; i < startsPos; i++) {
			starts[i].already = 0;
		}
		for (int i = 0; i < startsPos; i++) {
			for (int j = 0; j < startsPos; j++) {
				if (posY[i] == starts[j].y && starts[j].already == 0) {
					po[poPos].y = starts[j].y;
					for (int k = 0; k < startsPos; k++) {
						if (posX[k] == starts[j].x && starts[j].already == 0) {
							po[poPos].x = starts[j].x;
							starts[j].already = 1;
							poPos++;
						}
					}
				}
			}
		}
}

void printit() {
        printf("\x1b[2J");
        printf("\x1b[H");
        //printf("\x1b[%dC", 0);
        printf("\x1b[%dB", 3);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < (int)strlen(grid[y]); x++) {
			if (x == 0) {printf(" ");}
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	for (int i =0; i < startsPos; i++) {
        	printf("\x1b[H");
                printf("\x1b[%dC", starts[i].x+1);
                printf("\x1b[%dB%d", starts[i].y+3, i);
	}
	printf("\n\n\n\n\n");
	for (int i =0; i < startsPos; i++) {
		printf("x,y i %d,%d %d\n", starts[i].x, starts[i].y, i); 
	}
	//printf("\n");
}
void checkCollision() {
	int colNum = 0;
	for (int i = 0; i < startsPos-1; i++) {
		for (int j = 0; j < startsPos; j++) {
			if (i == j) {continue;}
			if (starts[i].x == starts[j].x && starts[i].y == starts[j].y) {
				//printf("%d, collisions at %d,%d\n", colNum++, starts[i].x, starts[i].y); getchar();
				fflush(stdout); dup2(fd, 1);
				printf("**ans: %d,%d\n", starts[i].x, starts[i].y); getchar();
				exit(0);
			} else {
				//printf("no coll\n");
			}
			
		}
	}
}
int ind = 0;
void next(int sPos) {

	ind++;
	//printf("ind: %d\n", ind);
	//printf("[%c]", grid[y][x]);

	switch(grid[starts[sPos].y][starts[sPos].x]) {
		case '-':
			if (starts[sPos].DIR == 1) {
				starts[sPos].x++; 
			} else if (starts[sPos].DIR == 3) {
				starts[sPos].x--; 
			}			
			break;
		case '|':
			if (starts[sPos].DIR == 2) {
				starts[sPos].y++;
			} else if (starts[sPos].DIR == 0) {
				starts[sPos].y--;
			}
			break;
				
		case '/':
			switch (starts[sPos].DIR) { 
				case 0:
					starts[sPos].DIR = 1;
					starts[sPos].x++;
					break;
				case 1:
					starts[sPos].DIR = 0;
					starts[sPos].y--;
					break;
				case 2:
					starts[sPos].DIR = 3;
					starts[sPos].x--;
					break;	
				case 3:
					starts[sPos].DIR = 2;
					starts[sPos].y++;
					break;
			}
			break;
		case '\\':         
			switch (starts[sPos].DIR) { 
				case 0:
					starts[sPos].DIR = 3;
					starts[sPos].x--;
					break;
				case 1:
					starts[sPos].DIR = 2;
					starts[sPos].y++;
					break;
				case 2:
					starts[sPos].DIR = 1;
					starts[sPos].x++;
					break;	
				case 3:
					starts[sPos].DIR = 0;
					starts[sPos].y--;
					break;
			}
			break;
		case '+':
			switch (starts[sPos].turnsPos) { 
				case 0:
					starts[sPos].DIR = (starts[sPos].DIR - 1 + 4) %4;
					break;
				case 1:
					break;
				case 2:
					starts[sPos].DIR = (starts[sPos].DIR + 1) %4;
					break;	
			}
			starts[sPos].turnsPos = (starts[sPos].turnsPos + 1) % 3;

			switch(starts[sPos].DIR) {
				case 0:
					starts[sPos].y--;
					break;
				case 1:
					starts[sPos].x++;
					break;
				case 2:
					starts[sPos].y++;
					break;
				case 3:
					starts[sPos].x--;
					break;
			}
			break;
		default:
			printf("ERR...\n"); exit(0);
	}
	ind--;
}
