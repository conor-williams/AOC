#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int score = 0;
unsigned long long tot = 0;
unsigned long long totG = 0;
int iX = 0;
int inside = 0;
#define SIZE 20000
#undef _DEBUG_
char line1[SIZE];
int loop();
char catchA[200][20];
int catchAPos;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

int leny = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	score = 0; tot = 0; totG = 0;
	for (iX = 0; iX < (int)strlen(line1); iX++) {
		printf("looking at %c\n", line1[iX]);
		loop();
	}
	leny++;
	//printf("***score is %d\n", score);
	printf("***tot is ^^ [%llu]\n", tot);
	printf("***totG %llu\n", totG); getchar();
}
/*
	printf("catchA (%d):\n", catchAPos);
	for (int i = 0; i < catchAPos; i++) {
		printf("	[%s]\n", catchA[i]);
	}
*/
	dup2(fd, 1);
	printf("***totG %llu\n", totG);

}
int loop() {
	if (line1[iX] == '{') {
		if (inside == 0) {
			score++;
			tot += score;
		}
		if (inside == 1) {totG++;}
	} else if (line1[iX] == '}') {
		if (inside == 1) {totG++;}
		if (inside == 0) {
/*
			if (line1[iX-1] == '!') {
				tot -= score;
			} else {
				int posend = 0;
				for (int i = iX-1; i > 1; i--) {
					if (line1[i] == '>') {
					} else {
						posend = i;
						break;
					}
				}
				if (line1[posend] == '!') {
					tot -= score;
				}
			}
*/
			score--;
		}
	} else if (line1[iX] == '<') {
		if (inside == 1) {totG++;}
		inside = 1;
	} else if (line1[iX] == '>') {
		inside = 0;
	} else if (line1[iX] == '!') {
		if (isdigit((int)line1[iX+1]) || isupper((int)line1[iX+1]) || islower((int)line1[iX+1]) || line1[iX+1] == '\"' || line1[iX+1] == ',' || line1[iX+1] == '\'') {
			
		} else {
			//if (line1[iX+1] == '<' || line1[iX+1] == '>' || line1[iX+1] == '}' || line1[iX+1] == '{') {
			//} else {
#ifdef _DEBUG_
				printf("neg:[");
				printf("!");
#endif
				int count = 1;
				char catch[20];
				char catch3[18];
				strcpy(catch3, catch);
				memset(catch, '\0', 19);
				sprintf(catch, "%s%c", catch3, '!');
				do {
					if (isdigit((int)line1[iX+count]) || isupper((int)line1[iX+count]) || islower((int)line1[iX+count]) || line1[iX+count] == '\"' || line1[iX+count] == ',' || line1[iX+count] == '\'' || line1[iX+count] == '\"') {
						break;
					} else {
#ifdef _DEBUG_
						printf("%c", line1[iX+count]);

#endif
						char catch2[18];
						strcpy(catch2, catch);
						sprintf(catch, "%s%c", catch2, line1[iX+count]);
					}
					count++;
					if (count == 4) {break;}
					if (line1[iX+count] == '!') { break;}
					if (iX+count > strlen(line1)) {break;}
				} while (1);
				catch[count] = '\0';
				int found = 0;
				for (int i = 0; i < catchAPos; i++) {
					if (strcmp(catchA[i], catch) == 0) {
						found = 1; break;
					}
				}
				if (found == 0) {
					strcpy(catchA[catchAPos], catch); catchAPos++;	
				}
#ifdef _DEBUG_
				printf("] --- [!");
#endif
				count = 1;
				do {
#ifdef _DEBUG_
					printf("%c", line1[iX+count]);
#endif
					count++;
					if (count == 8) {break;}
					if (iX+count > strlen(line1)) {break;}
				} while (1);
#ifdef _DEBUG_
				printf("]\n");
#endif
			//}
		}
		iX++;
		if (line1[iX] == '<' || line1[iX] == '{' || line1[iX] == '>' || line1[iX] == '}') { //20160
			char startOne = line1[iX];
			switch(startOne) {
				case '<':
						/*
						while (line1[iX+1] == '<' || line1[iX+1] == '{') {
							iX++;	
						}
						*/
						break;
				case '{':
						/*
						while (line1[iX+1] == '<' || line1[iX+1] == '{') {
							iX++;	
						}
						*/
						break;
				case '>':
						if (line1[iX+1] == '}') {
							if (inside == 0) {tot -= score;}
						}
						break;
				case '}':
						if (inside == 0) {tot -= score;}
						/*
						while (line1[iX+1] == '>' || line1[iX+1] == '}') {
							iX++;	
						}
						*/
						break;
			}
#ifdef _DEBUG_
			printf("startOne == %c next = %c\n", startOne, line1[iX]);
#endif
		}
	} else {
		printf("else: [%c]", line1[iX]);
		if (inside == 1) {totG++;}
	}
	return 0;
}
