#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>

#define getchar()
#include <unistd.h>

#define getchar()
int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
int main(int argc, char **argv)
{
	printf("%d", argc);
	printf("%s", argv[1]);
	fflush(stdin); fflush(stdout);

	FILE * a = fopen(argv[1], "r");
	printf("2023 Day3.1\n");

	fflush(stdout); int fd = dup(1); close(1);

	fflush(stdin); fflush(stdout);
	char line1[1000];
	char line2[1000];
	char line3[1000];
	//char *tok;
	int linenum = 0;
	//int gameNumTotalValid = 0;
	//char tmptok[200];
	//int sumpowerrgb = 0;
	fgets(line1, 1000, a);
	fgets(line2, 1000, a);
	fgets(line3, 1000, a);
	int sum = 0;
	while (1) {
		printf("LINE1: %s\nLINE2: %s\nLINE3: %s\n", line1, line2, line3);
		if (feof(a)) break;
		linenum++;
		int pos = 0, found = 0, lengthOfNum = 0, startOfNum = 0, goodNum = -1;
		char theNum[150] = "";
		for (int i = 0; i < 200 && line2[i] != '\0'; i++) {
			if (isdigit(line2[i])) {
				if (found == 0) {
					startOfNum = i; /*printf("Start: %d\n", startOfNum);*/ lengthOfNum++; theNum[pos++] = line2[i]; theNum[pos] = '\0';
					found = 1;
				}
				else if (found == 1) {
					lengthOfNum++; theNum[pos++] = line2[i]; theNum[pos] = '\0';
				}
				//printf("Num: %s Len %d, startOfNum: %d\n", theNum, lengthOfNum, startOfNum);
			} else {
				if (lengthOfNum != 0) {
					goodNum = -1;
					//printf("XNum: %s Len %d startOfNum %d\n", theNum, lengthOfNum, startOfNum);
					if (!isdigit(line2[startOfNum + lengthOfNum]) && 
							line2[startOfNum + lengthOfNum ] != '\0' && 
							line2[startOfNum + lengthOfNum ] != '\n' && 
							line2[startOfNum + lengthOfNum ] != '.') {
						goodNum = atoi(theNum);
						if (!isAlready(goodNum)) sum += goodNum;
						printf("GE2: %d\n", goodNum);
					} else { 
						if (!isdigit(line2[startOfNum - 1]) && 
								line2[startOfNum - 1] != '\0' && 
								line2[startOfNum - 1] != '.') {
							goodNum = atoi(theNum);
							if (!isAlready(goodNum)) sum += goodNum;
							printf("GS2: %d\n", goodNum);
						}
					}

					if (goodNum == -1) {	
						//if (startOfNum == 0) startOfNum = 1;
						if (startOfNum == 0) startOfNum = 1;
						if (startOfNum + lengthOfNum == 140) {printf("hereXXXXX"); lengthOfNum--;}

						for (int j = startOfNum -1; j < startOfNum + lengthOfNum + 1; j++) {

							if (!isdigit(line1[j]) && line1[j] != '\0' && line1[j] != '.') {
								goodNum = atoi(theNum);
								if (!isAlready(goodNum)) sum += goodNum;
								printf("G1: %s %d\n", theNum, goodNum);
								break;
							} else if (!isdigit(line3[j]) && line3[j] != '\0' && line3[j] != '.') {
								goodNum = atoi(theNum);
								if (!isAlready(goodNum)) sum += goodNum;
								printf("G3: %s %d\n", theNum, goodNum);
								break;
							} 
						}	
					}
				}
				pos = 0;
				lengthOfNum = 0;
				startOfNum = 0;
				found = 0;
			}
		}
		strcpy(line1, line2);
		strcpy(line2, line3);
		fgets(line3, 1000, a);

	}
	fflush(stdin); fflush(stdout);
	fclose(a);

	printf("*** Sum: %d ****\n", sum);
	printf("%d", linenum);
	printf("ARR:\n");
	for (int j = 0; j< endarr; j++) {
		printf("%d ", arr[j]);
	}	
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", sum);
}

int isAlready(int num) {
	return 0;
	int i = 0;
	for (i = 0; i< 50000 && i< endarr; i++) {
		if (arr[i] == num) {return 1;}
	}

	endarr++; arr[i] = num; return 0;
}
