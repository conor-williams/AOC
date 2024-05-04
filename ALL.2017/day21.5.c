#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int tot = 0;
#define SIZE 200
char line1[SIZE];
int leny = 0;

char gf[100][100];
int gFWidth;
char gT[100][100];
int gTWidth;
//.#.
//..#
//###
void convTwo(char frm[]);
void convThree(char frm[]);
void genallTwos();
void genallThrees();
char ans[1000];

struct twosandthrees_s {
	char frm[100];
	char to[100];
};
struct twosandthrees_s twos[30];
int twosPos = 0;
struct twosandthrees_s threes[600];
int threesPos = 0;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); printf("2017 Day9.1\n"); fflush(stdout);


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
		twosPos++;
	} else {
		strcpy(threes[threesPos].frm, frmx);
		strcpy(threes[threesPos].to, toy);
		threesPos++;
	}
	leny++;
}
fclose(a);
	genallTwos();
	printf("twosPos is %d\n", twosPos);
	printf("bef threesPos is %d\n", threesPos);
	genallThrees();
	printf("threesPos is %d\n", threesPos);

	char start[500] = ".#...####";

	for (int t = 0; t < 5; t++) {
		strcpy(ans, "");
		printf("start is %s\n", start);
		if (strlen(start) % 4 == 0) {
			int row1;
			for (int k = 0; k < ((int)strlen(start) / 4); k++) {
				char p2[100];
				int rowNum = 0;
				int numSq = (int)strlen(start) / 4;
				if (numSq == 1) {
					p2[0] = start[0];
					p2[1] = start[1];
					p2[2] = start[2];
					p2[3] = start[3];
					p2[4] = '\0';
					convTwo(p2);
				} else if (numSq == 4) {
					printf("		tested sq 4 of 2s\n");
					//0 1 4 5 
					//2 3 6 7 
					//8 9 12 13
					//10 11 14 15
	
					if (k < 2) { 
						rowNum = 0;
					} else if (k >= 2) {
						rowNum = 1;
					}
					p2[0] = start[(k*2)+0+(rowNum*4)];
					p2[1] = start[(k*2)+1+(rowNum*4)];
					p2[2] = start[(k*2)+2+(rowNum*4)+(int)sqrt(numSq)];
					p2[3] = start[(k*2)+3+(rowNum*4)+(int)sqrt(numSq)];

					p2[4] = '\0';
					printf("just after (%d): p2 is [%s]\n", k, p2);
					convTwo(p2);
				} else if (numSq == 9) {
					printf("**		to test nine of 2s...\n");
/*
					0 1 6 7
					2 3 8 9
					4 5 10 11
					
					12 13 18 19 
					14 15 20 21
					16 17 22 23
					
					24 25 30 31
					26 27 32 33
					28 29 34 35

*/
					if (k >= 6) { 
						row1 = 6;
					} else if (k >= 3) {
						row1 = 3;
					} else {
						row1 = 0;
					}
					p2[0] = start[(row1*2)+(k*2)+0];
					p2[1] = start[(row1*2)+(k*2)+1];
					p2[2] = start[((row1+1)*2)+(k*2)+4];
					p2[3] = start[((row1+1)*2)+(k*2)+5];

					p2[4] = '\0';
					convTwo(p2);
				} else if (numSq == 16) {
					printf("not implemented yet\n"); getchar();
				} else if (numSq == 36) { 
					printf("		to test 36 of 2s\n");
					//0 1 , 12 13
					//2 3 , 14 15
					//4 5 , 16 17
					//6 7, 18 19
					//8 9, 20 21
					//10 11, 22 23

					// 24 etc + 24

					if (k == 30) {
						row1 = 120;
					} else if (k == 24) {
						row1 = 96;
					} else if (k == 18) {
						row1 = 72;
					} else if (k == 12) {
						row1 = 48;
					} else if (k == 6) {
						row1 = 24;
					} else if (k == 0) {
						row1 = 0;
					} else {
						row1 = row1+2;
					}
					p2[0] = start[row1+0];
					p2[1] = start[row1+1];
					p2[2] = start[row1+12];
					p2[3] = start[row1+13];

					p2[4] = '\0';
					convTwo(p2);
				
				}
			}
		} else {
			int numSq = (int)strlen(start) / 9;
			for (int k = 0; k < ((int)strlen(start))/9; k++) {
				if (numSq == 1) {
					printf("tested 1s of 3s\n");
					convThree(start);
				} else if (numSq == 4) {
					printf("		to test sq 4 of 3s\n");
					// 0 1 2,   6 7 8, 12 13 14
					// 3 4 5, 9 10 11, 15 16 17
					// 18 19 20 24 25 26 30 31 32
					// 21 22 23 27 28 29 33 34 45
					int row1;
					if (k == 3) { 
						row1 = 21;
					} else if (k == 2) { 
						row1 = 18;
					} else if (k == 1) {
						row1 = 3;
					} else {
						row1 = 0;
					}

					char p3[100];
					p3[0] = start[(row1)+0];
					p3[1] = start[(row1)+1];
					p3[2] = start[(row1)+2];
					p3[4] = start[(row1)+6];
					p3[5] = start[(row1)+7];
					p3[6] = start[(row1)+8];
					p3[7] = start[(row1)+12];
					p3[8] = start[(row1)+13];
					p3[8] = start[(row1)+14];
					p3[9] = '\0';
					convThree(p3);
				} else if (numSq == 9) {
					printf("		to test sq 9 of 3s\n");
					// 0 1 2 ,   9 10 11, 18 19 20
					// 3 4 5 , 12, 13 14, 21 22 23
					// 6 7 8, 15, 16, 17, 24 25 26

					// 27 28 29, 
					// 30 31 32,
					// 33 34 35,
	
					// 54 55 56,
					// 57 58 59,
					// 60 61 62,                 80
					int row1;
					if (k == 8) { 
						row1 = 60;
					} else if (k == 7) {
						row1 = 57;
					} else if (k == 6) {
						row1 = 54;
					} else if (k == 5) {
						row1 = 33;
					} else if (k == 4) {
						row1 = 30;
					} else if (k == 3) {
						row1 = 27;
					} else if (k == 2) {
						row1 = 6;
					} else if (k == 1) {
						row1 = 3;
					} else {
						row1 = 0;
					}

					char p3[100];
					p3[0] = start[(row1)+0];
					p3[1] = start[(row1)+1];
					p3[2] = start[(row1)+2];
					p3[4] = start[(row1)+9];
					p3[5] = start[(row1)+10];
					p3[6] = start[(row1)+11];
					p3[7] = start[(row1)+18];
					p3[8] = start[(row1)+19];
					p3[8] = start[(row1)+20];
					p3[9] = '\0';
					convThree(p3);
				} else {
					printf("NOT YET\n");
				}
			
			}
		}
		strcpy(start, ans);
		strcpy(ans, "");
		getchar();
	}
	printf("start is [%s]\n", start);
	int mytot = 0; for (int i = 0; i < (int)strlen(start); i++) { if (start[i] == '#') { mytot++; } }		
	printf("**mytot is %d\n", mytot); getchar();
		
}

void genallThrees() {
	struct twosandthrees_s new[3100];
	int newPos = 0;
	for (int i = 0; i < threesPos; i++) {
		for (int k = 1; k < 9; k++) { //rotate
			new[newPos].frm[4] = threes[i].frm[4];
			if (k == 1) {
				new[newPos].frm[(1+0)%9] = threes[i].frm[0];
				new[newPos].frm[(1+1)%9] = threes[i].frm[1];
				new[newPos].frm[(1+4)%9] = threes[i].frm[2];
				new[newPos].frm[(1+8)%9] = threes[i].frm[3];
				new[newPos].frm[(1+7)%9] = threes[i].frm[5];
				new[newPos].frm[(1+2)%9] = threes[i].frm[6];
				new[newPos].frm[(1+5)%9] = threes[i].frm[7];
				new[newPos].frm[(1+6)%9] = threes[i].frm[8];
				new[newPos].frm[9] = '\0';
				strcpy(new[newPos].to, threes[i].to);
				newPos++;
			} else {
				new[newPos].frm[(1+0)%9] = new[newPos-1].frm[0];
				new[newPos].frm[(1+1)%9] = new[newPos-1].frm[1];
				new[newPos].frm[(1+4)%9] = new[newPos-1].frm[2];
				new[newPos].frm[(1+8)%9] = new[newPos-1].frm[3];
				new[newPos].frm[(1+7)%9] = new[newPos-1].frm[5];
				new[newPos].frm[(1+2)%9] = new[newPos-1].frm[6];
				new[newPos].frm[(1+5)%9] = new[newPos-1].frm[7];
				new[newPos].frm[(1+6)%9] = new[newPos-1].frm[8];
				new[newPos].frm[9] = '\0';
				strcpy(new[newPos].to, threes[i].to);
				newPos++;
				
			}
		}	
	}

	for (int i = 0; i < threesPos; i++) { //flip vert
		new[newPos].frm[2] = threes[i].frm[0];
		new[newPos].frm[1] = threes[i].frm[1];
		new[newPos].frm[0] = threes[i].frm[2];
		new[newPos].frm[5] = threes[i].frm[3];
		new[newPos].frm[4] = threes[i].frm[4];
		new[newPos].frm[3] = threes[i].frm[5];
		new[newPos].frm[8] = threes[i].frm[6];
		new[newPos].frm[7] = threes[i].frm[7];
		new[newPos].frm[6] = threes[i].frm[8];

		new[newPos].frm[9] = '\0';

		strcpy(new[newPos].to, threes[i].to);
			
		newPos++;
	}
	for (int i = 0; i < threesPos; i++) { //flip hor
		new[newPos].frm[6] = threes[i].frm[0];
		new[newPos].frm[7] = threes[i].frm[1];
		new[newPos].frm[8] = threes[i].frm[2];
		new[newPos].frm[3] = threes[i].frm[3];
		new[newPos].frm[4] = threes[i].frm[4];
		new[newPos].frm[5] = threes[i].frm[5];
		new[newPos].frm[0] = threes[i].frm[6];
		new[newPos].frm[1] = threes[i].frm[7];
		new[newPos].frm[2] = threes[i].frm[8];

		new[newPos].frm[9] = '\0';

		strcpy(new[newPos].to, threes[i].to);
			
		newPos++;
	}

	printf("newPos is %d\n", newPos);
	for (int j = 0; j < newPos; j++) {
		int found = 0;
		for (int i = 0; i < threesPos; i++) {
			if (strcmp(new[j].frm, threes[i].frm) ==0) {
				found = 1; break;
			}
		}
		if (found == 0) {
			strcpy(threes[threesPos].frm, new[j].frm);
			strcpy(threes[threesPos++].to, new[j].to);
		}
	}
}

void genallTwos() {
	struct twosandthrees_s new[500];
	int newPos = 0;
	printf("twosPos is %d\n", twosPos);
	for (int i = 0; i < twosPos; i++) {
		printf("twos[%d] is [%s]\n", i, twos[i].frm); getchar();
		for (int k = 1; k < 4; k++) { //rotate
			new[newPos].frm[(k+0)%4] = twos[i].frm[0];
			new[newPos].frm[(k+2)%4] = twos[i].frm[1];
			new[newPos].frm[(k+3)%4] = twos[i].frm[2];
			new[newPos].frm[(k+1)%4] = twos[i].frm[3];
			new[newPos].frm[4] = '\0';
			strcpy(new[newPos].to, twos[i].to);
			if (i == 2) {
				printf("new[%d] is [%s]\n", k, new[newPos].frm); getchar();
			}
			newPos++;
		}	
	}
	for (int i = 0; i < twosPos; i++) { //flip
		new[newPos].frm[1] = twos[i].frm[0];
		new[newPos].frm[0] = twos[i].frm[1];
		new[newPos].frm[3] = twos[i].frm[2];
		new[newPos].frm[2] = twos[i].frm[3];
		new[newPos].frm[4] = '\0';
		strcpy(new[newPos].to, twos[i].to);
		
		newPos++;
	}

	for (int i = 0; i < twosPos; i++) { //flip
		new[newPos].frm[2] = twos[i].frm[0];
		new[newPos].frm[3] = twos[i].frm[1];
		new[newPos].frm[0] = twos[i].frm[2];
		new[newPos].frm[1] = twos[i].frm[3];
		new[newPos].frm[4] = '\0';
		strcpy(new[newPos].to, twos[i].to);
		
		newPos++;
	}
	for (int j = 0; j < newPos; j++) {
		int found = 0;
		for (int i = 0; i < twosPos; i++) {
			if (strcmp(new[j].frm, twos[i].frm) == 0) {
				found = 1; break;
			}
		}
		if (found == 0) {
			strcpy(twos[twosPos].frm,  new[j].frm);
			strcpy(twos[twosPos++].to, new[j].to);
		}
	}
}

void convTwo(char frm[]) {
	int found = 0;
	for (int i = 0; i < twosPos; i++) {
		if (strcmp(frm, twos[i].frm) == 0) {
			found = 1;
			strcat(ans, twos[i].to); break;
		}
	}
	if (found == 0) {
		printf("ERROR two (not found)\n"); exit(0);
	}
}

void convThree(char frm[]) {
	int found = 0;
	for (int i = 0; i < threesPos; i++) {
		//printf("comparing %s V %s\n", frm, threes[i].frm);
		if (strcmp(frm, threes[i].frm) == 0) {
			found = 1;
			strcat(ans, threes[i].to); break;
		}
	}
	if (found == 0) {
		printf("ERROR three (not found)\n"); exit(0);
	}
}
