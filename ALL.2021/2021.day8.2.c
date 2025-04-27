#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <search.h>


#include <unistd.h>

#define getchar()
FILE *a;
int charsort(const void *p1, const void *p2);
int numsFromFile[20][10] = {0};
int numInter(int seven1[10], int seven2[10]);
void numJoin(int seven1[10], int seven2[10], int res[10]);
int countGreat = 0;
#define getchar()
int mynums[301] = {0};
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day8 Part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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
	int haveSevenFour  = -1;
	while (1) {
		have1 = -1;
		have2 = -1;
		have3 = -1;
		have4 = -1;
		have5 = -1;
		have6 = -1;
		have7 = -1;
		have8 = -1;
		have9 = -1;
		haveSevenFour = -1;
		fgets(line1, 4999, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		first = strtok(line1, "| ");

		//first = strtok(NULL, "| ");

		int posC = 0;
		for (int i = 0; i < 15; i++) {
			for (int k = 0; k < 9; k++) {
				numsFromFile[i][k] = -1;
			}
		}
		do {

			int fLen = strlen(first);
			qsort(first, fLen, 1, charsort);
			//printf("first is %s\n", first); //getchar();
			for (int i = 0; i < (int)strlen(first); i++) {
				numsFromFile[posC][first[i]-97] = 1;
			}
			numsFromFile[posC][7] = strlen(first);
			switch (fLen) {
				case 2:
					have1 = posC;
					numsFromFile[posC][8]= 1;
					break;
				case 3:
					have7 = posC;
					numsFromFile[posC][8]= 7;
					break;
				case 4:
					have4 = posC;
					numsFromFile[posC][8]= 4;
					break;
				case 7:
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

		if (have1 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have1], numsFromFile[i]) == 2 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 3;
					have3 = i;
				}
			}
			if (have3 == -1) {have3 = -2;}
			printf("no three from one??? %d\n", have3);
		} else if (have7 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have7], numsFromFile[i]) == 3 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 3;
					have3 = i;
				}
			}
			printf("no three from seven\n");
			if (have3 == -1) {have3 = -2;}
		} else {
			printf("oops... no 1 or 7\n"); getchar();
		}

		int sevenFour[10] = {0};
		for (int k = 0; k < 7; k++) {
			sevenFour[k] = 0;
		}
		if (have7 != -1 && have4 != -1) {
			haveSevenFour = 1;
			printf("Seven: ");
			for (int z = 0; z < 7; z++) {
				printf(" %d ", numsFromFile[have7][z]);
			} printf("\nFour: ");
			for (int z = 0; z < 7; z++) {
				printf(" %d ", numsFromFile[have4][z]);
			} printf("\n");
			numJoin(numsFromFile[have7], numsFromFile[have4], sevenFour);
		}

		if (have3 == -1 || have3 == -2) {printf("no three %d\n", have3); getchar();}
		if (have3 != -2 && have3 != -1) {	
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 6 && numInter(numsFromFile[have3], numsFromFile[i]) == 5 && numsFromFile[i][8] == -1) {
					printf("got nine...\n"); getchar();
					numsFromFile[i][8] = 9;
					have9 = i;
				}
			}
			if (have9 == -1) {have9 = -2;}
		} else if (haveSevenFour != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 6 && numInter(sevenFour, numsFromFile[i]) == 5 && numsFromFile[i][8] == -1) {
					printf("got nine..SEVENFOUR.\n"); getchar();
					numsFromFile[i][8] = 9;
					have9 = i;
					for (int j = 0; j<7;j++) {
						printf(" %d ", numsFromFile[i][j]);
					}
					printf("\n");
				}
			}
			if (have9 == -1) {have9 = -2;}
		}

		if (have7 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 6 && numInter(numsFromFile[have7], numsFromFile[i]) == 3 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 0;
					printf("got zero. witha 7..\n"); getchar();
					have0 = i;
				}
			}
			if (have0==-1) {have0 = -2;}
		} else if (have1 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 6 && numInter(numsFromFile[have1], numsFromFile[i]) == 2 && numsFromFile[i][8] == -1) {
					printf("got zero. witha 1..\n"); getchar();
					numsFromFile[i][8] = 0;
					have0 = i;
				}
			}
			if (have0==-1) {have0 = -2;}

		}
		if (have9 != -1 && have0 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 6 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 6;
					have6 = i;
				}
			}
		} else {
			printf("did not have 9 and 0\n");
		}

		if (have4 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have4], numsFromFile[i]) == 3 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 5;
					have5 = i;
				}
			}
			if (have5 == -1) {have5 = -2;}
		} else if (have9 != -1 && have9 != -2) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 5 && numInter(numsFromFile[have9], numsFromFile[i]) == 4 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 5;
					have5 = i;
				}
			}
			if (have5 == -1) {have5 = -2;}
		}


		if (have5 != -1 && have3 != -1) {
			for (int i = 0; i < posC; i++) {
				if (numsFromFile[i][7] == 5 && numsFromFile[i][8] == -1) {
					numsFromFile[i][8] = 2;
					have2 = i;
				}
			}
		} else {
			printf("did not have 5 and 3\n");
		}

		char mynum[5];
		if (numsFromFile[posC-1][8] != -1 && numsFromFile[posC-2][8] != -1 && numsFromFile[posC-3][8] != -1 && numsFromFile[posC-4][8] != -1) {
			printf("here3....");
			mynum[3] = numsFromFile[posC-1][8]+48;
			mynum[2] = numsFromFile[posC-2][8]+48;
			mynum[1] = numsFromFile[posC-3][8]+48;
			mynum[0] = numsFromFile[posC-4][8]+48;
			mynum[4] = '\0';
			mynums[leny] = atoi(mynum);
			tot += mynums[leny];
			countGreat++;
			printf("great... [%s]\n", mynum);
		}
		leny++;
	}
	fclose(a);


	printf("countGreat %d\n", countGreat);
	printf("***tot %d\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);
}


void numJoin(int seven1[10], int seven2[10], int sevenRes[10]) {

	for (int i = 0; i < 7; i++) {
		if (seven1[i] == 0 && seven2[i] ==0) {
			(sevenRes)[i] = 0;
		} else {
			(sevenRes)[i] = 1;
		}
	}
	printf("JOIN: ");
	for (int i = 0; i < 7; i++) {
		printf("%d ", sevenRes[i]);
	}
	printf("\n");
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
