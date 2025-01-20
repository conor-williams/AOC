#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day6 part2 \n"
#undef _DEBUG_
long tot;

char lines[700][12];
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	//fflush(stdout); int fd = dup(1); //close(1);
        char line1[220];
while(1) 
{
        fgets(line1, 200, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
        strcpy(lines[leny], line1);
	leny++;
}
    	fclose(a);
	for (int j = 0; j < strlen(lines[0]); j++) {
		int count[27] = {0};
		for (int i = 0; i < leny; i++) {
			count[lines[i][j] -97]++;
		}
		//int max = 0; int maxindex = 0;
		int min = 1000; int minindex = 0;
		for (int k = 0; k < 26; k++) {
			if (count[k] != 0 && count[k] < min) {min = count[k]; minindex = k;}
		}
		printf("%c", (char)(minindex+97));
	}
	printf("\n");
    	return 0;
} 
