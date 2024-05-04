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
void convTwo  (char frm[100][100], char to[100][100], int frmWidth, int *toWidth);
//void convThree(char frm[100][100], char to[100][100], int frmWidth, int *toWidth);
void convThree(char frm[200]);
void genallTwos();
void genallThrees();
char ans[220];

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
	if (strlen(frm) == 5) {
		strcpy(twos[twosPos].frm, frm);
		strcpy(twos[twosPos].to, to);
		twosPos++;
	} else {
		strcpy(threes[threesPos].frm, frm);
		strcpy(threes[threesPos].to, to);
		threesPos++;
	}
	leny++;
}
fclose(a);
	genallTwos();
	printf("twosPos is %d\n", twosPos);
	genallThrees();
	printf("threesPos is %d\n", threesPos);

	char start[] = ".#...####";
	int parts = 1;
	for (int k = 0; k < parts; k++) {
		convThree(start);
	}
	return 0;
}

void genallThrees() {
	struct twosandthrees_s new[3100];
	int newPos = 0;
	for (int i = 0; i < threesPos; i++) {
		for (int k = 1; k < 11; k++) { //rotate
			new[newPos].frm[(k+0)%11] = threes[i].frm[0];
			new[newPos].frm[(k+1)%11] = threes[i].frm[1];
			new[newPos].frm[(k+2)%11] = threes[i].frm[2];
			new[newPos].frm[3] = threes[i].frm[3];
			new[newPos].frm[(k+4)%11] = threes[i].frm[4];
			new[newPos].frm[(k+5)%11] = threes[i].frm[5];
			new[newPos].frm[(k+6)%11] = threes[i].frm[6];
			new[newPos].frm[7] = threes[i].frm[7];
			new[newPos].frm[(k+8)%11] = threes[i].frm[8];
			new[newPos].frm[(k+9)%11] = threes[i].frm[9];
			new[newPos].frm[(k+10)%11] = threes[i].frm[10];

			strcpy(new[newPos].to, threes[i].to);
			
			newPos++;
		}	
	}

	for (int i = 0; i < threesPos; i++) { //flip vert
		new[newPos].frm[2] = threes[i].frm[0];
		new[newPos].frm[1] = threes[i].frm[1];
		new[newPos].frm[0] = threes[i].frm[2];
		new[newPos].frm[3] = threes[i].frm[3];
		new[newPos].frm[6] = threes[i].frm[4];
		new[newPos].frm[5] = threes[i].frm[5];
		new[newPos].frm[4] = threes[i].frm[6];
		new[newPos].frm[7] = threes[i].frm[7];
		new[newPos].frm[10] = threes[i].frm[8];
		new[newPos].frm[9] = threes[i].frm[9];
		new[newPos].frm[8] = threes[i].frm[10];

		strcpy(new[newPos].to, threes[i].to);
			
		newPos++;
	}
	for (int i = 0; i < threesPos; i++) { //flip hor
		new[newPos].frm[8] = threes[i].frm[0];
		new[newPos].frm[9] = threes[i].frm[1];
		new[newPos].frm[10] = threes[i].frm[2];
		new[newPos].frm[3] = threes[i].frm[3];
		new[newPos].frm[4] = threes[i].frm[4];
		new[newPos].frm[5] = threes[i].frm[5];
		new[newPos].frm[6] = threes[i].frm[6];
		new[newPos].frm[7] = threes[i].frm[7];
		new[newPos].frm[0] = threes[i].frm[8];
		new[newPos].frm[1] = threes[i].frm[9];
		new[newPos].frm[2] = threes[i].frm[10];

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
	struct twosandthrees_s new[100];
	int newPos = 0;
	for (int i = 0; i < twosPos; i++) {
		for (int k = 1; k < 5; k++) { //rotate
			new[newPos].frm[(k+0)%5] = twos[i].frm[0];
			new[newPos].frm[(k+1)%5] = twos[i].frm[1];
			new[newPos].frm[2] = twos[i].frm[2];//always
			new[newPos].frm[(k+3)%5] = twos[i].frm[3];
			new[newPos].frm[(k+4)%5] = twos[i].frm[4];
			strcpy(new[newPos].to, twos[i].to);
			
			newPos++;
		}	
	}

	for (int j = 0; j < newPos; j++) {
		int found = 0;
		for (int i = 0; i < twosPos; i++) {
			if (strcmp(new[j].frm, twos[i].frm) ==0) {
				found = 1; break;
			}
		}
		if (found == 0) {
			strcpy(twos[twosPos].frm, new[j].frm);
			strcpy(twos[twosPos++].to, new[j].to);
		}
	}
}
void convTwo(char frm[100][100], char to[100][100], int frmWidth, int *toWidth) {
	//char sfrm[10];
	//for (int k = 0; k < numTabs; k++) {
		//sfrm[0] = frm[(2*k)*0][(2*k)+0] sfrm[1] = frm[(2*k)+0][(2*k)+1] sfrm[2] = '/'; sfrm[3] = frm[(2*k)+1][(2*k)+0] sfrm[4] = frm[(2*k)+1][(2*k)+1] sfrm[5] = '\0';

	//	for (int i = 0; i < twoPos; i++) {
	//		if (strcmp(twos[i], sfrm) == 0) {
	//			
	//	}
	//}
}

//void convThree(char frm[100], char to[100], int frmWidth, int *toWidth) {
void convThree(char frm[100]) {
	for (int i = 0; i < threesPos; i++) {
		if (strcmp(frm, threes[i].frm) == 0) {
			strcpy(ans, threes[i].to);
		}
	}
}
