#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <signal.h>

using namespace std;

#undef _DEBUG_
#define SIZE 14200
//#define POSS 490000
#define POSS 20000
char line1[SIZE];
unsigned long tot = 0;
#define SZ 51*2
char grid[SZ+1][SZ+1];
#define ST SZ/2

#define getchar()
char dirs[SIZE];
char (*exp1)[SIZE];
int *exp1Poses;
int exp1Pos = 0;

void follow(int *x, int *y, char c1);
void populate();
void printit(int, int, int, int);
void wallit();
void expand(char regEX[], char*, int pos123);
void readToCloseBracket(char *what);
void updateAll(char c2);
void printAll();
void expandPrimitiveOr(char regEX[], char *pre, int pos123);
void expandNonPrimitiveOr(char regEX[], char *pre, int pos123);
// run before and after (this shell (sed) script)
struct lengths_s {
	int first;
	int second;
	int third;
	int minLen;
};
struct lengths_s lengths[2000];
int lengthsPos = 0;
void signal_handler(int) {
	printf("INTR: exp1Pos: [[[[---%d---]]]] -- ", exp1Pos);
	printf("do you want to see a random exp1? y/?\n");

	char ans[5];
	fgets(ans, 4, stdin);
	if (ans[0] == 'y') {
		printf("%s\n", exp1[rand() % (exp1Pos-1)]);
		printf("..continueing...\n");
	} else {
		printf("no probs... continueing...\n");
	}

	fflush(stdin);
	printf("do you want to free all memory? y/?\n");
	char ans2[5]; fgets(ans2, 4, stdin); 

	if (ans2[0] == 'y') {
		free(exp1Poses); free(exp1);
		printf("memory freed...\n");
	}  else {
		printf("no probs on the memory front. continueing...\n");
	}
	time_t t; time(&t);
	printf("current time is %s (continueing...)\n", ctime(&t));
}

int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day20.1\n"); fflush(stdout);
	signal(SIGTSTP, &signal_handler);
	int leny = 0;
	exp1 = (char (*)[SIZE])malloc((unsigned long long) POSS * sizeof *exp1);
	if (exp1 == NULL) {perror("MEM1\n"); exit(0);}
	exp1Poses = (int *)malloc(POSS * sizeof(int));
	if (exp1Poses == NULL) {perror("MEM2\n"); exit(0);}
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		strcpy(dirs, line1);
		leny++;
	}

	int sx = ST+1; int sy = ST+1;	
	///int sxOrig = ST+1; int syOrig = ST+1;	

	int changed;
	printf("strlen before (dirs) is %d\n", (int)strlen(dirs));
ag:
	changed = 0;
	for (int i = 0; i < (int)strlen(dirs)-1; i++) {
		if (dirs[i] == '|' && dirs[i+1] == ')') {
			int j;
			for (j = i; j < (int)strlen(dirs)-1; j++) {
				dirs[j] = dirs[j+1];
			}
			dirs[j] = '\0';
			changed = 1;
		}
	}

	if (changed == 1) {goto ag;}
	for (int i = 0; i < 10; i++) {
		exp1Poses[i] = 0;
		strcpy(exp1[i], "");
	}
	printf("strlen after (dirs) is %d\n", (int)strlen(dirs));

	populate();
	exp1Pos = 1;
	//printf("dirs is [%s]\n", dirs);
	expandPrimitiveOr(dirs, (char*)"", 0);
	printf("after expandPrimitiveOrs\n");
	printf("finished expandPrimitive %d\n", exp1Pos);
	//printAll(); 
	printf("exp1Pos is %d\n", exp1Pos); 
	
again:
	//printf("going AGAIN\n");
	int myend = exp1Pos;
	for (int i = 0; i < myend; i++) {
		//printf("Trying %s\n", exp1[i]);
		expandNonPrimitiveOr(exp1[i], (char*)"", i);
	}
	//printf("exp1Pos is now %d\n", exp1Pos);
	//printf("myend is now %d\n", myend);
	if (myend != exp1Pos) {goto again;}

	//printAll(); 

	printf("finished expandNonPrimitive %d\n", exp1Pos);
again2:
	for (int q = 0; q < exp1Pos; q++) {
		for (int i = 0; i < (int)strlen(exp1[q]); i++) {
			if (exp1[q][i] == '|') {
				for (int z = q; z < exp1Pos-1; z++) {
					strcpy(exp1[z], exp1[z+1]);
				}
				exp1Pos--;
				goto again2;
			}
		}
	}
	printf("tidy 1 %d\n", exp1Pos);
	for (int q = 0; q < exp1Pos; q++) {
		int pos = 0;
		for (int i = 0; i < (int)strlen(exp1[q]); i++) {
			if (exp1[q][i] == '#') {
				exp1[q][i] = '|';
				exp1Poses[q] = strlen(exp1[q]);
			} else if (exp1[q][i] == '(' || exp1[q][i] == ')' || exp1[q][i] == '^' || exp1[q][i] == '$') {
			} else {
				exp1[q][pos++] = exp1[q][i];
			}
		}
		exp1[q][pos] = '\0';
	}
	//printAll();
	printf("tidy 2 %d\n", exp1Pos);
again3:
	for (int q = 0; q < exp1Pos-1; q++) {
		for (int r = q+1; r <exp1Pos; r++) {
			if (strcmp(exp1[q], exp1[r]) == 0) {
				for (int z = r; z < exp1Pos-1; z++) {
					strcpy(exp1[z], exp1[z+1]);
				}
				exp1Pos--;
				goto again3;
			}
		}
	}
	printf("tidy 3 %d\n", exp1Pos);
				

	printf("after non\n");
	printf("------------\n");
	//printAll(); getchar();
	
	
	int max = 0;
	for (int i = 0; i < exp1Pos; i++) {
		if ((int)strlen(exp1[i]) > max) {max = (int)strlen(exp1[i]);}
	}
	printf("****max %d\n", max);
	exit(0);
	//for (int i = 0; i < exp1Pos; i++) { expand(exp1[i], "", 0); getchar(); }
	

	for (int i = 0; i < exp1Pos; i++) {
		sx = ST+1; sy = ST+1;
		for (int j = 0; j < (int)strlen(exp1[i]); j++) {
			follow(&sx, &sy, exp1[i][j]);
			//printf("sx sy %d,%d\n", sx, sy);
		}
		//printf("Pos: %d, %d -> %d %d\n", sxOrig, syOrig, sx, sy);
	}
	wallit();
	//printit(sxOrig, syOrig, sx, sy); //getchar();

	fclose(a);
	printf("**tot %lu\n", tot);
	free(exp1Poses); free(exp1);

}
void printAll() {
	for (int i = 0; i < exp1Pos; i++) {
		printf("[%s]\n", exp1[i]);
	}
}

void updateAll(char c2) {
	for (int i = 0; i < exp1Pos; i++) {
		//printf("adding %c to %d\n", c2, i);
		exp1[i][exp1Poses[i]] = c2;
		exp1Poses[i]++;
		exp1[i][exp1Poses[i]] = '\0';
	}
}

void expandPrimitiveOr(char regEX[], char *pre, int pos123) {
	int ok = 0;
	
	strcpy(exp1[0], regEX);
	exp1Pos = 1;
	int Rpos, Lpos;
	int mytotnum = 0;
	for (int q = 0; q < exp1Pos; q++) {
		if (exp1[q][0] == '^') {
			int z;
			for (z = 0; z < (int)strlen(exp1[q]); z++) {
				exp1[q][z] = exp1[q][z+1];
			}
			exp1[q][z] = '\0';
		}
	}

	for (int q = 0; q < exp1Pos; q++) {
		if (exp1[q][(int)strlen(exp1[q]) -1] == '$') {
			exp1[q][(int)strlen(exp1[q])-1] = '\0';
		}
	}
	
	
	int changed3;
	for (int q = 0; q < exp1Pos; q++) {
ag3:
		changed3 = 0;
		for (int i = 0; i < (int)strlen(exp1[q])-1; i++) {
			if (exp1[q][i] == 'N' && exp1[q][i+1] == 'S') {
				int z;
				for (z = i; z < (int)strlen(exp1[q])-2; z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			} else  if (exp1[q][i] == 'S' && exp1[q][i+1] == 'N') {
				int z;
				for (z = i; z < (int)strlen(exp1[q]); z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			} else  if (exp1[q][i] == 'W' && exp1[q][i+1] == 'E') {
				int z;
				for (z = i; z < (int)strlen(exp1[q]); z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			} else  if (exp1[q][i] == 'E' && exp1[q][i+1] == 'W') {
				int z;
				for (z = i; z < (int)strlen(exp1[q]); z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			}
		}
		if (changed3 == 1) {
			//printf("ag3..\n");
			goto ag3;
		}
	}

	printf("after remove of NS SN etc... starting search .... \n");
restart:
	int changed = 0;
	for (int q = 0; q < exp1Pos; q++) {
		for (int i = 0; i < (int)strlen(exp1[q]); i++) {
			if (exp1[q][i] == '(') {
				char copyR[15000]; int pos2 = 0;
				for (int j = i+1; j < (int)strlen(exp1[q]); j++) {
					if (exp1[q][j] == '(') {
						goto cont;
					} else if (exp1[q][j] == 'N' || exp1[q][j] == 'S' || exp1[q][j] == 'E' || exp1[q][j] == 'W') {
						copyR[pos2++] = exp1[q][j];
						continue;
					} else if (exp1[q][j] == '|') {
						goto cont;
					} else if (exp1[q][j] == ')') {
						copyR[pos2] = '\0';
						string s1 = exp1[q];
						//printf("BEF:%s\n", s1.c_str());
						s1.replace(s1.begin()+i, s1.begin()+j+1, copyR);
						//printf("AFT:%s\n", s1.c_str()); //getchar();
						strcpy(exp1[q], s1.c_str());
						goto restart;
					}
				}
			}
cont:
			continue;
		}
		
					
		ok = 0; int bra = 0;
		for (int i = 0; i < (int)strlen(exp1[q]); i++) {
			if (exp1[q][i] == '|') {
				//exp1[q][i] = '#';
				//printf("found pipe\n");
				char copyL[15000]; int pos1 = 0;
				for (int j = i-1; j >= 0; j--) {
					if (exp1[q][j] == 'N' || exp1[q][j] == 'S' || exp1[q][j] == 'E' || exp1[q][j] == 'W') {
						copyL[pos1++] = exp1[q][j];
					} else if (exp1[q][j] == '(') {
						bra++;
						//copyL[pos1++] = exp1[q][j];
						copyL[pos1] = '\0';
						Lpos = j;
						//printf("copyL is %s\n", copyL); //getchar();

						ok = 1; break;
						//ok
					} else if (exp1[q][j] == ')') {
						copyL[pos1++] = exp1[q][j];
						bra--;
						break;
					}
					
				}
	
				int mid = 0;
				char copyR[15000]; int pos2 = 0; bra = 0;
				int myj;
				if (ok == 1) {
					//printf("here2..copyL is %s..\n", copyL); 
					ok = 0;
					//copyR[pos2++] = '(';
					for (int j = i+1; j < (int)strlen(exp1[q]); j++) {
						
						if (exp1[q][j] == '|' || exp1[q][j] == 'N' || exp1[q][j] == 'S' || exp1[q][j] == 'E' || exp1[q][j] == 'W') {
							copyR[pos2++] = exp1[q][j];
						} else if (exp1[q][j] == ')' || exp1[q][j] == '|') {
							bra--;
							//copyR[pos2++] = exp1[q][j];
							Rpos = j;
							copyR[pos2] = '\0';
							//printf("copyR is %s\n", copyR); //getchar();
							if (exp1[q][j] == '|') {mid = 1; myj = j;}
							ok = 1; break;
						} else if (exp1[q][j] == '(') {
							copyR[pos2++] = exp1[q][j];
							bra++;
							break;
						}
					}
				}
			
				if (ok == 1 && mid == 1) {
					if (exp1[q][myj+1] != ')') {
						perror("non bracket...\n");
						exit(0);
					}
				}
				if (ok == 1) {
					mytotnum++;
					///printf("here1 exp1[q] is %s\n", exp1[q]);
					string s1 = exp1[q];
					string tmp1 = copyL;
					reverse(tmp1.begin(), tmp1.end());
					//printf("L: %d R: %d\n", Lpos, Rpos);
					//printf("s1 bef %s\n", s1.c_str());
					//printf("Lpos is %d\n", Lpos);
					//string s2 = exp1[q];
					string tmp2 = copyR;
					//printf("s2 bef %s\n", s2.c_str());
					//printf("[%s] V [%s]\n", s1.c_str(), s2.c_str()); //getchar();

					lengths[lengthsPos].first = tmp1.length();
					lengths[lengthsPos].second = tmp2.length();
					if (lengths[lengthsPos].first < lengths[lengthsPos].second) {
						lengths[lengthsPos].minLen = 1;
					} else {
						lengths[lengthsPos].minLen = 2;
					}
					if (mid == 1) {
						lengths[lengthsPos].third = 0;
						lengths[lengthsPos].minLen = 3;
					} else {
						lengths[lengthsPos].third = 99999;
					}
							
					
					if (lengths[lengthsPos].minLen == 1) {
						s1.replace(s1.begin()+Lpos, s1.begin()+Rpos+1, tmp1);
						strcpy(exp1[q], s1.c_str());
						exp1Poses[q] = s1.length();
					} else if (lengths[lengthsPos].minLen == 2) {
						s1.replace(s1.begin()+Lpos, s1.begin()+Rpos+1, tmp2);
						strcpy(exp1[q], s1.c_str());
						exp1Poses[q] = s1.length();
					} else if (lengths[lengthsPos].minLen == 3) {
						string tmp3 = "";
						s1.replace(s1.begin()+Lpos, s1.begin()+Rpos+1, "");
						strcpy(exp1[q], s1.c_str());
						exp1Poses[q] = s1.length();
					}
							
					lengthsPos++;
					goto restart;
					changed = 1;
				}
				
			}
		}
		if (changed == 1) {
			goto restart; 
		}
	}

	for (int q = 0; q < exp1Pos; q++) {
ag4:
		changed3 = 0;
		for (int i = 0; i < (int)strlen(exp1[q])-1; i++) {
			if (exp1[q][i] == 'N' && exp1[q][i+1] == 'S') {
				int z;
				for (z = i; z < (int)strlen(exp1[q])-2; z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			} else  if (exp1[q][i] == 'S' && exp1[q][i+1] == 'N') {
				int z;
				for (z = i; z < (int)strlen(exp1[q]); z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			} else  if (exp1[q][i] == 'W' && exp1[q][i+1] == 'E') {
				int z;
				for (z = i; z < (int)strlen(exp1[q]); z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			} else  if (exp1[q][i] == 'E' && exp1[q][i+1] == 'W') {
				int z;
				for (z = i; z < (int)strlen(exp1[q]); z++) {
					exp1[q][z] = exp1[q][z+2];
				}
				exp1[q][z] = '\0';
				changed3 = 1;
			}
		}
		if (changed3 == 1) {
			//printf("ag3..\n");
			goto ag4;
		}
	}

	printf("exp1Pos is %d\n", exp1Pos);
	printf("exp1[0] is %s\n", exp1[0]);
	int vmin = (int)strlen(exp1[0]);
	for (int i = 0; i < exp1Pos; i++) {
		printf("MINLEN: [[%d ]] mytotnum %d\n", (int)strlen(exp1[i]), mytotnum);
	}

	int mylen2 = 0;
	for (int i = 0; i < mytotnum; i++) {
		
		if (lengths[i].minLen == 1) {
			mylen2 += lengths[i].first;

		} else if (lengths[i].minLen == 2) {
			mylen2 += lengths[i].second;
		} else if (lengths[i].minLen == 3) {
			mylen2 += lengths[i].third;
		}
		if (mylen2 > 1000) {
			printf("i is %d myLen2 is %d\n", i, mylen2);
			break;
		}
	}
	getchar();

	int qs[800];
	unsigned long long totL1000 = 0;
	unsigned long long totP1000 = 0;
	int ig;
	for (int end2 = 0;end2 < mylen2; end2++) {
		//if (end2 % 10 == 0) {printf("end2 is %d tots: P:%llu L:%llu\n", end2, totP1000, totL1000);}
		{printf("end2 is %d tots: P:%llu L:%llu\n", end2, totP1000, totL1000);}
		for (int i = 0; i < end2; i++) {
			qs[i] = 3;
		}
		for (int end = end2; end < mylen2; end++) {
			for (int i = end2; i < end; i++) {
				qs[i] = 1;
			} 
			for (int i = end; i < mylen2; i++) {
				qs[i] = 2;
			}

			sort(qs, qs+mylen2);
			
			do {
				ig = 0;
				int mylen = 0;
				for (int i = 0; i < mylen2; i++) {
					if (qs[i] == 1) {
						mylen += lengths[i].first;
					} else if (qs[i] == 2) {
						mylen += lengths[i].second;
					} else if (qs[i] == 3) {
						if (lengths[i].third != 99999) {
							mylen += 0;
						} else {
							ig = 1;
							break;
						}
					}
				}
				if (ig == 0) {if (mylen+vmin >= 1000) {totP1000++;} else if (mylen+vmin < 1000) {totL1000++;}}
				//printf("mylen is %d\n", mylen+vmin);	
			} while (next_permutation(qs, qs+mylen2));
		}
	}

		
	getchar();
	exit(0);
/*
	int changed1;
aga:
	printf("before %d\n", exp1Pos);
	changed1 = 0;
	int end = exp1Pos;
	for (int i = 0; i < end-1; i++) {
		for (int j = i+1; j < end; j++) {
			if (strcmp(exp1[i], exp1[j]) == 0) {
				for (int k = i; k < end-1; k++) {
					strcpy(exp1[k], exp1[k+1]);
				}
				exp1Pos--;
				changed1 = 1;
			}
		}
	}
	if (changed1 == 1) {
		printf("after %d\n", exp1Pos);
		goto aga;
	}
	printf("after all %d\n", exp1Pos);
*/
	for (int q = 0; q < exp1Pos; q++) {
		for (int i = 0; i < (int)strlen(exp1[q]); i++) {
			if (exp1[q][i] == '#') {
				exp1[q][i] = '|';
				exp1Poses[q] = strlen(exp1[q]);
			}
		}
	}

	char myfile[100];
	sprintf(myfile, "outprim.txt.%d", rand()%(exp1Pos-1));
	FILE *b = fopen(myfile, "a");
	
	for (int i = 0; i < exp1Pos; i++) {
		fputs(exp1[i], b);		
		fputs("\n", b);		
	}
	fclose(b);
	printf("written to file [[[%s]]]\n", myfile);
	//exit(0);

}

int ind = 0;
void expandNonPrimitiveOr(char regEX[], char *pre, int pos123) {
	int ok = 0;
	
	strcpy(exp1[0], regEX);
	int Rpos, Lpos;
		ok = 0; int bra = 0;
		for (int i = 0; i < (int)strlen(regEX); i++) {
			if (regEX[i] == '|') {
				//printf("found pipe\n");
				//regEX[i] = '#';
				char copyL[100]; int pos1 = 0; bra = 0;
				for (int j = i-1; j >= 0; j--) {
					if (regEX[j] == 'N' || regEX[j] == 'S' || regEX[j] == 'E' || regEX[j] == 'W') {
						copyL[pos1++] = regEX[j];
					} else if (regEX[j] == '(') {
						bra++;
						copyL[pos1++] = regEX[j];
						if (bra == 1) {
							copyL[pos1] = '\0';
							Lpos = j;
							//printf("copyL is %s\n", copyL);
	
							ok = 1; break;
						}
						//ok
					} else if (regEX[j] == ')') {
						copyL[pos1++] = regEX[j];
						bra--;
					}
					
				}
	
				char copyR[100]; int pos2 = 0; bra = 0;
				if (ok == 1) {
					///printf("here2..copyL is %s..\n", copyL); 
					ok = 0;
					copyR[pos2++] = '(';
					for (int j = i+1; j < (int)strlen(regEX); j++) {
						
						if (regEX[j] == '|' || regEX[j] == 'N' || regEX[j] == 'S' || regEX[j] == 'E' || regEX[j] == 'W') {
							copyR[pos2++] = regEX[j];
						} else if (regEX[j] == ')') {
							bra--;
							copyR[pos2++] = regEX[j];
							if (bra == -1) {
								Rpos = j;
								copyR[pos2] = '\0';
								///printf("copyR is %s\n", copyR);
								ok = 1; break;
							}
						} else if (regEX[j] == '(') {
							copyR[pos2++] = regEX[j];
							bra++;
						}
					}
				}
				if (ok == 1) {
					///printf("here1 regEX is %s\n", regEX);
					string s1 = regEX;
					string tmp1 = copyL;
					reverse(tmp1.begin(), tmp1.end());
					///printf("L: %d R: %d\n", Lpos, Rpos);
					///printf("s1 bef %s\n", s1.c_str());
					s1.replace(s1.begin()+Lpos, s1.begin()+Rpos, tmp1);
					string s2 = regEX;
					string tmp2 = copyR;
					///printf("s2 bef %s\n", s2.c_str());
					s2.replace(s2.begin()+Lpos, s2.begin()+Rpos, tmp2);
							
					int found23 = 0;
                                        for (int p = 0; p < exp1Pos; p++) {
                                                if (strcmp(s1.c_str(), exp1[p]) == 0) {
                                                        found23 = 1; break;
                                                }
                                        }
                                        if (found23 == 0) {
						strcpy(exp1[pos123], s1.c_str());
						exp1Poses[pos123] = s1.length();
					}
					///printf("s1 aft %s\n", s1.c_str());

			                int found22 = 0;
                                        for (int p = 0; p < exp1Pos; p++) {
                                                if (strcmp(s2.c_str(), exp1[p]) == 0) {
                                                        found22 = 1; break;
                                                }
                                        }
                                        if (found22 == 0) {
                                                strcpy(exp1[exp1Pos], s2.c_str());
                                                exp1Poses[exp1Pos] = s2.length();
                                                exp1Pos++;
						if (exp1Pos+100 > POSS) {
							printf("WARNNING exp1Pos %d\n", exp1Pos);
						}
                                        }
					///printf("***s2 aft %s\n", s2.c_str());
					//goto restart; getchar();
				}
				
				
			}
		}
		///printf("exp1Pos is now %d\n", exp1Pos);
}
void expand(char regEX[], char *pre, int pos123) {
	ind++;
	int end1; int found = 0;
	int pos1;  int nowAft1;
	char both1[100];
	char aft1[100];
	for (int curPos = 0; curPos < (int) strlen(regEX); curPos++) {
		if (strcmp(pre, "") == 0) {
		} else {
			for (int j = 0; j < (int)strlen(regEX); j++) {
				if (regEX[j] == '(') {
					do {
						j++;
					} while (regEX[j] != ')'); 
				}
				if (regEX[j] == '|') {
					curPos = j;
					break;
				}
			}
		}
		switch (regEX[curPos]) {
			case '^':
				break;
			case '$':
				//printf("thats the end...\n");
				break;
			case 'N':
				updateAll(regEX[curPos]);
				break;
			case 'S':
				updateAll(regEX[curPos]);
				break;
			case 'E':
				updateAll(regEX[curPos]);
				break;
			case 'W':
				updateAll(regEX[curPos]);
				break;
			case '(':
				char sub[100]; int k; curPos++;
				for (k = curPos; k < (int)strlen(regEX); k++) {
					sub[k-curPos] = regEX[k];
				}
				sub[k-curPos] = '\0';
				for (int z = 0; z<ind; z++) {printf("	");}printf("sub befor is %s\n", sub); //getchar();
				readToCloseBracket(sub);
				for (int z = 0; z<ind; z++) {printf("	");}printf("sub after is %s\n", sub); //getchar();
				curPos += (int)strlen(sub);
				printf("exp1[0] is [%s]\n", exp1[0]); //getchar();
				end1 = exp1Pos;
				char tmppre[100];
				for (int i = 0; i < end1; i++) {
					strcpy(tmppre, exp1[i]);
					expand(sub, tmppre, i);
				}
				break;
			case ')':
				for (int z = 0; z<ind; z++) {printf("	");}printf("ERR cb regEX[%d]: %c %d\n", curPos, regEX[curPos], regEX[curPos]); //getchar();
				break;
			case '|':
				char first[100];
				char second[100];
				int i;
				for (i = 0; i < curPos; i++) {
					first[i] = regEX[i];
				} first[i] = '\0';
				for (i = curPos+1; i < (int)strlen(regEX); i++) {
					second[i-(curPos+1)] = regEX[i];
				} second[i-(curPos+1)] = '\0';
				curPos = (int)strlen(regEX);	
				for (int z = 0; z<ind; z++) {printf("	");} printf("first is [%s]\n", first);
				for (int z = 0; z<ind; z++) {printf("	");} printf("secon is [%s]\n", second);
				
				printf("pre is %s\n", pre);
				found = 0;
				strcpy(both1, "");
				strcpy(aft1, "");
				nowAft1 = 0; pos1 = 0;
				if ((int)strlen(first) != 0) {
					for (int i = 0; i < (int)strlen(first); i++) {
						if (first[i] == '(') {
							found = 1;
							both1[i] = '\0';
							nowAft1 = 1;
							i++;
						}
						if (nowAft1 == 0) {	
							both1[i] = first[i];
						} else {
							aft1[pos1++] = first[i];
						}
					}
					printf("found is %d both1 is %s\n", found, both1);
					printf("found is %d aft1 is %s\n", found, aft1);
					aft1[pos1] = '\0';

					if (found == 1) {
						int found2 = 0;
						for (int j = 0; j < (int)strlen(first); j++) {
							if (first[j] == '(') {
								found2 = 1; break;
							}
						}
						if (found2 == 1) {
							exp1Pos++;
							if (exp1Pos+100 > POSS) {
								printf("WARNNING(2) exp1Pos %d\n", exp1Pos);
							}
							expand(first, pre, exp1Pos-1);
						} else {
							strcpy(exp1[pos123], pre);
							strcat(exp1[pos123], both1);
							strcat(exp1[pos123], aft1);
							exp1Poses[pos123] = (int)strlen(exp1[pos123]);
							printf("exp1[exp1Pos] %s\n", exp1[pos123]);
						}
						//exp1Pos++;
					} else {
						strcpy(exp1[pos123], pre);
						strcat(exp1[pos123], first);
						exp1Poses[pos123] = (int)strlen(exp1[pos123]);
						printf("exp1[pos123] %s\n", exp1[pos123]);
						//exp1Pos++;
						//expand(first, pre);
					}

					if (found == 1) {
						strcat(both1, second);
						strcpy(second, both1);
					}
				} else {
					strcpy(exp1[pos123], pre);
					exp1Poses[pos123] = (int)strlen(exp1[pos123]);
					//exp1Pos++;
				}	

				if (strlen(second) != 0) {
					found = 0;
					for (int i = 0; i < (int)strlen(second); i++) {
						if (second[i] == '(') {
							found = 1;
							break;
						}
					}
					if (found == 0) {
						strcpy(exp1[exp1Pos], pre);
						strcat(exp1[exp1Pos], second);
						printf("exp1[exp1Pos] %s\n", exp1[exp1Pos]);
						exp1Poses[exp1Pos] = (int)strlen(exp1[exp1Pos]);
						if (exp1Pos+100 > POSS) {
							printf("WARNNING(3) exp1Pos %d\n", exp1Pos);
						}
						exp1Pos++;
					} else {
						if (exp1Pos+100 > POSS) {
							printf("WARNNING(4) exp1Pos %d\n", exp1Pos);
						}
						exp1Pos++;
						expand(second, pre, exp1Pos-1);
					}
				} else {
					strcpy(exp1[exp1Pos], pre);
					exp1Poses[exp1Pos] = (int)strlen(exp1[exp1Pos]);
					if (exp1Pos+100 > POSS) {
						printf("WARNNING(5) exp1Pos %d\n", exp1Pos);
					}
					if (exp1Pos+100 > POSS) {
						printf("WARNNING(6) exp1Pos %d\n", exp1Pos);
					}
					exp1Pos++;
				}
					
				//curPos = strlen(pre) + 1 + strlen(first) + 1 + strlen(second);
				printAll(); //getchar();
				printf("NB pipe\n");
				break;
			default:
				for (int z = 0; z<ind; z++) {printf("	");}printf("ERR unk [%d][%c] - ind: %d\n", regEX[curPos], regEX[curPos], ind); //getchar();
				break;
		}
	}
	printf("calling printAll\n");
	printAll();

	ind --;
}

void readToCloseBracket(char *what) {
	int bra = 1;
	char new1[100];
	for (int i = 0; i < (int)strlen(what); i++) {
		if (what[i] == '(') {
			new1[i] = what[i];
			bra++;
		} else if (what[i] == ')') {
			new1[i] = what[i];
			bra--;
		} else {
			new1[i] = what[i];
		}

		if (bra == 0) {
			new1[i] = '\0';
			//end bra reached...
			strcpy(what, new1);
			printf("new1 is [%s]\n", new1);
			return;
		}
	}
}

void follow(int *x, int *y, char c1) {
	switch (c1) {
		case '^':
			break;
		case '$':
			break;
		case 'N':
			grid[*y-1][*x] = '-';
			*y -= 2;
			break;
		case 'S':
			grid[*y+1][*x] = '-';
			*y += 2;
			break;
		case 'E':
			grid[*y][*x+1] = '|';
			*x += 2;	
			break;
		case 'W':
			grid[*y][*x-1] = '|';
			*x -= 2;
			break;
		case '(':
			break;
		case ')':
			break;
		case '|':
			break;
	}	
}
void wallit() {
	for (int y = 0; y < SZ; y++) {
		for (int x = 0; x < SZ; x++) {
			if (grid[y][x] == '?') {
				grid[y][x] = '#';
			}
		}
	}
}
void printit(int sxOrig, int syOrig, int sx, int sy) {
	grid[syOrig][sxOrig] = 'S';
	grid[sy][sx] = 'D';
	for (int y = 0; y < SZ; y++) {
		printf("%s\n", grid[y]);
	}
}
	
void populate() {
	for (int y = 0; y < SZ; y++) {
		if (y %2 == 0) {
			for (int x = 0; x < SZ; x++) {
				if (x %2 == 0) {
					grid[y][x] = '.';
				} else {
					grid[y][x] = '|';
				}
			}
		} else {
			for (int x = 0; x < SZ; x++) {
				if (x %2 == 0) {
					grid[y][x] = '?';
				} else {
					grid[y][x] = '#';
				}
			}
		}
	}
}
