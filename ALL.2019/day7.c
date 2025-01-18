#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
using namespace std;

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2019 day7 part1\n"
#define _DEBUG_
#define MAX 200000
char instruction    [MAX][10];
char instructionOrig[MAX][10];
int instTOT = 0;
int inst[MAX];
int instOrig[MAX];

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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
	for (int i = 0; i < newStart; i++) {
		inst[i] = atoi(instruction[i]);
	}
	instTOT = newStart;
	printf("START-------------\n");
	int in = 0;
	for (int i = 0; i < instTOT; i++) {
		strcpy(instructionOrig[i], instruction[i]);
		instOrig[i] = inst[i];
	}
	int count = 0;
	int phase[] = {0,1,2,3,4,-1};
	//int phase[] = {1,0,4,3,2,-1};
	int phaseMAX[5];
	int phaseCounter = 0;
	int output;
	int outputMAX = 0;
	int input[100] = {0};
	int inputCounter = 0;
	sort(phase, phase+5);
	do {	
		printf("PHASE:\n"); for (int i = 0; i < 6; i++) { printf("%d ", phase[i]); } printf("g\n"); 
		output = 0;
		phaseCounter = 0;
		count = 0;
restart:
		for (int i = 0; i < instTOT; i++) {
			strcpy(instruction[i], instructionOrig[i]);
			inst[i] = instOrig[i];
		}
		inputCounter = 0;
		if (phase[phaseCounter] == -1) {printf("phase -1\n"); phaseCounter=0; goto end;}
		count++;	
		if (count == 1) {input[1] = 0;      input[0] = phase[0]; phaseCounter++;} else
			if (count > 0)  {input[1] = output; input[0] = phase[phaseCounter]; phaseCounter++;}
		for (int i = 0; i < instTOT; i++) {
			printf("POS InstNUM: (%d) ", i); fflush(stdout);
			printf(" is [%d] ", inst[i]); fflush(stdout);
			printf("also is [%s]\n", instruction[i]); fflush(stdout);

			if (in == 1) {getchar();}
			if (instruction[i][strlen(instruction[i])-1] == '3') {
				printf("got a 3 (using %d) -> [%d]\n", input[inputCounter], inst[i+1]); 
				inst[inst[i+1]] = input[inputCounter];
				char inputS[10]; sprintf(inputS, "%d", input[inputCounter]);
				strcpy(instruction[inst[i+1]], inputS);
				inputCounter++;
				i++;
			} else if (instruction[i][strlen(instruction[i])-1] == '4') {
				printf("got a 4\n"); fflush(stdout);
				printf("OUT: %d\n", inst[inst[i+1]]);
				printf("OUTS: %s\n", instruction[inst[i+1]]);
				output = inst[inst[i+1]];
				if (inst[inst[i+1]] != 0) {
					printf("not zero (pos: inst[i+1]) %d... ", inst[i+1]); //getchar();
				} else {
					printf("ZERO at address %d\n", inst[i+1]); //getchar();
				}
				i++;
			} else if (instruction[i][strlen(instruction[i])-1] == '9' && instruction[i][strlen(instruction[i])-2] == '9' && (strlen(instruction[i]) == 2)) {
				printf("GOT QUIT 99\n"); //in = 1; //getchar();
				goto restart;
			} else if ((instruction[i][strlen(instruction[i])-1] == '1' || instruction[i][strlen(instruction[i])-1] == '2' || instruction[i][strlen(instruction[i])-1] == '5' || instruction[i][strlen(instruction[i])-1] == '6' || instruction[i][strlen(instruction[i])-1] == '7' || instruction[i][strlen(instruction[i])-1] == '8' ) && (strlen(instruction[i]) == 1 || instruction[i][strlen(instruction[i])-2] == '0' )) {
				int err = 0;
				printf("gota proper:1,2,5,6,7,8\nWAS: %s (%d)\n", instruction[i], inst[i]);
				char tmpStr[20];
				sprintf(tmpStr, "%07d", inst[i]);
				for (int k = 0; k < 4; k++) {
					instruction[i][k] = tmpStr[strlen(tmpStr)-(3-k)-1];
				}
				int mypos = inst[i+3];
				printf("***mypos (->output) is %d\n", inst[i+3]); fflush(stdout);
				instruction[i][4] = '\0';
				printf("NOW: %s\n", instruction[i]); 
				int val1, val2, ans;
				if (instruction[i][1] == '0') {val1 = inst[inst[i+1]]; printf("pos val1 %d\n", inst[i+1]);}
				else if (instruction[i][1] == '1') {val1 = inst[i+1];} 
				else { printf("HERE"); getchar(); val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

				if (instruction[i][0] == '0') {val2 = inst[inst[i+2]]; printf("pos val2 %d\n", inst[i+2]);}
				else if (instruction[i][0] == '1') {val2 = inst[i+2]; } 
				else { printf("HERE2"); getchar(); val2 = inst[i+2];}

//clear:
				if (instruction[i][3] == '2') {
					printf("%d **** %d\n", val1, val2);
					ans = val1 * val2;
				} else if (instruction[i][3] == '1') {
					printf("%d ++++ %d\n", val1, val2);
					ans = val1 + val2;
				} else if (instruction[i][3] == '5') {
					if (val1 != 0) {i = val2-1; err = 2;} else {err = 1;}
				} else if (instruction[i][3] == '6') {
					if (val1 == 0) {i = val2-1; err = 2;} else {err = 1;}
				} else if (instruction[i][3] == '7') {
					if (val1 < val2) {ans = 1;} else {ans = 0;}
					printf("%d <<<<< %d\n", val1, val2); 
				} else if (instruction[i][3] == '8') {
					if (val1 == val2) {ans = 1;} else {ans = 0;}
				} else {
					printf("UNK: **ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); getchar();
					err = 1;
					getchar();
				}
				if (err == 0) {
					printf("ANS (%d) -> pos (i+3:%d) %d mypos %d\n", ans, i+3, inst[i+3], mypos); fflush(stdout);
					inst[mypos] = ans;
					char ansS[10]; sprintf(ansS, "%d", ans); strcpy(instruction[mypos], ansS);
				}
				if (err != 2) {
					i += 3;
				}
			} else {
				printf("UNKNOWN: out of sync [xxx%c]??\n", instruction[i][strlen(instruction[i])-1] );
				//i+= 3;
			}
		}
end:
		if (output > outputMAX) {outputMAX = output; phaseMAX[0] = phase[0]; phaseMAX[1] = phase[1]; phaseMAX[2] = phase[2]; phaseMAX[3] = phase[3]; phaseMAX[4] = phase[4];}
	} while (next_permutation(phase, phase+5));
	printf("INSTS:");
	for (int i = 0; i < instTOT; i++) {
		printf("%d ", inst[i]);
	}
	printf("\n");
	printf("PHASEMAX:\n"); for (int i = 0; i < 5; i++) { printf("%d ", phaseMAX[i]); } printf("g\n"); //getchar();
	fflush(stdout); dup2(fd, 1);
	printf("***OUTPUTMAX: %d\n", outputMAX);

	fclose(a);
}
