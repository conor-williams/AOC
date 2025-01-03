#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2015 day11 part1\n"
#define _DEBUG_

int tot = 0;
#define SIZE 200
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	//FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	//char line1[SIZE];
	char in[] = "hepxcrrq";
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



	for (int p = (int)'p'; p <= 122; p++) {
		for (int x = (int)'x'; x <= 122; x++) {
			for (int c = (int)'c'; c <= 122; c++) {
				for (int r1 = (int)'r'; r1 <= 122; r1++) {
					for (int r = (int)'r'; r <= 122; r++) {
						for (int q = (int)'q'; q <= 122; q++) { 
							int myIn[8];
							myIn[0] = (int)in[0]; myIn[1] = (int)in[1];
							myIn[2] = p; myIn[3] = x; myIn[4] = c; myIn[5] = r1;
							myIn[6] = r; myIn[7] = q;

							printf("%c%c%c%c%c%c%c%c\n", myIn[0], myIn[1], myIn[2], myIn[3],
									myIn[4], myIn[5], myIn[6], myIn[7]);
							int foundReq1 = 0;
							for (int i = 0; i < 8-2; i++) {
								if (myIn[i]+2 == myIn[i+1]+1 && myIn[i+1]+1 == myIn[i+2]) {
									printf("i is %d\n", i);
									printf("%d\n", myIn[i]);
									printf("%d\n", myIn[i+1]);
									printf("%d\n", myIn[i+2]);
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
													dup2(fd, 1);
													printf("thats it...: ");
													printf("%c%c%c%c%c%c%c%c\n", in[0], in[1], p, x, c, r1, r, q);

													printf("\n"); exit(0);
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
