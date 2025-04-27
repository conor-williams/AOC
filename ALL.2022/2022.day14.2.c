#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()

std::string replaceAll(std::string str, const std::string& from, const std::string& to);
std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
#define SX 11000
//447 515 13 168
int y22, x21;
char grid[SX][SX];
char gridTmp[SX][SX];
void printit();
void leftOrRight(int x, int y);
int minX = 99999, maxX = 0, minY = 99999, maxY = 0;
int mainX = 500; int mainY = 0;
void printit2(int sx, int ex, int sy, int ey);
void printit3(int x, int y);
void countit();
void justCount(); 
int var_count = 0;

int fd;
void sigfunc(int a) { countit(); printit(); justCount();}
int check(char a, char b, char c, int *x, int *y);
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 14 part2\n"); fflush(stdout);

	//fflush(stdout); int fd = dup(1); //close(1);
	char line1[LINE];
	char l2[LINE];

	memset(grid, '.', sizeof(grid));
	memset(gridTmp, '.', sizeof(gridTmp));
	int leny = 0;
	while (1) {
		//printf("----------------------\n");
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);

		string l1 = line1;
		l1 = replaceAll(l1, " -> ", " - ");
		//l1 = replaceAll(l1, " ", " ");

		strcpy(l2, l1.c_str());	
		//printf("l2 is %s\n", l2);
		char *f1 = strtok(l2, "- \0");
		int x1 = -1, y1 = -1;
		int first = 0;
		int prevX1, prevY1; int tmp1, sx, sy, ex, ey;
		do {
			prevX1 = x1; prevY1 = y1;
			int ret = sscanf(f1, "%d,%d", &x1, &y1);
			//printf("f1 is %s\n", f1);
			if (x1 < minX) {minX = x1;}
			if (x1 > maxX) {maxX = x1;}
			if (y1 < minY) {minY = y1;}
			if (y1 > maxY) {maxY = y1;}
			//printf("x1 is %d y1 == %d\n", x1, y1);
			if (ret != 2) {perror("scan\n"); exit(0);}
			if (first == 0) {
				first = 1;
			} else {
				if (x1 == prevX1) {
					if (prevY1 < y1) {ey=y1; sy=prevY1;} else {tmp1 = prevY1; sy = y1; ey = tmp1;}
					int x = x1;
					//printf("x1==prevX1 (%d) prevY1 V y1 %d V %d\n", x1, prevY1, y1);
					for (int y = sy; y <= ey; y++) {
						grid[y][x] = '#';
					}

				} else if (y1 == prevY1) {
					if (prevX1 < x1) {ex=x1; sx=prevX1;} else {tmp1 = prevX1; sx = x1; ex = tmp1;}
					int y = y1;
					//printf("y1==prevY1 (%d) prevX1 V x1 %d V %d\n", y1, prevX1, x1);
					for (int x = sx; x <= ex; x++) {
						grid[y][x] = '#';
					}
				} else {
					//printf("should not be here: ");
					//printf("x1 y1, prevX1, prevY1 %d,%d %d,%d\n", x1, y1, prevX1, prevY1);
				}
			}

		} while((f1 = strtok(NULL, " -\0")) != NULL);
		leny++;

		//461,87 -> 461,80 -> 461,87 -> 463,87 -> 463,80 -> 463,87 -> 465,87 -> 465,80 -> 465,87 -> 467,87 -> 467,86 -> 467,87
	}
	int y = maxY+2; 
	for (int x = minX-5000; x < maxX+5000; x++) {
		grid[y][x] = '#';
	}
	//printf("y is %d\n", y); getchar();
	fclose(a);

	//printf("------------------- %d %d %d %d\n", minX, maxX, minY, maxY); getchar();
	int count = 0;//, prevCount;
	leftOrRight(500, 1);
	//	do {
	//		prevCount = count;
	//		count = 0;
	//		mainX = 500; mainY = 0;
	//		leftOrRight(500, 1);
	//		/*
	//		while (grid[mainY][mainX] == '.') {
	//			mainY++;
	//			printf("here1...\n");
	//			if ((grid[mainY][mainX] == '#' && grid[mainY][mainX-1] == '#' && grid[mainY][mainX+1] == '#') || (grid[mainY][mainX-1] == 'o' && grid[mainY][mainX] == 'o' && grid[mainY][mainX+1] == 'o')) {
	//				grid[mainY-1][mainX] = 'o';
	//			} else if (grid[mainY][mainX] == 'o') {
	//				leftOrRight(mainX, mainY-1);
	//			} else {///drop
	//			}
	//		}
	//		for (int y = 0; y < maxY+3; y++) {
	//			for (int x = minX-2; x < maxX+1; x++) {
	//				if (grid[mainY][mainX] == 'o') {
	//					count++;
	//				}
	//			}
	//		} 
	//		*/
	//		if (prevCount == count && count > 5) {break;}
	//		printit(); printf("count: %d\n", count); getchar();
	//	} while (1);


	printf("**ans: %d\n", count);
}

/*
   .........#.
   ......oo.#.
   .#########.

*/
void justCount() 
{
	var_count = 0;
	for (int y = 0; y < maxY+3; y++) {
		for (int x = minX-4000; x < maxX+4000; x++) {
			if (grid[y][x] == 'o') {
				var_count++;
			}
		}
	} 
	//printit();
	printf("**ans: %d\n", var_count);
	//printf("**var_count is %d\n", var_count);
}

void countit() 
{
	int var_count = 0;
	for (int y = 0; y < maxY+10; y++) {
		for (int x = minX-4500; x < maxX+4500; x++) {
			if (grid[y][x] == 'o') {
				var_count++;
			}
		}
	} 
	//printit();
	printf("**var_count is %d\n", var_count);

}

int ind = 0;
void leftOrRight(int x, int y) { // x,y is o
ag:
	///*printit3(x, y); */justCount(); /*if (var_count < 3000) {} else {getchar();}*/
	if (x > maxX+1000 || x < minX-1000) {printf("outx\n");  countit(); x = 500; y = 0; exit(0);}
	if (y < 0 || y > maxY+10) {printf("outy\n"); countit(); x = 500; y = 0; exit(0);}

	/*
	   0 is o
	   1 is .
	   2 is #
	   000 001 002 
	   010 011 012
	   020 021 022

	   100 101 102
	   110 111 112
	   120 121 122

	   200 201 202
	   210 211 212
	   220 221 222
	   */
	do {
		if (grid[y+1][x] == '.' && grid[y][x] == '.' && y < maxY+4) {
			y++;
		} else {
			break;
		}
	} while (1);
	if (y > maxY+3) { printit(); perror ("out of range"); exit(0);}
	if (grid[0][500] == 'o') {justCount(); exit(0);}
	//assert(grid[y][x] == '.');
	//assert(grid[y+1][x] != '.');
	//printit3(x,y);

	if (check('o', 'o', 'o',&x,&y)) {goto ag;}
	if (check('o', 'o', '.',&x,&y)) {goto ag;}
	if (check('o', 'o', '#',&x,&y)) {goto ag;}

	if (check('o', '#', 'o',&x,&y)) {goto ag;}
	if (check('o', '#', '.',&x,&y)) {goto ag;}
	if (check('o', '#', '#',&x,&y)) {goto ag;}

	if (check('.', 'o', 'o',&x,&y)) {goto ag;}
	if (check('.', 'o', '.',&x,&y)) {goto ag;}
	if (check('.', 'o', '#',&x,&y)) {goto ag;}

	if (check('.', '#', 'o',&x,&y)) {goto ag;}
	if (check('.', '#', '.',&x,&y)) {goto ag;}
	if (check('.', '#', '#',&x,&y)) {goto ag;}

	if (check('#', 'o', 'o',&x,&y)) {goto ag;}
	if (check('#', 'o', '.',&x,&y)) {goto ag;}
	if (check('#', 'o', '#',&x,&y)) {goto ag;}

	if (check('#', '#', 'o',&x,&y)) {goto ag;}
	if (check('#', '#', '.',&x,&y)) {goto ag;}
	if (check('#', '#', '#',&x,&y)) {goto ag;}
	/*
	   check('o', 'o', 'o',&x,&y); check('o', 'o', '.',&x,&y); check('o', 'o', '#',&x,&y);
	   check('o', '#', 'o',&x,&y); check('o', '#', '.',&x,&y); check('o', '#', '#',&x,&y);

	   check('.', 'o', 'o',&x,&y); check('.', 'o', '.',&x,&y); check('.', 'o', '#',&x,&y);
	   check('.', '#', 'o',&x,&y); check('.', '#', '.',&x,&y); check('.', '#', '#',&x,&y);

	   check('#', 'o', 'o',&x,&y); check('#', 'o', '.',&x,&y); check('#', 'o', '#',&x,&y);
	   check('#', '#', 'o',&x,&y); check('#', '#', '.',&x,&y); check('#', '#', '#',&x,&y);
	   */
}

int check(char a, char b, char c, int *x, int *y) {
	if (grid[*y+1][*x-1] == a && grid[*y+1][*x] == b && grid[*y+1][*x+1] == c) {
		if (a == '.' && c == '.') {//reposition left
			*x = *x-1;	
			*y = *y+1;
			return 1;
		} else if (a == '.' && c != '.') {//reposition left
			*x = *x-1;
			*y = *y+1;
			return 1;
		} else if (a != '.' && c == '.') {//go right
			*x = *x+1;
			*y = *y+1;
			return 1;
		} else if (a != '.' && c != '.') {//stay
			grid[*y][*x] = 'o';
			*x = 500;
			*y = 0;
			return 1;
		} else {
			perror("should not be here...\n");
			exit(0);
		}
	}
	return 0;
}


void printit3(int x, int y)
{
	for (int y1 = 0; y1 < y+20; y1++) {
		for (int x1 = x-20; x1 < x+20; x1++) {
			if (x1 == x && y1 == y) {
				printf("X");
			} else {
				printf("%c", grid[y1][x1]);
			}
		}
		printf("\n");
	}

}
void printit2(int sx, int ex, int sy, int ey) {
	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
}
void printit() {
	for (int y = 0; y < maxY+3; y++) {
		for (int x = minX-3; x < maxX+3; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
}

