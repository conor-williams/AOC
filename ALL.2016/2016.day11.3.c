#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

int lenx, leny;
#define DAY "2016 day11 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 1000
//#define getchar()

char grid[5][12][4];
char gridOrig[5][12][4];
int posX = 0;
void makemove(int ar[]);
int cpoint();
void restore(int ps);
int tosort1[4];
int tosort2[4];
int tosort3[4];
int tosort4[4];
int mygrid[1000][4][4];
int cpp = 0;

int main(int argc, char **argv)
{
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

	tosort1[0] = 1; tosort1[1] = 0; tosort1[2] = 0; tosort1[3] = 0;
	tosort2[0] = 1; tosort2[1] = 0; tosort2[2] = 0; tosort2[3] = 0;
	tosort3[0] = 0; tosort3[1] = 1; tosort3[2] = 0; tosort3[3] = 0;
	tosort4[0] = 0; tosort4[1] = 0; tosort4[2] = 1; tosort4[3] = 0;
	
	int myqs[] = {0, 0, 0, 0, 0};
	makemove(myqs);
	tot = 0;

	printf("END\n");
} 
void makemove(int myqs[]) {

	printf("in makemove...\n");
	int po[30];
	int pos = 0;
	int qs[10];
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
			int found2 = 0; 
			for (int i = 0; i < 4; i++) {
				if (qs[i] == myqs[i] &&qs[i] == 1) {
					found2++;
				}
			}
			if (found2 >= 1) { continue; }

			for (int i = 0; i < 4; i++) { printf("%d ", qs[i]); }
			printf("\n");
			int tmpsortOrig[] = {0, 0, 0, 1};
			int tmpsort[] = {0, 0, 0, 1};

			//int tosort4[] = {0, 0, 1, 0};

			int num1 = -1; int num2 = -1;
			if (qs[0] == 1 && qs[1] ==1) {
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort1[i] == tosort2[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					for (int i = 0; i < 4; i++) {
			
						num1 = 0;
						num2 = 1;
						
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
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort1[i];
						num1 = 0;
						num2 = 2;
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
					for (int i = 0; i < 4; i++) {
						num1 = 0;
						num2 = 3;
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
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort2[i];
						num1 = 1; num2 = 2;
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
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort2[i];
						num1 = 1; num2 = 3;
						tmpsortOrig[i] = tosort2[i];
					}
				} else {continue;}
			} else if (qs[2] == 1 && qs[3] ==1) {
				int found = 0;
				for (int i = 0; i < 4; i++) {
					if (tosort3[i] == tosort4[i]) {
						found++;
					}
				}
				if (found == 4) {//ok
					for (int i = 0; i < 4; i++) {
						tmpsort[i] = tosort3[i];
						num1 = 2; num2 = 3;
						tmpsortOrig[i] = tosort3[i];
					}
				} else {continue;}
			} else if (qs[0] == 1) { for (int i = 0; i < 4; i++) { num1 = 0; tmpsort[i] = tosort1[i]; tmpsortOrig[i] = tosort1[i];} 
			} else if (qs[1] == 1) { for (int i = 0; i < 4; i++) { num1 = 1; tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort2[i];}
			} else if (qs[2] == 1) { for (int i = 0; i < 4; i++) { num1 = 2; tmpsort[i] = tosort2[i]; tmpsortOrig[i] = tosort3[i];} 
			} else if (qs[3] == 1) { for (int i = 0; i < 4; i++) { num1 = 3; tmpsort[i] = tosort4[i]; tmpsortOrig[i] = tosort4[i];} }

			sort(tmpsort, tmpsort+4);
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
/*
				int mytmpgrid[4][4];
				for (int fl = 4-1; fl >= 0; fl--) {//every floor
					for (int r = 0; r < 4; r++) {//every item
						if (qs[r] == 1) {//floor change
							printf("[%d] ", tmpsort[fl]);
							mytmpgrid[fl][r] = tmpsort[fl];
						} else if (qs[r] == 0) { //no floor change
							if (r == 0) {
								printf("[%d] ", tosort1[fl]);
								mytmpgrid[fl][r] = tosort1[fl];
							} else if (r == 1) {
								printf("[%d] ", tosort2[fl]);
								mytmpgrid[fl][r] = tosort2[fl];
							} else if (r == 2) {
								printf("[%d] ", tosort3[fl]);
								mytmpgrid[fl][r] = tosort3[fl];
							} else if (r == 3) {
								printf("[%d] ", tosort4[fl]);
								mytmpgrid[fl][r] = tosort4[fl];
							}
						}		
					}
					printf("\n");
				}
				printf("\n"); getchar();
*/
				//if (mytmpgrid[3][0] == 1 && mytmpgrid[3][1] == 1 && mytmpgrid[3][2] == 1 && mytmpgrid[3][3] == 1) {
				if (tosort1[3] == 1 && tosort2[3] == 1 && tosort3[3] == 1 && tosort4[3] == 1) {
					if (steps < minSteps) {minSteps = steps;}
					printf("END reached...\n"); getchar(); return;
				} else {
					int found10 = 0;
					for (int j = 0; j < cpp; j++) {
						int found11 = 0;
						for (int fl = 0; fl < 4; fl++) {
							for (int i = 0; i < 4; i++) {
								if (i == 0) {
									if (mygrid[j][fl][i] == tosort1[fl]) {
										found11++;
									}
								} else if (i == 1) {
									if (mygrid[j][fl][i] == tosort2[fl]) {
										found11++;
									}
								} else if (i == 2) {
									if (mygrid[j][fl][i] == tosort3[fl]) {
										found11++;
									}
								} else if (i == 3) {
									if (mygrid[j][fl][i] == tosort4[fl]) {
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
						po[pos++] = cpoint();
						makemove(qs);
						printf("back from makemove...\n");
						restore(po[pos]-1);
						//cpp = po[pos];
					}
				}
			} while (next_permutation(tmpsort, tmpsort+4));
		} while (next_permutation(qs, qs+4));

	}
	getchar();
}
void restore(int ps) {
	for (int fl = 0; fl < 4; fl++) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				tosort1[fl] = mygrid[ps][fl][i];
			} else if (i == 1) {
				tosort2[fl] = mygrid[ps][fl][i];
			} else if (i == 2) {
				tosort3[fl] = mygrid[ps][fl][i];
			} else if (i == 3) {
				tosort4[fl] = mygrid[ps][fl][i];
			}
		}
	}
}

int cpoint() {
	if (cpp + 10 > 1000) {printf("CPOINT ERR\n"); exit(0);}
	int found6 = 0;
	for (int z = 0; z < cpp; z++) {
		int found5 = 0;
		for (int fl = 0; fl < 4; fl++) {
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					if (mygrid[cpp][fl][i] == tosort1[fl]) {
						found5++;
					}
				} else if (i == 1) {
					if (mygrid[cpp][fl][i] == tosort2[fl]) {
						found5++;
					}
				} else if (i == 2) {
					if (mygrid[cpp][fl][i] == tosort3[fl]) {
						found5++;
					}
				} else if (i == 3) {
					if (mygrid[cpp][fl][i] == tosort4[fl]) {
						found5++;
					}
				}
			}
		}
		if (found5 == 16) {found6 = 1; break;}
	}
	if (found6 == 0) {
		for (int fl = 0; fl < 4; fl++) {
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					mygrid[cpp][fl][i] = tosort1[fl];
				} else if (i == 1) {
					mygrid[cpp][fl][i] = tosort2[fl];
				} else if (i == 2) {
					mygrid[cpp][fl][i] = tosort3[fl];
				} else if (i == 3) {
					mygrid[cpp][fl][i] = tosort4[fl];
				}
			}
		}
	} else {
		printf("already in cpoint...\n");
	}

	cpp++;
	return cpp;
}
