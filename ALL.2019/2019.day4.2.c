#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2019 day4 part2\n"
#define _DEBUG_

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        //char line1[3000];
	//int wire = 0;

/*
while(1) {
        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif
	leny++;
}
*/

fclose(a);

	char buf[10];
//int ia[] = {112233, 123444, 111122};
	//for (int i = 0; i <= 2; i++) 
	int count = 0;
	for (int i = 134792; i <= 675810; i++) {
		sprintf(buf, "%d", i);
		if (buf[5] >= buf[4] && buf[4] >= buf[3] && buf[3] >= buf[2] && buf[2] >= buf[1] && buf[1] >= buf[0]) { 
			int doubles = 0;
			for (int i = 5; i >= 1; i--) {
				if (i == 5) {
					if (buf[5] == buf[4] &&
						 buf[4] != buf[3]) {
						doubles = 1; break;
					}	
				} else if (i >= 2) {
					if (buf[i+1] != buf[i] && 
						buf[i] == buf[i-1] && 
						buf[i-1] != buf[i-2]) {
					    doubles = 1; break;
					}
				}  else if (i == 1) {
					if (buf[0] == buf[1] && 
						buf[1] != buf[2]) {
					    doubles = 1; break;
					}
					
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
