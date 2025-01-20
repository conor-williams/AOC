#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

int tot = 0;
#define SIZE 400
char line1[SIZE];
int leny = 0;

//.#.
//..#
//###

void convTwo(char frm[], int size);
void convThree(char frm[], int size);
void genallTwos();
void genallThrees();
char ans[300][50];
void genRealAns(int num, int size);
char realAns[500];

struct twosandthrees_s {
	char frm[100];
	char to[100];
};

struct twosandthrees_s twos[300];
int twosPos = 0;
struct twosandthrees_s threes[2000];
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

	char frm[200], to[200];
	sscanf(line1, "%s => %s", frm, to);
	int x = 0; char frmx[200];
	for (int i = 0; i < (int)strlen(frm); i++) {
		if (frm[i] == '/') {
		} else {
			frmx[x++] = frm[i];
		}
	}
	frmx[x] = '\0';
	int y = 0; char toy[200];
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

	char start[2000] = ".#...####";

	for (int t = 0; t < 5; t++) {
		strcpy(ans[0], "");
		strcpy(ans[1], "");
		strcpy(ans[2], "");
		printf("start is %s\n len:(%d)", start, (int)strlen(start));
		int mytot = 0; for (int i = 0; i < (int)strlen(start); i++) { if (start[i] == '#') { mytot++; } }
		printf("Interim : mytot is %d\n", mytot);
		if (strlen(start) % 2 == 0) {
			int numSq = (int)strlen(start) / 4;
			if (numSq == 1) {
				printf("NOT USED\n");
				char p2[10] = "";
				p2[0] = start[0];
				p2[1] = start[1];
				p2[2] = start[2];
				p2[3] = start[3];
				p2[4] = '\0';
				convTwo(p2, 0);
			} else if (numSq == 4) {
				printf("		tested sq 4 of 2s\n");
				int row1;
				for (int k = 0; k < ((int)strlen(start) / 4); k++) {
					assert((int)strlen(start)/4 == 4);
					char p2[10] = "";
					//0 1 4 5 
					//2 3 6 7 
					//8 9 12 13
					//10 11 14 15
	
					if (k == 0) {
						row1 = 0;
					} else if (k == 2) {
						row1 = 8;
					} else {
						row1+=2;
					}

					p2[0] = start[row1+0];
					p2[1] = start[row1+1];
					p2[2] = start[row1+4];
					p2[3] = start[row1+5];

					p2[4] = '\0';
					//printf("just after (%d): p2 is [%s]\n", k, p2);
					convTwo(p2, k);
				}
				genRealAns(2, 4);
			} else if (numSq == 9) {
				printf("**		to test nine of 2s...\n");
/*
				0 1  4 5  8 9        0 1 2 3 4 5
				2 3  6 7  10 11      6 7 8 9 10 11
						    
				12 13 16 17         
				14 15 20 21         
				16 17 22 23
				
				24 25 30 31
				26 27 32 33
				28 29 34 35

*/
				int row1;
				for (int k = 0; k < ((int)strlen(start) / 4); k++) {
					assert((int)strlen(start)/4 == 9);
					char p2[10] = "";
					if (k == 6) {
						row1 = 24;
					} else if (k == 3) {
						row1 = 12;
					} else if (k == 0) {
						row1 = 0;
					} else {
						row1 += 2;
					}

					p2[0] = start[row1+0];
					p2[1] = start[row1+1];
					p2[2] = start[row1+6];
					p2[3] = start[row1+7];
					if (k == 8) {assert(row1+7 == 35);}
					p2[4] = '\0';
					convTwo(p2, k);
				}
				genRealAns(2, 9);
			} else if (numSq == 16) {
				printf("not implemented yet\n"); getchar();
			} else if (numSq == 36) { 
				printf("		to test 36 of 2s\n");
			//abc jkl stu      abcd qrst efgh
			//def mno vwx  =>  efgh uvwx...
		//			   ijkl yzzz
			//ghi pqr yza      mnop abcd
				//0 1 , 12 13
				//2 3 , 14 15
				//4 5 , 16 17
				//6 7, 18 19
				//8 9, 20 21
				//10 11, 22 23

				// 24 etc + 24
				int row1;
				for (int k = 0; k < ((int)strlen(start) / 4); k++) {
					assert((int)strlen(start)/4 == 36);
					char p2[10] = "";

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
						row1 += 2;
					}
					p2[0] = start[row1+0];
					p2[1] = start[row1+1];
					p2[2] = start[row1+12];
					p2[3] = start[row1+13];

					if (k == 35) {assert(row1+13 == 143);}
					p2[4] = '\0';
					convTwo(p2, k);
				}
				genRealAns(2, 36);
			
			}
		} else { //the threes
			int numSq = (int)strlen(start) / 9;
			if (numSq == 1) {
				printf("tested 1s of 3s\n");
				convThree(start, 0);
				genRealAns(3, 1);
			} else if (numSq == 4) {
				printf("no imp\n"); exit(0);
			} else if (numSq == 9) {
				printf("**		to test sq 9 of 3s\n");
				// 0 1 2 ,  9 10 11, 18 19 20
				// 3 4 5 , 12 13 14, 21 22 23
				// 6 7 8 , 15 16 17, 24 25 26

				// 27 28 29, 
				// 30 31 32,
				// 33 34 35,

				// 54 55 56,
				// 57 58 59,
				// 60 61 62,                 80
				int row1;
				for (int k = 0; k < ((int)strlen(start))/9; k++) {
					assert((int)strlen(start)/9 == 9);
					if (k == 6) {
						row1 = 54;
					} else if (k == 3) {
						row1 = 27;
					} else if (k == 0) {
						row1 = 0;
					} else {
						row1 += 3;
					}

					char p3[11] = "";
					p3[0] = start[row1+0];
					p3[1] = start[row1+1];
					p3[2] = start[row1+2];
					p3[3] = start[row1+9];
					p3[4] = start[row1+10];
					p3[5] = start[row1+11];
					p3[6] = start[row1+18];
					p3[7] = start[row1+19];
					p3[8] = start[row1+20];
					if (k == 8) {assert(row1+20 == 80);}
					p3[9] = '\0';
					convThree(p3, k);
				}
				genRealAns(3, 9);
			} else {
				printf("NOT YET\n"); exit(0);
			}
		}
		strcpy(start, realAns);
		for (int i = 0; i < 50; i++) {
			strcpy(ans[i], "");
		}
		getchar();
	}
	printf("start is [%s]\n", start);
	int mytot = 0; for (int i = 0; i < (int)strlen(start); i++) { if (start[i] == '#') { mytot++; } }		
	printf("**mytot is %d\n", mytot); getchar();
		
}

void genRealAns(int num, int size) {
	printf("in genRealAns\n");
	if (num == 2) {
		if (size == 36) {
			//ab ef ij mn qr uv  => abc  jkl mno stv yza efg
			//cd gh kl op st wx     def  mno pqr vwx bcd hij
			//			ghi  pqr .....
				printf("ans[i]s is\n"); 
			for (int i = 0; i < 36; i++) {
				printf("%s\n", ans[i]);
			}
			for (int i = 0; i < 6; i++) {
				realAns[(54*i)+0] = ans[(i*6)+0][0];
				realAns[(54*i)+1] = ans[(i*6)+0][1];
				realAns[(54*i)+2] = ans[(i*6)+0][2];

				realAns[(54*i)+3] = ans[(i*6)+1][0];
				realAns[(54*i)+4] = ans[(i*6)+1][1];
				realAns[(54*i)+5] = ans[(i*6)+1][2];

				realAns[(54*i)+6] = ans[(i*6)+2][0];
				realAns[(54*i)+7] = ans[(i*6)+2][1];
				realAns[(54*i)+8] = ans[(i*6)+2][2];

				realAns[(54*i)+9] = ans[(i*6)+3][0];
				realAns[(54*i)+10] = ans[(i*6)+3][1];
				realAns[(54*i)+11] = ans[(i*6)+3][2];

				realAns[(54*i)+12] = ans[(i*6)+4][0];
				realAns[(54*i)+13] = ans[(i*6)+4][1];
				realAns[(54*i)+14] = ans[(i*6)+4][2];

				realAns[(54*i)+15] = ans[(i*6)+5][0];
				realAns[(54*i)+16] = ans[(i*6)+5][1];
				realAns[(54*i)+17] = ans[(i*6)+5][2];

				realAns[(54*i)+18] = ans[(i*6)+0][3];
				realAns[(54*i)+19] = ans[(i*6)+0][4];
				realAns[(54*i)+20] = ans[(i*6)+0][5];

				realAns[(54*i)+21] = ans[(i*6)+1][3];
				realAns[(54*i)+22] = ans[(i*6)+1][4];
				realAns[(54*i)+23] = ans[(i*6)+1][5];

				realAns[(54*i)+24] = ans[(i*6)+2][3];
				realAns[(54*i)+25] = ans[(i*6)+2][4];
				realAns[(54*i)+26] = ans[(i*6)+2][5];

				realAns[(54*i)+27] = ans[(i*6)+3][3];
				realAns[(54*i)+28] = ans[(i*6)+3][4];
				realAns[(54*i)+29] = ans[(i*6)+3][5];

				realAns[(54*i)+30] = ans[(i*6)+4][3];
				realAns[(54*i)+31] = ans[(i*6)+4][4];
				realAns[(54*i)+32] = ans[(i*6)+4][5];

				realAns[(54*i)+33] = ans[(i*6)+5][3];
				realAns[(54*i)+34] = ans[(i*6)+5][4];
				realAns[(54*i)+35] = ans[(i*6)+5][5];

				realAns[(54*i)+36] = ans[(i*6)+0][6];
				realAns[(54*i)+37] = ans[(i*6)+0][7];
				realAns[(54*i)+38] = ans[(i*6)+0][8];

				realAns[(54*i)+39] = ans[(i*6)+1][6];
				realAns[(54*i)+40] = ans[(i*6)+1][7];
				realAns[(54*i)+41] = ans[(i*6)+1][8];

				realAns[(54*i)+42] = ans[(i*6)+2][6];
				realAns[(54*i)+43] = ans[(i*6)+2][7];
				realAns[(54*i)+44] = ans[(i*6)+2][8];

				realAns[(54*i)+45] = ans[(i*6)+3][6];
				realAns[(54*i)+46] = ans[(i*6)+3][7];
				realAns[(54*i)+47] = ans[(i*6)+3][8];

				realAns[(54*i)+48] = ans[(i*6)+4][6];
				realAns[(54*i)+49] = ans[(i*6)+4][7];
				realAns[(54*i)+50] = ans[(i*6)+4][8];

				realAns[(54*i)+51] = ans[(i*6)+5][6];
				realAns[(54*i)+52] = ans[(i*6)+5][7];
				realAns[(54*i)+53] = ans[(i*6)+5][8];

			}
			realAns[324] = '\0';

		} else if (size == 9) {
			//ab ef ij -> abc jkl stv
                                    // /def mno
			//cd gh kl    ghi pqr
		
			for (int i = 0; i < 3; i++) {
				realAns[(27*i)+0] = ans[(3*i)+0][0];
				realAns[(27*i)+1] = ans[(3*i)+0][1];
				realAns[(27*i)+2] = ans[(3*i)+0][2];
				realAns[(27*i)+3] = ans[(3*i)+1][0];
				realAns[(27*i)+4] = ans[(3*i)+1][1];
				realAns[(27*i)+5] = ans[(3*i)+1][2];
				realAns[(27*i)+6] = ans[(3*i)+2][0];
				realAns[(27*i)+7] = ans[(3*i)+2][1];
				realAns[(27*i)+8] = ans[(3*i)+2][2];

				realAns[(27*i)+9] = ans[(3*i)+0][3];
				realAns[(27*i)+10] = ans[(3*i)+0][4];
				realAns[(27*i)+11] = ans[(3*i)+0][5];
				realAns[(27*i)+12] = ans[(3*i)+1][3];
				realAns[(27*i)+13] = ans[(3*i)+1][4];
				realAns[(27*i)+14] = ans[(3*i)+1][5];
				realAns[(27*i)+15] = ans[(3*i)+2][3];
				realAns[(27*i)+16] = ans[(3*i)+2][4];
				realAns[(27*i)+17] = ans[(3*i)+2][5];

				realAns[(27*i)+18] = ans[(3*i)+0][6];
				realAns[(27*i)+19] = ans[(3*i)+0][7];
				realAns[(27*i)+20] = ans[(3*i)+0][8];
				realAns[(27*i)+21] = ans[(3*i)+1][6];
				realAns[(27*i)+22] = ans[(3*i)+1][7];
				realAns[(27*i)+23] = ans[(3*i)+1][8];
				realAns[(27*i)+24] = ans[(3*i)+2][6];
				realAns[(27*i)+25] = ans[(3*i)+2][7];
				realAns[(27*i)+26] = ans[(3*i)+2][8];
			}
			realAns[81] = '\0';
			
		} else if (size == 4) {
/*
	ab ef ==> abc jkl
	cd gh     def mno
	          ghi pqr
	ij mn   
                  stu
	kl op
*/
			for (int i = 0; i < 2; i++) {
				realAns[(18*i)+0] = ans[(2*i)+0][0];
				realAns[(18*i)+1] = ans[(2*i)+0][1];
				realAns[(18*i)+2] = ans[(2*i)+0][2];

				realAns[(18*i)+3] = ans[(2*i)+1][0];
				realAns[(18*i)+4] = ans[(2*i)+1][1];
				realAns[(18*i)+5] = ans[(2*i)+1][2];

				realAns[(18*i)+6] = ans[(2*i)+0][3];
				realAns[(18*i)+7] = ans[(2*i)+0][4];
				realAns[(18*i)+8] = ans[(2*i)+0][5];

				realAns[(18*i)+9] = ans[(2*i)+1][3];
				realAns[(18*i)+10] = ans[(2*i)+1][4];
				realAns[(18*i)+11] = ans[(2*i)+1][5];

				realAns[(18*i)+12] = ans[(2*i)+0][6];
				realAns[(18*i)+13] = ans[(2*i)+0][7];
				realAns[(18*i)+14] = ans[(2*i)+0][8];

				realAns[(18*i)+15] = ans[(2*i)+1][6];
				realAns[(18*i)+16] = ans[(2*i)+1][7];
				realAns[(18*i)+17] = ans[(2*i)+1][8];
			}
			realAns[36] = '\0';

			printf("sending back %s \n", realAns);
		} else {
			printf("EERROR\n"); exit(0);
		}
	} else if (num == 3) {
		if (size == 1) {
			printf("here1\n");
			strcpy(realAns, ans[0]);
		} else if (size == 9) {
			//abc jkl stu      abcd qrst efgh
			//def mno vwx  =>  efgh uvwx...
		//			   ijkl yzzz
			//ghi pqr yza      mnop abcd

	
			for (int i = 0; i < 3; i++) {
				realAns[(48*i)+0] = ans[(3*i)+0][0];
				realAns[(48*i)+1] = ans[(3*i)+0][1];
				realAns[(48*i)+2] = ans[(3*i)+0][2];
				realAns[(48*i)+3] = ans[(3*i)+0][3];

				realAns[(48*i)+4] = ans[(3*i)+1][0];
				realAns[(48*i)+5] = ans[(3*i)+1][1];
				realAns[(48*i)+6] = ans[(3*i)+1][2];
				realAns[(48*i)+7] = ans[(3*i)+1][3];

				realAns[(48*i)+8] = ans[(3*i)+2][0];
				realAns[(48*i)+9] = ans[(3*i)+2][1];
				realAns[(48*i)+10] = ans[(3*i)+2][2];
				realAns[(48*i)+11] = ans[(3*i)+2][3];

				realAns[(48*i)+12] = ans[(3*i)+0][4];
				realAns[(48*i)+13] = ans[(3*i)+0][5];
				realAns[(48*i)+14] = ans[(3*i)+0][6];
				realAns[(48*i)+15] = ans[(3*i)+0][7];

				realAns[(48*i)+16] = ans[(3*i)+1][4];
				realAns[(48*i)+17] = ans[(3*i)+1][5];
				realAns[(48*i)+18] = ans[(3*i)+1][6];
				realAns[(48*i)+19] = ans[(3*i)+1][7];

				realAns[(48*i)+20] = ans[(3*i)+2][4];
				realAns[(48*i)+21] = ans[(3*i)+2][5];
				realAns[(48*i)+22] = ans[(3*i)+2][6];
				realAns[(48*i)+23] = ans[(3*i)+2][7];

				realAns[(48*i)+24] = ans[(3*i)+0][8];
				realAns[(48*i)+25] = ans[(3*i)+0][9];
				realAns[(48*i)+26] = ans[(3*i)+0][10];
				realAns[(48*i)+27] = ans[(3*i)+0][11];

				realAns[(48*i)+28] = ans[(3*i)+1][8];
				realAns[(48*i)+29] = ans[(3*i)+1][9];
				realAns[(48*i)+30] = ans[(3*i)+1][10];
				realAns[(48*i)+31] = ans[(3*i)+1][11];

				realAns[(48*i)+32] = ans[(3*i)+2][8];
				realAns[(48*i)+33] = ans[(3*i)+2][9];
				realAns[(48*i)+34] = ans[(3*i)+2][10];
				realAns[(48*i)+35] = ans[(3*i)+2][11];

				realAns[(48*i)+36] = ans[(3*i)+0][12];
				realAns[(48*i)+37] = ans[(3*i)+0][13];
				realAns[(48*i)+38] = ans[(3*i)+0][14];
				realAns[(48*i)+39] = ans[(3*i)+0][15];

				realAns[(48*i)+40] = ans[(3*i)+1][12];
				realAns[(48*i)+41] = ans[(3*i)+1][13];
				realAns[(48*i)+42] = ans[(3*i)+1][14];
				realAns[(48*i)+43] = ans[(3*i)+1][15];

				realAns[(48*i)+44] = ans[(3*i)+2][12];
				realAns[(48*i)+45] = ans[(3*i)+2][13];
				realAns[(48*i)+46] = ans[(3*i)+2][14];
				realAns[(48*i)+47] = ans[(3*i)+2][15];

			}
			realAns[144] = '\0';
		} else {
			printf("ERRORR\n"); exit(0);
		}

	} else {
		printf("ERRROR\n"); exit(0);
	}		

}

void genallThrees() {
	struct twosandthrees_s new[3100];
	int newPos = 0;
	for (int i = 0; i < threesPos; i++) {
		printf("three %d is [%s]\n", i, threes[i].frm);
		strcpy(new[newPos].frm, threes[i].frm); strcpy(new[newPos].to, threes[i].to); newPos++;
		for (int k = 1; k < 9; k++) { //rotate
			if (k == 1) {
				new[newPos].frm[1] = threes[i].frm[0];
				new[newPos].frm[2] = threes[i].frm[1];
				new[newPos].frm[5] = threes[i].frm[2];
				new[newPos].frm[0] = threes[i].frm[3];
				new[newPos].frm[4] = threes[i].frm[4];
				new[newPos].frm[8] = threes[i].frm[5];
				new[newPos].frm[3] = threes[i].frm[6];
				new[newPos].frm[6] = threes[i].frm[7];
				new[newPos].frm[7] = threes[i].frm[8];
				new[newPos].frm[9] = '\0';
				strcpy(new[newPos].to, threes[i].to);
				newPos++;
			} else {
				new[newPos].frm[1] = new[newPos-1].frm[0];

				new[newPos].frm[2] = new[newPos-1].frm[1];
				new[newPos].frm[5] = new[newPos-1].frm[2];
				new[newPos].frm[0] = new[newPos-1].frm[3];
				new[newPos].frm[4] = threes[i].frm[4];
				new[newPos].frm[8] = new[newPos-1].frm[5];
				new[newPos].frm[3] = new[newPos-1].frm[6];
				new[newPos].frm[6] = new[newPos-1].frm[7];
				new[newPos].frm[7] = new[newPos-1].frm[8];
				new[newPos].frm[9] = '\0';
				strcpy(new[newPos].to, threes[i].to);
				newPos++;
				
			}
		}	
		//flip
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

	threesPos = 0;
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
printf("--------------------\n");
	for (int i = 0; i < threesPos; i++) {
		printf("%s == > %s\n", threes[i].frm, threes[i].to);
	} 
getchar();
printf("--------------------\n");

}

void genallTwos() {
	struct twosandthrees_s new[1000];
	int newPos = 0;
	printf("twosPos is %d\n", twosPos); getchar();

	for (int i = 0; i < twosPos; i++) {
		//printf("twos[%d] is [%s]\n", i, twos[i].frm); getchar();
		
		strcpy(new[newPos].frm, twos[i].frm); strcpy(new[newPos].to, twos[i].to); newPos++;
		for (int k = 1; k < 4; k++) { //rotate
			if (k == 1) {
				new[newPos].frm[2] = twos[i].frm[0];
				new[newPos].frm[0] = twos[i].frm[1];
				new[newPos].frm[3] = twos[i].frm[2];
				new[newPos].frm[1] = twos[i].frm[3];
				new[newPos].frm[4] = '\0';
				strcpy(new[newPos].to, twos[i].to);
				newPos++;
			} else {
				new[newPos].frm[2] = new[newPos-1].frm[0];
				new[newPos].frm[0] = new[newPos-1].frm[1];
				new[newPos].frm[3] = new[newPos-1].frm[2];
				new[newPos].frm[1] = new[newPos-1].frm[3];
				new[newPos].frm[4] = '\0';
				strcpy(new[newPos].to, twos[i].to);
				newPos++;
			}
		}	
		new[newPos].frm[1] = twos[i].frm[0];
		new[newPos].frm[0] = twos[i].frm[1];
		new[newPos].frm[3] = twos[i].frm[2];
		new[newPos].frm[2] = twos[i].frm[3];
		new[newPos].frm[4] = '\0';
		strcpy(new[newPos].to, twos[i].to);
		
		newPos++;

		new[newPos].frm[2] = twos[i].frm[0];
		new[newPos].frm[3] = twos[i].frm[1];
		new[newPos].frm[0] = twos[i].frm[2];
		new[newPos].frm[1] = twos[i].frm[3];
		new[newPos].frm[4] = '\0';
		strcpy(new[newPos].to, twos[i].to);
		
		newPos++;
	}

	twosPos = 0;
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
	for (int i = 0; i < twosPos; i++) {
		printf("%s == > %s\n", twos[i].frm, twos[i].to);
	} getchar();
}

void convTwo(char frm[], int part) {
	int found = 0;
	for (int i = 0; i < twosPos; i++) {
		if (strcmp(frm, twos[i].frm) == 0) {
			found++;
			strcpy(ans[part], twos[i].to); break;
		}
	}
	assert(found == 1 || found == 0);
	if (found == 0) {
		printf("ERROR two (not found)\n"); exit(0);
	}
}

void convThree(char frm[], int part) {
	int found = 0;
	for (int i = 0; i < threesPos; i++) {
		//printf("comparing %s V %s\n", frm, threes[i].frm);
		if (strcmp(frm, threes[i].frm) == 0) {
			found++;
			strcpy(ans[part], threes[i].to); break;
		}
	}
	assert(found == 1 || found == 0);
	if (found == 0) {
		printf("ERROR three (not found) %s\n", frm); exit(0);
	}
}
