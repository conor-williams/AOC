#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2015 day12 part2\n"
#undef _DEBUG_

int pos=0;
int posSQ=0;
int posL2=0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	//printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[28000];
        char line2[28000];
        char line3[28000];
        char line[200][500];
        char linesSQ[100][500];
        char lines2[400][3000];
	for (int i = 0; i < 199; i++) {
		for (int j = 0; j < 4000; j++) {
			line[i][j] = '_';
			linesSQ[i][j] = '_';
			//lines2[i][j] = '_';
		}
	}
	line[0][0] = '\n';
	line[0][1] = '\0';
	for (int i = 0; i < 28000; i++) {
		line2[i] = ',';
	}
	int lastLine2 = 0;
while(1) {
        fgets(line1, 28000, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	strcpy(line3, line1);
	char curly[100];
	int changed = 0;
restart:
	changed = 0;

	for (int i = 0; i < strlen(line1); i++) {
		if (line1[i] == '\"' && line1[i+1] == 'r' && line1[i+2] == 'e' && line1[i+3] == 'd' && line1[i+4] == '\"') {
			changed = 1;
			line1[i] = ','; line1[i+1] = 'R'; line1[i+2] = 'E'; line1[i+3] = 'D'; line1[i+4] = ',';
			int openSQ = 0; int openCur = 0;
			for (int j = i-1; j >= 0; j--) {
				if (line1[j] == '[') {
					openSQ++;
					if (openSQ == 1) {
						i=i+4;
						goto next;
						int newOpenSQ = 0;
						int linesSQpos = 0;
						for (int k = j; k < strlen(line1); k++) {
							linesSQ[posSQ][linesSQpos++] = line3[k];
							if (line1[k] == ']') {
								newOpenSQ--;
								if (newOpenSQ == 0) {
									i=k;
									linesSQ[posSQ][linesSQpos+1] = '\n';
									linesSQ[posSQ][linesSQpos+2] = '\0';
									posSQ++;
									goto next;
								}
							} else if (line1[k] == '[') {
								newOpenSQ++;
							}
						}
					}
				} else if (line1[j] == ']') {
					openSQ--;
				} else if (line1[j] == '{') {
					openCur++;
					if (openCur == 1) {
						//proceed to next end curly	
						int sq = 0;
						int open = 0;
						int foundSq = 0;
						int linesPos = 0;
						int posL2pos = 0;
						for (int k = j; k < strlen(line1); k++) {
							line[pos][linesPos++] = line3[k];
							//i++;
							if (line1[k] == '}') {
								open--;	
								if (open == 0) {
									line[pos][linesPos+1] = '\n';
									line[pos][linesPos+2] = '\0';
									pos++;
									//printf("%s\n", line[pos]);
									i = k;	
									line1[k] = 'X';
									goto next;
								} 
							} else if (line1[k] == '{') {
								open++;
							} else {
								if (line1[k] == '[') {
									sq++;	
								} else if (line1[k] == ']') {
									foundSq = k;
									sq--;
								}
								if (sq > 0) {
									lines2[posL2][posL2pos++] = line3[k];
									//line2[k] = line3[k];
								} else if (sq == 0 && foundSq != 0) {
									lines2[posL2][posL2pos++] = line3[k];
									lines2[posL2][posL2pos++] = '\n';
									lines2[posL2][posL2pos++] = '\0';
									posL2++;
									posL2pos = 0;
									line2[foundSq] = '\n';
									foundSq = 0;
									lastLine2 = foundSq;
								}
							}
							line1[k] = 'X';
						}
								
					}
				} else if (line1[j] == '}') {
					openCur--;
				}
			}	
		}
next:
		continue;
	}
/*
if (changed == 1) {
	printf("going to restart\n");
	goto restart;
}
*/
	leny++;
}
line2[lastLine2] = '\0';
//printf("%s\n", line1);
//exit(0);
//printf("%s\n", line2);

for (int z = 0; z < pos; z++) {
//	printf("%s", line[z]);
}
printf("************************ *********************************** **************\n");
for (int z = 0; z < posSQ; z++) {
//	printf("%s", linesSQ[z]);
}
printf("************************ *********************************** **************\n");
printf("************************ *********************************** **************\n");
printf("************************ *********************************** **************\n");
//printf("%s\n", line1);
for (int z = 0; z < posL2; z++) {
	for (int i = 0; i < strlen(lines2[z]); i++) {
		if (lines2[z][i] == 'r' && lines2[z][i+1] == 'e' && lines2[z][i+2] == 'd') {
			if (strlen(lines2[z]) < 150) {
				int ind = 0;
				for (int k = 0; k < strlen(lines2[z]); k++) {
					if (lines2[z][k] == '{') {
						ind++;						
						printf("\n");
						for (int n = 0; n < ind; n++) {printf("	"); }
					} else if (lines2[z][k] == '[') {
						ind++;
						printf("\n");
						for (int n = 0; n < ind; n++) {printf("	"); }
					} else if (lines2[z][k] == '}') {
						ind--;
						printf("\n");
						for (int n = 0; n < ind; n++) {printf("	"); }
					} else if (lines2[z][k] == ']') {
						ind--;
						printf("\n");
						for (int n = 0; n < ind; n++) {printf("	"); }
					}
					printf("%c", lines2[z][k]);
				}
				//printf("%s", lines2[z]);
			}
			break;
		}
	}
}
exit(0);
struct braceLevel {
	int level;
	int type;
	int red;
	int part;
};
struct braceLevel bLev[100];
int bLevPos = 0;
	
struct braceLevel levelRed[100];
int levelRedPos = 0;
for (int z = 0; z < posL2; z++) {
	for (int i = 0; i < strlen(lines2[z]); i++) {
		if (lines2[z][i] == 'r' && lines2[z][i+1] == 'e' && lines2[z][i+2] == 'd') {
			if (strlen(lines2[z]) < 150) {
				printf("\n");
				bLevPos = 0; levelRedPos = 0; int level = 0; 
				int part = 0;
				for (int q = 0; q < strlen(lines2[z]); q++) {
					int redFound = 0;
					if (lines2[z][q] == 'r' && lines2[z][q+1] == 'e' && lines2[z][q+2] == 'd') {
						redFound = 1;
						int t = 1;
						for (int m = 0; m < bLevPos; m++) {
							if (bLev[m].level == level) {
								t = bLev[m].type;
							}
						}
						if (t == 1) {
							levelRed[levelRedPos].level = level;
							levelRed[levelRedPos].red = -1;
							levelRed[levelRedPos].part = part;
							levelRedPos++;	
						} else if (t == 2) {
							levelRed[levelRedPos].level = level;
							levelRed[levelRedPos].red = 1;
							levelRed[levelRedPos].part = part;
							levelRedPos++;	
						}
					} else if (lines2[z][q] == '{') {
						level++;
						part++;
						bLev[bLevPos].level = level;
						bLev[bLevPos].type = 1; bLevPos++;
					} else if (lines2[z][q] == '[') {
						level++;
						part++;
						bLev[bLevPos].level = level;
						bLev[bLevPos].type = 2; bLevPos++;
					} else if (lines2[z][q] == '}') {
						level--;
						part++;
						//bLev[bLevPos].level = level;
						//bLev[bLevPos].type = 1; bLevPos++;
						if (redFound == 0) {
						}
					} else if (lines2[z][q] == ']') {
						level--;
						part++;
						if (redFound == 0 && level != 1) {
							//levelRed[levelRedPos].level = level+1;
							//levelRed[levelRedPos].red = -1;
							//levelRed[levelRedPos].part = part-1;
						}
						//bLev[bLevPos].level = level;
						//bLev[bLevPos].type = 2; bLevPos++;
					}
				}
				level = 0;
				part = 0;
				for (int q = 0; q < strlen(lines2[z])-2; q++) {
					if (lines2[z][q] == '{') {
						part++;
						level++;
					} else if (lines2[z][q] == '[') {
						part++;
						level++;
					} else if (lines2[z][q] == '}') {
						part++;
						level--;
					} else if (lines2[z][q] == ']') {
						part++;
						level--;
					}
					for (int i = 0; i < levelRedPos; i++) {
						if (levelRed[i].level == level && levelRed[i].red == 1) {
							printf("%c", lines2[z][q]);
							break;
						} else if (levelRed[i].level == level && levelRed[i].red == -1) {
							printf("%c", 'Z');
							break;
						} else {
							int tmpLev = level;
							int tries = 0;
again:
							tmpLev--;
							tries++;
							int found = 0;
							if (levelRed[i].level == tmpLev && levelRed[i].red == 1) {
								found = 1;
								printf("%c", lines2[z][q]);
								break;
							} else if (levelRed[i].level == tmpLev && levelRed[i].red == -1) {
								found = 1;
								printf("%c", 'Q');
								break;
							}
							if (found == 0 && tries <5) {
								//printf("here1..char [%c] level: %d tmpLev: %d", lines2[z][q], level, tmpLev); getchar();
								goto again;
							}
						}
					}
				}

			}
			break;
		}
	}
}
fclose(a);
}
