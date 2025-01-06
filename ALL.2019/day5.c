#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx, leny;
#define DAY "2019 day5 part2\n"
#define _DEBUG_
#define MAX 2000
char instruction    [MAX][10];
char instructionOrig[MAX][10];
int instTOT = 0;
int inst[MAX];
int instOrig[MAX];
int fd;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); fd = dup(1); close(1);
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
	int input[100] = {0};
	int inputCounter = 0;
	do {	
		count = 1;
		for (int i = 0; i < instTOT; i++) {
			strcpy(instruction[i], instructionOrig[i]);
			inst[i] = instOrig[i];
		}
		inputCounter = 0;
		if (count == 1) {/*INPUTCONOR*/input[0] = 1;}
	for (int i = 0; i < instTOT; i++) {
		printf("\nNEW NEW NEW:::"); fflush(stdout);
		printf("POS InstNUM: (%d) ", i); fflush(stdout);
		printf(" is [%d] ", inst[i]); fflush(stdout);
		printf("(also is [%s])\n", instruction[i]); fflush(stdout); getchar();
		
		if (in == 1) {getchar();}
		if (instruction[i][strlen(instruction[i])-1] == '3') {
			printf("got a 3 (using %d) -> [%d]\n", input[inputCounter], inst[i+1]); 
			inst[inst[i+1]] = input[inputCounter];
			char inputS[10]; sprintf(inputS, "%d", input[inputCounter]);
			strcpy(instruction[inst[i+1]], inputS);
			inputCounter++;
			i++;
		} else if (instruction[i][strlen(instruction[i])-1] == '4') {
			printf("got a 4 look@ %d contains %d\n", inst[i+1], inst[inst[i+1]]); fflush(stdout);
			
			printf("strlen: %d\n", (int)strlen(instruction[i]));
			if (strlen(instruction[i]) == 3 && instruction[i][0] == '1') {
				printf("or is it OUT: %d\n", inst[i+1]);
				printf("or is it OUTS: %s\n", instruction[i+1]);
			} else {
				printf("OUT: %d\n", inst[inst[i+1]]);
				printf("OUTS: %s\n", instruction[inst[i+1]]); getchar();
				if (inst[inst[i+1]] != 0) {
					dup2(fd, 1);
					printf("**ans %d\n", inst[inst[i+1]]);
					exit(0);
				}
			}
			getchar();
			//output = inst[inst[i+1]]; getchar();
			if (inst[inst[i+1]] != 0) {
				printf("not zero (pos: inst[i+1]) %d... ", inst[i+1]); //getchar();
			} else {
				printf("ZERO at address %d\n", inst[i+1]); //getchar();
			}
			i++;
		} else if (instruction[i][strlen(instruction[i])-1] == '9' && instruction[i][strlen(instruction[i])-2] == '9' && (strlen(instruction[i]) == 2)) {
			printf("GOT QUIT 99\n"); //in = 1; //getchar();
			break;
		} else if ((instruction[i][strlen(instruction[i])-1] == '1' || instruction[i][strlen(instruction[i])-1] == '2' || instruction[i][strlen(instruction[i])-1] == '5' || instruction[i][strlen(instruction[i])-1] == '6' || instruction[i][strlen(instruction[i])-1] == '7' || instruction[i][strlen(instruction[i])-1] == '8' ) && (strlen(instruction[i]) == 1 || instruction[i][strlen(instruction[i])-2] == '0' )) {
		        if ((instruction[i][strlen(instruction[i])-1] == '5' || instruction[i][strlen(instruction[i])-1] == '6' || instruction[i][strlen(instruction[i])-1] == '7' || instruction[i][strlen(instruction[i])-1] == '8' )) {
			      continue;
			}
			
			int err = 0;
			//printf("gota proper:1,2,5,6,7,8\nWAS: %s (%d)\n", instruction[i], inst[i]);
			char tmpStr[20];
			sprintf(tmpStr, "%07d", inst[i]);
			for (int k = 0; k < 4; k++) {
				instruction[i][k] = tmpStr[strlen(tmpStr)-(3-k)-1];
			}
			int mypos = inst[i+3];
			//printf("***mypos (where output will be :) is %d\n", inst[i+3]); fflush(stdout);
			instruction[i][4] = '\0';
			printf("NOW: %s\n", instruction[i]); 
			int val1, val2, ans;
			if (instruction[i][1] == '0') {val1 = inst[inst[i+1]]; printf("(pos0) val1 %d\n", inst[inst[i+1]]);}
			else if (instruction[i][1] == '1') {val1 = inst[i+1]; printf("(Npos1) val1 %d\n", val1);} 
			else { printf("HERE"); getchar(); val1 = inst[i+1]; /*val2 = inst[i+2]; goto clear;*/}

			if (instruction[i][0] == '0') {val2 = inst[inst[i+2]]; printf("(pos0) val2 %d\n", val2);}
			else if (instruction[i][0] == '1') {val2 = inst[i+2]; printf("(Npos1) val2 %d\n", val2);} 
			else { printf("HERE2"); getchar(); val2 = inst[i+2];}
	
			if (instruction[i][3] == '2') {
				printf("%d **** %d\n", val1, val2);
				ans = val1 * val2;
			} else if (instruction[i][3] == '1') {
				printf("%d ++++ %d\n", val1, val2);
				ans = val1 + val2;
			} else {
				printf("UNK: **ERROR: instruction[i][3] (%d) [%c%c]\n", i, instruction[i][2], instruction[i][3]); getchar();
				err = 10;
				getchar();
			}
			if (err == 0) {
				printf("ANS (%d) -> pos (i+3:%d) %d (mypos %d)\n", ans, i+3, inst[i+3], mypos); fflush(stdout);
				inst[mypos] = ans;
				char ansS[10]; sprintf(ansS, "%d", ans); strcpy(instruction[mypos], ansS);
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
		printf("AT END..."); getchar();
		break;
	} while (1);

fclose(a);
}
