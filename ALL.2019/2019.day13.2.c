#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

#include <unistd.h>

//#define getchar()
using namespace std;
void printit();

#define SIZE 9000
int lenx, leny;
#define DAY "		2019 day13 part2\n"
#undef _DEBUG_
#define MAX 4000
int instTOT = 0;
long long inst[MAX];
long long instOrig[MAX];
char instruction    [MAX][40];
int day13outs[1000000];
int day13outsPos = 0;
long long output[6] = {0};
long long nextInst[6] = {0};
long long relativeBase[6] = {0};
//int times[6] = {0};
int finished[6] = {0};
int inputCounters[6] = {0};
int phase[] = {1,1,1,1,1,-1};
int machine(int machineNumber, int one);
int prevScore = 0;
#define GR 2000
int grid[GR][GR];
int myx = GR/2;
int myy = GR/2;
int fd;
int main(int argc, char **argv)
{

	lenx = 0; leny = 0;
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);

	char line1[SIZE];
	for (int i = 0 ; i < MAX; i++) {
		inst[i] = 0;
	}

	for (int y = 0; y < GR; y++) {
		for (int x = 0; x < GR; x++) {
			grid[y][x] = -1;
		}
	}
	int newStart = 0;
	int pos = 0;
	while(1) {
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
		for (int i = 0; i < (int)strlen(line1); i++) {
			if (line1[i] == ',') {
				instruction[newStart][pos] = '\0';
				newStart++;
				pos = 0;
			} else {
				instruction[newStart][pos] = line1[i];
				pos++;
			}
		}
		leny++;
	}
	fclose(a);
	strcpy(instruction[0], "2");
	instruction[newStart][pos] = '\0';
	newStart++;
	char *stop;
	for (int i = 0; i < newStart; i++) {
		inst[i] = strtoul(instruction[i], &stop, 10);
	}
	instTOT = newStart;
	printf("START-------------\n");

	for (int i = 0; i < instTOT; i++) {
		instOrig[i] = inst[i];
	}

	for (int i = 0; i < 5; i++) {
		output[i] = 0;
		nextInst[i] = 0;
	}
	int i = -1;	
	i = 0; /////////////////////////////////	just use 1 machine
	int one = 1;
	printit();
	machine(i, one);
}


int machine(int machineNumber, int one) {
	for (int i = nextInst[machineNumber]; i < instTOT; i++) {

		int myINST = inst[i] % 100;
		if (myINST == 3) {
			//printf("got tilt 0 neu -1 left 1 right\n");

			int its4x = 0;
			for (int i = day13outsPos -3; i >= 0; i-= 3) {
				if (day13outs[i+2] == 4) {
					its4x = day13outs[i];
					break;
				}
			}
			int its3x = 0;
			for (int i = day13outsPos -3; i >= 0; i-= 3) {
				if (day13outs[i+2] == 3) {
					its3x = day13outs[i];
					break;
				}
			}
			if (inst[i] > 200) {
				if (its3x > its4x) {
					inst[relativeBase[machineNumber]+inst[i+1]] = -1;
				} else if (its3x < its4x) {
					inst[relativeBase[machineNumber]+inst[i+1]] = 1;
				} else {
					inst[relativeBase[machineNumber]+inst[i+1]] = 0;
				}

			} else {
				if (its3x > its4x) {
					inst[inst[i+1]] = -1;
				} else if (its3x < its4x) {
					inst[inst[i+1]] = 1;
				} else {
					inst[inst[i+1]] = 0;
				}
			}
			i++;
		} else if (myINST == 4) {

			{printf("got a OUTPUT 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
			if (inst[i] > 200) {
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				}
				day13outs[day13outsPos++] = inst[relativeBase[machineNumber]+inst[i+1]];

			} else if (inst[i] > 100) {
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[i+1]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[i+1]; 
				}
				day13outs[day13outsPos++] = inst[i+1];
			} else {
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[inst[i+1]]; 
				}
				day13outs[day13outsPos++] = inst[inst[i+1]];
			}
			i++;
		} else if (myINST == 99) {
			printf("GOT QUIT 99\n"); //in = 1; 
			finished[machineNumber] = 1;

			if (one == 1) {
				printf("day13outsPos is %d\n", day13outsPos);
				printit();
				printf("---------------------\n");
				int maxscore = 0;
				for (int i = 0; i < day13outsPos; i+= 3) {
					if (day13outs[i] == -1 && day13outs[i+1] == 0) {
						if (day13outs[i+2] > maxscore) {
							maxscore = day13outs[i+2];
						}
					}
				}
				printf("Score: %d\n", maxscore);

				int tot = 0;
				for (int y = 0; y < GR; y++) {
					for (int x = 0; x < GR; x++) {
						if (grid[y][x] == 2) {
							tot++;
						}
					}
				}
				fflush(stdout); dup2(fd, 1);
				printf("**ans: %d\n", maxscore);
				exit(0); }
		} else { 
			int err = 0;
			char tmpStr[20]; char tmp2[20]; sprintf(tmpStr, "%05llu", inst[i]);

			for (int k = 0; k < 4; k++) {
				tmp2[k] = tmpStr[strlen(tmpStr)-(3-k)-1];
			}
			long long mypos;
			if (inst[i] > 20000)  {
				mypos = relativeBase[machineNumber] + inst[i+3];
			} else {
				mypos = inst[i+3];
			}
			tmp2[4] = '\0';
#ifdef _DEBUG_
			printf("NOW: %s\n", tmp2); 
#endif
			long long val1, val2, ans;
			if (tmp2[1] == '0') {val1 = inst[inst[i+1]]; 
#ifdef _DEBUG_
				printf("(pos0) val1 %lld\n", inst[inst[i+1]]);
#endif
			}
			else if (tmp2[1] == '1') {val1 = inst[i+1];
#ifdef _DEBUG_
				printf("(Npos1) val1 %lld\n", val1);
#endif
			} 
			else if (tmp2[1] == '2') {val1 = inst[relativeBase[machineNumber]+inst[i+1]];
#ifdef _DEBUG_
				printf("(Rpos1) val1 %lld\n", val1);
#endif
			} 
			else { val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

			if (myINST != 9) {
				if (tmp2[0] == '0') {val2 = inst[inst[i+2]];
#ifdef _DEBUG_
					printf("(pos0) val2 %lld\n", val2);
#endif
				} else if (tmp2[0] == '1') {val2 = inst[i+2];
#ifdef _DEBUG_
					printf("(Npos1) val2 %lld\n", val2);
#endif
				} else if (tmp2[0] == '2') {val2 = inst[relativeBase[machineNumber]+inst[i+2]];
#ifdef _DEBUG_
					printf("(Rpos2) val2 %lld\n", val2);
#endif
				} else { val2 = inst[i+2];}
			}

			if (myINST == 2) {
#ifdef _DEBUG_
				printf("%lld **** %lld\n", val1, val2);
#endif
				ans = val1 * val2;
			} else if (myINST == 1) {
#ifdef _DEBUG_
				printf("%lld ++++ %lld\n", val1, val2);
#endif
				ans = val1 + val2;
			} else if (myINST == 5) {
#ifdef _DEBUG_
				for (int i = 0; i < instTOT; i++) {
					printf("%lld,", inst[i]);
				} printf("\n");
				printf("val1 is %lld\n", val1); 
#endif
				if (val1 != 0) {
#ifdef _DEBUG_
					printf("NONZ: JUMP to (%lld)\n", val2);
#endif
					i = val2-1; err = 2;
				} else {
#ifdef _DEBUG_
					printf("ZNOJUMP (%lld)\n", val1);
#endif
					err = 1;} 
			} else if (myINST == 6) {
				if (val1 == 0) {
#ifdef _DEBUG_
					printf("ZERO: JUMP to (%lld)\n", val2);
#endif
					i = val2-1; err = 2;
				} else {
#ifdef _DEBUG_
					printf("NONZ NOJMP (%lld)\n", val1);
#endif
					err = 1;}
			} else if (myINST == 7) {
				if (val1 < val2) {ans = 1;} else {ans = 0;}
#ifdef _DEBUG_
				printf("%lld <<<<< %lld\n", val1, val2); 
#endif
			} else if (myINST == 8) {
				if (val1 == val2) {ans = 1;} else {ans = 0;}
#ifdef _DEBUG_
				printf("%lld ===== %lld\n", val1, val2); 
#endif
			} else if (myINST == 9) {
				relativeBase[machineNumber] += val1;
#ifdef _DEBUG_
				printf("relativeBase Change (+%lld) -> %lld\n", val1, relativeBase[machineNumber]); 
#endif
				err = 11;
			} else {
				printf("UNK: **ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); exit(0);
				err = 10;
			}

			if (err == 0) {
#ifdef _DEBUG_
				printf("ANS (%lld) -> pos (i+3:%d) %lld (mypos %lld)\n", ans, i+3, inst[i+3], mypos); fflush(stdout);
#endif
				inst[mypos] = ans;
				char ansS[10]; sprintf(ansS, "%lld", ans); strcpy(instruction[mypos], ansS);
				i += 3;
			} else if (err == 1) {
				i += 2;
			} else if (err == 11) {
				i += 1;
			} else if (err != 2) {
				i += 3;
			} //err2 is JMP //err10 = UNK
		} 
	}
	return 10;
}
void printit() {
	int maxx = 0;
	int minx = 9999;
	int maxy = 0;
	int miny = 9999;
	int maxscore = 0;
	for (int i = 0; i < day13outsPos; i+=3) {

		if (day13outs[i+1] == 0 && day13outs[i] == -1) {if (day13outs[i+2] > maxscore) {maxscore = day13outs[i+2];} continue;} 
		if ((GR/2)+day13outs[i]   < minx) {minx = (GR/2)+day13outs[i];}
		if ((GR/2)+day13outs[i]   > maxx) {maxx = (GR/2)+day13outs[i];}
		if ((GR/2)+day13outs[i+1] < miny) {miny = (GR/2)+day13outs[i+1];}
		if ((GR/2)+day13outs[i+1] > maxy) {maxy = (GR/2)+day13outs[i+1];}

		grid[GR/2+day13outs[i+1]][GR/2+day13outs[i]] = day13outs[i+2];
	}
	printf("minx is %d maxx is %d\n", minx, maxx);
	printf("miny is %d maxy is %d\n", miny, maxy);
	printf("Score: [[%d]]\n", maxscore);
	printf("diff is %d\n", maxscore - prevScore);
	prevScore = maxscore;
	printf("day13outsPos is %d\n", day13outsPos);
	for (int y = miny; y <= maxy; y++) {
		for (int x = minx; x <= maxx; x++) {
			if (grid[y][x] != -1 && grid[y][x] != 0) {
				printf("%d", grid[y][x]);
			} else {
				printf(" ");

			}
		}
		printf("\n");
	}	
	printf("\n");
}
