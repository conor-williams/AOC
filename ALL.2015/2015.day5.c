#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2015 day5 part1\n"
#define _DEBUG_

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[200];
	int count = 0;
while(1) {
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[(int)strlen(line1) -1]='\0';
	lenx = (int)strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	int nogood = 0;
printf("nogood: %d\n", nogood);
	for (int i = 0; i < (int)strlen(line1)-1; i++) {
		if (line1[i] == 'a' && line1[i+1] == 'b') {
			nogood = 1;
		} else if (line1[i] == 'c' && line1[i+1] == 'd') {
			nogood = 1;
		} else if (line1[i] == 'p' && line1[i+1] == 'q') {
			nogood = 1;
		} else if (line1[i] == 'x' && line1[i+1] == 'y') {
			nogood = 1;
		}
	}	
printf("nogood: %d\n", nogood);
	int a = 0; int e = 0; int i1 = 0; int o = 0; int u = 0;
	if (nogood == 0) {
		for (int j = 0; j < (int)strlen(line1); j++) {
			switch (line1[j]) {
				case 'a': {a++; break;}
				case 'e': {e++; break;}
				case 'i': {i1++; break;}
				case 'o': {o++; break;}
				case 'u': {u++; break;}
			}
				
		}
		if (a+e+i1+o+u >= 3) {/*ok*/} else {nogood = 1;}
	}
printf("nogood: %d\n", nogood);
	if (nogood == 0) {
		int ok = 0;
		for (int i = 0; i < (int)strlen(line1)-1; i++) {
			if (line1[i] == line1[i+1]) {	
				ok = 1; break;
			}
		}
		if (ok == 0) {
			nogood = 1;
		}
	}
printf("nogood: %d\n", nogood);
	if (nogood == 1) {
		// dont count
	} else {
		count++;
	}
        leny++;
}
fclose(a);

	fflush(stdout); dup2(fd, 1);
printf("***count %d\n", count);
}
