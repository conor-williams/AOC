#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
using namespace std;

int lenx, leny;
#define DAY "2019 day7 part1\n"
#define _DEBUG_
#define MAX 2000
char instruction    [MAX][10];
char instructionOrig[MAX][10];
char saveinstruction[MAX][MAX][10];
int instTOT = 0;
long long inst[MAX];
long long instOrig[MAX];
long long saveinst[MAX][MAX];

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
	for (int i = 0 ; i < MAX; i++) {
		strcpy(instruction    [i], "\0");
		strcpy(instructionOrig[i], "\0");
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
		strcpy(instructionOrig[i], instruction[i]);
		instOrig[i] = inst[i];
	}
	int count = 0;
	int phase[] = {9,7,8,5,6,-1};
	//int phase[] = {9,8,7,6,5,-1};
	//int phase[] = {1,0,4,3,2,-1};
	int phaseMAX[5];
	int phaseCounter = 0;
	long long output;
	long long outputMAX = 0;
	long long input[100] = {0};
	int inputCounter = 0;
	//sort(phase, phase+5);
	int first = 0;
	do {	
		
		printf("PHASE:\n"); for (int i = 0; i < 6; i++) { printf("%d ", phase[i]); } printf("g\n"); //getchar();
		output = 0;
		phaseCounter = 0;
		count = 0;
restart:
		
		printf("restart count is %d instTOT: %d\n", count, instTOT);

		if (first == 0) {
			for (int i = 0; i < instTOT; i++) {
				strcpy(instruction[i], instructionOrig[i]);
				inst[i] = instOrig[i];
			}
		} else if (first == 1) {
			for (int i = 0; i < instTOT; i++) {
				strcpy(instruction[i], saveinstruction[count][i]);
				inst[i] = saveinst[count][i];
			}
		}

		inputCounter = 0;
		if (phase[phaseCounter] == -1) {printf("phase -1\n"); phaseCounter=0; if (first == 1) {goto end;} else if (first == 0) {first = 1; count = 0; goto restart;}}
		count++;	
		if (count == 1 && first == 0) {input[1] = 0;      input[0] = phase[0]; phaseCounter++;} else
		if (count > 1 && first == 0)  {input[1] = output; input[0] = phase[phaseCounter]; phaseCounter++;} else 
		if (first == 1)  {input[1] = output; input[0] = phase[phaseCounter]; phaseCounter++;}
	for (int i = 0; i < instTOT; i++) {
                printf("\nNEW NEW NEW:::"); fflush(stdout);
#ifdef _DEBUG_
                printf("POS InstNUM: (%d) ", i); fflush(stdout);
                printf(" is [%lld] ", inst[i]); fflush(stdout);
                printf("(also is [%s])\n", instruction[i]); fflush(stdout);// getchar();
#endif

		if (in == 1) {getchar();}
		int myINST = inst[i] % 100;
		if (ction[i][strlen(instruction[i])-1] == '3') {
#ifdef _DEBUG_
			if (first == 1) {printf("got a 3 (using %lld) -> [pos:%lld]\n", input[inputCounter], inst[i+1]); getchar();}
#endif
			inst[inst[i+1]] = input[inputCounter];
			char inputS[10]; sprintf(inputS, "%lld", input[inputCounter]);
			strcpy(instruction[inst[i+1]], inputS);
			inputCounter = 1;
//printf("inputCount is %d\n", inputCounter); getchar();
			i++;
		} else if (instruction[i][strlen(instruction[i])-1] == '4') {
#ifdef _DEBUG_
                        if (first == 1) {printf("got a 4 look@ %lld contains %lld\n", inst[i+1], inst[inst[i+1]]); fflush(stdout); getchar();}
                        printf("strlen: %d\n", (int)strlen(instruction[i]));
#endif
                        if (strlen(instruction[i]) == 3 && instruction[i][0] == '1') {
#ifdef _DEBUG_
                                printf("or is it OUT: %lld\n", inst[i+1]);
                                printf("or is it OUTS: %s\n", instruction[i+1]);
#endif
				input[1] = inst[i+1];
                        	output = inst[i+1]; //getchar();
                        } else {
#ifdef _DEBUG_
                                printf("OUT: %lld\n", inst[inst[i+1]]);
                                printf("OUTS: %s\n", instruction[inst[i+1]]);// getchar();
#endif
				input[1] = inst[i+1];
                                output = inst[inst[i+1]]; //getchar();
                        }
                        if (inst[inst[i+1]] != 0) {
#ifdef _DEBUG_
                                printf("not zero (pos: inst[i+1]) %lld... ", inst[i+1]); //getchar();
#endif
                        } else {
#ifdef _DEBUG_
                                printf("ZERO at address %lld\n", inst[i+1]); //getchar();
#endif
                        }
                        i++;
		} else if (instruction[i][strlen(instruction[i])-1] == '9' && instruction[i][strlen(instruction[i])-2] == '9' && (strlen(instruction[i]) == 2)) {
#ifdef _DEBUG_
			printf("GOT QUIT 99\n"); //in = 1; //getchar();
#endif
		for (int i = 0; i < instTOT; i++) {
			strcpy(saveinstruction[count-1][i], instruction[i]);
			saveinst[count-1][i] = inst[i];
			
		}
			goto restart;
		} else if ((instruction[i][strlen(instruction[i])-1] == '1' || instruction[i][strlen(instruction[i])-1] == '2' || instruction[i][strlen(instruction[i])-1] == '5' || instruction[i][strlen(instruction[i])-1] == '6' || instruction[i][strlen(instruction[i])-1] == '7' || instruction[i][strlen(instruction[i])-1] == '8' ) && (strlen(instruction[i]) == 1 || instruction[i][strlen(instruction[i])-2] == '0' )) {
			int err = 0;
			//printf("gota proper:1,2,5,6,7,8\nWAS: %s (%lld)\n", instruction[i], inst[i]);
			char tmpStr[20];
			sprintf(tmpStr, "%07llu", inst[i]);
			for (int k = 0; k < 4; k++) {
				instruction[i][k] = tmpStr[strlen(tmpStr)-(3-k)-1];
			}
			long long mypos = inst[i+3];
			//printf("***mypos (where output will be :) is %d\n", inst[i+3]); fflush(stdout);
			instruction[i][4] = '\0';
#ifdef _DEBUG_
			printf("NOW: %s\n", instruction[i]); 
#endif
			long long val1, val2, ans;
			if (instruction[i][1] == '0') {val1 = inst[inst[i+1]]; 
#ifdef _DEBUG_
printf("(pos0) val1 %lld\n", inst[inst[i+1]]);
#endif
}
			else if (instruction[i][1] == '1') {val1 = inst[i+1];
#ifdef _DEBUG_
printf("(Npos1) val1 %lld\n", val1);
#endif
} 
			else { printf("HERE"); getchar(); val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

			if (instruction[i][0] == '0') {val2 = inst[inst[i+2]];
#ifdef _DEBUG_
printf("(pos0) val2 %lld\n", val2);
#endif
}
			else if (instruction[i][0] == '1') {val2 = inst[i+2];
#ifdef _DEBUG_
printf("(Npos1) val2 %lld\n", val2);
#endif
} 
			else { printf("HERE2"); getchar(); val2 = inst[i+2];}
	
			if (instruction[i][3] == '2') {
#ifdef _DEBUG_
				printf("%lld **** %lld\n", val1, val2);
#endif
				ans = val1 * val2;
			} else if (instruction[i][3] == '1') {
#ifdef _DEBUG_
				printf("%lld ++++ %lld\n", val1, val2);
#endif
				ans = val1 + val2;
			} else if (instruction[i][3] == '5') {
				if (val1 != 0) {
#ifdef _DEBUG_
printf("NONZ: JUMP to (%lld)\n", val2);
#endif
i = val2-1; err = 2;} else {
#ifdef _DEBUG_
printf("ZNOJUMP (%lld)\n", val1);
#endif
err = 1;}
			} else if (instruction[i][3] == '6') {
				if (val1 == 0) {
#ifdef _DEBUG_
printf("ZERO: JUMP to (%lld)\n", val2);
#endif
 i = val2-1; err = 2;} else {
#ifdef _DEBUG_
printf("NONZ NOJMP (%lld)\n", val1);
#endif
 err = 1;}
			} else if (instruction[i][3] == '7') {
				if (val1 < val2) {ans = 1;} else {ans = 0;}
#ifdef _DEBUG_
				printf("%lld <<<<< %lld\n", val1, val2); 
#endif
			} else if (instruction[i][3] == '8') {
				if (val1 == val2) {ans = 1;} else {ans = 0;}
#ifdef _DEBUG_
				printf("%lld ===== %lld\n", val1, val2); 
#endif
			} else {
				printf("UNK: **ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); getchar();
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
		} else {
			printf("UNKNOWN: out of sync [xxx%c]??\n", instruction[i][strlen(instruction[i])-1] ); getchar();
			//i+= 3;
		}
	}
end:
	printf("output CONOR %lld COUNT %d\n", output, count); //getchar(); getchar();
	if (output > outputMAX) {outputMAX = output; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
	break;
	} while (next_permutation(phase, phase+5));
#ifdef _DEBUG_
	printf("INSTS:"); for (int i = 0; i < instTOT; i++) { printf("%lld ", inst[i]); }
#endif
	printf("\n");
printf("***OUTPUTMAX: %lld\n", outputMAX);
	printf("PHASEMAX:\n"); for (int i = 0; i < 5; i++) { printf("%d ", phaseMAX[i]); } printf("g\n"); //getchar();

fclose(a);
}
