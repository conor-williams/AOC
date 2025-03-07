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
#include <map>
#include <sys/time.h>
#include <signal.h>
#include <vector>

using namespace std;


int lenx, leny;
#define DAY "2019 day 23 part2\n"
#undef _DEBUG_
//#define _DEBUG_
#define getchar()
#define MAX 9000
#define MAXI 4000
int instTOT = 0;
#define NM 51
int GOglobal = 0;
int allbooted = 0;
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
//void callMachine255();
void *callMachine255(void *);

char myInput;
char reverseInput(char in);
int MINPATH;
int OXX, OXY;
////////////////////////day23
long long Xval50 = -22, Yval50 = -22;
long long prevXval50, prevYval50;
pthread_mutex_t lock;
pthread_mutex_t lock2[100];
pthread_mutex_t lock3;
pthread_mutex_t lock4;
map <long long, int> mp;
int destReady[NM+1];
int booting[NM+1];
int watch[NM+1];
deque<long long> Q[NM+1];
deque<long long> Qtmp[NM+1];
vector <long long> QX;
vector <long long> QY;
int QidleCount[NM+1];
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
int BOOTED[50] = {0};
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
int fd;

void TimerSet(int interval);
void TimerStop(int signum);
void TimerSet(int interval) {
	printf("starting timer\n");
	struct itimerval it_val;

	it_val.it_value.tv_sec = interval;
	it_val.it_value.tv_usec = 0;
	it_val.it_interval.tv_sec = 0;
	it_val.it_interval.tv_usec = 0;

	if (signal(SIGALRM, TimerStop) == SIG_ERR) {
		perror("Unable to catch SIGALRM");
		exit(1);
	}
	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
		perror("error calling setitimer()");
		exit(1);
	}
}

void TimerStop(int signum) {

	printf("Timer ran out! Stopping timer\n");
	FILE *f = fopen("out.tim", "a");
	fprintf(f, "Timer ran out! Stopping timer timestamp@%s\n", "out.tim");
	fclose(f);
	exit(10);
}
int main(int argc, char **argv)
{
	//TimerSet(60*2);
	printf(DAY); fflush(stdin); fflush(stdout);
	fflush(stdout); fd = dup(1); close(1); 
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&lock3, NULL);
	pthread_mutex_init(&lock4, NULL);
	for (int i  = 0; i < 50; i++) {
		pthread_mutex_init(&lock2[i], NULL);
	}
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
	//printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
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
		if (i < 50) {      rc = pthread_create(&threads[i], NULL, callMachine, (void *) i);usleep(10);}
		else if (i == 50) {rc = pthread_create(&threads[i], NULL, callMachine255, (void *) i);}
		//if (i == 50) {sleep(1);} //else {usleep(i);}
		if (rc) {printf("ERR creating thread %d\n", rc); exit(-1);}
	}
	//usleep(6000000);
	//GOglobal = 1;

	for (int i = 0; i <NM; i++) {
		pthread_join(threads[i], NULL);
	}

	/*
	   getchar();
	   callMachine((void *)50);

*/
	printf("AFTER\n");
	getchar();
	printf("AM I EXITTING HERE\n");
	//exit(0);

}

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

void *callMachine255(void *threadid) {
	//void callMachine255() {
	map <long long, char> already;
	srand(time(NULL));
	sleep(1);
	for (int i = 0; i < 50; i++) {
		if (BOOTED[i] != 1) {i=-1;/*usleep(30);*/}
	}
	long long watX, watY, prevY=-55;
	vector <long long> QXprev;
	vector <long long> QYprev;
	while (1) {
		while (QX.empty() || QY.empty()) {
			//sleep(1);
			usleep(30);
			printf("%d Q50.size() QX.size() %d QY.size() %d\n", (int)Q[50].size(), (int)QX.size(), (int)QY.size());
			printf("QX or QY empty... continue sleep\n");
			//Q[0].push_back(rand()%20000);
			//Q[0].push_back(rand()%20000);
			continue;
		}
		while (QX.size() == QXprev.size() && QY.size() == QYprev.size()) {
			//sleep(1);
			usleep(30);
			printf("same size....\n");
		}
		QXprev = QX; QYprev = QY;

		printf("doing check...\n");
		for (int i = 0; i < 50; i++) {
			if (QidleCount[i] < 5) {i=-1;}
		}

		printf("after check...\n");
		for (int i = 0; i < 50; i++) {
			QidleCount[i] = 0;
		}
		printf("set to zero... check...\n");

		printf("pushing %lld %lld\n", watX, watY);

		printf("all the X QS\n");
		printf("............\n");
		for (auto one: QX) {
			printf("%lld ", one);
		}
		printf("all the Y QS\n");
		for (auto two: QY) {
			printf("%lld ", two);
		}
		printf("........press return....\n");
		//fgetc(stdin);

		//sleep(1);
		pthread_mutex_lock(&lock3);
		printf("pushing %lld %lld\n", watX = QX.back(), watY = QY.back());
		pthread_mutex_unlock(&lock3);
		if  (prevY == watY && prevY != -1) {fflush(stdout); dup2(fd, 1); printf("**ans: %lld\n", watY); exit(0);}
		prevY = watY;
		pthread_mutex_lock(&lock);
		pthread_mutex_lock(&lock3);
		Q[0].push_back(watX);
		Q[0].push_back(watY);
		pthread_mutex_unlock(&lock3);
		pthread_mutex_unlock(&lock);
		usleep(300);

	}
}
void *callMachine(void *threadid) {
	int one = 1;
	long tid = (long)threadid;
	//while (GOglobal != 1) {usleep(200);}
	printf("here1... %ld\n", tid);

	//again:
	int ret = machineMulti(tid, 0, one, inst[tid], instruction[tid], output[tid], times[tid],
			finished[tid], inputCounters[tid], saveInst[tid], nextInst[tid], relativeBase[tid]);
	printf("AFTER machineMulti\n"); fflush(stdout); getchar();


	if (ret != 34) {printf("ret not 34 (%d)\n", ret);}
	//goto again;
	return NULL;
}

int machineMulti(int var_mach, int machineNumber, int one, long long inst[MAXI], char instruction[MAXI][40],
		long long output[6], int times[6], int finished[6], int inputCounters[6], long long saveInst[6][MAXI], 
		long long nextInst[6], long long relativeBase[6]) {
	if (finished[machineNumber] == 1) { printf("return 22\n"); return 22;}
	//long long input[10];	

	QidleCount[var_mach] = 0;
	printf("var_mach is %d\n", var_mach);
	int inputCounter = inputCounters[machineNumber];

	if (machineNumber == 0 && times[machineNumber] == 0) {
		//input[1] = 1; 
		//input[0] = phase[machineNumber];
	} else {
		//input[1] = output[machineNumber];
		//input[0] = phase[machineNumber];
	}

	long long QNUM = 0;
	int bootit2 = var_mach;
	//usleep(100);
	usleep(300);
	//if (var_mach != 50) {usleep(1000);}
	if (var_mach == 50) {bootit2 = 255;}
	//if (allbooted != 1) {bootit2 = 255;}
	//while (!allbooted) {usleep(300);}


	//long long xval, yval;
	long long Yval;
	long long Xval;

	for (int i = nextInst[machineNumber]; i < instTOT; i++) {
#ifdef _DEBUG_
		printf("\nNEW NEW NEW:::"); fflush(stdout);
		printf("POS InstNUM: (%d) ", i); fflush(stdout);
		printf(" is [%lld] ", inst[i]); fflush(stdout); //getchar();
#endif

		// 3 is a read 4 is a write...
		// 3 is a receive 4 is a send...
		int myINST = inst[i] % 100;
		if (myINST == 3) {
			//READ OR RECEIVE
			if (inst[i] > 200) {
				if (booting[var_mach] == 1) {
					printf("***booting %d\n", var_mach);
					inst[relativeBase[machineNumber]+inst[i+1]] = bootit2;
					BOOTED[var_mach] = 1;
					printf("BOOTED %d\n", var_mach);
					for (int i = 0; i < 50; i++) {
						if (BOOTED[i] != 1) {i=-1;usleep(20);}
					}
					//sleep(1);
					usleep(300);
				} else {
					pthread_mutex_lock(&lock);
					int qsize = Q[var_mach].size();
					pthread_mutex_unlock(&lock);
					if (qsize == 0) {
						inst[relativeBase[machineNumber]+inst[i+1]] = -1;
					} else {
						pthread_mutex_lock(&lock);
						inst[relativeBase[machineNumber]+inst[i+1]] = Q[var_mach].front();
						Q[var_mach].pop_front();
						pthread_mutex_unlock(&lock);
					}
				}
			} else {
				if (booting[var_mach] == 1) {
					printf("**booting %d\n", var_mach);
					inst[inst[i+1]] = bootit2;
					BOOTED[var_mach] = 1;
					for (int i = 0; i < 50; i++) {
						if (BOOTED[i] != 1) {i=-1;usleep(30);}
					}
					usleep(300);
					//sleep(1);
				} else {
					pthread_mutex_lock(&lock);
					int qsize = Q[var_mach].size();
					pthread_mutex_unlock(&lock);
					if (qsize == 0) {
						pthread_mutex_lock(&lock);
						QidleCount[var_mach]++;
						pthread_mutex_unlock(&lock);
						inst[inst[i+1]] = -1;
					} else {
						pthread_mutex_lock(&lock);
						QidleCount[var_mach] = 0;
						pthread_mutex_unlock(&lock);

						pthread_mutex_lock(&lock);
						inst[inst[i+1]] = Q[var_mach].front();
						Q[var_mach].pop_front();
						pthread_mutex_unlock(&lock);
					}
				}
			}
			i++; 
			if (booting[var_mach] == 1) {
				booting[var_mach] = 0;
			}
//end3:
			continue;
		} else if (myINST == 4) {
			//WRITE OR SEND
			long long OUT;

			if (inst[i] > 200) {
				//input[1] = inst[relativeBase[machineNumber]+inst[i+1]];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[relativeBase[machineNumber]+inst[i+1]];
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[relativeBase[machineNumber]+inst[i+1]]; 
				}
				OUT =  inst[relativeBase[machineNumber]+inst[i+1]];
				if (OUT == 255) {printf("got a 255\n");}
#ifdef _DEBUG_
				printf("REL OUT: %lld (base: %lld+%lld)\n", inst[relativeBase[machineNumber]+inst[i+1]],
						relativeBase[machineNumber], inst[i+1]);
#endif
			} else if (inst[i] > 100) {
				printf("or is it OUT: %lld\n", inst[i+1]);
#ifdef _DEBUG_
				printf("or is it OUTS: %s\n", instruction[i+1]);
#endif
				///input[1] = inst[i+1];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[i+1]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[i+1]; 
				}
				OUT =  inst[i+1];
				if (OUT == 255) {printf("got a 255\n");}
			} else {
#ifdef _DEBUG_
				printf("OUT: %lld\n", inst[inst[i+1]]); 
				printf("OUTS: %s\n", instruction[inst[i+1]]);
#endif
				////input[1] = inst[inst[i+1]];
				if (one == 0) {
					output[(machineNumber+1)%5] = inst[inst[i+1]]; 
				} else if (one == 1) {
					output[(machineNumber)%5] = inst[inst[i+1]]; 
				}
				OUT = inst[inst[i+1]];
				if (OUT == 255) {printf("got a 255\n");}
			}
			struct pos_s pos1;

			pthread_mutex_lock(&lock4);
			int dReady = destReady[var_mach];
			pthread_mutex_unlock(&lock4);

			if (dReady == 1) {
				dReady++;
				if (OUT == 255) {QNUM = 50;} else {QNUM = OUT;}
			} else if (dReady == 2) {
				dReady++;
				Xval = OUT;
				if (QNUM < 50) {
					printf("sending %lld to Q:%lld\n", Xval, QNUM);
				} else if (QNUM == 50) {
					pthread_mutex_lock(&lock3);
					QX.push_back(OUT);
					pthread_mutex_unlock(&lock3);
					printf("Xval for Q 50 is %lld\n", Xval);
				}
			} else if (dReady == 3) {
				dReady = 1;
				Yval = OUT;
				if (QNUM < 50) {
					if (OUT == -1) {printf("STRANGE -1\n");}
					printf("send %lld to Q:%lld\n", Yval, QNUM);

					pthread_mutex_lock(&lock);
					if (Yval != -1) {
						Q[QNUM].push_back(Xval);
						Q[QNUM].push_back(Yval);
					}
					pthread_mutex_unlock(&lock);
					//usleep(30);
				} else if (QNUM == 50) {
					if (Yval != -1) {
						pthread_mutex_lock(&lock3);
						QY.push_back(Yval);
						pthread_mutex_unlock(&lock3);
					}
					printf("Yval for Q 50 is %lld..\n", Yval);
				}
			} else {
				printf("CONORUNK OUT %lld destReady[%d] is %d\n", OUT, var_mach, dReady); 
			}

			pthread_mutex_lock(&lock4);
			destReady[var_mach] = dReady;
			pthread_mutex_unlock(&lock4);

			for (int i = 0; i < instTOT; i++) {
				saveInst[machineNumber][i] = inst[i];
			}
			nextInst[machineNumber] = i+2;
			times[machineNumber]++;
			inputCounters[machineNumber] = inputCounter;
			i++;
		} else if (myINST == 99) {
			printf("GOT QUIT 99\n"); 
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
			return (0);
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

//printf("ever here...\n"); exit(0);

/*
   pthread_mutex_lock(&lock);
   if (Xval50 == -22 || Yval50 == -22) {
   pthread_mutex_unlock(&lock);
   goto ag2;
   }
   */
/*
   if (var_mach == 50) {
   printf("never here\n"); exit(0);
//fgetc(stdin);
if (QY.size() == 0) { i++; goto end3;}
if (QY.back() == -1 && QY.size() == 1) {printf("only -1\n"); i++; goto end3;}
usleep(300);
vector <int> lower;
ag2:
usleep(30);
for (int z = 0; z < 50; z++) {
Qtmp[z] = Q[z];
}
int found = 0;
for (int z = 0; z < 50; z++) {
if (Q[var_mach].size() == 0) {found = 1; continue;}
if (Q[var_mach].back() != -1) {usleep(30); found = 1;}
}
if (found == 1) {usleep(300); printf("goto ag2\n"); goto ag2;}
sleep(1);
int found2 = 0;
for (int z = 0; z < 50; z++) {
usleep(30);
if (Qtmp[z].size() == Q[z].size() && Q[z].back() == -1) {
} else {
found2 = 1;
}
}
if (found2 == 1) {printf("goto ag2\n"); goto ag2;}

for (int z = 0; z < 50; z++) {
if (find(lower.begin(), lower.end(), z) == lower.end() &&
QidleCount[z] <= 3) {
found = 1;
} else {
lower.push_back(z);
QidleCount[z] = 0;
}
usleep(40);
}
if (found == 1) {usleep(30); goto ag2;}
lower.clear();

while (1) {
//printf("Xval50 --- Yval50 %lld %lld\n", Xval50, Yval50);
//usleep(20);
if (Xval50 == -22) {continue;}
if (Yval50 == -22) {continue;}
else if (Xval50 ==  -1) {continue;}
else if (Yval50 ==  -1) {continue;}
else {break;}
}
while (Xval50 == -22 && Yval50 == -22) {
//
//if (Xval50 == 0) {continue;}
//if (Yval50 == 0) {continue;}
if (Xval50 == -1) {continue;}
if (Yval50 == -1) {continue;}
printf("-22... ");
usleep(20);
}
//prevXval50 = Xval50;
//prevYval50 = Xval50;
//yval = Yval50;
//xval = Xval50;

Xval50 = -22; Yval50 = -22;

printf("Yval is %lld\n", yval);
xval = QX.at(0);
for (auto it = QY.rbegin(); it != QY.rend(); it++) {
if (*it != -1) {yval = *it;}
}

auto it1 = mp.find(yval);

if (it1 != mp.end() && yval != -1) {
	printf("ANS is %lld\n", yval); fflush(stdout);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lld\n", yval);	
	exit(0);
} else {
	mp[yval] = 1;
}

printf("about to push_back... xval:%lld yval:%lld fgetc\n", xval, yval); //fgetc(stdin);

printf("all the X QS\n");
printf("............\n");
for (auto one: QX) {
	printf("%lld ", one);
}
printf("all the Y QS\n");
for (auto two: QY) {
	printf("%lld ", two);
}
printf("............\n");
//fgetc(stdin);
Q[0].push_back(QX.back());
Q[0].push_back(QY.back());
if (xval != -1 && yval != -1) {
	printf("pushing xval yval.. %lld %lld.\n", xval, yval);
	Q[0].push_back(xval);
	Q[0].push_back(yval);
} else {
	printf("*****Xval50 %lld Yval50 %lld\n", Xval50, Yval50);
}
usleep(20);
i++;
goto end3;
//goto ag2;
}
*/
//Yval = -22;
/*
   if (Yval50 == -1) {

   printf("iiinnn ssseeeenddddd all the X QS\n");
   printf("............\n");
   for (auto one: QX) {
   printf("%lld ", one);
   }
   printf("\niiiinnnn seeendddd all the Y QS\n");
   for (auto two: QY) {
   printf("%lld ", two);
   }
   printf("............\n");

   printf("Yval50 is %lld (m1\n", Yval50);
//Xval50 = prevXval50;
//Yval50 = prevYval50;
//QY.push_back(OUT);
} else {
QY.push_back(OUT);
}
//pthread_mutex_unlock(&lock);
*/
		/*
		   if (already.find(watY) == already.end()) {
		   already[watY] = '1';
		   } else {
		   printf("**ans: %lld\n", watY);
		   exit(0);
		   }
		   */
		/*
		   for (int i = 0; i < 50; i++) {
		   if (Q[i].size() != 0) {printf("strange..%d.\n", i); exit(0);}
		   }
		   */
		//for (int i = 0; i < 50; i++)  { QidleCount[i] = 0; }
					/*
					   pthread_mutex_lock(&lock);
					   if (Xval != -1) {
					   Q[QNUM].push_back(Xval);
					   }
					   pthread_mutex_unlock(&lock);
					   usleep(30);
					   */
