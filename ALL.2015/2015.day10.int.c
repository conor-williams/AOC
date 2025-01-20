#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2015 day10 part1\n"
#define _DEBUG_

int tot = 0;
#define SIZE 100000000
int ar[SIZE];
int arNew[SIZE];
int numAr = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	numAr=0;
	printf("INPUT:");
	for (int i = 0; i < strlen(line1); i++) {
		ar[i] = line1[i] - 48;
		printf("%d", ar[i]);
		numAr++;
	}
	printf("\n");

	for (int z = 0; z<50; z++)  {
		int pos = 0;
		for (int i = 0; i < numAr; i++) {
			int count = 1;
			for (int j = i+1; j < numAr; j++) {
				if (ar[i] == ar[j]) {
					count++;
				} else if (ar[i] != ar[j]) {
					break;	
				}
			}
			arNew[pos] = count;
			arNew[pos+1] = ar[i];
			i += count-1;
			pos+=2;
		}
		numAr = pos;
		
		if ((int)numAr +10000 > SIZE) {
			printf("WARNING SIZE...exit\n"); exit(0);
		}
		for (int k = 0; k < numAr; k++) {
			ar[k] = arNew[k];
		}
		//printf("numAr: %d z: %d\n", numAr, z);
		printf("ANS:");
		for (int z = 0; z < numAr; z++) {
			printf("%d", ar[z]);
		}
		printf("\n");
		getchar();
		//printf("numAr: %d \n", numAr);
	}
	printf("numAr: %d\n", numAr);

}
fclose(a);

}
