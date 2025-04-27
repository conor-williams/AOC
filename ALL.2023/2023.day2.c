#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <unistd.h>

#define getchar()
/*
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;


struct hash_function
{
size_t operator()(const tuple<int , int , int, int>&x) const
{
unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
}
};

*/



FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2023 Day 2 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	long tot = 0;
	////	Game 100: 16 blue, 12 red, 3 green; 2 green, 7 blue; 5 blue, 4 green; 10 blue, 6 red, 6 green; 5 red, 12 blue, 2 green; 9 red, 12 blue, 11 green
	int maxRed = 12;
	int maxGreen = 13;
	int maxBlue = 14;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		char *fir = strtok(line1, ":");
		char gameStr[20];
		strcpy(gameStr, fir);
		fir = strtok(NULL, ":");
		char *eachPtr = fir;
		char *each = strtok_r(eachPtr, ";\0", &eachPtr);
		
		int gameBad = 0;
		do {
			char *colorOrNumPtr = each;
			char *colorOrNum = strtok_r(colorOrNumPtr, ",\0", &colorOrNumPtr);
			do {
				printf("%s\n", colorOrNum);
				int num;
				char color[20];
				sscanf(colorOrNum, "%d %s", &num, color);
				printf("**%d---%s\n", num, color);
				if (strcmp(color, "red") == 0) {
					if (num > maxRed) {gameBad=1; goto next;}
				} else if (strcmp(color, "green") == 0) {
					if (num > maxGreen) {gameBad=1; goto next;}
				} else if (strcmp(color, "blue") == 0) {
					if (num > maxBlue) {gameBad=1; goto next;}
				}
			} while ((colorOrNum = strtok_r(colorOrNumPtr, ",\0", &colorOrNumPtr)) != NULL);

		} while ((each = strtok_r(eachPtr, ";\0", &eachPtr)) != NULL);

		if (gameBad == 0) {
			char *g1 = strtok(gameStr, " ");	
			g1 = strtok(NULL, " ");
			int gameNum = atoi(g1);
			tot+=gameNum;
		}
next:	
		leny++;
	}
	fclose(a);

	fflush(stdout); dup2(fd, 1);
	printf("**ans %ld\n", tot);
}
	
