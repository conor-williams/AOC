#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//int END = 2028;	//plus ten
int END = 330131;
int tot = 0;
#define SIZE 299
char line1[SIZE];
int leny = 0;
void printit(char ar1[], int len, int poses[], int posesPos);

char ar[400000];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);

while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[(int)strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	strcpy(ar, line1);
	leny++;
}
fclose(a);
	int poses[20];
	int posesPos = (int)strlen(ar);
	for (int i = 0; i < posesPos; i++) {
		poses[i] = i;
	}
	printit(ar, (int)strlen(ar), poses, posesPos); getchar();
	do {
		int sum = 0; 
		for (int j = 0; j < posesPos; j++) {
			sum += ar[poses[j]] - 48;
		}

		char dig1 = (sum % 10) +48;
		char dig2 = (sum / 10) +48;
		//printf(" %c %c\n", dig1, dig2);

		int len = (int)strlen(ar);
		if (dig2 != '0') {
			ar[len] = dig2;
			ar[len+1] = dig1;
			ar[len+2] = '\0';
		} else {
			ar[len] = dig1;
			ar[len+1] = '\0';
		}
		for (int j = 0; j < posesPos; j++) {
			poses[j] = (poses[j] + (ar[poses[j]]-48+1)) % (int)strlen(ar);
		}
		//printit(ar, (int)strlen(ar), poses, posesPos); getchar();
		
	} while ((int)strlen(ar) < END);

	printf("ANS: ");
	for (int k = END-10; k < END; k++) {
		printf("%c", ar[k]);
	}
	printf("\n");
}
void printit(char ar1[], int len, int poses[], int posesPos) {
	printf("AR: ");
	for (int i = 0; i < len; i++) {
		printf("%c,", ar1[i]);
	}
	printf("\n");
	printf("Poses: ");
	for (int i = 0; i < posesPos; i++) {
		printf(" %d, ", poses[i]);
	} 
	printf("\n");
}
	
