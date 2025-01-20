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
	while (1) {
		for (int r = 0; r < 4; r++) {
			vars[r] = varsSave[samePos][r];
		}
		///memset(vars, 0, sizeof(vars));
		iPos = 0;
		//printf("[%s]\n", input);
		
		//printf("startPos: %d\n", poses[samePos]);
		for (i = poses[samePos]; i < leny; i++) {
			//printf("inst: %s\n", inst[i]);
			switch(inst[i][0]) {
				case 'i': {
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
		if (vars['z'-119]  == 0) {printf("[[ %s ]]-- valid\n", input); getchar();}

		
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
	}
		for (int p  =0 ; p < 4; p++) { printf("%c: %lld\n", p+119, vars[p]); }
	}
