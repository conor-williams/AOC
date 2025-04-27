#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2022 day2 part2\n"
#define _DEBUG_
long tot;
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[3000];
	//int fnum = 0; int udnum = 0; int aim = 0;
	while(1) {
		fgets(line1, 2990, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s\n", line1);
#endif

		//char command[50];
		//int num = 0;
		char HIS; char MINE;
		//A == ROCK  	== X
		//B == PAPER	== Y
		//C == SCISSORS	== Z

		//Y draw
		//X lose
		//Z win
		sscanf(line1, "%c %c\n", &HIS, &MINE);
		switch(HIS) {
			case 'A':
				switch (MINE) {
					case 'X': 
						MINE = 'Z';
						break;
					case 'Y':
						MINE = 'X';	
						break;
					case 'Z':
						MINE = 'Y';
						break;
				}
				break;

			case 'B':
				switch (MINE) {
					case 'X': 
						MINE = 'X';
						break;
					case 'Y':
						MINE = 'Y';	
						break;
					case 'Z':
						MINE = 'Z';
						break;
				}
				break;
			case 'C':
				switch (MINE) {
					case 'X':
						MINE = 'Y';
						break;
					case 'Y':
						MINE = 'Z';	
						break;
					case 'Z':
						MINE = 'X';
						break;
				}
				break;

		}	




		switch (HIS) {
			case 'A': 
				switch(MINE) {
					case 'X': 
						tot += 1+3;
						break;
					case 'Y':
						tot += 2+6;
						break;
					case 'Z':
						tot += 3+0;
						break;
				}
				break;
			case 'B': 
				switch(MINE) {
					case 'X':
						tot += 1+0;
						break;
					case 'Y':
						tot += 2+3;
						break;
					case 'Z':
						tot += 3+6;
						break;
				}
				break;
			case 'C':
				switch(MINE) {
					case 'X':
						tot += 1+6;
						break;
					case 'Y':
						tot += 2+0;
						break;
					case 'Z':
						tot += 3+3;
						break;
				}
				break;
		}
	}
	fclose(a);
	printf("**tot %ld\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", tot);
}
