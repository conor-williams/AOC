#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2016 day9 part2 \n"
#define _DEBUG_
long tot;
#define SIZE 90000000

///compile: -Wl,--stack,999777666
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[SIZE];
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	char newLine[SIZE]; int newLinePos = 0;
	int found; int count = 0;
        do {
		found = 0; newLinePos = 0;
		memset(newLine, 0, sizeof(newLine));
		for (int i = 0; i < (int)strlen(line1); i++) {
			if (line1[i] == '\(') {
				int fI = 0; int sI = 0;
				char f[SIZE]; char s[SIZE];
				int fPos = 0; int j; 
				for (j = i+1; line1[j] != 'x'; j++) {
					f[fPos] = line1[j]; fPos++;
				}
				f[fPos] = '\0'; fI = atoi(f);
				int k; int sPos = 0;
				for (k = j+1; line1[k] != ')'; k++) {
					s[sPos] = line1[k]; sPos++;
					
				}
				i = k+1;
				s[sPos] = '\0'; sI = atoi(s);
				int z;
//		printf("%d X %d\n", fI, sI); 
				char subString[SIZE];
		memset(subString, 0, sizeof(subString));
				for (z = 0; z < fI; z++) {
					subString[z] = line1[i]; i++;
				}
				subString[z] = '\0';
//		printf("substring = %s\n", subString); 
				char mulSubString[SIZE];
		memset(mulSubString, 0, sizeof(mulSubString));
				for (int q = 0; q < sI; q++) {
					strcat(mulSubString, subString);
				}
				strcat(newLine, mulSubString);
//		printf("mulSub %s\n", mulSubString); 
				newLinePos += strlen(mulSubString);
				found = 1;
				i--;
			} else if (line1[i] == ')') {
				printf("ERROR\n"); getchar();
				found = 1;
			} else {
				newLine[newLinePos] = line1[i]; newLinePos++;
			}
		}
		newLine[newLinePos] = '\0'; newLinePos++;
//	printf("newLine %s\n", newLine); fflush(stdout);
		dup2(fd, 1);
		printf("pass %d len(%d)\n", count, (int)strlen(newLine)); fflush(stdout);
		exit(0);
		count++;
		strcpy(line1, newLine);
		//break;
	} while (found == 1);
	printf("deCOMP len %d\n", (int)strlen(newLine));
	tot += (int)strlen(newLine);

}
fclose(a);

	printf("***tot %ld END\n", tot); fflush(stdout);
} 
