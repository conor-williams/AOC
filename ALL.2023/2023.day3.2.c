#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
	printf("Day3.2\n");
	fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	char line2[1000];
	char line3[1000];
	//char *tok;
	int linenum = 0;
	///int gameNumTotalValid = 0;
	//char tmptok[200];
	//int sumpowerrgb = 0;
	fgets(line1, 1000, a);
	fgets(line2, 1000, a);
	fgets(line3, 1000, a);
	//int sum = 0;
	int mulandplus = 0;
	while (1) {
		printf("LINE1: %s\nLINE2: %s\nLINE3: %s\n", line1, line2, line3);
		if (feof(a)) break;
		linenum++;
		///int pos = 0, found = 0, lengthOfNum = 0, startOfNum = 0, goodNum = -1;
		int found = 0;
		char theNum[150] = "";
		for (int i = 0; i < 200 && line2[i] != '\0'; i++) {
			if (line2[i] == '*') {
				if (isdigit(line1[i])) { found++; }
				if (!isdigit(line1[i]) && isdigit(line1[i-1])) { found++; }
				if (!isdigit(line1[i]) && isdigit(line1[i+1])) { found++; }

				if (isdigit(line3[i])) { found++; }
				if (!isdigit(line3[i]) && isdigit(line3[i-1])) { found++; }
				if (!isdigit(line3[i]) && isdigit(line3[i+1])) { found++; }

				if (isdigit(line2[i-1])) {found++;}
				if (isdigit(line2[i+1])) {found++;}

				if (found == 2) {
					/*extract numbers*/
					int whichNum = 0;
					int nums[2] = {0};
					if (isdigit(line1[i])) { 
						int startpos = i;
						{while (isdigit(line1[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line1[nextpos])) {theNum[nextpos - startpos] = line1[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;

					}
					if (!isdigit(line1[i]) && isdigit(line1[i-1])) {
						int startpos = i-1;
						{while (isdigit(line1[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line1[nextpos])) {theNum[nextpos - startpos] = line1[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;

					}
					if (!isdigit(line1[i]) && isdigit(line1[i+1])) { 
						int startpos = i+1;
						{while (isdigit(line1[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line1[nextpos])) {theNum[nextpos - startpos] = line1[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						printf("%d\n", atoi(theNum));
						nums[whichNum] = atoi(theNum); whichNum++;
					}


					if (isdigit(line3[i])) { 
						int startpos = i;
						{while (isdigit(line3[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line3[nextpos])) {theNum[nextpos - startpos] = line3[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;
					}
					if (!isdigit(line3[i]) && isdigit(line3[i-1])) {
						int startpos = i-1;
						{while (isdigit(line3[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line3[nextpos])) {theNum[nextpos - startpos] = line3[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;
					}
					if (!isdigit(line3[i]) && isdigit(line3[i+1])) {
						int startpos = i+1;
						{while (isdigit(line3[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line3[nextpos])) {theNum[nextpos - startpos] = line3[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;
					}

					if (isdigit(line2[i-1])) {
						int startpos = i-1;
						{while (isdigit(line2[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line2[nextpos])) {theNum[nextpos - startpos] = line2[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;
					}
					if (isdigit(line2[i+1])) {
						int startpos = i+1;
						{while (isdigit(line2[startpos])) {startpos--;}} startpos++; /*get the start*/
						/*getTheNumForward*/ int nextpos = startpos;
						while (isdigit(line2[nextpos])) {theNum[nextpos - startpos] = line2[nextpos]; nextpos++;} theNum[nextpos - startpos]='\0';
						nums[whichNum] = atoi(theNum); whichNum++;
					}
					printf("Nums: %d * %d\n", nums[0], nums[1]);
					mulandplus += nums[0] * nums[1];
				}
			}
			found = 0;
		}
		strcpy(line1, line2);
		strcpy(line2, line3);
		fgets(line3, 1000, a);

	}
	fflush(stdin); fflush(stdout);
	fclose(a);
	printf("*** MulandPlus Gears: %d ****\n", mulandplus);
	printf("%d", linenum);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", mulandplus);
}

