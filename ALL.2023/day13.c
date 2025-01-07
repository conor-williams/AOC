#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define DAY "2023 Day13 Part1"

void doif(int x1, int x2, int y);
void doifY(int y1, int y2);

int mainX;
int mainY;
char line1[1000];
char line[1000][1000];
int arrayofxes[1000];
long tot = 0;
#undef _DEBUG_ 
int foundmirror;
int newpuzzle;
void printpuzzle(int lines);
int linenum;
int main(int argc, char **argv)
{
	newpuzzle = 0;
	printf("args: %d ", argc); printf("file: %s ", argv[1]); fflush(stdin); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);


	//int breakcontinue = 0;
	while(1) {
		int breakcontinue = 0;
#ifdef _DEBUG_
		printf("---------NEXT LINE----------\n");
#endif
		fgets(line1, 999, a);
#ifdef _DEBUG_
		printf("LINE: %s", line1); fflush(stdout);
#endif

		if (line1[0] == '\n' || feof(a)) {
#ifdef _DEBUG_
			printf("found slash n -- time to process on line %d...",linenum);
#endif
			breakcontinue = 1;
			newpuzzle++;
		} else {
			strcpy(line[linenum], line1);
			line[linenum][(int)strlen(line1)-1] = '\0';
			linenum++;
		}

		foundmirror = 0;
		if (breakcontinue == 1 && linenum > 0) {
			printf("----NEW PUZZLE---%d------\n", newpuzzle);
#ifdef _DEBUG_
			printf("----NEW PUZZLE---%d------\n", newpuzzle);
#endif
			{ // mirror  1
				for (int i = 0; i < (int)strlen(line[0]); i++) {
					arrayofxes[i] = 0;
				}	
				for (int y = 0; y < linenum; y++) {
					for (int x = 0; x < (int)strlen(line[0]); x++) {
						int xpos = x; int ypos = y;
						mainX = x;
						doif(xpos, xpos+1, ypos);
					}
				}

				int maxind = 0;
				for (int i = 0; i < (int)strlen(line[0]); i++) {
					if (arrayofxes[i] > arrayofxes[maxind]) {maxind = i;}
				}	
				if (arrayofxes[maxind] == linenum) {
					printf("mirror X @ maxind: %d...\n", maxind);
#ifdef _DEBUG_
					printf("mirror X @ maxind: %d...\n", maxind);
#endif
					foundmirror = 1;
					tot += maxind + 1;

				}

			}

			if (foundmirror == 0 || foundmirror == 1)
			{ // mirror 2
				for (int y = 0; y < linenum; y++) {
					mainY = y;
					int y1 = y; int y2 = y+1;
					doifY(y1, y2);
				}
			}

			if (foundmirror == 0) {printf("ERROR... no X or Y mirror found: puzzle %d***\n", newpuzzle); getchar(); printpuzzle(linenum); }
			linenum = 0;
		}//breakcontinue
		breakcontinue = 0;
		if (feof(a)) break;
	} //while 
	fclose(a);
	printf("\n****** tot: %ld\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", tot);
}
void printpuzzle(int lines)
{
	for (int i = 0; i < lines; i++) {
		printf("%s\n", line[i]);
	}
}
void doifY(int y1, int y2) {
	if (strcmp(line[y1], line[y2]) == 0) {
		y1--; y2++;
#ifdef _DEBUG_
		printf("*comp**y1 %d y2 %d -- 0, linenum: %d\n", y1, y2, linenum);
#endif
		if (y1 >= 0 && y2 < linenum) {
			doifY(y1, y2);
		} else {
			printf("found Y mirror @ %d\n", mainY);
			foundmirror = 1;
			tot += 100*(mainY + 1);
		}
	} else {
#ifdef _DEBUG_
		printf("%d not the same as  %d\n", y1, y2);
#endif
	}
}

void doif(int x1, int x2, int ypos) {
	if (line[ypos][x1] == line[ypos][x2]) {
		x1--; x2++;
		if (x1 >= 0 && x2 < (int)strlen(line[0])) {
			doif(x1, x2, ypos);
		} else {
			//int myx =  (abs(x2) + abs(x1)) /2);
#ifdef _DEBUG_
			//printf("found mirror all the way @ %d: (y=%d)\n", mainX, ypos); fflush(stdout);
#endif
			arrayofxes[mainX]++;
#ifdef _DEBUG_
			//printf("x1: %d x2: %d\n", x1, x2); fflush(stdout);
#endif
		}
	} else {/*printf("no match %d:[%c] %d:[%c]\n", x1, line[ypos][x1], x2, line[ypos][x2]);*/}
}
