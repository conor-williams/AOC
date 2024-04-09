#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
int numlet[26];
#define DAY "2018 day2 part1\n"
#define _DEBUG_
int main(int argc, char **argv)
{
	int totFound2 = 0;
	int totFound3 = 0;
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[1000];

while(1) {
	for (int i = 0; i < 26; i++) {numlet[i] = 0;}
        fgets(line1, 999, a);
        if (feof(a)) break;
	leny++;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	printf("lenx %d - leny %d\n", lenx, leny);
	for (int i = 0; i< lenx; i++) {
		int pos = (int)((int)line1[i] - (int)'a');
		if (pos < 0 || pos > 25) {
#ifdef _DEBUG_
			printf("CONTINUE: ERROR getchar: [%]", line1[i]); 
#endif
			break;
		} else {
#ifdef _DEBUG_
			printf("pos %d: %c\n", pos, line1[i]);
#endif
			numlet[pos]++;
		}
	}
		
	int found2 = 0;
	int found3 = 0;
	for (int i = 0; i < 26; i++) {
		if (numlet[i] == 2) {
			found2 = 1;
		} else if (numlet[i] == 3) {
			found3 = 1;
		}
		
		if (found2 == 1 && found3 == 1) {
			break;
		}
	}	
	if (found2 == 1) {totFound2++;}
	if (found3 == 1) {totFound3++;}
	
}
fclose(a);
long tot = 0;
	tot = totFound2 * totFound3;
	
	printf("******** tot %ld\n", tot);
}
