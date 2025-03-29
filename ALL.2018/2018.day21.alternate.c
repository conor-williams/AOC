#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
unsigned long long regb[10] = {0};
//#define getchar()
void printit();
unsigned long long minCount = 99999999999;
unsigned long long maxCount = 0;
unsigned long long minb0;
unsigned long long maxb0;


#define INTERVAL 4

void TimerStop(int signum);
void TimerSet(int interval);
FILE *a;
int REG0 = 0;
int tim = 0;

void TimerStop(int signum) {
        printf("\x1b[H");
        printf("\x1b[%dB", 4);
        printf("Timer ran out! Stopping timer %d\n", REG0);
        fclose(a);
        exit(0);
}

void TimerSet(int interval) {
    //printf("starting timer\n");
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


int main(void) {
//TimerSet(INTERVAL);
static void *array[] = { &&zero, &&one,&&two,&&three, &&four, &&five, &&six, &&seven,&&eight, &&nine, &&ten, &&eleven, &&twelve, &&thirteen,&&fourteen, &&fifteen, &&sixteen, &&seventeen, &&eighteen, &&nineteen, &&twenty, &&twentyone, &&twentytwo, &&twentythree, &&twentyfour, &&twentyfive, &&twentysix, &&twentyseven, &&twentyeight, &&twentynine, &&thirty, &&thirtyone};

//regb[0] = (unsigned long long)15328188; //YES
//regb[0] = (unsigned long long)7902108;
//regb[0] = (unsigned long long)9784884;
//regb[0] = (unsigned long long)2828916;
//regb[0] = (unsigned long long)2873524;
//regb[0] = 13311888; ///YES
////////////////////////

unsigned long long compar = 0;
unsigned long long myAr[] = {

1000 };
///////////////////////////////////
///////////////////////
//for (unsigned long long k = 11900000; myAr[k] !=1000 ; k++) {
for (unsigned long long k = 0; k < 10; k++) {
tim = 0;
for (int i = 0; i < 6; i++) { regb[i] = 0; }
//regb[0] = (unsigned long long)15328188; //YES
	//regb[0] = myAr[k];
	//regb[0] = k;
	//regb[0] = 13311888;
	regb[0] = 12565657;
//regb[0] = 10025910;
	//printf("myAr[%d] is %llu\n", k, myAr[k]);

//regb[0] = 6483199;
//regb[0]= 9212376;
unsigned long long count = 0;
zero:
//seti 123 0 1
//printf("seti 123 0 1");
regb[1] = 123;
regb[4] = regb[4]+1; 
count++;
//printit();
one:
//bani 1 456 1
//printf("bani 1 456 1");
regb[1] = regb[1] & 456;
regb[4] = regb[4]+1; 
count++;
//printit();
two:
//eqri 1 72 1
//printf("eqri 1 72 1");
//printf("ANS: %d\n", 123 & 456); getchar();
if (regb[1] == 72) {regb[1] = 1;} else {regb[1] = 0;}
regb[4] = regb[4]+1; 
count++;
//printit();
three:
//addr 1 4 4
//printf("addr 1 4 4");
regb[4] = regb[1] + regb[4];
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
four:
//seti 0 0 4
//printf("seti 0 0 4");
regb[4] = 0;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
five:
//seti 0 3 1
//printf("seti 0 3 1");
regb[1] = 0;
regb[4] = regb[4]+1; 
count++;
//printit();
six:
//bori 1 65536 2
//printf("bori 1 65536 2");
regb[2] = regb[1] | 65536;
regb[4] = regb[4]+1; 
count++;
//printit();
seven:
//seti 7902108 7 1
//printf("seti 7902108 7 1");
regb[1] = 7902108;
regb[4] = regb[4]+1; 
count++;
//printit();
eight:
//bani 2 255 5
//printf("bani 2 255 5");
//CONOR4
regb[5] = regb[2] & 255;
regb[4] = regb[4]+1; 
count++;
//printit();
nine:
//addr 1 5 1
//printf("addr 1 5 1");
regb[1] = regb[1] + regb[5];
regb[4] = regb[4]+1; 
count++;
//printit();
ten:
//bani 1 16777215 1
//printf("bani 1 16777215 1");
regb[1] = regb[1] & 16777215;
regb[4] = regb[4]+1; 
count++;
//printit();
eleven:
//muli 1 65899 1
//printf("muli 1 65899 1");
regb[1] = regb[1] * 65899;
regb[4] = regb[4]+1; 
count++;
//printit();
twelve:
//bani 1 16777215 1
//printf("bani 1 16777215 1");
regb[1] = regb[1] & 16777215;
regb[4] = regb[4]+1; 
count++;
//printit();
thirteen:
//gtir 256 2 5
//printf("gtir 256 2 5");
if (256 > regb[2]) {regb[5] = 1;} else {regb[5] = 0;}
regb[4] = regb[4]+1; 
count++;
//printit();
fourteen:
//addr 5 4 4
//printf("addr 5 4 4");
regb[4] = regb[5] + regb[4];
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
fifteen:
//addi 4 1 4
//printf("addi 4 1 4");
regb[4] = regb[4] + 1;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
sixteen:
//seti 27 0 4
//printf("seti 27 0 4");
regb[4] = 27;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
seventeen:
//seti 0 0 5
//printf("seti 0 0 5");
regb[5] = 0;
regb[4] = regb[4]+1; 
count++;
//printit();
eighteen:
//addi 5 1 3
//printf("addi 5 1 3");
//CONOR2
/*
if (regb[3] < 65530) {
	regb[3] = 65530;
} else {
	regb[3] = 65536;
}
*/

regb[3] = regb[5] + 1;
regb[4] = regb[4]+1; 
count++;
//printit();
nineteen:
//muli 3 256 3
//printf("muli 3 256 3");
///CONOR1
/*
if (regb[3] < 65530) {
	regb[3] = 65530;
} else {
	regb[3] = 65537;
}
*/
regb[3] = regb[3] * 256;
regb[4] = regb[4]+1; 
count++;
//printit();
twenty:
//gtrr 3 2 3
//printf("gtrr 3 2 3");
if (regb[3] > regb[2]) {regb[3] = 1;} else {regb[3] = 0;}
regb[4] = regb[4]+1; 
count++;
//printit();
twentyone:
//addr 3 4 4
//printf("addr 3 4 4");
regb[4] = regb[3] + regb[4];
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
twentytwo:
//addi 4 1 4
//printf("addi 4 1 4");
regb[4] = regb[4] + 1;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
twentythree:
//seti 25 2 4
//printf("seti 25 2 4");
regb[4] = 25;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
twentyfour:
//addi 5 1 5
//printf("addi 5 1 5");
//CONOR3
//regb[5] = regb[5] + 65530;
//printf(" NO\n");
///continue;
regb[5] = regb[5] + 1;
regb[4] = regb[4]+1; 
count++;
//if (regb[5] > 65536) { goto twentysix; }
//printit();
twentyfive:
//seti 17 2 4
//printf("seti 17 2 4");
regb[4] = 17;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
twentysix:
//setr 5 1 2
//printf("setr 5 1 2");
regb[2] = regb[5];
regb[4] = regb[4]+1; 
count++;
//printit();
twentyseven:
//seti 7 2 4
//printf("seti 7 2 4");
regb[4] = 7;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
twentyeight:
//eqrr 1 0 5
//printf("eqrr 1 0 5");
//if (regb[1] > 11900000 && regb[1] < 12990000) {
	tim++;
	printf("%d regb[1] == regb[0] %llu V %llu\n", tim, regb[1], regb[0]);
	getchar();
	continue;
	//if (tim > 5000) { continue; }
//}
//
//goto thirtyone;
compar = regb[1];

if (regb[1] == regb[0]) {regb[5] = 1;} else {regb[5] = 0;}
regb[4] = regb[4]+1; 
count++;
//printit();
twentynine:
//addr 5 4 4
//printf("addr 5 4 4");
regb[4] = regb[5] + regb[4];
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
thirty:
//seti 5 9 4
//printf("seti 5 9 4");
regb[4] = 5;
regb[4] = regb[4]+1; 
count++;
//printit();
if (regb[4] <= 30) {goto *array[regb[4]];} else {goto thirtyone;}
thirtyone:
	//if (count < minCount) {minCount = count; minb0 = regb[0];}
	//if (count > maxCount) {maxCount = count; maxb0 = regb[0];}
	printf("tim is %d\n", tim);
	if (regb[1] > 11900000 && regb[1] < 14990000) {
		printf("at thirtyone -- count [[%llu]] regb[0]:: %llu\n", count, regb[0]);
		printf("regb[1]: %llu\n", regb[1]);
	}
}
//printf("**minCount is %llu minb0: %llu\n", minCount, minb0);
//printf("**maxCount is %llu maxb0: %llu\n", maxCount, maxb0);
}
void printit() { printf("\n%llu %llu %llu %llu [[%llu]] %llu\n", regb[0], regb[1], regb[2], regb[3], regb[4], regb[5]); getchar(); }
