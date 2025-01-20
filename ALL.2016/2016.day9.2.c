#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day9 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 120000

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); //close(1);
        char line1[SIZE];
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	///char newLine[SIZE]; int newLinePos = 0;
	//int found; int count = 0;
	int a[SIZE];
	for (int ii = 0; ii < (int)strlen(line1); ii++) {
		a[ii] = 1;
	}
	for (int i = 0; i < (int)strlen(line1); i++) {
		if (line1[i] == '(') {
			int j = i;
			char line2[1000];
			do {
				line2[j-i] = line1[j];
				j++;
			} while (line1[j] != ')');
			line2[j-i] = ')';
			line2[j-i+1] = '\0';
			int fir; int sec;
			int ret = sscanf(line2, "(%dx%d)", &fir, &sec);
			if (ret != 2) {printf("ERR"); exit(0);}
			//printf("fir: %d sec: %d\n", fir, sec);
			for (int kk = j+1; kk < j+1+fir; kk++) {
				a[kk] *= sec;
			}
			i = j;
			assert(line1[i] == ')');
		}
		//printf("weights: ");
		//for (int zz = 0; zz < (int)strlen(line1); zz++) {
		//	printf("%d", a[zz]);
		//}
		//printf("\n");
	}
	tot = 0;
	int ignore = 0;
	for (int ii = 0; ii < (int)strlen(line1); ii++) {
		if (line1[ii] == '(') {ignore = 1; continue;}
		else if (line1[ii] == ')') {ignore = 0;continue;}
		if (ignore == 0) {tot += a[ii];}
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", tot);
}
fclose(a);

} 
