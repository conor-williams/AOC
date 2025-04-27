#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define DAY "		2023 Day13 Part2"

void doif(int x1, int x2, int y);
int doifY(int y1, int y2);

int mainX;
int mainY;
char line1[1000];
char line[1000][1000];
char lineOrig[1000][1000];
int arrayofxes[1000];
long tot = 0;
#undef _DEBUG_ 
#define getchar()
int foundmirror;
int newpuzzle;
void printpuzzle(int lines);
int linenum;
int puz1tot = 0;
int conorAnsX = 0;
int countY = 0;
int countX = 0;
int fd;
int main(int argc, char **argv)
{
	newpuzzle = 0;
	//printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdout);
	fd = dup(1); close(1);

	int breakcontinue = 0;
	int ansans = 0;
	while(1) {
#ifdef _DEBUG_
		printf("---------NEXT LINE----------\n");
#endif
		fgets(line1, 999, a);
		printf("LINE: %s", line1); fflush(stdout);
#ifdef _DEBUG_
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

		foundmirror = 0;


		if (breakcontinue == 1 && linenum > 0) {
			int foundit = 0;
			int ansOrig = -1;
			int ansNew = -1;
			//int singletot = 0;
			foundmirror = 0;
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
					//tot += maxind + 1;
					ansOrig = (maxind+1);
					puz1tot += maxind+1;
					printf("ansOrig is %d\n", ansOrig);
					getchar();
					goto next;
				}
			}

			if (foundmirror == 0) { // mirror 2
				printf("here2...\n");getchar();
				for (int y = 0; y < linenum; y++) {
					mainY = y;
					int y1 = y; int y2 = y+1;
					int bla = doifY(y1, y2);
					printf("bla is %d\n", bla);
					if (bla >= 0) {ansOrig=(mainY+1)*100; puz1tot+=(mainY+1)*100; printf("***blah(ansOrig) is %d\n", ansOrig); getchar(); goto next;}
				}
			}
next:	
			for (int qqq = 0; qqq < linenum; qqq++) {
				strcpy(lineOrig[qqq], line[qqq]);
			}
			for (int xx = 0; xx < (int)strlen(line[0]); xx++) {
				for (int yy = 0; yy < linenum; yy++) {
					//printf("here1.. %d %d..\n", xx, yy);
					for (int qq = 0; qq < linenum; qq++) {
						strcpy(line[qq], lineOrig[qq]);
					}

					if (line[yy][xx] == '.') {
						line[yy][xx] = '#';
					} else {
						line[yy][xx] = '.';
					}
					printf("changing %d,%d\n", xx, yy);
					printf("----NEW PUZZLE---%d------\n", newpuzzle);
#ifdef _DEBUG_
					printf("----NEW PUZZLE---%d------\n", newpuzzle);
#endif
					foundmirror = 0;

					{ // mirror  1
						//if (ansOrig == 0) {st = 1;}
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

						int maxind = (int)strlen(line[0])-1;
						for (int i = 0; i < (int)strlen(line[0]); i++) {
							if (arrayofxes[i] > arrayofxes[maxind] && i != ansOrig-1) {maxind = i;}
						}	
						/*
						for (int i = 0; i < (int)strlen(line[0]); i++) {
							if (arrayofxes[i] == arrayofxes[maxind]) {ve.insert(i);}
						}
						*/
						if (arrayofxes[maxind] == linenum) {
							printf("mirror X @ maxind: %d...\n", maxind);
#ifdef _DEBUG_
							printf("mirror X @ maxind: %d...\n", maxind);
#endif
							ansNew = maxind+1;
							printf("*ansNew is %d\n", ansNew);
							if (ansOrig != ansNew) {
								printf("adding to tot\n");
								tot += (maxind + 1);
								foundit = 1;
								foundmirror = 1;
								countX++;
								goto aft;
							} else {
								printf("ansNew same as ansOrig... trying YY\n");
								foundmirror = 0;
								//goto agag55;
							}

						}

					}

agag55:
					if (foundmirror == 0) { // mirror 2
						//printf("in check2...\n"); getchar();
						for (int y = 0; y < linenum; y++) {
							mainY = y;
							int y1 = y; int y2 = y+1;
							int bla = doifY(y1, y2);
							if (bla >= 0) {
								printf("found a Y mirror %d\n", bla);
								getchar();
							}

							if (bla >= 0) {
								printf("bla > 0...\n");
								ansNew = (mainY+1)*100;
								printf("ansOrig V ansNew %d V %d\n", ansNew, ansOrig);

								if (ansOrig != ansNew) {
									countY++;
									foundit = 2;
									printf("ansnew != ansOrig\n");
									for (int yy = 0; yy < linenum; yy++) {
										printf("XX: %s \n", line[yy]);
									}

									tot+=ansNew;
									goto aft;
								} else {
									printf("ansOrig same as ansNew\n");
									//goto con;
								}
							} else {
								//goto con;
							}
						}
					}

					//linenum = 0;
					printf("continueP\n");
				}
			}

aft:
			linenum = 0;
			breakcontinue = 0;

			if (foundit == 0) {ansans+=ansOrig; printf("not found.... ansans+=ansOrig %d\n", ansans);}
		}

		if (feof(a)) break;
	} //while 
	fclose(a);
	printf("**puz1tot is %d\n", puz1tot);
	printf("\n****** tot: %ld\n", tot);
	printf("\n****** tot+74: %ld\n", tot+74);
	printf("should be p1: %d V p2: %d\n", 34821, 36919);
	printf("countY %d V %d countX\n", countY, countX);
	printf("ansans %d\n", ansans);
	fflush(stdout); dup2(fd, 1); 
	//printf("**puz1tot is %d\n", puz1tot);
	printf("**ans: %ld\n", tot);
}
void printpuzzle(int lines)
{
	for (int i = 0; i < lines; i++) {
		printf("%s\n", line[i]);
	}
}
int doifY(int y1, int y2) {
	if (strcmp(line[y1], line[y2]) == 0) {
		y1--; y2++;
#ifdef _DEBUG_
		printf("*comp**y1 %d y2 %d -- 0, linenum: %d\n", y1, y2, linenum);
#endif
		if (y1 >= 0 && y2 < linenum) {
			return doifY(y1, y2);
		} else {
			printf("**found Y mirror @ %d\n", mainY); getchar();
			//ansans = linenum;
			foundmirror = 1;
			//tot += 100*(mainY + 1);
			printf("returning 100*(mainY+1) %d\n", 100*(mainY+1));
			return (100*(mainY+1));
		}
	} else {
#ifdef _DEBUG_
		printf("%d not the same as  %d\n", y1, y2);
#endif
	}
	return -1;
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
			conorAnsX = mainX;
			arrayofxes[mainX]++;
#ifdef _DEBUG_
			//printf("x1: %d x2: %d\n", x1, x2); fflush(stdout);
#endif
		}
	} else {/*printf("no match %d:[%c] %d:[%c]\n", x1, line[ypos][x1], x2, line[ypos][x2]);*/}
}






					//if (foundmirror == 0) {printf("ERROR... no X or Y mirror found: puzzle %d***\n", newpuzzle); getchar(); printpuzzle(linenum); }
