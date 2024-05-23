#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//static void *array[40];
unsigned long long regb[10] = {0};

#define getchar()

//unsigned long long LIM = 10551348;
unsigned long long LIM = 940;
void printit();
int times = 1;
int ti = 0;
int main(void) {
//	int fd = dup(1); close(1);
static void *array[] = { &&zero, &&one,&&two,&&three, &&four, &&five, &&six, &&seven,&&eight, &&nine, &&ten, &&eleven, &&twelve, &&thirteen,&&fourteen, &&fifteen, &&sixteen, &&seventeen, &&eighteen, &&nineteen, &&twenty, &&twentyone, &&twentytwo, &&twentythree, &&twentyfour, &&twentyfive, &&twentysix, &&twentyseven, &&twentyeight, &&twentynine, &&thirty, &&thirtyone, &&thirtytwo, &&thirtythree, &&thirtyfour, &&thirtyfive, &&thirtysix};

regb[0] = 0;
zero:
//printf("addi 1 16 1\n"); getchar();
regb[1] = regb[1] + 16;
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
one:
//printf("here at 1:: "); fflush(stdout);
//printf("seti 1 8 2\n"); getchar();
regb[2] = 1;
regb[1] = regb[1]+1;
two:
//printf("here at 2:: "); fflush(stdout);
//printf("seti 1 5 4\n"); getchar();
regb[4] = 1;
regb[1] = regb[1]+1;
three:
//printf("here at 3"); fflush(stdout);
//printf("mulr 2 4 3\n"); getchar();
regb[3] = regb[2] * regb[4];
regb[1] = regb[1]+1;
printit();
four:
//printf("here at 4"); fflush(stdout);
//printf("eqrr 3 5 3\n"); getchar();
if (regb[3] == regb[5]) {printf("%llu * %llu (%d)\n", regb[2], regb[4], ti);ti++; regb[3] = 1;} else {regb[3] = 0;}
regb[1] = regb[1]+1;
five:
//printf("here at 5:: "); fflush(stdout);
//printf("addr 3 1 1\n"); getchar();
regb[1] = regb[3] + regb[1];
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
six:
//printf("here at 6:: "); fflush(stdout);
//printf("addi 1 1 1\n"); getchar();
regb[1] = regb[1] + 1;
regb[1] = regb[1]+1;
if (regb[1] <= 36) {
goto *array[regb[1]]; } else {goto thirtysix;}
seven:
printf("here at 7"); fflush(stdout);
//printf("addr 2 0 0 --- regb[2] + regb[0] is regb[0]\n"); getchar();
//if (regb[0] < 10551340) { regb[0] = 10551340; } else { regb[0]++;	}
//regb[0] = 10551350;
printf("BEF regb[0] + regb[2] %llu + %llu -- ", regb[2], regb[0]);
regb[0] = regb[2] + regb[0];
regb[1] = regb[1]+1;
printf(" AFT -> %llu\n", regb[0]);
eight:
//printf("here at 8::: "); fflush(stdout);
//printf("addi 4 1 4\n"); getchar();
//CONOR1
/*
	if (regb[4] < LIM) {
		regb[4] = LIM;
	} else if (regb[4] >= LIM) {
		regb[4] = regb[4] + 1;
	}
*/
regb[4] = regb[4] + 1;
regb[1] = regb[1]+1;
nine:
//printf("here at 9"); fflush(stdout);
//printf("gtrr 4 5 3\n"); getchar();
if (regb[4] > regb[5]) {regb[3] = 1;} else {regb[3] = 0;}
regb[1] = regb[1]+1;
ten:
//printf("here at 10:: "); fflush(stdout);
//printf("addr 1 3 1\n"); getchar();
regb[1] = regb[1] + regb[3];
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
eleven:
//printf("here at 11:: "); fflush(stdout);
//printf("seti 2 8 1\n"); getchar();
regb[1] = 2;
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
twelve:
//printf("here at 12:: "); fflush(stdout);
//printf("addi 2 1 2\n"); getchar();
//if (regb[2] < 10550339) { regb[2] = 10550339; } else { regb[2]++; }
//CONOR2
/*
	if (regb[2] < LIM) {
		regb[2] = LIM;
	} else if (regb[2] >= LIM) {
		regb[2] = regb[2] + 1;
	}
*/
regb[2] = regb[2]+1;
regb[1] = regb[1]+1;
thirteen:
//printf("here at 13:: "); fflush(stdout);
//printf("gtrr 2 5 3\n"); getchar();
if (regb[2] > regb[5]) {regb[3] = 1;} else {regb[3] = 0;}
regb[1] = regb[1]+1;
fourteen:
//printf("here at 14:: "); fflush(stdout);
//printf("addr 3 1 1\n"); getchar();
regb[1] = regb[3] + regb[1];
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
fifteen:
//printf("here at 15:: "); fflush(stdout);
//printf("seti 1 8 1\n"); getchar();
regb[1] = 1;
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
sixteen:
//printf("here at 16:: "); fflush(stdout);
//printf("mulr 1 1 1\n"); getchar();
//printf("BEFORE %llu = %llu * %llu\n", regb[1] *regb[1], regb[1], regb[1]);
regb[1] = regb[1] * regb[1];
//printf("AFTER %llu \n", regb[1]);
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
seventeen:
//printf("here at 17:: "); fflush(stdout); 
//printf("addi 5 2 5\n"); getchar();
regb[5] = regb[5] + 2;
regb[1] = regb[1]+1;
eighteen:
//printf("here at 18:: "); fflush(stdout);
//printf("mulr 5 5 5\n"); getchar();
regb[5] = regb[5] * regb[5];
regb[1] = regb[1]+1;
nineteen:
//printf("here at 19"); fflush(stdout);
//printf("mulr 1 5 5\n"); getchar();
regb[5] = regb[1] * regb[5];
regb[1] = regb[1]+1;
twenty:
//printf("here at 20"); fflush(stdout);
//printf("muli 5 11 5\n"); getchar();
regb[5] = regb[5] * 11;
regb[1] = regb[1]+1;
twentyone:
//printf("here at 21"); fflush(stdout);
//printf("addi 3 5 3\n"); getchar();
regb[3] = regb[3] + 5;
regb[1] = regb[1]+1;
twentytwo:
//printf("here at 22"); fflush(stdout);
//printf("mulr 3 1 3\n"); getchar();
regb[3] = regb[3] * regb[1];
regb[1] = regb[1]+1;
twentythree:
//printf("here at 23"); fflush(stdout);
//printf("addi 3 4 3\n"); getchar();
regb[3] = regb[3] + 4;
regb[1] = regb[1]+1;
twentyfour:
//printf("here at 24"); fflush(stdout);
//printf("addr 5 3 5\n"); getchar();
regb[5] = regb[5] + regb[3];
regb[1] = regb[1]+1;
twentyfive:
//printf("here at 25:: "); fflush(stdout);
//printf("addr 1 0 1 == regb[1] + regb[0] = regb[1]\n"); getchar();
regb[1] = regb[1] + regb[0];
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
twentysix:
//printf("here at 26:: "); fflush(stdout);
//printf("seti 0 7 1\n"); getchar();
regb[1] = 0;
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
twentyseven:
//printf("here at 27"); fflush(stdout);
//printf("setr 1 1 3\n"); getchar();
regb[3] = regb[1];
regb[1] = regb[1]+1;
twentyeight:
//printf("here at 28"); fflush(stdout);
//printf("mulr 3 1 3\n"); getchar();
regb[3] = regb[3] * regb[1];
regb[1] = regb[1]+1;
twentynine:
//printf("here at 29"); fflush(stdout);
//printf("addr 1 3 3\n"); getchar();
regb[3] = regb[1] + regb[3];
regb[1] = regb[1]+1;
thirty:
//printf("here at 30"); fflush(stdout);
//printf("mulr:: 1 3 3\n"); getchar();
//printf("mulr %llu * %llu \n", regb[1], regb[3]); getchar();
regb[3] = regb[1] * regb[3];
regb[1] = regb[1]+1;
thirtyone:
//printf("here at 31"); fflush(stdout);
//muli 3 14 3
//printf("muli:: %llu * %d\n", regb[3], 14); getchar();
regb[3] = regb[3] * 14;
regb[1] = regb[1]+1;
thirtytwo:
//printf("here at 32"); fflush(stdout);
//printf("mulr 3 1 3\n"); getchar();
regb[3] = regb[3] * regb[1];
regb[1] = regb[1]+1;
thirtythree:
//printf("here at 33"); fflush(stdout);
//printf("addr 5 3 5\n"); getchar();
regb[5] = regb[5] + regb[3];
regb[1] = regb[1]+1;
thirtyfour:
//printf("here at 34"); fflush(stdout);
//printf("seti 0 9 0 === regb zero to zero\n"); getchar();
regb[0] = 0;
regb[1] = regb[1]+1;
thirtyfive:
//printf("here at 35:: "); fflush(stdout);
//printf("seti 0 0 1\n"); getchar();
regb[1] = 0;
regb[1] = regb[1]+1;
printit();
if (regb[1] <= 36) { goto *array[regb[1]]; } else {goto thirtysix;}
thirtysix:
//printf("here at 36"); fflush(stdout);

//dup2(fd, 1);
printf("regb[0] is %llu\n", regb[0]); fflush(stdout);
}

void printit() {
	return;
	printf("%llu [[%llu]] %llu %llu %llu %llu\n", regb[0], regb[1], regb[2], regb[3], regb[4], regb[5]); getchar();
}
