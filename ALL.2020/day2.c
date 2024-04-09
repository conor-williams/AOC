#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2020 day2 part1\n"
#define _DEBUG_
int tot = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
while(1) {
        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif

	int min = 0; int max = 0; char letter; char password[200];
	sscanf(line1, "%d-%d %c: %s", &min, &max, &letter, password);
printf("%d -- %d %c %s\n", min, max, letter, password);
	int numletter = 0;
	for (int i = 0; i< strlen(password); i++) {
		if (password[i] == letter)  {
			numletter++;
		}	
	}
	if (numletter >= min && numletter <= max) {
		tot++;
		printf("valid: %s\n", password);
	}
		leny++;
	printf("lenx %d - leny %d\n", lenx, leny);
}
fclose(a);
	printf("******** tot %d\n", tot);
}
