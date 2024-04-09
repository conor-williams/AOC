#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2021 day2 part1\n"
#define _DEBUG_
int tot = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
	int fnum = 0; int udnum = 0;
while(1) {
        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif

	char command[50];
	int num = 0;
	sscanf(line1, "%s %d\n", command, &num);
	switch (command[0]) {
		case 'f': fnum += num; break;
		case 'u': udnum += num; break;
		case 'd': udnum -= num; break;
	}
}
fclose(a);
	printf("**MUL %d****** tots: H:%d D:%d\n", abs(fnum*udnum), fnum, udnum);
}
