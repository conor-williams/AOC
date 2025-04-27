#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "		2015 day11 part2\n"
#define _DEBUG_

int tot = 0;
#define SIZE 200
int secondOne = 0;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	//FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);


	//char line1[SIZE];
	char in[] = "hepxcrrq";
	//	char in[] = "hepxxyzz";
	//int inI[] = {(int)'h', (int) 'e', (int) 'p', (int) 'x', (int) 'c', (int) 'r', (int) 'r', (int) 'q'};
	/*
	   while(1) {
	   fgets(line1, SIZE-1, a);
	   if (feof(a)) break;
	   line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
printf("LINE: %s\n", line1);
#endif
}
	 */
	//fclose(a);


	int first[9] = {1};
for (int p = (int)'a'; p <= 122; p++) {
	if (first[2] == 0) {p = 'p'; first[2] = 1;}
	for (int x = (int)'a'; x <= 122; x++) {
		if (first[3] == 0) {x = 'x'; first[3] = 1;}
		for (int c = (int)'a'; c <= 122; c++) {
			if (first[4] == 0) {c = 'c'; first[4] = 1;}
			for (int r1 = (int)'a'; r1 <= 122; r1++) {
				if (first[5] == 0) {r1 = 'r'; first[5] = 1;}
				for (int r = (int)'a'; r <= 122; r++) {
					if (first[6] == 0) {r = 'r'; first[6] = 1;}
					for (int q = (int)'a'; q <= 122; q++) { 
						if (first[7] == 0) {q = 'q'; first[7] = 1;}
						int myIn[8];
						myIn[0] = (int)in[0]; myIn[1] = (int)in[1];
						myIn[2] = p; myIn[3] = x; myIn[4] = c; myIn[5] = r1;
						myIn[6] = r; myIn[7] = q;

						/*printf("%c%c%c%c%c%c%c%c\n", myIn[0], myIn[1], myIn[2], myIn[3],
						  myIn[4], myIn[5], myIn[6], myIn[7]);*/
						int foundReq1 = 0;
						for (int i = 0; i < 8-2; i++) {
							if (myIn[i]+2 == myIn[i+1]+1 && myIn[i+1]+1 == myIn[i+2]) {
								/*
								   printf("i is %d\n", i);
								   printf("%d\n", myIn[i]);
								   printf("%d\n", myIn[i+1]);
								   printf("%d\n", myIn[i+2]);
								 */
								foundReq1 = 1; break;
							}
						}	
						if (foundReq1 == 1) {
							int foundReq2 = 0;
							for (int i = 0; i < 8; i++) {
								if (myIn[i] == 'i' || myIn[i] == 'o' || myIn[i] == 'l') {
									foundReq2 = 1; break;
								}
							}	
							if (foundReq2 == 0) {
								for (int i = 0; i < 5; i++) {
									if (myIn[i] == myIn[i+1]) {
										for (int j = i+2; j < 7; j++) {
											if (myIn[j] == myIn[j+1]) {
												if (secondOne == 1) {
													printf("thats it...\n");
													fflush(stdout); dup2(fd, 1);
													printf("**ans: ");
													printf("%c%c%c%c%c%c%c%c\n", in[0], in[1], p, x, c, r1, r, q);
													exit(0);
												} else {
													secondOne = 1;

												}
											}

										}
									}
								}

							}
						}

					}
				}
			}
		}
	}
}
}
