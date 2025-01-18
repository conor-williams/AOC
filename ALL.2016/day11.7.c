#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <unistd.h>

using namespace std;
int ind = 1;

int CHECK = 200;
int lenx, leny;
#define DAY "2016 day11 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 1000
//#define getchar()

char grid[5][12][4];
int posX = 0;
void makemove(int ar[], long steps, int first);
int cpoint();
void restore(int ps);
int tosort1[4];
int tosort2[4];
int tosort3[4];
int tosort4[4];
int tosort5[4];
int tosort6[4];
int tosort7[4];
int tosort8[4];
int tosort9[4];
int tosorta[4];
#define MAXCPOINT 10000
struct mygrid_s {
	int mygridA[4][10];
	int qs[4];
	int tmpsort[4];
};
struct mygrid_s mygrid[MAXCPOINT];
int cpp = 0;
int maxc = 0;
void printit(int asd[], int steps, int ind);

long minSteps = 999999;
void sig_handler(int signum){
        printf("CONOR ctrl-z minSteps is:::: %ld\n", minSteps); getchar();
}

int main(int argc, char **argv)
{
	//int fd = dup(1); close(1);
         signal(SIGTSTP, sig_handler);

	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	if (argc > 2) {CHECK = atoi(argv[2]);}
	printf("CHECK is %d\n", CHECK); getchar();
	char line1[SIZE];
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			for (int i = 0; i < 4; i++) {
				grid[y][x][i] = '0';
			}
		}
	}
	for (int j = 0; j < MAXCPOINT; j++) {
		for (int fl = 0; fl < 4; fl++) {
			for (int i = 0; i < 10; i++) {
				mygrid[j].mygridA[fl][i] = 0;
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

getchar();
	tosort1[0] = 1; tosort1[1] = 0; tosort1[2] = 0; tosort1[3] = 0;
	tosort2[0] = 1; tosort2[1] = 0; tosort2[2] = 0; tosort2[3] = 0;
	tosort3[0] = 1; tosort3[1] = 0; tosort3[2] = 0; tosort3[3] = 0;
	tosort4[0] = 1; tosort4[1] = 0; tosort4[2] = 0; tosort4[3] = 0;
	tosort5[0] = 0; tosort5[1] = 1; tosort5[2] = 0; tosort5[3] = 0;
	tosort6[0] = 0; tosort6[1] = 1; tosort6[2] = 0; tosort6[3] = 0;
	tosort7[0] = 0; tosort7[1] = 0; tosort7[2] = 1; tosort7[3] = 0;
	tosort8[0] = 0; tosort8[1] = 0; tosort8[2] = 1; tosort8[3] = 0;
	tosort9[0] = 0; tosort9[1] = 0; tosort9[2] = 1; tosort9[3] = 0;
	tosorta[0] = 0; tosorta[1] = 0; tosorta[2] = 1; tosorta[3] = 0;
	
	int myqs[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	makemove(myqs, 0, 1);
	tot = 0;

	//fflush(stdout); dup2(fd, 1);
	printf("minSteps: [%ld] END\n", minSteps);
	printf("maxc: [%d] END\n", maxc);
} 
/*
START:
F3:
F2:                             PRG *PRM RUG *RUM
F1:                     *PLM *STM
F0: E THG *THM PLG STG
*/


int docheck() {
	int THG; for (THG = 0; THG < 4; THG++) {
		if (tosort1[THG] == 1) {break;} //HM - hydrogen chip
	}
	int THM; for(THM = 0; THM < 4; THM++) {
		if (tosort2[THM] == 1) {break;} //HG - hydrogen generator
	}
	int PLG; for (PLG = 0; PLG < 4; PLG++) {
		if (tosort3[PLG] == 1) {break;} //LM - lithium chip
	}
	int STG; for (STG = 0; STG < 4; STG++) {
		if (tosort4[STG] == 1) {break;} //LG - lithium generator
	}
	int PLM; for (PLM = 0; PLM < 4; PLM++) {
		if (tosort5[PLM] == 1) {break;} //LG - lithium generator
	}
	int STM; for (STM = 0; STM < 4; STM++) {
		if (tosort6[STM] == 1) {break;} //LG - lithium generator
	}
	int PRG; for (PRG = 0; PRG < 4; PRG++) {
		if (tosort7[PRG] == 1) {break;} //LG - lithium generator
	}
	int PRM; for (PRM = 0; PRM < 4; PRM++) {
		if (tosort8[PRM] == 1) {break;} //LG - lithium generator
	}
	int RUG; for (RUG = 0; RUG < 4; RUG++) {
		if (tosort9[RUG] == 1) {break;} //LG - lithium generator
	}
	int RUM; for (RUM = 0; RUM < 4; RUM++) {
		if (tosorta[RUM] == 1) {break;} //LG - lithium generator
	}
/*
START:
F3:
F2:                             PRG *PRM RUG *RUM
F1:                     *PLM *STM
F0: E THG *THM PLG STG
*/
	struct both_s {
		int M;
		int G;
	};
	struct both_s both[5];
	both[0].M = THM;
	both[0].G = THG;
	both[1].M = PLM;
	both[1].G = PLG;
	both[2].M = STM;
	both[2].G = STG;
	both[3].M = PRM;
	both[3].G = PRG;
	both[4].M = RUM;
	both[4].G = RUG;

	int pos = 0;
	struct both_s lookat[5];

	for (int it = 0; it < 5; it++) {
		if (both[it].M == both[it].G) {
			//ok
		} else {
			lookat[pos++] = both[it];
		}
	}
	
	for (int it = 0; it < pos-1; it++) {
		for (int it2 = it+1; it2 < pos; it2++) {
			if (lookat[it].G == lookat[it2].M) {
				//chips blown
				return 0;
			}
		}
	}
			
	return 1;

}
int count123 = 0;
void makemove(int myqs[], long steps, int first) {
	ind++;

	if (steps >= minSteps) {ind--; return;}
	
	if (steps >= CHECK) {ind--; return;}
	if (first != 1) { }
	int mainPos = cpoint();
	int qs[10];
	for (int end = 1; end <= 2; end++) {
		for (int o = 0; o < end; o++) {
			qs[o] = 1;
		}
		for (int z = end; z < 10; z++) {
			qs[z] = 0;
		}
		sort(qs, qs+10);
		int found2tot = 0;
		for (int i = 0; i < 10; i++) { if (myqs[i] == 1) { found2tot++; } }
		do {
			if (docheck() == 0) {ind--; return;}
			int found2 = 0; 
			for (int i = 0; i < 10; i++) { if (qs[i] == myqs[i] && qs[i] == 1) { found2++; } } if (found2 >= 1) { continue; }

			if (first == 1) {
				if (qs[0] == 1 || qs[1] == 1 || qs[2] == 1 || qs[3] == 1) {/*ok*/} else {continue;}
			}
			if (qs[1] == 1 || qs[4] == 1 || qs[5] == 1 || qs[7] == 1 || qs[9] == 1) {} else {/*printf("skip1\n");*/ printit(qs, steps, ind); continue;}

			int tmpsortOrig[] = {0, 0, 0, 1};
			int tmpsort[] = {0, 0, 0, 1};

			int num1 = -1; int num2 = -1;
			if (qs[0] == 1 && qs[1] ==1) {
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort1[i] == tosort2[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					num1 = 0;
					num2 = 1;
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort1[i];
						tmpsortOrig[i] = tosort1[i];
					}
				} else {continue;}
			} else if (qs[0] == 1 && qs[2] ==1) {
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort1[i] == tosort3[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					num1 = 0;
					num2 = 2;
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort1[i];
						tmpsortOrig[i] = tosort1[i];
					}
				} else {continue;}
			} else if (qs[0] == 1 && qs[3] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosort4[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 3; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}
			} else if (qs[0] == 1 && qs[4] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosort5[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 4; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}
			} else if (qs[0] == 1 && qs[5] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosort6[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 5; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}
			} else if (qs[0] == 1 && qs[6] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosort7[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 6; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}
			} else if (qs[0] == 1 && qs[7] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosort8[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}
			} else if (qs[0] == 1 && qs[8] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosort9[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}
			} else if (qs[0] == 1 && qs[9] ==1) {
				int found = 0; for (int i = 0; i < 4; i++) { if (tosort1[i] == tosorta[i]) { found++; } }
				if (found == 4) {num1 = 0; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i]; }
				} else {continue;}

			} else if (qs[1] == 1 && qs[2] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort3[i]) { found++; } } 
				if (found == 4) {num1 = 1; num2 = 2; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[3] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort4[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 3; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[4] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort5[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 4; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[5] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort6[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 5; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[6] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort7[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 6; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[7] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort8[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosort9[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}
			} else if (qs[1] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort2[i] == tosorta[i]) { found++; } }
				if (found == 4) {num1 = 1; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i]; }
				} else {continue;}

			} else if (qs[2] == 1 && qs[3] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosort4[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 3; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}
			} else if (qs[2] == 1 && qs[4] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosort5[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 4; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}
			} else if (qs[2] == 1 && qs[5] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosort6[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 5; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}
			} else if (qs[2] == 1 && qs[6] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosort7[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 6; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}
			} else if (qs[2] == 1 && qs[7] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosort8[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}
			} else if (qs[2] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosort9[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}
			} else if (qs[2] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort3[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 2; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i]; }
				} else {continue;}

			} else if (qs[3] == 1 && qs[4] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort4[i] == tosort5[i]) { found++; } }
				if (found == 4) { num1 = 3; num2 = 4; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i]; }
				} else {continue;}
			} else if (qs[3] == 1 && qs[5] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort4[i] == tosort6[i]) { found++; } }
				if (found == 4) { num1 = 3; num2 = 5; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i]; }
				} else {continue;}
			} else if (qs[3] == 1 && qs[6] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort4[i] == tosort7[i]) { found++; } }
				if (found == 4) { num1 = 3; num2 = 6; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i]; }
				} else {continue;}
			} else if (qs[3] == 1 && qs[7] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort4[i] == tosort8[i]) { found++; } }
				if (found == 4) { num1 = 3; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i]; }
				} else {continue;}
			} else if (qs[3] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort4[i] == tosort9[i]) { found++; } }
				if (found == 4) { num1 = 3; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i]; }
				} else {continue;}
			} else if (qs[3] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort4[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 3; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i]; }
				} else {continue;}

			} else if (qs[4] == 1 && qs[5] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort5[i] == tosort6[i]) { found++; } }
				if (found == 4) { num1 = 4; num2 = 5; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort5[i]; tmpsortOrig[i] = tosort5[i]; }
				} else {continue;}
			} else if (qs[4] == 1 && qs[6] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort5[i] == tosort7[i]) { found++; } }
				if (found == 4) { num1 = 4; num2 = 6; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort5[i]; tmpsortOrig[i] = tosort5[i]; }
				} else {continue;}
			} else if (qs[4] == 1 && qs[7] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort5[i] == tosort8[i]) { found++; } }
				if (found == 4) { num1 = 4; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort5[i]; tmpsortOrig[i] = tosort5[i]; }
				} else {continue;}
			} else if (qs[4] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort5[i] == tosort9[i]) { found++; } }
				if (found == 4) { num1 = 4; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort5[i]; tmpsortOrig[i] = tosort5[i]; }
				} else {continue;}
			} else if (qs[4] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort5[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 4; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort5[i]; tmpsortOrig[i] = tosort5[i]; }
				} else {continue;}

			} else if (qs[5] == 1 && qs[6] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort6[i] == tosort7[i]) { found++; } }
				if (found == 4) { num1 = 5; num2 = 6; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort6[i]; tmpsortOrig[i] = tosort6[i]; }
				} else {continue;}
			} else if (qs[5] == 1 && qs[7] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort6[i] == tosort8[i]) { found++; } }
				if (found == 4) { num1 = 5; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort6[i]; tmpsortOrig[i] = tosort6[i]; }
				} else {continue;}
			} else if (qs[5] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort6[i] == tosort9[i]) { found++; } }
				if (found == 4) { num1 = 5; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort6[i]; tmpsortOrig[i] = tosort6[i]; }
				} else {continue;}
			} else if (qs[5] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort6[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 5; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort6[i]; tmpsortOrig[i] = tosort6[i]; }
				} else {continue;}

			} else if (qs[6] == 1 && qs[7] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort7[i] == tosort8[i]) { found++; } }
				if (found == 4) { num1 = 6; num2 = 7; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort7[i]; tmpsortOrig[i] = tosort7[i]; }
				} else {continue;}
			} else if (qs[6] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort7[i] == tosort9[i]) { found++; } }
				if (found == 4) { num1 = 6; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort7[i]; tmpsortOrig[i] = tosort7[i]; }
				} else {continue;}
			} else if (qs[6] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort9[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 6; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort7[i]; tmpsortOrig[i] = tosort7[i]; }
				} else {continue;}

			} else if (qs[7] == 1 && qs[8] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort8[i] == tosort9[i]) { found++; } }
				if (found == 4) { num1 = 7; num2 = 8; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort8[i]; tmpsortOrig[i] = tosort8[i]; }
				} else {continue;}
			} else if (qs[7] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort8[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 7; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort8[i]; tmpsortOrig[i] = tosort8[i]; }
				} else {continue;}

			} else if (qs[8] == 1 && qs[9] ==1) { int found = 0; for (int i = 0; i < 4; i++) { if (tosort9[i] == tosorta[i]) { found++; } }
				if (found == 4) { num1 = 8; num2 = 9; for (int i = 0; i < 4; i++) { tmpsort[i] = tosort9[i]; tmpsortOrig[i] = tosort9[i]; }
				} else {continue;}

			} else if (qs[0] == 1) { num1 = 0; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i];}
			} else if (qs[1] == 1) { num1 = 1; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i];}
			} else if (qs[2] == 1) { num1 = 2; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i];}
			} else if (qs[3] == 1) { num1 = 3; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i];}
			} else if (qs[4] == 1) { num1 = 4; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort5[i]; tmpsortOrig[i] = tosort5[i];}
			} else if (qs[5] == 1) { num1 = 5; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort6[i]; tmpsortOrig[i] = tosort6[i];}
			} else if (qs[6] == 1) { num1 = 6; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort7[i]; tmpsortOrig[i] = tosort7[i];}
			} else if (qs[7] == 1) { num1 = 7; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort8[i]; tmpsortOrig[i] = tosort8[i];}
			} else if (qs[8] == 1) { num1 = 8; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort9[i]; tmpsortOrig[i] = tosort9[i];}
			} else if (qs[9] == 1) { num1 = 9; for (int i = 0; i < 4; i++) {tmpsort[i] = tosorta[i]; tmpsortOrig[i] = tosorta[i];} }

			int tmpsortVo[4];
			int posVo = 0;
			int posTs;
			for (int i = 0 ; i < 4; i++) {
				tmpsortVo[i] = tmpsort[i];
				if (tmpsort[i] == 1) {posVo = i;}
				
			}
			sort(tmpsort, tmpsort+4);
			int changed = 0;
			int found55 = 0;
			for (int i = 0; i < 10; i++) {
				if (tmpsortOrig[i] == tmpsort[i]) {
					found55++;
				}
			}
			if (found55 == 10) {} else {changed = 1;}
			
			do {
				for (int i = 0; i < 4; i++) {
					if (tmpsort[i] == 1) {
						posTs = i; break;	
					}
				}
				int dist = abs(posTs - posVo);
				if (dist == 0) {continue;}
				if (num1 == 0) {
					for (int i = 0; i < 4; i++) {
						tosort1[i] = tmpsort[i];
					}
				} else if (num1 == 1) {
					for (int i = 0; i < 4; i++) {
						tosort2[i] = tmpsort[i];
					}
				} else if (num1 == 2) {
					for (int i = 0; i < 4; i++) {
						tosort3[i] = tmpsort[i];
					}
				} else if (num1 == 3) { for (int i = 0; i < 4; i++) { tosort4[i] = tmpsort[i]; }
				} else if (num1 == 4) { for (int i = 0; i < 4; i++) { tosort5[i] = tmpsort[i]; }
				} else if (num1 == 5) { for (int i = 0; i < 4; i++) { tosort6[i] = tmpsort[i]; }
				} else if (num1 == 6) { for (int i = 0; i < 4; i++) { tosort7[i] = tmpsort[i]; }
				} else if (num1 == 7) { for (int i = 0; i < 4; i++) { tosort8[i] = tmpsort[i]; }
				} else if (num1 == 8) { for (int i = 0; i < 4; i++) { tosort9[i] = tmpsort[i]; }
				} else if (num1 == 9) { for (int i = 0; i < 4; i++) { tosorta[i] = tmpsort[i]; } }

				if (num2 == -1) {
					//nothing
				} else if (num2 == 0) {
					for (int i = 0; i < 4; i++) {
						tosort1[i] = tmpsort[i];
					}
				} else if (num2 == 1) {
					for (int i = 0; i < 4; i++) {
						tosort2[i] = tmpsort[i];
					}
				} else if (num2 == 2) {
					for (int i = 0; i < 4; i++) {
						tosort3[i] = tmpsort[i];
					}
				} else if (num2 == 3) { for (int i = 0; i < 4; i++) { tosort4[i] = tmpsort[i]; }
				} else if (num2 == 4) { for (int i = 0; i < 4; i++) { tosort5[i] = tmpsort[i]; }
				} else if (num2 == 5) { for (int i = 0; i < 4; i++) { tosort6[i] = tmpsort[i]; }
				} else if (num2 == 6) { for (int i = 0; i < 4; i++) { tosort7[i] = tmpsort[i]; }
				} else if (num2 == 7) { for (int i = 0; i < 4; i++) { tosort8[i] = tmpsort[i]; }
				} else if (num2 == 8) { for (int i = 0; i < 4; i++) { tosort9[i] = tmpsort[i]; }
				} else if (num2 == 9) { for (int i = 0; i < 4; i++) { tosorta[i] = tmpsort[i]; } }

				int found4 = 0;
				for (int i = 0; i < 10; i++) {
					if (tmpsort[i] == tmpsortOrig[i]) {
						found4++;
					}
				}
				if (found4 == 10) {
					continue;
				}
				printit(qs, steps, ind);
				if (tosort1[3] == 1 && tosort2[3] == 1 && tosort3[3] == 1 && tosort4[3] == 1 && tosort5[3] == 1 && tosort6[3] == 1 && tosort7[3] == 1 && tosort8[3] == 1 && tosort9[3] == 1 && tosorta[3] == 1) {
					if (steps < minSteps) {minSteps = steps;}
					printit(qs, steps, ind);
					printf("END reached.^^.. %ld %ld ------ret-----\n", steps, minSteps); ind--; return;
				} else {
					int found10 = 0;
					for (int j = 0; j < cpp; j++) {
						int found11 = 0;
						for (int fl = 0; fl < 4; fl++) {
							for (int i = 0; i < 10; i++) {
								if (i == 0) {
									if (mygrid[j].mygridA[fl][i] == tosort1[fl]) {
										found11++;
									}
								} else if (i == 1) {
									if (mygrid[j].mygridA[fl][i] == tosort2[fl]) {
										found11++;
									}
								} else if (i == 2) {
									if (mygrid[j].mygridA[fl][i] == tosort3[fl]) {
										found11++;
									}
								} else if (i == 3) { if (mygrid[j].mygridA[fl][i] == tosort4[fl]) { found11++; }
								} else if (i == 4) { if (mygrid[j].mygridA[fl][i] == tosort5[fl]) { found11++; }
								} else if (i == 5) { if (mygrid[j].mygridA[fl][i] == tosort6[fl]) { found11++; }
								} else if (i == 6) { if (mygrid[j].mygridA[fl][i] == tosort7[fl]) { found11++; }
								} else if (i == 7) { if (mygrid[j].mygridA[fl][i] == tosort8[fl]) { found11++; }
								} else if (i == 8) { if (mygrid[j].mygridA[fl][i] == tosort9[fl]) { found11++; }
								} else if (i == 9) { if (mygrid[j].mygridA[fl][i] == tosorta[fl]) { found11++; } }
							}
						}
						if (found11 == 4*10) {
							found10 = 1;
							break;
						}
					}
					if (found10 == 1) {
						continue;
					} else {	
						//printf("calling makemove with steps: %ld\n", steps+1);
						makemove(qs, steps+dist, 2);
/*
						if (changed == 1) {
							makemove(qs, steps+dist, 2);
						} else {
							makemove(qs, steps+dist, 2);
						}
*/
						restore(mainPos-1);
					}
				}
			} while (next_permutation(tmpsort, tmpsort+4));
		} while (next_permutation(qs, qs+10));

	}
}
void printit(int qs[], int steps, int ind) {
	return;
	printf("------------------VVVVV VVVV------------\n");
	for (int fl = 3; fl >=0; fl--) { for (int i = 0; i < 10; i++) { if (i == 0) { printf("%d ", tosort1[fl]); } else if (i == 1) { printf("%d ", tosort2[fl]); } else if (i == 2) { printf("%d ", tosort3[fl]); } 
	else if (i == 3) { printf("%d ", tosort4[fl]); }  
	else if (i == 4) { printf("%d ", tosort5[fl]); }  
	else if (i == 5) { printf("%d ", tosort6[fl]); }  
	else if (i == 6) { printf("%d ", tosort7[fl]); }  
	else if (i == 7) { printf("%d ", tosort8[fl]); }  
	else if (i == 8) { printf("%d ", tosort9[fl]); }  
	else if (i == 9) { printf("%d ", tosorta[fl]); } } 


printf("\n"); } printf("\n");

	printf("Q: ");
	for (int i = 0; i < 10; i++) {
		printf("%d ", qs[i]);
	} 
	printf("\n");	
	printf("steps: %d\n", steps);
	printf("ind: %d\n", ind);
	printf("------------------^^^^^^^^^^^^^^^------------\n");
}
void restore(int ps) {
	if (ps < 0) {printf("ERROR ps less than zero in restore\n"); exit(0);}
	if (ps+1 > cpp) {printf("					ERROR restore out of sync...\n"); exit(0);}

	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 10; i++) {
			if (i == 0) {
				tosort1[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 1) {
				tosort2[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 2) { tosort3[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 3) { tosort4[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 4) { tosort5[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 5) { tosort6[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 6) { tosort7[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 7) { tosort8[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 8) { tosort9[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 9) { tosorta[fl] = mygrid[ps].mygridA[fl][i];
			}
		}
	}
	cpp = ps+1;
}

int cpoint() {
	if (cpp > maxc) {maxc = cpp;}
	if (cpp + 10 > MAXCPOINT) {printf("CPOINT ERR\n"); exit(0);}

	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 10; i++) {
			if (i == 0) { mygrid[cpp].mygridA[fl][i] = tosort1[fl];
			} else if (i == 1) { mygrid[cpp].mygridA[fl][i] = tosort2[fl];
			} else if (i == 2) { mygrid[cpp].mygridA[fl][i] = tosort3[fl];
			} else if (i == 3) { mygrid[cpp].mygridA[fl][i] = tosort4[fl];
			} else if (i == 4) { mygrid[cpp].mygridA[fl][i] = tosort5[fl];
			} else if (i == 5) { mygrid[cpp].mygridA[fl][i] = tosort6[fl];
			} else if (i == 6) { mygrid[cpp].mygridA[fl][i] = tosort7[fl];
			} else if (i == 7) { mygrid[cpp].mygridA[fl][i] = tosort8[fl];
			} else if (i == 8) { mygrid[cpp].mygridA[fl][i] = tosort9[fl];
			} else if (i == 9) { mygrid[cpp].mygridA[fl][i] = tosorta[fl];
			} 
		}
	}
	cpp++;
	return cpp;
}
