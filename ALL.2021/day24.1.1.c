#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

FILE *a;
#define LINE 1000
//#define getchar()
char inst[300][10];
//#define getchar()

struct diffs_s {
	int one;
	int two;
	int three;
};
struct diffs_s diffs[15];
int diffsPos = 0;

int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 24\n"); fflush(stdout);
	char line1[LINE];

	int leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		if (line1[0] == 'm' && line1[1] == 'o') {
			line1[0] = 'o';
		}
		strcpy(inst[leny], line1);
		leny++;
	}
	fclose(a);

	//char input[20] = "13";
	int iPos = 0;
	//char input[] = "13579246899999";

	char input[] = "99999999999999"; 
	char inputPrev[15];
	int first = 1;
	int poses[15] = {0};
	long long vars[4] = {0}; //w, x, y, z;
	long long varsSave[15][4];
	memset(varsSave, 0, sizeof(varsSave));
	printf("first input is [[%s]]\n", input);
	int i;
	int samePos = 0;
	int veryFirst = 1;

	int diffsPos = -1;
	int restartVal = 0;
	while (1) {
		for (int r = 0; r < 4; r++) {
			vars[r] = varsSave[samePos][r];
		}
		///memset(vars, 0, sizeof(vars));
		iPos = 0;
		//printf("[%s]\n", input);

		//printf("startPos: %d\n", poses[samePos]);
		//for (i = poses[samePos]; i < leny; i++) 
		for (i = 0; i < leny; i++) {
			//printf("inst: %s\n", inst[i]);
			restartVal = i % 18;
			switch(inst[i][0]) {
				case 'i': {
						  diffsPos++;
						  printf("inp restartVal is %d -- diffsPos %d\n", restartVal, diffsPos);
						  char in;
						  int ret = sscanf(inst[i], "inp %c", &in);
						  if (ret != 1) {perror("ERR1"); goto again;}
						  vars[in - 119] = input[iPos] - 48;
						  //printf("input: %c\n", input[iPos]);
						  iPos++;
						  if (veryFirst) {poses[iPos] = i; if (iPos == 14) {veryFirst = 0;};}
						  if (first) {if (iPos == 14) {first = 0;} for (int q = 0; q<4; q++) {varsSave[iPos][q] = vars[q];} }
						  if (iPos > 14) {perror("LONG");}
						  break;
					  }
				case 'a': {
						  char i1, i2; int i3;
						  int ret = sscanf(inst[i], "add %c %d", &i1, &i3);
						  if (ret == 2) {
							  if  (restartVal == 5) { diffs[diffsPos].two = i3;} 
							  if  (restartVal == 15) { diffs[diffsPos].three = i3;} 
							  vars[i1 - 119] = vars[i1-119] + i3;
							  break;
						  }

						  ret = sscanf(inst[i], "add %c %c", &i1, &i2);
						  if (ret == 2) {
							  vars[i1 - 119] = vars[i1-119] + vars[i2 - 119];
							  break;
						  } else {
							  perror("ERRa1"); goto again;
						  }
						  perror("ERRa"); goto again;

						  break;
					  }
				case 'm': {
						  char i1, i2; int i3;
						  int ret = sscanf(inst[i], "mul %c %d", &i1, &i3);
						  if (ret == 2) {
							  vars[i1 - 119] = vars[i1-119] * i3;
							  break;
						  }

						  ret = sscanf(inst[i], "mul %c %c", &i1, &i2);
						  if (ret == 2) {
							  vars[i1 - 119] = vars[i1-119] * vars[i2 - 119];
							  break;
						  } else {
							  perror("ERRm1"); goto again;
						  }

						  break;
					  }
				case 'd': {
						  char i1, i2; int i3;
						  int ret = sscanf(inst[i], "div %c %d", &i1, &i3);
						  if (ret == 2) {
							  if (i3 == 0) {perror("div1"); goto again;}
							  vars[i1 - 119] = vars[i1-119] / i3;
							  if  (restartVal == 4) { diffs[diffsPos].one = i3;}
							  break;
						  }

						  ret = sscanf(inst[i], "div %c %c", &i1, &i2);
						  if (ret == 2) {
							  if (vars[i2-119] == 0) {perror("div2"); goto again;}
							  vars[i1 - 119] = vars[i1-119] / vars[i2 - 119];
							  break;
						  } else {
							  perror("ERRd1"); goto again;
						  }
						  break;
					  }
				case 'o': {
						  char i1, i2; int i3;
						  int ret = sscanf(inst[i], "ood %c %d", &i1, &i3);
						  if (ret == 2) {
							  if (vars[i1-119] < 0) {perror("mod1"); goto again;}
							  if (i3 <= 0) {perror("mod3"); goto again;}
							  vars[i1 - 119] = vars[i1-119] % i3;
							  break;
						  }

						  ret = sscanf(inst[i], "ood %c %c", &i1, &i2);
						  if (ret == 2) {
							  if (vars[i1-119] < 0) {perror("mod4"); goto again;}
							  if (vars[i2-119] <= 0) {perror("mod5"); goto again;}
							  vars[i1 - 119] = vars[i1-119] % vars[i2 - 119];
							  break;
						  } else {
							  perror("ERRo1"); goto again;
						  }
						  perror("ERRo"); goto again;
						  break;
					  }
				case 'e': {
						  char i1, i2; int i3;
						  int ret = sscanf(inst[i], "eql %c %d", &i1, &i3);
						  if (ret == 2) {
							  if (vars[i1-119] == i3) {
								  vars[i1 - 119] = 1;
							  } else {
								  vars[i1 - 119] = 0;
							  }
							  break;
						  }

						  ret = sscanf(inst[i], "eql %c %c", &i1, &i2);
						  if (ret == 2) {
							  if (vars[i1-119] == vars[i2-119]) {
								  vars[i1 - 119] = 1;
							  } else {
								  vars[i1 - 119] = 0;
							  }
							  break;
						  } else {
							  perror("ERRe1"); goto again;
						  }
						  perror("ERRe"); goto again;
						  break;
					  }
			}
			//for (int i  =0 ; i < 4; i++) { printf("%c: %lld\n", i+119, vars[i]); }
		}
again:
		if (vars['z'-119]  == 0) {printf("[[ %s ]]-- valid\n", input); exit(0);}


		int found;
		strcpy(inputPrev, input);
		do {
			char *ex; long long inLL =  strtoll(input, &ex, 10); inLL--;
			sprintf(input, "%014lld", inLL);
			found = 0;
			for (int z = 0; z < 14; z++) {
				if (input[z] == '0') {
					found = 1; break;
				}
			}
		} while (found == 1);	


		samePos = 0;
		for (int i = 0; i < 14; i++) {
			if (input[i] == inputPrev[i] && input[0] == inputPrev[i]) {
				samePos = i+1;
			} else {
				break;
			}
		}
		//printf("%s V %s - %d\n", inputPrev, input, samePos); getchar();
		if (samePos == 0) {
			first = 1;
		}
		//printf("input is %s\n", input); getchar();
		break;
	}
	for (int p  =0 ; p < 4; p++) { printf("%c: %lld\n", p+119, vars[p]); }

	for (int i = 0; i < 14; i++) {
		printf("%d %d %d\n", diffs[i].one, diffs[i].two, diffs[i].three);
	}
	getchar();

	printf("starting fast...\n");
	strcpy(input, "99999999999999");
	int w = 0, x = 1, y = 2, z= 3;		
	samePos = 0;
	long long same[15][4] = {0};
	while (1) {
		vars[0] = same[samePos][0]; vars[1] = same[samePos][1]; vars[2] = same[samePos][2]; vars[3] = same[samePos][3];
		//printf("start(i:%d): %lld %lld %lld %lld\n", samePos-1, vars[0], vars[1], vars[2], vars[3]); getchar();
		//if (samePos - 1 < 0) {samePos = 1;}
		for (int i = samePos; i < 14; i++) {

			//inp w
			vars[w] = input[i] - 48;
			//mul x 0
/*
			vars[x] *= 0; 
			//add x z
			vars[x] += vars[z]; 
*/
 			vars[x] = vars[z];
			//mod x 26
			vars[x] %= 26;
			//div z QQQ
			vars[z] /= diffs[i].one; 
			//add x QQQ
			vars[x] += diffs[i].two;
			//eql x w
			vars[x] = (vars[x] == vars[w]) ? 1 : 0;
			//eql x 0
			vars[x] = (vars[x] == 0) ? 1 : 0;
/*
			//mul y 0
			vars[y] *= 0;  
			//add y 25
			vars[y] += 25; 
*/
			vars[y] = 25;

			//mul y x
			vars[y] *= vars[x];
			//add y 1
			vars[y] += 1;
			//mul z y
			vars[z] *= vars[y];
/*
			//mul y 0
			vars[y] *= 0; 
			//add y w
			vars[y] += vars[w]; //**
*/

			vars[y] = vars[w];
			///add y QQQ
			vars[y] += diffs[i].three;
			///mul y x
			vars[y] *= vars[x];
			///add z y
			vars[z] += vars[y];
			same[i+1][0] = vars[0]; same[i+1][1] = vars[1]; same[i+1][2] = vars[2]; same[i+1][3] = vars[3];
			//printf("END(%d) %lld %lld %lld %lld\n", i+1, vars[0], vars[1], vars[2], vars[3]); fflush(stdout); getchar(); 

		}
		if (vars['z'-119]  == 0) {printf("[[ %s ]]-- valid\n", input); getchar();} //***
		strcpy(inputPrev, input);

		int found;
		do {
			char *ex; long long inLL =  strtoll(input, &ex, 10); inLL--;
			sprintf(input, "%014lld", inLL);
			found = 0;
			for (int z = 0; z < 14; z++) {
				if (input[z] == '0') {
					found = 1; break;
				}
			}
		} while (found == 1);	

		int samePosPrev = samePos;
                {
			samePos = 0;
			for (int j = 0; j < 14; j++) {
				if (input[j] == inputPrev[j] && input[0] == inputPrev[j]) {
					samePos = j+1;
				} else {
					break;
				}
			}
			//if (samePos == 0) {memset(vars, 0, sizeof(vars));}
		}
		if (samePosPrev != samePos) {printf("[[ %s ]]\n", input);}
		//printf("%s V %s\n", input, inputPrev); printf("samePos: %d\n", samePos); getchar();



	}
	for (int p  =0 ; p < 4; p++) { printf("%c: %lld\n", p+119, vars[p]); }
}
