#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2015 day12 part1\n"
#undef _DEBUG_

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);

	char line1[28000];

	int tot = 0;
	while(1) {
		fgets(line1, 28000, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif
		char line2[28000];
		for (int i = 0; i < (int)strlen(line1); i++) {
			if (isdigit(line1[i]) || line1[i] == '-') {line2[i] = line1[i];}
			else {line2[i] = ',';}
		}
		line2[(int)strlen(line1)] = '\0';
		char *fir = strtok(line2, ",");
		do {
			if (fir[0] == '\0') {continue;} else {tot+=atoi(fir);}
		} while ((fir = strtok(NULL, ",")) != NULL);
	}
	fclose(a);
	
	printf("**ans: %d\n", tot);
}
