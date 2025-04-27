#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
int numlet[26];
#define DAY "		2018 day2 part2\n"
#define _DEBUG_
int fd;
int main(int argc, char **argv)
{
	int totFound2 = 0;
	int totFound3 = 0;
	lenx = 0; leny = 0;
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); fd = dup(1); close(1);
        char line1[1000];
	char lines[2000][200];
while(1) {
	for (int i = 0; i < 26; i++) {numlet[i] = 0;}
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	strcpy(lines[leny], line1);
	leny++; lenx = strlen(line1);
	printf("lenx %d - leny %d\n", lenx, leny);
}

	for (int i = 0; i < leny; i++) {
		for (int j = i+1; j < leny; j++) {
			if (strcmp(lines[i], lines[j]) != 0) {
				int diffs = 0; int myindex = -1;
				for (int k = 0; k < lenx; k++) {
					if (lines[i][k] != lines[j][k]) {if (myindex == -1) {myindex = k;} diffs++;}
					if (diffs > 1) {break;}
				}
				if (diffs == 1) {printf("Line %s V %s INDEX:%d\n", lines[i], lines[j], myindex);
					fflush(stdout); dup2(fd, 1);
					char ans[1000];
					strcpy(ans, lines[j]);
					ans[myindex] = ' ';
					char ans2[1000];
					int qq = 0;
					for (int zz = 0; zz <= (int)strlen(ans); zz++) {
						if (ans[zz] == ' ') {
						} else {
							ans2[qq++] = ans[zz];	
						}
					}
					printf("**ans: %s\n", ans2); exit(0);
				}
				diffs = 0; myindex = 0;
			}
		}
			
	}


fclose(a);
long tot = 0;
	tot = totFound2 * totFound3;
	

	fflush(stdout); dup2(fd, 1);
	printf("*** tot %ld\n", tot);
}
