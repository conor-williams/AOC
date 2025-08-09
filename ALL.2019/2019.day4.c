#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "		2019 day4 part1\n"
#define _DEBUG_

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
	//int wire = 0;

	int fir = 0, sec = 0;
while(1) {
        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	sscanf(line1, "%d-%d", &fir, &sec);
	leny++;
}

fclose(a);

	char buf[10];
	int count = 0;
	for (int i = fir; i <= sec; i++) {
		sprintf(buf, "%d", i);
		if (buf[5] >= buf[4] && buf[4] >= buf[3] && buf[3] >= buf[2] && buf[2] >= buf[1] && buf[1] >= buf[0]) { 
			int doubles = 0;
			for (int i = 5; i > 0; i--) {
				if (buf[i] == buf[i-1]) {
					doubles++;	 	
				}
			}
			if (doubles > 0) {
				count++;
			}
		}
	}
	
	//printf("lenx %d - leny %d\n", lenx, leny);
	printf("***count %d\n", count);
}
