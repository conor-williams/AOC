#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <algorithm>
#include <string>

#include <unistd.h>

#define getchar()
using namespace std;
int tot = 0;
#define SIZE 100
char line1[SIZE];
int leny = 0;
//compile: -Wl,--stack,999777666
//.#.
//..# == .#./..#/### == .#...###
//###

void convTwo(char frm[], int part, int size);
void convThree(char frm[], int size);
void convEighty1(char frm[], int part);
void genallTwos();
void genallThrees();
char startG[60000];
void genRealAns(int num, int size);
char realAns[60000];
char ans[7000][60000];
void s(char startIn[]);
void s2(char startIn[]);

struct twosandthrees_s {
	char frm[900];
	char to[900];
	char orig[900];
};

struct twosandthrees_s twos[18];
int twosPos = 0;
struct twosandthrees_s threes[515];
int threesPos = 0;
void printStartHashes(char start[]);
struct twosandthrees_s eighty1s[515];
int eighty1sPos = 0;
int fd;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day21.1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);


while (1) 
{
        fgets(line1, SIZE -1, a);
	if (feof(a)) break;
 	line1[strlen(line1)-1] = '\0';
 	printf("line1 %s\n", line1);

	char frm[100], to[100];
	sscanf(line1, "%s => %s", frm, to);
	int x = 0; char frmx[100];
	for (int i = 0; i < (int)strlen(frm); i++) {
		if (frm[i] == '/') {
		} else {
			frmx[x++] = frm[i];
		}
	}
	frmx[x] = '\0';
	int y = 0; char toy[100];
	for (int i = 0; i < (int)strlen(to); i++) {
		if (to[i] == '/') {
		} else {
			toy[y++] = to[i];
		}
	}
	toy[y] = '\0';

	if (strlen(frmx) == 4) {
		strcpy(twos[twosPos].frm, frmx);
		strcpy(twos[twosPos].to, toy);
		strcpy(twos[twosPos].orig, frmx);
		twosPos++;
	} else {
		strcpy(threes[threesPos].frm, frmx);
		strcpy(threes[threesPos].to, toy);
		strcpy(threes[threesPos].orig, frmx);
		threesPos++;
	}
	leny++;
}
fclose(a);


printf("here1"); getchar();
	genallTwos();
	printf("bef threesPos is %d\n", threesPos);
printf("here2"); getchar();
	genallThrees();
	printf("threesPos is %d\n", threesPos);
	printf("twosPos is %d\n", twosPos);
}
///////////////////////////////////////
///////////////////////////////////////
void s2(char startIn[]) {
	char start[60000];
	//strcpy(startG, ".#...####");
	strcpy(start, startIn);
	for (int t = 0; t < 2; t++) {
		strcpy(ans[0], "");
		{ 
			printf("start is %s\n len:(%d) t: %d", start, (int)strlen(start), t);
			printStartHashes(start);
		}

		int numSq;
		if (((int)sqrt(strlen(start)) % 2) == 0) {
			assert((int)strlen(start)%4 == 0);
			int posAdder = -4;
			numSq = (int)strlen(start) / 4;
			switch (numSq) {
				case 16:
				case 1:
					printf("not used...\n"); exit(0);
					
				case 4:
				case 9:
				case 36:
				case 81:
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/4 == numSq);
						char p2[6] = ""; posAdder+=4;
						p2[0] = start[posAdder+0]; p2[1] = start[posAdder+1]; p2[2] = start[posAdder+2]; p2[3] = start[posAdder+3];
						p2[4] = '\0';
						convTwo(p2, k, numSq);
					}
					genRealAns(2, numSq);
					break;
				default:
					printf("not impl.2 of .%d.\n", numSq); exit(0);
			}
				

		} else { //the threes
			numSq = (int)strlen(start) / 9;
			int posAdder = -9;
			assert((int)strlen(start) %9 == 0);
			long long my3 = 0;
			switch (numSq) {
				case 4:
					printf("no imp 3s (%d)..\n", numSq); exit(0);
				case 1:
				case 9:
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/9 == numSq);
						char p3[11] = ""; posAdder += 9;

						p3[0] = start[posAdder+0];
						p3[1] = start[posAdder+1];
						p3[2] = start[posAdder+2];
						p3[3] = start[posAdder+3];
						p3[4] = start[posAdder+4];
						p3[5] = start[posAdder+5];
						p3[6] = start[posAdder+6];
						p3[7] = start[posAdder+7];
						p3[8] = start[posAdder+8];
						p3[9] = '\0';
						convThree(p3, k);
					}
					genRealAns(3, numSq);
					break;
				case 81:
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/9 == numSq);
						char p3[11] = ""; posAdder += 9;

						p3[0] = start[posAdder+0];
						p3[1] = start[posAdder+1];
						p3[2] = start[posAdder+2];
						p3[3] = start[posAdder+3];
						p3[4] = start[posAdder+4];
						p3[5] = start[posAdder+5];
						p3[6] = start[posAdder+6];
						p3[7] = start[posAdder+7];
						p3[8] = start[posAdder+8];
						p3[9] = '\0';
						convEighty1(p3, k);
						printf("after convEighty1\n");
					}
					printf("before genRealAns\n");
					genRealAns(3, numSq);
					printf("afeter genRealAns\n");
					break;

				case (81*729)/9:
					printf("readying for 81*729: %d\n", 81*729); getchar();
					my3 = 0;
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/9 == numSq);
						char p3[11] = ""; posAdder += 9;

						p3[0] = start[posAdder+0];
						p3[1] = start[posAdder+1];
						p3[2] = start[posAdder+2];
						p3[3] = start[posAdder+3];
						p3[4] = start[posAdder+4];
						p3[5] = start[posAdder+5];
						p3[6] = start[posAdder+6];
						p3[7] = start[posAdder+7];
						p3[8] = start[posAdder+8];
						p3[9] = '\0';
						convEighty1(p3, k);
						int sub1 = 0;
						for (int i = 0; i < (int)strlen(ans[k]); i++) {
							if (ans[k][i] == '#') {
								sub1++;
								my3++;
							}
						}
						printf("sub1 %d\n", sub1);
					}
					dup2(fd, 1);
					printf("***ans: %lld\n", my3); exit(0);
						
				default:	
					printf("NOT YET impl 3s of %d\n", numSq); exit(0);
					
			}
		}
		strcpy(startG, realAns);
		strcpy(start, realAns);
		for (int i = 0; i < numSq; i++) {
			strcpy(ans[i], "");
		}
	}

	printf("leaving s2\n"); getchar();
	printf("start is [%s]\n", start);
	{ 
		//printStartHashes(start);
	}

}
void s(char startIn[]) {
	char start[900];
	//strcpy(startG, ".#...####");
	strcpy(start, startIn);
	for (int t = 0; t < 3; t++) {
		strcpy(ans[0], "");
		{ 
			printf("start is %s\n len:(%d) t: %d", start, (int)strlen(start), t);
			printStartHashes(start);
		}

		int numSq;
		if (((int)sqrt(strlen(start)) % 2) == 0) {
			assert((int)strlen(start)%4 == 0);
			int posAdder = -4;
			numSq = (int)strlen(start) / 4;
			switch (numSq) {
				case 16:
				case 1:
					printf("not used...\n"); exit(0);
					
				case 4:
				case 9:
				case 36:
				case 81:
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/4 == numSq);
						char p2[6] = ""; posAdder+=4;
						p2[0] = start[posAdder+0]; p2[1] = start[posAdder+1]; p2[2] = start[posAdder+2]; p2[3] = start[posAdder+3];
						p2[4] = '\0';
						convTwo(p2, k, numSq);
					}
					genRealAns(2, numSq);
					break;
				default:
					printf("not impl.2 of .%d.\n", numSq); exit(0);
			}
				

		} else { //the threes
			numSq = (int)strlen(start) / 9;
			int posAdder = -9;
			assert((int)strlen(start) %9 == 0);
			switch (numSq) {
				case 4:
					printf("no imp 3s (%d)..\n", numSq); exit(0);
				case 1:
				case 9:
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/9 == numSq);
						char p3[11] = ""; posAdder += 9;

						p3[0] = start[posAdder+0];
						p3[1] = start[posAdder+1];
						p3[2] = start[posAdder+2];
						p3[3] = start[posAdder+3];
						p3[4] = start[posAdder+4];
						p3[5] = start[posAdder+5];
						p3[6] = start[posAdder+6];
						p3[7] = start[posAdder+7];
						p3[8] = start[posAdder+8];
						p3[9] = '\0';
						convThree(p3, k);
					}
					genRealAns(3, numSq);
					break;
				case 81:
					for (int k = 0; k < numSq; k++) {
						assert((int)strlen(start)/9 == numSq);
						char p3[11] = ""; posAdder += 9;

						p3[0] = start[posAdder+0];
						p3[1] = start[posAdder+1];
						p3[2] = start[posAdder+2];
						p3[3] = start[posAdder+3];
						p3[4] = start[posAdder+4];
						p3[5] = start[posAdder+5];
						p3[6] = start[posAdder+6];
						p3[7] = start[posAdder+7];
						p3[8] = start[posAdder+8];
						p3[9] = '\0';
						convEighty1(p3, k);
						printf("after convEighty1\n"); 
					}
					genRealAns(3, numSq);
					break;
					
				default:	
					printf("NOT YET impl 3s of %d\n", numSq); exit(0);
					
			}
		}
		strcpy(startG, realAns);
		strcpy(start, realAns);
		for (int i = 0; i < numSq; i++) {
			strcpy(ans[i], "");
		}
	}

	printf("start is [%s]\n", start);
	{ 
		printStartHashes(start);
	}
	strcpy(eighty1s[eighty1sPos].frm, startIn);
	strcpy(eighty1s[eighty1sPos++].to, start);
	
}
int HASH;
void printStartHashes(char start[])
{
	int mytot = 0; printf("ans[i]s is\n"); 

	for (int i = 0; i < (int)strlen(start); i++) { if (start[i] == '#') { mytot++; } }
	printf("Start: \n%s\n HASH: %d\n", start, mytot); 
	HASH = mytot;
}
	
void printAnsAndHashes(int num, int size)
{
	return;
	int mytot = 0;
	printf("ans[i]s is\n"); 
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < (int)strlen(ans[j]); i++) { if (ans[j][i] == '#') { mytot++; } }
		printf("%s\n", ans[j]);
	}
	printf("sub getReal size: %d ----from %d ||| tot is %d\n", size, num, mytot);
	
	int mytotRealAns = 0;
	for (int i = 0; i < (int)strlen(realAns); i++) { if (realAns[i] == '#') { mytotRealAns++; } }
	assert(mytot == mytotRealAns);

	int sq = sqrt((int)strlen(realAns));
	int twos1 = 3;
	if ((int)strlen(realAns) % 2 == 0) {
		twos1 = 2;
	}
        printf("\x1b[2J");
        printf("\x1b[HZ After Conversion of bottom to top\n");
	int yMax = 0;
	int pos = 0;
	for (int y = 0; y < sq/twos1; y++) {
		for (int x = 0; x < sq/twos1; x++) {

			for (int y1 = 0; y1 < twos1; y1++) {
	                        yMax = ((y*4)+2+y1);
                		printf("\x1b[HZ");
				if (twos1 == 3) {
	                        	printf("\x1b[%dB", ((y*4)+2+y1));
                        		printf("\x1b[%dC", x*5);
				} else {
	                        	printf("\x1b[%dB", ((y*3)+2+y1));    
                        		printf("\x1b[%dC", x*4);
				}
				for (int x1 = 0; x1 < twos1; x1++) {
					printf("%c", realAns[pos++]);
				}
			}
		}
	}
	for (int i = 0; i < twosPos; i++) {
                printf("\x1b[HZ");
                printf("\x1b[%dC", 60);
                printf("\x1b[%dB", 10+i);
		printf("[%s] -> [%s]", twos[i].frm, twos[i].to);
	}
	sq = sqrt((int)strlen(startG));
	twos1 = 3;
	if ((int)strlen(startG) % 2 == 0) {
		twos1 = 2;
	}
	pos = 0;
	for (int y = 0; y < sq/twos1; y++) {
		for (int x = 0; x < sq/twos1; x++) {

			for (int y1 = 0; y1 < twos1; y1++) {
                		printf("\x1b[HZ");
				if (twos1 == 3) {
	                        	printf("\x1b[%dB", yMax+((y*4)+2+y1));
                        		printf("\x1b[%dC", x*5);
				} else {
	                        	printf("\x1b[%dB", yMax+((y*3)+2+y1));
                        		printf("\x1b[%dC", x*4);
				}
				for (int x1 = 0; x1 < twos1; x1++) {
					printf("%c", startG[pos++]);
				}
			}
		}
	}
        printf("\n\n\n (%d) from:num %d ::size: %d", twos1, num, size);
	printf("\nDONE...\n\n");
}
	
void genRealAns(int num, int size) {
	strcpy(realAns, "");
	//CONOR
	if (size == 36) {
	int c1 = 0;
	for (int zz = 0; zz < size; zz++) {
		for (int i = 0; i < (int)strlen(ans[zz]); i++) {
			if (ans[zz][i] == '#') {
				c1++;
			}
		}
	}
	printf("c1 is %d num:%d size:%d\n", c1, num, size);
	dup2(fd, 1);
	printf("**ans: %d\n", c1);
	exit(0);
	}
	if (num == 2) {
		if (size == 81) {
			for (int p = 0; p < 81; p++) {
				strcat(realAns, ans[p]);
			}
			assert((int)strlen(realAns) == 81*9);
			printf("strlen(realAns) is %d\n", (int)strlen(realAns));
		} else if (size == 36) {
			{
	// 0.0 0.1 0.2  1.0 1.1 1.2  2.0 2.1 2.2  3.0 3.1 3.2  4.0 4.1 4.2  5.0 5.1 5.2
	// 0.3 0.4 0.5  1.3 1.4 1.5  2.3 2.4 2.5  3.3 3.4 3.5  4.3 4.4 4.5  5.3 5.4 5.5
	// 0.6 0.7 0.8  1.6 1.7 1.8  2.6 2.7 2.8  3.6 3.7 3.8  4.6 4.7 4.8  5.6 5.7 5.8
	// 6.0 
			}
			for (int i = 0; i < 3; i++) {
				realAns[(108*i)+0] = ans[(12*i)+0][0];
				realAns[(108*i)+1] = ans[(12*i)+0][1];
				realAns[(108*i)+2] = ans[(12*i)+0][3];
				realAns[(108*i)+3] = ans[(12*i)+0][4];

				realAns[(108*i)+4] = ans[(12*i)+0][2];
				realAns[(108*i)+5] = ans[(12*i)+1][0];
				realAns[(108*i)+6] = ans[(12*i)+0][5];
				realAns[(108*i)+7] = ans[(12*i)+1][3];

				realAns[(108*i)+8] = ans[(12*i)+1][1];
				realAns[(108*i)+9]  = ans[(12*i)+1][2];
				realAns[(108*i)+10] = ans[(12*i)+1][4];
				realAns[(108*i)+11] = ans[(12*i)+1][5];

				realAns[(108*i)+12] = ans[(12*i)+2][0];
				realAns[(108*i)+13] = ans[(12*i)+2][1];
				realAns[(108*i)+14] = ans[(12*i)+2][3];
				realAns[(108*i)+15] = ans[(12*i)+2][4];

				realAns[(108*i)+16] = ans[(12*i)+2][2];
				realAns[(108*i)+17] = ans[(12*i)+3][0];
				realAns[(108*i)+18] = ans[(12*i)+2][5];
				realAns[(108*i)+19] = ans[(12*i)+3][3];
		
				realAns[(108*i)+20] = ans[(12*i)+3][1];
				realAns[(108*i)+21] = ans[(12*i)+3][2];
				realAns[(108*i)+22] = ans[(12*i)+3][4];
				realAns[(108*i)+23] = ans[(12*i)+3][5];

				realAns[(108*i)+24] = ans[(12*i)+4][0];
				realAns[(108*i)+25] = ans[(12*i)+4][1];
				realAns[(108*i)+26] = ans[(12*i)+4][3];
				realAns[(108*i)+27] = ans[(12*i)+4][4];

				realAns[(108*i)+28] = ans[(12*i)+4][2];
				realAns[(108*i)+29] = ans[(12*i)+5][0];
				realAns[(108*i)+30] = ans[(12*i)+4][5];
				realAns[(108*i)+31] = ans[(12*i)+5][3];

				realAns[(108*i)+32] = ans[(12*i)+5][1];
				realAns[(108*i)+33] = ans[(12*i)+5][2];
				realAns[(108*i)+34] = ans[(12*i)+5][4];
				realAns[(108*i)+35] = ans[(12*i)+5][5];
	// 0.6 0.7 0.8  1.6 1.7 1.8  2.6 2.7 2.8  3.6 3.7 3.8  4.6 4.7 4.8  5.6 5.7 5.8
	// 6.0 6.1 6.2  7.0 7.1 7.2  8.0 8.1 8.2  9.0 9.1 9.2  10.0 10.1 10.2  11.0 11.1 11.2

				realAns[(108*i)+36] = ans[(12*i)+0][6];
				realAns[(108*i)+37] = ans[(12*i)+0][7];
				realAns[(108*i)+38] = ans[(12*i)+6][0];
				realAns[(108*i)+39] = ans[(12*i)+6][1];

				realAns[(108*i)+40] = ans[(12*i)+0][8];
				realAns[(108*i)+41] = ans[(12*i)+1][6];
				realAns[(108*i)+42] = ans[(12*i)+6][2];
				realAns[(108*i)+43] = ans[(12*i)+7][0];

				realAns[(108*i)+44] = ans[(12*i)+1][7];
				realAns[(108*i)+45] = ans[(12*i)+1][8];
				realAns[(108*i)+46] = ans[(12*i)+7][1];
				realAns[(108*i)+47] = ans[(12*i)+7][2];

				realAns[(108*i)+48] = ans[(12*i)+2][6];
				realAns[(108*i)+49] = ans[(12*i)+2][7];
				realAns[(108*i)+50] = ans[(12*i)+8][0];
				realAns[(108*i)+51] = ans[(12*i)+8][1];

				realAns[(108*i)+52] = ans[(12*i)+2][8];
				realAns[(108*i)+53] = ans[(12*i)+3][6];
				realAns[(108*i)+54] = ans[(12*i)+8][2];
				realAns[(108*i)+55] = ans[(12*i)+9][0];

				realAns[(108*i)+56] = ans[(12*i)+3][7];
				realAns[(108*i)+57] = ans[(12*i)+3][8];
				realAns[(108*i)+58] = ans[(12*i)+9][1];
				realAns[(108*i)+59] = ans[(12*i)+9][2];

				realAns[(108*i)+60] = ans[(12*i)+4][6];
				realAns[(108*i)+61] = ans[(12*i)+4][7];
				realAns[(108*i)+62] = ans[(12*i)+10][0];
				realAns[(108*i)+63] = ans[(12*i)+10][1];

				realAns[(108*i)+64] = ans[(12*i)+4][8];
				realAns[(108*i)+65] = ans[(12*i)+5][6];
				realAns[(108*i)+66] = ans[(12*i)+10][2];
				realAns[(108*i)+67] = ans[(12*i)+11][0];

				realAns[(108*i)+68] = ans[(12*i)+5][7];
				realAns[(108*i)+69] = ans[(12*i)+5][8];
				realAns[(108*i)+70] = ans[(12*i)+11][1];
				realAns[(108*i)+71] = ans[(12*i)+11][2];
	// 6.3 6.4 6.5  7.3 7.4 7.5  8.3 8.4 8.5  9.3 9.4 9.5  10.3 10.4 10.5  11.3 11.4 11.5
	// 6.6 6.7 6.8  7.6 7.7 7.8  8.6 8.7 8.8  9.6 9.7 9.8  10.6 10.7 10.8  11.6 11.7 11.8
				realAns[(108*i)+72] = ans[(12*i)+6][3];
				realAns[(108*i)+73] = ans[(12*i)+6][4];
				realAns[(108*i)+74] = ans[(12*i)+6][6];
				realAns[(108*i)+75] = ans[(12*i)+6][7];

				realAns[(108*i)+76] = ans[(12*i)+6][5];
				realAns[(108*i)+77] = ans[(12*i)+7][3];
				realAns[(108*i)+78] = ans[(12*i)+6][8];
				realAns[(108*i)+79] = ans[(12*i)+7][6];

				realAns[(108*i)+80] = ans[(12*i)+7][4];
				realAns[(108*i)+81] = ans[(12*i)+7][5];
				realAns[(108*i)+82] = ans[(12*i)+7][7];
				realAns[(108*i)+83] = ans[(12*i)+7][8];

				realAns[(108*i)+84] = ans[(12*i)+8][3];
				realAns[(108*i)+85] = ans[(12*i)+8][4];
				realAns[(108*i)+86] = ans[(12*i)+8][6];
				realAns[(108*i)+87] = ans[(12*i)+8][7];

				realAns[(108*i)+88] = ans[(12*i)+8][5];
				realAns[(108*i)+89] = ans[(12*i)+9][3];
				realAns[(108*i)+90] = ans[(12*i)+8][8];
				realAns[(108*i)+91] = ans[(12*i)+9][6];

				realAns[(108*i)+92] = ans[(12*i)+9][4];
				realAns[(108*i)+93] = ans[(12*i)+9][5];
				realAns[(108*i)+94] = ans[(12*i)+9][7];
				realAns[(108*i)+95] = ans[(12*i)+9][8];

				realAns[(108*i)+96] = ans[(12*i)+10][3];
				realAns[(108*i)+97] = ans[(12*i)+10][4];
				realAns[(108*i)+98] = ans[(12*i)+10][6];
				realAns[(108*i)+99] = ans[(12*i)+10][7];

				realAns[(108*i)+100] = ans[(12*i)+10][5];
				realAns[(108*i)+101] = ans[(12*i)+11][3];
				realAns[(108*i)+102] = ans[(12*i)+10][8];
				realAns[(108*i)+103] = ans[(12*i)+11][6];

				realAns[(108*i)+104] = ans[(12*i)+11][4];
				realAns[(108*i)+105] = ans[(12*i)+11][5];
				realAns[(108*i)+106] = ans[(12*i)+11][7];
				realAns[(108*i)+107] = ans[(12*i)+11][8];
			}
			realAns[324] = '\0';
			printf("LAST strlen realAns %d\n", (int)strlen(realAns));
			assert((int)strlen(realAns) == 324);
			{ //==> 36 3x3 -> readying for 4x4
				printAnsAndHashes(num, size);
			}
		} else if (size == 9) {
			for (int p = 0; p < size; p++) {
				strcat(realAns, ans[p]);
			}
			assert((int)strlen(realAns) == 81);
			{// 9 3x3 ->  readying for 4x4
				printAnsAndHashes(num, size);
			}
		} else if (size == 4) {
			{
				// 4 - 3x3 => 
				// 0.0 0.1 0.2    1.0 1.1 1.2
				// 0.3 0.4 0.5    1.3 1.4 1.5
				// 0.6 0.7 0.8    1.6 1.7 1.8
											     
				// 2.0 2.1 2.2    3.0 3.1 3.2
				// 2.3 2.4 2.5    3.3 3.4 3.5
				// 2.6 2.7 2.8    3.6 3.7 3.8
			}
		
				realAns[0] = ans[0][0];
				realAns[1] = ans[0][1];
				realAns[2] = ans[0][3];
				realAns[3] = ans[0][4];

				realAns[4] = ans[0][2];
				realAns[5] = ans[1][0];
				realAns[6] = ans[0][5];
				realAns[7] = ans[1][3];

				realAns[8] = ans[1][1];
				realAns[9] = ans[1][2];
				realAns[10] = ans[1][4];
				realAns[11] = ans[1][5];

				realAns[12] = ans[0][6];
				realAns[13] = ans[0][7];
				realAns[14] = ans[2][0];
				realAns[15] = ans[2][1];

				realAns[16] = ans[0][8];
				realAns[17] = ans[1][6];
				realAns[18] = ans[2][2];
				realAns[19] = ans[3][0];

				realAns[20] = ans[1][7];
				realAns[21] = ans[1][8];
				realAns[22] = ans[3][1];
				realAns[23] = ans[3][2];

				realAns[24] = ans[2][3];
				realAns[25] = ans[2][4];
				realAns[26] = ans[2][6];
				realAns[27] = ans[2][7];

				realAns[28] = ans[2][5];
				realAns[29] = ans[3][3];
				realAns[30] = ans[2][8];
				realAns[31] = ans[3][6];

				realAns[32] = ans[3][4];
				realAns[33] = ans[3][5];
				realAns[34] = ans[3][7];
				realAns[35] = ans[3][8];
				
			realAns[36] = '\0';
			assert((int)strlen(realAns) == 36);
			{
				printAnsAndHashes(num, size);
			}
		} else {
			printf("EERROR\n"); exit(0);
		}
	} else if (num == 3) {
		if (size == 1) {
			{
				///1 4x4 -> 4  x 2x2
				//0 1 2 3              -> 0 1 4 5 2 3 6 7 
				//4 5 6 7                 8 9 12 13 10 11 14 15
				//8 9 10 11
				//12 13 14 15
			}
			realAns[0] = ans[0][0];
			realAns[1] = ans[0][1];
			realAns[2] = ans[0][4];
			realAns[3] = ans[0][5];
			realAns[4] = ans[0][2];
			realAns[5] = ans[0][3];
			realAns[6] = ans[0][6];
			realAns[7] = ans[0][7];

			realAns[8] = ans[0][8];
			realAns[9] = ans[0][9];
			realAns[10] = ans[0][12];
			realAns[11] = ans[0][13];
			realAns[12] = ans[0][10];
			realAns[13] = ans[0][11];
			realAns[14] = ans[0][14];
			realAns[15] = ans[0][15];
			realAns[16] = '\0';
			assert((int)strlen(realAns) == 16);
			{
				printAnsAndHashes(num, size);
			}
		} else if (size == 9) {
			{
				///9 x (4x4) => 36 (2x2)
				///      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15   0.0 0.1 0.2 0.3     1.0  1.1  1.2  1.3    2.0  2.1  2.2  2.3  
				///	16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31   0.4 0.5 0.6 0.7     1.4  1.5  1.6  1.7    2.4
				///	32 33 34 45 46 37 38 39 40 41 42 43 44 45 46 47   0.8 0.9 0.10 0.11   1.8  1.9  1.10 1.11
				///	48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63   0.12 0.13 0.14 0.5  1.12 1.13 1.14 1.15
				///	64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 
				///	80 81 82 83 84 85 86 87 88 89 90 91 91 93 94 95
				///	96 97 98 99 10 01 02 03 04 05 06 07 08 09 10 11
				///	12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 
				///	28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43
						     
			}
						     
			printf("THIS ONE\n"); 
			for (int i = 0; i < 3; i++) {
				realAns[(48*i)+0] = ans[(3*i)+0][0];
				realAns[(48*i)+1] = ans[(3*i)+0][1];
				realAns[(48*i)+2] = ans[(3*i)+0][4];
				realAns[(48*i)+3] = ans[(3*i)+0][5];

				realAns[(48*i)+4] = ans[(3*i)+0][2];
				realAns[(48*i)+5] = ans[(3*i)+0][3];
				realAns[(48*i)+6] = ans[(3*i)+0][6];
				realAns[(48*i)+7] = ans[(3*i)+0][7];

				realAns[(48*i)+8] = ans[(3*i)+1][0];
				realAns[(48*i)+9] = ans[(3*i)+1][1];
				realAns[(48*i)+10] = ans[(3*i)+1][4];
				realAns[(48*i)+11] = ans[(3*i)+1][5];

				realAns[(48*i)+12] = ans[(3*i)+1][2];
				realAns[(48*i)+13] = ans[(3*i)+1][3];
				realAns[(48*i)+14] = ans[(3*i)+1][6];
				realAns[(48*i)+15] = ans[(3*i)+1][7];

				realAns[(48*i)+16] = ans[(3*i)+2][0];
				realAns[(48*i)+17] = ans[(3*i)+2][1];
				realAns[(48*i)+18] = ans[(3*i)+2][4];
				realAns[(48*i)+19] = ans[(3*i)+2][5];

				realAns[(48*i)+20] = ans[(3*i)+2][2];
				realAns[(48*i)+21] = ans[(3*i)+2][3];
				realAns[(48*i)+22] = ans[(3*i)+2][6];
				realAns[(48*i)+23] = ans[(3*i)+2][7];

					//0.0  0.1  0.2  0.3      1.0 1.1 1.2 1.3      2.0 2.1 2.2 2.3
					//0.4  0.5  0.6  0.7      1.4 1.5 1.6 1.7      2.4 2.5 2.6 2.7
					//0.8  0.9  0.10 0.11     1.8 1.9 1.10 1.11    2.8 2.9 2.10 2.11
					//0.12 0.13 0.14 0.15     1.12 1.13 1.14 1.15  2.12 2.13 2.14 2.15

				realAns[(48*i)+24] = ans[(3*i)+0][8];
				realAns[(48*i)+25] = ans[(3*i)+0][9];
				realAns[(48*i)+26] = ans[(3*i)+0][12];
				realAns[(48*i)+27] = ans[(3*i)+0][13];

				realAns[(48*i)+28] = ans[(3*i)+0][10];
				realAns[(48*i)+29] = ans[(3*i)+0][11];
				realAns[(48*i)+30] = ans[(3*i)+0][14];
				realAns[(48*i)+31] = ans[(3*i)+0][15];

				realAns[(48*i)+32] = ans[(3*i)+1][8];
				realAns[(48*i)+33] = ans[(3*i)+1][9];
				realAns[(48*i)+34] = ans[(3*i)+1][12];
				realAns[(48*i)+35] = ans[(3*i)+1][13];

				realAns[(48*i)+36] = ans[(3*i)+1][10];
				realAns[(48*i)+37] = ans[(3*i)+1][11];
				realAns[(48*i)+38] = ans[(3*i)+1][14];
				realAns[(48*i)+39] = ans[(3*i)+1][15];

				realAns[(48*i)+40] = ans[(3*i)+2][8];
				realAns[(48*i)+41] = ans[(3*i)+2][9];
				realAns[(48*i)+42] = ans[(3*i)+2][12];
				realAns[(48*i)+43] = ans[(3*i)+2][13];

				realAns[(48*i)+44] = ans[(3*i)+2][10];
				realAns[(48*i)+45] = ans[(3*i)+2][11];
				realAns[(48*i)+46] = ans[(3*i)+2][14];
				realAns[(48*i)+47] = ans[(3*i)+2][15];
			}
			realAns[144] = '\0';
			printf("%d\n", (int)strlen(realAns));
			assert((int)strlen(realAns) == 144);
			{
				printAnsAndHashes(num, size);
			}
		} else {
			printf("%d\n", (int)strlen(ans[0]));
			printf("size: %d\n", size);
			printf("tot %d\n", size*(int)strlen(ans[0]));
			for (int p = 0; p < size; p++) {
				strcat(realAns, ans[p]);
			}
			assert((int)strlen(realAns) == 81*729);
		}

	} else {
		printf("ERRROR unk2\n"); exit(0);
	}		

}
void genallThrees() {
	struct twosandthrees_s fl[4000];
	int flPos = 0;
	for (int i = 0; i < threesPos; i++) {
		printf("three %d is [%s]\n", i, threes[i].frm);

		for (int k = 0; k < 4; k++) { //rotate
			if (k == 0) {
				fl[flPos].frm[0] = threes[i].frm[0];
				fl[flPos].frm[1] = threes[i].frm[1];
				fl[flPos].frm[2] = threes[i].frm[2];
				fl[flPos].frm[3] = threes[i].frm[3];
				fl[flPos].frm[4] = threes[i].frm[4];
				fl[flPos].frm[5] = threes[i].frm[5];
				fl[flPos].frm[6] = threes[i].frm[6];
				fl[flPos].frm[7] = threes[i].frm[7];
				fl[flPos].frm[8] = threes[i].frm[8];
				fl[flPos].frm[9] = '\0';
				strcpy(fl[flPos].to, threes[i].to);
				strcpy(fl[flPos].orig, threes[i].frm);
				flPos++;
			} else if (k == 1) {
				fl[flPos].frm[6] = threes[i].frm[0];
				fl[flPos].frm[3] = threes[i].frm[1];
				fl[flPos].frm[0] = threes[i].frm[2];
				fl[flPos].frm[7] = threes[i].frm[3];
				fl[flPos].frm[4] = threes[i].frm[4];
				fl[flPos].frm[1] = threes[i].frm[5];
				fl[flPos].frm[8] = threes[i].frm[6];
				fl[flPos].frm[5] = threes[i].frm[7];
				fl[flPos].frm[2] = threes[i].frm[8];
				fl[flPos].frm[9] = '\0';
				strcpy(fl[flPos].to, threes[i].to);
				strcpy(fl[flPos].orig, threes[i].frm);
				flPos++;
			} else if (k == 2) {
				fl[flPos].frm[8] = threes[i].frm[0];
				fl[flPos].frm[7] = threes[i].frm[1];
				fl[flPos].frm[6] = threes[i].frm[2];
				fl[flPos].frm[5] = threes[i].frm[3];
				fl[flPos].frm[4] = threes[i].frm[4];
				fl[flPos].frm[3] = threes[i].frm[5];
				fl[flPos].frm[2] = threes[i].frm[6];
				fl[flPos].frm[1] = threes[i].frm[7];
				fl[flPos].frm[0] = threes[i].frm[8];
				fl[flPos].frm[9] = '\0';
				strcpy(fl[flPos].to, threes[i].to);
				strcpy(fl[flPos].orig, threes[i].frm);
				flPos++;
				
			} else if (k == 3) {
				fl[flPos].frm[2] = threes[i].frm[0];
				fl[flPos].frm[5] = threes[i].frm[1];
				fl[flPos].frm[8] = threes[i].frm[2];
				fl[flPos].frm[1] = threes[i].frm[3];
				fl[flPos].frm[4] = threes[i].frm[4];
				fl[flPos].frm[7] = threes[i].frm[5];
				fl[flPos].frm[0] = threes[i].frm[6];
				fl[flPos].frm[3] = threes[i].frm[7];
				fl[flPos].frm[6] = threes[i].frm[8];
				fl[flPos].frm[9] = '\0';
				strcpy(fl[flPos].to, threes[i].to);
				strcpy(fl[flPos].orig, threes[i].frm);
				flPos++;

			}
	
			int mypos1 = flPos-1;
			{ //flip across vert line
				fl[flPos].frm[2] = fl[mypos1].frm[0];
				fl[flPos].frm[1] = fl[mypos1].frm[1];
				fl[flPos].frm[0] = fl[mypos1].frm[2];
				fl[flPos].frm[5] = fl[mypos1].frm[3];
				fl[flPos].frm[4] = fl[mypos1].frm[4];
				fl[flPos].frm[3] = fl[mypos1].frm[5];
				fl[flPos].frm[8] = fl[mypos1].frm[6];
				fl[flPos].frm[7] = fl[mypos1].frm[7];
				fl[flPos].frm[6] = fl[mypos1].frm[8];
				fl[flPos].frm[9] = '\0';
				strcpy(fl[flPos].to, threes[i].to);
				strcpy(fl[flPos].orig, threes[i].frm);
				flPos++;
			}
			{ //flip across horiz line
				fl[flPos].frm[6] = fl[mypos1].frm[0];
				fl[flPos].frm[7] = fl[mypos1].frm[1];
				fl[flPos].frm[8] = fl[mypos1].frm[2];
				fl[flPos].frm[3] = fl[mypos1].frm[3];
				fl[flPos].frm[4] = fl[mypos1].frm[4];
				fl[flPos].frm[5] = fl[mypos1].frm[5];
				fl[flPos].frm[0] = fl[mypos1].frm[6];
				fl[flPos].frm[1] = fl[mypos1].frm[7];
				fl[flPos].frm[2] = fl[mypos1].frm[8];
				fl[flPos].frm[9] = '\0';
				strcpy(fl[flPos].to, threes[i].to);
				strcpy(fl[flPos].orig, threes[i].frm);
				flPos++;
			}
		}
		
	}
	printf("flPos: %d\n", flPos);

	struct twosandthrees_s fl2[4000];
	int fl2Pos = 0;
	for (int j = 0; j < flPos; j++) {
		int found = 0;
		for (int i = 0; i < fl2Pos; i++) {
			if (strcmp(fl[j].frm, fl2[i].frm) ==0 && strcmp(fl[j].to, fl2[i].to) == 0) {
				found = 1; break;
			}
		}
		if (found == 0) {
			strcpy(fl2[fl2Pos].frm, fl[j].frm);
			strcpy(fl2[fl2Pos].to,  fl[j].to);
			strcpy(fl2[fl2Pos].orig,  fl[j].orig);
			fl2Pos++;
		}
		
	}
	printf("ff2Pos is %d\n", fl2Pos); 
	//threesPos = 0;
	for (int j = 0; j < fl2Pos; j++) {
		int found = 0;
		for (int i = 0; i < threesPos; i++) {
			if (strcmp(fl2[j].frm, threes[i].frm) ==0 /*&& strcmp(fl2[j].to, threes[i].to) == 0*/) {
				found = 1; break;
			}
		}
		if (found == 0) {
			strcpy(threes[threesPos].frm, fl2[j].frm);
			strcpy(threes[threesPos].to, fl2[j].to);
			strcpy(threes[threesPos].orig, fl2[j].orig);
			threesPos++;
		}
	}
	for (int i = 0; i < twosPos; i++) {
		int found  = 0;
		for (int j = 0; j < threesPos; j++) {
			if (strcmp(twos[i].to, threes[j].frm) == 0) {
				found++;
			}
		}
		if (found > 1) {
			printf("[[%s]]---->[[[%s]]] (%d)   ===>\n ", twos[i].frm, twos[i].to, found); 
			for (int k = 0; k < threesPos; k++) {
				if (strcmp(twos[i].to, threes[k].frm) == 0) {
					printf("	[[%s]]-->[[%s]] (ORIG: [((%s))]\n", threes[k].frm, threes[k].to, threes[k].orig);
				}
			}
		}
	}
		
	printf("threesPos: %d\n", threesPos);
printf("--------------------\n");
	for (int i = 0; i < threesPos; i++) {
		printf("%s == > %s\n", threes[i].frm, threes[i].to);
	} 
getchar();
printf("--------------------\n");

/*
	printf("calling s\n"); fflush(stdout);
	{
		strcpy(startG, ".#...####");
		s(startG);

	}
*/
	for (int i = 0; i < threesPos; i++) {
		s(threes[i].frm);
	}

	
	for (int i = 0; i < eighty1sPos; i++) {
		printf("%s ----> %s\n", eighty1s[i].frm, eighty1s[i].to);
	}
	strcpy(startG, ".#...####");
	convEighty1(startG, 0);
	printf("calling s2\n");
	s2(ans[0]);
	//s3(realAns);
}

void genallTwos() {
	struct twosandthrees_s fl[2000];
	int flPos = 0;
	printf("twosPos is %d\n", twosPos);

	for (int i = 0; i < twosPos; i++) {

		for (int k = 0; k < 4; k++) { //rotate
			if (k == 0) {
				fl[flPos].frm[0] = twos[i].frm[0];
				fl[flPos].frm[1] = twos[i].frm[1];
				fl[flPos].frm[2] = twos[i].frm[2];
				fl[flPos].frm[3] = twos[i].frm[3];
				fl[flPos].frm[4] = '\0';
				strcpy(fl[flPos].to, twos[i].to);
				flPos++;
			} else if (k == 1) {                                   
				fl[flPos].frm[2] = twos[i].frm[0];             
				fl[flPos].frm[0] = twos[i].frm[1];   
				fl[flPos].frm[3] = twos[i].frm[2];          
				fl[flPos].frm[1] = twos[i].frm[3];         
				fl[flPos].frm[4] = '\0';
				strcpy(fl[flPos].to, twos[i].to);
				flPos++;
			} else if (k == 2) {	                           
				fl[flPos].frm[3] = twos[i].frm[0];         
				fl[flPos].frm[2] = twos[i].frm[1];        
				fl[flPos].frm[1] = twos[i].frm[2];       
				fl[flPos].frm[0] = twos[i].frm[3];
				fl[flPos].frm[4] = '\0';
				strcpy(fl[flPos].to, twos[i].to);
				flPos++;
			} else if (k == 3) {
				fl[flPos].frm[1] = twos[i].frm[0];          
				fl[flPos].frm[3] = twos[i].frm[1];         
				fl[flPos].frm[0] = twos[i].frm[2];
				fl[flPos].frm[2] = twos[i].frm[3];
				fl[flPos].frm[4] = '\0';
				strcpy(fl[flPos].to, twos[i].to);
				flPos++;
			}
			int mypos3 = flPos -1;
			{ //flip across vert line
				fl[flPos].frm[1] = fl[mypos3].frm[0];
				fl[flPos].frm[0] = fl[mypos3].frm[1];
				fl[flPos].frm[3] = fl[mypos3].frm[2];
				fl[flPos].frm[2] = fl[mypos3].frm[3];
				fl[flPos].frm[4] = '\0';
				strcpy(fl[flPos].to, twos[i].to);
				printf("flip to %s\n", fl[flPos].to);	
				flPos++;
			}
			{ //flip horiz line
				fl[flPos].frm[2] = fl[mypos3].frm[0];
				fl[flPos].frm[3] = fl[mypos3].frm[1];
				fl[flPos].frm[0] = fl[mypos3].frm[2];
				fl[flPos].frm[1] = fl[mypos3].frm[3];
				fl[flPos].frm[4] = '\0';
				strcpy(fl[flPos].to, twos[i].to);
			
				flPos++;
			}
		}	
	}

	for (int j = 0; j < flPos; j++) {
		int found = 0;
		for (int i = 0; i < twosPos; i++) {
			if (strcmp(fl[j].frm, twos[i].frm) == 0) {
				found = 1; break;
			}
		}
		if (found == 0 && (int)strlen(fl[j].frm) == 4 && (int)strlen(fl[j].to) == 9) {
			strcpy(twos[twosPos].frm,  fl[j].frm);
			strcpy(twos[twosPos].to,   fl[j].to);
			twosPos++;
		} else {
			if ((int)strlen(fl[j].frm) == 4 && (int)strlen(fl[j].to) == 9) {
				printf("ignoring %s -> %s\n", fl[j].frm, fl[j].to);
			}
		}
	}
	for (int i = 0; i < twosPos; i++) {
		printf("%s == > %s\n", twos[i].frm, twos[i].to); 
	} 
}

void convTwo(char frm[], int part, int size) {
	int found = 0;
	for (int i = 0; i < twosPos; i++) {
		if (strcmp(frm, twos[i].frm) == 0) {
			found++;
			strcpy(ans[part], twos[i].to); 

			//if (size == 36) { printf("[%s] ---->  [%s]\n", frm, ans[part]); getchar(); }
			break;
		}
	}
	assert(found == 1 || found == 0);
	if (found == 0) { printf("ERROR two (not found): [%s] (%d)\n", frm, part); exit(0); }
}

void convThree(char frm[], int part) {
	int found = 0;
	for (int i = 0; i < threesPos; i++) {
		if (strcmp(frm, threes[i].frm) == 0) {
			found++;
			strcpy(ans[part], threes[i].to); break;
		}
	}
	assert(found == 1 || found == 0);
	if (found == 0) { printf("ERROR three (not found) %s\n", frm); exit(0); }
}
void convEighty1(char frm[], int part) {
	int found = 0;
	for (int i = 0; i < eighty1sPos; i++) {
		if (strcmp(frm, eighty1s[i].frm) == 0) {
			found++;
			//printf("%s --> %s\n", frm, eighty1s[i].to); getchar();
			strcpy(ans[part], eighty1s[i].to); break;
		}
	}
	assert(found == 1 || found == 0);
	if (found == 0) { printf("ERROR eighty1 (not found) %s\n", frm); exit(0); }
}
