#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day7 part2 \n"
#undef _DEBUG_
long tot;

int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
	int count = 0;
while(1) 
{
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
	printf("LINE: %s\n", line1);
#endif
	char first[1000]; int firstPos = 0;
	char second[1000]; int secondPos = 0;
	int inSecond = 0;
	for (int i = 0; i < strlen(line1); i++) {
		if (line1[i] == '[') {
			inSecond = 1;
			continue;
		} else if (line1[i] == ']') {
			inSecond = 0;
			continue;
		}
		
		if (inSecond == 1) {
			second[secondPos] = line1[i];
			secondPos++;
		} else {
			first[firstPos] = line1[i];
			firstPos++;
		}
	}	
	first[firstPos] = '\0'; firstPos++;
	second[secondPos] = '\0'; secondPos++;
		

#ifdef _DEBUG_
	printf("%s %s\n", first, second);
#endif
/*
	int invalidFirst = 1;
	for (int i = 0; i < strlen(first) -3; i++) {
		int iX = i;
		if (first[iX] == first[iX+3] && first[iX+1] == first[iX+2] && first[iX] != first[iX+1]) {
			printf("%d(good)(1): %c%c%c%c\n", leny, first[iX], first[iX+1], first[iX+2], first[iX+3]);
			invalidFirst = 0; break;
		} else {
		}
	}

	int invalidSecond = 0;
	if (invalidFirst == 0) {
		for (int j = 0; j < strlen(second) -3; j++) { 
			int jX = j;
			if (second[jX] == second[jX+3] && second[jX+1] == second[jX+2] && second[jX] != second[jX+1]) {
				printf("%d(bad)(2): %c%c%c%c\n", leny, second[jX], second[jX+1], second[jX+2], second[jX+3]);
				invalidSecond = 1; break;
			} else {
			}
		}
	}
*/
	int invalidThird = 1;
	char ABA1[100];
	char ABA2[100];
	int ABApos=0;
	int invalidSecond = 0;
	if (invalidSecond == 0) {
		printf("ABA search...\n"); 
		for (int j = 0; j < strlen(first) -2; j++) { 
			int jX = j;
			if (first[jX] == first[jX+2] && first[jX] != first[jX+1]) {
				ABA1[ABApos] = first[jX];
				ABA2[ABApos] = first[jX+1];
				printf("good ABA(3) %c %c %c\n", first[jX], first[jX+1], first[jX+2]);
				ABApos++;
				invalidThird = 0;
			} else {
			}
		}
	}
	int invalidFourth = 1;
	if (invalidThird == 0) {
		printf("BAB search..."); 
		for (int j = 0; j < strlen(second) -2; j++) { 
			int jX = j;
			for (int z = 0; z < ABApos; z++) {
				if (second[jX] == second[jX+2] && second[jX] == ABA2[z] && second[jX+1] == ABA1[z]) {
					printf("good BAB(3) %c %c %c\n", second[jX], second[jX+1], second[jX+2]); fflush(stdout); 
					invalidFourth = 0; goto end;
				} else {
					printf("(badBAB)(2): %c %c %c\n", second[jX], second[jX+1], second[jX+2]); fflush(stdout);
				}
			}
		}
	}
end:
	//printf("%d %d %d %d\n", invalidFirst, invalidSecond, invalidThird, invalidFourth);
	printf("%d %d\n", invalidThird, invalidFourth);
	//if (invalidFirst == 0 && invalidSecond == 0 && invalidThird == 0 && invalidFourth == 0) {
	if (invalidThird == 0 && invalidFourth == 0) {
		printf("count now %d\n", count); fflush(stdout);
		count++;
	}
	leny++;
	printf("------------\n");
}
fclose(a);

	dup2(fd, 1);
	printf("**count [%d]\n", count);
	printf("\n");
    	return 0;
} 
