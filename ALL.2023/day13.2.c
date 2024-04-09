#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define DAY "2023 Day13 Part2"

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
int foldXarrayLen;
int foldXarray[1000];
int foldYarrayLen;
int foldYarray[1000];
int main(int argc, char **argv)
{
	newpuzzle = 0;
        printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);
       

int breakcontinue = 0;
while(1) {
	breakcontinue = 0;
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
		line[linenum][strlen(line1)-1] = '\0';
		linenum++;
	}

if (breakcontinue == 1 && linenum > 0) {
foundmirror = 0;
	printf("----NEW PUZZLE---%d------\n", newpuzzle);
foldXarrayLen = 0;
foldYarrayLen = 0;
for (int i = 0; i< 900; i++) {foldXarray[i] = -1;}
for (int i = 0; i< 900; i++) {foldYarray[i] = -1;}

for (int rYejig = 0; rYejig < linenum ; rYejig++) {
for (int rejigX = 0; rejigX < strlen(line[0]); rejigX++) {
	char prevChar = line[rYejig][rejigX];
	if (prevChar == '.') {line[rYejig][rejigX] = '#';}
	else {line[rYejig][rejigX] = '.';}

printf("flipping y:%d x:%d was %c after %c\n", rYejig, rejigX, prevChar, line[rYejig][rejigX]);
printf("LIN^^^: %s\n", line[rYejig]);

	printf("----NEW PUZZLE---%d------\n", newpuzzle);
{ // mirror  1
            for (int i = 0; i < strlen(line[0]); i++) {
		arrayofxes[i] = 0;
	    }	
  	    for (int y = 0; y < linenum; y++) {
	  	    for (int x = 0; x < strlen(line[0]); x++) {
			int xpos = x; int ypos = y;
			mainX = x;
			doif(xpos, xpos+1, ypos);
	            }
	    }

	    int maxind = -1;
	    int maxind2 = -1;

            for (int i = 0; i < strlen(line[0]); i++) {
		if (arrayofxes[i] > arrayofxes[maxind]) {maxind = i;} 
	    }	
	    for (int i = 0; i < strlen(line[0]); i++) {
if (i != maxind) {
		if (arrayofxes[maxind] == arrayofxes[i]) {
			maxind2 = i; /*second mirror*/
//			printf("SECOND index %d....\n", maxind2); getchar();
		}
}
	    }

	    if (arrayofxes[maxind2] == linenum) {
		    printf("mirror X @ maxind2: %d...\n", maxind2);
#ifdef _DEBUG_
		    printf("mirror X @ maxind2: %d...\n", maxind2);
#endif
		    foundmirror = 1;

			int there = 0;
	            for (int k = 0; k < foldXarrayLen; k++) {
//			printf("%d LEN foldXarrayLen %d\n", k, foldXarrayLen); fflush(stdout);
			if (maxind2 == foldXarray[k]) {
				there = 1;
			}
		    }
			if (there == 0 || foldXarrayLen == 0) {
//			    printf("**adding mirror X @ maxind2: %d...\n", maxind2); fflush(stdout);
			    foldXarray[foldXarrayLen] = maxind2;
			    foldXarrayLen++;	
			}
//		    tot += maxind + 1;

	    }
	    if (arrayofxes[maxind] == linenum) {
		    printf("mirror X @ maxind: %d...\n", maxind);
#ifdef _DEBUG_
		    printf("mirror X @ maxind: %d...\n", maxind);
#endif
		    foundmirror = 1;

			int there = 0;
	            for (int k = 0; k < foldXarrayLen; k++) {
//			printf("%d LEN foldXarrayLen %d\n", k, foldXarrayLen); fflush(stdout);
			if (maxind == foldXarray[k]) {
				there = 1;
			}
		    }
			if (there == 0 || foldXarrayLen == 0) {
//			    printf("**adding mirror X @ maxind: %d...\n", maxind); fflush(stdout);
			    foldXarray[foldXarrayLen] = maxind;
			    foldXarrayLen++;	
			}
//		    tot += maxind + 1;

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

if (foundmirror == 0) {printf("ERROR... no X or Y mirror found: puzzle %d***\n", newpuzzle); /*printpuzzle(linenum);*/ }

	line[rYejig][rejigX] = prevChar;
}}
linenum = 0;
breakcontinue = 0;
int modit = 0;
if (foldXarrayLen + foldYarrayLen == 2) {
} else {modit = 1;printf("oh dear not 2...getchar\n"); getchar();}
for (int k = 0; k < foldXarrayLen; k++) {
	printf("adding from foldXarray %d to tot once...\n", foldXarray[k]);
	tot += foldXarray[k] + 1;
	
}
for (int k = 0; k < foldYarrayLen; k++) {
	printf("adding from fold Y array %d to tot once...\n", foldYarray[k]);
	tot += 100*(foldYarray[k] + 1);
}
}//breakcontinue
if (feof(a)) break;
} //while 
	fclose(a);
	printf("\n****** tot: %ld\n", tot);

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
			//printf("found Y mirror @ %d\n", mainY);
			foundmirror = 1;
			int existsP = 0;
		   	for (int k = 0; k < foldYarrayLen; k++) {
		    	       if (foldYarray[k] == mainY) {
				   existsP = 1;
				}
			}
			if (existsP != 1 || foldYarrayLen == 0) {
			 	   //printf("***adding found Y mirror @ %d\n", mainY);
				   foldYarray[foldYarrayLen] = mainY;
			    	   foldYarrayLen++;
			 }

		}

	//		tot += 100*(mainY + 1);
	} else {
#ifdef _DEBUG_
		printf("%d not the same as  %d\n", y1, y2);
#endif
	}
}

void doif(int x1, int x2, int ypos) {
	if (line[ypos][x1] == line[ypos][x2]) {
		x1--; x2++;
		if (x1 >= 0 && x2 < strlen(line[0])) {
			doif(x1, x2, ypos);
		} else {
//			printf("found mirror all the way @ %d: (y=%d)\n", mainX, ypos); fflush(stdout);
#ifdef _DEBUG_
			//printf("found mirror all the way @ %d: (y=%d)\n", mainX, ypos); fflush(stdout);
#endif
			arrayofxes[mainX]++;
#ifdef _DEBUG_
			//printf("x1: %d x2: %d\n", x1, x2); fflush(stdout);
#endif
	        }
	} else {
/*printf("no match %d:[%c] %d:[%c]\n", x1, line[ypos][x1], x2, line[ypos][x2]);*/
	}
}
