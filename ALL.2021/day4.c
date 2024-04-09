#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char ar[1000][50];
FILE *a;
struct bin {
	int val;
	int got;
};
struct bin bar[120][5][5];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day3\n"); fflush(stdout);
        char line1[1000];

int leny = -1;
char numsS[300];
//int  bAr[120][5][5];
int pos = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	if (leny == -1) {strcpy(numsS, line1); leny++; continue;}
	if (line1[0] != '\0') {
		for (int i = 0; i < strlen(line1)-1; i++) {
			if (i == 0 && line1[0] == ' ') {
				int j;
				for (j = i; j < strlen(line1)-1; j++) {
					line1[j] = line1[j+1];
				}
				line1[j] = '\0';
			}
			if (line1[i] == ' ' && line1[i+1] == ' ') {
				int j;
				for (j = i; j < strlen(line1)-1; j++) {
					line1[j] = line1[j+1];
				}
				line1[j] = '\0';
			}
		}
	}
	if (line1[0] == '\0') {pos=0; continue;} else {
		printf("leny pos line1.. %d %d: %s", leny, pos, line1);
		char numA[5][4];
		sscanf(line1, "%[^ ] %[^ ] %[^ ] %[^ ] %d", numA[0], numA[1], numA[2],numA[3], &bar[leny][pos][4].val);
		
		printf("%s %s %s\n", numA[0], numA[1], numA[2]);
		bar[leny][pos][0].val = atoi(numA[0]);
		bar[leny][pos][0].got = 0;
		bar[leny][pos][1].val  = atoi(numA[1]);
		bar[leny][pos][1].got = 0;
		bar[leny][pos][2].val  = atoi(numA[2]);
		bar[leny][pos][2].got = 0;
		bar[leny][pos][3].val  = atoi(numA[3]);
		bar[leny][pos][3].got = 0;
		bar[leny][pos][4].got = 0;
		printf("SHUD: %d %d %d\n", bar[leny][pos][0].val , bar[leny][pos][1].val , bar[leny][pos][2].val );
		if (pos == 4) {pos=0; leny++;}
		pos++;
	}
	printf("atend\n");
}
fclose(a);
	for (int i = 0; i < leny; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d %d %d %d %d\n",
				bar[i][j][0].val,
				bar[i][j][1].val,
				bar[i][j][2].val,
				bar[i][j][3].val,
				bar[i][j][4].val);
		}
		//printf("get\n"); 
	}

	int mynums[500];
	int numpos = 0;
	char s[2] = ",";
	char *token;
	token = strtok(numsS, s);
	while(token!=NULL) {
		printf("%d ", mynums[numpos] = atoi(token));
		numpos++;
		token = strtok(NULL, s);	
	}

	int tot = 0;
	for (int n = 0; n < numpos; n++) {
		for (int i = 0; i < leny; i++) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					if (bar[i][j][k].val == mynums[n]) {
						bar[i][j][k].got = 1;
					}
				}
			}
		}
		//check	row
		for (int i = 0; i < leny; i++) {
			for (int j = 0; j < 5; j++) {
				int win = 1;
				for (int k = 0; k < 5; k++) {
					if (bar[i][j][k].got == 0) {
						win = 0;
					}
				}
				if (win == 1) {
					printf("\ngot a win puz: i(%d) rowj: (%d) \n", i, j);
					for (j=0; j<5;j++) {
						for (int k=0; k<5;k++) {
							if (bar[i][j][k].got == 0) {
								tot += bar[i][j][k].val;	
							}
						}
					}
					printf("***tot %d\n", tot*mynums[n]);
					exit(0);
				}
			}
		}
		//check	column
		for (int i = 0; i < leny; i++) {
			for (int j = 0; j < 5; j++) {
				int win = 1;
				int k;
				for (k = 0; k < 5; k++) {
					if (bar[i][k][j].got == 0) {
						win = 0;
					}
				}
				if (win == 1) {
					printf("\ngot a win puz: i(%d) col: k(%d) \n", i, k);
					for (j=0; j<5;j++) {
						for (int k=0; k<5;k++) {
							if (bar[i][j][k].got == 0) {
								tot += bar[i][j][k].val;	
							}
						}
					}
					printf("***tot %d\n", tot*mynums[n]);
					exit(0);
				}
			}
		}
	}
}
