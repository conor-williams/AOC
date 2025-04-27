#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int score = 0;
unsigned long long tot = 0;
int iX = 0;
int inside = 0;
#define SIZE 20000
char line1[SIZE];
int loop();
char cAtchA[200][20];
int cAtchAPos;
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("		2017 Day9.1\n"); fflush(stdout);
	fflush(stdout); int fd = dup(1); close(1);


int leny = 0;
while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	score = 0; tot = 0;
	for (iX = 0; iX < (int)strlen(line1); iX++) {
		printf("looking at %c\n", line1[iX]);
		loop();
	}
	leny++;
	//printf("***score is %d\n", score);

	//printf("***tot is ^^ [%llu]\n", tot);
}
	printf("cAtchA (%d):\n", cAtchAPos);
	for (int i = 0; i < cAtchAPos; i++) {
		printf("	[%s]\n", cAtchA[i]);
	}
	fflush(stdout); dup2(fd, 1);
	printf("***tot is ^^ [%llu]\n", tot);

}
int loop() {
	if (line1[iX] == '{') {
		if (inside == 0) {
			score++;
			tot += score;
		}
	} else if (line1[iX] == '}') {
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
		inside = 1;
	} else if (line1[iX] == '>') {
		inside = 0;
	} else if (line1[iX] == '!') {
		if (isdigit((int)line1[iX+1]) || isupper((int)line1[iX+1]) || islower((int)line1[iX+1]) || line1[iX+1] == '\"' || line1[iX+1] == ',' || line1[iX+1] == '\'') {
			
		} else {
			//if (line1[iX+1] == '<' || line1[iX+1] == '>' || line1[iX+1] == '}' || line1[iX+1] == '{') {
			//} else {
				printf("neg:[");
				printf("!");
				int count = 1;
				char cAtch[20];

				memset(cAtch, '\0', 19);
				char cAtch2[18];
				strcpy(cAtch2, cAtch);
				sprintf(cAtch, "%s%c", cAtch2, '!');
				
				do {
					if (isdigit((int)line1[iX+count]) || isupper((int)line1[iX+count]) || islower((int)line1[iX+count]) || line1[iX+count] == '\"' || line1[iX+count] == ',' || line1[iX+count] == '\'' || line1[iX+count] == '\"') {
						break;
					} else {
						printf("%c", line1[iX+count]);
						char cAtch3[18];
						strcpy(cAtch3, cAtch);
						sprintf(cAtch, "%s%c", cAtch3, line1[iX+count]);
					}
					count++;
					if (count == 4) {break;}
					if (line1[iX+count] == '!') { break;}
					if (iX+count > strlen(line1)) {break;}
				} while (1);
				cAtch[count] = '\0';
				int found = 0;
				for (int i = 0; i < cAtchAPos; i++) {
					if (strcmp(cAtchA[i], cAtch) == 0) {
						found = 1; break;
					}
				}
				if (found == 0) {
					strcpy(cAtchA[cAtchAPos], cAtch); cAtchAPos++;	
				}
				printf("] --- [!");
				count = 1;
				do {
					printf("%c", line1[iX+count]);
					count++;
					if (count == 8) {break;}
					if (iX+count > strlen(line1)) {break;}
				} while (1);
				printf("]\n");
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
			printf("startOne == %c next = %c\n", startOne, line1[iX]);
		}
/*
		if (line1[iX] == '<' || line1[iX] == '{' || line1[iX] == '>' || line1[iX] == '}') { //20160
			char startOne = line1[iX];
			switch(startOne) {
				case '<':
				case '{':
						while (line1[iX+1] == '<' || line1[iX+1] == '{') {
							iX++;	
						}
						
						break;
				case '>':
				case '}':
						while (line1[iX+1] == '>' || line1[iX+1] == '}') {
							iX++;	
						}
						break;
			}
			printf("startOne == %c next = %c\n", startOne, line1[iX]);
			if (line1[iX] == '}') {
				if (inside == 0) {tot -= score;}
			}
		}
*/
/*
		if (line1[iX] == '<' || line1[iX] == '{' || line1[iX] == '>' || line1[iX] == '}') { //20160
			char startOne = line1[iX];
			switch(startOne) {
				case '<':
				case '{':
						while (line1[iX+1] == '<' || line1[iX+1] == '{') {
							iX++;	
						}
						
						break;
				case '>':
				case '}':
						while (line1[iX+1] == '>' || line1[iX+1] == '}') {
							iX++;	
						}
						break;
			}
			printf("startOne == %c next = %c\n", startOne, line1[iX]);
			if (line1[iX] == '}') {
				if (inside == 0) {tot -= score;}
			}
		}
*/
/*
		if (line1[iX] == '<' || line1[iX] == '{' || line1[iX] == '>' || line1[iX] == '}') { //20160
			char startOne = line1[iX];
			switch(startOne) {
				case '<':
				case '{':
						while (line1[iX+1] == '<' || line1[iX+1] == '{') {
							iX++;	
						}
						
						break;
				case '>':
				case '}':
						while (line1[iX+1] == '>' || line1[iX+1] == '}') {
							iX++;	
						}
						break;
			}
			printf("startOne == %c next = %c\n", startOne, line1[iX]);
			if (line1[iX] == '}') {
				if (inside == 0) {tot -= score;}
			}
		}
*/
/*
		if (line1[iX] == '<' || line1[iX] == '{' || line1[iX] == '>' || line1[iX] == '}') { //20160
			char startOne = line1[iX];
			switch(startOne) {
				case '<':
				case '{':
						while (line1[iX+1] == '<' || line1[iX+1] == '{') {
							iX++;	
						}
						
						break;
				case '>':
				case '}':
						while (line1[iX+1] == '>' || line1[iX+1] == '}') {
							iX++;	
						}
						break;
			}
			printf("startOne == %c next = %c\n", startOne, line1[iX]);
			if (line1[iX] == '}') {
				if (inside == 0) {tot -= score;}
			}
		}
*/
	}
	return 0;
}
