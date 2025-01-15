#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <unistd.h>

using namespace std;

#define getchar()

int lenx, leny;
#define DAY "2016 day11 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 1000000
#define getchar()

char grid[5][12][4];
char gridOrig[5][12][4];
int notalltop();
int posX = 0;
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SIZE];
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			for (int i = 0; i < 4; i++) {
				grid[y][x][i] = '0';
			}
		}
	}
	grid[0][posX][0] = 'E'; grid[0][posX][1] = '\0'; posX++;
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	char rest[200];
	char floor[20];

	int ret1 = sscanf(line1, "The %s floor contains %[^\0]", floor, rest);
	
	string fl = floor;
	int fintY;
	if (fl == "first") {
		fintY = 0;
	} else if (fl == "second") {
		fintY = 1;
	} else if (fl == "third") {
		fintY = 2;
	} else if (fl == "fourth") {
		fintY = 3;
	} else {
		printf("ERROR floor. %s..\n", floor);
	}

	if (ret1 == 2) {
		char *first = strtok(rest, " ");
		int count = 0;
		do {
			if (strcmp(first, "a") == 0) {
				//ignore
			} else if (strcmp(first, "nothing") == 0) {
				//ignore
			} else if (strcmp(first, "relevant.") == 0) {
				//ignore
			} else if (strcmp(first, "and") == 0) {
				//ignore
			} else {
				count++;
				//printf("%c", first[0]);	
				if (count % 2 != 0) {grid[fintY][posX][0] = toupper(first[0]); grid[fintY][posX][1] = toupper(first[1]); }
				if (count % 2 == 0) {grid[fintY][posX][2] = toupper(first[0]); grid[fintY][posX][3] = '\0'; posX++;}
			}
		} while ((first = strtok(NULL, " ")) != NULL);
	}
	ret1 = 0; 
	leny++;
}
fclose(a);
	printf("START: \n");
	for (int y = leny-1; y >= 0; y--) {
		printf("F%d: ", y);
		for (int x = 0; x < posX; x++) {
			if (grid[y][x][0] != '0') {
				printf("%s ", grid[y][x]);
			} else {
				printf("    ");
			}
		}
		printf("\n");
	}
	printf("\n");

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			for (int i = 0; i < 4; i++) {
				gridOrig[y][x][i] = grid[y][x][i];
			}
		}
	}

	printf("posX is %d\n", posX); getchar();
	for (int y = 0; y < 4; y++) { for (int x = 0; x < 10; x++) { for (int i = 0; i < 4; i++) { grid[y][x][i] = gridOrig[y][x][i]; } } }
	int tosortE[] = {0, 1, 2, 3}; int IposE = 0; //zero
	int tosortEprev[5];
	int tosort1[] = {0, 1, 2, 3}; int Ipos1 = 1; //one
	int tosort1prev[5];
	int tosort2[] = {0, 1, 2, 3}; int Ipos2 = 1; //one
	int tosort2prev[5];
	int tosort3[] = {0, 1, 2, 3}; int Ipos3 = 2; //two
	int tosort3prev[5];
	int tosort4[] = {0, 1, 2, 3}; int Ipos4 = 3; //three
	int tosort4prev[5];
	tot = 0;
	//do {
		int mycount = 0;
		sort(tosortE, tosortE+4);
		do {
			sort(tosort1, tosort1+4);
			do {
				sort(tosort2, tosort2+4);
				do {
					sort(tosort3, tosort3+4);
					do {
						sort(tosort4, tosort4+4);
						do {
							tot++;
							if (tosortE[3] == tosortEprev[3] && tosortE[2] == tosortEprev[2] && tosortE[1] == tosortEprev[1] && tosortE[0] == tosortEprev[0]) {
								//ignore -- move without lift
							} else if (tosortE[3] == IposE && tosort1[3] == Ipos1 && tosort2[3] == Ipos2 && tosort3[3] == Ipos3 && tosort4[3] == Ipos4) {
								mycount++;
								/*printf("F3: %d %d %d %d %d\n", tosortE[3], tosort1[3], tosort2[3], tosort3[3], tosort4[3]);	
								printf("F2: %d %d %d %d %d\n", tosortE[2], tosort1[2], tosort2[2], tosort3[2], tosort4[2]);	
								printf("F1: %d %d %d %d %d\n", tosortE[1], tosort1[1], tosort2[1], tosort3[1], tosort4[1]);	
								printf("F0: %d %d %d %d %d\n", tosortE[0], tosort1[0], tosort2[0], tosort3[0], tosort4[0]);	
								printf("\n"); 
								*/
							} else {
								char psortE[5] = "    ";
								char psort1[5] = "    ";
								char psort2[5] = "    ";
								char psort3[5] = "    ";
								char psort4[5] = "    ";
								int fE; for (fE = 0; fE < 4; fE++) {
									if (tosortE[fE] == IposE) {psortE[fE] = 'E'; break;} ///ELEVATOR fi
								}
								int fHM; for (fHM = 0; fHM < 4; fHM++) {
									if (tosort1[fHM] == Ipos1) {psort1[fHM] = 'M'; break;} //HM - hydrogen chip
								}
								int fHG; for(fHG = 0; fHG < 4; fHG++) {
									if (tosort3[fHG] == Ipos3) {psort3[fHG] = 'G'; break;} //HG - hydrogen generator
								}
								int fLM; for (fLM = 0; fLM < 4; fLM++) {
									if (tosort2[fLM] == Ipos2) {psort2[fLM] = 'm'; break;} //LM - lithium chip
								}
								int fLG; for (fLG = 0; fLG < 4; fLG++) {
									if (tosort4[fLG] == Ipos4) {psort4[fLG] = 'g'; break;} //LG - lithium generator
								}
								if (fHM == fLG && fHG != fHM && fLM != fLG) {
									goto newElev;
									//ERROR
									//no good 
								} else if (fLM == fHG && fLG != fLM && fHM != fHG) {
									goto newElev;
									//ERROR
								} else if (fE != fLM || fE != fHM) {
									goto newElev;
									//ERROR
								} else {
									printf("F3: %c %c %c %c %c\n", psortE[3], psort1[3], psort2[3], psort3[3], psort4[3]);	
									printf("F2: %c %c %c %c %c\n", psortE[2], psort1[2], psort2[2], psort3[2], psort4[2]);	
									printf("F1: %c %c %c %c %c\n", psortE[1], psort1[1], psort2[1], psort3[1], psort4[1]);	
									printf("F0: %c %c %c %c %c\n", psortE[0], psort1[0], psort2[0], psort3[0], psort4[0]);	
									printf("\n"); 
									getchar();
								}

							}
								
						} while (next_permutation(tosort4, tosort4+4));	
					} while (next_permutation(tosort3, tosort3+4));	
				} while (next_permutation(tosort2, tosort2+4));	
			} while (next_permutation(tosort1, tosort1+4));	
			tosortEprev[3] = tosortE[3]; tosortEprev[2] = tosortE[2]; tosortEprev[1] = tosortE[1]; tosortEprev[0] = tosortE[0];
newElev:
			continue;
		} while (next_permutation(tosortE, tosortE+4));	
		
	//} while (notalltop());

	printf("**mycount is %d\n", mycount);
	printf("***tot %ld END\n", tot); fflush(stdout);
	dup2(fd, 1);
	printf("not working... broken todo\n");
} 
int notalltop() {
	int count = 0;
	for (int y = leny-1; y >= 0; y--) {
		printf("F%d: ", y);
		for (int x = 0; x < posX; x++) {
			if (grid[y][x][0] != '0') {
				count++;
				//printf("%s ", grid[y][x]);
			} else {
				//printf("    ");
			}
		}
		printf("\n");
	}
	printf("\n");
	if (count == posX) {return 1;} else {return 0;}

}
