#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <deque>
#include <cassert>
#include <unistd.h>

using namespace std;
int myinPos = 0;
//char myin[] = "A,B,A,C,B,B,A,B,A,CZL,10,R,8,R,8,R,12,L,8ZL,10,R,6Z2,R,6,L,10,R,12,L,8,L,10,R,12ZnZ";
//char myin[] = "A,B,CZ3ZL3ZR2ZyZ";
//char myin[] = "A,B,C,A,B,XXX,C,B,C,B,XXX,C,A,B,C,A,B,XXX,CZR,6,L,10,R,8,R,8ZR,12,L,8ZL,10Zn";
//char myin[] = "A,B,C,A,B,C,B,B,A,C,C,B,A,A,A,A,A,C,C,B,B,B,C,B,C,B,C,B,B,A,C,C,B,A,A,A,A,A,C,C,B,B,B,C,A,B,C,A,B,C,B,B,A,C,C,B,A,A,A,A,A,C,C,B,B,B,CZR,6,L,10,R,8,R,8ZR,12,L,8ZL,10ZnZ";
//-- R:6 L:10 R:8 R:8 -- R:12 L:8 -- L:10

char myin[] = "A,B,A,C,B,C,A,B,A,CZR,6,L,10,R,8,R,8ZR,12,L,8,L,10ZR,12,L,10,R,6,L,10ZnZ";
int numNewline = 0;
int numDots = 0;
int numPos = 0;
int firstHash = -1;
int lenx, leny;
int turnon = 0;
#define DAY "		2019 day 17 part2\n"
//#define _DEBUG_
#undef DEBUG
//#define getchar()
int numSteps = 0;
#define MAX 5000
int instTOT = 0;
long long inst[MAX];
long long instOrig[MAX];
char instruction    [MAX][40];

long long output[6] = {0};
long long saveInst[6][MAX] = {0};
long long nextInst[6] = {0};
long long relativeBase[6] = {0};
int times[6] = {0};
int finished[6] = {0};
int inputCounters[6] = {0};
int phase[] = {1,1,1,1,1,-1};
int machine(int machineNumber, int one);
char myInput;
char reverseInput(char in);
int OXX = 0;
int OXY = 0;
int MINPATH;
//char tmpIn[] = {'3','3','3','1','2'};
long long  tmpIn[] = {1, 2, 2,  2, 2, 2, 2, 2, 2, 2, -1};
int tmpInPos = 0;
void printit();
void next(int x, int y, int path);
int mytimes = 1;
#define SX 78
#define SY 41
char grid[SY+5][SX+5];
int yCur = 0;
int xCur = 0;
int already[SY][SX];
int MAXPATH = 0;

int pathPrev = 0;
struct pos_s {
	//char dir;
	int x;
	int y;
	deque <char> path;
};
deque <pos_s> myInputQ;
deque <char> myBack;
struct pos_s pos2;
int MOVE = 0;
deque <char> PATH;
int pathPOS = 0;
void ne(int x, int y, int endX, int endY, int px, int py, int dir, int turn, int path, char move);
int fd;
#define getchar()
int main(int argc, char **argv)
{

	struct pos_s st = {xCur, yCur, PATH};

	//myInputQ.push_back(st);
	for (int y = 0; y < SY; y++) {
		for (int x = 0; x < SX; x++) {
			grid[y][x] = '.';
		}
		grid[y][SX] = ' ';
		grid[y][SX+1] = (y%10) + 48;
	}
	for (int x = 0; x < SX; x++) {
		grid[SY][x] = ' ';
		grid[SY+1][x] = (x%10)+48;
	}

	//grid[0][0] = 'X';
	lenx = 0; leny = 0;
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdout);
	fd = dup(1); close(1);

	char line1[MAX];
	for (int i = 0 ; i < MAX; i++) {
		inst[i] = 0;
	}

	int newStart = 0;
	int pos = 0;
	while(1) {
		fgets(line1, MAX-1, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		lenx = strlen(line1);
#ifdef _DEBUG_
		printf("LINE: %s getchar\n", line1); getchar();
#endif
		for (int i = 0; i < (int)strlen(line1); i++) {
			if (line1[i] == ',') {
				instruction[newStart][pos] = '\0';
#ifdef _DEBUG_
				printf("instruction[newStart]: %s (newStart:%d)\n", instruction[newStart], newStart); 
#endif
				newStart++;
				pos = 0;
#ifdef _DEBUG_
				printf("instruction[newStart]getc\n");
				printf("getc\n");
#endif
			} else {
				if (i != 0) {
					instruction[newStart][pos] = line1[i];
				} else {
					instruction[newStart][pos] = '2';
				}
				pos++;
			}
		}
		leny++;
	}
	fclose(a);
	instruction[newStart][pos] = '\0';
	newStart++;
	char *stop;
	for (int i = 0; i < newStart; i++) {
		inst[i] = strtoul(instruction[i], &stop, 10);
#ifdef _DEBUG_
		if (inst[i] < 0) {
			printf("%lld\n", inst[i]); getchar();
		} else {
			printf("%lld\n", inst[i]);
		}
#endif
	}
	instTOT = newStart;
	printf("START-------------\n");

	for (int i = 0; i < instTOT; i++) {
		instOrig[i] = inst[i];
	}

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < instTOT; i++) {
			saveInst[j][i] = inst[i];
		}
	}

	sort(phase, phase+5);
	long long outputMAX = 0; int phaseMAX[5] = {0};
	do {	
		for (int i = 0; i < 5; i++) {
			output[i] = 0;
			nextInst[i] = 0;
			times[i] = 0;
			finished[i] = 0;
			inputCounters[i] = 0;
		}
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < instTOT; i++) {
				saveInst[j][i] = instOrig[i];
			}
		}
		int i = -1;	
restart:
		i++;
		i = i%5;
		i = 0; /////////////////////////////////	
		int one = 1;
		int ret = machine(i, one);
		if (ret == 34) {goto restart;} else if (ret == 33 && i == 4) {goto end;} else if (ret == 33 && one == 1) {goto end;}  else if (ret == 22) {goto restart;}
end:
		printf("output CONOR %lld\n", output[0]);  getchar();
		if (output[0] > outputMAX) {outputMAX = output[0]; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
		//printf("output: %lld\n", output[0]);
		//printf("outputMAX now: %lld\n", outputMAX);
	} while (next_permutation(phase, phase+5));

	printf("***OUTPUTMAX: %lld\n", outputMAX);
	printf("PHASEMAX:\n"); for (int i = 0; i < 5; i++) { printf("%d ", phaseMAX[i]); } printf("\n"); //getchar();


}

char reverseInput(char in) {
	switch (in) {
		case '1': return '2';
		case '2': return '1';
		case '3': return '4';
		case '4': return '3';
	}
	return 0;
}
void next(int x, int y, int path) {
	if (x == OXX && y == OXY) {
		printf("end reached path is %d\n", path);
		if (mytimes == 1) { mytimes++; if (path < MINPATH) {MINPATH = path;}} else {MINPATH = 0;}
	}

	if (already[y][x] == -1 || path < already[y][x]) {
		already[y][x] = path;
		switch (grid[y][x]) {
			case '#':
				return;
			case '.':
				next(x+1, y, path+1);
				next(x-1, y, path+1);
				next(x, y+1, path+1);
				next(x, y-1, path+1);
		}
	}
}

int machine(int machineNumber, int one) {
	if (finished[machineNumber] == 1) { return 22;}
	long long input[10];	

	for (int i = 0; i < instTOT; i++) {
		inst[i] = saveInst[machineNumber][i];
	}

	int inputCounter = inputCounters[machineNumber];

	if (machineNumber == 0 && times[machineNumber] == 0) {
		input[1] = 1; 
		input[0] = phase[machineNumber];
	} else {
		input[1] = output[machineNumber];
		input[0] = phase[machineNumber];
	}

	for (int i = nextInst[machineNumber]; i < instTOT; i++) {
#ifdef _DEBUG_
		printf("\nNEW NEW NEW:::"); fflush(stdout);
		printf("POS InstNUM: (%d) ", i); fflush(stdout);
		printf(" is [%lld] ", inst[i]); fflush(stdout); //getchar();
#endif

		int myINST = inst[i] % 100;
		if (myINST == 3) {
			{printf("got a 3 (using %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]);}
#ifdef _DEBUG_
#endif
			printf("myInput is [%c]\n", myInput); printf("%d,%d \n", xCur, yCur);// getchar();
			if (inst[i] > 200) {
				printf("giveinput\n");
				///char in[100]; gets(in); fflush(stdin);
				//inst[relativeBase[machineNumber]+inst[i+1]] = input[inputCounter];
				///printf("in is %s\n", in); printf("int of in is %d\n", in[0]);
				//printf("giving %d\n", in[0]); getchar();
				if (myin[myinPos] == 'Z') {
					myin[myinPos] = '\n';
				}
				inst[relativeBase[machineNumber]+inst[i+1]] = (int)myin[myinPos++];
			} else {
				///input[inputCounter] = (long long)(myInput - 48);
				printf("giveinput\n");
				//char in[100]; gets(in); fflush(stdin);

				///printf("in is %s\n", in);
				//printf("giving %d\n", in[0]); getchar();
				if (myin[myinPos] == 'Z') {
					myin[myinPos] = '\n';
				}
				//inst[inst[i+1]] = input[inputCounter];
				inst[inst[i+1]] = (int)myin[myinPos++];
			}
			if (inputCounter != 1) {
				inputCounter++;
			}
			i++; printf("leaving 3 (input)...\n"); fflush(stdout);
			//printit(); getchar();
		} else if (myINST == 4) {
			printf("here5...\n"); fflush(stdout);
			{printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
#ifdef _DEBUG_
#endif
			//OUT 0 == Wall 1 == OK 2==OX
			numSteps++;
			long long OUT;
			if (inst[i] > 200) {
				input[1] = inst[relativeBase[machineNumber]+inst[i+1]];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				}
				OUT =  inst[relativeBase[machineNumber]+inst[i+1]];

				printf("REL OUT: %lld (base: %lld+%lld)\n", inst[relativeBase[machineNumber]+inst[i+1]],
						relativeBase[machineNumber], inst[i+1]);
#ifdef _DEBUG_
#endif
			} else if (inst[i] > 100) {
				printf("or is it OUT: %lld\n", inst[i+1]);
#ifdef _DEBUG_
				printf("or is it OUTS: %s\n", instruction[i+1]);
#endif
				input[1] = inst[i+1];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[i+1]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[i+1]; 
				}
				OUT = inst[i+1];
			} else {
				printf("OUT: %lld\n", inst[inst[i+1]]); 
#ifdef _DEBUG_
				printf("OUTS: %s\n", instruction[inst[i+1]]);
#endif
				input[1] = inst[inst[i+1]];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[inst[i+1]]; 
				}
				OUT = inst[inst[i+1]];
			}
			struct pos_s pos1;

			switch(OUT) {
				case (35): {
						   if (firstHash == -1) {
							   firstHash = numDots;
							   printf("firstHash is %d\n", firstHash); //getchar();
						   }
						   printf("got a 35 : hash \n");
						   numPos++;
						   if (turnon == 1) { getchar(); }
						   grid[yCur][xCur] = '#';
						   xCur++;
						   //yCur = yPrev; xCur = xPrev;
						   //myBack.pop_front();
						   //MOVE = 0;
						   break;
					   }
				case (46): {
						   printf("got a 46 : dot numDots (%d)\n", numDots);// getchar();
						   numDots++;
						   numPos++;
						   if (turnon == 1) { getchar(); }
						   grid[yCur][xCur] = '.';
						   xCur++;
						   //MOVE = 0;
						   break;
					   }
				case (10):
					   {
						   //grid[yCur][xCur] = '.';
						   xCur = 0;
						   yCur++;
						   printf("got a 10: newline %d numNewline(%d)\n", numSteps, numNewline); //getchar();
						   numNewline++;
						   numDots = 0;
						   firstHash = -1;
						   numPos = 0;
						   if (turnon == 1) { getchar(); }
						   //MOVE = 0;
						   //OXX = xCur;
						   //OXY = yCur;
						   //printf("found OXEGEN at %d,%d\n", xCur, yCur); //getchar(); getchar();// exit(0);
						   break;
					   }
				default: //if ((char)OUT == '?') {turnon = 1;} printf("got other, OUT %lld (%c) numNewline %d numPos %d\n", OUT, (int)OUT, numNewline, numPos); getchar();
					   printf("got other, OUT %lld (%c) numNewline %d numPos %d\n", OUT, (int)OUT, numNewline, numPos); getchar();
					   if (OUT < 256) {
						   printf("got other, OUT %lld (%c) numNewline %d numPos %d\n", OUT, (int)OUT, numNewline, numPos); 
					   } else {
						   printf("got other, OUT %lld \n", OUT); getchar(); 
						   fflush(stdout); dup2(fd, 1);
						   printf("**ans: %lld\n", OUT);
						   exit(0);
					   }

			}

			for (int i = 0; i < instTOT; i++) {
				saveInst[machineNumber][i] = inst[i];
			}
			nextInst[machineNumber] = i+2;
			times[machineNumber]++;
			inputCounters[machineNumber] = inputCounter;
			return 34;
			//i++;
		} else if (myINST == 99) {
			printf("GOT QUIT 99\n"); //in = 1; 
#ifdef _DEBUG_
#endif
#ifdef _DEBUG_
			printf("INSTS:\n");
			for (int i = 0; i < instTOT; i++) {
				printf("%lld ", inst[i]);

			}
			printf("\n");
#endif
			finished[machineNumber] = 1;

			//printit();
			if (one == 1) {printf("numSteps is %d\n", numSteps);

				int stX = -1; int stY;
				int enX; int enY;
				for (int y = 1; y < SY-1; y++) {
					for (int x = 1; x < SX-1; x++) {
						if (grid[y][x] == '#') {
							int count = 0;
							if (grid[y-1][x] == '.') {
								count++;
							}
							if (grid[y+1][x] == '.') {
								count++;
							}
							if (grid[y][x+1] == '.') {
								count++;
							}
							if (grid[y][x-1] == '.') {
								count++;
							}
							if (count == 3 && stX == -1) {
								stX = x; stY = y;
								y+=3; //jump past the boggie
							} else if (count == 3) {
								enX = x; enY = y;
							}
						}

					}
				}

				for (int y = 0; y < SY; y++) {
					for (int x = 0; x < SX; x++) {
						if (grid[y][x] == '#') {
							if (grid[y][x+1] == '#' && grid[y][x-1] == '#' && grid[y+1][x] == '#' && grid[y-1][x] == '#') {
								grid[y][x] = 'o';
							}
						}

					}
				}
				int alignment = 0;
				for (int y = 0; y < SY; y++) {
					for (int x = 0; x < SX; x++) {
						if (grid[y][x] == 'o' ) {
							alignment += y*x;
							/*
							   if (y == 10 && x == 56) {}  else {
							   alignment += y*x;
							   }
							   */
						}
					}
				}
				printf("stX, stY %d,%d\n", stX, stY);
				printf("enX, enY %d,%d\n", enX, enY);
				printf("**alignment is %d (minus bogie...)\n", alignment);

				//printit();
				for (int y = 0; y < SY; y++) {
					for (int x = 0; x < SX; x++) {
						already[y][x] = -1;
					}
				}
				already[stY][stX] = 1;
				ne(stX, stY-1, enX, enY, stX, stY, 'U', 'n', 1, 'S');
				/*CONOR2*/

				int testit = 0;
				if (testit == 1) {
					int SXT = 14;
					int SYT = 8;
					char gridT[SYT][SXT];
					strcpy(gridT[0], "..#..........");
					strcpy(gridT[1], "..#..........");
					strcpy(gridT[2], "#######...###");
					strcpy(gridT[3], "#.#...#...#.#");
					strcpy(gridT[4], "#############");
					strcpy(gridT[5], "..#...#...#..");
					strcpy(gridT[6], "..#####...#..");

					for (int y = 0; y < SYT; y++) {
						printf("%s\n", gridT[y]);
					}

					for (int y = 0; y < SYT; y++) {
						for (int x = 0; x < SXT; x++) {
							if (gridT[y][x] == '#') {
								if (gridT[y][x+1] == '#' && gridT[y][x-1] == '#' && gridT[y+1][x] == '#' && gridT[y-1][x] == '#') {
									gridT[y][x] = 'o';
								}
								/*
								   if (x+1 < SXT && gridT[y][x+1] == '#' && y-1 > 0 && gridT[y-1][x] == '#') {
								   gridT[y][x] = 'o';
								   }
								   if (x-1 > 0 && gridT[y][x-1] == '#' && y+1 < SYT && gridT[y+1][x] == '#') {
								   gridT[y][x] = 'o';
								   }
								   if (x+1 < SXT && gridT[y][x+1] == '#' && y+1 < SYT && gridT[y+1][x] == '#') {
								   gridT[y][x] = 'o';
								   }
								   if (x-1 > 0 && gridT[y][x-1] == '#' && y-1 >0 && gridT[y-1][x] == '#') {
								   gridT[y][x] = 'o';
								   }
								   */
							}

						}
					}
					for (int y = 0; y < SYT; y++) {
						printf("%s\n", gridT[y]);
					}
					int alignmentT = 0;
					for (int y = 0; y < SYT; y++) {
						for (int x = 0; x < SXT; x++) {
							if (gridT[y][x] == 'o' ) {
								alignmentT += y*x;
							}
						}
					}
					printf("**alignmentT is %d\n", alignmentT);
					assert(alignmentT == 76);
				}

				//for (int y = 0; y < SY; y++) { for (int x = 0; x < SX; x++) { already[y][x] = -1; } }

				exit(0);}
			if (machineNumber == 4) {return 33;} else if (machineNumber == 0 && one == 1) {return 33;} else {return 22;}
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
			if (tmp2[2] != '0') {
				printf("tmp2... not zero... [[ %s ]]\n", tmp2);  exit(0);
			}
			tmp2[4] = '\0';
#ifdef _DEBUG_
			printf("NOW: %s\n", tmp2); 
#endif
			long long val1, val2, ans;

			if (tmp2[1] == '0') {

				val1 = inst[inst[i+1]]; 
#ifdef _DEBUG_
				printf("(pos0) val1 %lld\n", inst[inst[i+1]]);
#endif
			}
			else if (tmp2[1] == '1') {


				val1 = inst[i+1];
#ifdef _DEBUG_
				printf("(Npos1) val1 %lld\n", val1);
#endif
			} 
			else if (tmp2[1] == '2') {val1 = inst[relativeBase[machineNumber]+inst[i+1]];
				printf("(Rpos1) val1 %lld\n", val1);
#ifdef _DEBUG_
#endif
			} 
			else { printf("HERE"); /*getchar();*/ val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

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
				} else { printf("HERE2"); /*getchar(); */val2 = inst[i+2];}
			} else {
				printf("GOT A NINE\n"); //getchar();
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
				//getchar();
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
	//printf("output CONOR %lld COUNT %d\n", output, count); //getchar(); getchar();
	//if (output > outputMAX) {outputMAX = output; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
	//printf("output: %lld\n", output);
	return 10;
}
void printit() {
	for (int y = 0; y < SY+2; y++) { 
		for (int x = 0; x<SX+2; x++) {
			if (x == xCur && y == yCur) {
				printf("D");
			} else {
				printf("%c", grid[y][x]);
			}
		} 
		printf("\n");
	} printf("\n");
}

void ne(int x, int y, int endX, int endY, int px, int py, int dir, int turn, int path, char move) {
	//printf("in ne... x,y %d,%d\n", x, y);
	if (endX == x && endY == y) { printf("end reached"); return; }
	if (grid[y][x] == '.') {printf("DOT\n"); return;}
	if (x < 0 || x > SX || y < 0 || y > SY) {printf("OOR\n"); return;}
	if (turn == 'y') {printf(":%d %c", path - pathPrev, move); pathPrev = path;}
	if (already[y][x] == -1 || grid[y][x] == 'o') {
		already[y][x] = 1;
		if (dir == 'U' && (grid[y-1][x] == '#'  || grid[y-1][x] == 'o')&& (already[y-1][x] == -1 || grid[y-1][x] == 'o') && y-1 >= 0 ) {
			ne(x, y-1, endX, endY, x, y, 'U', 'n', path+1, 'S');
			return;
		} else if (dir == 'D' && (grid[y+1][x] == '#'  || grid[y+1][x] == 'o')&& (already[y+1][x] == -1 || grid[y+1][x] == 'o') && y+1 < SY) {
			ne(x, y+1, endX, endY, x, y, 'D', 'n', path+1, 'S');
			return;
		} else if (dir == 'R' && (grid[y][x+1] == '#'  || grid[y][x+1] == 'o')&& (already[y][x+1] == -1 || grid[y][x+1] == 'o') && x+1 < SX) {
			ne(x+1, y, endX, endY, x, y, 'R', 'n', path+1, 'S'); 
			return;
		} else if (dir == 'L' && (grid[y][x-1] == '#' || grid[y][x-1] == 'o') && (already[y][x-1] == -1 || grid[y][x-1] == 'o') && x-1 >= 0) {
			ne(x-1, y, endX, endY, x, y, 'L', 'n', path+1, 'S');
			return;
		} else if (dir == 'U' && (grid[y][x-1] == '#'  || grid[y][x-1] == 'o')&& (already[y][x-1] == -1|| grid[y][x-1] == 'o')  && x-1 >= 0) {
			ne(x-1, y, endX, endY, x, y, 'L', 'y', path+1, 'L');
			return;
		} else if (dir == 'U' && (grid[y][x+1] == '#'  || grid[y][x+1] == 'o')&& (already[y][x+1] == -1 || grid[y][x+1] == 'o') && x+1 < SX) {
			ne(x+1, y, endX, endY, x, y, 'R', 'y', path+1, 'R'); 
			return;
		} else if (dir == 'D' && (grid[y][x+1] == '#'  || grid[y][x+1] == 'o')&& (already[y][x+1] == -1 || grid[y][x+1] == 'o') && x+1 < SX) {
			ne(x+1, y, endX, endY, x, y, 'R', 'y', path+1, 'L');
			return;
		} else if (dir == 'D' && (grid[y][x-1] == '#'  || grid[y][x-1] == 'o')&& (already[y][x-1] == -1 || grid[y][x-1] == 'o') && x-1 >= 0) {
			ne(x-1, y, endX, endY, x, y, 'L', 'y', path+1, 'R'); 
			return;
		} else if (dir == 'L' && (grid[y+1][x] == '#'  || grid[y+1][x] == 'o')&& (already[y+1][x] == -1 || grid[y+1][x] == 'o') && y+1 < SY) {
			ne(x, y+1, endX, endY, x, y, 'D', 'y', path+1, 'L');
			return;
		} else if (dir == 'L' && (grid[y-1][x] == '#'  || grid[y-1][x] == 'o')&& (already[y-1][x] == -1 || grid[y-1][x] == 'o') && y-1 >= 0) {
			ne(x, y-1, endX, endY, x, y, 'U', 'y', path+1, 'R'); 
			return;
		} else if (dir == 'R' && (grid[y-1][x] == '#'  || grid[y-1][x] == 'o')&& (already[y-1][x] == -1 || grid[y-1][x] == 'o') && y-1 >= 0) {
			ne(x, y-1, endX, endY, x, y, 'U', 'y', path+1, 'L'); 
			return;
		} else if (dir == 'R' && (grid[y+1][x] == '#'  || grid[y+1][x] == 'o')&& (already[y+1][x] == -1 || grid[y+1][x] == 'o') && y+1 < SY) {
			ne(x, y+1, endX, endY, x, y, 'D', 'y', path+1, 'R'); 
			return;
		}
	}
}
