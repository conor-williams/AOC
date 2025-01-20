#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <deque>
#include <cassert>

using namespace std;

int lenx, leny;
#define DAY "2019 day 15 part1\n"
//#define _DEBUG_
#undef DEBUG
//#define getchar()
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

//char tmpIn[] = {'3','3','3','1','2'};
long long  tmpIn[] = {1, 2, 2,  2, 2, 2, 2, 2, 2, 2, -1};
int tmpInPos = 0;
void printit();

#define SZ 30
char grid[SZ+5][SZ+5];
int yPrev; int yCur = SZ/2;
int xPrev; int xCur = SZ/2;
struct pos_s {
	//char dir;
	int x;
	int y;
	deque <char> path;
};
deque <pos_s> myInputQ;
struct pos_s pos2;
int MOVE = 0;
deque <char> PATH;
int pathPOS = 0;
int main(int argc, char **argv)
{

	struct pos_s st = {xCur, yCur, PATH};
	
	myInputQ.push_back(st);
	for (int y = 0; y < SZ; y++) {
		for (int x = 0; x < SZ; x++) {
			grid[y][x] = 'U';
		}
		grid[y][SZ] = ' ';
		grid[y][SZ+1] = (y%10) + 48;
	}
	for (int x = 0; x < SZ; x++) {
		grid[SZ][x] = ' ';
		grid[SZ+1][x] = (x%10)+48;
	}

	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
	for (int i = 0 ; i < MAX; i++) {
		inst[i] = 0;
	}

	int newStart = 0;
	int pos = 0;
while(1) {
        fgets(line1, 2990, a);
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
			instruction[newStart][pos] = line1[i];
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
                printf(" is [%lld] ", inst[i]); fflush(stdout); getchar();
#endif

		int myINST = inst[i] % 100;
		if (myINST == 3) {
			{printf("got a 3 (using %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]);}
#ifdef _DEBUG_
#endif
			// N==1 S==2 W==3 E==4 
			yPrev = yCur; xPrev = xCur;
			if (myInputQ.size() == 0) {printf("EMPTY Q\n"); fflush(stdout); /*printit();*/ getchar();}
again:
			if (MOVE == 0) { // moving as normal...
				printf("MOVE IS ZERO -- looking four ways\n");
				struct pos_s pos1;
				int pushes = 0;
				pos1.x = xCur; pos1.y = yCur+1;	pos1.path.clear(); pos1.path.push_front('2');
				if (grid[pos1.y][pos1.x] == 'U' && pos1.x >= 0 && pos1.x < SZ && pos1.y >= 0 && pos1.y <= SZ) { pushes &= (1<<1); myInputQ.push_front(pos1);}
				pos1.x = xCur+1; pos1.y = yCur;	pos1.path.clear(); pos1.path.push_front('4');
				if (grid[pos1.y][pos1.x] == 'U' && pos1.x >= 0 && pos1.x < SZ && pos1.y >= 0 && pos1.y <= SZ) { pushes &= (1<<2); myInputQ.push_front(pos1);}
				pos1.x = xCur-1; pos1.y = yCur;	pos1.path.clear(); pos1.path.push_front('3');
				if (grid[pos1.y][pos1.x] == 'U' && pos1.x >= 0 && pos1.x < SZ && pos1.y >= 0 && pos1.y <= SZ) { pushes &= (1<<3); myInputQ.push_front(pos1);}
				pos1.x = xCur; pos1.y = yCur-1;	pos1.path.clear(); pos1.path.push_front('1');
				if (grid[pos1.y][pos1.x] == 'U' && pos1.x >= 0 && pos1.x < SZ && pos1.y >= 0 && pos1.y <= SZ) { pushes &= (1<<4); myInputQ.push_front(pos1);}
				printf("pushes: %d\n", pushes);
			} else if (MOVE == 1) {//hit a wall
				printf("MOVE is ONE\n");
			}

			if (myInputQ.size() == 0) {printf("myInputQ.size is ZERO\n");exit(0);}
			pos2 = myInputQ.front();
			myInputQ.pop_front();
			printf("***pos2.path: [");
			for (auto it = pos2.path.begin();  it != pos2.path.end(); it++) {
				printf("%c", *it);
			} printf("]\n");
			if (pos2.path.size() == 0) {
				printf("po2.path.size() is ZERO -- loop again\n");
				MOVE = 0;
				goto again;
			}
			myInput = pos2.path.front();
			pos2.path.pop_front();
			if ((int)pos2.path.size() > 0) {
				myInputQ.push_front(pos2);
			}

			printf("pos2.path.size() now %d\n", (int)pos2.path.size());
			//myInput = reverseInput(myInput);
			switch (myInput) {
				case('1'): yCur--; break;
				case('2'): yCur++; break;
				case('3'): xCur--; break;
				case('4'): xCur++; break;
			}

			printf("myInput is [%c]\n", myInput); printf("%d,%d \n", xCur, yCur); getchar();
                        if (inst[i] > 200) {
				input[inputCounter] = (long long)(myInput - 48);	
				inst[relativeBase[machineNumber]+inst[i+1]] = input[inputCounter];
			} else {
				input[inputCounter] = (long long)(myInput - 48);
				inst[inst[i+1]] = input[inputCounter];
			}
			if (inputCounter != 1) {
				inputCounter++;
			}
			i++; printf("leaving 3 (input)...\n"); fflush(stdout);
		} else if (myINST == 4) {
			printf("here5...\n"); fflush(stdout);
                        {printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
#ifdef _DEBUG_
#endif
			//OUT 0 == Wall 1 == OK 2==OX
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
				case (0): {
						printf("got a 0: ZERO (wall)\n");
						grid[yCur][xCur] = '#';
						yCur = yPrev; xCur = xPrev;
						MOVE = 1;
						break;
					}
				case (1): {
						grid[yCur][xCur] = '.';
						struct pos_s pos3 = myInputQ.front();	
						myInputQ.pop_front();
						struct pos_s pos4 = myInputQ.front();	
						myInputQ.pop_front();
						pos4.path.push_front(reverseInput(myInput));
						myInputQ.push_front(pos4);
						myInputQ.push_front(pos3);
						//if (MOVE == 0) {MOVE = 1;} else if (MOVE == 1) {MOVE = 1;}
						MOVE = 0;
						break;
					}
				case (2):
					{
						grid[yCur][xCur] = 'O';
						struct pos_s pos3 = myInputQ.front();	
						myInputQ.pop_front();
						pos3.path.push_front(reverseInput(myInput));
						myInputQ.push_front(pos3);
						printf("found OXEGEN at %d,%d\n", xCur, yCur); getchar();
						break;
					}
	
			}

			printit(); getchar();
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
			
			printit();
			if (one == 1) {exit(0);}
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
				printf("tmp2... not zero... [[ %s ]]\n", tmp2); getchar(); getchar(); exit(0);
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
				printf("GOT A NINE\n"); getchar();
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
	//printf("output CONOR %lld COUNT %d\n", output, count); //getchar(); getchar();
	//if (output > outputMAX) {outputMAX = output; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
	//printf("output: %lld\n", output);
	return 10;
}
void printit() {
			for (int y = 0; y < SZ+2; y++) { for (int x = 0; x<SZ+2; x++) { printf("%c", grid[y][x]); } printf("\n"); } printf("\n");
}
