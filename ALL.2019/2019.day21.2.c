#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <deque>
#include <cassert>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "		2019 day 21 part2\n"
//#define _DEBUG_
#undef DEBUG
#define getchar()
int numSteps = 0;
#define MAX 7500
#define MAXI 3000
int instTOT = 0;
long long inst[MAXI];
long long instOrig[MAXI];
char instruction    [MAXI][40];
char instructionOrig    [MAXI][40];

long long output[6] = {0};
long long saveInst[6][MAXI] = {0};
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
long long  tmpIn[] = {0, 0, 1,  0, 2, 0, 3, 2, 2, 2, -1};

//char code[] = "NOT B T\nOR T J\nWALK\n";
///char code[] = "NOT T J\nNOT A J\nWALK\n";
//char code[] = "NOT A J\nNOT B T\nAND T J\nNOT C T\nAND T J\nAND D J\n WALK\n";
//char code[] = "NOT A J\nNOT C J\nWALK\n";
//pART 1char code[] = "NOT D T\nNOT T T\nNOT C J\nAND T J\nNOT A T\nOR T J\nWALK\n";
///char code[] = "NOT D T\nNOT T T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
/// WORKING TO #.#.#..##.# -> #.#...#.#.# char code[] = "NOT G J\nNOT J J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT G J\nNOT J J\nAND J T\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT G J\nNOT J J\nAND J T\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nNOT B T\nNOT T T\nNOT C\nNOT D\nNOT \nNOT E\NOT F\nNOT G\nRUN\n";
//char code[] = "NOT H J\nNOT J J\nAND J T\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//#####.##.#.##.###
//char code[] = "NOT H J\nNOT J J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT F J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//if no f then no b
//if no f then no e
//char code[] = "NOT F J\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT I T\nNOT T T\nNOT F J\nAND T J\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//if no i must have a a
//char code[] = "NOT H J\nNOT J J\nNOT I T\nNOT T T\nOR J T\nNOT F J\nAND T J\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT F J\nNOT J J\nNOT I T\nNOT T T\nOR J T\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT E J\nNOT D T\nNOT T T\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT A J\nRUN\n";

//char code[] = "NOT I T\nNOT T T\nNOT F J\nAND T J\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT F J\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT I T\nNOT T T\nOR T J\nNOT B T\nOR T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT H T\nNOT T T\nNOT F J\nAND T J\nNOT E T\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//// nEARLY char code[] = "NOT F J\nNOT E T\nOR J T\nNOT G J\nOR T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT A J\nNOT B T\nNOT T T\nAND T J\nNOT D T\nNOT T T\nAND J T\nNOT C J\nAND T J\nNOT E T\nAND T J\nNOT F T\nAND T J\nNOT B T\nOR T J\nRUN\n";
//char code[] = "NOT A T\nNOT D J\nNOT J J\nAND T J\nNOT E T\nAND T J\nNOT F T\nAND T J\nNOT H T\nNOT T T\nOR J T\nNOT C J\nOR T J\nRUN\n";
//char code[] = "NOT E T\nNOT F J\nAND T J\nNOT H T\nNOT T T\nOR T J\nNOT C T\nAND T J\nNOT A T\nAND T J\nNOT D T\nNOT T T\nAND T J\nRUN\n";
//char code[] = "NOT E T\nNOT F J\nAND T J\nNOT H T\nNOT T T\nOR T J\nNOT J T\nOR B T\nNOT A J\nNOT J J\nAND T J\nNOT C T\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT E T\nNOT F J\nAND T J\nNOT H T\nNOT T T\nAND T J\nNOT J T\nNOT A J\nNOT J J\nAND T J\nNOT D T\nNOT T T\nAND T J\nNOT A T\nOR T J\nRUN\n";
//char code[] = "NOT E T\nNOT F J\nAND T J\nNOT H T\nNOT T T\nAND T J\nNOT A T\nAND T J\nNOT C T\nAND J T\nNOT C J\nAND T J\nNOT C T\nOR T J\nAND D J\nRUN\n";
char code[] = "NOT B T\nNOT C J\nOR T J\nNOT H T\nNOT T T\nAND J T\nNOT A J\nNOT J J\nAND T J\nNOT D T\nNOT T T\nAND T J\nNOT A T\nOR T J\nRUN\n";
//#####...#########
//char code[] = "AND A J\nRUN\n";
int codePos = 0;
char out1[300];
char out2[300];
char out3[300];
char out4[300];
int OUTPos = 0;
int OUTStart = 0;

int fd;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        ////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); fd = dup(1); close(1);
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
			instructionOrig[newStart][pos] = '\0';
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
			instructionOrig[newStart][pos] = line1[i];
			pos++;
		}
	}
	leny++;
}
	fclose(a);
	newStart++;
	instruction[newStart][pos] = '\0';
	instructionOrig[newStart][pos] = '\0';
RErestart:
	for (int i = 0; i < 6; i++) {
		output[i] = 0;
		nextInst[i] = 0;
		relativeBase[i] = 0;
		times[i] = 0;
		finished[i] = 0;
		inputCounters[i] = 0;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < MAXI; j++) {
			saveInst[i][j] = 0;
		}
	}
	
	for (int i = 0; i < newStart; i++) {
		strcpy(instruction[i], instructionOrig[i]);
	}
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
	printf("START-------%d------\n", instTOT); getchar();

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
		if (ret == 100) {printf("RErestart\n"); getchar(); goto RErestart;}
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
                printf(" is [%lld] ", inst[i]); fflush(stdout); //getchar();
#endif

		int myINST = inst[i] % 100;
		if (myINST == 3) {
			//{printf("got a 3 (using %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]);}
			{printf("got a 3 (using %d) \n", (int)code[codePos]);}
#ifdef _DEBUG_
#endif
                        if (inst[i] > 200) {
				int in;
				if (code[codePos] == ' ') {
					in = 34;
				} else if (code[codePos] == 'Z') {
					in = 10;
				} else {
					in = code[codePos];
				}
				in = code[codePos];
				printf("3333333: [%c]\n", (char)in);
				
				inst[relativeBase[machineNumber]+inst[i+1]] = in;
			} else {
				int in;
				if (code[codePos] == ' ') {
					in = 34;
				} else if (code[codePos] == 'Z') {
					in = 10;
				} else {
					in = code[codePos];
				}
				in = code[codePos];
				printf("33333: [%c]\n", (char)in);
				inst[inst[i+1]] = in;
			}
			if (inputCounter != 1) {
				inputCounter++;
			}
			i++; printf("leaving 3 (input)...\n"); fflush(stdout); getchar();
			codePos++;
		} else if (myINST == 4) {
#ifdef _DEBUG_
                        {printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
#endif
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
#ifdef _DEBUG_
                                printf("or is it OUT: %lld\n", inst[i+1]);
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

			if (OUT >= 0 && OUT <= 256) {
				//printf("OUT is [%c]", (char)OUT);
				printf("%c", (char)OUT);
			} else {
				printf("OUT outside range... %lld\n", OUT);
				fflush(stdout); dup2(fd, 1);
				printf("**ans: %lld\n", OUT);
				exit(0);
			}

			if (OUT == ';') {
				printf("\n");
				OUTPos = 0;
				OUTStart = 1;
			}
			if (OUTStart == 1) {
				OUTPos++;
			}
			if (OUTPos == 18) {
				printf("\n");
				OUTPos = 0;
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
			

			exit(0);

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
