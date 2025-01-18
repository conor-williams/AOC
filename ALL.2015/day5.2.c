#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2015 day5 part2\n"
#define _DEBUG_

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
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
	for (int i = 0; i < (int)strlen(line1)-3; i++) {
		char f = line1[i];
		char n = line1[i+1]; 
		for (int k = i+2; k < (int)strlen(line1)-1; k++) {
			if (f == line1[k] && n == line1[k+1]) {
				nogood = 0;
				printf("(f,n): (%c,%c) setting nogood: %d\n", f, n, nogood);
				goto next;
			} else {
				nogood = 1;
			}
		}
	
	}	
next:
printf("nogood: %d\n", nogood);
	if (nogood == 0) {
		printf("HERE\n");
		for (int i = 0; i < (int)strlen(line1)-2; i++) {
			char f = line1[i];
			//char n = line1[i+1];	
			if (f == line1[i+2]) {
				printf("f f %c %c\n", f, f);
				nogood = 0; break;
			} else {
				nogood = 1;
			}
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
