#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <search.h>


FILE *a;
int charsort(const void *p1, const void *p2);
int panel[20][8][8] = {0}; // each led the possibles (for each 20 numbers)
int numsFromFile[20][10] = {0};
int numInter(int seven1[10], int seven2[10]);
int countGreat = 0;
#define getchar()
int mynums[301] = {0};
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day8\n"); fflush(stdout);
        char line1[5000];
	char *first;
	int tot = 0;
	int leny = 0;

	//uniq
	int have1 = -1; int have7 = -1; int have4 = -1; int have8 = -1;
	
	//fives
	int have2 = -1; int have3 = -1; int have5 = -1;

	//sixes
	int have6 = -1; int have9 = -1; int have0 = -1;
while (1) {
        fgets(line1, 4999, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	first = strtok(line1, "| ");

	//first = strtok(NULL, "| ");

	int posC = 0;
	for (int j = 0; j < 8; j++) {
		for (int l = 0; l < 8; l++) {
			panel[posC][j][l] = 0;
		}
	}
	for (int i = 0; i < 15; i++) {
		numsFromFile[i][8] = -1;
	}
	do {
	
		int fLen = strlen(first);
		qsort(first, fLen, 1, charsort);
		printf("first is %s\n", first); //getchar();
		for (int i = 0; i < strlen(first); i++) {
			numsFromFile[posC][first[i]-97] = 1;
		}
		numsFromFile[posC][7] = strlen(first);
		switch (fLen) {
			case 2:
				for (int j = 0; j < 7; j++) {
					if (j == 1 || j == 2) {
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 1;
						}
					} else {
						for (int k = 0; k < 7; k++) {
							panel[posC][j][k] = 1;
						}
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 0;
						}
					}
				}
				have1 = posC;
				numsFromFile[posC][8]= 1;
				break;
			case 3:
				for (int j = 0; j < 7; j++) {
					if (j==0 || j == 1 || j == 2) {
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 1;
						}
					} else {
						for (int k = 0; k < 7; k++) {
							panel[posC][j][k] = 1;
						}
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 0;
						}
					}
				}

				have7 = posC;
				numsFromFile[posC][8]= 7;
				break;
			case 4:
				for (int j = 0; j < 7; j++) {
					if (j == 1 || j == 2 || j == 5 || j==6) {
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 1;
						}
					} else {
						for (int k = 0; k < 7; k++) {
							panel[posC][j][k] = 1;
						}
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 0;
						}
					}
				}

				have4 = posC;
				numsFromFile[posC][8]= 4;
				break;
			case 7:
				for (int j = 0; j < 7; j++) {
					if (j == 1 || j == 2 || j==0 || j==3 || j==4 || j==5 || j==6) {
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 1;
						}
					} else {
						for (int k = 0; k < 7; k++) {
							panel[posC][j][k] = 1;
						}
						for (int m=0; m < strlen(first); m++) {
							int x1 = first[m] - 97;
							panel[posC][j][x1] = 0;
						}
					}
				}
				have8 = posC;
				numsFromFile[posC][8]= 8;
				break;
			case 5: //five lights (5,2,3)
				
				break;
			case 6: //6 lights (0,6,9)
				break;
		}
		posC++;
	} while ((first = strtok(NULL, "| ")) != NULL);

	if (have1) {
		printf("here1...\n"); getchar();
		for (int i = 0; i < posC; i++) {
			if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have1], numsFromFile[i]) == 2 && numsFromFile[i][8] == -1) {
				numsFromFile[i][8] = 3;
				have3 = i;
			}
		}
	} else if (have7) {
		printf("here1...\n"); getchar();
		for (int i = 0; i < posC; i++) {
			if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have7], numsFromFile[i]) == 3 && numsFromFile[i][8] == -1) {
				numsFromFile[i][8] = 3;
				have3 = i;
			}
		}
	}

	if (have3) {	
		printf("here2...\n"); getchar();
		for (int i = 0; i < posC; i++) {
			if (numsFromFile[i][7] == 6 && numInter(numsFromFile[have3], numsFromFile[i]) == 5 && numsFromFile[i][8] == -1) {
				numsFromFile[i][8] = 9;
				have9 = i;
			}
		}
	}
	if (have7) {
		for (int i = 0; i < posC; i++) {
			if (numsFromFile[i][7] == 6 && numInter(numsFromFile[have7], numsFromFile[i]) == 3 && numsFromFile[i][8] == -1) {
				numsFromFile[i][8] = 0;
				have0 = i;
			}
		}
	}
	for (int i = 0; i < posC; i++) {
		if (numsFromFile[i][7] == 6 && numsFromFile[i][8] == -1) {
			numsFromFile[i][8] = 6;
			have6 = i;
		}
	}
       
	if (have4) {
		for (int i = 0; i < posC; i++) {
			if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have4], numsFromFile[i]) == 3 && numsFromFile[i][8] == -1) {
				numsFromFile[i][8] = 2;
				have2 = i;
			}
		}
	}

	for (int i = 0; i < posC; i++) {
		if (numsFromFile[i][7] == 5 && numsFromFile[i][8] == -1) {
			numsFromFile[i][8] = 5;
			have5 = i;
		}
	}

	char mynum[5];
	if (numsFromFile[posC-1][8] != -1 && numsFromFile[posC-2][8] != -1 && numsFromFile[posC-3][8] != -1 && numsFromFile[posC-4][8] != -1) {
		printf("here3....");
		mynum[0] = numsFromFile[posC-1][8]+48;
		mynum[1] = numsFromFile[posC-2][8]+48;
		mynum[2] = numsFromFile[posC-3][8]+48;
		mynum[3] = numsFromFile[posC-4][8]+48;
		mynum[4] = '\0';
		mynums[leny] = atoi(mynum);
		tot += mynums[leny];
		countGreat++;
		printf("great... [%s]\n", mynum);
	}
/*
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i< posC; i++) {
			if (ignore[i] == 1) {continue;}
			for (int k = 0; k < 7; k++) {
				printf("%d ", panel[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	int panels[10] = {-1};
	int times = 0;
restart:
        for (int j = 0; j < 7; j++) {
                int count[10] = {-1};
                for (int i = 0; i < posC; i++) {
			if (ignore[i] == 1) {continue;}
                        for (int k = 0; k < 7; k++) {
                                count[k] += panel[i][j][k];
                        }
                }
		int found = 0;
                for (int k = 0; k<7;k++) {
			int found1 = 0;
			for (int z = 0; z < 7; z++) {
				if (count[z] == posC-ignoreTOT) {
					found1++;
				}
			}
			if (found1 == 1) {
				if (count[k] == posC-ignoreTOT) {
					panels[j] = k;
					found = 1;
					printf("FOUND panels j:[%d] is %d\n", j, panels[j]); getchar();
				}
			}
                }
		if (found == 1) {
			for (int i = 0; i < posC; i++) {
				for (int k = 0; k < 7; k++) {
					if (k != panels[j]) {
						panel[i][j][k] = 0;
					} else {
						panel[i][j][k] = 1;
					}

				}
				for (int j1 = 0; j1 < 7; j1++) {
					if (j == j1) {continue;}
					int k = panels[j];
					panel[i][j1][k] = 0;
				}
			}
			for (int j = 0; j < 7; j++) {
				for (int i = 0; i< posC; i++) {
					if (ignore[i] == 1) {continue;}
					for (int k = 0; k < 7; k++) {
						printf("%d ", panel[i][j][k]);
					}
					printf("\n");
				}
				printf("\n");
			}
			
		}
        }
        times++;
        if (times < 10) {
        	for (int i = 0; i < 7; i++) {
                	printf("panels[%d] %d\n", i, panels[i]); getchar();
        	}
                goto restart;
        }

        for (int i = 0; i < 7; i++) {
                printf("panels[%d] %d\n", i, panels[i]); getchar();
        }
*/

	leny++;
}
fclose(a);

	printf("countGreat %d\n", countGreat);
	printf("***tot %d\n", tot);
}
 
 
int numInter(int seven1[10], int seven2[10]) {

	int count = 0;
	for (int i = 0; i < 7; i++) {
		if (seven1[i] == seven2[i] && seven1[i] == 1) {
			count++;	
		}
	}
	return count;
}
int charsort(const void *p1, const void *p2) 
{ 
	unsigned char *c1, *c2; 
	c1 = (unsigned char*) p1; 
	c2 = (unsigned char*) p2; 
	return(*c1 - *c2); 
} 
