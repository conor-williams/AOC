#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2019 day5 part1\n"
#define _DEBUG_
#define MAX 200000
char instruction    [MAX][10];
char instructionOrig[MAX][10];
int instTOT = 0;
int inst[MAX];

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
	for (int i = 0 ; i < MAX; i++) {
		strcpy(instruction    [MAX], "\0");
		strcpy(instructionOrig[MAX], "\0");
		inst[MAX] = 0;
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
	for (int i = 0; i < strlen(line1); i++) {
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
	int input = 1;
	printf("START-------------\n");
	int in = 0;
	for (int i = 0; i < instTOT; i++) {
		strcpy(instructionOrig[i], instruction[i]);
	}
	for (int i = 0; i < instTOT; i++) {
		printf("InstNUM: (%d) ", i); fflush(stdout);
		printf(" is [%d]\n", inst[i]); fflush(stdout);
		//printf("ORIG was [%s,%s,%s,%s]\n", instructionOrig[i], instructionOrig[i+1], instructionOrig[i+2], instructionOrig[i+3]);
		
		getchar();
/*
		if (inst[i] < instTOT) {
			printf(" is [%d]\n", inst[inst[i]]); fflush(stdout);
		}
*/
		if (in == 1) {getchar();}
		if (instruction[i][strlen(instruction[i])-1] == '3') {
		//if (inst[i] == 3) 
			printf("got a 3 (using %d) -> [%d]\n", input, inst[i+1]);
			inst[inst[i+1]] = input;
			char inputS[10];
			sprintf(inputS, "%d", input);
			strcpy(instruction[inst[i+1]], inputS);
			i++;
		} else if (instruction[i][strlen(instruction[i])-1] == '4') {
			printf("got a 4\n"); fflush(stdout);
			printf("OUT: %d\n", inst[inst[i+1]]);
			if (inst[inst[i+1]] != 0) {
				printf("not zero (pos: inst[i+1]) %d... ", inst[i+1]); //getchar();
			} else {
				printf("ZERO at address %d\n", inst[i+1]); //getchar();
			}
			i++;
		} else if (instruction[i][strlen(instruction[i])-1] == '9' && instruction[i][strlen(instruction[i])-2] == '9') {
			printf("GOT QUIT 99\n"); //in = 1; //getchar();
		} else if (instruction[i][strlen(instruction[i])-1] == '1' || instruction[i][strlen(instruction[i])-1] == '2') {
			int err = 0;
			printf("gota proper: WAS: %s\n", instruction[i]);
			//printf("WAS: %07d\n", inst[i]);
			char tmpStr[20];
			sprintf(tmpStr, "%07d", inst[i]);
			for (int k = 0; k < 4; k++) {
				instruction[i][k] = tmpStr[strlen(tmpStr)-(3-k)-1];
			}
			int mypos = inst[i+3];
			printf("mypos is %d\n", inst[i+3]); fflush(stdout);
			instruction[i][4] = '\0';
			printf("NOW: %s\n", instruction[i]); 
			int val1, val2, ans;
			if (instruction[i][0] == '0') {val1 = inst[inst[i+2]]; printf("pos val1 %d\n", inst[i+2]);}
			else if (instruction[i][0] == '1') {val1 = inst[i+2]; }
			if (instruction[i][1] == '0') {val2 = inst[inst[i+1]]; printf("pos val2 %d\n", inst[i+1]);}
			else if (instruction[i][1] == '1') {val2 = inst[i+1];}
	
			if (instruction[i][3] == '2') {
				printf("%d **** %d\n", val1, val2);
				ans = val1 * val2;
			} else if (instruction[i][3] == '1') {
				printf("%d ++++ %d\n", val1, val2);
				ans = val1 + val2;
			} else {
				printf("UNK: ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); //getchar();
				err = 1;
			}
			if (err == 0) {
				printf("ANS (%d) -> pos %d mypos %d\n", ans, inst[i+3], mypos); fflush(stdout);
				inst[mypos] = ans;
				char ansS[10]; sprintf(ansS, "%d", ans); strcpy(instruction[inst[i+3]], ansS);
				i += 3;
			}
		} else {
			printf("UNKNOWN: out of sync [%c]??\n", instruction[i][strlen(instruction[i])-1] ); //getchar();
		}
	}
	printf("INSTS:");
	for (int i = 0; i < instTOT; i++) {
		printf("%d ", inst[i]);
	}
	printf("\n");
fclose(a);
}
