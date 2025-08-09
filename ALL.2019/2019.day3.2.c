#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <map>
#include <unistd.h>

using namespace std;
#define getchar()
int pos;
int lenx, leny;
#define DAY "		2019 day3 part2\n"
#undef _DEBUG_
struct posmin {
	int x;
	int y;
	int man;
	int stepsW1;
	int stepsW2;
};
struct posmin points[1000];
/*
#define GRIDX 50
#define GRIDY 50
#define STARTX 10
#define STARTY 40
*/
/*
#define GRIDX 35000
#define GRIDY 20000
#define STARTX 30000
#define STARTY 15000
*/
int GRIDX = 0;
int GRIDY = 0;
int STARTX = 0;
int STARTY = 0;
int prevX; int prevY; 
void recordW1(int x, int y, int man, int stepsW1);
void recordW1(int x, int y, int man, int stepsW1) {
	for (int i = 0; i < pos; i++) {
		if (points[i].x == x && points[i].y == y) {
			points[i].stepsW1 = stepsW1;
			break;
		}

	}
}
void recordW2(int x, int y, int man, int stepsW2);
void recordW2(int x, int y, int man, int stepsW2) {

	points[pos].x = x;	
	points[pos].y = y;
	points[pos].man = man;
	points[pos].stepsW2 = stepsW2;
	pos++;
}
int man2X();
int man2X(int x, int y) {
	return abs(STARTX - x) + abs(STARTY - y);

}
/*
   void manX();
   void manX() {
   for (int y = 0; y < GRIDY; y++) {
   for (int x = 0 ; x < GRIDX; x++) {
   if (puz[1][y][x] == 'X') {
   printf("res is: %d\n", abs(STARTX - x) + abs(STARTY - y));
   }
   }
   }

   }
   void minmanX();
   void minmanX() {
   int min = 0;
   int first = 0;
   for (int y = 0; y < GRIDY; y++) {
   for (int x = 0 ; x < GRIDX; x++) {
   if (puz[1][y][x] == 'X') {
   if (first == 0) {first = 1; min = abs(STARTX-x) + abs(STARTY-y);}
   if ((abs(STARTX -x) + abs(STARTY-y)) < min) {
   min = abs(STARTX -x) + abs(STARTY-y);
   }
   }
   }
   }
   printf("min is %d\n", min);

   }
   void printpuzzle();
   void printpuzzle() {
   for (int y = 0; y < GRIDY; y++) {
   for (int x = 0 ; x < GRIDX; x++) {
   printf("%c", puz[1][y][x]);
   }
   printf("\n");
   }
   }
   void dotpuzzle();

   void dotpuzzle()
   {
   for (int y = 0; y < GRIDY; y++) {
   for (int x = 0 ; x < GRIDX; x++) {
   puz[0][y][x] = '.';
   puz[1][y][x] = '.';
   }
   }
   }
   */
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1);// close(1);
	pos = 0;

	char line1[3000];
	int wire = 0;
	int stepsW1 = 0; int stepsW2 = 0;
	int startx = 0;
	int starty = 0;
	int minX = 99999999;
	int minY = 99999999;
	int maxX = 0;
	int maxY = 0;
	int pX = 0; int pY = 0;
	char lines[2][3000];

	while (1) {
		pX = 0; pY = 0;
		int num = 0;
		fgets(line1, 2990, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		strcpy(lines[wire], line1);
		lenx = strlen(line1);
		//printf("%s\n", lines[wire]); fflush(stdout);
		char *token = strtok(line1, ",\0");
		while (token != NULL) {
			char tokenRLUD = token[0];
			token[0] = ' ';
			//printf("%s\n", token);
			num = atoi(token);
			//printf("%d\n", num);
			switch(tokenRLUD) {
				case 'R':
					pX+=num;
					break;
				case 'L':
					pX-=num;
					break;
				case 'U':
					pY-=num;
					break;
				case 'D':
					pY+=num;
					break;
			}
			if (pX > maxX) {maxX = pX;}
			if (pX < minX) {minX = pX;}
			if (pY > maxY) {maxY = pY;}
			if (pY < minY) {minY = pY;}
			token = strtok(NULL, ",\0");
		}
		wire++;
	}
	fclose(a);

	GRIDX = maxX-minX+30;
	GRIDY = maxY-minY+30;


	STARTX=abs(minX)+15;
	STARTY=abs(minY)+15;

	//char puz[2][GRIDY][GRIDX];
	map <int, map <int, char>> grid;
	map <int, map <int, int>> trip1;
	map <int, map <int, int>> trip2;

	/*
	   for (int y = 0; y < GRIDY; y++) {
	   for (int x = 0 ; x < GRIDX; x++) {
	   puz[0][y][x] = '.';
	   puz[1][y][x] = '.';
	   }
	   }
	   */
	wire = 0;

	while(1) {
		if (wire == 2) {break;}

		strcpy(line1, lines[wire]);

		int lenlen = 0;
		int x = STARTX;
		int y = STARTY;
		if (wire == 1) {
			grid[y][x] = '1';
		}
		char *token = strtok(line1, ",\n");
		while (token != NULL) {
			char URDL = token[0];
			token[0] = ' ';
			int val = atoi(token);
			switch (URDL) {
				case 'U':
					for (int yy = 0; yy < val; yy++) {
						y--;
						lenlen++;
						if (wire == 0) {
							grid[y][x] = '1';
							if (trip1[y][x] == 0) {
								trip1[y][x] = lenlen;
							}
						} else if (wire == 1) {
							if (trip2[y][x] == 0) {
								trip2[y][x] = lenlen;
							}
							if (grid[y][x] == '1' || grid[y][x] == '3') {
								grid[y][x] = '3';
							} else {
								grid[y][x] = '2';
							}
						}
					}
					break;
				case 'R':
					for (int xx = 0; xx < val; xx++) {
						x++;
						lenlen++;
						if (wire == 0) {
							if (trip1[y][x] == 0) {
								trip1[y][x] = lenlen;
							}
							grid[y][x] = '1';
						} else if (wire == 1) {
							if (trip2[y][x] == 0) {
								trip2[y][x] = lenlen;
							}
							if (grid[y][x] == '1' || grid[y][x] == '3') {
								grid[y][x] = '3';
							} else {
								grid[y][x] = '2';
							}
						}
					}
					break;
				case 'D':
					for (int yy = 0; yy < val; yy++) {
						y++;
						lenlen++;
						if (wire == 0) {
							if (trip1[y][x] == 0) {
								trip1[y][x] = lenlen;
							}
							grid[y][x] = '1';
						} else if (wire == 1) {
							if (trip2[y][x] == 0) {
								trip2[y][x] = lenlen;
							}
							if (grid[y][x] == '1' || grid[y][x] == '3') {
								grid[y][x] = '3';
							} else {
								grid[y][x] = '2';
							}
						}
					}
					break;
				case 'L':
					for (int xx = 0; xx < val; xx++) {
						x--;
						lenlen++;
						if (wire == 0) {
							if (trip1[y][x] == 0) {
								trip1[y][x] = lenlen;
							}
							grid[y][x] = '1';
						} else if (wire == 1) {
							if (trip2[y][x] == 0) {
								trip2[y][x] = lenlen;
							}
							if (grid[y][x] == '1' || grid[y][x] == '3') {
								grid[y][x] = '3';
							} else {
								grid[y][x] = '2';
							}
						}
					}
					break;
			}

			token = strtok(NULL, ",\n");
		}
		wire++;

	}
	int minlen = 9999999;
	for (auto yyy: grid) {
		for (auto xxx: yyy.second) {
			if (xxx.second == '3') {
				int len = trip1[yyy.first][xxx.first] + trip2[yyy.first][xxx.first];
				if (len < minlen) {minlen = len;}
			}
		}
	}
	printf("**ans: ");
	printf("%d", minlen);
	printf("\n");


}

