#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <iostream>
#include <map>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
char inst[300][10];

struct diffs_s {
	int one;
	int two;
	int three;
};
struct diffs_s diffs[15];
int diffsPos = 0;

char input[50] = "89999999999999"; 
//char input[] = "12";
long long zvar = 0;
char inputPrev[15];
void sigfunc(int a) {
	printf("[[ %s ]] zvar:[[%lld]]\n", inputPrev, zvar);
}


int main(int argc, char **argv)
{
	printf("SLOW: ~2mins\n");
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 24.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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
	strcpy(input, "89999999999999");
	int c = 0;
	while (1) {
		if (c == 20000) {break;}
		c++;
		//for (int r = 0; r < 4; r++) { vars[r] = varsSave[samePos][r]; }
		memset(vars, 0, sizeof(vars));
		//printf("%lld %lld %lld %lld\n", vars[0], vars[1], vars[2], vars[3]);
		iPos = 0;
		//printf("input: [%s]\n", input); getchar();

		//printf("startPos: %d\n", poses[samePos]);
		//for (i = poses[samePos]; i < leny; i++) 
		for (i = 0; i < leny; i++) {
			//printf("inst: %s\n", inst[i]);
			restartVal = i % 18;
			switch(inst[i][0]) {
				case 'i': {
						  diffsPos++; // ONCON
							      //diffsPos = 0;
							      //printf("inp restartVal is %d -- diffsPos %d\n", restartVal, diffsPos);
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
		//printf("input: %s ansz: %lld\n", input, vars['z' - 119]);


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
	printf("after...\n");
	getchar();

	for (int i = 0; i < 14; i++) {
		printf("%d %d %d\n", diffs[i].one, diffs[i].two, diffs[i].three);
	}
	//getchar();

	struct stage_s {
		int pos;
		map <int, int> mp;
		map <int, pair<long long, int>> mp2;
		int max;
		unsigned long long minus;
	};

	struct stage_s stage[14];
	for (int i = 0; i < 14; i++) {
		stage[i].pos = i;
		stage[i].minus = pow(10, 13-i);
		printf("i: %d -- %llu\n", i, stage[i].minus);
	}
	stage[0].max = 100;
	stage[1].max = 1000;
	stage[2].max = 20000;
	stage[3].max = 300000;
	stage[4].max = 8000000;
	stage[5].max = 400000;
	stage[6].max = 8000000;
	stage[7].max = 300000;
	stage[8].max = 20000;
	stage[9].max = 1000;
	stage[10].max = 20000;
	stage[11].max = 1000;
	stage[12].max = 1000;
	stage[13].max = 1000;

	printf("starting fast...\n"); getchar();
	strcpy(input, "99999999999999");
	int w = 0, x = 1, y = 2, z= 3;		
	samePos = 0;
	//long long same[15][4] = {0};

	int var_incr = -1;
	int kk = -1;

again4:
	kk++; 
	if (kk >= 14) {printf("kk 14 -- goto end\n"); goto end;}
	//strcpy(input, "99999999999999");
	strcpy(input,   "11111111111111");
	printf("in goto again4 kk:%d-- input [%s]\n", kk, input);
	long long max = 0;
	for (int qq = 0; qq < 9; qq++) {
		var_incr = -1;
		int first11 = 1;
again2:
		var_incr++;
		{
			vars[w] = 0; vars[x] = 0; vars[y] = 0; vars[z] = 0;
			vars[z] = var_incr; //CONCON
			if (kk==13) {assert(vars[z] == 0);}
			for (int i = 13-kk; i <= 13-kk; i++) {
				//inp w
				vars[w] = input[i] - 48;
				if (kk == 13 && first11 == 1) {first11 = 0; printf("[%s] input[i] is %c\n", input, input[i]);}
				//mul x 0

				vars[x] = vars[z];
				//mod x 26
				vars[x] %= 26;
				//div z QQQ
				vars[z] /= diffs[i].one; 
				//add x QQQ
				vars[x] += diffs[i].two;
				//eql x w
				vars[x] = (vars[x] == vars[w]) ? 0 : 1;

				vars[y] = 25;

				//mul y x
				vars[y] *= vars[x];
				vars[y]++;
				//mul z y
				vars[z] *= vars[y];

				vars[y] = vars[w];
				///add y QQQ
				vars[y] += diffs[i].three;
				///mul y x
				vars[y] *= vars[x];
				///add z y
				vars[z] += vars[y];
				//same[i+1][0] = vars[0]; same[i+1][1] = vars[1]; same[i+1][2] = vars[2]; same[i+1][3] = vars[3];
				//printf("END(%d) %lld %lld %lld %lld\n", i+1, vars[0], vars[1], vars[2], vars[3]); fflush(stdout); getchar(); 
				if (kk == 13) {printf("vars[z] is %lld\n", vars[z]);}
				//if (kk == 12 && (var_incr >= 13 && var_incr <=21)) {printf("kk:12 13=<var_incr:<=21 vars[z] is %lld\n", vars[z]);}

			}
			/*
			   for (int j = 0; j < stage[13-kk].vec.size(); j++) {
			   if (stage[13-kk].vec[j].first == vars[z]) {
			   {printf("4ndlast: zmustbe:[%d] (189-404): %lld  in:[[ %s ]] (4nd last dig)-- valid\n", var_incr, vars[z], input); getchar();} 

			   }
			   }
			   */
		}
		if (kk == 0) {
			if (vars[z]  == 0) {
				printf("[%d] %lld in: [[ %s ]]-- valid\n", var_incr, vars[z], input);
				stage[13-kk].mp[var_incr] = input[13-kk];
				stage[13-kk].mp2[var_incr] = pair(vars[z], input[13-kk]-48);
				//printf("var_incr %d -- input[13-kk] %c\n", var_incr, input[13-kk]); //getchar();
				if (vars[z] > max) {max = vars[z];}

			}
		} else {
			if (stage[13-(kk-1)].mp.find(vars[z]) != stage[13-(kk-1)].mp.end()) {
				stage[13-kk].mp[var_incr] = input[13-kk];
				stage[13-kk].mp2[var_incr] = pair(vars[z], input[13-kk]-48);
				if (kk==13) {
					printf("valid: vars[z]: (%lld) kk:%d var_incr %d -- input[13-kk] %c\n", vars[z], kk, var_incr, input[13-kk]); //getchar();
				}
				if (vars[z] > max) {max = vars[z];}
			}
		}
		strcpy(inputPrev, input);
		if (kk != 13 && var_incr != stage[kk].max) {
			goto again2;
		}

		if (qq == 8) {
			if (kk > 0) {
				printf("max for kk %d (adjust-max k:%d) is %lld V stage[kk-1].max:%d\n", kk, kk-1, max, stage[kk-1].max);
			} else {
				printf("max for kk %d is %lld V nomax\n", kk, max);
			}
		}
		int found;
		do {
			char *ex; long long inLL =  strtoll(input, &ex, 10); inLL += stage[13-kk].minus;
			sprintf(input, "%014lld", inLL);
			found = 0;
			if (inLL == 99999999999999 && kk==13) {break;}
			for (int z = 0; z < 14; z++) {
				if (input[z] == '0' ) {
					found = 1; break;
				}
			}

		} while (found == 1);	
	}

	if (kk < 14) {
		if (kk == 13) {printf("input [%s] -- vars[z]: %lld\n", input, vars[z]);}
		goto again4;
	}
end:
	for (int p  =0 ; p < 4; p++) { printf("%c: %lld\n", p+119, vars[p]); }


	int var_max = 0;
	int digit_max = 0;
	for (auto it = stage[0].mp2.begin(); it!=stage[0].mp2.end(); it++) {
		pair x11 = it->second;
		if (x11.second > digit_max) {digit_max = x11.second; var_max = x11.first;}
		printf("x11.first %lld x11.second %d\n", x11.first, x11.second);
	}
	printf("first digit is %d %c\n", digit_max, digit_max);
	char ans[30];
	char anstmp[20];
	sprintf(ans, "%d", digit_max);
	for (int ii = 1; ii < 14; ii++) {
		pair p1 = stage[ii].mp2[var_max];
		var_max = p1.first;
		int digit1 = p1.second;
		//pair p2 = stage[ii+1].mp2[out1];
		printf("digit %d: %d\n", ii, digit1);
		strcpy(anstmp, ans);
		sprintf(ans, "%s%d", anstmp, digit1);
	}

	dup2(fd, 1);
	printf("**ans [[ %s ]]\n", ans);
	exit(0);

}
