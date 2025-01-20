#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <deque>
#include <cassert>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2019 day 23 part1\n"
#undef _DEBUG_
//#define _DEBUG_
#define getchar()
int numSteps = 0;
#define MAX 9000
#define MAXI 4000
int instTOT = 0;
#define NM 50

long long inst[NM+1][MAXI];
long long instOrig[MAXI];
char instruction[NM+1][MAXI][40];
char instructionOrig[MAXI][40];
long long output[NM+1][6] = {0};
long long saveInst[NM+1][6][MAXI] = {0};
long long nextInst[NM+1][6] = {0};
long long relativeBase[NM+1][6] = {0};
int times[NM+1][6] = {0};
int finished[NM+1][6] = {0};
int inputCounters[NM+1][6] = {0};
int phase[] = {1,1,1,1,1,-1};
int machine(int var_mach, int machineNumber, int one);

char myInput;
char reverseInput(char in);
int MINPATH;
int OXX, OXY;
////////////////////////day23
int destReady[NM+1];
int booting[NM+1];
int watch[NM+1];
deque<long long> Q[NM+1];
void *callMachine(void *threadid);
int machineMulti(int var_mach, int machineNumber, int one, long long inst[MAXI], char instruction[MAXI][40],
	long long output[6], int times[6], int finished[6], int inputCounters[6], long long saveInst[6][MAXI],
	long long nextInst[6], long long relativeBase[6]);
////////////////////////day23
//char tmpIn[] = {'3','3','3','1','2'};
long long  tmpIn[] = {0, 0, 1,  0, 2, 0, 3, 2, 2, 2, -1};

int tmpInPos = 0;
void printit();
void next(int x, int y, int path);
int mytimes = 1;
#define SX 51
#define SY 51
int grid[SY+5][SX+5];
int yCur = 0;
int xCur = 0;
int already[SY][SX];
int MAXPATH = 0;
int fd;
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
int main(int argc, char **argv)
{
	time_t rawtime;
	struct tm *info;
	time( &rawtime );
	info = localtime( &rawtime );
	printf("%s", asctime(info));
	for (int i = 0; i < NM; i++) {
		destReady[i] = 1;
		booting[i] = 1;
		watch[i] = 0;
	}
	
	struct pos_s st = {xCur, yCur, PATH};
	
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); fd = dup(1); close(1);
        char line1[MAX];
	for (int i = 0 ; i < MAX; i++) {
		inst[0][i] = 0;
	}

	int newStart = 0;
	int pos = 0;
while(1) {
        fgets(line1, MAX-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	//printf("LINE: %s getchar\n", line1); getchar();
#endif
	for (int i = 0; i < (int)strlen(line1); i++) {
		if (line1[i] == ',') {
			instruction[0][newStart][pos] = '\0';
			instructionOrig[newStart][pos] = '\0';
			newStart++;
			pos = 0;
		} else {
			instruction[0][newStart][pos] = line1[i];
			instructionOrig[newStart][pos] = line1[i];
			pos++;
		}
	}
	leny++;
}
	fclose(a);
	newStart++;
	instruction[0][newStart][pos] = '\0';
	instructionOrig[newStart][pos] = '\0';
	for (int k = 1; k < NM; k++) {
		for (int j = 0; j < newStart; j++) {
			strcpy(instruction[k][j], instruction[0][j]);
		}
	}
		
//RErestart:
	for (int k = 0; k < NM; k++) {
		for (int i = 0; i < 6; i++) {
			output[k][i] = 0;
			nextInst[k][i] = 0;
			relativeBase[k][i] = 0;
			times[k][i] = 0;
			finished[k][i] = 0;
			inputCounters[k][i] = 0;
		}
	}
	//long long saveInst[NM][6][MAXI] = {0};
	for (int k = 0; k < NM; k++) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < MAXI; j++) {
				saveInst[k][i][j] = 0;
			}
		}
	}
	
	for (int i = 0; i < newStart; i++) {
		strcpy(instruction[0][i], instructionOrig[i]);
	}
	char *stop;
	for (int i = 0; i < newStart; i++) {
		inst[0][i] = strtoul(instruction[0][i], &stop, 10);
#ifdef _DEBUG_
		if (inst[0][i] < 0) {
		//	printf("%lld\n", inst[0][i]); getchar();
		} else {
		//	printf("%lld\n", inst[0][i]);
		}
#endif
	}
	instTOT = newStart;
	printf("START-------%d------\n", instTOT); getchar();

	for (int i = 0; i < instTOT; i++) {
		instOrig[i] = inst[0][i];
	}

	for (int k = 1; k < NM; k++) {
		for (int i = 0; i < instTOT; i++) {
			inst[k][i] = instOrig[i];
		}
	}
	for (int k = 0; k < NM; k++) {
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < instTOT; i++) {
				saveInst[k][j][i] = inst[k][i];
			}
		}
	}

	//sort(phase, phase+5);
	//long long outputMAX = 0; int phaseMAX[5] = {0};

	pthread_t threads[NM+2];
	int rc;
	
	for (long i = 0; i < NM; i++) {
		rc = pthread_create(&threads[i], NULL, callMachine, (void *) i);
		if (rc) {printf("ERR creating thread %d\n", rc); exit(-1);}
	}

	for (int i = 0; i < NM; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("AFTER\n");
	getchar();
	printf("AM I EXITTING HERE\n");
	//exit(0);

}

void *callMachine(void *threadid) {
	int one = 1;
	long tid = (long)threadid;
	
        for (int i = 0; i < 5; i++) {
               output[tid][i] = 0;
               nextInst[tid][i] = 0;
               times[tid][i] = 0;
               finished[tid][i] = 0;
               inputCounters[tid][i] = 0;
        }
        for (int j = 0; j < 5; j++) {
               for (int i = 0; i < instTOT; i++) {
                        saveInst[tid][j][i] = instOrig[i];
                }
        }
	
again:
	int ret = machineMulti(tid, 0, one, inst[tid], instruction[tid], output[tid], times[tid],
		finished[tid], inputCounters[tid], saveInst[tid], nextInst[tid], relativeBase[tid]);
	printf("AFTER machineMulti\n"); fflush(stdout); getchar();


	if (ret != 34) {printf("ret not 34 (%d)\n", ret);}
	goto again;
	return NULL;
}

int machineMulti(int var_mach, int machineNumber, int one, long long inst[MAXI], char instruction[MAXI][40],
	long long output[6], int times[6], int finished[6], int inputCounters[6], long long saveInst[6][MAXI], 
	long long nextInst[6], long long relativeBase[6]) {
		if (finished[machineNumber] == 1) { printf("return 22\n"); return 22;}
		long long input[10];	

		for (int i = 0; i < instTOT; i++) {
			inst[i] = saveInst[machineNumber][i];
		}

		int inputCounter = inputCounters[machineNumber];

		if (machineNumber == 0 && times[machineNumber] == 0) {
			//input[1] = 1; 
			//input[0] = phase[machineNumber];
		} else {
			//input[1] = output[machineNumber];
			//input[0] = phase[machineNumber];
		}
 
	long long QNUM = 0;
	for (int i = nextInst[machineNumber]; i < instTOT; i++) {
#ifdef _DEBUG_
                printf("\nNEW NEW NEW:::"); fflush(stdout);
                printf("POS InstNUM: (%d) ", i); fflush(stdout);
                printf(" is [%lld] ", inst[i]); fflush(stdout); //getchar();
#endif

		int myINST = inst[i] % 100;
		if (myINST == 3) {
			//{printf("got a 3 (THREAD: %d) \n", var_mach);}
#ifdef _DEBUG_
#endif
			//printf("myInput is [%c]\n", myInput); printf("%d,%d \n", xCur, yCur);// getchar();
                        if (inst[i] > 200) {
				//inst[relativeBase[machineNumber]+inst[i+1]] = input[inputCounter];
				if (booting[var_mach] == 1) {
					printf("booting %d\n", var_mach);
					inst[relativeBase[machineNumber]+inst[i+1]] = var_mach;
				} else if (Q[var_mach].empty()) {
					//printf("Q is empty\n");
					inst[relativeBase[machineNumber]+inst[i+1]] = -1;
					usleep(100);
				} else {
					//printf("Q not empty\n");
					inst[relativeBase[machineNumber]+inst[i+1]] = Q[var_mach].front();
					//printf("recv %lld\n", Q[var_mach].front()); getchar();
					Q[var_mach].pop_front();
				}
					
			} else {
				///input[inputCounter] = (long long)(myInput - 48);
				//inst[inst[i+1]] = input[inputCounter];
				if (booting[var_mach] == 1) {
					printf("booting %d\n", var_mach);
					inst[inst[i+1]] = var_mach;
				} else if (Q[var_mach].empty()) {
					//printf("Q is empty\n");
					inst[inst[i+1]] = -1;
					usleep(100);
				} else {
					//printf("Q not empty\n");
					//printf("recv %lld\n", Q[var_mach].front()); getchar();
					inst[inst[i+1]] = Q[var_mach].front();
					Q[var_mach].pop_front();
				}
			}
			//if (inputCounter != 1) { inputCounter++; }

			i++; 
			//printf("leaving 3 (input)... mach [[ %d ]]\n", var_mach); fflush(stdout); 
			getchar();
			if (booting[var_mach] == 1) {
				booting[var_mach] = 0;
			}
		} else if (myINST == 4) {
			//printf("here5...\n"); fflush(stdout);
                        //{printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
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

#ifdef _DEBUG_
                                printf("REL OUT: %lld (base: %lld+%lld)\n", inst[relativeBase[machineNumber]+inst[i+1]],
					relativeBase[machineNumber], inst[i+1]);
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
#ifdef _DEBUG_
                                printf("OUT: %lld\n", inst[inst[i+1]]); 
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

			if (destReady[var_mach] == 1) {
				//printf("got a 0-50 (maybe 255) dest addr..[[[[%lld]]\n", OUT);
				if (OUT < 0 || OUT > 49) {printf("OUT is %lld\n", OUT);}
				watch[var_mach] = 0;
				QNUM = OUT;
				if (OUT == 255) {time_t rawtime; struct tm *info; time (&rawtime); info = localtime(&rawtime); printf("%s\n", asctime(info)); watch[var_mach] = 1; printf("the next Y is the ANS\n");}
				destReady[var_mach]++;
				getchar();
			} else if (destReady[var_mach] == 2) {
				long long Xval = OUT;
				//printf("got a Xval %lld\n", Xval);
				destReady[var_mach]++;
				if (QNUM < 50) {
					Q[QNUM].push_back(Xval);
				} else {
					printf("oops QNUM is %lld Xval %lld\n", QNUM, Xval);
				}
			} else if (destReady[var_mach] == 3) {
				long long Yval = OUT;
				//printf("got a Yval %lld [%d]\n", Yval, var_mach);
				if (QNUM > 49 || watch[var_mach] == 1) {
					char cans[100];
					sprintf(cans, "touch %lld", Yval);
					system(cans);
					fflush(stdout); dup2(fd, 1);
					printf("ANS is %lld\n", Yval); exit(0);
				} else {
					destReady[var_mach] = 1;
					Q[QNUM].push_back(Yval);
				}
			} else {
				printf("UNK OUT %lld destReady[%d] is %d\n", OUT, var_mach, destReady[var_mach]); //exit(0);
			}

	
			for (int i = 0; i < instTOT; i++) {
				saveInst[machineNumber][i] = inst[i];
			}
			nextInst[machineNumber] = i+2;
			times[machineNumber]++;
			inputCounters[machineNumber] = inputCounter;
			//printf("return 34\n");
			//return 34;
                        i++;
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
			

			printf("got a 99\n"); fflush(stdout);
			getchar();
			//exit(0);

			if (machineNumber == 4) {printf("return 33\n"); return 33;} else if (machineNumber == 0 && one == 1) {printf("return 33\n"); return 33;} else {printf("return 22"); return 22;}
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
				printf("tmp2... not zero... [[ %s ]]\n", tmp2); getchar(); getchar(); //exit(0);
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
#ifdef _DEBUG_
				printf("(Rpos1) val1 %lld\n", val1);
#endif
} 
			else { printf("HERE"); getchar(); val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

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
				} else { printf("HERE2"); getchar(); val2 = inst[i+2];}
	                } else {
#ifdef _DEBUG_
				printf("GOT A NINE\n");
#endif
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
				//for (int i = 0; i < instTOT; i++) {
				//	printf("%lld,", inst[i]);
			//	} printf("\n");
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
				printf("AN EXIT HERE1\n");
				printf("UNK: **ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); //exit(0);
				err = 10;
				getchar();
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
	printf("return 10\n");
	return 10;
}

