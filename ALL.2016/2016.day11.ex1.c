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

int lenx, leny;
#define DAY "2016 day11 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 1000
//#define getchar()

char grid[5][12][4];
char gridOrig[5][12][4];
int posX = 0;
void makemove(int ar[], long steps, int first);
//int cpoint(int tmpsort[], int qs[]);
int cpoint();
//void restore(int ps, int (*tmpsort)[], int (*qs)[]);
void restore(int ps);
int tosort1[4];
int tosort2[4];
int tosort3[4];
int tosort4[4];
#define MAXCPOINT 5000
struct mygrid_s {
	int mygridA[4][4];
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
         //signal(SIGILL, sig_handler);
         //signal(SIGKILL, sig_handler);
         //signal(SIGQUIT, sig_handler);
         signal(SIGTSTP, sig_handler);

	tot = 0;lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

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
			for (int i = 0; i < 4; i++) {
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

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 10; x++) {
			for (int i = 0; i < 4; i++) {
				gridOrig[y][x][i] = grid[y][x][i];
			}
		}
	}
getchar();
	tosort1[0] = 1; tosort1[1] = 0; tosort1[2] = 0; tosort1[3] = 0;
	tosort2[0] = 1; tosort2[1] = 0; tosort2[2] = 0; tosort2[3] = 0;
	tosort3[0] = 0; tosort3[1] = 1; tosort3[2] = 0; tosort3[3] = 0;
	tosort4[0] = 0; tosort4[1] = 0; tosort4[2] = 1; tosort4[3] = 0;
	
	int myqs[] = {0, 0, 0, 0, 0};
	makemove(myqs, 1, 1);
	tot = 0;

	//fflush(stdout); dup2(fd, 1);
	printf("minSteps: [%ld] END\n", minSteps);
	printf("maxc: [%d] END\n", maxc);
} 
int docheck() {
	int fHM; for (fHM = 0; fHM < 4; fHM++) {
		if (tosort1[fHM] == 1) {break;} //HM - hydrogen chip
	}
	int fHG; for(fHG = 0; fHG < 4; fHG++) {
		if (tosort3[fHG] == 1) {break;} //HG - hydrogen generator
	}
	int fLM; for (fLM = 0; fLM < 4; fLM++) {
		if (tosort2[fLM] == 1) {break;} //LM - lithium chip
	}
	int fLG; for (fLG = 0; fLG < 4; fLG++) {
		if (tosort4[fLG] == 1) {break;} //LG - lithium generator
	}
	if (fHM == fLG) {
		if (fHG == fHM) {
			//ok
		} else if (fLM == fLG) {
			//ok
		} else {
			//ERROR
			return 0;
		}
	} else if (fLM == fHG) {
		if  (fLG == fLM) {
			//ok
		} else if (fHM == fHG) {
			//ok
		} else {
			//ERROR
			return 0;
		}
	
	} else { 
		return 1;
	}
	return 0;

}
int count123 = 0;
void makemove(int myqs[], long steps, int first) {
	ind++;

	if (steps > minSteps) {ind--; return;}
	if (first != 1) { }
	int mainPos = cpoint();
	int qs[4];
	for (int end = 1; end <= 2; end++) {
		for (int o = 0; o < end; o++) {
			qs[o] = 1;
		}
		for (int z = end; z < 4; z++) {
			qs[z] = 0;
		}
		sort(qs, qs+4);
		int found2tot = 0;
		for (int i = 0; i < 4; i++) { if (myqs[i] == 1) { found2tot++; } }
		do {
			if (docheck() == 0) {ind--; return;}
			int found2 = 0; 
			for (int i = 0; i < 4; i++) { if (qs[i] == myqs[i] && qs[i] == 1) { found2++; } } if (found2 >= 1) { continue; }

			if (qs[0] == 1 || qs[1] == 1) {} else {printf("skip1\n"); printit(qs, steps, ind); continue;}

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
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort1[i] == tosort4[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					num1 = 0;
					num2 = 3;
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort1[i];
						tmpsortOrig[i] = tosort1[i];
					}
				} else {continue;}
			} else if (qs[1] == 1 && qs[2] ==1) {
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort2[i] == tosort3[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					num1 = 1; num2 = 2;
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort2[i];
						tmpsortOrig[i] = tosort2[i];
					}
				} else {continue;}
			} else if (qs[1] == 1 && qs[3] ==1) {
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort2[i] == tosort4[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					num1 = 1; num2 = 3;
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort2[i];
						tmpsortOrig[i] = tosort2[i];
					}
				} else {continue;}
			} else if (qs[2] == 1 && qs[3] ==1) {
printf("NEVER "); printit(qs, steps, ind);
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort3[i] == tosort4[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					num1 = 2; num2 = 3;
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort3[i];
						tmpsortOrig[i] = tosort3[i];
					}
				} else {continue;}
			} else if (qs[0] == 1) { num1 = 0; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i];} 
			} else if (qs[1] == 1) { num1 = 1; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i];}
			} else if (qs[2] == 1) { printf("NEVER2\n"); num1 = 2; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort3[i]; tmpsortOrig[i] = tosort3[i];} 
			} else if (qs[3] == 1) { printf("NEVER3\n"); num1 = 3; for (int i = 0; i < 4; i++) {tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i];} }

			sort(tmpsort, tmpsort+4);
			int changed = 0;
			int found55 = 0;
			for (int i = 0; i < 4; i++) {
				if (tmpsortOrig[i] == tmpsort[i]) {
					found55++;
				}
			}
			if (found55 == 4) {} else {changed = 1;}
			
			do {
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
				} else if (num1 == 3) {
					for (int i = 0; i < 4; i++) {
						tosort4[i] = tmpsort[i];
					}
				}
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
				} else if (num2 == 3) {
					for (int i = 0; i < 4; i++) {
						tosort4[i] = tmpsort[i];
					}
				}

				int found4 = 0;
				for (int i = 0; i < 4; i++) {
					if (tmpsort[i] == tmpsortOrig[i]) {
						found4++;
					}
				}
				if (found4 == 4) {
					continue;
				}
				printit(qs, steps, ind);
				if (tosort1[3] == 1 && tosort2[3] == 1 && tosort3[3] == 1 && tosort4[3] == 1) {
					if (steps < minSteps) {minSteps = steps;}
					printit(qs, steps, ind);
					printf("END reached.^^.. %ld %ld ------ret-----\n", steps, minSteps); ind--; return;
				} else {
					int found10 = 0;
					for (int j = 0; j < cpp; j++) {
						int found11 = 0;
						for (int fl = 0; fl < 4; fl++) {
							for (int i = 0; i < 4; i++) {
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
								} else if (i == 3) {
									if (mygrid[j].mygridA[fl][i] == tosort4[fl]) {
										found11++;
									}
								}
							}
						}
						if (found11 == 16) {
							found10 = 1;
							break;
						}
					}
					if (found10 == 1) {
						continue;
					} else {	
						printf("calling makemove with steps: %ld\n", steps+1);
						if (changed == 1) {
							makemove(qs, steps+2, 2);
						} else {
							makemove(qs, steps+1, 2);
						}
						restore(mainPos-1);
					}
				}
			} while (next_permutation(tmpsort, tmpsort+4));
		} while (next_permutation(qs, qs+4));

	}
}
void printit(int qs[], int steps, int ind) {
	printf("------------------VVVVV VVVV------------\n");
	for (int fl = 3; fl >=0; fl--) { for (int i = 0; i < 4; i++) { if (i == 0) { printf("%d ", tosort1[fl]); } else if (i == 1) { printf("%d ", tosort2[fl]); } else if (i == 2) { printf("%d ", tosort3[fl]); } else if (i == 3) { printf("%d ", tosort4[fl]); } } printf("\n"); } printf("\n");

	printf("Q: ");
	for (int i = 0; i < 4; i++) {
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
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				tosort1[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 1) {
				tosort2[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 2) {
				tosort3[fl] = mygrid[ps].mygridA[fl][i];
			} else if (i == 3) {
				tosort4[fl] = mygrid[ps].mygridA[fl][i];
			}
		}
	}
	cpp = ps+1;
}

///int cpoint(int tmpsort[], int qs[]) {
int cpoint() {
	if (cpp > maxc) {maxc = cpp;}
	if (cpp + 10 > MAXCPOINT) {printf("CPOINT ERR\n"); exit(0);}

	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				mygrid[cpp].mygridA[fl][i] = tosort1[fl];
			} else if (i == 1) {
				mygrid[cpp].mygridA[fl][i] = tosort2[fl];
			} else if (i == 2) {
				mygrid[cpp].mygridA[fl][i] = tosort3[fl];
			} else if (i == 3) {
				mygrid[cpp].mygridA[fl][i] = tosort4[fl];
			}
		}
	}
	cpp++;
	return cpp;
}
