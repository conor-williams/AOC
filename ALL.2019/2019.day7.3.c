#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
using namespace std;

int lenx, leny;
#define DAY "2019 day7 part1\n"
#undef _DEBUG_
#define MAX 2000
int instTOT = 0;
long long inst[MAX];
long long instOrig[MAX];
long long saveinst[MAX][MAX];
char instruction    [MAX][10];

int main(int argc, char **argv)
{
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
			printf("instruction[newStart]: %s (newStart:%d)\n", instruction[newStart], newStart); 
			newStart++;
			pos = 0;
			printf("instruction[newStart]getc\n");
			printf("getc\n");
		} else {
			instruction[newStart][pos] = line1[i];
			pos++;
		}
	}
	leny++;
}
	instruction[newStart][pos] = '\0';
	newStart++;
	char *stop;
	for (int i = 0; i < newStart; i++) {
		inst[i] = strtoul(instruction[i], &stop, 10);
		printf("%lld\n", inst[i]);
	}
	instTOT = newStart;
	printf("START-------------\n");
	int in = 0;
	for (int i = 0; i < instTOT; i++) {
		instOrig[i] = inst[i];
	}
	int count = 0;
	int phase[] = {9,8,7,6,5,-1};
	// int phase[] = {9,8,7,6,5,-1};
	//int phase[] = {1,0,4,3,2,-1};
	int phaseMAX[5];
	int phaseCounter = 0;
	long long output;
	long long outputMAX = 0;
	long long input[100] = {0};
	int inputCounter = 0;
	sort(phase, phase+5);
	int first = 0;
	do {	
			
		first = 0;
		printf("PHASE:\n"); for (int i = 0; i < 6; i++) { printf("%d ", phase[i]); } printf("\n"); //getchar();
		output = 0;
		phaseCounter = 0;
		count = 0;
restart:
		
#ifdef _DEBUG_
		printf("restart count is %d instTOT: %d\n", count, instTOT);
#endif

		if (first == 0) {
			for (int i = 0; i < instTOT; i++) {
				inst[i] = instOrig[i];
			}
		} else if (first == 1) {
			for (int i = 0; i < instTOT; i++) {
				inst[i] = instOrig[i];
			}
/*
			for (int i = 0; i < instTOT; i++) {
				inst[i] = saveinst[count][i];
				printf("%lld,", inst[i]);
			}
			printf("\n"); 
*/
		}

		inputCounter = 0;
		if (phase[phaseCounter] == -1) {printf("phase -1\n"); phaseCounter=0; if (first == 1) {goto end;} else if (first == 0) {first = 1; count = 0; goto end;}}
		count++;	
		if (count == 1 && first == 0) {input[1] = 0;      input[0] = phase[0];            phaseCounter++;} else
		if (count > 1 && first == 0)  {input[1] = output; input[0] = phase[phaseCounter]; phaseCounter++;} else 
		if (first == 1)  {             input[1] = output; input[0] = phase[phaseCounter]; phaseCounter++;}
	for (int i = 0; i < instTOT; i++) {
#ifdef _DEBUG_
                printf("\nNEW NEW NEW:::"); fflush(stdout);
                printf("POS InstNUM: (%d) ", i); fflush(stdout);
                printf(" is [%lld] ", inst[i]); fflush(stdout); getchar();
#endif

		if (in == 1) {getchar();}
		int myINST = inst[i] % 100;
		if (myINST == 3) {
#ifdef _DEBUG_
			if (first == 1) {printf("got a 3 (using %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]);}
#endif
			inst[inst[i+1]] = input[inputCounter];
#ifdef _DEBUG_
			{printf("got a 3 (using val %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]);}
#endif
			if (inputCounter != 1) {
				inputCounter++;
			}
			i++;
		} else if (myINST == 4) {
#ifdef _DEBUG_
                        if (first == 1) {printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);}
#endif
                        if (inst[i] > 100) {
#ifdef _DEBUG_
                                printf("or is it OUT: %lld\n", inst[i+1]);
                                printf("or is it OUTS: %s\n", instruction[i+1]);
#endif
				input[1] = inst[i+1];
                        	output = inst[i+1]; 
                        } else {
#ifdef _DEBUG_
                                printf("OUT: %lld\n", inst[inst[i+1]]); 
                                printf("OUTS: %s\n", instruction[inst[i+1]]);
#endif
				input[1] = inst[inst[i+1]];
                                output = inst[inst[i+1]]; 
                        }
                        if (inst[inst[i+1]] != 0) {
#ifdef _DEBUG_
                                printf("not zero (pos: inst[i+1]) %lld... ", inst[i+1]); 
#endif
                        } else {
#ifdef _DEBUG_
                                printf("ZERO at address %lld\n", inst[i+1]); 
#endif
                        }
                        i++;
		} else if (myINST == 99) {
#ifdef _DEBUG_
			printf("GOT QUIT 99\n"); //in = 1; 
#endif
#ifdef _DEBUG_
			for (int i = 0; i < instTOT; i++) {
				//strcpy(saveinstruction[count-1][i], instruction[i]);
				saveinst[count-1][i] = inst[i];
			}
#endif
			goto restart;
		} else { 
			int err = 0;
			char tmpStr[20]; char tmp2[20]; sprintf(tmpStr, "%07llu", inst[i]);

			for (int k = 0; k < 4; k++) {
				tmp2[k] = tmpStr[strlen(tmpStr)-(3-k)-1];
			}
			long long mypos = inst[i+3];
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
			else { printf("HERE"); getchar(); val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

			if (tmp2[0] == '0') {val2 = inst[inst[i+2]];
#ifdef _DEBUG_
printf("(pos0) val2 %lld\n", val2);
#endif
}
			else if (tmp2[0] == '1') {val2 = inst[i+2];
#ifdef _DEBUG_
printf("(Npos1) val2 %lld\n", val2);
#endif
} 
			else { printf("HERE2"); getchar(); val2 = inst[i+2];}
	
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
			} else if (err != 2) {
				i += 3;
			} //err2 is JMP //err10 = UNK
		} 
	}
end:
	//printf("output CONOR %lld COUNT %d\n", output, count); //getchar(); getchar();
	if (output > outputMAX) {outputMAX = output; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
		printf("output: %lld\n", output);
	} while (next_permutation(phase, phase+5));
#ifdef _DEBUG_
	printf("INSTS:"); for (int i = 0; i < instTOT; i++) { printf("%lld ", inst[i]); }
#endif
	printf("\n");
printf("***OUTPUTMAX: %lld\n", outputMAX);
	printf("PHASEMAX:\n"); for (int i = 0; i < 5; i++) { printf("%d ", phaseMAX[i]); } printf("\n"); //getchar();

fclose(a);
}
