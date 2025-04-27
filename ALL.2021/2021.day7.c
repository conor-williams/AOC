#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
struct crab {
	int posI;
	char posS[10];

};
struct crab crabs[1200];
FILE *a;
int main(int argc, char **argv)
{
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2021 Day7 Part1\n"); fflush(stdout);
	
	fflush(stdout); int fd = dup(1); close(1);

        char line1[5000];
	char *first;
	int posC = 0;
	int leny = 0;
while (1) {
        fgets(line1, 4999, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = ',';
        printf("LINE: %s\n", line1);
	first = strtok(line1, ",");
	crabs[posC].posI = atoi(first);	
	strcpy(crabs[posC].posS, first);
	while ((first = strtok(NULL, ",")) != NULL) {
		posC++;
		strcpy(crabs[posC].posS, first);
		crabs[posC].posI = atoi(first);	
	}

	leny++;
}
fclose(a);
	posC++;
	int maxC = 0; int minC = 999999;

	for (int i = 0; i < posC; i++) {
		if (crabs[i].posI > maxC) {maxC = crabs[i].posI;}
		if (crabs[i].posI < minC) {minC = crabs[i].posI;}
		printf("crab:%d:%d ", i, crabs[i].posI);
	}
	printf("\n");
	getchar();
	printf("MAX MIN %d %d\n", maxC, minC);


	int minTOT = 9999999;
	int minPOS = 0;
	for (int i = minC; i <= maxC; i++) {
		int tot = 0;
		for (int k = 0; k < posC; k++) {
			tot += abs(crabs[k].posI - i);
		}
		if (tot < minTOT) {minTOT = tot; minPOS = i;}
        } 
	
	printf("***minTOT %d (%d)\n", minTOT, minPOS);

	fflush(stdout); dup2(fd, 1);
	printf("**ans %d \n", minTOT);
	exit(0);

	int maxTOT = 0;
	int maxPOS = 0;
	for (int i = minC; i <= maxC; i++) {
		int tot = 0;
		for (int k = 0; k < posC; k++) {
			tot += abs(crabs[k].posI - i);
		}
		if (tot > maxTOT) {maxTOT = tot; maxPOS = i;}
        } 

	printf("***maxTOT %d (%d)\n", maxTOT, maxPOS);
}
