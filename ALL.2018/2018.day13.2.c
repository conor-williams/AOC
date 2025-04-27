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
	int rem;
};
void removeCollisions();
void mysort2();

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
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day13.2\n"); fflush(stdout);

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
					starts[startsPos].rem = 0;
					startsPos++;
					grid[leny][i] = '-';
					break;
				case '<':
					starts[startsPos].x = i;
					starts[startsPos].y = leny;
					starts[startsPos].c = '<';
					starts[startsPos].DIR = 3;
					starts[startsPos].turnsPos = 0;
					starts[startsPos].rem = 0;
					startsPos++;
					grid[leny][i] = '-';
					break;
				case '^':
					starts[startsPos].x = i;
					starts[startsPos].y = leny;
					starts[startsPos].c = '^';
					starts[startsPos].DIR = 0;
					starts[startsPos].turnsPos = 0;
					starts[startsPos].rem = 0;
					startsPos++;
					grid[leny][i] = '|';
					break;
				case 'v':
					starts[startsPos].x = i;
					starts[startsPos].y = leny;
					starts[startsPos].c = 'v';
					starts[startsPos].DIR = 2;
					starts[startsPos].turnsPos = 0;
					starts[startsPos].rem = 0;
					startsPos++;
					grid[leny][i] = '|';
					break;
			}
		}
		leny++;
	}
	fclose(a);

	//100,7
	/*
	   while (1) {
	   for (int i = 0; i < startsPos; i++) {
	   checkCollision();
	   next(i);
	   if (startsPos == 1) {
	   printf("%d,%d\n", starts[0].x, starts[0].y); 
	   printf("^^^^   ANS POSS  ^^^^\n"); getchar();
	   }
	   }
	   removeCollisions();
	   }
	 */
	printf("startsPos is %d\n", startsPos);
	while (1) {
		for (int i = 0; i < startsPos; i++) {
			if (starts[i].rem == 0) {
				checkCollision();
				//printit(); getchar();
				next(i);
			}
		}

		if (startsPos == 1) {

			printf("%d,%d\n", starts[0].x, starts[0].y); 
			printf("^^^^   ANS POSS  ^^^^\n"); getchar();
		}
		checkCollision();
		removeCollisions();
		mysort();
	}
	/*
	   printf("startsPos is %d\n", startsPos);
	   while (1) {
	   mysort();

	   for (int i = 0; i < startsPos; i++) {
	   for (int j = 0; j < startsPos; j++) {
	   if (po[i].y == starts[j].y && po[i].x == starts[j].x && starts[j].rem == 0) {
	   checkCollision();
	//printit(); getchar();
	next(j);
	}
	}
	}
	if (startsPos == 1) {
	printf("%d,%d\n", starts[0].x, starts[0].y); 
	printf("^^^^   ANS POSS  ^^^^\n"); getchar();
	}
	checkCollision();
	removeCollisions();
	mysort();
	}
	 */
	return 0;
}
/*
   void mysort2() {
   if (startsPos == 1) {
   po[0].x = starts[0].x;
   po[0].y = starts[0].y;
   poPos = 1;
   return;
   }
   int posY[20];
   for (int i = 0; i < startsPos; i++) {
   posY[i] = starts[i].y;
   }
   sort(posY, posY+startsPos);

   poPos = 0;

   int distinct[10]; int distinctPos = 0;
   for (int i = 0; i < startsPos-1; i++) {
   if (posY[i] != posY[i+1]) {
   distinct[distinctPos++] = posY[i];
   }
   }

   if (distinctPos == 0) {distinct[0] = posY[0]; distinctPos++;}

   int counts[10]; int countsPos = 0;
   for (int i = 0; i < distinctPos; i++) {
   for (int j = 0; j < startsPos; j++) {
   if (posY[j] == distincts[i]) {
   counts[countsPos]++;
   }
   }
   }
/////	
for (int i = 0; i < startsPos-1; i++) {
if (posY[i] == posY[i+1]) {
counts[posY[i]]++;
}

}
for (int i = 0; i < startsPos; i++) {
for (int j = 0; j < startsPos; j++) {
if (posY[i] == starts[j].y && starts[j].already == 0) {
po[poPos].x = starts[j].x;
po[poPos].y = starts[j].y;
starts[j].already = 1;
poPos++;
}
}
}
}
 */

/*
   bool
   operator < (const positionInfo & left, const positionInfo & right)
   {
   return left.X + left.Y < right.X + right.Y;
   }
 */

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


again:
	for (int i = 0; i < startsPos-1; i++) {
		for (int j = i+1; j < startsPos; j++) {
			if (starts[i].y >  starts[j].y)  {
				struct starts_s tmp;
				tmp = starts[i]; 
				starts[i] = starts[j];
				starts[j] = tmp;
				goto again;
			}
		}
	}

again2:
	for (int i = 0; i < startsPos-1; i++) {
		for (int j = i+1; j < startsPos; j++) {
			if (starts[i].y ==  starts[j].y)  {
				if (starts[i].x > starts[j].x) {
					struct starts_s tmp;
					tmp = starts[i]; 
					starts[i] = starts[j];
					starts[j] = tmp;
					goto again2;
				}
			}
		}
	}	

	/*
	   for (int i = 0; i < startsPos-1; i++) {
	   for (int j = i+1; j < startsPos; j++) {
	   po[poPos].y = starts[j].y;
	   if (posY[i] == posY[i+1]) {
	   for (int k = 0; k < startsPos; k++) {
	   if (starts[j].x == posY[k]) {
	   po[poPos].x = starts[j].x;	
	   starts[j].already = 1;
	   }
	   }
	   } else {
	   po[poPos].x = starts[j].x;
	   }
	   poPos++; break;
	   }
	   }
	 */
	/*

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
	 */
	for (int i = 0; i < startsPos-1; i++) {
		for (int j = i+1; j < startsPos; j++) {
			if (po[i].y == po[j].y) {
				if (po[i].x > po[j].x) {
					printf("ERR\n"); getchar();
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

void removeCollisions() {
restart:
	for (int i = 0; i < startsPos; i++) {
		if (starts[i].rem == 1) {
			for (int z = i; z < startsPos-1; z++) {
				starts[z] = starts[z+1]; 
			}
			startsPos--;
			goto restart;
		}
	}
	if (startsPos == 1) {
		printf("ANS: %d,%d\n", starts[0].x, starts[0].y); 
		fflush(stdout); dup2(fd, 1);
		printf("**ans: %d,%d\n", starts[0].x, starts[0].y); 
		exit(0);
		printf("^^^^   ANS  ^^^^\n"); getchar();
	}
}
void checkCollision() {
	int colNum = 0;
	for (int i = 0; i < startsPos-1; i++) {
		for (int j = i+1; j < startsPos; j++) {
			if (starts[i].x == starts[j].x && starts[i].y == starts[j].y && starts[j].rem == 0) {
				printf("%d, collisions at %d,%d\n", colNum++, starts[i].x, starts[i].y);
				starts[i].rem = 1;
				starts[j].rem = 1;
				if (startsPos == 3) {
					for (int z = 0; z < 3; z++) {
						if (z == i || z ==j) {
						} else {
							printf("maybe: %d,%d\n", starts[z].x, starts[z].y);
						}
					}
				}
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
